/*
 * @Author: Franch-Toast
 * @Date: 2024-01-03 14:16:28
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-04-02 16:15:59
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
 * @file etmr_config.h
 * @brief
 *
 */

#ifndef __ETMR_CONFIG_H__
#define __ETMR_CONFIG_H__

#include "etmr_common.h"

#include "etmr_pwm_driver.h"

#include "etmr_ic_driver.h"

/*
 * Common
 */

/*
 * MC
 */

/*
 * PWM
 */
extern etmr_pwm_param_t ETMR_PWM_Config0;
extern etmr_pwm_ch_param_t ETMR_PWM_Config0IndChConfig[4];

/*
 * IC
 */
extern etmr_ic_param_t ETMR_IC_Config0;

/*
 * OC
 */

/*
 * QD
 */

#endif
