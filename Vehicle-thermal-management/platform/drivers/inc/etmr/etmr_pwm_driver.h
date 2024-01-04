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
 * @file etmr_pwm_driver.h
 */

#ifndef eTMR_PWM_DRIVER_H
#define eTMR_PWM_DRIVER_H

#include "etmr_common.h"

/*!
 * @addtogroup etmr_pwm_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Maximum value for PWM duty cycle */
#define eTMR_MAX_DUTY_CYCLE      (0x8000U)
/*! @brief Shift value which converts duty to ticks */
#define eTMR_DUTY_TO_TICKS_SHIFT (15U)

/*!
 * @brief The polarity of the channel output is configured in PWM signal
 *
 * Implements : etmr_polarity_t_Class
 */
typedef enum
{
    eTMR_POLARITY_NORMAL = 0x00U, /*!< The channel polarity is not inverted */
    eTMR_POLARITY_INVERT = 0x01U  /*!< The channel polarity is inverted */
} etmr_polarity_t;

/*!
 * @brief eTMR fault mode
 *
 * Implements : etmr_fault_mode_t_Class
 */
typedef enum
{
    eTMR_FAULT_WITH_CLK = 0U,    /*!< Fault generated, but etmr clock is still existing */
    eTMR_FAULT_WITHOUT_CLK = 1U, /*!< Fault generated, and etmr clock is lost */
} etmr_fault_mode_t;

/*!
 * @brief PWM recovery opportunity
 *
 * Implements: etmr_pwm_recovery_opportunity_t_Class
 */
typedef enum
{
    eTMR_FAULT_PWM_RECOVERY_DISABLED = 0U,    /*!< not recovery */
    eTMR_FAULT_PWM_RECOVERY_WITH_MID = 1U,    /*!< recovery when counter matches with MID */
    eTMR_FAULT_PWM_RECOVERY_WITH_MOD = 2U,    /*!< recovery when counter matches with MOD */
    eTMR_FAULT_PWM_RECOVERY_IMMEDIATELY = 3U, /*!< recovery immediately */
} etmr_pwm_recovery_opportunity_t;

/*!
 * @brief PWM recovery mode
 *
 * Implements: etmr_pwm_recovery_auto_mode_t_Class
 */
typedef enum
{
    eTMR_MANUAL_CLEAR_FAULT_FLAG_THEN_AUTO_RECOVERY = 0U, /*!< Recovery needs clearing fault flag first */
    eTMR_AUTO_RECOVERY_WITHOUT_CLEAR_FAULT_FLAG = 1U,     /*!< Recovery regardless of clearing fault flag */
    eTMR_AUTO_RECOVERY_WITH_CLEAR_FAULT_FLAG = 2U,        /*!< Recovery and clearing fault flag */
} etmr_pwm_recovery_auto_mode_t;

/*!
 * @brief Fault input polarity mode selection
 *
 * Implements: etmr_fault_input_polarity_t_Class
 */
typedef enum
{
    eTMR_FAULT_SIGNAL_HIGH = 0U, /*!< Regard high level(1) input as fault signal */
    eTMR_FAULT_SIGNAL_LOW = 1U,  /*!< Regard low level(0) input as fault signal */
} etmr_fault_input_polarity_t;

/*!
 * @brief Select level of the channel (n) output at the beginning
 *
 * Implements : etmr_safe_state_t_Class
 */
typedef enum
{
    eTMR_LOW_STATE = 0x00U,  /*!< When fault is detected PWM channel is low. */
    eTMR_HIGH_STATE = 0x01U, /*!< When fault is detected PWM channel is high. */
    eTMR_TRI_STATE = 0x02U,  /*!< When fault is detected PWM channel is tristate. */
} etmr_safe_state_t;

/*!
 * @brief eTMR driver PWM Fault channel parameters
 *
 * Implements : etmr_pwm_ch_fault_param_t_Class
 */
typedef struct
{
    bool faultChannelEnabled;                       /*!< Fault channel enable or not */
    etmr_fault_input_polarity_t faultInputPolarity; /*!< Fault input polarity signal */
} etmr_fault_ch_param_t;

/*!
 * @brief eTMR driver PWM Fault parameter
 *
 * Implements : etmr_pwm_fault_param_t_Class
 */
typedef struct
{
    bool pwmFaultInterrupt;                                                   /*!< PWM fault interrupt state */
    uint8_t faultFilterSampleCounter;                                         /*!< Fault filter sample counter */
    uint8_t faultFilterSamplePeriod;                                          /*!< Fault filter sample period */
    uint8_t faultInputStrentch;                                               /*!< Fault input strentch */
    etmr_pwm_recovery_opportunity_t pwmRecoveryOpportunity;                   /*!< PWM Recovery opportunity */
    etmr_pwm_recovery_auto_mode_t pwmAutoRecoveryMode;                        /*!< PWM Recovery automatic mode */
    etmr_fault_mode_t faultMode;                                              /*!< Fault mode */
    etmr_fault_ch_param_t etmrFaultChannelParam[FEATURE_eTMR_FAULT_CHANNELS]; /*!< Fault channels configuration */
    etmr_safe_state_t safeState[FEATURE_eTMR_CHANNEL_MAX_COUNT];              /*!< Channel safe state after fault */
} etmr_fault_param_t;

/*!
 * @brief eTMR driver independent PWM parameter
 *
 * Implements : etmr_pwm_ch_param_t_Class
 */
typedef struct
{
    uint8_t hwChannelId;                   /*!< Physical hardware channel ID */
    etmr_polarity_t polarity;              /*!< Polarity of the complementary even channel signal */
    bool pwmSrcInvert;                     /*!< Polarity of the channel PWM, not includes output initial */
    etmr_pwm_align_mode_t align;           /*!< PWM alignment mode */
    uint8_t channelInitVal;                /*!< Channel output initial value */
    etmr_pwm_update_option_t typeOfUpdate; /*!< Type of update */
    uint32_t dutyCycle;                    /*!< PWM duty cycle */
    uint32_t offset;                       /*!< offset from 0 to the rising edge of pwm for asymmetrical mode */
    bool enableSecondChannelOutput;        /*!< Enable complementary mode on next channel */
    etmr_polarity_t secondChannelPolarity; /*!< Polarity of the complementary odd channel signal */
#if FEATURE_eTMR_HAS_DOUBLE_SWITCH
    bool enableDoubleSwitch; /*!< Enable double switch mode */
#endif
#if FEATURE_eTMR_DEADTIME_CONFIG_EACH_CHANNEL
    uint16_t evenDeadTime; /*!< Enable/disable dead time for channel 0,2,4,6 */
    uint16_t oddDeadTime;  /*!< Enable/disable dead time for channel 1,3,5,7 */
#endif
#if FEATURE_eTMR_HAS_CHANNEL_VALUE_MATCH_INTERRUPT_IN_PWM_MODE
    bool interruptEnable; /*!< Interrupt enable or not */
#endif
} etmr_pwm_ch_param_t;

#if !FEATURE_eTMR_DEADTIME_CONFIG_EACH_CHANNEL
typedef struct
{
    uint8_t prs;           /*!< Prescaler value */
    uint16_t evenDeadTime; /*!< Enable/disable dead time for channel 0,2,4,6 */
    uint16_t oddDeadTime;  /*!< Enable/disable dead time for channel 1,3,5,7 */
} etmr_deadtime_param_t;
#endif

/*!
 * @brief eTMR driver PWM parameters
 *
 * Implements : etmr_pwm_param_t_Class
 */
typedef struct
{
    uint8_t nNumPwmChannels;  /*!< Number of independent PWM channels */
    etmr_channel_mode_t mode; /*!< eTMR pwm mode */
    uint32_t uFrequencyHZ;    /*!< PWM period in Hz */
#if FEATURE_eTMR_HAS_CNT_INIT_SRC
    bool counterInitValFromInitReg; /*!< Counter initial value source from INIT register or not */
#endif
    uint32_t cntVal;                       /*!< Counter initial value from CNT register */
    etmr_pwm_ch_param_t *pwmChannelConfig; /*!< Configuration for independent PWM channels */
#if !FEATURE_eTMR_DEADTIME_CONFIG_EACH_CHANNEL
    etmr_deadtime_param_t *deadtimeConfig; /*!< Configuration for PWM dead time */
#endif
    etmr_fault_param_t *faultConfig; /*!< Configuration for PWM fault */
} etmr_pwm_param_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the PWM signal for the independent channel
 *
 * @param[in] instance the eTMR peripheral instance number.
 * @param[in] param    eTMR driver PWM parameters.
 */
status_t eTMR_DRV_InitPwmChannel(uint32_t instance, const etmr_pwm_param_t *param);

/*!
 * @brief This function will update the duty cycle for the PWM signal
 *        at the initialization.
 *
 * @param[in] instance the eTMR peripheral instance number.
 * @param[in] param    eTMR driver PWM parameters.
 * @return success
 *        - STATUS_SUCCESS : Completed successfully.
 *        - STATUS_ERROR : Error occurred.
 */
status_t eTMR_DRV_InitPwmDutyCycleChannel(uint32_t instance, const etmr_pwm_param_t *param);

/*!
 * @brief Configure fault settings in the initialization
 *
 * @param[in] instance the eTMR peripheral instance number.
 * @param[in] param    eTMR driver PWM fault parameters
 * @return success
 *        - STATUS_SUCCESS : Completed successfully.
 *        - STATUS_ERROR : Error occurred.
 */
status_t eTMR_DRV_InitFault(uint32_t instance, const etmr_fault_param_t *param);

/*!
 * @brief This function is to initialize counter, configure pwm period, duty cycle
 *        and fault for specified channels.
 *
 * @param [in] instance The eTMR peripheral instance number.
 * @param [in] param eTMR driver PWM parameter to configure PWM options.
 * @return success
 *        - STATUS_SUCCESS : Completed successfully.
 *        - STATUS_ERROR : Error occurred.
 */
status_t eTMR_DRV_InitPwm(uint32_t instance, const etmr_pwm_param_t *param);

/*!
 * @brief Stops all PWM channels .
 *
 * @param [in] instance The eTMR peripheral instance number.
 * @return success
 *        - STATUS_SUCCESS : Completed successfully.
 *        - STATUS_ERROR : Error occurred.
 */
status_t eTMR_DRV_DeinitPwm(uint32_t instance);

/*!
 * @brief This function will update the val0 and val1 to change the duty cycle
 * 
 * @param[in] instance  The eTMR peripheral instance number.
 * @param[in] channel  The channel index
 * @param[in] periodTicks The period in ticks
 * @param[in] dutyCycleTicks The duty cycle in ticks
 * @param[in] offset The offset in ticks for asymmetrical pwm
 * @return success
 *        - STATUS_SUCCESS : Completed successfully.
 *        - STATUS_ERROR : Error occurred.
 */
status_t eTMR_DRV_UpdatePwmPeriodAndDuty(uint32_t instance,
                                         uint8_t channel,
                                         uint32_t periodTicks,
                                         uint32_t dutyCycleTicks,
                                         uint32_t offset);

/*!
 * @brief This function updates the waveform output in PWM mode (duty cycle and phase).
 *
 * @param [in] instance The eTMR peripheral instance number.
 * @param [in] channel The channel number. In combined mode, the code finds the channel.
 * @param [in] dutyCycle  Duty cycle of PWM.
 * @param [in] offset The offset from counter initial value to the first rising edge.
 *                    It is used for asymmetrical alignment pwm. When in edge align and
 *                    center align pwm mode, it is forced to 0.
 * @return success
 *        - STATUS_SUCCESS : Completed successfully.
 *        - STATUS_ERROR : Error occurred.
 */
status_t eTMR_DRV_UpdatePwmChannel(uint32_t instance, uint8_t channel, uint32_t dutyCycle, uint32_t offset);

/*!
 * @brief This function will update the new period in the frequency or
 *        in the counter value into mode register which modify the period
 *        of PWM signal on the channel output.
 *
 * @param [in] instance The eTMR peripheral instance number.
 * @param [in] unit The unit of newPeriod.
 * @param [in] newPeriod The frequency or the counter value which will select with modified value for PWM signal.
 *                       If the type of update in the duty cycle, the newPeriod parameter must be value
 *                       between 1U and maximum is the frequency of the eTMR counter.
 *                       If the type of update in ticks, the newPeriod parameter must be value between 1U and 0xFFFFU.
 * @return operation status
 *        - STATUS_SUCCESS : Completed successfully.
 *        - STATUS_ERROR : Error occurred.
 */
status_t eTMR_DRV_UpdatePwmPeriod(uint32_t instance, etmr_pwm_period_unit_t unit, uint32_t newPeriod);

/*!
 * @brief This function generate software trigger to synchronize
 *        registers(INIT, CHMASK, MOD, MID, CHx_VAL0, CHx_VAL1)
 *
 * @param[in] instance the eTMR peripheral instance number
 */
void eTMR_DRV_SyncWithSoftTrigger(uint32_t instance);

#if defined(__cplusplus)
}
#endif

/*! @}*/

/*! @}*/ /* End of addtogroup etmr_pwm_driver */

#endif /* eTMR_PWM_DRIVER_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
