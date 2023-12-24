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

#if !defined(CLOCK_H)
#define CLOCK_H

#include "device_registers.h"
#include "status.h"

/*
 * Include the cpu specific clock API header files.
 */

#if (defined(CPU_YTM32B1LD0))
/* YTM32B1LD0 Clock System Level API header file */
#include "../src/clock/YTM32B1LD0/clock_YTM32B1LD0.h"
#elif (defined(CPU_YTM32B1LE0))
/* YTM32B1LE0 Clock System Level API header file */
#include "../src/clock/YTM32B1LE0/clock_YTM32B1LE0.h"
#elif (defined(CPU_YTM32B1MD0))
/* YTM32B1MD0 Clock System Level API header file */
#include "../src/clock/YTM32B1MD0/clock_YTM32B1MD0.h"
#elif (defined(YTM32B1M_SERIES))
/* YTM32B1Mx Clock System Level API header file */
#include "../src/clock/YTM32B1Mx/clock_YTM32B1Mx.h"
#elif (defined(YTM32B1H_SERIES))
/* YTM32B1Mx Clock System Level API header file */
#include "../src/clock/YTM32B1Hx/clock_YTM32B1Hx.h"
#elif (defined(YTM32Z1L_SERIES))
/* YTM32Z1x Clock System Level API header file */
#include "../src/clock/YTM32Z1x/clock_YTM32Z1x.h"

#else
#error "No valid CPU defined!"
#endif

/*!
 * @file clock.h
 */

/*! 
* @addtogroup clock_manager
*/
/*! @{*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @name Dynamic clock setting
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
* @brief Gets the clock frequency for a specific clock name.
*
* This function checks the current clock configurations and then calculates
* the clock frequency for a specific clock name defined in clock_names_t.
* Clock modules must be properly configured before using this function.
* See features.h for supported clock names for different chip families.
* The returned value is in Hertz. If it cannot find the clock name
* or the name is not supported for a specific chip family, it returns an
* STATUS_UNSUPPORTED. If frequency is required for a peripheral and the
* module is not clocked, then STATUS_MCU_GATED_OFF status is returned.
* Frequency is returned if a valid address is provided. If frequency is
* required for a peripheral that doesn't support protocol clock, the zero
* value is provided.
*
* @param[in] clockName Clock names defined in clock_names_t
* @param[out] frequency Returned clock frequency value in Hertz
* @return status   Error code defined in status_t
*/
status_t CLOCK_DRV_GetFreq(clock_names_t clockName, uint32_t *frequency);


/*!
 * @brief Set clock configuration according to pre-defined structure.
 *
 * This function sets system to target clock configuration; It sets the
 * clock modules registers for clock mode change. 
 *
 * @param[in] config  Pointer to configuration structure.
 *
 * @return Error code.
 *
 * @note If external clock is used in the target mode, please make sure it is
 * enabled, for example, if the external oscillator is used, please setup correctly.
 *
 * @note If the configuration structure is NULL, the function will set a default
 * configuration for clock.
 */
status_t CLOCK_DRV_Init(clock_user_config_t const *config);

/*! @} */


#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* CLOCK_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/

