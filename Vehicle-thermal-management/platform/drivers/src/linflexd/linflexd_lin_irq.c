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
 * @file linflexd_lin_irq.c
 */

#include "linflexd_lin_irq.h"

#if (FEATURE_LINFlexD_ORED_INT_LINES)

#if (LINFlexD_INSTANCE_COUNT > 0U)
/* Implementation of LINFlexD0 handler named in startup code. */
void LINFlexD0_LIN_IRQHandler(void)
{
    LINFlexD_LIN_DRV_IRQHandler(0U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 1U)
/* Implementation of LINFlexD1 handler named in startup code. */
void LINFlexD1_LIN_IRQHandler(void)
{
    LINFlexD_LIN_DRV_IRQHandler(1U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 2U)
/* Implementation of LINFlexD2 handler named in startup code. */
void LINFlexD2_LIN_IRQHandler(void)
{
    LINFlexD_LIN_DRV_IRQHandler(2U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 3U)
/* Implementation of LINFlexD3 handler named in startup code. */
void LINFlexD3_LIN_IRQHandler(void)
{
    LINFlexD_LIN_DRV_IRQHandler(3U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 4U)
/* Implementation of LINFlexD4 handler named in startup code. */
void LINFlexD4_LIN_IRQHandler(void)
{
    LINFlexD_LIN_DRV_IRQHandler(4U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 5U)
/* Implementation of LINFlexD5 handler named in startup code. */
void LINFlexD5_LIN_IRQHandler(void)
{
    LINFlexD_LIN_DRV_IRQHandler(5U);
}
#endif
/* ISR array for LINFlexD LIN driver */
const isr_t g_LinLINFlexDIsr[LINFlexD_INSTANCE_COUNT] = {
    #if (LINFlexD_INSTANCE_COUNT > 0U)
    &LINFlexD0_LIN_IRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 1U)
    &LINFlexD1_LIN_IRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 2U)
    &LINFlexD2_LIN_IRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 3U)
    &LINFlexD3_LIN_IRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 4U)
    &LINFlexD4_LIN_IRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 5U)
    &LINFlexD5_LIN_IRQHandler,
    #endif
};

#elif (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)

#if (LINFlexD_INSTANCE_COUNT > 0U)
/* Implementation of LINFlexD0 rx handler named in startup code. */
void LINFlexD0_LIN_RxIRQHandler(void)
{
    LINFlexD_LIN_DRV_RxIRQHandler(0U);
}

/* Implementation of LINFlexD0 tx handler named in startup code. */
void LINFlexD0_LIN_TxIRQHandler(void)
{
    LINFlexD_LIN_DRV_TxIRQHandler(0U);
}

/* Implementation of LINFlexD0 error handler named in startup code. */
void LINFlexD0_LIN_ErrIRQHandler(void)
{
    LINFlexD_LIN_DRV_ErrIRQHandler(0U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 1U)
/* Implementation of LINFlexD1 rx handler named in startup code. */
void LINFlexD1_LIN_RxIRQHandler(void)
{
    LINFlexD_LIN_DRV_RxIRQHandler(0U);
}

/* Implementation of LINFlexD1 tx handler named in startup code. */
void LINFlexD1_LIN_TxIRQHandler(void)
{
    LINFlexD_LIN_DRV_TxIRQHandler(0U);
}

/* Implementation of LINFlexD1 error handler named in startup code. */
void LINFlexD1_LIN_ErrIRQHandler(void)
{
    LINFlexD_LIN_DRV_ErrIRQHandler(0U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 2U)
/* Implementation of LINFlexD2 rx handler named in startup code. */
void LINFlexD2_LIN_RxIRQHandler(void)
{
    LINFlexD_LIN_DRV_RxIRQHandler(0U);
}

/* Implementation of LINFlexD2 tx handler named in startup code. */
void LINFlexD2_LIN_TxIRQHandler(void)
{
    LINFlexD_LIN_DRV_TxIRQHandler(0U);
}

/* Implementation of LINFlexD2 error handler named in startup code. */
void LINFlexD2_LIN_ErrIRQHandler(void)
{
    LINFlexD_LIN_DRV_ErrIRQHandler(0U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 3U)
/* Implementation of LINFlexD3 rx handler named in startup code. */
void LINFlexD3_LIN_RxIRQHandler(void)
{
    LINFlexD_LIN_DRV_RxIRQHandler(0U);
}

/* Implementation of LINFlexD3 tx handler named in startup code. */
void LINFlexD3_LIN_TxIRQHandler(void)
{
    LINFlexD_LIN_DRV_TxIRQHandler(0U);
}

/* Implementation of LINFlexD3 error handler named in startup code. */
void LINFlexD3_LIN_ErrIRQHandler(void)
{
    LINFlexD_LIN_DRV_ErrIRQHandler(0U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 4U)
/* Implementation of LINFlexD4 rx handler named in startup code. */
void LINFlexD4_LIN_RxIRQHandler(void)
{
    LINFlexD_LIN_DRV_RxIRQHandler(0U);
}

/* Implementation of LINFlexD4 tx handler named in startup code. */
void LINFlexD4_LIN_TxIRQHandler(void)
{
    LINFlexD_LIN_DRV_TxIRQHandler(0U);
}

/* Implementation of LINFlexD4 error handler named in startup code. */
void LINFlexD4_LIN_ErrIRQHandler(void)
{
    LINFlexD_LIN_DRV_ErrIRQHandler(0U);
}
#endif
#if (LINFlexD_INSTANCE_COUNT > 5U)
/* Implementation of LINFlexD5 rx handler named in startup code. */
void LINFlexD5_LIN_RxIRQHandler(void)
{
    LINFlexD_LIN_DRV_RxIRQHandler(0U);
}

/* Implementation of LINFlexD5 tx handler named in startup code. */
void LINFlexD5_LIN_TxIRQHandler(void)
{
    LINFlexD_LIN_DRV_TxIRQHandler(0U);
}

/* Implementation of LINFlexD5 error handler named in startup code. */
void LINFlexD5_LIN_ErrIRQHandler(void)
{
    LINFlexD_LIN_DRV_ErrIRQHandler(0U);
}
#endif

/* Rx ISR array for LINFlexD LIN driver */
const isr_t g_LinLINFlexDRxIsr[LINFlexD_INSTANCE_COUNT] = {
    #if (LINFlexD_INSTANCE_COUNT > 0U)
    &LINFlexD0_LIN_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 1U)
    &LINFlexD1_LIN_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 2U)
    &LINFlexD2_LIN_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 3U)
    &LINFlexD3_LIN_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 4U)
    &LINFlexD4_LIN_RxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 5U)
    &LINFlexD5_LIN_RxIRQHandler,
    #endif
};

/* Tx ISR array for LINFlexD LIN driver */
const isr_t g_LinLINFlexDTxIsr[LINFlexD_INSTANCE_COUNT] = {
    #if (LINFlexD_INSTANCE_COUNT > 0U)
    &LINFlexD0_LIN_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 1U)
    &LINFlexD1_LIN_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 2U)
    &LINFlexD2_LIN_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 3U)
    &LINFlexD3_LIN_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 4U)
    &LINFlexD4_LIN_TxIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 5U)
    &LINFlexD5_LIN_TxIRQHandler,
    #endif
};

/* Err ISR array for LINFlexD LIN driver */
const isr_t g_LinLINFlexDErrIsr[LINFlexD_INSTANCE_COUNT] = {
    #if (LINFlexD_INSTANCE_COUNT > 0U)
    &LINFlexD0_LIN_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 1U)
    &LINFlexD1_LIN_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 2U)
    &LINFlexD2_LIN_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 3U)
    &LINFlexD3_LIN_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 4U)
    &LINFlexD4_LIN_ErrIRQHandler,
    #endif
    #if (LINFlexD_INSTANCE_COUNT > 5U)
    &LINFlexD5_LIN_ErrIRQHandler,
    #endif
};

#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/

