/*
 * @Author: Franch-Toast
 * @Date: 2023-12-24 11:53:25
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-02-28 13:01:59
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

typedef struct
{
    uint8_t head;                 // 缓冲区头部位置
    uint8_t tail;                 // 缓冲区尾部位置
    uint8_t ringBuff[BUFFER_MAX]; // 缓冲区数组
} ringBuffer_t;

void UART_init(void);
void RingBuff_Write(uint8_t data);
void RingBuff_Read_frame(uint8_t *frame, uint8_t data_length);
uint8_t RingBuff_data_length(void);
void RingBuff_Read_Byte(uint8_t *pData);

extern ringBuffer_t buffer;

#endif
