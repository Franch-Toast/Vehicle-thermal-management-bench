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
 * @file dma_hw_access.c
 */

#include "dma_hw_access.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_Init
 * Description   : Initializes DMA module to known state.
 *END**************************************************************************/
void DMA_Init(DMA_Type *base)
{
    uint8_t i;
    /* Clear the bit of CR register */
    uint32_t regValTemp;
    regValTemp = base->CTRL;
    regValTemp &= ~(DMA_CTRL_CLM_MASK);
    regValTemp &= ~(DMA_CTRL_CX_MASK);
    regValTemp &= ~(DMA_CTRL_ECX_MASK);
    regValTemp &= ~(DMA_CTRL_DBGDIS_MASK);
    regValTemp &= ~(DMA_CTRL_LOEN_MASK);
    base->CTRL = regValTemp;
    for (i = 0; i < FEATURE_DMA_CHANNELS; i++)
    {
        DMA_CTSClearReg(base, i);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_CancelTransfer
 * Description   : Cancels the remaining data transfer.
 *END**************************************************************************/
void DMA_CancelTransfer(DMA_Type *base)
{
    uint32_t regValTemp;
    regValTemp = base->CTRL;
    regValTemp &= ~(DMA_CTRL_CX_MASK);
    regValTemp |= DMA_CTRL_CX(1U);
    base->CTRL = regValTemp;
    while (((base->CTRL & DMA_CTRL_CX_MASK) >> DMA_CTRL_CX_SHIFT) != 0UL)
    {}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_CancelTransferWithError
 * Description   : Cancels the remaining data transfer and treat it as error.
 *END**************************************************************************/
void DMA_CancelTransferWithError(DMA_Type *base)
{
    uint32_t regValTemp;
    regValTemp = base->CTRL;
    regValTemp &= ~(DMA_CTRL_ECX_MASK);
    regValTemp |= DMA_CTRL_ECX(1U);
    base->CTRL = regValTemp;
    while (((base->CTRL & DMA_CTRL_ECX_MASK) >> DMA_CTRL_ECX_SHIFT) != 0UL)
    {}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_SetErrorIntCmd
 * Description   : Enable/Disable error interrupt for channels.
 *END**************************************************************************/
void DMA_SetErrorIntCmd(DMA_Type *base, uint8_t channel, bool enable)
{
    if (enable)
    {
        base->CHEIE |= 0x01 << channel;
    } else
    {
        base->CHEIE &= ~(0x01UL << channel);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_SetDmaRequestCmd
 * Description   : Enable/Disable dma request for channel or all channels.
 *END**************************************************************************/
void DMA_SetDmaRequestCmd(DMA_Type *base, uint8_t channel, bool enable)
{
    if (enable)
    {
        base->REQEN |= (0x01UL << channel);
    } else
    {
        base->REQEN &= ~(0x01UL << channel);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_CTSClearReg
 * Description   : Set registers to 0 for hardware CTS of DMA channel.
 *END**************************************************************************/
void DMA_CTSClearReg(DMA_Type *base, uint8_t channel)
{
    base->CTS[channel].BCNT.BCNT = 0U;
    base->CTS[channel].SADDR = 0U;
    base->CTS[channel].SOFF = 0;
    base->CTS[channel].TCR = 0U;
    base->CTS[channel].STO = 0;
    base->CTS[channel].DADDR = 0U;
    base->CTS[channel].DOFF = 0;
    base->CTS[channel].TCNT.LKDIS = 0U;
    base->CTS[channel].DTO_RLD.DTO = 0;
    base->CTS[channel].CSR = 0U;
    base->CTS[channel].TCNTRV = 0U;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_CTSSetAttribute
 * Description   : Configures the transfer attribute for DMA channel.
 *END**************************************************************************/
void DMA_CTSSetAttribute(
    DMA_Type *base, uint8_t channel,
    dma_modulo_t srcModulo, dma_modulo_t destModulo,
    dma_transfer_size_t srcTransferSize, dma_transfer_size_t destTransferSize)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = (uint16_t) (DMA_CTS_TCR_SMOD(srcModulo) | DMA_CTS_TCR_SSIZE(srcTransferSize));
    regValTemp |= (uint16_t) (DMA_CTS_TCR_DMOD(destModulo) | DMA_CTS_TCR_DSIZE(destTransferSize));
    base->CTS[channel].TCR = regValTemp;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_CTSSetNbytes
 * Description   : Configures the nbytes for DMA channel.
 *END**************************************************************************/
void DMA_CTSSetNbytes(DMA_Type *base, uint8_t channel, uint32_t nbytes)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif

    if (((base->CTRL & DMA_CTRL_LOEN_MASK) >> DMA_CTRL_LOEN_SHIFT) != 0UL)
    {
        bool mlOffNo = false;
        if (((base->CTS[channel].BCNT.LODIS & DMA_CTS_BCNT_LODIS_SLOE_MASK) >> DMA_CTS_BCNT_LODIS_SLOE_SHIFT) == 0UL)
        {
            if (((base->CTS[channel].BCNT.LODIS & DMA_CTS_BCNT_LODIS_DLOE_MASK) >> DMA_CTS_BCNT_LODIS_DLOE_SHIFT) ==
                0UL)
            {
                base->CTS[channel].BCNT.LODIS = (nbytes & DMA_CTS_BCNT_LODIS_BCNT_MASK);
                mlOffNo = true;
            }
        }
        if (!mlOffNo)
        {
            uint32_t regValTemp;
            regValTemp = base->CTS[channel].BCNT.LOEN;
            regValTemp &= ~(DMA_CTS_BCNT_LOEN_BCNT_MASK);
            regValTemp |= DMA_CTS_BCNT_LOEN_BCNT(nbytes);
            base->CTS[channel].BCNT.LOEN = regValTemp;
        }
    } else
    {
        base->CTS[channel].BCNT.BCNT = nbytes;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_CTSSetTransferLoopOffset
 * Description   : Configures the transfer loop offset for the CTS.
 *END**************************************************************************/
void DMA_CTSSetTransferLoopOffset(DMA_Type *base, uint8_t channel, int32_t offset)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif

    if (((base->CTRL & DMA_CTRL_LOEN_MASK) >> DMA_CTRL_LOEN_SHIFT) != 0UL)
    {
        bool mlOffNo = false;
        if (((base->CTS[channel].BCNT.LODIS & DMA_CTS_BCNT_LODIS_SLOE_MASK) >> DMA_CTS_BCNT_LODIS_SLOE_SHIFT) != 0UL)
        {
            mlOffNo = true;
        }
        if (((base->CTS[channel].BCNT.LODIS & DMA_CTS_BCNT_LODIS_DLOE_MASK) >> DMA_CTS_BCNT_LODIS_DLOE_SHIFT) != 0UL)
        {
            mlOffNo = true;
        }
        if (mlOffNo)
        {
            uint32_t regValTemp;
            regValTemp = base->CTS[channel].BCNT.LOEN;
            regValTemp &= ~(DMA_CTS_BCNT_LOEN_OFFSET_MASK);
            regValTemp |= DMA_CTS_BCNT_LOEN_OFFSET(offset);
            base->CTS[channel].BCNT.LOEN = regValTemp;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_CTSSetRamReloadLink
 * Description   : Configures the memory address of the next CTS, in Scatter/Gather mode.
 *
 *END**************************************************************************/
void DMA_CTSSetRamReloadLink(DMA_Type *base, uint8_t channel, uint32_t nextCTSAddr)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->CTS[channel].DTO_RLD.RLD = nextCTSAddr;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_CTSSetChannelLoopLink
 * Description   : Set Channel minor link for hardware CTS.
 *END**************************************************************************/
void DMA_CTSSetChannelLoopLink(
    DMA_Type *base, uint8_t channel, uint32_t linkChannel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
    DEV_ASSERT(linkChannel < FEATURE_DMA_CHANNELS);
#endif

    uint16_t regValTemp;
    regValTemp = base->CTS[channel].TCNTRV;
    regValTemp &= (uint16_t) ~(DMA_CTS_TCNT_LKEN_LKEN_MASK);
    regValTemp |= (uint16_t) DMA_CTS_TCNT_LKEN_LKEN(enable ? 1UL : 0UL);
    base->CTS[channel].TCNTRV = regValTemp;
    regValTemp = base->CTS[channel].TCNT.LKEN;
    regValTemp &= (uint16_t) ~(DMA_CTS_TCNT_LKEN_LKEN_MASK);
    regValTemp |= (uint16_t) DMA_CTS_TCNT_LKEN_LKEN(enable ? 1UL : 0UL);
    base->CTS[channel].TCNT.LKEN = regValTemp;

    if (enable)
    {
        regValTemp = base->CTS[channel].TCNTRV;
        regValTemp &= (uint16_t) ~(DMA_CTS_TCNT_LKEN_LKCH_MASK);
        regValTemp |= (uint16_t) DMA_CTS_TCNT_LKEN_LKCH(linkChannel);
        base->CTS[channel].TCNTRV = regValTemp;

        regValTemp = base->CTS[channel].TCNT.LKEN;
        regValTemp &= (uint16_t) ~(DMA_CTS_TCNT_LKEN_LKCH_MASK);
        regValTemp |= (uint16_t) DMA_CTS_TCNT_LKEN_LKCH(linkChannel);
        base->CTS[channel].TCNT.LKEN = regValTemp;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_CTS_CTSSetMajorCount
 * Description   : Sets the major iteration count according to transfer loop
 * channel link setting.
 *END**************************************************************************/
void DMA_CTSSetTriggerCount(DMA_Type *base, uint8_t channel, uint32_t count)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    if ((base->CTS[channel].TCNTRV & DMA_CTS_TCNT_LKDIS_LKEN_MASK) == DMA_CTS_TCNT_LKDIS_LKEN_MASK)
    {
        regValTemp = base->CTS[channel].TCNTRV;
        regValTemp &= (uint16_t) ~(DMA_CTS_TCNT_LKEN_TCNT_MASK);
        regValTemp |= (uint16_t) DMA_CTS_TCNT_LKEN_TCNT(count);
        base->CTS[channel].TCNTRV = regValTemp;

        regValTemp = base->CTS[channel].TCNT.LKEN;
        regValTemp &= (uint16_t) ~(DMA_CTS_TCNT_LKEN_TCNT_MASK);
        regValTemp |= (uint16_t) DMA_CTS_TCNT_LKEN_TCNT(count);
        base->CTS[channel].TCNT.LKEN = regValTemp;
    } else
    {
        regValTemp = base->CTS[channel].TCNTRV;
        regValTemp &= (uint16_t) ~(DMA_CTS_TCNT_LKDIS_TCNT_MASK);
        regValTemp |= (uint16_t) DMA_CTS_TCNT_LKDIS_TCNT(count);
        base->CTS[channel].TCNTRV = regValTemp;

        regValTemp = base->CTS[channel].TCNT.LKDIS;
        regValTemp &= (uint16_t) ~(DMA_CTS_TCNT_LKDIS_TCNT_MASK);
        regValTemp |= (uint16_t) DMA_CTS_TCNT_LKDIS_TCNT(count);
        base->CTS[channel].TCNT.LKDIS = regValTemp;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_CTSGetCurrentTriggerCount
 * Description   : Gets the current major iteration count according to minor
 * loop channel link setting.
 *END**************************************************************************/
uint32_t DMA_CTSGetCurrentTriggerCount(const DMA_Type *base, uint8_t channel)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t result;
    if ((base->CTS[channel].TCNTRV & DMA_CTS_TCNT_LKDIS_LKEN_MASK) == DMA_CTS_TCNT_LKDIS_LKEN_MASK)
    {
        result = (uint16_t) ((base->CTS[channel].TCNT.LKEN & DMA_CTS_TCNT_LKEN_TCNT_MASK)
            >> DMA_CTS_TCNT_LKEN_TCNT_SHIFT);
    } else
    {
        result = (uint16_t) ((base->CTS[channel].TCNT.LKDIS & DMA_CTS_TCNT_LKDIS_TCNT_MASK)
            >> DMA_CTS_TCNT_LKDIS_TCNT_SHIFT);
    }
    return (uint32_t) result;
}

#ifdef FEATURE_DMAMUX_AVAILABLE

/*FUNCTION**********************************************************************
 *
 * Function Name : DMAMUX_init
 * Description   : Initialize the dmamux module to the reset state.
 *END**************************************************************************/
void DMAMUX_Init(DMA_Type *base)
{
    uint8_t i;

    for (i = 0; i < FEATURE_DMA_CHANNELS; i++)
    {
        base->CHMUX[i] = 0;
    }
}

#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
