/*
 * @Author: Franch-Toast
 * @Date: 2024-01-17 21:40:11
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-03-01 13:19:51
 * @Description:
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood.
 * Welcome to communicate with each other!
 */
#include "LIN.h"
#include "UART.h"
#include "linflexd_lin_driver.h"

/*
LincurrentEvent = 1 means master recv done,
LincurrentEvent = 2 means master send done,
LincurrentEvent = 3 means error happens
*/
volatile uint8_t LincurrentEvent = 0;
#define linMasterCurrentState linflexd_lin_config0_State

linflexd_frame_t linMasterFrame =
    {
        .id = 0x23,
        .checksumType = LIN_ENHANCED_CHECKSUM,
        .responseType = LIN_MASTER_RESPONSE,
        .dataLength = 8,
        .data = {0x01, 0xFA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

// 定义回调函数
static void linflexd_process_callback(uint32_t instance, void *state)
{
    linflexd_state_t *linState = (linflexd_state_t *)state;
    (void)instance;
    if (LINFlexD_HEADER_RECEIVED_EVENT == linState->currentEventId)
    {
    }
    else if (LINFlexD_DATA_RECEIVED_EVENT == linState->currentEventId)
    {
        LincurrentEvent = LINMaserRecvDone;
    }
    else if (LINFlexD_DATA_SENT_EVENT == linState->currentEventId)
    {
        LincurrentEvent = LINMasterSendDone;
    }
    else if (LINFlexD_OUTPUT_COMPARE_EVENT == linState->currentEventId)
    {
        LincurrentEvent = LINMasterError;
    }
    /* If any error happened, deal with it following */
    if (linState->errorStatus)
    {
        /* Master response */
        if (0x35 == linMasterFrame.id)
        {
            LincurrentEvent = LINMasterError;
        }
        /* Slave response */
        else if (0x32 == linMasterFrame.id)
        {
            LincurrentEvent = LINMasterError;
        }
        else
        {
        }
        linState->errorStatus = 0;
    }
}

// LIN主机 初始化
void LIN_MASTER_init()
{
    status_t status = STATUS_SUCCESS;
    status |= LINFlexD_DRV_Init(LINFlexD_Master, &linflexd_lin_config0, &linMasterCurrentState);
    LINFlexD_DRV_InstallCallback(LINFlexD_Master, linflexd_process_callback); // 注册回调函数
    if (status == STATUS_SUCCESS)
        PRINTF("LIN MASTER initialize successfully!\n");
    else
        PRINTF("LIN MASTER initialize fail!\n");
}

// LIN主机 发送帧
status_t LIN_Master_Send_Frame()
{
    status_t status = STATUS_SUCCESS;
    LincurrentEvent = 0;
    /* LIN Master Send a Frame */
    // linMasterFrame.id = 0x35;
    linMasterFrame.responseType = LIN_MASTER_RESPONSE; // 发送时，MCU作为主机必须为LIN_MASTER_RESPONSE模式
    status |= LINFlexD_DRV_MasterTransfer(LINFlexD_Master, &linMasterFrame);
    /* Wait until master transmission completed */
    while (0 == LincurrentEvent)
        ;
    if (LincurrentEvent == LINMasterSendDone)
        return status;
    return STATUS_ERROR;
}

// LIN主机 接收帧
status_t LIN_Master_Receive_Frame()
{
    status_t status = STATUS_SUCCESS;
    LincurrentEvent = 0;
    /* LIN Master receive a Frame */
    // linMasterFrame.id = 0x32;
    linMasterFrame.responseType = LIN_SLAVE_RESPONSE; // 接收时，MCU作为主机必须为LIN_SLAVE_RESPONSE模式
    status |= LINFlexD_DRV_MasterTransfer(LINFlexD_Master, &linMasterFrame);
    /* wait until master receive completed */
    while (0 == LincurrentEvent)
        ;
    if (LincurrentEvent == LINMasterSendDone)
        return status;
    return STATUS_ERROR;
}
