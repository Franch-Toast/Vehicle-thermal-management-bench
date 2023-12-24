/*
 * Copyright 2020-2022 Yuntu Microelectronics co.,ltd
 * All rights reserved.
 *
 * YUNTU Confidential. This software is owned or controlled by YUNTU and may
 * only be used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 *//*!
 * @file pins_driver.c
 *
 */

#include "device_registers.h"
#include "pins_gpio_hw_access.h"
#include "pins_port_hw_access.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_Init
 * Description   : This function configures the pins with the options provided
 * in the given structure.
 *
 * Implements    : PINS_DRV_Init_Activity
 *END**************************************************************************/
status_t PINS_DRV_Init(uint32_t pinCount,
                       const pin_settings_config_t config[])
{
    uint32_t i;
    for (i = 0U; i < pinCount; i++)
    {
        PINS_Init(&config[i]);
    }

    return STATUS_SUCCESS;
}

#if FEATURE_PINS_HAS_PULL_SELECTION
/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetPullSel
 * Description   : This function configures the internal resistor.
 *
 * Implements    : PINS_DRV_SetPullSel_Activity
 *END**************************************************************************/
void PINS_DRV_SetPullSel(PCTRL_Type * const base,
                         uint32_t pin,
                         port_pull_config_t pullConfig)
{
    PINS_SetPullSel(base, pin, pullConfig);
}

#endif /* FEATURE_PINS_HAS_PULL_SELECTION */

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetMuxModeSel
 * Description   : This function configures the pin muxing.
 *
 * Implements    : PINS_DRV_SetMuxModeSel_Activity
 *END**************************************************************************/
void PINS_DRV_SetMuxModeSel(PCTRL_Type * const base,
                            uint32_t pin,
                            port_mux_t mux)
{
    PINS_SetMuxModeSel(base, pin, mux);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetPinIntSel
 * Description   : This function configures the gpio pin interrupt/DMA request.
 *
 * Implements    : PINS_DRV_SetPinIntSel_Activity
 *END**************************************************************************/
void PINS_DRV_SetPinIntSel(GPIO_Type * const base,
                           uint32_t pin,
                           gpio_interrupt_config_t intConfig)
{
    PINS_SetPinIntSel(base, pin, intConfig);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetPinIntSel
 * Description   : This function gets the current gpio pin interrupt/DMA request configuration.
 *
 * Implements    : PINS_DRV_GetPinIntSel_Activity
 *END**************************************************************************/
gpio_interrupt_config_t PINS_DRV_GetPinIntSel(const GPIO_Type * const base,
                                              uint32_t pin)
{
    return PINS_GetPinIntSel(base, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ClearPinIntFlagCmd
 * Description   : This function clears the individual pin-interrupt status flag.
 *
 * Implements    : PINS_DRV_ClearPinIntFlagCmd_Activity
 *END**************************************************************************/
void PINS_DRV_ClearPinIntFlagCmd(GPIO_Type * const base,
                                 uint32_t pin)
{
    PINS_ClearPinIntFlagCmd(base, pin);
}

#if defined(FEATURE_PINS_HAS_DIGITAL_FILTER) && (FEATURE_PINS_HAS_DIGITAL_FILTER)
/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_EnableDigitalFilter
 * Description   : This function enables digital filter feature for digital pin muxing.
 *
 * Implements    : PINS_DRV_EnableDigitalFilter_Activity
 *END**************************************************************************/
void PINS_DRV_EnableDigitalFilter(GPIO_Type * const base,
                                  uint32_t pin)
{
    PINS_EnableDigitalFilter(base, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_DisableDigitalFilter
 * Description   : This function disables digital filter feature for digital
 * pin muxing.
 *
 * Implements    : PINS_DRV_DisableDigitalFilter_Activity
 *END**************************************************************************/
void PINS_DRV_DisableDigitalFilter(GPIO_Type * const base,
                                   uint32_t pin)
{
    PINS_DisableDigitalFilter(base, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ConfigDigitalFilter
 * Description   : This function configures digital filter for port with
 * given configuration.
 *
 * Implements    : PINS_DRV_ConfigDigitalFilter_Activity
 *END**************************************************************************/
void PINS_DRV_ConfigDigitalFilter(GPIO_Type * const base,
                                  const gpio_digital_filter_config_t * const config, uint32_t pin)
{
    PINS_ConfigDigitalFilter(base, config, pin);
}
#endif /* FEATURE_PINS_HAS_DIGITAL_FILTER */

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetPortIntFlag
 * Description   : This function reads the entire gpio interrupt status flag.
 *
 * Implements    : PINS_DRV_GetPortIntFlag_Activity
 *END**************************************************************************/
uint32_t PINS_DRV_GetPortIntFlag(const GPIO_Type * const base)
{
    return PINS_GetPortIntFlag(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ClearPortIntFlagCmd
 * Description   : This function clears the entire port interrupt status flag.
 *
 * Implements    : PINS_DRV_ClearPortIntFlagCmd_Activity
 *END**************************************************************************/
void PINS_DRV_ClearPortIntFlagCmd(GPIO_Type * const base)
{
    PINS_ClearPortIntFlagCmd(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetPinsDirection
 * Description   : This function returns the current pins directions for a port. Pins
 * corresponding to bits with value of '1' are configured as output and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * Implements    : PINS_DRV_GetPinsDirection_Activity
 *END**************************************************************************/
pins_channel_type_t PINS_DRV_GetPinsDirection(const GPIO_Type * const base)
{
    return PINS_GPIO_GetPinsDirection(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetPinDirection
 * Description   : This function configures the direction for the given pin, with the
 * given value('1' for pin to be configured as output and '0' for pin to
 * be configured as input).
 *
 * Implements    : PINS_DRV_SetPinDirection_Activity
 *END**************************************************************************/
void PINS_DRV_SetPinDirection(GPIO_Type * const base,
                              pins_channel_type_t pin,
                              pin_direction_t direction)
{
    PINS_GPIO_SetPinDirection(base, pin, direction);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetPinsDirection
 * Description   : This function sets the direction configuration for all pins
 * in a port. Pins corresponding to bits with value of '1' will be configured as
 * output and pins corresponding to bits with value of '0' will be configured as
 * input.
 *
 * Implements    : PINS_DRV_SetPinsDirection_Activity
 *END**************************************************************************/
void PINS_DRV_SetPinsDirection(GPIO_Type * const base,
                               pins_channel_type_t pins)
{
    PINS_GPIO_SetPinsDirection(base, pins);
}

#if FEATURE_PINS_HAS_INPUT_DISABLE
/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetPortInputDisable
 * Description   : This function sets the pins input state for a port.
 * Pins corresponding to bits with value of '1' will not be configured
 * as input and pins corresponding to bits with value of '0' will be configured
 * as input.
 *
 * Implements    : PINS_DRV_SetPortInputDisable_Activity
 *END**************************************************************************/
void PINS_DRV_SetPortInputDisable(GPIO_Type * const base,
                                  pins_channel_type_t pins)
{
    PINS_GPIO_SetPortInputDisable(base, pins);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetPortInputDisable
 * Description   : This function returns the current pins input state for a port. Pins
 * corresponding to bits with value of '1' are not configured as input and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * Implements    : PINS_DRV_GetPortInputDisable_Activity
 *END**************************************************************************/
pins_channel_type_t PINS_DRV_GetPortInputDisable(const GPIO_Type * const base)
{
    return PINS_GPIO_GetPortInputDisable(base);
}
#endif /* FEATURE_PINS_HAS_INPUT_DISABLE */


/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_WritePin
 * Description   : This function writes the given pin from a port, with the given value
 * ('0' represents LOW, '1' represents HIGH).
 *
 * Implements    : PINS_DRV_WritePin_Activity
 *END**************************************************************************/
void PINS_DRV_WritePin(GPIO_Type * const base,
                       pins_channel_type_t pin,
                       pins_level_type_t value)
{
    PINS_GPIO_WritePin(base, pin, value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_WritePins
 * Description   : This function writes all pins configured as output with the values given in
 * the parameter pins. '0' represents LOW, '1' represents HIGH.
 *
 * Implements    : PINS_DRV_WritePins_Activity
 *END**************************************************************************/
void PINS_DRV_WritePins(GPIO_Type * const base,
                        pins_channel_type_t pins)
{
    PINS_GPIO_WritePins(base, pins);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_GetPinsOutput
 * Description   : This function returns the current output that is written to a port. Only pins
 * that are configured as output will have meaningful values.
 *
 * Implements    : PINS_DRV_GetPinsOutput_Activity
 *END**************************************************************************/
pins_channel_type_t PINS_DRV_GetPinsOutput(const GPIO_Type * const base)
{
    return PINS_GPIO_GetPinsOutput(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_SetPins
 * Description   : This function configures output pins listed in parameter pins (bits that are
 * '1') to have a value of 'set' (HIGH). Pins corresponding to '0' will be
 * unaffected.
 *
 * Implements    : PINS_DRV_SetPins_Activity
 *END**************************************************************************/
void PINS_DRV_SetPins(GPIO_Type * const base,
                      pins_channel_type_t pins)
{
    PINS_GPIO_SetPins(base, pins);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ClearPins
 * Description   : This function configures output pins listed in parameter pins (bits that are
 * '1') to have a 'cleared' value (LOW). Pins corresponding to '0' will be
 * unaffected.
 *
 * Implements    : PINS_DRV_ClearPins_Activity
 *END**************************************************************************/
void PINS_DRV_ClearPins(GPIO_Type * const base,
                        pins_channel_type_t pins)
{
    PINS_GPIO_ClearPins(base, pins);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_TogglePins
 * Description   : This function toggles output pins listed in parameter pins (bits that are
 * '1'). Pins corresponding to '0' will be unaffected.
 *
 * Implements    : PINS_DRV_TogglePins_Activity
 *END**************************************************************************/
void PINS_DRV_TogglePins(GPIO_Type * const base,
                         pins_channel_type_t pins)
{
    PINS_GPIO_TogglePins(base, pins);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_DRV_ReadPins
 * Description   : This function returns the current input values from a port. Only pins
 * configured as input will have meaningful values.
 *
 * Implements    : PINS_DRV_ReadPins_Activity
 *END**************************************************************************/
pins_channel_type_t PINS_DRV_ReadPins(const GPIO_Type * const base)
{
    return PINS_GPIO_ReadPins(base);
}

/******************************************************************************
 * EOF
 *****************************************************************************/
