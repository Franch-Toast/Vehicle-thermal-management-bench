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
 * @file dma_irq.c
 */

#include "dma_irq.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#ifdef FEATURE_DMA_ORED_IRQ_LINES_16_CHN
void DMA0_15_IRQHandler(void);
#if (FEATURE_DMA_VIRTUAL_CHANNELS > 16U)
void DMA16_31_IRQHandler(void);
#endif
#endif

#ifdef FEATURE_DMA_SEPARATE_IRQ_LINES_PER_CHN

void DMA0_IRQHandler(void);

void DMA1_IRQHandler(void);

void DMA2_IRQHandler(void);

void DMA3_IRQHandler(void);

#if (FEATURE_DMA_VIRTUAL_CHANNELS > 4U)

void DMA4_IRQHandler(void);

void DMA5_IRQHandler(void);

void DMA6_IRQHandler(void);

void DMA7_IRQHandler(void);

#endif
#if (FEATURE_DMA_VIRTUAL_CHANNELS > 8U)

void DMA8_IRQHandler(void);

void DMA9_IRQHandler(void);

void DMA10_IRQHandler(void);

void DMA11_IRQHandler(void);

void DMA12_IRQHandler(void);

void DMA13_IRQHandler(void);

void DMA14_IRQHandler(void);

void DMA15_IRQHandler(void);

#endif
#if (FEATURE_DMA_VIRTUAL_CHANNELS > 16U)
void DMA16_IRQHandler(void);
void DMA17_IRQHandler(void);
void DMA18_IRQHandler(void);
void DMA19_IRQHandler(void);
void DMA20_IRQHandler(void);
void DMA21_IRQHandler(void);
void DMA22_IRQHandler(void);
void DMA23_IRQHandler(void);
void DMA24_IRQHandler(void);
void DMA25_IRQHandler(void);
void DMA26_IRQHandler(void);
void DMA27_IRQHandler(void);
void DMA28_IRQHandler(void);
void DMA29_IRQHandler(void);
void DMA30_IRQHandler(void);
void DMA31_IRQHandler(void);
#endif
#endif

#ifdef FEATURE_DMA_HAS_ERROR_IRQ

void DMA_Error_IRQHandler(void);

#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

#ifdef FEATURE_DMA_ORED_IRQ_LINES_16_CHN

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA0_15_IRQHandler(void)
{
    /* Read the status flags register */
    const DMA_Type * dmaRegBase = DMA_DRV_GetDmaRegBaseAddr(0U);
    uint32_t mask = 0xFFFF;
    uint32_t flags = dmaRegBase->CHTLDIF;
    uint8_t virtualChannel = 0U;
    flags &= mask;
    /* Check all the flags from 0 to 15 and call the handler for the appropriate channel */
    while (flags > 0U)
    {
       if ((flags & 1U) > 0U)
       {
           DMA_DRV_IRQHandler(virtualChannel);
       }
       virtualChannel++;
       flags >>= 1U;
    }
}
#if (FEATURE_DMA_VIRTUAL_CHANNELS > 16U)
/*! @brief DMA16_31_IRQn IRQ handler with the same name in the startup code*/
void DMA16_31_IRQHandler(void)
{
    /* Read the status flags register */
    const DMA_Type * dmaRegBase = DMA_DRV_GetDmaRegBaseAddr(0U);
    uint32_t flags = dmaRegBase->INT;
    uint8_t virtualChannel = 16U;
    flags >>= 16U;
    /* Check all the flags from 16 to 31 and call the handler for the appropriate channel */
    while (flags > 0U)
    {
       if ((flags & 1U) > 0U)
       {
           DMA_DRV_IRQHandler(virtualChannel);
       }
       virtualChannel++;
       flags >>= 1U;
    }
}
#endif /* (FEATURE_DMA_VIRTUAL_CHANNELS > 16U) */
#endif /* FEATURE_DMA_ORED_IRQ_LINES_16_CHN */

#ifdef FEATURE_DMA_SEPARATE_IRQ_LINES_PER_CHN

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA0_IRQHandler(void)
{
    DMA_DRV_IRQHandler(0U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA1_IRQHandler(void)
{
    DMA_DRV_IRQHandler(1U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA2_IRQHandler(void)
{
    DMA_DRV_IRQHandler(2U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA3_IRQHandler(void)
{
    DMA_DRV_IRQHandler(3U);
}

#if (FEATURE_DMA_VIRTUAL_CHANNELS > 4U)

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA4_IRQHandler(void)
{
    DMA_DRV_IRQHandler(4U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA5_IRQHandler(void)
{
    DMA_DRV_IRQHandler(5U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA6_IRQHandler(void)
{
    DMA_DRV_IRQHandler(6U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA7_IRQHandler(void)
{
    DMA_DRV_IRQHandler(7U);
}

#endif /* (FEATURE_DMA_VIRTUAL_CHANNELS > 4U) */
#if (FEATURE_DMA_VIRTUAL_CHANNELS > 8U)

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA8_IRQHandler(void)
{
    DMA_DRV_IRQHandler(8U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA9_IRQHandler(void)
{
    DMA_DRV_IRQHandler(9U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA10_IRQHandler(void)
{
    DMA_DRV_IRQHandler(10U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA11_IRQHandler(void)
{
    DMA_DRV_IRQHandler(11U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA12_IRQHandler(void)
{
    DMA_DRV_IRQHandler(12U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA13_IRQHandler(void)
{
    DMA_DRV_IRQHandler(13U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA14_IRQHandler(void)
{
    DMA_DRV_IRQHandler(14U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA15_IRQHandler(void)
{
    DMA_DRV_IRQHandler(15U);
}

#endif /* (FEATURE_DMA_VIRTUAL_CHANNELS > 8U) */
#if (FEATURE_DMA_VIRTUAL_CHANNELS > 16U)
void DMA16_IRQHandler(void)
{
    DMA_DRV_IRQHandler(16U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA17_IRQHandler(void)
{
    DMA_DRV_IRQHandler(17U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA18_IRQHandler(void)
{
    DMA_DRV_IRQHandler(18U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA19_IRQHandler(void)
{
    DMA_DRV_IRQHandler(19U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA20_IRQHandler(void)
{
    DMA_DRV_IRQHandler(20U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA21_IRQHandler(void)
{
    DMA_DRV_IRQHandler(21U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA22_IRQHandler(void)
{
    DMA_DRV_IRQHandler(22U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA23_IRQHandler(void)
{
    DMA_DRV_IRQHandler(23U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA24_IRQHandler(void)
{
    DMA_DRV_IRQHandler(24U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA25_IRQHandler(void)
{
    DMA_DRV_IRQHandler(25U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA26_IRQHandler(void)
{
    DMA_DRV_IRQHandler(26U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA27_IRQHandler(void)
{
    DMA_DRV_IRQHandler(27U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA28_IRQHandler(void)
{
    DMA_DRV_IRQHandler(28U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA29_IRQHandler(void)
{
    DMA_DRV_IRQHandler(29U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA30_IRQHandler(void)
{
    DMA_DRV_IRQHandler(30U);
}

/*! @brief DMA IRQ handler with the same name in the startup code*/
void DMA31_IRQHandler(void)
{
    DMA_DRV_IRQHandler(31U);
}
#endif /* (FEATURE_DMA_VIRTUAL_CHANNELS > 16U) */
#endif /* FEATURE_DMA_SEPARATE_IRQ_LINES_PER_CHN */

#ifdef FEATURE_DMA_HAS_ERROR_IRQ

/*! @brief DMA ERROR IRQ handler with the same name in the startup code*/
void DMA_Error_IRQHandler(void)
{
    const DMA_Type *dmaRegBase = DMA_DRV_GetDmaRegBaseAddr(0U);
    uint32_t error = DMA_GetErrorIntStatusFlag(dmaRegBase);
    uint8_t virtualChannel;

    for (virtualChannel = 0U;
         virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS;
         virtualChannel++)
    {
        if ((error & DMA_ERR_LSB_MASK) != 0UL)
        {
            DMA_DRV_ErrorIRQHandler(virtualChannel);
        }
        error = error >> 1U;
    }
}

#endif /* FEATURE_DMA_HAS_ERROR_IRQ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
