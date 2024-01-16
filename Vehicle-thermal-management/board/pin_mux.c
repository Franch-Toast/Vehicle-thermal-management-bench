/*
 * @Author: Franch-Toast
 * @Date: 2023-12-23 23:43:52
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-01-15 16:03:16
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
 * @file pin_mux.c
 * @brief 
 * 
 */



#include "pin_mux.h"

pin_settings_config_t g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0] = {
    /*PTA_8-144-LINFlexD2_RX-*/
    {
        .base=PCTRLA,
        .pinPortIdx = 8U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_ALT2,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = false,
        .digitalFilter = false,
        .gpioBase = GPIOA,
        .direction=GPIO_INPUT_DIRECTION,
        .initValue=0,
    },
    /*PTA_9-143-LINFlexD2_TX-*/
    {
        .base=PCTRLA,
        .pinPortIdx = 9U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_ALT2,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = false,
        .digitalFilter = false,
        .gpioBase = GPIOA,
        .direction=GPIO_INPUT_DIRECTION,
        .initValue=0,
    },
    /*PTB_12-98-eTMR0_CH0-*/
    {
        .base=PCTRLB,
        .pinPortIdx = 12U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_ALT2,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = false,
        .digitalFilter = false,
        .gpioBase = GPIOB,
        .direction=GPIO_INPUT_DIRECTION,
        .initValue=0,
    },
    /*PTC_0-53-eTMR1_CH6-*/
    {
        .base=PCTRLC,
        .pinPortIdx = 0U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_ALT6,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = false,
        .digitalFilter = false,
        .gpioBase = GPIOC,
        .direction=GPIO_OUTPUT_DIRECTION,
        .initValue=0,
    },
};


/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/