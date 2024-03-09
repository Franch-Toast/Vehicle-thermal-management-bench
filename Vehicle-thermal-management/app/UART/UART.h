/*
 * @Author: Franch-Toast
 * @Date: 2023-12-24 11:53:25
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-02-28 20:02:06
 * @Description:
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood.
 * Welcome to communicate with each other!
 */

#ifndef _UART_H_
#define _UART_H_

#include "linflexd_uart_config.h"
#include "printf/printf.h"
#include "string.h"

#define PRINTF_UART (2U)

#define BUFFER_MAX 24 // 缓冲区大小

/* 定义串口传输帧结构体 */
typedef struct 
{
    uint8_t data_length;// 数据的长度
    uint8_t data[35]; // 数据内容，这里暂时给35的大小
}Serial_data_frame_t;

typedef struct
{
    uint8_t head;                 // 缓冲区头部位置
    uint8_t tail;                 // 缓冲区尾部位置
    uint8_t ringBuff[BUFFER_MAX]; // 缓冲区数组
} ringBuffer_t;

void UART_init(void);
void RingBuff_Write(uint8_t data);
uint8_t RingBuff_Read_frame(void);

void RingBuff_Read_Byte(uint8_t *pData);

extern ringBuffer_t buffer;

#endif
