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
 */
#ifndef PINS_GPIO_HW_ACCESS_H
#define PINS_GPIO_HW_ACCESS_H

#include "pins_driver.h"

/*!
 * pins_gpio_hw_access
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name GPIO
 * General GPIO functions.
 */
/*! @{*/

/*!
 * @brief Get the pins directions configuration for a port
 *
 * This function returns the current pins directions for a port. Pins
 * corresponding to bits with value of '1' are configured as output and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * @param base  GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @return GPIO directions. Each bit represents one pin (LSB is pin 0, MSB is
 * pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 */
static inline pins_channel_type_t PINS_GPIO_GetPinsDirection(const GPIO_Type * const base)
{
    return (pins_channel_type_t)base->POER;
}

/*!
 * @brief Configure the direction for a certain pin from a port
 *
 * This function configures the direction for the given pin, with the
 * given value('1' for pin to be configured as output and '0' for pin to
 * be configured as input)
 *
 * @param base  GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param pin the pin number for which to configure the direction
 * @param direction the pin direction:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 */
static inline void PINS_GPIO_SetPinDirection(GPIO_Type * const base,
                                             pins_channel_type_t pin,
                                             pins_level_type_t direction)
{
    pins_channel_type_t pinsDirections = (pins_channel_type_t)base->POER;
    pinsDirections &= (pins_channel_type_t)(~((pins_channel_type_t)1U << pin));
    pinsDirections |= (pins_channel_type_t)((pins_channel_type_t)direction << pin);
    base->POER = GPIO_POER_POE(pinsDirections);
    // base->PIER = GPIO_PIER_PIE(~pinsDirections);
}

/*!
 * @brief Set the pins directions configuration for a port
 *
 * This function sets the direction configuration for all pins
 * in a port. Pins corresponding to bits with value of '1' will be configured as
 * output and pins corresponding to bits with value of '0' will be configured as
 * input.
 *
 * @param base  GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param pins pin mask where each bit represents one pin (LSB
 * is pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 */
static inline void PINS_GPIO_SetPinsDirection(GPIO_Type * const base,
                                              pins_channel_type_t pins)
{
    base->POER = GPIO_POER_POE(pins);
    // base->PIER = GPIO_PIER_PIE(~pins);
}

#if FEATURE_PINS_HAS_INPUT_DISABLE
/*!
 * @brief Set the pins input disable state for a port
 *
 * This function sets the pins input state for a port.
 * Pins corresponding to bits with value of '1' will not be configured
 * as input and pins corresponding to bits with value of '0' will be configured
 * as input.
 *
 * @param base  GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param pins pin mask where each bit represents one pin (LSB is pin 0, MSB is
 * pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is not set to input
 */
static inline void PINS_GPIO_SetPortInputDisable(GPIO_Type * const base,
                                                 pins_channel_type_t pins)
{
    base->PIER = GPIO_PIER_PIE(~pins);
}

/*!
 * @brief Get the pins input disable state for a port
 *
 * This function returns the current pins input state for a port. Pins
 * corresponding to bits with value of '1' are not configured as input and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * @param base  GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @return GPIO input state. Each bit represents one pin (LSB is pin 0, MSB is
 * pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is not set to input
 */
static inline pins_channel_type_t PINS_GPIO_GetPortInputDisable(const GPIO_Type * const base)
{
    return ~(pins_channel_type_t)base->PIER;
}
#endif /* FEATURE_PINS_HAS_INPUT_DISABLE */


/*!
 * @brief Write a pin of a port with a given value
 *
 * This function writes the given pin from a port, with the given value
 * ('0' represents LOW, '1' represents HIGH).
 *
 * @param base  GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param pin pin number to be written
 * @param value pin value to be written
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
static inline void PINS_GPIO_WritePin(GPIO_Type * const base,
                                      pins_channel_type_t pin,
                                      pins_level_type_t value)
{
    pins_channel_type_t pinsValues = (pins_channel_type_t)base->PDOR;
    pinsValues &= (pins_channel_type_t)(~((pins_channel_type_t)1U << pin));
    pinsValues |= (pins_channel_type_t)((pins_channel_type_t)value << pin);
    base->PDOR = GPIO_PDOR_PDO(pinsValues);
}

/*!
 * @brief Write all pins of a port
 *
 * This function writes all pins configured as output with the values given in
 * the parameter pins. '0' represents LOW, '1' represents HIGH.
 *
 * @param base  GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param pins pin mask to be written
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
static inline void PINS_GPIO_WritePins(GPIO_Type * const base,
                                       pins_channel_type_t pins)
{
    base->PDOR = GPIO_PDOR_PDO(pins);
}

/*!
 * @brief Get the current output from a port
 *
 * This function returns the current output that is written to a port. Only pins
 * that are configured as output will have meaningful values.
 *
 * @param base  GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @return GPIO outputs. Each bit represents one pin (LSB is pin 0, MSB is pin
 * 31). For each bit:
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
static inline pins_channel_type_t PINS_GPIO_GetPinsOutput(const GPIO_Type * const base)
{
    pins_channel_type_t returnValue = 0U;

    returnValue = (pins_channel_type_t)(base->PDOR);

    return returnValue;
}

/*!
 * @brief Write pins with 'Set' value
 *
 * This function configures output pins listed in parameter pins (bits that are
 * '1') to have a value of 'set' (HIGH). Pins corresponding to '0' will be
 * unaffected.
 *
 * @param base  GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param pins pin mask of bits to be set.  Each bit represents one pin (LSB is
 * pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is unaffected
 *        - 1: corresponding pin is set to HIGH
 */
static inline void PINS_GPIO_SetPins(GPIO_Type * const base,
                                     pins_channel_type_t pins)
{
    base->PSOR = GPIO_PSOR_PSO(pins);
}

/*!
 * @brief Write pins to 'Clear' value
 *
 * This function configures output pins listed in parameter pins (bits that are
 * '1') to have a 'cleared' value (LOW). Pins corresponding to '0' will be
 * unaffected.
 *
 * @param base  GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param pins pin mask of bits to be cleared.  Each bit represents one pin (LSB
 * is pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is unaffected
 *        - 1: corresponding pin is cleared(set to LOW)
 */
static inline void PINS_GPIO_ClearPins(GPIO_Type * const base,
                                       pins_channel_type_t pins)
{
    base->PCOR = GPIO_PCOR_PCO(pins);
}

/*!
 * @brief Toggle pins value
 *
 * This function toggles output pins listed in parameter pins (bits that are
 * '1'). Pins corresponding to '0' will be unaffected.
 *
 * @param base  GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param pins pin mask of bits to be toggled.  Each bit represents one pin (LSB
 * is pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is unaffected
 *        - 1: corresponding pin is toggled
 */
static inline void PINS_GPIO_TogglePins(GPIO_Type * const base,
                                        pins_channel_type_t pins)
{
    base->PTOR = GPIO_PTOR_PTO(pins);
}

/*!
 * @brief Read input pins
 *
 * This function returns the current input values from a port. Only pins
 * configured as input will have meaningful values.
 *
 * @param base  GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @return GPIO inputs. Each bit represents one pin (LSB is pin 0, MSB is pin
 * 31). For each bit:
 *        - 0: corresponding pin is read as LOW
 *        - 1: corresponding pin is read as HIGH
 */
static inline pins_channel_type_t PINS_GPIO_ReadPins(const GPIO_Type * const base)
{
    pins_channel_type_t returnValue = 0U;

    returnValue = (pins_channel_type_t)(base->PDIR);
    return returnValue;
}
/*!
 * @brief Configures the gpio pin interrupt/DMA request.
 *
 * @param[in] base       gpio base pointer.
 * @param[in] pin        gpio pin number
 * @param[in] intConfig  interrupt configuration
 *        - GPIO_INT_DISABLED     : Interrupt/DMA request disabled.
 *        - GPIO_DMA_RISING_EDGE  : DMA request on rising edge.
 *        - GPIO_DMA_FALLING_EDGE : DMA request on falling edge.
 *        - GPIO_DMA_EITHER_EDGE  : DMA request on either edge.
 *        - GPIO_FLAG_RISING_EDGE : Flag sets on rising edge only.
 *        - GPIO_FLAG_FALLING_EDGE: Flag sets on falling edge only.
 *        - GPIO_FLAG_EITHER_EDGE : Flag sets on either edge only.
 *        - GPIO_INT_LOGIC_ZERO   : Interrupt when logic zero.
 *        - GPIO_INT_RISING_EDGE  : Interrupt on rising edge.
 *        - GPIO_INT_FALLING_EDGE : Interrupt on falling edge.
 *        - GPIO_INT_EITHER_EDGE  : Interrupt on either edge.
 *        - GPIO_INT_LOGIC_ONE    : Interrupt when logic one.
 *        - GPIO_HIGH_TRIGGER_OUT : Enable active high trigger output, flag is disabled.
 *        - GPIO_LOW_TRIGGER_OUT  : Enable active low trigger output, flag is disabled.
 */
static inline void PINS_SetPinIntSel(GPIO_Type * const base,
                                     uint32_t pin,
                                     gpio_interrupt_config_t intConfig)
{
    DEV_ASSERT(pin < PCTRL_PCR_COUNT);
    uint32_t regValue = base->PCR[pin];
    regValue &= ~(GPIO_PCR_IRQC_MASK);
    regValue |= GPIO_PCR_IRQC(intConfig);
    base->PCR[pin] = regValue;
}

/*!
 * @brief Gets the current gpio pin interrupt/DMA request configuration.
 *
 * @param[in] base  gpio base pointer
 * @param[in] pin   gpio pin number
 * @return  interrupt configuration
 *        - GPIO_INT_DISABLED     : Interrupt/DMA request disabled.
 *        - GPIO_DMA_RISING_EDGE  : DMA request on rising edge.
 *        - GPIO_DMA_FALLING_EDGE : DMA request on falling edge.
 *        - GPIO_DMA_EITHER_EDGE  : DMA request on either edge.
 *        - GPIO_FLAG_RISING_EDGE : Flag sets on rising edge only.
 *        - GPIO_FLAG_FALLING_EDGE: Flag sets on falling edge only.
 *        - GPIO_FLAG_EITHER_EDGE : Flag sets on either edge only.
 *        - GPIO_INT_LOGIC_ZERO   : Interrupt when logic zero.
 *        - GPIO_INT_RISING_EDGE  : Interrupt on rising edge.
 *        - GPIO_INT_FALLING_EDGE : Interrupt on falling edge.
 *        - GPIO_INT_EITHER_EDGE  : Interrupt on either edge.
 *        - GPIO_INT_LOGIC_ONE    : Interrupt when logic one.
 *        - GPIO_HIGH_TRIGGER_OUT : Enable active high trigger output, flag is disabled.
 *        - GPIO_LOW_TRIGGER_OUT  : Enable active low trigger output, flag is disabled.
 */
static inline gpio_interrupt_config_t PINS_GetPinIntSel(const GPIO_Type * const base,
                                                        uint32_t pin)
{
    DEV_ASSERT(pin < PCTRL_PCR_COUNT);
    uint32_t regValue = base->PCR[pin];
    regValue = (regValue & GPIO_PCR_IRQC_MASK) >> GPIO_PCR_IRQC_SHIFT;

    return (gpio_interrupt_config_t)regValue;
}

/*!
 * @brief Clears the individual pin-interrupt status flag.
 *
 * @param[in] base  gpio base pointer
 * @param[in] pin   gpio pin number
 */
static inline void PINS_ClearPinIntFlagCmd(GPIO_Type * const base,
                                           uint32_t pin)
{
    DEV_ASSERT(pin < PCTRL_PCR_COUNT);
    base->PIFR =  1 << pin;
}

#if FEATURE_PINS_HAS_DIGITAL_FILTER
/*!
 * @brief Enables digital filter for digital pin muxing
 *
 * @param[in] base  gpio base pointer
 * @param[in] pin   gpio pin number
 */
static inline void PINS_EnableDigitalFilter(GPIO_Type * const base,
                                            uint32_t pin)
{
    DEV_ASSERT(pin < PCTRL_PCR_COUNT);
    base->PCR[pin] |= GPIO_PCR_DFE_MASK;
}

/*!
 * @brief Disables digital filter for digital pin muxing
 *
 * @param[in] base  gpio base pointer
 * @param[in] pin   gpio pin number
 */
static inline void PINS_DisableDigitalFilter(GPIO_Type * const base,
                                             uint32_t pin)
{
    DEV_ASSERT(pin < PCTRL_PCR_COUNT);
    base->PCR[pin] &= ~GPIO_PCR_DFE_MASK;
}

/*!
 * @brief Configures digital filter clock for gpio with given configuration
 *
 * @param[in] base   gpio base pointer
 * @param[in] config configuration struct
 */
static inline void PINS_ConfigDigitalFilter(GPIO_Type * const base,
                                            const gpio_digital_filter_config_t * const config, uint32_t pin)
{
#if FEATURE_PINS_HAS_FILTER_CLOCK_SELECTION
    base->PCR[pin] &= ~GPIO_PCR_DFCS_MASK;
    base->PCR[pin] |= GPIO_PCR_DFCS(config->clock);
#endif
    base->PCR [pin] &= ~GPIO_PCR_DFW_MASK;
    base->PCR [pin] |= GPIO_PCR_DFW(config->width);
}
#endif /* FEATURE_PINS_HAS_DIGITAL_FILTER */

#if FEATURE_PCTRL_HAS_DIGITAL_FILTER
/*!
 * @brief Enables digital filter for digital pin muxing
 *
 * @param[in] base  gpio base pointer
 * @param[in] pin   gpio pin number
 */
static inline void PINS_EnableDigitalFilter(PCTRL_Type * const base,
                                            uint32_t pin)
{
    DEV_ASSERT(pin < PCTRL_PCR_COUNT);
    base->PCR[pin] |= PCTRL_PCR_DFE_MASK;
}

/*!
 * @brief Disables digital filter for digital pin muxing
 *
 * @param[in] base  gpio base pointer
 * @param[in] pin   gpio pin number
 */
static inline void PINS_DisableDigitalFilter(PCTRL_Type * const base,
                                             uint32_t pin)
{
    DEV_ASSERT(pin < PCTRL_PCR_COUNT);
    base->PCR[pin] &= ~PCTRL_PCR_DFE_MASK;
}

/*!
 * @brief Configures digital filter clock for gpio with given configuration
 *
 * @param[in] base   gpio base pointer
 * @param[in] config configuration struct
 */
static inline void PINS_ConfigDigitalFilter(PCTRL_Type * const base,
                                            const gpio_digital_filter_config_t * const config, uint32_t pin)
{
    base->PCR [pin] &= ~PCTRL_PCR_DFW_MASK;
    base->PCR [pin] |= PCTRL_PCR_DFW(config->width);
}
#endif /* FEATURE_PCTRL_HAS_DIGITAL_FILTER */

/*!
 * @brief Reads the entire gpio interrupt status flag.
 *
 * @param[in] base  gpio base pointer
 * @return all 32 pin interrupt status flags. For specific bit:
 *         - 0: interrupt is not detected.
 *         - 1: interrupt is detected.
 */
static inline uint32_t PINS_GetPortIntFlag(const GPIO_Type * const base)
{
    uint32_t regValue = base->PIFR;

    return regValue;
}

/*!
 * @brief Clears the entire gpio interrupt status flag.
 *
 * @param[in] base  gpio base pointer
 */
static inline void PINS_ClearPortIntFlagCmd(GPIO_Type * const base)
{
    base->PIFR = GPIO_PIFR_PIF_MASK;
}



/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* PINS_GPIO_HW_ACCESS_H*/
/*******************************************************************************
 * EOF
 ******************************************************************************/
