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
#if !defined(INTERRUPT_MANAGER_H)
#define INTERRUPT_MANAGER_H

#include "device_registers.h"



/*! @file interrupt_manager.h */

/*! @addtogroup interrupt_manager*/
/*! @{*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* SDK needs to disable global IRQ before run some critical operation which should
 * not be interrupted.
 */
#define SDK_ENTER_CRITICAL() INT_SYS_DisableIRQGlobal()
/* After critical operation done, global interrupt should be restored.
 */
#define SDK_EXIT_CRITICAL() INT_SYS_EnableIRQGlobal()

/*! @brief Interrupt handler type */
typedef void (*isr_t)(void);

/*******************************************************************************
 * Default interrupt handler - implemented in startup.s
 ******************************************************************************/
/*! @brief Default ISR. */
void DefaultISR(void);

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name Interrupt manager APIs*/
/*@{*/

/*!
 * @brief Installs an interrupt handler routine for a given IRQ number. 
 *
 * This function lets the application register/replace the interrupt
 * handler for a specified IRQ number. See a chip-specific reference
 * manual for details and the  startup_<SoC>.s file for each chip
 * family to find out the default interrupt handler for each device.
 *
 * @note This method is applicable only if interrupt vector is copied in RAM.
 *
 * @param irqNumber   IRQ number
 * @param newHandler  New interrupt handler routine address pointer
 * @param oldHandler  Pointer to a location to store current interrupt handler
 */
void INT_SYS_InstallHandler(IRQn_Type irqNumber,
                            isr_t newHandler,
                            isr_t *oldHandler);

/*!
 * @brief Enables an interrupt for a given IRQ number. 
 *
 * This function  enables the individual interrupt for a specified IRQ number.
 *
 * @param irqNumber IRQ number
 */
void INT_SYS_EnableIRQ(IRQn_Type irqNumber);

/*!
 * @brief Disables an interrupt for a given IRQ number. 
 *
 * This function disables the individual interrupt for a specified IRQ number.
 *
 * @param irqNumber IRQ number
 */
void INT_SYS_DisableIRQ(IRQn_Type irqNumber);

/*!
 * @brief Enables system interrupt.
 *
 * This function enables the global interrupt by calling the core API.
 *
 */
void INT_SYS_EnableIRQGlobal(void);

/*!
 * @brief Disable system interrupt. 
 *
 * This function disables the global interrupt by calling the core API.
 *
 */
void INT_SYS_DisableIRQGlobal(void);

/*! @brief  Set Interrupt Priority
 *
 *   The function sets the priority of an interrupt.
 *
 *   @param  irqNumber  Interrupt number.
 *   @param  priority  Priority to set.
 */
void INT_SYS_SetPriority(IRQn_Type irqNumber, uint8_t priority);

/*! @brief  Get Interrupt Priority
 *
 *   The function gets the priority of an interrupt.
 *
 *   @param  irqNumber  Interrupt number.
 *   @return priority   Priority of the interrupt.
 */
uint8_t INT_SYS_GetPriority(IRQn_Type irqNumber);

#if FEATURE_INTERRUPT_HAS_PENDING_STATE

/*!
 * @brief Clear Pending Interrupt
 *
 * The function clears the pending bit of a peripheral interrupt
 * or a directed interrupt to this CPU (if available).
 *
 * @param irqNumber IRQ number
 */
void INT_SYS_ClearPending(IRQn_Type irqNumber);

/*!
 * @brief Set Pending Interrupt
 *
 * The function configures the pending bit of a peripheral interrupt.
 *
 * @param irqNumber IRQ number
 */
void INT_SYS_SetPending(IRQn_Type irqNumber);

/*!
 * @brief Get Pending Interrupt
 *
 * The function gets the pending bit of a peripheral interrupt
 * or a directed interrupt to this CPU (if available).
 *
 * @param irqNumber IRQ number
 * @return pending  Pending status 0/1
 */
uint32_t INT_SYS_GetPending(IRQn_Type irqNumber);

#endif /* FEATURE_INTERRUPT_HAS_PENDING_STATE */

#if FEATURE_INTERRUPT_HAS_ACTIVE_STATE
/*!
 * @brief Get Active Interrupt
 *
 * The function gets the active state of a peripheral interrupt.
 *
 * @param irqNumber IRQ number
 * @return active   Active status 0/1
 */
uint32_t INT_SYS_GetActive(IRQn_Type irqNumber);

#endif /* FEATURE_INTERRUPT_HAS_ACTIVE_STATE */

#if FEATURE_INTERRUPT_HAS_SOFTWARE_IRQ

/*!
 * @brief Set software interrupt request
 *
 * The function sets a software settable interrupt request.
 *
 * @param irqNumber IRQ number
 */
void INT_SYS_SetSoftwareIRQRequest(IRQn_Type irqNumber);

/*!
 * @brief Clear software interrupt request
 *
 * The function clears a software settable interrupt request.
 *
 * @param irqNumber IRQ number
 */
void INT_SYS_ClearSoftwareIRQRequest(IRQn_Type irqNumber);

#endif /* FEATURE_INTERRUPT_HAS_SOFTWARE_IRQ */


#if FEATURE_INTERRUPT_MULTICORE_SUPPORT

/*!
 * @brief Enables an interrupt for a given IRQ number, on the given cores.
 *
 * This function enables the individual interrupt for a specified IRQ number,
 * and on the specified cores.
 *
 * @param irqNumber IRQ number
 * @param coresIds array with the cores ids for which to enable the interrupt
 * @param coresCnt the number of cores in the coresIds array
 */
void INT_SYS_EnableIRQ_MC(IRQn_Type irqNumber, const uint8_t *coresIds, uint8_t coresCnt);

/*!
 * @brief Gets the cores on which an interrupt for the specified IRQ
 * number is enabled.
 *
 * This function will populate an array with all the supported cores,
 * for which the value will be INTERRUPT_CORE_ENABLED if interrupt is enabled
 * on that core, and INTERRUPT_CORE_DISABLED if interrupt is not enabled on
 * that core. The array has to be previously allocated using the
 * NUMBER_OF_CORES define value.
 *
 * @param irqNumber IRQ number
 * @param cores array with array index as core number; it has to be previously
 * allocated using the NUMBER_OF_CORES define value. it will be populated with the
 * following value:
 *  - INTERRUPT_CORE_DISABLED interrupt disabled for that core
 * 	- INTERRUPT_CORE_ENABLED enabled for that core
 */
void INT_SYS_GetCoresForIRQ(IRQn_Type irqNumber, interrupt_core_enable_t *cores);

/*!
 * @brief Disables an interrupt for a given IRQ number, on the given cores.
 *
 * This function disables the individual interrupt for a specified IRQ number,
 * and on the specified cores.
 *
 * @param irqNumber IRQ number
 * @param coresIds array with the cores ids for which to enable the interrupt
 * @param coresCnt the number of cores in the coresIds array
 */
void INT_SYS_DisableIRQ_MC(IRQn_Type irqNumber, const uint8_t *coresIds, uint8_t coresCnt);

/*!
 * @brief Disables an interrupt for a given IRQ number, on all cores.
 *
 * This function disables the individual interrupt for a specified IRQ number,
 * on all cores. It also clears priority for that IRQ number
 *
 * @param irqNumber IRQ number
 */
void INT_SYS_DisableIRQ_MC_All(IRQn_Type irqNumber);

#endif /* FEATURE_INTERRUPT_MULTICORE_SUPPORT */


/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* INTERRUPT_MANAGER_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
