/*
 * @Author: Franch-Toast
 * @Date: 2023-12-24 11:53:14
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-02-28 13:04:03
 * @Description:
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood.
 * Welcome to communicate with each other!
 */

#include "UART.h"
#include "linflexd_hw_access.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* 上位机指令传输信号量 */
extern SemaphoreHandle_t Get_upper_order_Handle;

ringBuffer_t buffer; // 定义一个环形缓冲区

uint8_t Rx_Byte;

void RingBuff_Write(uint8_t data)
{
    buffer.ringBuff[buffer.tail] = data; // 从尾部追加
    if (++buffer.tail >= BUFFER_MAX)     // 尾节点偏移
        buffer.tail = 0;                 // 大于数组最大长度 归零 形成环形队列
    if (buffer.tail == buffer.head)      // 如果尾部节点追到头部节点，则修改头节点偏移位置丢弃早期数据
        if (++buffer.head >= BUFFER_MAX) // 这里直接自增
            buffer.head = 0;
}

void RingBuff_Read_frame(uint8_t *frame, uint8_t data_length)
{
    /* 已经传参进来了，所以不需要进行判断了 */
    // if (buffer.head == buffer.tail) // 如果头尾接触表示缓冲区为空
    // {
    //     return 1; // 返回1，环形缓冲区是空的
    // }

    memcpy(frame, buffer.ringBuff + buffer.head, data_length); // 直接memcpy
    // 由于 copy 等同于读，所以要修改缓冲区的指针
    if ((buffer.head += data_length) >= BUFFER_MAX)
        buffer.head = buffer.head - BUFFER_MAX;
    // return 0; // 返回0，表示读取数据成功
    
}
void RingBuff_Read_Byte(uint8_t *pData)
{
    /* 已经传参进来了，所以不需要进行判断了 */
    if (buffer.head == buffer.tail) // 如果头尾接触表示缓冲区为空
    {
        // return 1; // 返回1，环形缓冲区是空的
    }

    *pData = buffer.ringBuff[buffer.head];
    if (++buffer.head >= BUFFER_MAX)
        buffer.head = 0;
    // return 0; // 返回0，表示读取数据成功
}

/* 获取缓冲区中的消息的大小 */
uint8_t RingBuff_data_length(void)
{
    if (buffer.head <= buffer.tail)
        return (buffer.tail - buffer.head);
    else
        return BUFFER_MAX - (buffer.head - buffer.tail);
}

void UART_Rx_Callback(void *driverState, uart_event_t event, void *userData)
{
    // uint32_t ulReturn = taskENTER_CRITICAL_FROM_ISR();
    if (event == UART_EVENT_RX_FULL)
    {
        RingBuff_Write(Rx_Byte);
        LINFlexD_UART_DRV_StartReceiveUsingInterrupts_Personal(PRINTF_UART, &Rx_Byte, 1);
    }
    else if (event == UART_EVENT_TIMEOUT) // 串口空闲中断
    {
        BaseType_t xReturn = pdPASS;
        xReturn = xSemaphoreGive(Get_upper_order_Handle); // 给出二值信号量
    }
    // taskEXIT_CRITICAL_FROM_ISR(ulReturn);
}

void UART_init()
{
    LINFlexD_UART_DRV_Init(PRINTF_UART, &linflexd_uart_config0_State, &linflexd_uart_config0);
    LINFlexD_UART_DRV_InstallRxCallback(PRINTF_UART, UART_Rx_Callback, NULL);

    /* 创建二值信号量 */
    Get_upper_order_Handle = xSemaphoreCreateBinary();
    if (Get_upper_order_Handle != NULL)
        PRINTF("二值信号量创建成功！\n");

    LINFlexD_UART_DRV_StartReceiveUsingInterrupts_Personal(PRINTF_UART, &Rx_Byte, 1);
}
