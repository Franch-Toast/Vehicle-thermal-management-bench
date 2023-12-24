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
 * @file linflexd_uart_irq.c
 *
 */

#include "linflexd_uart_irq.h"

#if (FEATURE_LINFlexD_ORED_INT_LINES)

#if (LINFlexD_INSTANCE_COUNT > 0U)
/* Implementation of LINFlexD0 handler named in startup code. */
void LINFlexD0_UART_IRQHandler(void)
{
    LINFlexD_UART_DRV_IRQHandler(0U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 1U)
/* Implementation of LINFlexD1 handler named in startup code. */
void LINFlexD1_UART_IRQHandler(void)
{
    LINFlexD_UART_DRV_IRQHandler(1U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 2U)
/* Implementation of LINFlexD2 handler named in startup code. */
void LINFlexD2_UART_IRQHandler(void)
{
    LINFlexD_UART_DRV_IRQHandler(2U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 3U)
/* Implementation of LINFlexD3 handler named in startup code. */
void LINFlexD3_UART_IRQHandler(void)
{
    LINFlexD_UART_DRV_IRQHandler(3U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 4U)
/* Implementation of LINFlexD4 handler named in startup code. */
void LINFlexD4_UART_IRQHandler(void)
{
    LINFlexD_UART_DRV_IRQHandler(4U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 5U)
/* Implementation of LINFlexD5 handler named in startup code. */
void LINFlexD5_UART_IRQHandler(void)
{
    LINFlexD_UART_DRV_IRQHandler(5U);
}
#endif

/* ISR array for LINFlexD UART driver */
const isr_t g_uartLINFlexDIsr[LINFlexD_INSTANCE_COUNT] = {
    #if (LINFlexD_INSTANCE_COUNT > 0U)
    &LINFlexD0_UART_IRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 1U)
    &LINFlexD1_UART_IRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 2U)
    &LINFlexD2_UART_IRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 3U)
    &LINFlexD3_UART_IRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 4U)
    &LINFlexD4_UART_IRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 5U)
    &LINFlexD5_UART_IRQHandler,
    #endif
};

#elif (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)

#if (LINFlexD_INSTANCE_COUNT > 0U)
/* Implementation of LINFlexD0 rx handler named in startup code. */
void LINFlexD0_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(0U);
}

/* Implementation of LINFlexD0 tx handler named in startup code. */
void LINFlexD0_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(0U);
}

/* Implementation of LINFlexD0 error handler named in startup code. */
void LINFlexD0_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(0U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 1U)
/* Implementation of LINFlexD1 rx handler named in startup code. */
void LINFlexD1_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(1U);
}

/* Implementation of LINFlexD1 tx handler named in startup code. */
void LINFlexD1_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(1U);
}

/* Implementation of LINFlexD1 error handler named in startup code. */
void LINFlexD1_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(1U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 2U)
/* Implementation of LINFlexD2 rx handler named in startup code. */
void LINFlexD2_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(2U);
}

/* Implementation of LINFlexD2 tx handler named in startup code. */
void LINFlexD2_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(2U);
}

/* Implementation of LINFlexD2 error handler named in startup code. */
void LINFlexD2_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(2U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 3U)
/* Implementation of LINFlexD3 rx handler named in startup code. */
void LINFlexD3_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(3U);
}

/* Implementation of LINFlexD3 tx handler named in startup code. */
void LINFlexD3_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(3U);
}

/* Implementation of LINFlexD3 error handler named in startup code. */
void LINFlexD3_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(3U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 4U)
/* Implementation of LINFlexD4 rx handler named in startup code. */
void LINFlexD4_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(4U);
}

/* Implementation of LINFlexD4 tx handler named in startup code. */
void LINFlexD4_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(4U);
}

/* Implementation of LINFlexD4 error handler named in startup code. */
void LINFlexD4_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(4U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 5U)
/* Implementation of LINFlexD5 rx handler named in startup code. */
void LINFlexD5_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(5U);
}

/* Implementation of LINFlexD5 tx handler named in startup code. */
void LINFlexD5_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(5U);
}

/* Implementation of LINFlexD5 error handler named in startup code. */
void LINFlexD5_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(5U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 6U)
/* Implementation of LINFlexD6 rx handler named in startup code. */
void LINFlexD6_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(6U);
}

/* Implementation of LINFlexD6 tx handler named in startup code. */
void LINFlexD6_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(6U);
}

/* Implementation of LINFlexD6 error handler named in startup code. */
void LINFlexD6_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(6U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 7U)
/* Implementation of LINFlexD7 rx handler named in startup code. */
void LINFlexD7_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(7U);
}

/* Implementation of LINFlexD7 tx handler named in startup code. */
void LINFlexD7_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(7U);
}

/* Implementation of LINFlexD7 error handler named in startup code. */
void LINFlexD7_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(7U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 8U)
/* Implementation of LINFlexD8 rx handler named in startup code. */
void LINFlexD8_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(8U);
}

/* Implementation of LINFlexD8 tx handler named in startup code. */
void LINFlexD8_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(8U);
}

/* Implementation of LINFlexD8 error handler named in startup code. */
void LINFlexD8_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(8U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 9U)
/* Implementation of LINFlexD9 rx handler named in startup code. */
void LINFlexD9_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(9U);
}

/* Implementation of LINFlexD9 tx handler named in startup code. */
void LINFlexD9_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(9U);
}

/* Implementation of LINFlexD9 error handler named in startup code. */
void LINFlexD9_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(9U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 10U)
/* Implementation of LINFlexD10 rx handler named in startup code. */
void LINFlexD10_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(10U);
}

/* Implementation of LINFlexD10 tx handler named in startup code. */
void LINFlexD10_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(10U);
}

/* Implementation of LINFlexD10 error handler named in startup code. */
void LINFlexD10_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(10U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 11U)
/* Implementation of LINFlexD11 rx handler named in startup code. */
void LINFlexD11_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(11U);
}

/* Implementation of LINFlexD11 tx handler named in startup code. */
void LINFlexD11_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(11U);
}

/* Implementation of LINFlexD11 error handler named in startup code. */
void LINFlexD11_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(11U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 12U)
/* Implementation of LINFlexD12 rx handler named in startup code. */
void LINFlexD12_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(12U);
}

/* Implementation of LINFlexD12 tx handler named in startup code. */
void LINFlexD12_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(12U);
}

/* Implementation of LINFlexD12 error handler named in startup code. */
void LINFlexD12_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(12U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 13U)
/* Implementation of LINFlexD13 rx handler named in startup code. */
void LINFlexD13_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(13U);
}

/* Implementation of LINFlexD13 tx handler named in startup code. */
void LINFlexD13_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(13U);
}

/* Implementation of LINFlexD13 error handler named in startup code. */
void LINFlexD13_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(13U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 14U)
/* Implementation of LINFlexD14 rx handler named in startup code. */
void LINFlexD14_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(14U);
}

/* Implementation of LINFlexD14 tx handler named in startup code. */
void LINFlexD14_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(14U);
}

/* Implementation of LINFlexD14 error handler named in startup code. */
void LINFlexD14_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(14U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 15U)
/* Implementation of LINFlexD15 rx handler named in startup code. */
void LINFlexD15_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(15U);
}

/* Implementation of LINFlexD15 tx handler named in startup code. */
void LINFlexD15_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(15U);
}

/* Implementation of LINFlexD15 error handler named in startup code. */
void LINFlexD15_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(15U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 16U)
/* Implementation of LINFlexD16 rx handler named in startup code. */
void LINFlexD16_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(16U);
}

/* Implementation of LINFlexD16 tx handler named in startup code. */
void LINFlexD16_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(16U);
}

/* Implementation of LINFlexD16 error handler named in startup code. */
void LINFlexD16_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(16U);
}
#endif

#if (LINFlexD_INSTANCE_COUNT > 17U)
/* Implementation of LINFlexD17 rx handler named in startup code. */
void LINFlexD17_UART_RxIRQHandler(void)
{
    LINFlexD_UART_DRV_RxIRQHandler(17U);
}

/* Implementation of LINFlexD17 tx handler named in startup code. */
void LINFlexD17_UART_TxIRQHandler(void)
{
    LINFlexD_UART_DRV_TxIRQHandler(17U);
}

/* Implementation of LINFlexD17 error handler named in startup code. */
void LINFlexD17_UART_ErrIRQHandler(void)
{
    LINFlexD_UART_DRV_ErrIRQHandler(17U);
}
#endif

/* Rx ISR array for LINFlexD UART driver */
const isr_t g_uartLINFlexDRxIsr[LINFlexD_INSTANCE_COUNT] = {
    #if (LINFlexD_INSTANCE_COUNT > 0U)
    &LINFlexD0_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 1U)
    &LINFlexD1_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 2U)
    &LINFlexD2_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 3U)
    &LINFlexD3_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 4U)
    &LINFlexD4_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 5U)
    &LINFlexD5_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 6U)
    &LINFlexD6_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 7U)
    &LINFlexD7_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 8U)
    &LINFlexD8_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 9U)
    &LINFlexD9_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 10U)
    &LINFlexD10_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 11U)
    &LINFlexD11_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 12U)
    &LINFlexD12_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 13U)
    &LINFlexD13_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 14U)
    &LINFlexD14_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 15U)
    &LINFlexD15_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 16U)
    &LINFlexD16_UART_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 17U)
    &LINFlexD17_UART_RxIRQHandler
    #endif
};

/* Tx ISR array for LINFlexD UART driver */
const isr_t g_uartLINFlexDTxIsr[LINFlexD_INSTANCE_COUNT] = {
    #if (LINFlexD_INSTANCE_COUNT > 0U)
    &LINFlexD0_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 1U)
    &LINFlexD1_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 2U)
    &LINFlexD2_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 3U)
    &LINFlexD3_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 4U)
    &LINFlexD4_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 5U)
    &LINFlexD5_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 6U)
    &LINFlexD6_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 7U)
    &LINFlexD7_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 8U)
    &LINFlexD8_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 9U)
    &LINFlexD9_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 10U)
    &LINFlexD10_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 11U)
    &LINFlexD11_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 12U)
    &LINFlexD12_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 13U)
    &LINFlexD13_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 14U)
    &LINFlexD14_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 15U)
    &LINFlexD15_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 16U)
    &LINFlexD16_UART_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 17U)
    &LINFlexD17_UART_TxIRQHandler
    #endif
};

/* Err ISR array for LINFlexD UART driver */
const isr_t g_uartLINFlexDErrIsr[LINFlexD_INSTANCE_COUNT] = {
    #if (LINFlexD_INSTANCE_COUNT > 0U)
    &LINFlexD0_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 1U)
    &LINFlexD1_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 2U)
    &LINFlexD2_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 3U)
    &LINFlexD3_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 4U)
    &LINFlexD4_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 5U)
    &LINFlexD5_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 6U)
    &LINFlexD6_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 7U)
    &LINFlexD7_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 8U)
    &LINFlexD8_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 9U)
    &LINFlexD9_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 10U)
    &LINFlexD10_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 11U)
    &LINFlexD11_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 12U)
    &LINFlexD12_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 13U)
    &LINFlexD13_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 14U)
    &LINFlexD14_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 15U)
    &LINFlexD15_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 16U)
    &LINFlexD16_UART_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 17U)
    &LINFlexD17_UART_ErrIRQHandler
    #endif
};

#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/

