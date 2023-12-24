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

/*!
 * @file ipc_hw_access.h
 */

#ifndef IPC_HW_ACCESS_H
#define IPC_HW_ACCESS_H

#include "device_registers.h"
#include <stdbool.h>
#include <stddef.h>

/*!
 * @ingroup ipc_hw_access
 * @defgroup ipc_hw_access
 * @{
 */


/*! @brief Clock name mappings
 *         Constant array storing the mappings between clock names and peripheral clock control indexes.
 *         If there is no peripheral clock control index for a clock name, then the corresponding value is
 *         IPC_INVALID_INDEX.
 */
extern const uint16_t clockNameMappings[CLOCK_NAME_COUNT];

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/


/*!
* @brief Sets SOSC control register
*
* @param[in] base        ipc base pointer
* @param[in] clockName   is the name of the peripheral clock
* @param[in] clockGate   control register can be written or not
* @param[in] clockSource is the source of the peripheral clock
* @param[in] divider     peripheral clock divider
*/
static inline void IPC_SetPeripheralClockControl(IPC_Type* base, clock_names_t clkName, bool clockGate, uint32_t clkSrc, uint32_t div)
{
   /* Configure the peripheral clock source, the fractional clock divider and the clock gate */
   uint32_t value =  IPC_CTRL_SRCSEL(clkSrc)              |
                     IPC_CTRL_DIV(div)                  |
                     IPC_CTRL_CLKEN(clockGate ? 1U : 0U);

   base->CTRL[clockNameMappings[clkName]] = value;
}

/*!
* @brief Enables/disables the clock for a given peripheral.
* For example, to enable the ADC0 clock, use like this:
* @code
*  IPC_SetClockMode(IPC, IPC_ADC0_CLOCK, true);
* @endcode
*
* @param[in] base        ipc base pointer
* @param[in] clockName   is the name of the peripheral clock
* must be one of the following values (see the clock_names_t type from clock_names.h)
*    IPC_DMA0_CLOCK
*    IPC_MPU0_CLOCK
*    ...
*    IPC_UART3_CLOCK
* @param[in] isClockEnabled  is the value of the command that enables/disables the clock
*/
static inline void IPC_SetClockMode(IPC_Type* const base,
                                       const clock_names_t clockName,
                                       const bool isClockEnabled)
{
   if (isClockEnabled)
   {
       base->CTRL[clockNameMappings[clockName]] |= IPC_CTRL_CLKEN(1UL);
   }
   else
   {
       base->CTRL[clockNameMappings[clockName]] &= (uint32_t)(~(IPC_CTRL_CLKEN_MASK));
   }
}



/*!
* @brief Gets the clock gate control mode.
*
* @param[in] base        ipc base pointer
* @param[in] clockName   is the name of the peripheral clock
* must be one of the following values (see the clock_names_t type from clock_names.h)
*    IPC_DMA0_CLOCK
*    IPC_MPU0_CLOCK
*    ...
*    IPC_UART3_CLOCK
* @return  the clock gate control mode
*        - false : Clock is disabled
*        - true : Clock is enabled
*/
static inline bool IPC_GetClockMode(const IPC_Type* const base,
                                       const clock_names_t clockName)
{
   uint32_t regValue = (uint32_t)base->CTRL[clockNameMappings[clockName]];
   regValue = (regValue & IPC_CTRL_CLKEN_MASK) >> IPC_CTRL_CLKEN_SHIFT;
   return (regValue == 0U) ? false : true;
}

/*!
* @brief Gets the selection of a clock source for a specific peripheral
*
* @param[in] base        ipc base pointer
* @param[in] clockName   is the name of the peripheral clock
* must be one of the following values (see the clock_names_t type from clock_names.h)
*    IPC_DMA0_CLOCK
*    IPC_MPU0_CLOCK
*    ...
*    IPC_UART3_CLOCK
* @return  the clock source
*/
static inline uint32_t IPC_GetClockSourceSel(const IPC_Type* const base,
                                                                 const clock_names_t clockName)
{
   return ((base->CTRL[clockNameMappings[clockName]] & IPC_CTRL_SRCSEL_MASK) >> IPC_CTRL_SRCSEL_SHIFT);
}

/*!
* @brief Gets the selection of the divider value for a specific peripheral
*
* @param[in] base        ipc base pointer
* @param[in] clockName   is the name of the peripheral clock
* must be one of the following values (see the clock_names_t type from clock_names.h)
*    IPC_DMA0_CLOCK
*    IPC_MPU0_CLOCK
*    ...
*    IPC_UART3_CLOCK
* @return  the divider value
*/
static inline uint32_t IPC_GetDividerSel(const IPC_Type* const base,
                                             const clock_names_t clockName)
{
   return ((base->CTRL[clockNameMappings[clockName]] & IPC_CTRL_DIV_MASK) >> IPC_CTRL_DIV_SHIFT);
}





#if defined(__cplusplus)
}
#endif /* __cplusplus*/


/*! @}*/

#endif /* IPC_HW_ACCESS_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
