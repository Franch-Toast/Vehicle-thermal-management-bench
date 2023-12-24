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
#ifndef PINS_DRIVER_H
#define PINS_DRIVER_H

#include <stddef.h>
#include "device_registers.h"
#include "status.h"

/*!
 * @defgroup pins_driver PINS Driver
 * @ingroup pins
 * @details This section describes the programming interface of the PINS driver.
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief Type of a GPIO channel representation
 * Implements : pins_channel_type_t_Class
 */
typedef uint32_t pins_channel_type_t;

/*!
 * @brief Type of a port levels representation.
 * Implements : pins_level_type_t_Class
 */
typedef uint8_t pins_level_type_t;

/*!
 * @brief Configures the port data direction
 * Implements : pin_direction_t_Class
 */
typedef enum
{
    GPIO_INPUT_DIRECTION = 0x0U,  /*!< General purpose input direction.       */
    GPIO_OUTPUT_DIRECTION = 0x1U,  /*!< General purpose output direction.      */
    GPIO_UNSPECIFIED_DIRECTION = 0x2U   /*!< General purpose unspecified direction. */
} pin_direction_t;

#if FEATURE_PINS_HAS_PULL_SELECTION
/*!
 * @brief Internal resistor pull feature selection
 * Implements : port_pull_config_t_Class
 */
typedef enum
{
    PCTRL_INTERNAL_PULL_NOT_ENABLED = 0U,  /*!< internal pull-down or pull-up resistor is not enabled.           */
    PCTRL_INTERNAL_PULL_DOWN_ENABLED = 1U,  /*!< internal pull-down resistor is enabled. */
    PCTRL_INTERNAL_PULL_UP_ENABLED = 2U   /*!< internal pull-up resistor is enabled.     */
} port_pull_config_t;
#endif /* FEATURE_PINS_HAS_PULL_SELECTION */

#if FEATURE_PINS_HAS_OPEN_DRAIN
/*!
 * @brief Configures the Open Drain Enable field.
 * Implements : port_open_drain_t_Class
 */
typedef enum
{
    PCTRL_OPEN_DRAIN_DISABLED  = 0U, /*!< Output is CMOS       */
    PCTRL_OPEN_DRAIN_ENABLED   = 1U  /*!< Output is open drain */
} port_open_drain_t;
#endif /* FEATURE_PINS_HAS_OPEN_DRAIN */

#if FEATURE_PINS_HAS_FILTER_CLOCK_SEL
/*!
 * @brief Configures the Open Drain Enable field.
 * Implements : port_open_drain_t_Class
 */
typedef enum
{
    PIN_FILETER_USE_BUS_CLOCK = 0U, /*!< Filter clock is GPIO bus clock */
    PIN_FILTER_USE_FUNCTION_CLOCK = 1U  /*!< Filter clock is GPIO function clock */
} pin_filter_clock_sel_t;
#endif /* FEATURE_PINS_HAS_FILTER_CLOCK_SEL */

#if FEATURE_PINS_HAS_DRIVE_STRENGTH
/*!
 * @brief Configures the drive strength.
 * Implements : port_drive_strength_t_Class
 */
typedef enum
{
    PCTRL_LOW_DRIVE_STRENGTH = 0U,    /*!< low drive strength is configured.   */
    PCTRL_HIGH_DRIVE_STRENGTH = 1U     /*!< high drive strength is configured. */
} port_drive_strength_t;
#endif /* FEATURE_PINS_HAS_DRIVE_STRENGTH */

/*!
 * @brief Configures the Pin mux selection
 * Implements : port_mux_t_Class
 */
typedef enum
{
    PCTRL_PIN_DISABLED = 0U,  /*!< corresponding pin is disabled, but is used as an analog pin       */
    PCTRL_MUX_AS_GPIO = 1U,  /*!< corresponding pin is configured as GPIO                           */
    PCTRL_MUX_ALT2 = 2U,  /*!< chip-specific                                                     */
    PCTRL_MUX_ALT3 = 3U,  /*!< chip-specific                                                     */
    PCTRL_MUX_ALT4 = 4U,  /*!< chip-specific                                                     */
    PCTRL_MUX_ALT5 = 5U,  /*!< chip-specific                                                     */
    PCTRL_MUX_ALT6 = 6U,  /*!< chip-specific                                                     */
    PCTRL_MUX_ALT7 = 7U,  /*!< chip-specific                                                     */
#if FEATURE_PCTRL_HAS_ALT_15
    PCTRL_MUX_ALT8 = 8U,  /*!< chip-specific                                                     */
    PCTRL_MUX_ALT9 = 9U,  /*!< chip-specific                                                     */
    PCTRL_MUX_ALT10 = 10U,  /*!< chip-specific                                                     */
    PCTRL_MUX_ALT11 = 11U,  /*!< chip-specific                                                     */
    PCTRL_MUX_ALT12 = 12U,  /*!< chip-specific                                                     */
    PCTRL_MUX_ALT13 = 13U,  /*!< chip-specific                                                     */
    PCTRL_MUX_ALT14 = 14U,  /*!< chip-specific                                                     */
    PCTRL_MUX_ALT15 = 15U  /*!< chip-specific                                                     */
#endif
} port_mux_t;

/*!
 * @brief Configures the interrupt generation condition.
 * Implements : port_interrupt_config_t_Class
 */
typedef enum
{
    PCTRL_DMA_INT_DISABLED = 0x0U,  /*!< Interrupt/DMA request is disabled.                   */
    PCTRL_DMA_RISING_EDGE = 0x1U,  /*!< DMA request on rising edge.                          */
    PCTRL_DMA_FALLING_EDGE = 0x2U,  /*!< DMA request on falling edge.                         */
    PCTRL_DMA_EITHER_EDGE = 0x3U,  /*!< DMA request on either edge.                          */
#if FEATURE_PINS_HAS_FLAG_SET_ONLY
    PCTRL_FLAG_RISING_EDGE  = 0x5U,  /*!< Flag sets on rising edge, no interrupt is generated. */
    PCTRL_FLAG_FALLING_EDGE = 0x6U,  /*!< Flag sets on falling edge, no interrupt is generated.*/
    PCTRL_FLAG_EITHER_EDGE  = 0x7U,  /*!< Flag sets on either edge, no interrupt is generated. */
#endif /* FEATURE_PINS_HAS_FLAG_SET_ONLY */
    PCTRL_INT_LOGIC_ZERO = 0x8U,  /*!< Interrupt when logic 0.                              */
    PCTRL_INT_RISING_EDGE = 0x9U,  /*!< Interrupt on rising edge.                            */
    PCTRL_INT_FALLING_EDGE = 0xAU,  /*!< Interrupt on falling edge.                           */
    PCTRL_INT_EITHER_EDGE = 0xBU,  /*!< Interrupt on either edge.                            */
    PCTRL_INT_LOGIC_ONE = 0xCU,  /*!< Interrupt when logic 1.                              */
#if FEATURE_PINS_HAS_TRIGGER_OUT
    PCTRL_HIGH_TRIGGER_OUT = 0xDU,  /*!< Enable active high trigger output, flag is disabled. */
    PCTRL_LOW_TRIGGER_OUT = 0xEU   /*!< Enable active low trigger output, flag is disabled.  */
#endif /* FEATURE_PINS_HAS_TRIGGER_OUT */
} gpio_interrupt_config_t;

#if FEATURE_PINS_HAS_SLEW_RATE
/*!
 * @brief Configures the Slew Rate field.
 * Implements : port_slew_rate_t_Class
 */
typedef enum
{
    PCTRL_FAST_SLEW_RATE = 0U,   /*!< fast slew rate is configured.  */
    PCTRL_SLOW_SLEW_RATE = 1U    /*!< slow slew rate is configured.  */
} port_slew_rate_t;
#endif /* FEATURE_PINS_HAS_SLEW_RATE */

#if FEATURE_PINS_HAS_FILTER_CLOCK_SELECTION
/*!
 * @brief Clock source for the digital input filters
 * Implements : port_digital_filter_clock_t_Class
 */
typedef enum
{
    PCTRL_DIGITAL_FILTER_BUS_CLOCK  = 0U, /*!< Digital filters are clocked by the bus clock.  */
    PCTRL_DIGITAL_FILTER_LPO_CLOCK  = 1U  /*!< Digital filters are clocked by the LPO clock.  */
} port_digital_filter_clock_t;
#endif
/*!
 * @brief The digital filter configuration
 * Implements : port_digital_filter_config_t_Class
 */
typedef struct
{
#if FEATURE_PINS_HAS_FILTER_CLOCK_SELECTION
    port_digital_filter_clock_t clock;  /*!< The digital filter clock for port */
#endif
    uint8_t width;  /*!< The digital filter width value */
} gpio_digital_filter_config_t;


/*!
 * @brief Defines the converter configuration
 *
 * This structure is used to configure the pins
 * Implements : pin_settings_config_t_Class
 */
typedef struct
{
    PCTRL_Type *base;              /*!< Port base pointer.                        */
    uint32_t pinPortIdx;        /*!< Port pin number.                          */
#if FEATURE_PINS_HAS_PULL_SELECTION
    port_pull_config_t pullConfig;        /*!< Internal resistor pull feature selection. */
#endif
#if FEATURE_PINS_HAS_SLEW_RATE
    port_slew_rate_t rateSelect;        /*!< Slew rate selection.                      */
#endif
#if FEATURE_PINS_HAS_PASSIVE_FILTER
    bool passiveFilter;     /*!< Passive filter configuration.             */
#endif
#if FEATURE_PINS_HAS_OPEN_DRAIN
    port_open_drain_t           openDrain;         /*!< Configures open drain.                    */
#endif
#if FEATURE_PINS_HAS_DRIVE_STRENGTH
    port_drive_strength_t driveSelect;       /*!< @brief Configures the drive strength.     */
#endif
    port_mux_t mux;               /*!< @brief Pin (C55: Out) mux selection.      */
#if FEATURE_PCTRL_HAS_PIN_CONTROL_LOCK
    bool                        pinLock;           /*!< Lock pin control register or not.         */
#endif
    gpio_interrupt_config_t intConfig;         /*!< Interrupt generation condition.           */
    bool clearIntFlag;      /*!< Clears the interrupt status flag.         */
    bool digitalFilter;     /*!< Enables digital filter.                   */
#if (FEATURE_PINS_HAS_DIGITAL_FILTER) || (FEATURE_PCTRL_HAS_DIGITAL_FILTER)
    gpio_digital_filter_config_t filterConfig;     /*!< Digital filter configuration.             */
#endif /* FEATURE_PINS_HAS_DIGITAL_FILTER || FEATURE_PCTRL_HAS_DIGITAL_FILTER */
    GPIO_Type *gpioBase;          /*!< GPIO base pointer.                        */
    pin_direction_t direction;         /*!< Configures the port data direction.       */
    pins_level_type_t initValue;         /*!< Initial value                             */
} pin_settings_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @name PINS DRIVER API.
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif


/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function configures the pins with the options provided in the
 * provided structure.
 *
 * @param[in] pinCount The number of configured pins in structure
 * @param[in] config The configuration structure
 * @return The status of the operation
 */
status_t PINS_DRV_Init(uint32_t pinCount,
                       const pin_settings_config_t config[]);

#if FEATURE_PINS_HAS_PULL_SELECTION

/*!
 * @brief Configures the internal resistor.
 *
 * This function configures the internal resistor.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pin Port pin number
 * @param[in] pullConfig The pull configuration
 */
void PINS_DRV_SetPullSel(PCTRL_Type *const base,
                         uint32_t pin,
                         port_pull_config_t pullConfig);

#endif /* FEATURE_PINS_HAS_PULL_SELECTION */

/*!
 * @brief Configures the pin muxing.
 *
 * This function configures the pin muxing.
 *
 * @param[in] base Port base pointer (PORTA, PORTB, PORTC, etc.)
 * @param[in] pin Port pin number
 * @param[in] mux Pin muxing slot selection
 */
void PINS_DRV_SetMuxModeSel(PCTRL_Type *const base,
                            uint32_t pin,
                            port_mux_t mux);

/*!
 * @brief Configures the port pin interrupt/DMA request.
 *
 * This function configures the port pin interrupt/DMA request.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] pin GPIO pin number
 * @param[in] intConfig  Interrupt configuration
 */
void PINS_DRV_SetPinIntSel(GPIO_Type *const base,
                           uint32_t pin,
                           gpio_interrupt_config_t intConfig);

/*!
 * @brief Gets the current gpio pin interrupt/DMA request configuration.
 *
 * This function gets the current gpio pin interrupt/DMA request configuration.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] pin GPIO pin number
 * @return Interrupt configuration
 */
gpio_interrupt_config_t PINS_DRV_GetPinIntSel(const GPIO_Type *const base,
                                              uint32_t pin);

/*!
 * @brief Clears the individual pin-interrupt status flag.
 *
 * This function clears the individual pin-interrupt status flag.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] pin GPIO pin number
 */
void PINS_DRV_ClearPinIntFlagCmd(GPIO_Type *const base,
                                 uint32_t pin);

/*!
 * @brief Enables digital filter for digital pin muxing
 *
 * This function enables digital filter feature for digital pin muxing
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] pin GPIO pin number
 */
void PINS_DRV_EnableDigitalFilter(GPIO_Type *const base,
                                  uint32_t pin);

/*!
 * @brief Disables digital filter for digital pin muxing
 *
 * This function disables digital filter feature for digital pin muxing
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] pin GPIO pin number
 */
void PINS_DRV_DisableDigitalFilter(GPIO_Type *const base,
                                   uint32_t pin);

/*!
 * @brief Configures digital filter for gpio with given configuration
 *
 * This function configures digital filter for gpio with given configuration
 *
 * Note: Updating the filter configuration must be done only after all filters are disabled.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] config the digital filter configuration struct
 */
void PINS_DRV_ConfigDigitalFilter(GPIO_Type *const base,
                                  const gpio_digital_filter_config_t *const config,
                                  uint32_t pin);

/*!
 * @brief Reads the entire port interrupt status flag
 *
 * This function reads the entire gpio interrupt status flag.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @return All 32 pin interrupt status flags
 */
uint32_t PINS_DRV_GetPortIntFlag(const GPIO_Type *const base);

/*!
 * @brief Clears the entire gpio interrupt status flag.
 *
 * This function clears the entire port interrupt status flag.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 */
void PINS_DRV_ClearPortIntFlagCmd(GPIO_Type *const base);


/*!
 * @brief Get the pins directions configuration for a port
 *
 * This function returns the current pins directions for a port. Pins
 * corresponding to bits with value of '1' are configured as output and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @return GPIO directions. Each bit represents one pin (LSB is pin 0, MSB is
 * pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 */
pins_channel_type_t PINS_DRV_GetPinsDirection(const GPIO_Type *const base);

/*!
 * @brief Configure the direction for a certain pin from a port
 *
 * This function configures the direction for the given pin, with the
 * given value('1' for pin to be configured as output and '0' for pin to
 * be configured as input)
 *
 * Note: With some platforms when you want to set a pin as output only and disable
 * input completely, it is required to call PINS_DRV_SetPortInputDisable if platform
 * has this feature.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] pin The pin number for which to configure the direction
 * @param[in] direction The pin direction:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 */
void PINS_DRV_SetPinDirection(GPIO_Type *const base,
                              pins_channel_type_t pin,
                              pin_direction_t direction);

/*!
 * @brief Set the pins directions configuration for a port
 *
 * This function sets the direction configuration for all pins
 * in a port. Pins corresponding to bits with value of '1' will be configured as
 * output and pins corresponding to bits with value of '0' will be configured as
 * input.
 *
 * Note: With some platforms when you want to set a pin as output only and disable
 * input completely, it is required to call PINS_DRV_SetPortInputDisable if platform
 * has this feature.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] pins Pin mask where each bit represents one pin (LSB
 * is pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 */
void PINS_DRV_SetPinsDirection(GPIO_Type *const base,
                               pins_channel_type_t pins);

#if FEATURE_PINS_HAS_INPUT_DISABLE

/*!
 * @brief Set the pins input disable state for a port
 *
 * This function sets the pins input state for a port.
 * Pins corresponding to bits with value of '1' will not be configured
 * as input and pins corresponding to bits with value of '0' will be configured
 * as input.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] pins Pin mask where each bit represents one pin (LSB is pin 0, MSB is
 * pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is not set to input
 */
void PINS_DRV_SetPortInputDisable(GPIO_Type *const base,
                                  pins_channel_type_t pins);

/*!
 * @brief Get the pins input disable state for a port
 *
 * This function returns the current pins input state for a port. Pins
 * corresponding to bits with value of '1' are not configured as input and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @return GPIO input state. Each bit represents one pin (LSB is pin 0, MSB is
 * pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is not set to input
 */
pins_channel_type_t PINS_DRV_GetPortInputDisable(const GPIO_Type *const base);

#endif /* FEATURE_PINS_HAS_INPUT_DISABLE */


/*!
 * @brief Write a pin of a port with a given value
 *
 * This function writes the given pin from a port, with the given value
 * ('0' represents LOW, '1' represents HIGH).
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] pin Pin number to be written
 * @param[in] value Pin value to be written
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
void PINS_DRV_WritePin(GPIO_Type *const base,
                       pins_channel_type_t pin,
                       pins_level_type_t value);

/*!
 * @brief Write all pins of a port
 *
 * This function writes all pins configured as output with the values given in
 * the parameter pins. '0' represents LOW, '1' represents HIGH.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] pins Pin mask to be written
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
void PINS_DRV_WritePins(GPIO_Type *const base,
                        pins_channel_type_t pins);

/*!
 * @brief Get the current output from a port
 *
 * This function returns the current output that is written to a port. Only pins
 * that are configured as output will have meaningful values.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @return GPIO outputs. Each bit represents one pin (LSB is pin 0, MSB is pin
 * 31). For each bit:
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
pins_channel_type_t PINS_DRV_GetPinsOutput(const GPIO_Type *const base);

/*!
 * @brief Write pins with 'Set' value
 *
 * This function configures output pins listed in parameter pins (bits that are
 * '1') to have a value of 'set' (HIGH). Pins corresponding to '0' will be
 * unaffected.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] pins Pin mask of bits to be set. Each bit represents one pin (LSB is
 * pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is unaffected
 *        - 1: corresponding pin is set to HIGH
 */
void PINS_DRV_SetPins(GPIO_Type *const base,
                      pins_channel_type_t pins);

/*!
 * @brief Write pins to 'Clear' value
 *
 * This function configures output pins listed in parameter pins (bits that are
 * '1') to have a 'cleared' value (LOW). Pins corresponding to '0' will be
 * unaffected.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] pins Pin mask of bits to be cleared. Each bit represents one pin (LSB
 * is pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is unaffected
 *        - 1: corresponding pin is cleared(set to LOW)
 */
void PINS_DRV_ClearPins(GPIO_Type *const base,
                        pins_channel_type_t pins);

/*!
 * @brief Toggle pins value
 *
 * This function toggles output pins listed in parameter pins (bits that are
 * '1'). Pins corresponding to '0' will be unaffected.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @param[in] pins Pin mask of bits to be toggled.  Each bit represents one pin (LSB
 * is pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is unaffected
 *        - 1: corresponding pin is toggled
 */
void PINS_DRV_TogglePins(GPIO_Type *const base,
                         pins_channel_type_t pins);

/*!
 * @brief Read input pins
 *
 * This function returns the current input values from a port. Only pins
 * configured as input will have meaningful values.
 *
 * @param[in] base GPIO base pointer (GPIOA, GPIOB, GPIOC, etc.)
 * @return GPIO inputs. Each bit represents one pin (LSB is pin 0, MSB is pin
 * 31). For each bit:
 *        - 0: corresponding pin is read as LOW
 *        - 1: corresponding pin is read as HIGH
 */
pins_channel_type_t PINS_DRV_ReadPins(const GPIO_Type *const base);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* PINS_DRIVER_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
