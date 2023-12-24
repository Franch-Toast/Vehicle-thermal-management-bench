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
 * @file linflexd_uart_irq.h
 */

#include "linflexd_hw_access.h"

/*!
 * @brief Or'ed interrupt handler, implemented in driver c file.
 */
void LINFlexD_UART_DRV_IRQHandler(uint32_t instance);

/*!
 * @brief Rx interrupt handler, implemented in driver c file.
 */
void LINFlexD_UART_DRV_RxIRQHandler(uint32_t instance);

/*!
 * @brief Tx interrupt handler, implemented in driver c file.
 */
void LINFlexD_UART_DRV_TxIRQHandler(uint32_t instance);

/*!
 * @brief Error interrupt handler, implemented in driver c file.
 */
void LINFlexD_UART_DRV_ErrIRQHandler(uint32_t instance);

/*!
 * @brief ISR declarations - implemented in linflexd_uart_irq.c.
 */
#if (FEATURE_LINFlexD_ORED_INT_LINES)

    /* ISR declarations for rx/tx/err interrupts or'ed together */
    #if (LINFlexD_INSTANCE_COUNT > 0U)
    void LINFlexD0_UART_IRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 1U)
    void LINFlexD1_UART_IRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 2U)
    void LINFlexD2_UART_IRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 3U)
    void LINFlexD3_UART_IRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 4U)
    void LINFlexD4_UART_IRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 5U)
    void LINFlexD5_UART_IRQHandler(void);
    #endif

    /* ISR array for LINFlexD UART driver */
    extern const isr_t g_uartLINFlexDIsr[LINFlexD_INSTANCE_COUNT];

#elif (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)

    /* ISR declarations for separate rx/tx/err interrupts */
    #if (LINFlexD_INSTANCE_COUNT > 0U)
    void LINFlexD0_UART_RxIRQHandler(void);
    void LINFlexD0_UART_TxIRQHandler(void);
    void LINFlexD0_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 1U)
    void LINFlexD1_UART_RxIRQHandler(void);
    void LINFlexD1_UART_TxIRQHandler(void);
    void LINFlexD1_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 2U)
    void LINFlexD2_UART_RxIRQHandler(void);
    void LINFlexD2_UART_TxIRQHandler(void);
    void LINFlexD2_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 3U)
    void LINFlexD3_UART_RxIRQHandler(void);
    void LINFlexD3_UART_TxIRQHandler(void);
    void LINFlexD3_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 4U)
    void LINFlexD4_UART_RxIRQHandler(void);
    void LINFlexD4_UART_TxIRQHandler(void);
    void LINFlexD4_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 5U)
    void LINFlexD5_UART_RxIRQHandler(void);
    void LINFlexD5_UART_TxIRQHandler(void);
    void LINFlexD5_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 6U)
    void LINFlexD6_UART_RxIRQHandler(void);
    void LINFlexD6_UART_TxIRQHandler(void);
    void LINFlexD6_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 7U)
    void LINFlexD7_UART_RxIRQHandler(void);
    void LINFlexD7_UART_TxIRQHandler(void);
    void LINFlexD7_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 8U)
    void LINFlexD8_UART_RxIRQHandler(void);
    void LINFlexD8_UART_TxIRQHandler(void);
    void LINFlexD8_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 9U)
    void LINFlexD9_UART_RxIRQHandler(void);
    void LINFlexD9_UART_TxIRQHandler(void);
    void LINFlexD9_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 10U)
    void LINFlexD10_UART_RxIRQHandler(void);
    void LINFlexD10_UART_TxIRQHandler(void);
    void LINFlexD10_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 11U)
    void LINFlexD11_UART_RxIRQHandler(void);
    void LINFlexD11_UART_TxIRQHandler(void);
    void LINFlexD11_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 12U)
    void LINFlexD12_UART_RxIRQHandler(void);
    void LINFlexD12_UART_TxIRQHandler(void);
    void LINFlexD12_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 13U)
    void LINFlexD13_UART_RxIRQHandler(void);
    void LINFlexD13_UART_TxIRQHandler(void);
    void LINFlexD13_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 14U)
    void LINFlexD14_UART_RxIRQHandler(void);
    void LINFlexD14_UART_TxIRQHandler(void);
    void LINFlexD14_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 15U)
    void LINFlexD15_UART_RxIRQHandler(void);
    void LINFlexD15_UART_TxIRQHandler(void);
    void LINFlexD15_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 16U)
    void LINFlexD16_UART_RxIRQHandler(void);
    void LINFlexD16_UART_TxIRQHandler(void);
    void LINFlexD16_UART_ErrIRQHandler(void);
    #endif

    #if (LINFlexD_INSTANCE_COUNT > 17U)
    void LINFlexD17_UART_RxIRQHandler(void);
    void LINFlexD17_UART_TxIRQHandler(void);
    void LINFlexD17_UART_ErrIRQHandler(void);
    #endif

    /* Rx ISR array for LINFlexD UART driver */
    extern const isr_t g_uartLINFlexDRxIsr[LINFlexD_INSTANCE_COUNT];

    /* Tx ISR array for LINFlexD UART driver */
    extern const isr_t g_uartLINFlexDTxIsr[LINFlexD_INSTANCE_COUNT];

    /* Err ISR array for LINFlexD UART driver */
    extern const isr_t g_uartLINFlexDErrIsr[LINFlexD_INSTANCE_COUNT];

#endif
