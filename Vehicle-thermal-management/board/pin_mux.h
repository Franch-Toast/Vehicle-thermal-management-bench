
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
 * @file pin_mux.h
 * @brief 
 * 
 */



#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#include "pins_driver.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! @brief Definitions for BOARD_InitPins Functional Group */

/*! @brief User number of configured pins */
#define NUM_OF_CONFIGURED_PINS0                        4
/*! @brief User configuration structure */
extern pin_settings_config_t g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0];

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

