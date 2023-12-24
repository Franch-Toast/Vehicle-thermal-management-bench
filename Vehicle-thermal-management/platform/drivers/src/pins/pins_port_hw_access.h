/*
 * Copyright 2020-2022 Yuntu Microelectronics co.,ltd
 * All rights reserved.
 *
 * YUNTU Confidential. This software is owned or controlled by YUNTU and may only
 * be used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 */

#ifndef PINS_PCTRL_HW_ACCESS_H
#define PINS_PCTRL_HW_ACCESS_H

#include "pins_driver.h"


/*!
 * @defgroup port_hal Port Control and Interrupts (PORT)
 * @ingroup pins_driver
 * @brief This module covers the functionality of the PORT peripheral.
 * <p>
 *  PORT HAL provides the API for reading and writing register bit-fields belonging to the PORT module.
 * </p>
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Configuration
 * @{
 */

/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function configures the pins with the options provided in the
 * given structure.
 *
 * @param[in] config the configuration structure
 */
void PINS_Init(const pin_settings_config_t * config);

#if FEATURE_PINS_HAS_PULL_SELECTION
/*!
 * @brief Configures the internal resistor.
 *
 * Pull configuration is valid in all digital pin muxing modes.
 *
 * @param[in] base        port base pointer.
 * @param[in] pin         port pin number
 * @param[in] pullConfig  internal resistor pull feature selection
 *        - PCTRL_PULL_NOT_ENABLED: internal pull-down or pull-up resistor is not enabled.
 *        - PCTRL_PULL_DOWN_ENABLED: internal pull-down resistor is enabled.
 *        - PCTRL_PULL_UP_ENABLED: internal pull-up resistor is enabled.
 */
static inline void PINS_SetPullSel(PCTRL_Type * const base,
                                   uint32_t pin,
                                   port_pull_config_t pullConfig)
{
    DEV_ASSERT(pin < PCTRL_PCR_COUNT);
    switch (pullConfig)
    {
        case PCTRL_INTERNAL_PULL_NOT_ENABLED:
            {
                base->PCR[pin] &= ~(PCTRL_PCR_PE_MASK);
            }
            break;
        case PCTRL_INTERNAL_PULL_DOWN_ENABLED:
            {
                uint32_t regValue = base->PCR[pin];
                regValue &= ~(PCTRL_PCR_PS_MASK);
                regValue |= PCTRL_PCR_PE(1U);
                base->PCR[pin] = regValue;
            }
            break;
        case PCTRL_INTERNAL_PULL_UP_ENABLED:
            {
                uint32_t regValue = base->PCR[pin];
                regValue |= PCTRL_PCR_PE(1U);
                regValue |= PCTRL_PCR_PS(1U);
                base->PCR[pin] = regValue;
            }
            break;
        default:
            /* invalid command */
            DEV_ASSERT(false);
            break;
    }
}

#endif /* if FEATURE_PINS_HAS_PULL_SELECTION */

/*!
 * @brief Configures the pin muxing.
 *
 * @param[in] base  port base pointer
 * @param[in] pin  port pin number
 * @param[in] mux  pin muxing slot selection
 *        - PCTRL_PIN_DISABLED: Pin disabled.
 *        - PCTRL_MUX_AS_GPIO : Set as GPIO.
 *        - PCTRL_MUX_ADC_INTERLEAVE : For ADC interleaved
 *        - others           : chip-specific.
 */
void PINS_SetMuxModeSel(PCTRL_Type * const base,
                        uint32_t pin,
                        port_mux_t mux);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* PINS_PCTRL_HW_ACCESS_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
