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
 * @file dma_irq.h
 */

#include "dma_hw_access.h"

/*! @brief DMA channel interrupt handler, implemented in driver c file. */
void DMA_DRV_IRQHandler(uint8_t virtualChannel);

#ifdef FEATURE_DMA_HAS_ERROR_IRQ

/*! @brief DMA error interrupt handler, implemented in driver c file. */
void DMA_DRV_ErrorIRQHandler(uint8_t virtualChannel);

#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
