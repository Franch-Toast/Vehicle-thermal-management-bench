
/*
 *  Copyright 2020-2023 Yuntu Microelectronics co.,ltd
 *  All rights reserved.
 * 
 *  YUNTU Confidential. This software is owned or controlled by YUNTU and may only be
 *  used strictly in accordance with the applicable license terms. By expressly
 *  accepting such terms or by downloading, installing, activating and/or otherwise
 *  using the software, you are agreeing that you have read, and that you agree to
 *  comply with and are bound by, such license terms. If you do not agree to be
 *  bound by the applicable license terms, then you may not retain, install,
 *  activate or otherwise use the software. The production use license in
 *  Section 2.3 is expressly granted for this software.
 * 
 * @file linflexd_uart_config.c
 * @brief 
 * 
 */



#include "linflexd_uart_config.h"


/*linflexd_uart_config0*/
linflexd_uart_state_t linflexd_uart_config0_State;
const linflexd_uart_user_config_t linflexd_uart_config0 = {
    .baudRate=115200U,
    .parityCheck=false,
    .parityType=LINFlexD_UART_PARITY_EVEN,
    .stopBitsCount=LINFlexD_UART_ONE_STOP_BIT,
    .wordLength=LINFlexD_UART_8_BITS,
    .txTransferType=LINFlexD_UART_USING_INTERRUPTS,
    .rxTransferType=LINFlexD_UART_USING_INTERRUPTS,
    .rxDMAChannel=0,
    .txDMAChannel=0,
};
