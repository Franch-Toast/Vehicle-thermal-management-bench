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
 * @file etmr_common.c
 */

#include "etmr_common.h"
#include "etmr_hw_access.h"
#include "interrupt_manager.h"
#include "clock_manager.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Table of base addresses for eTMR instances. */
eTMR_Type *const g_etmrBase[eTMR_INSTANCE_COUNT] = eTMR_BASE_PTRS;
uint8_t const g_etmrChannelNum[eTMR_INSTANCE_COUNT] = FEATURE_eTMR_CHANNEL_COUNTS;

/*! @brief Interrupt vectors for the eTMR peripheral. */
const IRQn_Type g_etmrIrqId[eTMR_INSTANCE_COUNT][FEATURE_eTMR_CHANNEL_INTERRUPT_COUNTS] = eTMR_CHN_IRQS;
const IRQn_Type g_etmrFaultIrqId[eTMR_INSTANCE_COUNT] = eTMR_FAULT_IRQS;
const IRQn_Type g_etmrOverflowIrqId[eTMR_INSTANCE_COUNT] = eTMR_OVF_IRQS;

/*! @brief Pointer to runtime state structure. */
etmr_state_t *etmrStatePtr[eTMR_INSTANCE_COUNT] = { NULL };

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_Disable
 * Description   : Disable eTMR counter
 *
 * Implements    : eTMR_DRV_Disable_Activity
 *END**************************************************************************/
void eTMR_DRV_Disable(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);

    eTMR_Type *etmrBase = g_etmrBase[instance];

    eTMR_Disable(etmrBase);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_Enable
 * Description   : Enable eTMR counter
 *
 * Implements    : eTMR_DRV_Enable_Activity
 *END**************************************************************************/
void eTMR_DRV_Enable(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);

    eTMR_Type *etmrBase = g_etmrBase[instance];

    eTMR_Enable(etmrBase);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_Init
 * Description   : Initializes the eTMR driver and get the clock frequency value
 * which select one of three possible clock sources for the eTMR counter.
 *
 * Implements    : eTMR_DRV_Init_Activity
 *END**************************************************************************/
status_t eTMR_DRV_Init(uint32_t instance, const etmr_user_config_t *info, etmr_state_t *state)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(info != NULL);
    // DEV_ASSERT(state != NULL);
    DEV_ASSERT((info->etmrClockSource == eTMR_CLOCK_SOURCE_INTERNALCLK) ||
               (info->etmrClockSource == eTMR_CLOCK_SOURCE_EXTERNALCLK));
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    status_t status = STATUS_SUCCESS;
    uint8_t index;

    /* Check if this instance is already initialized */
    if (etmrStatePtr[instance] != NULL)
    {
        status = STATUS_ERROR;
    }
    else // instance is not initialized
    {
        /* Configure state structure. */
        state->etmrClockSource = info->etmrClockSource;
        state->etmrPeriod = 0U;
        state->etmrModValue = 0U;
        for (index = 0U; index < g_etmrChannelNum[instance]; index++)
        {
            state->typeOfUpdate[index] = eTMR_PWM_UPDATE_IN_DUTY_CYCLE;
            state->alignMode[index] = eTMR_PWM_RIGHT_EDGE_ALIGN;
            state->dutyCycle[index] = 0;
            state->offset[index] = 0;
            state->measurementComplete[index] = 0;
            state->measurementPosPulseCnt[index] = 0;
            state->measurementNegPulseCnt[index] = 0;
            state->measurementCapCnt[index] = 0;
            state->measurementType[index] = eTMR_POS_PULSE_MEASUREMENT;
            state->channelsCallbacksParams[index] = NULL;
            state->channelsCallbacks[index] = NULL;
            state->enableNotification[index] = false;
        }

        /* The reset operation */
        eTMR_DRV_Reset(instance);
        /* Set etmr clock source */
        eTMR_SetClkSrc(etmrBase, info->etmrClockSource);
        /* Set etmr clock prescaler */
        eTMR_SetClkPrs(etmrBase, info->etmrPrescaler - 1);
        /* Set etmr debug mode */
        eTMR_SetDebugModeDisable(etmrBase, !info->debugMode);
        /* Configure etmrStatePtr */
        etmrStatePtr[instance] = state;
        /* Get clock name used to configure the eTMR module */
        state->etmrSourceClockFrequency = eTMR_DRV_GetFrequency(instance);
    }

    if (STATUS_SUCCESS == status)
    {
        /* Configure sync for between registers and buffers */
        if (info->syncMethod != NULL)
        {
            status = eTMR_DRV_SetSync(instance, info->syncMethod);
        }

        /* Configure the output trigger */
        if (info->outputTrigConfig != NULL)
        {
            eTMR_DRV_SetOutputTrigger(instance, info->outputTrigConfig);
        }

        /* Check if enable interrupt in counter mode */
        if (info->isTofIntEnabled)
        {
            /* Clear the overflow flag */
            eTMR_DRV_ClearTofFlag(instance);
            /* Enable timer overflow interrupt */
            eTMR_SetTofIntEnable(etmrBase, true);
            INT_SYS_EnableIRQ(g_etmrOverflowIrqId[instance]);
        }
        else
        {
            eTMR_SetTofIntEnable(etmrBase, false);
            INT_SYS_DisableIRQ(g_etmrOverflowIrqId[instance]);
        }
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetChannelNum
 * Description   : Get eTMR channel number by base address
 *
 * Implements    : eTMR_DRV_GetChannelNum_Activity
 *END**************************************************************************/
uint8_t eTMR_DRV_GetChannelNum(eTMR_Type *etmrBase)
{
    uint8_t instance;

    for (instance = 0; instance < eTMR_INSTANCE_COUNT; instance++)
    {
        if (g_etmrBase[instance] == etmrBase)
        {
            break;
        }
    }

    return g_etmrChannelNum[instance];
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_Deinit
 * Description   : Shuts down the eTMR driver.
 * First, eTMR_DRV_Init must be called. Then this function will disables the eTMR module.
 *
 * Implements    : eTMR_DRV_Deinit_Activity
 *END**************************************************************************/
status_t eTMR_DRV_Deinit(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);

    /* Reset all eTMR register */
    eTMR_DRV_Reset(instance);

    /* Clear etmr state */
    etmrStatePtr[instance] = NULL;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetDefaultConfig
 * Description   : This function will get the default configuration values
 * in the structure which is used as a common use-case.
 * Return        : None
 * Implements    : eTMR_DRV_GetDefaultConfig_Activity
 *END**************************************************************************/
void eTMR_DRV_GetDefaultConfig(etmr_user_config_t *const config)
{
    DEV_ASSERT(config != NULL);

    config->etmrClockSource = eTMR_CLOCK_SOURCE_INTERNALCLK;
    config->etmrPrescaler = 1;
    config->debugMode = true;
    config->syncMethod->regSyncFreq = 1;                // 1 cycles
    config->syncMethod->regSyncSel = REG_SYNC_WITH_MOD; // sync when counter match with MOD
    config->syncMethod->cntInitSyncSel = CNT_SYNC_WITH_REG;
    config->syncMethod->maskOutputSyncSel = CHMASK_SYNC_WITH_REG;
    config->syncMethod->regSyncTrigSrc = DISABLE_TRIGGER;
    config->syncMethod->cntInitSyncTrigSrc = DISABLE_TRIGGER;
    config->syncMethod->maskOutputSyncTrigSrc = DISABLE_TRIGGER;
    config->syncMethod->hwTrigFromTmuEnable = false;
    config->syncMethod->hwTrigFromCimEnable = false;
    config->syncMethod->hwTrigFromPadEnable = false;
    config->outputTrigConfig = NULL;
    config->isTofIntEnabled = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetChnOutMasks
 * Description   : This function will mask the output of the channels and at match
 * events will be ignored by the masked channels.
 *
 * Implements : eTMR_DRV_SetChnOutMasks_Activity
 *END**************************************************************************/
status_t eTMR_DRV_SetChnOutMask(uint32_t instance, uint8_t maskEn, uint16_t maskVal, bool softwareTrigger)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    eTMR_ClearLdok(etmrBase);

    if (softwareTrigger)
    {
        /* select CHMASK loading trigger source */
        eTMR_SetMaskLoadTrigSrc(etmrBase, SW_TRIGGER);
        /* select CHMASK loading opportunity */
        eTMR_SetMaskLoadOpportunity(etmrBase, CHMASK_SYNC_WITH_TRIG);
    }
    else // sync with register loading
    {
        /* select CHMASK loading trigger source */
        eTMR_SetMaskLoadTrigSrc(etmrBase, DISABLE_TRIGGER);
        /* select CHMASK loading opportunity */
        eTMR_SetMaskLoadOpportunity(etmrBase, CHMASK_SYNC_WITH_REG);
    }
    /* set channel Mask enable and value */
    eTMR_SetChnOutMask(etmrBase, maskVal, maskEn);
    /* set ldok */
    eTMR_DRV_SetLdok(instance);

    if (softwareTrigger)
    {
        /* generate one bus clock cycle pulse trigger */
        eTMR_GenSoftwareTrigger(etmrBase, true);
    }

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetCounterInit
 * Description   : This function configure the initial counter value. The counter
 * will get this value after an overflow event.
 *
 * Implements : eTMR_DRV_SetCounterInit_Activity
 *END**************************************************************************/
status_t eTMR_DRV_SetCounterInit(uint32_t instance, uint16_t counterValue, bool softwareTrigger)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    /* set counter load trigger source */
    eTMR_SetCounterLoadTrigSrc(etmrBase, SW_TRIGGER);
    /* set counter load opportunity */
    eTMR_SetCounterLoadOpportunity(etmrBase, CNT_SYNC_WITH_TRIG);
#if FEATURE_eTMR_HAS_INIT_REG
    /* set counter initial value */
    eTMR_SetInitVal(etmrBase, counterValue);
#else
    (void)counterValue;
#endif
    /* set ldok */
    eTMR_DRV_SetLdok(instance);
    /* generate software trigger */
    eTMR_GenSoftwareTrigger(etmrBase, softwareTrigger);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetCounterMod
 * Description   : This function configure the maximum counter value.
 *
 * Implements : eTMR_DRV_SetCounterMod_Activity
 *END**************************************************************************/
status_t eTMR_DRV_SetCounterMod(uint32_t instance, uint16_t counterValue, bool softwareTrigger)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    /* set MOD value */
    eTMR_SetMod(etmrBase, counterValue - 1U + FEATURE_eTMR_COUNT_FROM_INIT_PLUS_ONE);
    /* set ldok */
    eTMR_DRV_SetLdok(instance);
    /* generate software trigger */
    eTMR_GenSoftwareTrigger(etmrBase, softwareTrigger);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetLdok
 * Description   : This function will set the LDOK to start registers synchronization.
 *
 * Implements : eTMR_DRV_SetLdok_Activity
 *END**************************************************************************/
status_t eTMR_DRV_SetLdok(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    /* Open Ldok to start transfer from shadow register to working register */
    eTMR_SetLdok(etmrBase);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_ClearLdok
 * Description   : This function will clear the LDOK.
 *
 * Implements : eTMR_DRV_ClearLdok_Activity
 *END**************************************************************************/
status_t eTMR_DRV_ClearLdok(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    /* Open Ldok to start transfer from shadow register to working register */
    eTMR_ClearLdok(etmrBase);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetSync
 * Description   : This function configure the synchronization for PWM register
 * (INIT, MOD, MID, VAL0/1, CHMASK). If this function is used whit wrong parameters
 * it's possible to generate wrong waveform. Registers synchronization need to
 * be configured for PWM and output compare mode.
 *
 * Implements : eTMR_DRV_SetSync_Activity
 *END**************************************************************************/
status_t eTMR_DRV_SetSync(uint32_t instance, const etmr_pwm_sync_t *param)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(param != NULL);
    eTMR_Type *etmrBase = g_etmrBase[instance];
    status_t retStatus = STATUS_SUCCESS;

    /* set register loading frequency */
    eTMR_SetRegLoadFreq(etmrBase, param->regSyncFreq - 1U);
    /* set hardware trigger to register loading enable or not */
    eTMR_SetHwTrig0Enable(etmrBase, param->hwTrigFromTmuEnable);
    /* set hardware trigger to counter loading enable or not */
    eTMR_SetHwTrig1Enable(etmrBase, param->hwTrigFromCimEnable);
    /* set hardware trigger to channel mask loading enable or not */
    eTMR_SetHwTrig2Enable(etmrBase, param->hwTrigFromPadEnable);

    /* enable CHxVAL0 & CHxVAL1 register loading */
    for (uint32_t i = 0; i < TOTAL_CHAN; i++)
    {
        eTMR_SetChnLdEnable(etmrBase, i, true);
    }
    /* set register loading opportunity */
    eTMR_SetRegLoadOpportunity(etmrBase, param->regSyncSel);
    /* set counter initial loading opportunity */
    eTMR_SetCounterLoadOpportunity(etmrBase, param->cntInitSyncSel);
    /* set mask output loading opportunity */
    eTMR_SetMaskLoadOpportunity(etmrBase, param->maskOutputSyncSel);

    /* set register loading trigger source */
    eTMR_SetRegLoadTrigSrc(etmrBase, param->regSyncTrigSrc);
    /* set counter initial value loading trigger source */
    eTMR_SetCounterLoadTrigSrc(etmrBase, param->cntInitSyncTrigSrc);
    /* set mask output loading trigger source */
    eTMR_SetMaskLoadTrigSrc(etmrBase, param->maskOutputSyncTrigSrc);

    return retStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetSafeState
 * Description   : Set channel safe state when fault is detected.
 *
 * Implements    : eTMR_DRV_SetSafeState_Activity
 *END**************************************************************************/
status_t eTMR_DRV_SetSafeState(uint32_t instance, uint32_t safeState)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];
    status_t retStatus = STATUS_SUCCESS;

    eTMR_SetChnOutFaultVal(etmrBase, safeState);

    return retStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetOutputTrigger
 * Description   : This function configures output trigger
 *
 * Implements : eTMR_DRV_SetOutputTrigger_Activity
 *END**************************************************************************/
status_t eTMR_DRV_SetOutputTrigger(uint32_t instance, const etmr_trig_config_t *param)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(param != NULL);

    uint8_t index;
    eTMR_Type *etmrBase = g_etmrBase[instance];
    status_t retStatus = STATUS_SUCCESS;

    if (param != NULL)
    {
        if (param->trigSrc == TRIGGER_FROM_PWM)
        {
            /* select output trigger source */
            eTMR_SetOutTrigSrc(etmrBase, TRIGGER_FROM_PWM);

            /* select pwm output source of channel n */
            eTMR_SetPulseOutSrc(etmrBase, (etmr_channel_index_t)param->pwmOutputChannel);
        }
        else // TRIGGER_FROM_MATCHING_EVENT
        {
#if FEATURE_eTMR_HAS_OUTPUT_TRIGGER_WIDTH
            /* set output trigger width */
            eTMR_SetOutputTrigWidth(etmrBase, param->outputTrigWidth);
#endif

            /* set output trigger frequency */
            eTMR_SetOutputTrigFreq(etmrBase, param->outputTrigFreq);

            /* select output trigger source */
            eTMR_SetOutTrigSrc(etmrBase, TRIGGER_FROM_MATCHING_EVENT);

            /* enable mod matching event trigger */
            if (param->modMatchTrigEnable)
            {
                eTMR_SetModMatchTrigEnable(etmrBase, param->modMatchTrigEnable);
            }

#if FEATURE_eTMR_HAS_MID
            /* enable mid matching event trigger */
            if (param->midMatchTrigEnable)
            {
                eTMR_SetMidMatchTrigEnable(etmrBase, param->midMatchTrigEnable);
            }
#endif

#if FEATURE_eTMR_HAS_INIT_REG
            /* enable init matching event trigger */
            if (param->initMatchTrigEnable)
            {
                eTMR_SetInitMatchTrigEnable(etmrBase, param->initMatchTrigEnable);
            }
#endif

            if (param->channelTrigParamConfig != NULL)
            {
                for (index = 0; index < param->numOfChannels; index++)
                {
                    eTMR_IsChnVal0MatchTrigEnable(etmrBase,
                                                  param->channelTrigParamConfig[index].channelId,
                                                  param->channelTrigParamConfig[index].channelVal0MatchTrigEn);
                    eTMR_IsChnVal1MatchTrigEnable(etmrBase,
                                                  param->channelTrigParamConfig[index].channelId,
                                                  param->channelTrigParamConfig[index].channelVal1MatchTrigEn);
                }
            }
        }
    }

    return retStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_EnableInterrupts
 * Description   : This function will enable the generation a list of interrupts.
 * It includes the eTMR overflow interrupts, the reload point interrupt, the fault
 * interrupt and the channel (n) interrupt.
 *
 * Implements : eTMR_DRV_EnableInterrupts_Activity
 *END**************************************************************************/
status_t eTMR_DRV_EnableInterrupts(uint32_t instance, uint32_t interruptMask)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];
    uint32_t chnlInts = (interruptMask & 0x000000FFU);
    uint8_t channel = 0U;

    /* Enable the timer overflow interrupt */
    if ((interruptMask & (uint32_t)eTMR_TIME_OVER_FLOW_INT_ENABLE) != 0x0U)
    {
        eTMR_SetTofIntEnable(etmrBase, true);
        INT_SYS_EnableIRQ(g_etmrOverflowIrqId[instance]);
    }

    /* Enable the fault interrupt */
    if ((interruptMask & (uint32_t)eTMR_FAULT_INT_ENABLE) != 0x0U)
    {
        eTMR_SetFaultIntEnable(etmrBase, true);
        INT_SYS_EnableIRQ(g_etmrFaultIrqId[instance]);
    }

    /* Enable the channel interrupts */
    while (chnlInts != 0U)
    {
        if ((chnlInts & 0x1U) != 0x0U)
        {
            eTMR_DRV_EnableChnInt(instance, channel);
            INT_SYS_EnableIRQ(g_etmrIrqId[instance][channel]);
        }
        channel++;
        chnlInts = chnlInts >> 1U;
    }

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_DisableInterrupts
 * Description   : This function is used to disable some interrupts.
 *
 * Implements : eTMR_DRV_DisableInterrupts_Activity
 *END**************************************************************************/
void eTMR_DRV_DisableInterrupts(uint32_t instance, uint32_t interruptMask)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];
    uint32_t chnlInts = (interruptMask & 0x000000FFU);
    uint8_t channel = 0U;

    /* Disable the timer overflow interrupt */
    if ((interruptMask & (uint32_t)eTMR_TIME_OVER_FLOW_INT_ENABLE) != 0x0U)
    {
        eTMR_SetTofIntEnable(etmrBase, false);
        INT_SYS_DisableIRQ(g_etmrOverflowIrqId[instance]);
    }

    /* Disable the fault interrupt */
    if ((interruptMask & (uint32_t)eTMR_FAULT_INT_ENABLE) != 0x0U)
    {
        eTMR_SetFaultIntEnable(etmrBase, false);
        INT_SYS_DisableIRQ(g_etmrFaultIrqId[instance]);
    }

    /* Disable the channel interrupts */
    while (chnlInts != 0U)
    {
        if ((chnlInts & 0x1U) != 0x0U)
        {
            eTMR_DRV_DisableChnInt(instance, channel);
            INT_SYS_DisableIRQ(g_etmrIrqId[instance][channel]);
        }
        channel++;
        chnlInts = chnlInts >> 1U;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetEnabledInterrupts
 * Description   : This function will get the enabled eTMR interrupts.
 *
 * Implements : eTMR_DRV_GetEnabledInterrupts_Activity
 *END**************************************************************************/
uint32_t eTMR_DRV_GetEnabledInterrupts(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    uint32_t enabledInterrupts = 0U;
    uint8_t channel = g_etmrChannelNum[instance];

    /* Check if timer overflow interrupt is enabled */
    if (eTMR_DRV_IsTofIntEnabled(instance) == true)
    {
        enabledInterrupts |= (uint32_t)eTMR_TIME_OVER_FLOW_INT_ENABLE;
    }

    /* Check if fault interrupt is enabled */
    if (eTMR_DRV_IsFaultIntEnabled(instance) == true)
    {
        enabledInterrupts |= (uint32_t)eTMR_FAULT_INT_ENABLE;
    }

    /* Check if the channel interrupts are enabled */
    while (channel > 0U)
    {
        channel--;
        if (eTMR_DRV_IsChnIntEnabled(instance, channel) == true)
        {
            enabledInterrupts |= (1UL << (uint32_t)channel);
        }
    }

    return enabledInterrupts;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetStatusFlags
 * Description   : This function will get the eTMR status flags.
 *
 * Implements : eTMR_DRV_GetStatusFlags_Activity
 *END**************************************************************************/
uint32_t eTMR_DRV_GetStatusFlags(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    uint8_t channel;
    uint8_t fltChannel;
    uint32_t statusFlags = 0U;

    /* Check the timer overflow flag */
    if (eTMR_DRV_GetTofFlag(instance) == true)
    {
        statusFlags |= (uint32_t)eTMR_TIME_OVER_FLOW_FLAG;
    }

    /* Check reload flag */
    if (eTMR_DRV_GetReloadFlag(instance) == true)
    {
        statusFlags |= (uint32_t)eTMR_RELOAD_FLAG;
    }

    /* Check fault flag */
    for (fltChannel = 0U; fltChannel < (g_etmrChannelNum[instance] >> 1); fltChannel++)
    {
        if (eTMR_DRV_GetFaultFlag(instance, fltChannel) == true)
        {
            statusFlags |= (uint32_t)(eTMR_FAULT0_FLAG << fltChannel);
        }
    }

    /* Lower 8 bits contain the channel status flags */
    for (channel = 0U; channel < g_etmrChannelNum[instance]; channel++)
    {
        if (eTMR_DRV_GetChnFlag(instance, channel) == true)
        {
            statusFlags |= (1UL << (uint32_t)channel);
        }
    }

    return statusFlags;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetFrequency
 * Description   : Retrieves the frequency of the clock source feeding the eTMR counter.
 * Function will return a 0 if no clock source is selected and the eTMR counter is disabled.
 * The returned value is clock sources for the eTMR counter.
 *
 * Implements    : eTMR_DRV_GetFrequency_Activity
 *END**************************************************************************/
uint32_t eTMR_DRV_GetFrequency(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(etmrStatePtr[instance] != NULL);
    eTMR_Type const *etmrBase = g_etmrBase[instance];
    status_t returnCode = STATUS_SUCCESS;
    uint8_t clkPrs;
    uint32_t frequency = 0U;
    const etmr_state_t *state = etmrStatePtr[instance];
    clkPrs = (uint8_t)(eTMR_GetClkPrs(etmrBase) + 1U);

    switch (state->etmrClockSource)
    {
        case eTMR_CLOCK_SOURCE_INTERNALCLK:
            /* Get the clock frequency value */
            returnCode = CLOCK_SYS_GetFreq(eTMR_INTERNAL_CLOCK, &frequency);
            break;
        case eTMR_CLOCK_SOURCE_EXTERNALCLK:
            frequency = FEATURE_eTMR_EXTERNAL_CLOCK_FREQ;
            break;
        default:
            /* Nothing to do */
            break;
    }

    /* Checks the functional clock of eTMR module */
    (void)returnCode;
    DEV_ASSERT(returnCode == STATUS_SUCCESS);

    return (uint32_t)(frequency / clkPrs);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_ConvertFreqToPeriodTicks
 * Description   : This function converts the input parameters representing
 * frequency in Hz to a period value in ticks needed by the hardware timer.
 *
 * Implements    : eTMR_DRV_ConvertFreqToPeriodTicks_Activity
 *END**************************************************************************/
uint32_t eTMR_DRV_ConvertFreqToPeriodTicks(uint32_t instance, uint32_t freqencyHz)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(freqencyHz != 0U);
    uint32_t ueTMRhz;
    const etmr_state_t *state = etmrStatePtr[instance];
    ueTMRhz = state->etmrSourceClockFrequency;

    return (ueTMRhz / freqencyHz);
}

/*******************************************************************************
* EOF
******************************************************************************/
