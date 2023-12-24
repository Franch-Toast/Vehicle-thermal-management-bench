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
 * @file clock_YTM32B1Mx.h
 */

#ifndef CLOCK_YTM32B1Mx_H
#define CLOCK_YTM32B1Mx_H

#include "device_registers.h"
#include "status.h"
#include <stdint.h>
#include <stdbool.h>


/*!
 * @ingroup clock_manager_ytm32b1Mx
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CMU_ALWAYS_ON

/*! @brief Peripheral features list
 *         Constant array storing the mappings between clock names of the peripherals and feature lists.
 */
extern const uint8_t peripheralFeaturesList[CLOCK_NAME_COUNT];


/*! @brief EXTAL0 clock frequency. */
extern uint32_t g_xtal0ClkFreq;

/*! @brief The maximum number of system clock dividers and system clock divider indexes. */
#define SYS_CLK_MAX_NO    3U
#define SYSTEM_CLK_INDEX  0U
#define BUS_CLK_INDEX     1U

/*!
 * @brief SCU CLKOUT select
 * Implements scu_clkout_src_t_Class
 */
typedef enum
{
    SCU_CLKOUT_SEL_DISABLE      = 0U,     /*!< SCU CLKOUT Disable           */
    SCU_CLKOUT_SEL_FIRC_CLK     = 1U,     /*!< SCU CLKOUT Select FIRC CLK   */
    SCU_CLKOUT_SEL_SIRC_CLK     = 2U,     /*!< SCU CLKOUT Select SIRC CLK   */
    SCU_CLKOUT_SEL_FXOSC_CLK    = 3U,     /*!< SCU CLKOUT Select FXOSC CLK  */
    SCU_CLKOUT_SEL_SXOSC_CLK    = 4U,     /*!< SCU CLKOUT Select SXOSC CLK  */
    SCU_CLKOUT_SEL_PLL_CLK      = 5U,     /*!< SCU CLKOUT Select PLL CLK    */
    SCU_CLKOUT_SEL_CORE_CLK     = 7U,     /*!< SCU CLKOUT Select CORE CLK   */
} scu_clkout_src_t;

/*!
 * @brief SCU ClockOut configuration.
 * Implements scu_clock_out_config_t_Class
 */
typedef struct
{
    bool              enable;           /*!< SCU ClockOut enable or not.            */
    uint8_t           divider;          /*!< SCU ClockOut divider                   */
    scu_clkout_src_t  source;           /*!< SCU ClockOut source select.            */
} scu_clock_out_config_t;

/*!
 * @brief SCU FXOSC configuration.
 * Implements scu_fxosc_config_t_Class
 */
typedef struct
{
    bool enable;                       /*!< FXOSC enable */
    bool bypassMode;                   /*!< FXOSC bypass mode*/
    uint8_t gainSelection;             /*!< FXOSC gain selection */
    uint32_t frequency;                /*!< FXOSC frequency */
} scu_fxosc_config_t;

/*!
 * @brief SCU SXOSC configuration.
 * Implements scu_sxosc_config_t_Class
 */
typedef struct
{
    bool enable;                       /*!< SXOSC enable */
#if defined(SCU_SXOSC_CTRL_GMSEL_MASK)
    uint8_t gainSelection;             /*!< SXOSC gain selection */
#endif /* SCU_SXOSC_CTRL_GMSEL_MASK */
    bool bypassMode;                   /*!< SXOSC bypass mode*/
    bool deepsleepEnable;              /*!< SXOSC deepsleep enable */
    bool standbyEnable;                /*!< SXOSC standby enable */
    bool powerdownEnable;              /*!< SXOSC powerdown enable */
    uint32_t frequency;                /*!< SXOSC frequency */
} scu_sxosc_config_t;

/*!
 * @brief SCU PLL reference clock select
 * Implements scu_pll_ref_clk_t_Class
 */
typedef enum
{
    SCU_PLL_REF_FXOSC_CLK      = 0U,     /*!< SCU PLL use FXOSC as reference clock */
    SCU_PLL_REF_FIRC_CLK       = 1U,     /*!< SCU PLL use FIRC as reference clock  */ 
} scu_pll_ref_clk_t;

/*!
 * @brief SCU PLL configuration.
 * Implements scu_pll_config_t_Class
 */
typedef struct
{
    bool enable;                   /*!< PLL enable or not */
    scu_pll_ref_clk_t pllRefClock; /*!< PLL reference clock source */
    uint8_t pllFeedBackDiv;        /*!< PLL Feedback clock divider */
    uint8_t pllRefClkDiv;          /*!< PLL Reference clock divider */
} scu_pll_config_t;

/*!
 * @brief SCU system clock source.
 * Implements ipc_system_clock_src_t_Class
 */
typedef enum {
    SCU_SYSTEM_CLOCK_SRC_FIRC     = 0U,       /*!< Fast IRC         */
    SCU_SYSTEM_CLOCK_SRC_PLL      = 1U,       /*!< PLL Clock        */
    SCU_SYSTEM_CLOCK_SRC_FXOSC    = 2U,       /*!< External OSC     */
    SCU_SYSTEM_CLOCK_SRC_SIRC     = 3U,       /*!< Slow IRC         */
    SCU_SYSTEM_CLOCK_SRC_NONE     = 255U      /*!< MAX value        */
} scu_system_clock_src_t;

/*!
 * @brief SCU configure structure.
 * Implements scu_config_t_Class
 */
typedef struct
{
    bool                      sircDeepSleepEnable;
    bool                      sircStandbyEnable;
    bool                      sircPowerDownEnable;
    bool                      fircEnable;
    bool                      fircDeepSleepEnable;
    scu_system_clock_src_t    sysClkSrc;                      /*!< Core clock selection */
    scu_fxosc_config_t        fxoscConfig;                    /*!< External fast oscillator configuration.           */
#if FEATURE_SCU_SUPPORT_SXOSC
    scu_sxosc_config_t        sxoscConfig;                    /*!< External slow oscillator configuration.           */
#endif /* FEATURE_SCU_SUPPORT_SXOSC */
    scu_pll_config_t          pllConfig;                      /*!< Pll configuration.   */
    uint8_t                   sysDiv;                         /*!< system clock divider */
    uint8_t                   fastBusDiv;                     /*!< IPS Fast Bus clock divider */
    uint8_t                   slowBusDiv;                     /*!< IPS Slow Bus clock divider */
    uint8_t                   flashDiv;                       /*!< Flash Clock divider */
    uint8_t                   flashPrs;                       /*!< Flash clock prescaler */
    scu_clock_out_config_t    clockOutConfig;                 /*!< Clock Out configuration. */
} scu_config_t;

/*!
 * @brief CMU reference clock source.
 * Implements cmu_refclk_t_Class
 */
typedef enum
{
    CMU_REF_SIRC_CLOCK  = 0, /*!< Use SIRC as CMU clock reference clock source. */
    CMU_REF_FXOSC_CLOCK = 1, /*!< Use FXOSC as CMU clock reference clock source. */
} cmu_refclk_t;
/*!
 * @brief CMU channel configure structure.
 * Implements cmu_ch_config_t_Class
 */
typedef struct
{
    bool enable;                 /*!< Specifies whether the channel is enabled or disabled */
    bool resetEnable;            /*!< Specifies whether the channel clock error reset enable */
    cmu_refclk_t refClock;       /*!< CMU reference clock selection */
    uint16_t compareHigh;        /*!< CMU counter compare high threshold */
    uint16_t compareLow;         /*!< CMU counter compare low threshold */
} cmu_ch_config_t;
/*!
 * @brief CMU configure structure.
 * Implements cmu_config_t_Class
 */
typedef struct
{
    cmu_ch_config_t slowBusMonitor;           /*!< Clock monitor for slow bus clock */
    cmu_ch_config_t fircClockMonitor;           /*!< Clock monitor for fast bus clock */
    cmu_ch_config_t pllClockMonitor;         /*!< Clock monitor for core clock */
    cmu_ch_config_t fxoscClockMonitor;          /*!< Clock monitor for pll clock */
} cmu_config_t;

/*!
 * @brief SCU system clock divider.
 * Implements ipc_system_clock_src_t_Class
 */
typedef enum {
    SCU_SYS_CLK_DIV_BY_1  = 0,     /*!< Divided by 1 */
    SCU_SYS_CLK_DIV_BY_2  = 1,     /*!< Divided by 2 */
    SCU_SYS_CLK_DIV_BY_3  = 2,     /*!< Divided by 3 */
    SCU_SYS_CLK_DIV_BY_4  = 3,     /*!< Divided by 4 */
    SCU_SYS_CLK_DIV_BY_5  = 4,     /*!< Divided by 5 */
    SCU_SYS_CLK_DIV_BY_6  = 5,     /*!< Divided by 6 */
    SCU_SYS_CLK_DIV_BY_7  = 6,     /*!< Divided by 7 */
    SCU_SYS_CLK_DIV_BY_8  = 7,     /*!< Divided by 8 */
    SCU_SYS_CLK_DIV_BY_9  = 8,     /*!< Divided by 9 */
    SCU_SYS_CLK_DIV_BY_10 = 9,     /*!< Divided by 10 */
    SCU_SYS_CLK_DIV_BY_11 = 10,    /*!< Divided by 11 */
    SCU_SYS_CLK_DIV_BY_12 = 11,    /*!< Divided by 12 */
    SCU_SYS_CLK_DIV_BY_13 = 12,    /*!< Divided by 13 */
    SCU_SYS_CLK_DIV_BY_14 = 13,    /*!< Divided by 14 */
    SCU_SYS_CLK_DIV_BY_15 = 14,    /*!< Divided by 15 */
    SCU_SYS_CLK_DIV_BY_16 = 15,    /*!< Divided by 16 */
} system_clock_divider_t;

/*! @brief IPC clock source select
 *  Implements peripheral_clock_source_t_Class
 */
typedef enum 
{
    CLK_SRC_DISABLED        = 0x00U,            /*!< Disabled clock */
    CLK_SRC_FIRC            = 0x01U,            /*!< Fast IRC Clock */
    CLK_SRC_SIRC            = 0x02U,            /*!< Slow IRC Clock */
    CLK_SRC_FXOSC           = 0x03U,            /*!< External Fast OSC Clock */
#if FEATURE_SCU_SUPPORT_SXOSC
    CLK_SRC_SXOSC           = 0x04U,            /*!< External Slow OSC Clock */
#endif /* FEATURE_SCU_SUPPORT_SXOSC */
    CLK_SRC_PLL             = 0x05U,            /*!< PLL Clock */
} peripheral_clock_source_t;

/*!
 * @brief SCU ipc clock divider.
 * Implements ipc_clock_divider_t_Class
 */
typedef enum 
{
    SCU_IPC_CLK_DIV_BY_1  = 0,     /*!< Divider by 1 */   
    SCU_IPC_CLK_DIV_BY_2  = 1,     /*!< Divider by 2 */  
    SCU_IPC_CLK_DIV_BY_3  = 2,     /*!< Divider by 3 */  
    SCU_IPC_CLK_DIV_BY_4  = 3,     /*!< Divider by 4 */ 
    SCU_IPC_CLK_DIV_BY_5  = 4,     /*!< Divided by 5 */
    SCU_IPC_CLK_DIV_BY_6  = 5,     /*!< Divided by 6 */
    SCU_IPC_CLK_DIV_BY_7  = 6,     /*!< Divided by 7 */
    SCU_IPC_CLK_DIV_BY_8  = 7,     /*!< Divided by 8 */
    SCU_IPC_CLK_DIV_BY_9  = 8,     /*!< Divided by 9 */
    SCU_IPC_CLK_DIV_BY_10 = 9,     /*!< Divided by 10 */
    SCU_IPC_CLK_DIV_BY_11 = 10,    /*!< Divided by 11 */
    SCU_IPC_CLK_DIV_BY_12 = 11,    /*!< Divided by 12 */
    SCU_IPC_CLK_DIV_BY_13 = 12,    /*!< Divided by 13 */
    SCU_IPC_CLK_DIV_BY_14 = 13,    /*!< Divided by 14 */
    SCU_IPC_CLK_DIV_BY_15 = 14,    /*!< Divided by 15 */
    SCU_IPC_CLK_DIV_BY_16 = 15,    /*!< Divided by 16 */
} ipc_clock_divider_t;



/*! @brief IPC divider value select
 *  Implements peripheral_clock_divider_t_Class
 */
typedef enum
{
    DIV_BY_1  =  0U,        /*!< Divided by 1      */
    DIV_BY_2  =  1U,        /*!< Divided by 2      */
    DIV_BY_3  =  2U,        /*!< Divided by 3      */
    DIV_BY_4  =  3U,        /*!< Divided by 4      */
    DIV_BY_5  =  4U,        /*!< Divided by 5      */
    DIV_BY_6  =  5U,        /*!< Divided by 6      */
    DIV_BY_7  =  6U,        /*!< Divided by 7      */
    DIV_BY_8  =  7U,        /*!< Divided by 8      */
    DIV_BY_9  =  8U,        /*!< Divided by 9      */
    DIV_BY_10 =  9U,        /*!< Divided by 10     */
    DIV_BY_11 = 10U,        /*!< Divided by 11     */
    DIV_BY_12 = 11U,        /*!< Divided by 12     */
    DIV_BY_13 = 12U,        /*!< Divided by 13     */
    DIV_BY_14 = 13U,        /*!< Divided by 14     */
    DIV_BY_15 = 14U,        /*!< Divided by 15     */
    DIV_BY_16 = 15U         /*!< Divided by 16     */
} peripheral_clock_divider_t;

/*! @brief IPC peripheral instance clock configuration.
 *  Implements peripheral_clock_config_t_Class
 */
typedef struct
{
    /* clockName   is the name of the peripheral clock
     *    must be one of the following values (see the clock_names_t type from YTM32B1Mx_clock_names.h)
     *    IPC_DMA_CLOCK
     *    IPC_GPIO_CLOCK
     *    ...
     *    IPC_SPI0_CLOCK
     */
    clock_names_t clkName;
    bool clkGate;                                      /*!< Peripheral clock gate.                     */
    peripheral_clock_source_t clkSrc;                  /*!< Peripheral clock source.                   */
    peripheral_clock_divider_t divider;                /*!< Peripheral clock divider value.            */
} peripheral_clock_config_t;

/*! @brief IPC configuration.
 *  Implements ipc_config_t_Class
 */
typedef struct
{
    uint32_t count;                                    /*!< Number of peripherals to be configured.               */
    peripheral_clock_config_t const * peripheralClocks;       /*!< Pointer to the peripheral clock configurations array. */
} ipc_config_t;

/*!
 * @brief Clock configuration structure.
 * Implements clock_manager_user_config_t_Class
 */
typedef struct
{
    ipc_config_t                 ipcConfig;       /*!< IPC Clock configuration.      */
    scu_config_t const           *scuConfigPtr;   /*!< SCU Clock configuration.      */
    cmu_config_t const           *cmuConfigPtr;   /*!< SCU CMU Clock configuration.      */
} clock_manager_user_config_t;

typedef clock_manager_user_config_t clock_user_config_t;

/*!
 * @brief System clock configuration.
 * Implements sys_clk_config_t_Class
 */
typedef struct
{
    clock_names_t src;                         /*!< System clock source. */
    uint16_t dividers[SYS_CLK_MAX_NO];         /*!< System clock dividers. Value by which system clock is divided. 0 means that system clock is not divided. */
} sys_clk_config_t;

/*!
 * @brief Clock source configuration.
 * Implements clock_source_config_t_Class
 */
typedef struct
{
	bool       enable;                   /*!< Enable/disable clock source. */
    uint32_t   refFreq;                  /*!< Frequency of the input reference clock. It applies to external oscillator clock sources */
	uint16_t   outputDiv1;               /*!< First output divider. It's used as protocol clock by modules. Zero means that divider is disabled.   /
										  *   Possible values 0(disabled), 1, 2, 4, 8, 16, 32, 64; all the other values are not valid.             /
										  */
	uint16_t   outputDiv2;               /*!< Second output divider. It's used as protocol clock by modules. Zero means that divider is disabled.   /
										  *   Possible values 0(disabled), 1, 2, 4, 8, 16, 32, 64; all the other values are not valid.              /
										  */

} clock_source_config_t;


/*!
 * @brief The clock notification type.
 * Implements clock_manager_notify_t_Class
 */
typedef enum
{
    CLOCK_MANAGER_NOTIFY_RECOVER = 0x00U,  /*!< Notify IP to recover to previous work state.      */
    CLOCK_MANAGER_NOTIFY_BEFORE  = 0x01U,  /*!< Notify IP that system will change clock setting.  */
    CLOCK_MANAGER_NOTIFY_AFTER   = 0x02U,  /*!< Notify IP that have changed to new clock setting. */
} clock_manager_notify_t;

/*!
 * @brief The callback type, indicates what kinds of notification this callback handles.
 * Implements clock_manager_callback_type_t_Class
 */
typedef enum
{
    CLOCK_MANAGER_CALLBACK_BEFORE       = 0x01U, /*!< Callback handles BEFORE notification.          */
    CLOCK_MANAGER_CALLBACK_AFTER        = 0x02U, /*!< Callback handles AFTER notification.           */
    CLOCK_MANAGER_CALLBACK_BEFORE_AFTER = 0x03U  /*!< Callback handles BEFORE and AFTER notification */
} clock_manager_callback_type_t;

/*!
 * @brief Clock transition policy.
 * Implements clock_manager_policy_t_Class
 */
typedef enum
{
    CLOCK_MANAGER_POLICY_AGREEMENT,  /*!< Clock transfers gracefully. */
    CLOCK_MANAGER_POLICY_FORCIBLE    /*!< Clock transfers forcefully. */
} clock_manager_policy_t;

/*!
 * @brief Clock notification structure passed to clock callback function.
 * Implements clock_notify_struct_t_Class
 */
typedef struct
{
    uint8_t targetClockConfigIndex;    /*!< Target clock configuration index. */
    clock_manager_policy_t policy;     /*!< Clock transition policy.          */
    clock_manager_notify_t notifyType; /*!< Clock notification type.          */
} clock_notify_struct_t;

/*!
 * @brief Type of clock callback functions.
 */
typedef status_t (*clock_manager_callback_t)(clock_notify_struct_t *notify,
                                             void* callbackData);

/*!
 * @brief Structure for callback function and its parameter.
 * Implements clock_manager_callback_user_config_t_Class
 */
typedef struct
{
    clock_manager_callback_t      callback;      /*!< Entry of callback function.     */
    clock_manager_callback_type_t callbackType;  /*!< Callback type.                  */
    void* callbackData;                          /*!< Parameter of callback function. */
} clock_manager_callback_user_config_t;

/*!
 * @brief Clock manager state structure.
 * Implements clock_manager_state_t_Class
 */
typedef struct
{
    clock_manager_user_config_t const **configTable;/*!< Pointer to clock configure table.*/
    uint8_t clockConfigNum;                         /*!< Number of clock configurations.  */
    uint8_t curConfigIndex;                         /*!< Index of current configuration.  */
    clock_manager_callback_user_config_t **callbackConfig; /*!< Pointer to callback table.*/
    uint8_t callbackNum;                            /*!< Number of clock callbacks.       */
    uint8_t errorCallbackIndex;                     /*!< Index of callback returns error. */
} clock_manager_state_t;



/*******************************************************************************
 * API
 ******************************************************************************/

#if defined (__cplusplus)
extern "C" {
#endif /* __cplusplus*/


/*!
 * @brief Install pre-defined clock configurations.
 *
 * This function installs the pre-defined clock configuration table to
 * clock manager.
 *
 * @param[in] clockConfigsPtr Pointer to the clock configuration table.
 * @param[in] configsNumber Number of clock configurations in table.
 * @param[in] callbacksPtr Pointer to the callback configuration table.
 * @param[in] callbacksNumber Number of callback configurations in table.
 *
 * @return Error code.
 */
status_t CLOCK_SYS_Init(clock_manager_user_config_t const **clockConfigsPtr,
                        uint8_t configsNumber,
                        clock_manager_callback_user_config_t **callbacksPtr,
                        uint8_t callbacksNumber);

/*!
 * @brief Set system clock configuration according to pre-defined structure.
 *
 * This function sets system to target clock configuration; before transition,
 * clock manager will send notifications to all drivers registered to the
 * callback table.  When graceful policy is used, if some drivers are not ready
 * to change, clock transition will not occur, all drivers still work in
 * previous configuration and error is returned. When forceful policy is used,
 * all drivers should stop work and system changes to new clock configuration.
 * The function should be called only on run mode.
 *
 * @param[in] targetConfigIndex Index of the clock configuration.
 * @param[in] policy Transaction policy, graceful or forceful.
 *
 * @return Error code.
 *
 */
status_t CLOCK_SYS_UpdateConfiguration(uint8_t targetConfigIndex,
                                       clock_manager_policy_t policy);

/*!
 * @brief Set system clock configuration.
 *
 * This function sets the system to target configuration, it only sets the
 * clock modules registers for clock mode change, but not send notifications
 * to drivers. This function is different by different SoCs.
 *
 * @param[in] config Target configuration.
 *
 * @return Error code.
 *
 * @note This function should be called only on run mode.
 */
status_t CLOCK_SYS_SetConfiguration(clock_manager_user_config_t const * config);

/*!
 * @brief Get current system clock configuration.
 *
 * @return Current clock configuration index.
 */
uint8_t CLOCK_SYS_GetCurrentConfiguration(void);

/*!
 * @brief Get the callback which returns error in last clock switch.
 *
 * When graceful policy is used, if some IP is not ready to change clock
 * setting, the callback will return error and system stay in current
 * configuration. Applications can use this function to check which
 * IP callback returns error.
 *
 * @return Pointer to the callback which returns error.
 */
clock_manager_callback_user_config_t* CLOCK_SYS_GetErrorCallback(void);

/*!
 * @brief Wrapper over CLOCK_DRV_GetFreq function. It's part of the old API.
 *
 * @param[in] clockName Clock names defined in clock_names_t
 * @param[out] frequency Returned clock frequency value in Hertz
 * @return status   Error code defined in status_t
 */
status_t CLOCK_SYS_GetFreq(clock_names_t clockName, uint32_t *frequency);


#if defined (__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* CLOCK_YTM32B1Mx_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
