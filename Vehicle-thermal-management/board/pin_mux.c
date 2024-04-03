
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
        .direction=GPIO_INPUT_DIRECTION,
        .initValue=0,
    },
    /*PTC_1-52-eTMR1_CH7-*/
    {
        .base=PCTRLC,
        .pinPortIdx = 1U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_ALT6,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = false,
        .digitalFilter = false,
        .gpioBase = GPIOC,
        .direction=GPIO_INPUT_DIRECTION,
        .initValue=0,
    },
    /*PTD_8-54-eTMR1_CH4-*/
    {
        .base=PCTRLD,
        .pinPortIdx = 8U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_ALT6,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = false,
        .digitalFilter = false,
        .gpioBase = GPIOD,
        .direction=GPIO_INPUT_DIRECTION,
        .initValue=0,
    },
    /*PTD_9-55-eTMR1_CH5-*/
    {
        .base=PCTRLD,
        .pinPortIdx = 9U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_ALT6,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = false,
        .digitalFilter = false,
        .gpioBase = GPIOD,
        .direction=GPIO_INPUT_DIRECTION,
        .initValue=0,
    },
    /*PTC_8-81-LINFlexD1_RX-*/
    {
        .base=PCTRLC,
        .pinPortIdx = 8U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_ALT2,
        .intConfig = PCTRL_INT_FALLING_EDGE,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = true,
        .digitalFilter = false,
        .gpioBase = GPIOC,
        .direction=GPIO_INPUT_DIRECTION,
        .initValue=0,
    },
    /*PTC_9-80-LINFlexD1_TX-*/
    {
        .base=PCTRLC,
        .pinPortIdx = 9U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_ALT2,
        .intConfig = PCTRL_INT_FALLING_EDGE,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = true,
        .digitalFilter = false,
        .gpioBase = GPIOC,
        .direction=GPIO_INPUT_DIRECTION,
        .initValue=0,
    },
    /*PTA_7-83-GPIO-LINFlexD1_SLEEPEN*/
    {
        .base=PCTRLA,
        .pinPortIdx = 7U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_AS_GPIO,
        .intConfig = PCTRL_INT_FALLING_EDGE,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = true,
        .digitalFilter = false,
        .gpioBase = GPIOA,
        .direction=GPIO_OUTPUT_DIRECTION,
        .initValue=1,
    },
    /*PTB_0-78-LINFlexD0_RX-*/
    {
        .base=PCTRLB,
        .pinPortIdx = 0U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_ALT2,
        .intConfig = PCTRL_INT_FALLING_EDGE,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = true,
        .digitalFilter = false,
        .gpioBase = GPIOB,
        .direction=GPIO_INPUT_DIRECTION,
        .initValue=0,
    },
    /*PTB_1-77-LINFlexD0_TX-*/
    {
        .base=PCTRLB,
        .pinPortIdx = 1U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_ALT2,
        .intConfig = PCTRL_INT_FALLING_EDGE,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = true,
        .digitalFilter = false,
        .gpioBase = GPIOB,
        .direction=GPIO_INPUT_DIRECTION,
        .initValue=0,
    },
    /*PTC_10-75-GPIO-LINFlexD0_SLEEPEN*/
    {
        .base=PCTRLC,
        .pinPortIdx = 10U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_AS_GPIO,
        .intConfig = PCTRL_INT_FALLING_EDGE,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = true,
        .digitalFilter = false,
        .gpioBase = GPIOC,
        .direction=GPIO_OUTPUT_DIRECTION,
        .initValue=1,
    },
    /*PTE_10-6-LINFlexD3_RX-*/
    {
        .base=PCTRLE,
        .pinPortIdx = 10U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_ALT5,
        .intConfig = PCTRL_INT_FALLING_EDGE,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = true,
        .digitalFilter = false,
        .gpioBase = GPIOE,
        .direction=GPIO_INPUT_DIRECTION,
        .initValue=0,
    },
    /*PTE_11-5-LINFlexD3_TX-*/
    {
        .base=PCTRLE,
        .pinPortIdx = 11U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_ALT5,
        .intConfig = PCTRL_INT_FALLING_EDGE,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = true,
        .digitalFilter = false,
        .gpioBase = GPIOE,
        .direction=GPIO_INPUT_DIRECTION,
        .initValue=0,
    },
    /*PTA_15-120-GPIO-*/
    {
        .base=PCTRLA,
        .pinPortIdx = 15U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .passiveFilter = false,
        .mux = PCTRL_MUX_AS_GPIO,
        .intConfig = PCTRL_INT_FALLING_EDGE,
        .rateSelect = PCTRL_FAST_SLEW_RATE,
        .clearIntFlag = true,
        .digitalFilter = false,
        .gpioBase = GPIOA,
        .direction=GPIO_OUTPUT_DIRECTION,
        .initValue=1,
    },
};


/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/