/*
 * @Author: Franch-Toast
 * @Date: 2024-01-17 17:09:21
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-03-14 18:44:30
 * @Description: 
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood. 
 * Welcome to communicate with each other!
 */

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
 * @file linflexd_lin_config.c
 * @brief 
 * 
 */


#include <stddef.h>
#include "linflexd_lin_config.h"


/*linflexd_lin_config0*/
linflexd_state_t linflexd_lin0_State;
linflexd_state_t linflexd_lin1_State;
linflexd_state_t linflexd_lin2_State;
linflexd_user_config_t linflexd_lin_config0 = {
    .baudRate=19200U,
    .nodeFunction=true,
    .breakLength=LINFlexD_BREAK_13_BIT,
    .autobaudEnable=false,
    .timeoutEnable=true,
    .responseTimeoutValue=14,
    .headerTimeoutValue=0,
    .filterCount=0,
    .slaveFilterCfgPtr=NULL,
};
