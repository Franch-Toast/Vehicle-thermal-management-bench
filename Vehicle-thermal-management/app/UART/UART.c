/*
 * @Author: Franch-Toast
 * @Date: 2023-12-24 11:53:14
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2023-12-24 18:13:14
 * @Description: 
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood. 
 * Welcome to communicate with each other!
 */


#include "UART.h"
#include "linflexd_hw_access.h"



ringBuffer_t buffer; // 定义一个结构体

uint8_t Rx_Byte;

void RingBuff_Write(uint8_t data)
{
    buffer.ringBuff[buffer.tail] = data;     // 从尾部追加
    if (++buffer.tail >= BUFFER_MAX)        // 尾节点偏移
        buffer.tail = 0;                    // 大于数组最大长度 归零 形成环形队列
    if (buffer.tail == buffer.head) // 如果尾部节点追到头部节点，则修改头节点偏移位置丢弃早期数据
        if (++buffer.head >= BUFFER_MAX) // 这里直接自增
            buffer.head = 0;
}

uint8_t RingBuff_Read(uint8_t *pData)
{
    if (buffer.head == buffer.tail) // 如果头尾接触表示缓冲区为空
    {
        return 1; // 返回1，环形缓冲区是空的
    }
    else
    {
        *pData = buffer.ringBuff[buffer.head]; // 如果缓冲区非空则取头节点值并偏移头节点
        if (++buffer.head >= BUFFER_MAX)
            buffer.head = 0;
        return 0; // 返回0，表示读取数据成功
    }
}


void UART_Rx_Callback(void *driverState, uart_event_t event, void *userData)
{
    if (event == UART_EVENT_END_TRANSFER)
    {
        RingBuff_Write(Rx_Byte);
        LINFlexD_UART_DRV_StartReceiveUsingInterrupts_Personal(PRINTF_UART, &Rx_Byte, 1);
    }
    else if (event == UART_EVENT_RX_FULL)
    {
        
    }
}


void UART_init()
{
    LINFlexD_UART_DRV_Init(PRINTF_UART,&linflexd_uart_config0_State,&linflexd_uart_config0);
    LINFlexD_UART_DRV_InstallRxCallback(PRINTF_UART,UART_Rx_Callback,NULL);

    // LINFlexD_SetReceiverState(((LINFlexD_Type *)(0x4001D000)), true);
    LINFlexD_UART_DRV_StartReceiveUsingInterrupts_Personal(PRINTF_UART, &Rx_Byte, 1);
}



