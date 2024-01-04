
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
 * @file clock_config.c
 * @brief 
 * 
 */

#include "stddef.h"
#include "clock_config.h"

/*! @brief peripheral clock PeripheralClockConfig */

peripheral_clock_config_t clock_config0PeripheralClockConfig[2] = {
    {
        .clkName = LINFlexD2_CLK,
        .clkGate = true,
        .divider = DIV_BY_1,
        .clkSrc = CLK_SRC_DISABLED,
    },
    {
        .clkName = eTMR0_CLK,
        .clkGate = true,
        .divider = DIV_BY_1,
        .clkSrc = CLK_SRC_FIRC, // eTMR internal clock source is fixed Fast bus clock
    },
};

const scu_config_t clock_config0ScuConfig = {
    .fircEnable = true,
    .fircDeepSleepEnable = false,
    .sircDeepSleepEnable = true,
    .sircStandbyEnable = true,
    .sircPowerDownEnable = true,
    .sysClkSrc = SCU_SYSTEM_CLOCK_SRC_PLL,
    .fxoscConfig =
        {
            .enable = true,
            .bypassMode = false,
            .gainSelection = 5,
            .frequency = 24000000U,
        },
    .sxoscConfig = 
        {
            .enable = false,
            .gainSelection = 0,
            .bypassMode = false,
            .deepsleepEnable = false,
            .standbyEnable = false,
            .powerdownEnable = false,
            .frequency = 32768U,
        },
    .pllConfig =
        {
            .enable = true,
            .pllRefClock = SCU_PLL_REF_FXOSC_CLK,
            .pllFeedBackDiv = 10,
            .pllRefClkDiv = 1,
        },
    .sysDiv = SCU_SYS_CLK_DIV_BY_1,
    .fastBusDiv = SCU_SYS_CLK_DIV_BY_1,
    .slowBusDiv = SCU_SYS_CLK_DIV_BY_3,
    .flashDiv = SCU_SYS_CLK_DIV_BY_3,
    .clockOutConfig =
        {
            .enable = false,
            .source = SCU_CLKOUT_SEL_PLL_CLK,
            .divider = 1
        },
};


/*! @brief User Configuration structure clock_config0ClockManager */
clock_manager_user_config_t clock_config0ClockManager = {
    .scuConfigPtr = &clock_config0ScuConfig,
    .cmuConfigPtr = NULL,
    .ipcConfig =
        {
            .peripheralClocks = clock_config0PeripheralClockConfig,
            .count = 2,
        },
};

/*! @brief Array of pointers to User configuration structures */
clock_manager_user_config_t const *g_clockManConfigsArr[] = {
    &clock_config0ClockManager,
};

/*! @brief Array of pointers to User defined Callbacks configuration structures */
/* The tool do not support generate Callbacks configuration. It's always empty. */
clock_manager_callback_user_config_t *g_clockManCallbacksArr[] = {(void *)0};
