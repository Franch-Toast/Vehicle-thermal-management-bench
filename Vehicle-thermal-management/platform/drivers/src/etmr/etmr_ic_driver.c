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
 * @file etmr_ic_driver.c
 */

#include "etmr_ic_driver.h"
#include "etmr_hw_access.h"
#include "interrupt_manager.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_IC_DRV_SetChannelMode
 * Description   : This function is used to set input capture mode and the input
 *                 detected edge mode.
 *
 * Implements    : eTMR_IC_DRV_SetChannelMode_Activity
 *END**************************************************************************/

void eTMR0_Ch0_Ch1_IRQHandler(void)
{
    for (uint8_t channel = 0; channel < 2; channel++)
    {
        eTMR_DRV_InputCaptureHandler(0, channel);
    }

    eTMR_DRV_ClearChnFlag(0, 1 << 0 | 1 << 1);
}

void eTMR0_Ch2_Ch3_IRQHandler(void)
{
    for (uint8_t channel = 2; channel < 4; channel++)
    {
        eTMR_DRV_InputCaptureHandler(0, channel);
    }
    eTMR_DRV_ClearChnFlag(0, 1 << 2 | 1 << 3);
}

void eTMR0_Ch4_Ch5_IRQHandler(void)
{
    for (uint8_t channel = 4; channel < 6; channel++)
    {
        eTMR_DRV_InputCaptureHandler(0, channel);
    }
    eTMR_DRV_ClearChnFlag(0, 1 << 4 | 1 << 5);
}

void eTMR0_Ch6_Ch7_IRQHandler(void)
{
    for (uint8_t channel = 6; channel < 8; channel++)
    {
        eTMR_DRV_InputCaptureHandler(0, channel);
    }
    eTMR_DRV_ClearChnFlag(0, 1 << 6 | 1 << 7);
}

void eTMR1_Ch0_Ch1_IRQHandler(void)
{
    for (uint8_t channel = 0; channel < 2; channel++)
    {
        eTMR_DRV_InputCaptureHandler(1, channel);
    }
    eTMR_DRV_ClearChnFlag(1, 1 << 0 | 1 << 1);
}

void eTMR1_Ch2_Ch3_IRQHandler(void)
{
    for (uint8_t channel = 2; channel < 4; channel++)
    {
        eTMR_DRV_InputCaptureHandler(1, channel);
    }
    eTMR_DRV_ClearChnFlag(1, 1 << 2 | 1 << 3);
}

void eTMR1_Ch4_Ch5_IRQHandler(void)
{
    for (uint8_t channel = 4; channel < 6; channel++)
    {
        eTMR_DRV_InputCaptureHandler(1, channel);
    }
    eTMR_DRV_ClearChnFlag(1, 1 << 4 | 1 << 5);
}

void eTMR1_Ch6_Ch7_IRQHandler(void)
{
    for (uint8_t channel = 6; channel < 8; channel++)
    {
        eTMR_DRV_InputCaptureHandler(1, channel);
    }
    eTMR_DRV_ClearChnFlag(1, 1 << 6 | 1 << 7);
}

#if eTMR_INSTANCE_COUNT > 2U
void eTMR2_Ch0_Ch1_IRQHandler(void)
{
    for (uint8_t channel = 0; channel < 2; channel++)
    {
        eTMR_DRV_InputCaptureHandler(2, channel);
    }
    eTMR_DRV_ClearChnFlag(2, 1 << 0 | 1 << 1);
}

void eTMR2_Ch2_Ch3_IRQHandler(void)
{
    for (uint8_t channel = 2; channel < 4; channel++)
    {
        eTMR_DRV_InputCaptureHandler(2, channel);
    }
    eTMR_DRV_ClearChnFlag(2, 1 << 2 | 1 << 3);
}

void eTMR2_Ch4_Ch5_IRQHandler(void)
{
    for (uint8_t channel = 4; channel < 6; channel++)
    {
        eTMR_DRV_InputCaptureHandler(2, channel);
    }
    eTMR_DRV_ClearChnFlag(2, 1 << 4 | 1 << 5);
}

void eTMR2_Ch6_Ch7_IRQHandler(void)
{
    for (uint8_t channel = 6; channel < 8; channel++)
    {
        eTMR_DRV_InputCaptureHandler(2, channel);
    }
    eTMR_DRV_ClearChnFlag(2, 1 << 6 | 1 << 7);
}
#endif

#if eTMR_INSTANCE_COUNT > 3U
void eTMR3_Ch0_Ch1_IRQHandler(void)
{
    for (uint8_t channel = 0; channel < 2; channel++)
    {
        eTMR_DRV_InputCaptureHandler(3, channel);
    }
    eTMR_DRV_ClearChnFlag(3, 1 << 0 | 1 << 1);
}

void eTMR3_Ch2_Ch3_IRQHandler(void)
{
    for (uint8_t channel = 2; channel < 4; channel++)
    {
        eTMR_DRV_InputCaptureHandler(3, channel);
    }
    eTMR_DRV_ClearChnFlag(3, 1 << 2 | 1 << 3);
}

void eTMR3_Ch4_Ch5_IRQHandler(void)
{
    for (uint8_t channel = 4; channel < 6; channel++)
    {
        eTMR_DRV_InputCaptureHandler(3, channel);
    }
    eTMR_DRV_ClearChnFlag(3, 1 << 4 | 1 << 5);
}

void eTMR3_Ch6_Ch7_IRQHandler(void)
{
    for (uint8_t channel = 6; channel < 8; channel++)
    {
        eTMR_DRV_InputCaptureHandler(3, channel);
    }
    eTMR_DRV_ClearChnFlag(3, 1 << 6 | 1 << 7);
}
#endif

#if eTMR_INSTANCE_COUNT > 4U
void eTMR4_Ch0_Ch1_IRQHandler(void)
{
    for (uint8_t channel = 0; channel < 2; channel++)
    {
        eTMR_DRV_InputCaptureHandler(4, channel);
    }
    eTMR_DRV_ClearChnFlag(4, 1 << 0 | 1 << 1);
}

void eTMR4_Ch2_Ch3_IRQHandler(void)
{
    for (uint8_t channel = 2; channel < 4; channel++)
    {
        eTMR_DRV_InputCaptureHandler(4, channel);
    }
    eTMR_DRV_ClearChnFlag(4, 1 << 2 | 1 << 3);
}

void eTMR4_Ch4_Ch5_IRQHandler(void)
{
    for (uint8_t channel = 4; channel < 6; channel++)
    {
        eTMR_DRV_InputCaptureHandler(4, channel);
    }
    eTMR_DRV_ClearChnFlag(4, 1 << 4 | 1 << 5);
}

void eTMR4_Ch6_Ch7_IRQHandler(void)
{
    for (uint8_t channel = 6; channel < 8; channel++)
    {
        eTMR_DRV_InputCaptureHandler(4, channel);
    }
    eTMR_DRV_ClearChnFlag(4, 1 << 6 | 1 << 7);
}
#endif

#if eTMR_INSTANCE_COUNT > 5U
void eTMR5_Ch0_Ch1_IRQHandler(void)
{
    for (uint8_t channel = 0; channel < 2; channel++)
    {
        eTMR_DRV_InputCaptureHandler(5, channel);
    }
    eTMR_DRV_ClearChnFlag(5, 1 << 0 | 1 << 1);
}

void eTMR5_Ch2_Ch3_IRQHandler(void)
{
    for (uint8_t channel = 2; channel < 4; channel++)
    {
        eTMR_DRV_InputCaptureHandler(5, channel);
    }
    eTMR_DRV_ClearChnFlag(5, 1 << 2 | 1 << 3);
}

void eTMR5_Ch4_Ch5_IRQHandler(void)
{
    for (uint8_t channel = 4; channel < 6; channel++)
    {
        eTMR_DRV_InputCaptureHandler(5, channel);
    }
    eTMR_DRV_ClearChnFlag(5, 1 << 4 | 1 << 5);
}

void eTMR5_Ch6_Ch7_IRQHandler(void)
{
    for (uint8_t channel = 6; channel < 8; channel++)
    {
        eTMR_DRV_InputCaptureHandler(5, channel);
    }
    eTMR_DRV_ClearChnFlag(5, 1 << 6 | 1 << 7);
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_InitInputCapture
 * Description   : This function initialize the channel in the Input Capture mode
 *
 * Implements    : eTMR_DRV_InitInputCapture_Activity
 *END**************************************************************************/
status_t eTMR_DRV_InitInputCapture(uint32_t instance, const etmr_ic_param_t *param)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(param != NULL);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    etmr_state_t *state = etmrStatePtr[instance];
    uint8_t index;
    uint8_t hwChannel;
    status_t status = STATUS_SUCCESS;

    if (NULL != state)
    {
#if FEATURE_eTMR_HAS_CNT_INIT_SRC
        eTMR_SetCounterInitValSrc(etmrBase, true);
#endif
#if FEATURE_eTMR_HAS_INIT_REG
        /* Set initial value for counter */
        eTMR_SetInitVal(etmrBase, 0U);
#endif
        /* Set maximum value for counter */
        eTMR_SetMod(etmrBase, param->countValue);
        /* Get current MOD value */
        state->etmrModValue = param->countValue;

#if FEATURE_eTMR_HAS_COMBINATION_CAPTURE_MODE
        for (index = 0U; index < (param->numChannelPairs); index++)
        {
            uint8_t hwChannelPair = param->inputChPairConfig[index].hwChannelPairId;
            eTMR_DRV_SetChnCombMode(instance, hwChannelPair, param->inputChPairConfig[index].combEn);
            eTMR_DRV_SetChnCombSrc(instance, hwChannelPair, param->inputChPairConfig[index].combSrc);
        }
#endif

        /* Initialize channel configuration */
        for (index = 0U; index < (param->numChannels); index++)
        {
            hwChannel = param->inputChConfig[index].hwChannelId;

            /* Set input capture mode for channel */
            eTMR_SetChnMode(etmrBase, hwChannel, eTMR_INPUT_CAPTURE_MODE);
            state->etmrChnMode[hwChannel] = eTMR_STATE_INPUT_CAPTURE;
            /* Set edge detection */
            eTMR_SetChnCapEdge(etmrBase, hwChannel, param->inputChConfig[index].edge);
            state->measurementType[hwChannel] = param->inputChConfig[index].measurementType;
#if FEATURE_eTMR_HAS_CAPTURE_HOLD
            /* Set capture hold feature */
            eTMR_SetChnCapHoldEnable(etmrBase, hwChannel, param->inputChConfig[index].capHoldEn);
#endif
            /* Set filter sample counter/period for input capture channel */
            eTMR_SetChnCapFilterSampleCounter(etmrBase, hwChannel, param->inputChConfig[index].filterSampleCounter);
            eTMR_SetChnCapFilterSamplePeriod(etmrBase, hwChannel, param->inputChConfig[index].filterSamplePeriod);
            /* Set DMA */
            if (param->inputChConfig[index].dmaEnable)
            {
                eTMR_SetChnDmaEnable(etmrBase, hwChannel, true);
            }


            if (param->inputChConfig[index].interruptEnable)
            {
#if defined(CPU_YTM32B1MC0)
                eTMR_DRV_EnableChnInt(instance, hwChannel);
#endif
                INT_SYS_EnableIRQ(g_etmrIrqId[instance][hwChannel]);
            }
            else
            {
                eTMR_DRV_DisableChnInt(instance, hwChannel);
                INT_SYS_DisableIRQ(g_etmrIrqId[instance][hwChannel]);
            }

            /* Save in state structure user define handlers */
            state->enableNotification[hwChannel] = param->inputChConfig[index].enableNotification;
            state->channelsCallbacksParams[hwChannel] = param->inputChConfig[index].channelsCallbacksParams;
            state->channelsCallbacks[hwChannel] = param->inputChConfig[index].channelsCallbacks;
        }
    }
    else /* state is NULL */
    {
        status = STATUS_ERROR;
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_DeinitInputCapture
 * Description   : This function de-initialize input capture mode and configure
 *                 channel as none mode
 *
 * Implements    : eTMR_DRV_DeinitInputCapture_Activity
 *END**************************************************************************/
status_t eTMR_DRV_DeinitInputCapture(uint32_t instance, const etmr_ic_param_t *param)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(param != NULL);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    etmr_state_t *state = etmrStatePtr[instance];
    DEV_ASSERT(state != NULL);
    uint8_t index;
    uint8_t hwChannel;

    /* Deinit channel configuration */
#if FEATURE_eTMR_HAS_COMBINATION_CAPTURE_MODE
    for (index = 0U; index < (param->numChannelPairs); index++)
    {
        uint8_t hwChannelPair = param->inputChPairConfig[index].hwChannelPairId;
        eTMR_DRV_SetChnCombMode(instance, hwChannelPair, false);
        eTMR_DRV_SetChnCombSrc(instance, hwChannelPair, eTMR_COMB_SRC_EVEN);
    }
#endif

    for (index = 0U; index < param->numChannels; index++)
    {
        hwChannel = param->inputChConfig[index].hwChannelId;

        /* Set channel mode as none */
        eTMR_SetChnMode(etmrBase, hwChannel, eTMR_CHANNEL_DISABLE);
        /* Set channel capture edge as none */
        eTMR_SetChnCapEdge(etmrBase, hwChannel, eTMR_NOT_SEL_EDGE);
        /* Disable channel interrupt */
        eTMR_DRV_DisableChnInt(instance, hwChannel);
        /* Clear channel event flags */
        eTMR_DRV_ClearChnFlag(instance, hwChannel);
#if !FEATURE_eTMR_HAS_COMBINATION_CAPTURE_MODE
        eTMR_DRV_ClearChnPosPulseRdyFlag(instance, hwChannel);
        eTMR_DRV_ClearChnNegPulseRdyFlag(instance, hwChannel);
#endif
#if FEATURE_eTMR_HAS_CAPTURE_HOLD
        eTMR_SetChnCapHoldEnable(etmrBase, hwChannel, false);
#endif
        /* Disable filter */
        eTMR_SetChnCapFilterSampleCounter(etmrBase, hwChannel, 0);
        eTMR_SetChnCapFilterSamplePeriod(etmrBase, hwChannel, 0);
        /* Disable DMA */
        eTMR_SetChnDmaEnable(etmrBase, hwChannel, false);
        /* Save etmr channel mode in state structure */
        state->etmrChnMode[hwChannel] = eTMR_STATE_NO_MODE;
        /* Clear Callbacks function from the state structure */
        state->enableNotification[index] = false;
        state->channelsCallbacksParams[index] = NULL;
        state->channelsCallbacks[index] = NULL;
    }

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetInputCapturePositivePulseCount
 * Description   : This function is used to get positive pulse count value.
 *
 * Implements    : eTMR_DRV_GetInputCapturePositivePulseCount_Activity
 *END**************************************************************************/
uint32_t eTMR_DRV_GetInputCapturePositivePulseCount(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);
    const etmr_state_t *state = etmrStatePtr[instance];
    uint32_t value = 0;

    if (state != NULL)
    {
        value = state->measurementPosPulseCnt[channel];
    }

    return value;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetInputCaptureNegativePulseCount
 * Description   : This function is used to get negative pulse count value.
 *
 * Implements    : eTMR_DRV_GetInputCaptureNegativePulseCount_Activity
 *END**************************************************************************/
uint32_t eTMR_DRV_GetInputCaptureNegativePulseCount(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);
    const etmr_state_t *state = etmrStatePtr[instance];
    uint32_t value = 0;

    if (state != NULL)
    {
        value = state->measurementNegPulseCnt[channel];
    }

    return value;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetInputCaptureComplete
 * Description   : This function is used to get complete status.
 *
 * Implements    : eTMR_DRV_GetInputCaptureComplete_Activity
 *END**************************************************************************/
bool eTMR_DRV_GetInputCaptureComplete(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);
    etmr_state_t *state = etmrStatePtr[instance];
    uint8_t value = 0U;

    if (state != NULL)
    {
        value = state->measurementComplete[channel];
    }

    return value;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_ClearInputCaptureComplete
 * Description   : This function is used to clear complete status.
 *
 * Implements    : eTMR_DRV_ClearInputCaptureComplete_Activity
 *END**************************************************************************/
status_t eTMR_DRV_ClearInputCaptureComplete(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);
    etmr_state_t *state = etmrStatePtr[instance];

    if (state != NULL)
    {
        state->measurementComplete[channel] = 0;
    }

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_InputCaptureHandler
 * Description   : This function is used to calculate measurement for input capture.
 *
 * Implements    : eTMR_DRV_InputCaptureHandler_Activity
 *END**************************************************************************/
#if !FEATURE_eTMR_HAS_COMBINATION_CAPTURE_MODE
void eTMR_DRV_InputCaptureHandler(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);

    eTMR_Type *etmrBase = g_etmrBase[instance];
    etmr_state_t *state = etmrStatePtr[instance];
    DEV_ASSERT(state->captureEdge[channel] == eTMR_DUAL_EDGES);

    if (state->measurementType[channel] == eTMR_PERIOD_MEASUREMENT)
    {
        /* Get positive and negative pulse counts */
        if (eTMR_DRV_GetChnPosPulseRdyFlag(instance, channel) == true &&
            eTMR_DRV_GetChnNegPulseRdyFlag(instance, channel) == true)
        {
            state->measurementPosPulseCnt[channel] = eTMR_GetChnPosPulseWidthCapVal(etmrBase, channel) +
                                                     eTMR_GetChnPosPulseCntPeriodNum(etmrBase, channel) * state->etmrModValue;
            state->measurementNegPulseCnt[channel] = eTMR_GetChnNegPulseWidthCapVal(etmrBase, channel) +
                                                     eTMR_GetChnNegPulseCntPeriodNum(etmrBase, channel) * state->etmrModValue;
            eTMR_DRV_ClearChnNegPulseRdyFlag(instance, channel);
            eTMR_DRV_ClearChnPosPulseRdyFlag(instance, channel);
            state->measurementComplete[channel] = true;
        }
    }
    else if (state->measurementType[channel] == eTMR_POS_PULSE_MEASUREMENT)
    {
        if (eTMR_DRV_GetChnPosPulseRdyFlag(instance, channel) == true)
        {
            state->measurementPosPulseCnt[channel] = eTMR_GetChnPosPulseWidthCapVal(etmrBase, channel) +
                                                     eTMR_GetChnPosPulseCntPeriodNum(etmrBase, channel) * state->etmrModValue;
            eTMR_DRV_ClearChnPosPulseRdyFlag(instance, channel);
            state->measurementComplete[channel] = true;
        }
    }
    else // eTMR_NEG_PULSE_MEASUREMENT
    {
        if (eTMR_DRV_GetChnNegPulseRdyFlag(instance, channel) == true)
        {
            state->measurementNegPulseCnt[channel] = eTMR_GetChnNegPulseWidthCapVal(etmrBase, channel) +
                                                     eTMR_GetChnNegPulseCntPeriodNum(etmrBase, channel) * state->etmrModValue;
            eTMR_DRV_ClearChnNegPulseRdyFlag(instance, channel);
            state->measurementComplete[channel] = true;
        }
    }

    /* If the callback is defined to use it */
    if ((state->channelsCallbacks[channel] != NULL) && (state->enableNotification[channel] == true))
    {
        state->channelsCallbacks[channel](IC_EVENT_MEASUREMENT_COMPLETE, state->channelsCallbacksParams[channel]);
    }
}
#endif

/*******************************************************************************
* EOF
******************************************************************************/
