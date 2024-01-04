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
 * @file etmr_hal.c
 */

#include "etmr_hw_access.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_Reset
 * Description   : Resets the eTMR registers. All the register use in the driver should be
 * reset to default value of each register.
 *
 * Implements    : eTMR_DRV_Reset_Activity
 *END**************************************************************************/
void eTMR_DRV_Reset(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    IPC->CTRL[instance + IPC_eTMR0_INDEX] |= IPC_CTRL_SWREN_MASK;
    IPC->CTRL[instance + IPC_eTMR0_INDEX] &= ~IPC_CTRL_SWREN_MASK;
}

/******************************************** STS Register **************************************************/
#if !FEATURE_eTMR_HAS_COMBINATION_CAPTURE_MODE
/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetChnNegPulseRdyFlag
 * Description   : Get channel negative pulse ready flag
 *
 * Implements    : eTMR_DRV_GetChnNegPulseRdyFlag_Activity
 *END**************************************************************************/
bool eTMR_DRV_GetChnNegPulseRdyFlag(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    bool retVal = false;

    switch (channel)
    {
        case 0:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH0NPF_MASK) >> eTMR_STS_CH0NPF_SHIFT);
            break;
        case 1:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH1NPF_MASK) >> eTMR_STS_CH1NPF_SHIFT);
            break;
        case 2:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH2NPF_MASK) >> eTMR_STS_CH2NPF_SHIFT);
            break;
        case 3:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH3NPF_MASK) >> eTMR_STS_CH3NPF_SHIFT);
            break;
        case 4:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH4NPF_MASK) >> eTMR_STS_CH4NPF_SHIFT);
            break;
        case 5:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH5NPF_MASK) >> eTMR_STS_CH5NPF_SHIFT);
            break;
        case 6:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH6NPF_MASK) >> eTMR_STS_CH6NPF_SHIFT);
            break;
        case 7:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH7NPF_MASK) >> eTMR_STS_CH7NPF_SHIFT);
            break;
        default:
            break;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetChnPosPulseRdyFlag
 * Description   : Get the channel positive pulse ready flag
 *
 * Implements    : eTMR_DRV_GetChnPosPulseRdyFlag_Activity
 *END**************************************************************************/
bool eTMR_DRV_GetChnPosPulseRdyFlag(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];

    bool retVal = false;

    switch (channel)
    {
        case 0:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH0PPF_MASK) >> eTMR_STS_CH0PPF_SHIFT);
            break;
        case 1:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH1PPF_MASK) >> eTMR_STS_CH1PPF_SHIFT);
            break;
        case 2:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH2PPF_MASK) >> eTMR_STS_CH2PPF_SHIFT);
            break;
        case 3:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH3PPF_MASK) >> eTMR_STS_CH3PPF_SHIFT);
            break;
        case 4:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH4PPF_MASK) >> eTMR_STS_CH4PPF_SHIFT);
            break;
        case 5:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH5PPF_MASK) >> eTMR_STS_CH5PPF_SHIFT);
            break;
        case 6:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH6PPF_MASK) >> eTMR_STS_CH6PPF_SHIFT);
            break;
        case 7:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH7PPF_MASK) >> eTMR_STS_CH7PPF_SHIFT);
            break;
        default:
            break;
    }

    return retVal;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetQuadDecodeDir
 * Description   : Get quadrature decoder direction
 *
 * Implements    : eTMR_DRV_GetQuadDecodeDir_Activity
 *END**************************************************************************/
bool eTMR_DRV_GetQuadDecodeDir(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    return (bool)(((etmrBase->STS) & eTMR_STS_QDDIR_MASK) >> eTMR_STS_QDDIR_SHIFT);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetQuadDecodeTofFlag
 * Description   : Get quadrature decoder counter overflow flag
 *
 * Implements    : eTMR_DRV_GetQuadDecodeTofFlag_Activity
 *END**************************************************************************/
bool eTMR_DRV_GetQuadDecodeTofFlag(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    return (bool)(((etmrBase->STS) & eTMR_STS_QDTOF_MASK) >> eTMR_STS_QDTOF_SHIFT);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetTofFlag
 * Description   : Get eTMR counter overflow flag
 *
 * Implements    : eTMR_DRV_GetTofFlag_Activity
 *END**************************************************************************/
bool eTMR_DRV_GetTofFlag(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    return (bool)(((etmrBase->STS) & eTMR_STS_TOF_MASK) >> eTMR_STS_TOF_SHIFT);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetReloadFlag
 * Description   : Get eTMR reload flag
 *
 * Implements    : eTMR_DRV_GetReloadFlag_Activity
 *END**************************************************************************/
bool eTMR_DRV_GetReloadFlag(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    return (bool)(((etmrBase->STS) & eTMR_STS_RF_MASK) >> eTMR_STS_RF_SHIFT);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetFaultFlag
 * Description   : Get eTMR fault channel flag
 *
 * Implements    : eTMR_DRV_GetFaultFlag_Activity
 *END**************************************************************************/
bool eTMR_DRV_GetFaultFlag(uint32_t instance, uint8_t fltChannel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    DEV_ASSERT(fltChannel < (FEATURE_eTMR_CHANNEL_MAX_COUNT >> 1));
    bool retVal = true;

    switch (fltChannel)
    {
        case 0:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_F0F_MASK) >> eTMR_STS_F0F_SHIFT);
            break;
        case 1:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_F1F_MASK) >> eTMR_STS_F1F_SHIFT);
            break;
        case 2:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_F2F_MASK) >> eTMR_STS_F2F_SHIFT);
            break;
        case 3:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_F3F_MASK) >> eTMR_STS_F3F_SHIFT);
            break;
        default:
            break;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetChnFlag
 * Description   : Get eTMR channel interrupt flag
 *
 * Implements    : eTMR_DRV_GetChnFlag_Activity
 *END**************************************************************************/
bool eTMR_DRV_GetChnFlag(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);
    bool retVal = true;

    switch (channel)
    {
        case 0:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH0F_MASK) >> eTMR_STS_CH0F_SHIFT);
            break;
        case 1:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH1F_MASK) >> eTMR_STS_CH1F_SHIFT);
            break;
        case 2:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH2F_MASK) >> eTMR_STS_CH2F_SHIFT);
            break;
        case 3:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH3F_MASK) >> eTMR_STS_CH3F_SHIFT);
            break;
        case 4:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH4F_MASK) >> eTMR_STS_CH4F_SHIFT);
            break;
        case 5:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH5F_MASK) >> eTMR_STS_CH5F_SHIFT);
            break;
        case 6:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH6F_MASK) >> eTMR_STS_CH6F_SHIFT);
            break;
        case 7:
            retVal = (bool)(((etmrBase->STS) & eTMR_STS_CH7F_MASK) >> eTMR_STS_CH7F_SHIFT);
            break;
        default:
            break;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_ClearChnNegPulseRdyFlag
 * Description   : Clear channel negative pulse ready flag
 *
 * Implements    : eTMR_DRV_ClearChnNegPulseRdyFlag_Activity
 *END**************************************************************************/
#if !FEATURE_eTMR_HAS_COMBINATION_CAPTURE_MODE
void eTMR_DRV_ClearChnNegPulseRdyFlag(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);

    switch (channel)
    {
        case 0:
            etmrBase->STS = eTMR_STS_CH0NPF_MASK;
            break;
        case 1:
            etmrBase->STS = eTMR_STS_CH1NPF_MASK;
            break;
        case 2:
            etmrBase->STS = eTMR_STS_CH2NPF_MASK;
            break;
        case 3:
            etmrBase->STS = eTMR_STS_CH3NPF_MASK;
            break;
        case 4:
            etmrBase->STS = eTMR_STS_CH4NPF_MASK;
            break;
        case 5:
            etmrBase->STS = eTMR_STS_CH5NPF_MASK;
            break;
        case 6:
            etmrBase->STS = eTMR_STS_CH6NPF_MASK;
            break;
        case 7:
            etmrBase->STS = eTMR_STS_CH7NPF_MASK;
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_ClearChnPosPulseRdyFlag
 * Description   : Clear channel positive pulse ready flag
 *
 * Implements    : eTMR_DRV_ClearChnPosPulseRdyFlag_Activity
 *END**************************************************************************/
void eTMR_DRV_ClearChnPosPulseRdyFlag(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);

    switch (channel)
    {
        case 0:
            etmrBase->STS = eTMR_STS_CH0PPF_MASK;
            break;
        case 1:
            etmrBase->STS = eTMR_STS_CH1PPF_MASK;
            break;
        case 2:
            etmrBase->STS = eTMR_STS_CH2PPF_MASK;
            break;
        case 3:
            etmrBase->STS = eTMR_STS_CH3PPF_MASK;
            break;
        case 4:
            etmrBase->STS = eTMR_STS_CH4PPF_MASK;
            break;
        case 5:
            etmrBase->STS = eTMR_STS_CH5PPF_MASK;
            break;
        case 6:
            etmrBase->STS = eTMR_STS_CH6PPF_MASK;
            break;
        case 7:
            etmrBase->STS = eTMR_STS_CH7PPF_MASK;
            break;
        default:
            break;
    }
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_ClearQuadDecodeTofFlag
 * Description   : Clear quadrature decoder counter overflow flag
 *
 * Implements    : eTMR_DRV_ClearQuadDecodeTofFlag_Activity
 *END**************************************************************************/
void eTMR_DRV_ClearQuadDecodeTofFlag(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    etmrBase->STS = eTMR_STS_QDTOF_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_ClearTofFlag
 * Description   : Clear eTMR counter overflow flag
 *
 * Implements    : eTMR_DRV_ClearTofFlag_Activity
 *END**************************************************************************/
void eTMR_DRV_ClearTofFlag(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    etmrBase->STS = eTMR_STS_TOF_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_ClearReloadFlag
 * Description   : Clear eTMR reload flag
 *
 * Implements    : eTMR_DRV_ClearReloadFlag_Activity
 *END**************************************************************************/
void eTMR_DRV_ClearReloadFlag(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    etmrBase->STS = eTMR_STS_RF_MASK;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_ClearFaultFlag
 * Description   : Clear fault channel flag
 *
 * Implements    : eTMR_DRV_ClearFaultFlag_Activity
 *END**************************************************************************/
void eTMR_DRV_ClearFaultFlag(uint32_t instance, uint8_t fltChannel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(fltChannel < FEATURE_eTMR_FAULT_CHANNELS);
    eTMR_Type *const etmrBase = g_etmrBase[instance];

    switch (fltChannel)
    {
        case 0:
            etmrBase->STS = eTMR_STS_F0F_MASK;
            break;
        case 1:
            etmrBase->STS = eTMR_STS_F1F_MASK;
            break;
        case 2:
            etmrBase->STS = eTMR_STS_F2F_MASK;
            break;
        case 3:
            etmrBase->STS = eTMR_STS_F3F_MASK;
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_ClearChnFlag
 * Description   : Clear channel interrupt flag
 *
 * Implements    : eTMR_DRV_ClearChnFlag_Activity
 *END**************************************************************************/
void eTMR_DRV_ClearChnFlag(uint32_t instance, uint8_t channelSet)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *const etmrBase = g_etmrBase[instance];

    etmrBase->STS = channelSet << eTMR_STS_CH0F_SHIFT;
}

/******************************************** IOSTS Register **************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetPhaseBStatus
 * Description   : Get status of phase B in quadrature decode mode
 *
 * Implements    : eTMR_DRV_GetPhaseBStatus_Activity
 *END**************************************************************************/
uint8_t eTMR_DRV_GetPhaseBStatus(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    return (uint8_t)(((etmrBase->IOSTS) & eTMR_IOSTS_PHB_MASK) >> eTMR_IOSTS_PHB_SHIFT);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetPhaseAStatus
 * Description   : Get status of phase A in quadrature decode mode
 *
 * Implements    : eTMR_DRV_GetPhaseAStatus_Activity
 *END**************************************************************************/
uint8_t eTMR_DRV_GetPhaseAStatus(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    return (uint8_t)(((etmrBase->IOSTS) & eTMR_IOSTS_PHA_MASK) >> eTMR_IOSTS_PHA_SHIFT);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetFaultInputStatus
 * Description   : Get the fault input status(polarity)
 *
 * Implements    : eTMR_DRV_GetFaultInputStatus_Activity
 *END**************************************************************************/
uint8_t eTMR_DRV_GetFaultInputStatus(uint32_t instance, uint8_t fltChannel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(fltChannel < FEATURE_eTMR_FAULT_CHANNELS);
    eTMR_Type *const etmrBase = g_etmrBase[instance];
    uint8_t retVal = 0;

    switch (fltChannel)
    {
        case 0:
            retVal = (bool)(((etmrBase->IOSTS) & eTMR_IOSTS_F0_MASK) >> eTMR_IOSTS_F0_SHIFT);
            break;
        case 1:
            retVal = (bool)(((etmrBase->IOSTS) & eTMR_IOSTS_F1_MASK) >> eTMR_IOSTS_F1_SHIFT);
            break;
        case 2:
            retVal = (bool)(((etmrBase->IOSTS) & eTMR_IOSTS_F2_MASK) >> eTMR_IOSTS_F2_SHIFT);
            break;
        case 3:
            retVal = (bool)(((etmrBase->IOSTS) & eTMR_IOSTS_F3_MASK) >> eTMR_IOSTS_F3_SHIFT);
            break;
        default:
            break;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetChnIoStatus
 * Description   : Get eTMR channel IO status in pwm, output compare and input
 *                 capture mode.
 *
 * Implements    : eTMR_DRV_GetChnIoStatus_Activity
 *END**************************************************************************/
uint8_t eTMR_DRV_GetChnIoStatus(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    return ((etmrBase->IOSTS >> channel) & eTMR_IOSTS_CH0IO_MASK);
}

/******************************************** CTRL Register **************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetChnCompMode
 * Description   : Set channel as complementary mode
 *
 * Implements    : eTMR_DRV_SetChnCompMode_Activity
 *END**************************************************************************/
void eTMR_DRV_SetChnCompMode(uint32_t instance, uint8_t channelPair, etmr_pwm_mode_t mode)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channelPair < (FEATURE_eTMR_CHANNEL_MAX_COUNT >> 1));
    eTMR_Type *etmrBase = g_etmrBase[instance];

    switch (channelPair)
    {
        case 0:
            eTMR_SetCh01CompMode(etmrBase, mode);
            break;
        case 1:
            eTMR_SetCh23CompMode(etmrBase, mode);
            break;
        case 2:
            eTMR_SetCh45CompMode(etmrBase, mode);
            break;
        case 3:
            eTMR_SetCh67CompMode(etmrBase, mode);
            break;
        default:
            break;
    }
}

#if FEATURE_eTMR_HAS_DOUBLE_SWITCH
/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetChnDoubleSwitch
 * Description   : Set channel as double switch mode
 *
 * Implements    : eTMR_DRV_SetChnDoubleSwitch_Activity
 *END**************************************************************************/
void eTMR_DRV_SetChnDoubleSwitch(uint32_t instance, uint8_t channelPair, bool en)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channelPair < (FEATURE_eTMR_CHANNEL_MAX_COUNT >> 1));
    eTMR_Type *etmrBase = g_etmrBase[instance];

    switch (channelPair)
    {
        case 0:
            eTMR_SetCh01DoubleSwitch(etmrBase, en);
            break;
        case 1:
            eTMR_SetCh23DoubleSwitch(etmrBase, en);
            break;
        case 2:
            eTMR_SetCh45DoubleSwitch(etmrBase, en);
            break;
        case 3:
            eTMR_SetCh67DoubleSwitch(etmrBase, en);
            break;
        default:
            break;
    }
}
#endif

#if FEATURE_eTMR_HAS_COMBINATION_CAPTURE_MODE
/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetChnCombMode
 * Description   : Set channel as combination capture mode
 *
 * Implements    : eTMR_DRV_SetChnCombMode_Activity
 *END**************************************************************************/
void eTMR_DRV_SetChnCombMode(uint32_t instance, uint8_t channelPair, bool en)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channelPair < (FEATURE_eTMR_CHANNEL_MAX_COUNT >> 1));
    eTMR_Type *etmrBase = g_etmrBase[instance];

    switch (channelPair)
    {
        case 0:
            eTMR_SetCh01CombMode(etmrBase, en);
            break;
        case 1:
            eTMR_SetCh23CombMode(etmrBase, en);
            break;
        case 2:
            eTMR_SetCh45CombMode(etmrBase, en);
            break;
        case 3:
            eTMR_SetCh67CombMode(etmrBase, en);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetChnCombSrc
 * Description   : Set channel as combination capture source
 *
 * Implements    : eTMR_DRV_SetChnCombSrc_Activity
 *END**************************************************************************/
void eTMR_DRV_SetChnCombSrc(uint32_t instance, uint8_t channelPair, uint8_t src)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channelPair < (FEATURE_eTMR_CHANNEL_MAX_COUNT >> 1));
    eTMR_Type *etmrBase = g_etmrBase[instance];

    switch (channelPair)
    {
        case 0:
            eTMR_SetCh01CombSrc(etmrBase, src);
            break;
        case 1:
            eTMR_SetCh23CombSrc(etmrBase, src);
            break;
        case 2:
            eTMR_SetCh45CombSrc(etmrBase, src);
            break;
        case 3:
            eTMR_SetCh67CombSrc(etmrBase, src);
            break;
        default:
            break;
    }
}
#endif
/******************************************** FAULT Register **************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetFaultChnPol
 * Description   : Set fault channel input polarity
 *
 * Implements    : eTMR_DRV_SetFaultChnPol_Activity
 *END**************************************************************************/
void eTMR_DRV_SetFaultChnPol(uint32_t instance, uint8_t fltChannel, bool pol)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(fltChannel < FEATURE_eTMR_FAULT_CHANNELS);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    switch (fltChannel)
    {
        case 0:
            eTMR_IsInvertFault0InputPol(etmrBase, pol);
            break;
        case 1:
            eTMR_IsInvertFault1InputPol(etmrBase, pol);
            break;
        case 2:
            eTMR_IsInvertFault2InputPol(etmrBase, pol);
            break;
        case 3:
            eTMR_IsInvertFault3InputPol(etmrBase, pol);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetFaultChnEnable
 * Description   : Set fault channel interrupt enable or not
 *
 * Implements    : eTMR_DRV_SetFaultChnEnable_Activity
 *END**************************************************************************/
void eTMR_DRV_SetFaultChnEnable(uint32_t instance, uint8_t fltChannel, bool enable)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(fltChannel < FEATURE_eTMR_FAULT_CHANNELS);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    switch (fltChannel)
    {
        case 0:
            eTMR_IsFault0Enable(etmrBase, enable);
            break;
        case 1:
            eTMR_IsFault1Enable(etmrBase, enable);
            break;
        case 2:
            eTMR_IsFault2Enable(etmrBase, enable);
            break;
        case 3:
            eTMR_IsFault3Enable(etmrBase, enable);
            break;
        default:
            break;
    }
}

/******************************************** INTE Register **************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_EnableQuadDecodeTofInt
 * Description   : Enable quadrature decoder counter overflow interrupt.
 *
 * Implements    : eTMR_DRV_EnableQdTofInt_Activity
 *END**************************************************************************/
void eTMR_DRV_EnableQuadDecodeTofInt(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    eTMR_SetQdTofIntEnable(etmrBase, true);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_DisableQuadDecodeTofInt
 * Description   : Disable quadrature decoder counter overflow interrupt
 *
 * Implements    : eTMR_DRV_DisableQuadDecodeTofInt_Activity
 *END**************************************************************************/
void eTMR_DRV_DisableQuadDecodeTofInt(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    eTMR_SetQdTofIntEnable(etmrBase, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_EnableTofInt
 * Description   : Enable eTMR overflow interrupt
 *
 * Implements    : eTMR_DRV_EnableTofInt_Activity
 *END**************************************************************************/
void eTMR_DRV_EnableTofInt(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    eTMR_SetTofIntEnable(etmrBase, true);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_DisableTofInt
 * Description   : Disable eTMR overflow interrupt
 *
 * Implements    : eTMR_DRV_DisableTofInt_Activity
 *END**************************************************************************/
void eTMR_DRV_DisableTofInt(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    eTMR_SetTofIntEnable(etmrBase, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_EnableChnInt
 * Description   : Enable specified channel interrupt.
 *
 * Implements    : eTMR_DRV_EnableChnInt_Activity
 *END**************************************************************************/
void eTMR_DRV_EnableChnInt(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    switch (channel)
    {
        case 0:
            eTMR_SetCh0IntEnable(etmrBase, true);
            break;
        case 1:
            eTMR_SetCh1IntEnable(etmrBase, true);
            break;
        case 2:
            eTMR_SetCh2IntEnable(etmrBase, true);
            break;
        case 3:
            eTMR_SetCh3IntEnable(etmrBase, true);
            break;
        case 4:
            eTMR_SetCh4IntEnable(etmrBase, true);
            break;
        case 5:
            eTMR_SetCh5IntEnable(etmrBase, true);
            break;
        case 6:
            eTMR_SetCh6IntEnable(etmrBase, true);
            break;
        case 7:
            eTMR_SetCh7IntEnable(etmrBase, true);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetChnsetIntEnable
 * Description   : Enable channel set interrupt.
 *
 * Implements    : eTMR_DRV_SetChnsetIntEnable_Activity
 *END**************************************************************************/
void eTMR_DRV_SetChnsetIntEnable(uint32_t instance, uint8_t channelSet)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    etmrBase->INTE |= channelSet << eTMR_INTE_CH0IE_SHIFT;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_DisableChnInt
 * Description   : Disable specified channel interrupt.
 *
 * Implements    : eTMR_DRV_DisableChnInt_Activity
 *END**************************************************************************/
void eTMR_DRV_DisableChnInt(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];
    switch (channel)
    {
        case 0:
            eTMR_SetCh0IntEnable(etmrBase, false);
            break;
        case 1:
            eTMR_SetCh1IntEnable(etmrBase, false);
            break;
        case 2:
            eTMR_SetCh2IntEnable(etmrBase, false);
            break;
        case 3:
            eTMR_SetCh3IntEnable(etmrBase, false);
            break;
        case 4:
            eTMR_SetCh4IntEnable(etmrBase, false);
            break;
        case 5:
            eTMR_SetCh5IntEnable(etmrBase, false);
            break;
        case 6:
            eTMR_SetCh6IntEnable(etmrBase, false);
            break;
        case 7:
            eTMR_SetCh7IntEnable(etmrBase, false);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_SetChnsetIntDisable
 * Description   : Disable channel set interrupt.
 *
 * Implements    : eTMR_DRV_SetChnsetIntDisable_Activity
 *END**************************************************************************/
void eTMR_DRV_SetChnsetIntDisable(uint32_t instance, uint8_t channelSet)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];

    etmrBase->INTE &= ~channelSet << eTMR_INTE_CH0IE_SHIFT;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_IsTofIntEnabled
 * Description   : Get if counter overflow interrupt is enabled or not.
 *
 * Implements    : eTMR_DRV_IsTofIntEnabled_Activity
 *END**************************************************************************/
bool eTMR_DRV_IsTofIntEnabled(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];
    bool retVal;

    retVal = (bool)(((etmrBase->INTE) & eTMR_INTE_TOIE_MASK) >> eTMR_INTE_TOIE_SHIFT);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_IsQuadDecodeTofIntEnabled
 * Description   : Get if quadrature decoder counter overflow interrupt is enabled or not.
 *
 * Implements    : eTMR_DRV_IsQdTofIntEnabled_Activity
 *END**************************************************************************/
bool eTMR_DRV_IsQuadDecodeTofIntEnabled(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];
    bool retVal;

    retVal = (bool)(((etmrBase->INTE) & eTMR_INTE_QDTOIE_MASK) >> eTMR_INTE_QDTOIE_SHIFT);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_IsFaultIntEnabled
 * Description   : Get if fault interrupt is enabled or not.
 *
 * Implements    : eTMR_DRV_IsFaultIntEnabled_Activity
 *END**************************************************************************/
bool eTMR_DRV_IsFaultIntEnabled(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];
    bool retVal;

    retVal = (bool)(((etmrBase->INTE) & eTMR_INTE_FIE_MASK) >> eTMR_INTE_FIE_SHIFT);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_IsChnIntEnabled
 * Description   : Get if the channel interrupt is enabled or not.
 *
 * Implements    : eTMR_DRV_IsChnIntEnabled_Activity
 *END**************************************************************************/
bool eTMR_DRV_IsChnIntEnabled(uint32_t instance, uint8_t channel)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    DEV_ASSERT(channel < FEATURE_eTMR_CHANNEL_MAX_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];
    bool retVal;

    switch (channel)
    {
        case 0:
            retVal = (bool)(((etmrBase->INTE) & eTMR_INTE_CH0IE_MASK) >> eTMR_INTE_CH0IE_SHIFT);
            break;
        case 1:
            retVal = (bool)(((etmrBase->INTE) & eTMR_INTE_CH1IE_MASK) >> eTMR_INTE_CH1IE_SHIFT);
            break;
        case 2:
            retVal = (bool)(((etmrBase->INTE) & eTMR_INTE_CH2IE_MASK) >> eTMR_INTE_CH2IE_SHIFT);
            break;
        case 3:
            retVal = (bool)(((etmrBase->INTE) & eTMR_INTE_CH3IE_MASK) >> eTMR_INTE_CH3IE_SHIFT);
            break;
        case 4:
            retVal = (bool)(((etmrBase->INTE) & eTMR_INTE_CH4IE_MASK) >> eTMR_INTE_CH4IE_SHIFT);
            break;
        case 5:
            retVal = (bool)(((etmrBase->INTE) & eTMR_INTE_CH5IE_MASK) >> eTMR_INTE_CH5IE_SHIFT);
            break;
        case 6:
            retVal = (bool)(((etmrBase->INTE) & eTMR_INTE_CH6IE_MASK) >> eTMR_INTE_CH6IE_SHIFT);
            break;
        case 7:
            retVal = (bool)(((etmrBase->INTE) & eTMR_INTE_CH7IE_MASK) >> eTMR_INTE_CH7IE_SHIFT);
            break;
        default:
            retVal = false;
            break;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : eTMR_DRV_GetCntVal
 * Description   : Get eTMR current counter value.
 *
 * Implements    : eTMR_DRV_GetCntVal_Activity
 *END**************************************************************************/
uint32_t eTMR_DRV_GetCntVal(uint32_t instance)
{
    DEV_ASSERT(instance < eTMR_INSTANCE_COUNT);
    eTMR_Type *etmrBase = g_etmrBase[instance];
    uint32_t retVal;

    retVal = eTMR_GetCntVal(etmrBase);

    return retVal;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
