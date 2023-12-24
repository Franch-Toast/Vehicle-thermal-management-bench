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


#define  PRINTF_UART (2U)


void UART_init()
{
    LINFlexD_UART_DRV_Init(PRINTF_UART,&linflexd_uart_config0_State,&linflexd_uart_config0);
}



