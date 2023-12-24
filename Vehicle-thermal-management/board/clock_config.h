
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
 * @file clock_config.h
 * @brief 
 * 
 */


#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include "clock.h"



/*! @brief Count of user configuration structures */
#define CLOCK_MANAGER_CONFIG_CNT                           1U /*!< Count of user configuration */

/*! @brief Count of user Callbacks structures */
#define CLOCK_MANAGER_CALLBACK_CNT                         0U /*!< Count of user Callbacks */

/*! @brief Actived clock configuration */
#define CLOCK_MANAGER_ACTIVE_INDEX  0U

/*! @brief Array of User callbacks */
/* The tool do not support generate Callbacks configuration. It's always empty. */
extern clock_manager_callback_user_config_t *g_clockManCallbacksArr[];

/*! @brief Array of pointers to User configuration structures */
extern clock_manager_user_config_t const *g_clockManConfigsArr[CLOCK_MANAGER_CONFIG_CNT];

#endif /* CLOCK_CONFIG_H */



