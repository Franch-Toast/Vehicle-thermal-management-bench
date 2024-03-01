/*
 * @Author: Franch-Toast
 * @Date: 2024-02-29 20:18:57
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-03-01 13:46:56
 * @Description:
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood.
 * Welcome to communicate with each other!
 */
#include "LIN_device_control.h"

/* 外部全局变量 */
extern linflexd_frame_t linMasterFrame;
extern SemaphoreHandle_t MuxSem_Handle;
extern Workbench_status_t Workbench_status; // 台架的状态

/************************************ 压缩机通讯 ************************************/

/* 更改压缩机的转速，变相等于开启压缩机 */
uint8_t Compressor_Set_Speed(uint16_t speed, uint16_t limit_power)
{
    status_t status = 0;
    xSemaphoreTake(MuxSem_Handle, portMAX_DELAY); // 加锁

    linMasterFrame.id = 0x30;
    linMasterFrame.dataLength = 7;                        // 七个字节
    memset(linMasterFrame.data, 0, 8);                    // 8个字节内容全部清0
    linMasterFrame.data[0] = (uint8_t)(limit_power / 40); // 第一个字节为压缩机允许功率，放大因数为40
    linMasterFrame.data[1] = (uint8_t)(speed / 50);       // 第二个字节为压缩机转速，放大因数为50
    linMasterFrame.data[2] = 0x01;                        // 第三个字节低两位压缩机允许运行

    status = LIN_Master_Send_Frame(); // 发送帧

    if (status != 0) // 如果发送失败了，则
    {
    }

    xSemaphoreGive(MuxSem_Handle); // 解锁
    return status;
}

/* 关闭压缩机 */
uint8_t Compressor_Shutdown(void)
{
    status_t status = 0;
    xSemaphoreTake(MuxSem_Handle, portMAX_DELAY); // 加锁

    linMasterFrame.id = 0x30;
    linMasterFrame.dataLength = 7;     // 七个字节
    memset(linMasterFrame.data, 0, 8); // 8个字节内容全部清0
    linMasterFrame.data[2] = 0x00;     // 第三个字节低两位压缩机停止运行
    status = LIN_Master_Send_Frame();  // 发送帧

    if (status != 0) // 如果发送失败了，则
    {
    }

    xSemaphoreGive(MuxSem_Handle); // 解锁
    return status;
}

/* 获取压缩机状态 */
uint8_t Compressor_Get_info(void)
{
    status_t status = 0;
    xSemaphoreTake(MuxSem_Handle, portMAX_DELAY); // 加锁

    linMasterFrame.id = 0x12;          // 帧ID为0x12
    linMasterFrame.dataLength = 8;     // 八个字节
    memset(linMasterFrame.data, 0, 8); // 8个字节内容全部清0

    status = LIN_Master_Receive_Frame(); // 接收帧

    if (status != 0) // 如果发送失败了，则
    {
    }

    /* 对接收数据进行解析 */

    Workbench_status.Compressor_status.compressor_speed = linMasterFrame.data[1];                                                // 转速：rpm
    Workbench_status.Compressor_status.temperature_basic_board = linMasterFrame.data[2];                                         // 基板温度：℃
    Workbench_status.Compressor_status.temperature_IGBT = linMasterFrame.data[3];                                                // IGBT温度：℃
    Workbench_status.Compressor_status.compressor_current = ((linMasterFrame.data[4])) | ((linMasterFrame.data[4] & 0x0F) << 8); // 电流：A
    Workbench_status.Compressor_status.compressor_voltage = linMasterFrame.data[6] | ((linMasterFrame.data[7] & 0x03) << 8);     // 电压：V
    Workbench_status.Compressor_status.compressor_status = linMasterFrame.data[7] & 0x38;                                        // 压缩机状态

    xSemaphoreGive(MuxSem_Handle); // 解锁
    return status;
}

/************************************ 电子膨胀阀通讯 ************************************/

/* 更改电子膨胀阀的开度 */
uint8_t Expansion_valve_Set_Open(uint16_t open)
{
    status_t status = 0;
    xSemaphoreTake(MuxSem_Handle, portMAX_DELAY); // 加锁

    linMasterFrame.id = 0x19;
    linMasterFrame.dataLength = 8;     // 8个字节
    memset(linMasterFrame.data, 0, 8); // 8个字节内容全部清0

    linMasterFrame.data[0] = (uint8_t)open;        // 第一二个字节为请求位置，两个字节的宽度，但是大小仅允许【0，480】
    linMasterFrame.data[1] = (uint8_t)(open >> 4); 

    linMasterFrame.data[2] = 0x01;                 // 第三个字节bit0允许使能膨胀阀
    linMasterFrame.data[3] = 0x00;                 // 第四个字节3个bit允许是否初始化
    status = LIN_Master_Send_Frame(); // 发送帧

    if (status != 0) // 如果发送失败了，则
    {
    }

    xSemaphoreGive(MuxSem_Handle); // 解锁
    return status;
}







/************************************ 三通阀通讯 ************************************/

/************************************ 四通阀通讯 ************************************/

/************************************ 四通阀通讯 ************************************/

/************************************ WPTC通讯 ************************************/
