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
 * @file etmr_common.h
 */
#ifndef eTMR_COMMON_H
#define eTMR_COMMON_H

#include <stddef.h>
#include "status.h"
#include "device_registers.h"
#include "callbacks.h"

/*!
 * @defgroup etmr_common etmr common
 * @ingroup etmr
 * @{
 */
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Table of base addresses for eTMR instances. */
extern eTMR_Type *const g_etmrBase[eTMR_INSTANCE_COUNT];
extern uint8_t const g_etmrChannelNum[eTMR_INSTANCE_COUNT];

/*! @brief Interrupt vectors for the eTMR peripheral. */
extern const IRQn_Type g_etmrIrqId[eTMR_INSTANCE_COUNT][FEATURE_eTMR_CHANNEL_INTERRUPT_COUNTS];
extern const IRQn_Type g_etmrFaultIrqId[eTMR_INSTANCE_COUNT];
extern const IRQn_Type g_etmrOverflowIrqId[eTMR_INSTANCE_COUNT];

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!< @brief Channel number for CHAN0.*/
#define CHAN0_IDX (0U)
/*!< @brief Channel number for CHAN1.*/
#define CHAN1_IDX (1U)
/*!< @brief Channel number for CHAN2.*/
#define CHAN2_IDX (2U)
/*!< @brief Channel number for CHAN3.*/
#define CHAN3_IDX (3U)
/*!< @brief Channel number for CHAN4.*/
#define CHAN4_IDX (4U)
/*!< @brief Channel number for CHAN5.*/
#define CHAN5_IDX (5U)
/*!< @brief Channel number for CHAN6.*/
#define CHAN6_IDX (6U)
/*!< @brief Channel number for CHAN7.*/
#define CHAN7_IDX (7U)

#define TOTAL_CHAN (8U)

/*******************************************************************************
 * Enumerations
 ******************************************************************************/
/**
 * @brief eTMR Channel Mode
 *
 * Implements : etmr_channel_mode_t_Class
 */
typedef enum
{
    eTMR_CHANNEL_DISABLE = 0x0U,    /*!< Channel disable */
    eTMR_PWM_MODE = 0x1U,           /*!< PWM mode */
    eTMR_COMPARE_MODE = 0x2U,       /*!< Compare mode */
    eTMR_INPUT_CAPTURE_MODE = 0x3U, /*!< Input capture mode */
} etmr_channel_mode_t;

/**
 * @brief eTMR PWM mode
 *
 * Implements : etmr_pwm_mode_t_Class
 */
typedef enum
{
    PWM_INDEPENDENT_MODE = 0,   /*!< Independent mode */
    PWM_COMPLEMENTARY_MODE = 1, /*!< Complementary mode */
} etmr_pwm_mode_t;

/*!
 * @brief eTMR Configure type of PWM update in the duty cycle or in ticks
 *
 * Implements : etmr_pwm_update_option_t_Class
 */
typedef enum
{
    eTMR_PWM_UPDATE_IN_DUTY_CYCLE = 0x00U, /*!< The type of PWM update in the duty cycle/pulse */
    eTMR_PWM_UPDATE_IN_TICKS = 0x01U,      /*!< The type of PWM update in ticks which is filled into registers */
} etmr_pwm_update_option_t;

/*!
 * @brief eTMR PWM period unit
 *
 * Implements : etmr_pwm_period_unit_t_Class
 */
typedef enum
{
    eTMR_PWM_PERIOD_IN_HZ = 0U,    /*!< The type of PWM period in Hz */
    eTMR_PWM_PERIOD_IN_TICKS = 1U, /*!< The type of PWM period in ticks */
} etmr_pwm_period_unit_t;

/*!
 * @brief eTMR PWM align mode
 *
 * Implements : etmr_pwm_align_mode_t_Class
 */
typedef enum
{
    eTMR_PWM_RIGHT_EDGE_ALIGN = 0U, /*!< Rising edge aligned pwm */
    eTMR_PWM_LEFT_EDGE_ALIGN = 1U,  /*!< Falling edge aligned pwm */
    eTMR_PWM_CENTER_ALIGN = 2U,     /*!< Center aligned pwm */
    eTMR_PWM_ASYMMETRICAL = 3U,     /*!< Asymmetrical pwm*/
} etmr_pwm_align_mode_t;

/*!
 * @brief eTMR clock source selection
 *
 * Implements : etmr_clock_source_t_Class
 */
typedef enum
{
    eTMR_CLOCK_SOURCE_INTERNALCLK = 0x00U, /*!< Internal clock */
    eTMR_CLOCK_SOURCE_EXTERNALCLK = 0x01U, /*!< External clock */
} etmr_clock_source_t;

/*!
 * @brief eTMR quadrature decoder modes, phase encode or count and direction mode
 *
 * Implements: etmr_qd_mode_t_Class
 */
typedef enum
{
    eTMR_QUAD_PHASE_B_FOLLOW_A = 0U,         /*!< Phase A and B, B follow A, counter increase */
    eTMR_QUAD_PHASE_A_FOLLOW_B = 1U,         /*!< Phase A and B, A follow B, counter increase */
    eTMR_QUAD_COUNT_AND_DIR_BY_PHASE_B = 2U, /*!< Counting and direction mode, phase B controls direction */
    eTMR_QUAD_COUNT_AND_DIR_BY_PHASE_A = 3U, /*!< Counting and direction mode, phase A controls direction */
} etmr_qd_mode_t;

/*!
 * @brief eTMR quadrature decoder clock prescaler
 *
 * Implements: etmr_qd_clock_prs_t_Class
 */
typedef enum
{
    eTMR_QD_CLOCK_DIV_BY_1 = 0x00U,  /*!< Divide by 1   */
    eTMR_QD_CLOCK_DIV_BY_2 = 0x01U,  /*!< Divide by 2   */
    eTMR_QD_CLOCK_DIV_BY_4 = 0x02U,  /*!< Divide by 4   */
    eTMR_QD_CLOCK_DIV_BY_8 = 0x03U,  /*!< Divide by 8   */
    eTMR_QD_CLOCK_DIV_BY_16 = 0x04U, /*!< Divide by 16  */
    eTMR_QD_CLOCK_DIV_BY_32 = 0x05U, /*!< Divide by 32  */
    eTMR_QD_CLOCK_DIV_BY_64 = 0x06U, /*!< Divide by 64  */
    eTMR_QD_CLOCK_DIV_BY_128 = 0x07U /*!< Divide by 128 */
} etmr_qd_clock_prs_t;

/*!
 * @brief eTMR CHMASK register sync selection
 *
 * Implements: etmr_sync_sel_t_Class
 */
typedef enum
{
    CHMASK_SYNC_WITH_REG = 0U,  /*!< Synchronized with register loading */
    CHMASK_SYNC_WITH_MOD = 1U,  /*!< Synchronized with counter matching MOD */
    CHMASK_SYNC_WITH_MID = 2U,  /*!< Synchronized with counter matching MID */
    CHMASK_SYNC_WITH_TRIG = 3U, /*!< Synchronized with trigger source 2 */
} etmr_mask_sync_sel_t;

/*!
 * @brief eTMR counter sync selection
 *
 * Implements: etmr_cnt_sync_sel_t_Class
 */
typedef enum
{
    CNT_SYNC_WITH_REG = 0,  /*!< Synchronized with register loading */
    CNT_SYNC_WITH_MID = 1,  /*!< Synchronized with counter matching MID */
    CNT_SYNC_WITH_TRIG = 2, /*!< Synchronized with trigger source 1 */
} etmr_cnt_sync_sel_t;

/*!
 * @brief eTMR register sync selection
 *
 * Implements: etmr_reg_sync_sel_t_Class
 */
typedef enum
{
    REG_SYNC_DISABLED = 0,  /*!< Synchronized disabled */
    REG_SYNC_WITH_MOD = 1,  /*!< Synchronized with counter matching MOD */
    REG_SYNC_WITH_MID = 2,  /*!< Synchronized with counter matching MID */
    REG_SYNC_WITH_TRIG = 3, /*!< Synchronized with trigger source 0 */
} etmr_reg_sync_sel_t;

/*!
 * @brief eTMR register loading trigger source
 *
 * Implements: etmr_sync_trig_src_t_Class
 */
typedef enum
{
    DISABLE_TRIGGER = 0U,   /*!< Disable trigger, with register loading or matching with MOD/MID */
    SW_TRIGGER = 1U,        /*!< Select software trigger to load */
    HW_TRIGGER = 2U,        /*!< Select hardware trigger to load */
    SW_AND_HW_TRIGGER = 3U, /*!< Select software and hardware trigger to load */
} etmr_sync_trig_src_t;

typedef enum
{
    eTMR_CHANNEL_0 = 0x00U, /*!< channel 0 */
    eTMR_CHANNEL_1 = 0x01U, /*!< channel 1 */
    eTMR_CHANNEL_2 = 0x02U, /*!< channel 2 */
    eTMR_CHANNEL_3 = 0x03U, /*!< channel 3 */
    eTMR_CHANNEL_4 = 0x04U, /*!< channel 4 */
    eTMR_CHANNEL_5 = 0x05U, /*!< channel 5 */
    eTMR_CHANNEL_6 = 0x06U, /*!< channel 6 */
    eTMR_CHANNEL_7 = 0x07U, /*!< channel 7 */
} etmr_channel_index_t;

typedef enum
{
    TRIGGER_FROM_MATCHING_EVENT = 0U,
    TRIGGER_FROM_PWM = 1U,
} etmr_trig_src_t;

/*!
 * @brief List of eTMR interrupts
 *
 * Implements : etmr_interrupt_option_t_Class
 */
typedef enum
{
    eTMR_CHANNEL0_INT_ENABLE = 0x00000001U,       /*!< Channel 0 interrupt */
    eTMR_CHANNEL1_INT_ENABLE = 0x00000002U,       /*!< Channel 1 interrupt */
    eTMR_CHANNEL2_INT_ENABLE = 0x00000004U,       /*!< Channel 2 interrupt */
    eTMR_CHANNEL3_INT_ENABLE = 0x00000008U,       /*!< Channel 3 interrupt */
    eTMR_CHANNEL4_INT_ENABLE = 0x00000010U,       /*!< Channel 4 interrupt */
    eTMR_CHANNEL5_INT_ENABLE = 0x00000020U,       /*!< Channel 5 interrupt */
    eTMR_CHANNEL6_INT_ENABLE = 0x00000040U,       /*!< Channel 6 interrupt */
    eTMR_CHANNEL7_INT_ENABLE = 0x00000080U,       /*!< Channel 7 interrupt */
    eTMR_FAULT_INT_ENABLE = 0x00000100U,          /*!< Fault interrupt */
    eTMR_TIME_OVER_FLOW_INT_ENABLE = 0x00000200U, /*!< Time overflow interrupt */
} etmr_interrupt_option_t;

/*!
 * @brief List of eTMR flags
 *
 * Implements : etmr_status_flag_t_Class
 */
typedef enum
{
    eTMR_CHANNEL0_FLAG = 0x00000001U,       /*!< Channel 0 Flag */
    eTMR_CHANNEL1_FLAG = 0x00000002U,       /*!< Channel 1 Flag */
    eTMR_CHANNEL2_FLAG = 0x00000004U,       /*!< Channel 2 Flag */
    eTMR_CHANNEL3_FLAG = 0x00000008U,       /*!< Channel 3 Flag */
    eTMR_CHANNEL4_FLAG = 0x00000010U,       /*!< Channel 4 Flag */
    eTMR_CHANNEL5_FLAG = 0x00000020U,       /*!< Channel 5 Flag */
    eTMR_CHANNEL6_FLAG = 0x00000040U,       /*!< Channel 6 Flag */
    eTMR_CHANNEL7_FLAG = 0x00000080U,       /*!< Channel 7 Flag */
    eTMR_FAULT0_FLAG = 0x00000100U,         /*!< Fault Flag */
    eTMR_FAULT1_FLAG = 0x00000200U,         /*!< Fault Flag */
    eTMR_FAULT2_FLAG = 0x00000400U,         /*!< Fault Flag */
    eTMR_FAULT3_FLAG = 0x00000800U,         /*!< Fault Flag */
    eTMR_TIME_OVER_FLOW_FLAG = 0x00001000U, /*!< Time overflow Flag */
    eTMR_RELOAD_FLAG = 0x00002000U,         /*!< Reload Flag; Available only on certain SoC's */
} etmr_status_flag_t;

#if FEATURE_eTMR_HAS_CNT_INIT_SRC
/*!
 * @brief eTMR Initial counter value source
 *
 * Implements : etmr_counter_init_src_t_Class
 */
typedef enum
{
    COUNTER_VAL_FROM_CNT = 0U,  /*!< Counter initial value from CNT register */
    COUNTER_VAL_FROM_INIT = 1U, /*!< Counter initial value from INIT register */
} etmr_counter_init_src_t;
#endif

/*!
 * @brief eTMR channel val0 and val1 trigger enablement
 *
 * Implements: etmr_trig_ch_param_t_Class
 */
typedef struct
{
    uint8_t channelId;           /*!< channel id */
    bool channelVal0MatchTrigEn; /*!< channel val0 match trigger enablement */
    bool channelVal1MatchTrigEn; /*!< channel val1 match trigger enablement */
} etmr_trig_ch_param_t;

/*!
 * @brief eTMR trigger configurations
 *
 * Implements: etmr_trig_config_t_Class
 */
typedef struct
{
    etmr_trig_src_t trigSrc;                      /*!< trigger source */
    uint8_t pwmOutputChannel;                     /*!< pwm output channel as trigger source */
    uint8_t outputTrigWidth;                      /*!< output trigger width */
    uint8_t outputTrigFreq;                       /*!< output trigger per x times */
    bool modMatchTrigEnable;                      /*!< mod match trigger enablement */
    bool midMatchTrigEnable;                      /*!< mid match trigger enablement */
    bool initMatchTrigEnable;                     /*!< init match trigger enablement */
    uint8_t numOfChannels;                        /*!< number of channels */
    etmr_trig_ch_param_t *channelTrigParamConfig; /*!< trigger channel configurations */
} etmr_trig_config_t;

/*!
 * @brief eTMR Registers sync configurations
 *
 * Implements : etmr_pwm_sync_t_Class
 */
typedef struct
{
    uint8_t regSyncFreq;                        /*!< register loading frequency */
    etmr_reg_sync_sel_t regSyncSel;             /*!< register loading opportunity */
    etmr_cnt_sync_sel_t cntInitSyncSel;         /*!< counter initial loading opportunity */
    etmr_mask_sync_sel_t maskOutputSyncSel;     /*!< mask output loading opportunity */
    etmr_sync_trig_src_t regSyncTrigSrc;        /*!< register loading trigger source selection */
    etmr_sync_trig_src_t cntInitSyncTrigSrc;    /*!< counter initial loading trigger source selection */
    etmr_sync_trig_src_t maskOutputSyncTrigSrc; /*!< mask output loading trigger source selection */
    bool hwTrigFromTmuEnable;                   /*!< hardware trigger from TMU enable or not */
    bool hwTrigFromCimEnable;                   /*!< hardware trigger from CIM enable or not */
    bool hwTrigFromPadEnable;                   /*!< hardware trigger from pad enable or not */
} etmr_pwm_sync_t;

/*!
 * @brief Configuration structure that the user needs to set
 *
 * Implements : etmr_user_config_t_Class
 */
typedef struct
{
    etmr_clock_source_t etmrClockSource;  /*!< Select clock source for eTMR */
    uint8_t etmrPrescaler;                /*!< eTMR clock prescaler */
    bool debugMode;                       /*!< true  -- debug mode enabled, counter will stop in debug mode
                                           *   false -- debug mode disabled, counter will continue to run in debug mode */
    etmr_pwm_sync_t *syncMethod;          /*!< etmr sync method */
    etmr_trig_config_t *outputTrigConfig; /*!< etmr output trigger configure */
    bool isTofIntEnabled;                 /*!< true: enable interrupt, false: disable interrupt */
} etmr_user_config_t;

/*!
 * @brief eTMR channel mode state
 *
 * Implements: etmr_channel_state_t_Class
 */
typedef enum
{
    eTMR_STATE_NO_MODE = 0U,           /*!< No mode */
    eTMR_STATE_PWM_INDEPENDENT = 1U,   /*!< PWM independent mode */
    eTMR_STATE_PWM_COMPLEMENTARY = 2U, /*!< PWM complementary mode */
    eTMR_STATE_OUTPUT_COMPARE = 3U,    /*!< Output compare mode */
    eTMR_STATE_INPUT_CAPTURE = 4U,     /*!< Input Capture mode */
} etmr_channel_state_t;

/*!
 * @brief eTMR input capture edge mode as rising edge or falling edge
 *
 * Implements : etmr_ic_capture_edge_t_Class
 */
typedef enum
{
    eTMR_NOT_SEL_EDGE = 0x00U, /*!< No select edge */
    eTMR_POS_EDGE = 0x01U,     /*!< Positive edge */
    eTMR_NEG_EDGE = 0x02U,     /*!< Negative edge */
    eTMR_DUAL_EDGES = 0x03U    /*!< Dual edges */
} etmr_ic_capture_edge_t;

/*!
 * @brief eTMR input capture measurement type
 *
 * Implements : etmr_ic_measurement_type_t_Class
 */
typedef enum
{
    eTMR_POS_PULSE_MEASUREMENT = 0x00U, /*!< Positive pulse measurement */
    eTMR_NEG_PULSE_MEASUREMENT = 0x01U, /*!< Negative pulse measurement */
    eTMR_PERIOD_MEASUREMENT = 0x02U,    /*!< Period measurement */
} etmr_ic_measurement_type_t;

/*!
 * @brief eTMR state structure of the driver
 *
 * Implements : etmr_state_t_Class
 */
typedef struct
{
    etmr_clock_source_t etmrClockSource;                              /*!< Clock source used by eTMR counter */
    uint32_t etmrSourceClockFrequency;                                /*!< The clock frequency is used for counting */
    etmr_channel_state_t etmrChnMode[FEATURE_eTMR_CHANNEL_MAX_COUNT]; /*!< Mode of operation for eTMR */
    uint32_t etmrPeriod;   /*!< This field is used only in PWM mode to store signal period */
    uint32_t etmrModValue; /*!< This field is used only in input capture mode to store MOD value */
    etmr_pwm_update_option_t typeOfUpdate[FEATURE_eTMR_CHANNEL_MAX_COUNT]; /*!< Type of update for PWM update */
    etmr_pwm_align_mode_t alignMode[FEATURE_eTMR_CHANNEL_MAX_COUNT];       /*!< Align mode of PWM update */
    uint32_t dutyCycle[FEATURE_eTMR_CHANNEL_MAX_COUNT];                    /*!< Duty cycle of PWM update */
    uint32_t offset[FEATURE_eTMR_CHANNEL_MAX_COUNT];                       /*!< Offset of pulse for asymmetric mode */
    bool measurementComplete[FEATURE_eTMR_CHANNEL_MAX_COUNT]; /*!< eTMR input capture measurement complete signal */
    uint32_t measurementPosPulseCnt[FEATURE_eTMR_CHANNEL_MAX_COUNT];            /*!< Positive pulse count value */
    uint32_t measurementNegPulseCnt[FEATURE_eTMR_CHANNEL_MAX_COUNT];            /*!< Negative pulse count value */
    uint32_t measurementCapCnt[FEATURE_eTMR_CHANNEL_MAX_COUNT];                 /*!< Store capture value */
    etmr_ic_capture_edge_t captureEdge[FEATURE_eTMR_CHANNEL_MAX_COUNT];         /*!< Input capture edge */
    etmr_ic_measurement_type_t measurementType[FEATURE_eTMR_CHANNEL_MAX_COUNT]; /*!< Measurement type */
    void *channelsCallbacksParams[FEATURE_eTMR_CHANNEL_MAX_COUNT];   /*!< The parameters of callback function */
    ic_callback_t channelsCallbacks[FEATURE_eTMR_CHANNEL_MAX_COUNT]; /*!< The callback function */
    bool enableNotification[FEATURE_eTMR_CHANNEL_MAX_COUNT]; /*!< The notification on the callback application */
} etmr_state_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointer to runtime state structure. */
extern etmr_state_t *etmrStatePtr[eTMR_INSTANCE_COUNT];

/*******************************************************************************
 * Functions
 ******************************************************************************/
/*!
 * @brief Disable eTMR counter
 *
 * @param[in] instance  The eTMR peripheral instance number.
 */
void eTMR_DRV_Disable(uint32_t instance);

/*!
 * @brief Enable eTMR counter
 *
 * @param[in] instance  The eTMR peripheral instance number.
 */
void eTMR_DRV_Enable(uint32_t instance);

/*!
 * @brief Initializes the eTMR driver.
 *
 * @param[in] instance The eTMR peripheral instance number.
 * @param[in] info The eTMR user configuration structure, see #etmr_user_config_t.
 * @param[out] state The eTMR state structure of the driver.
 * @return operation status
 *        - STATUS_SUCCESS : Completed successfully.
 *        - STATUS_ERROR : Error occurred.
 */
status_t eTMR_DRV_Init(uint32_t instance, const etmr_user_config_t *info, etmr_state_t *state);

/*!
 * @brief Get eTMR instance channel number by base.
 *
 * @param[in] etmrBase The eTMR base address pointer
 * @return eTMR instance channel number
 */
uint8_t eTMR_DRV_GetChannelNum(eTMR_Type *etmrBase);

/*!
 * @brief Shuts down the eTMR driver.
 *
 * @param[in] instance The eTMR peripheral instance number.
 * @return operation status
 *        - STATUS_SUCCESS : Completed successfully.
 *        - STATUS_ERROR : Error occurred.
 */
status_t eTMR_DRV_Deinit(uint32_t instance);

/*!
 * @brief This function will get the default configuration values
 *        in the structure which is used as a common use-case.
 * @param[out] config Pointer to the structure in which the
 *                    configuration will be saved.
 */
void eTMR_DRV_GetDefaultConfig(etmr_user_config_t *const config);

/*!
 * @brief This function will mask the output of the channels and at match events will be ignored
 * by the masked channels.
 *
 * @param [in] instance The eTMR peripheral instance number.
 * @param [in] maskEn The set of channel mask enable
 * @param [in] maskVal The set of channel mask value
 * @param [in] softwareTrigger If true a software trigger is generate to update PWM parameters.
 * @return success
 *        - STATUS_SUCCESS : Completed successfully.
 */
status_t eTMR_DRV_SetChnOutMask(uint32_t instance, uint8_t maskEn, uint16_t maskVal, bool softwareTrigger);

/*!
 * @brief This function configure the initial counter value. The counter will get this
 * value after an overflow event.
 *
 * @param [in] instance The eTMR peripheral instance number.
 * @param [in] counterValue Initial counter value.
 * @param [in] softwareTrigger If true a software trigger is generate to update parameters.
 * @return success
 *        - STATUS_SUCCESS : Completed successfully.
 */
status_t eTMR_DRV_SetCounterInit(uint32_t instance, uint16_t counterValue, bool softwareTrigger);

/*!
 * @brief This function configure the maximum counter value.
 *
 * @param [in] instance The eTMR peripheral instance number.
 * @param [in] counterValue Maximum counter value
 * @param [in] softwareTrigger If true a software trigger is generate to update parameters.
 * @return success
 *        - STATUS_SUCCESS : Completed successfully.
 */
status_t eTMR_DRV_SetCounterMod(uint32_t instance, uint16_t counterValue, bool softwareTrigger);

/*!
 * @brief This function will set the LDOK to start registers synchronization.
 * 
 * @param [in] instance The eTMR peripheral instance number.
 * @return success
 *        - STATUS_SUCCESS : Completed successfully.
 */
status_t eTMR_DRV_SetLdok(uint32_t instance);

/*!
 * @brief This function will clear the LDOK.
 *
 * @param [in] instance The eTMR peripheral instance number.
 * @return success
 *        - STATUS_SUCCESS : Completed successfully.
 */
status_t eTMR_DRV_ClearLdok(uint32_t instance);

/*!
 * @brief This function configures sync mechanism for some eTMR registers (MOD, MID,
 *        INIT, CHMASK, CHxVAL0, CHxVAL1).
 *
 * @param[in] instance The eTMR peripheral instance number.
 * @param[in] param The sync configuration structure.
 * @return operation status
 *        - STATUS_SUCCESS : Completed successfully.
 *        - STATUS_ERROR : Error occurred.
 */
status_t eTMR_DRV_SetSync(uint32_t instance, const etmr_pwm_sync_t *param);

/*!
 * @brief Set channel safe state when fault is detected.
 *
 * @param[in] instance the eTMR peripheral instance
 * @param[in] safeState the eTMR channels safe state after fault detected
 *            safeState: CH7FV | CH6FV | CH5FV | CH4FV |
 *                       CH3FV | CH2FV | CH1FV | CH0FV
 * @return    operation status
 *            - STATUS_SUCCESS : Completed successfully.
 *            - STATUS_ERROR :   Error occurred.
 */
status_t eTMR_DRV_SetSafeState(uint32_t instance, uint32_t safeState);

/*!
 * @brief This function configures output trigger
 * 
 * @param[in] instance the eTMR peripheral instance
 * @param[in] param    The trigger configuration structure
 * @return    operation status
 *            - STATUS_SUCCESS : Completed successfully.
 *            - STATUS_ERROR :   Error occurred.
 */
status_t eTMR_DRV_SetOutputTrigger(uint32_t instance, const etmr_trig_config_t *param);

/*!
 * @brief This function will enable the generation a list of interrupts.
 *        It includes the eTMR overflow interrupts, the reload point interrupt, the fault
 *        interrupt and the channel (n) interrupt.
 *
 * @param[in] instance The eTMR peripheral instance number.
 * @param[in] interruptMask The mask of interrupt. This is a logical OR of members of the
 *            enumeration ::etmr_interrupt_option_t
 * @return operation status
 *        - STATUS_SUCCESS : Completed successfully.
 */
status_t eTMR_DRV_EnableInterrupts(uint32_t instance, uint32_t interruptMask);

/*!
 * @brief This function is used to disable some interrupts.
 *
 * @param[in] instance The eTMR peripheral instance number.
 * @param[in] interruptMask The mask of interrupt. This is a logical OR of members of the
 *            enumeration ::etmr_interrupt_option_t
 */
void eTMR_DRV_DisableInterrupts(uint32_t instance, uint32_t interruptMask);

/*!
 * @brief This function will get the enabled eTMR interrupts.
 *
 * @param[in] instance The eTMR peripheral instance number.
 * @return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::etmr_interrupt_option_t
 */
uint32_t eTMR_DRV_GetEnabledInterrupts(uint32_t instance);

/*!
 * @brief This function will get the eTMR status flags.
 * @note: Regarding the duty cycle is 100% at the channel output, the match interrupt
 *        has no event due to the CHxVAL1 value are not between INIT value and MOD value.
 *
 * @param[in] instance The eTMR peripheral instance number.
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::etmr_status_flag_t
 */
uint32_t eTMR_DRV_GetStatusFlags(uint32_t instance);

/*!
 * @brief Retrieves the frequency of the clock source feeding the eTMR counter.
 *
 * Function will return a 0 if no clock source is selected and the eTMR counter is disabled
 *
 * @param [in] instance The eTMR peripheral instance number.
 * @return The frequency of the clock source running the eTMR counter (0 if counter is disabled)
 */
uint32_t eTMR_DRV_GetFrequency(uint32_t instance);

/*!
 * @brief This function is used to covert the given frequency to period in ticks
 *
 * @param [in] instance The eTMR peripheral instance number.
 * @param [in] freqencyHz Frequency value in Hz.
 *
 * @return The value in ticks of the frequency
 */
uint32_t eTMR_DRV_ConvertFreqToPeriodTicks(uint32_t instance, uint32_t freqencyHz);

/*!
 * @brief This function is used to clear all status flags
 *
 * @param [in] instance The eTMR peripheral instance number.
 *
 * @return The status
 */
status_t eTMR_DRV_ClearAllStatusFlag(uint32_t instance);

#if defined(__cplusplus)
}
#endif

/*! @}*/

/*! @}*/ /* End of addtogroup etmr_common */

#endif /* eTMR_COMMON_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
