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

#include "linflexd_uart_irq.h"
#include "linflexd_uart_driver.h"


/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Array of pointers to UART driver runtime state structures */
static linflexd_uart_state_t * s_uartLINFlexDStatePtr[LINFlexD_INSTANCE_COUNT] = {NULL};

/*! @brief Table of base addresses for LINFlexD instances. */
static LINFlexD_Type * const s_uartLINFlexDBase[LINFlexD_INSTANCE_COUNT] = LINFlexD_BASE_PTRS;

#if (FEATURE_LINFlexD_HAS_DIFFERENT_MEM_MAP)
/*! @brief Table storing DMA capabilities for LINFlexD instances. */
static const bool s_LINFlexDInstHasFilters[LINFlexD_INSTANCE_COUNT] = FEATURE_LINFlexD_INST_HAS_IFCR;
#endif

#if (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)
/*! @brief Tables to save LINFlexD IRQ vectors defined in the header file */
static const IRQn_Type s_uartLINFlexDRxIntVec[LINFlexD_INSTANCE_COUNT] = LINFlexD_RX_IRQS;
static const IRQn_Type s_uartLINFlexDTxIntVec[LINFlexD_INSTANCE_COUNT] = LINFlexD_TX_IRQS;
static const IRQn_Type s_uartLINFlexDErrIntVec[LINFlexD_INSTANCE_COUNT] = LINFlexD_ERR_IRQS;
#elif (FEATURE_LINFlexD_ORED_INT_LINES)
/*! @brief Table to save LINFlexD IRQ vectors defined in the header file */
static const IRQn_Type s_uartLINFlexDIntVec[LINFlexD_INSTANCE_COUNT] = LINFlexD_IRQS;
#endif

/*! @brief Table to save LINFlexD clock indexes in clock configuration */
static const clock_names_t s_uartLINFlexDClkNames[LINFlexD_INSTANCE_COUNT] = LINFlexD_CLOCK_NAMES;

/*******************************************************************************
 * Private Functions
 ******************************************************************************/

static status_t LINFlexD_UART_DRV_StartSendUsingInterrupts(uint32_t instance,
                                                           const uint8_t * txBuff,
                                                           uint32_t txSize);
static status_t LINFlexD_UART_DRV_StartReceiveUsingInterrupts(uint32_t instance,
                                                              uint8_t * rxBuff,
                                                              uint32_t rxSize);
static void LINFlexD_UART_DRV_CompleteSendUsingInterrupts(uint32_t instance);
static void LINFlexD_UART_DRV_CompleteReceiveUsingInterrupts(uint32_t instance);
static status_t LINFlexD_UART_DRV_StartSendUsingDma(uint32_t instance,
                                                    const uint8_t * txBuff,
                                                    uint32_t txSize);
static status_t LINFlexD_UART_DRV_StartReceiveUsingDma(uint32_t instance,
                                                       uint8_t * rxBuff,
                                                       uint32_t rxSize);
static void LINFlexD_UART_DRV_CompleteSendUsingDma(void * parameter, dma_chn_status_t status);
static void LINFlexD_UART_DRV_CompleteReceiveUsingDma(void * parameter, dma_chn_status_t status);
static void LINFlexD_UART_DRV_PutData(uint32_t instance);
static void LINFlexD_UART_DRV_GetData(uint32_t instance);
static void LINFlexD_UART_DRV_FlushRxFifo(const LINFlexD_Type *base);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_SetBaudRate
 * Description   : This function sets the baud rate for UART communication.
 *
 * Implements    : LINFlexD_UART_DRV_SetBaudRate_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_SetBaudRate(uint32_t instance, uint32_t baudrate)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    float32_t prescaler;
    float32_t fraction;
    uint32_t mantissa;
    uint32_t fractionDenominator;
    uint8_t fractionNumerator;
    uint32_t uartSourceClock;
    clock_names_t instanceClkName;
    LINFlexD_Type * base;
    bool resetIdle = false;

    instanceClkName = s_uartLINFlexDClkNames[instance];
    base = s_uartLINFlexDBase[instance];
    (void)CLOCK_SYS_GetFreq(instanceClkName, &uartSourceClock);

    const linflexd_uart_state_t * uartState;
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    if (uartState->isTxBusy == true)
    {
        return STATUS_BUSY;
    }

    if (uartState->isRxBusy == true)
    {
        return STATUS_BUSY;
    }

    /* Compute the values for baud rate divider mantissa and fraction */
    prescaler = (float32_t)uartSourceClock / ((float32_t)baudrate * (float32_t)DEFAULT_OSR);
    mantissa = (uint32_t)prescaler;
    fraction = prescaler - (float32_t)mantissa;
    fractionDenominator = ((uint32_t)1U << (uint32_t)BAUDRATE_FRACTION_WIDTH);
    float32_t float32_tNumerator = ((float32_t)fraction * (float32_t)fractionDenominator) + (float32_t)0.5F;
    fractionNumerator = (uint8_t)(float32_tNumerator);

    if (fractionNumerator == fractionDenominator)
    {
        fractionNumerator = 0;
        mantissa++;
    }

    if (LINFlexD_GetLinState(base) != LINFlexD_STATE_INIT_MODE)
    {
        /* Request init mode and wait until the mode entry is complete */
        LINFlexD_EnterInitMode(base);
        while (LINFlexD_GetLinState(base) != LINFlexD_STATE_INIT_MODE) {}

        resetIdle = true;
    }

    /* Write the computed values to registers */
    LINFlexD_SetIntegerBaudRate(base, mantissa);
    LINFlexD_SetFractionalBaudRate(base, fractionNumerator);

    if (resetIdle == true)
    {
        /* Enter normal mode */
        LINFlexD_EnterNormalMode(base);
    }

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_GetBaudRate
 * Description   : This function retrieves the baud rate for UART communication.
 *
 * Implements    : LINFlexD_UART_DRV_GetBaudRate_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_GetBaudRate(uint32_t instance, uint32_t * baudrate)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);
    DEV_ASSERT(baudrate != NULL);

    uint32_t mantissa;
    uint8_t fraction;
    uint32_t uartSourceClock;
    clock_names_t instanceClkName;
    const LINFlexD_Type * base;

    instanceClkName = s_uartLINFlexDClkNames[instance];
    base = s_uartLINFlexDBase[instance];
    (void)CLOCK_SYS_GetFreq(instanceClkName, &uartSourceClock);

    /* Get the baud rate divider integer and fractional parts from registers */
    mantissa = LINFlexD_GetIntegerBaudRate(base);
    fraction = LINFlexD_GetFractionalBaudRate(base);

    /* Compute the baud rate based on protocol clock value */
    *baudrate = uartSourceClock / ((mantissa * DEFAULT_OSR) + (uint32_t)fraction);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_InstallRxCallback
 * Description   : This function installs a callback for UART receive.
 *
 * Implements    : LINFlexD_UART_DRV_InstallRxCallback_Activity
 *END**************************************************************************/
uart_callback_t LINFlexD_UART_DRV_InstallRxCallback(uint32_t instance,
                                                    uart_callback_t function,
                                                    void * callbackParam)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    linflexd_uart_state_t * uartState;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Save the previous callback and set the new one */
    uart_callback_t currentCallback = uartState->rxCallback;
    uartState->rxCallback = function;
    uartState->rxCallbackParam = callbackParam;

    return currentCallback;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_InstallTxCallback
 * Description   : This function installs a callback for UART transmit.
 *
 * Implements    : LINFlexD_UART_DRV_InstallTxCallback_Activity
 *END**************************************************************************/
uart_callback_t LINFlexD_UART_DRV_InstallTxCallback(uint32_t instance,
                                                    uart_callback_t function,
                                                    void * callbackParam)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    linflexd_uart_state_t * uartState;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Save the previous callback and set the new one */
    uart_callback_t currentCallback = uartState->txCallback;
    uartState->txCallback = function;
    uartState->txCallbackParam = callbackParam;

    return currentCallback;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_InstallErrorCallback
 * Description   : This function installs a callback for UART error cases.
 *
 * Implements    : LINFlexD_UART_DRV_InstallErrorCallback_Activity
 *END**************************************************************************/
uart_callback_t LINFlexD_UART_DRV_InstallErrorCallback(uint32_t instance,
                                                       uart_callback_t function,
                                                       void * callbackParam)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    linflexd_uart_state_t * uartState;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Save the previous callback and set the new one */
    uart_callback_t currentCallback = uartState->errorCallback;
    uartState->errorCallback = function;
    uartState->errorCallbackParam = callbackParam;

    return currentCallback;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_Init
 * Description   : This function initializes a LINFlexD instance for UART
 * operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, initialize the module to user defined settings and
 * default settings, enable the module-level interrupt to the core, and enable
 * the UART module transmitter and receiver.
 *
 * Implements    : LINFlexD_UART_DRV_Init_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_Init(uint32_t instance, linflexd_uart_state_t * uartStatePtr,
                                const linflexd_uart_user_config_t * uartUserConfig)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);
    DEV_ASSERT(uartStatePtr != NULL);
    DEV_ASSERT(uartUserConfig != NULL);

    status_t uartStatus;
    LINFlexD_Type * base;
    uint32_t idx;
    uint32_t uartSourceClock;
    clock_names_t instanceClkName;

    base = s_uartLINFlexDBase[instance];
    instanceClkName = s_uartLINFlexDClkNames[instance];

    /* Check if current instance is clock gated off. */
    (void)CLOCK_SYS_GetFreq(instanceClkName, &uartSourceClock);
    DEV_ASSERT(uartSourceClock != 0U);

#if !(FEATURE_LINFlexD_HAS_DMA_ENABLED)
    /* Check if an instance with no DMA support is configured in DMA mode */
    DEV_ASSERT(uartUserConfig->txTransferType != LINFlexD_UART_USING_DMA);
    DEV_ASSERT(uartUserConfig->rxTransferType != LINFlexD_UART_USING_DMA);
#endif /* FEATURE_LINFlexD_HAS_DMA_ENABLED */

    /* Clear the state struct for this instance. */
    uint8_t *clearStructPtr = (uint8_t *)uartStatePtr;
    for (idx = 0; idx < sizeof(linflexd_uart_state_t); idx++)
    {
        clearStructPtr[idx] = 0;
    }

    /* Save runtime structure pointer.*/
    s_uartLINFlexDStatePtr[instance] = uartStatePtr;

    /* Request init mode and wait until the mode entry is complete */
    LINFlexD_EnterInitMode(base);
    while (LINFlexD_GetLinState(base) != LINFlexD_STATE_INIT_MODE) {}

    /* Set UART mode */
    LINFlexD_SetMode(base, LINFlexD_UART_MODE);

    /* Set the baud rate */
    uartStatus = LINFlexD_UART_DRV_SetBaudRate(instance, uartUserConfig->baudRate);
    if (uartStatus != STATUS_SUCCESS)
    {
        return uartStatus;
    }

    /* Set word length */
    LINFlexD_SetUartWordLength(base, uartUserConfig->wordLength);
    LINFlexD_SetTxDataFieldLength(base, (uint8_t)((uint8_t)uartUserConfig->wordLength >> 1U));
    LINFlexD_SetRxDataFieldLength(base, (uint8_t)((uint8_t)uartUserConfig->wordLength >> 1U));
    uartStatePtr->wordLength = uartUserConfig->wordLength;

    /* Set parity */
    if (uartUserConfig->parityCheck)
    {
        LINFlexD_SetParityControl(base, true);
        LINFlexD_SetParityType(base, uartUserConfig->parityType);
    }
    else
    {
        LINFlexD_SetParityControl(base, false);
    }

    /* Set stop bits count */
    LINFlexD_SetRxStopBitsCount(base, uartUserConfig->stopBitsCount);
#if (FEATURE_LINFlexD_HAS_DIFFERENT_MEM_MAP)
    LINFlexD_SetTxStopBitsCount(base, uartUserConfig->stopBitsCount, s_LINFlexDInstHasFilters[instance]);
#else
    LINFlexD_SetTxStopBitsCount(base, uartUserConfig->stopBitsCount, true);
#endif

    /* Enable FIFO for DMA based communication, or buffer mode for interrupt based communication */
    if (uartUserConfig->txTransferType == LINFlexD_UART_USING_DMA)
    {
        LINFlexD_SetTxMode(base, LINFlexD_UART_RXTX_FIFO_MODE);
    }
    else
    {
        LINFlexD_SetTxMode(base, LINFlexD_UART_RXTX_BUFFER_MODE);
    }
    if (uartUserConfig->rxTransferType == LINFlexD_UART_USING_DMA)
    {
        LINFlexD_SetRxMode(base, LINFlexD_UART_RXTX_FIFO_MODE);
    }
    else
    {
        LINFlexD_SetRxMode(base, LINFlexD_UART_RXTX_BUFFER_MODE);
    }
 
    LINFlexD_SetMonitorIdleState(base, true); 

    LINFlexD_SetDisableTimeout(base, true);

    /* Enter normal mode */
    LINFlexD_EnterNormalMode(base);

    /* initialize last driver operation status */
    uartStatePtr->transmitStatus = STATUS_SUCCESS;
    uartStatePtr->receiveStatus = STATUS_SUCCESS;

    /* Save the transfer type and DMA channels in driver state */
    uartStatePtr->txTransferType = uartUserConfig->txTransferType;
    uartStatePtr->rxTransferType = uartUserConfig->rxTransferType;
#if (FEATURE_LINFlexD_HAS_DMA_ENABLED)
    uartStatePtr->rxDMAChannel = uartUserConfig->rxDMAChannel;
    uartStatePtr->txDMAChannel = uartUserConfig->txDMAChannel;
#endif

    /* Initialize callback functions and parameters */
    uartStatePtr->rxCallback = NULL;
    uartStatePtr->txCallback = NULL;
    uartStatePtr->errorCallback = NULL;
    uartStatePtr->rxCallbackParam = NULL;
    uartStatePtr->txCallbackParam = NULL;
    uartStatePtr->errorCallbackParam = NULL;

    /* Create the synchronization objects */
    (void)OSIF_SemaCreate(&uartStatePtr->rxComplete, 0);
    (void)OSIF_SemaCreate(&uartStatePtr->txComplete, 0);

    /* Install UART handlers */
#if (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)
    INT_SYS_InstallHandler(s_uartLINFlexDRxIntVec[instance], g_uartLINFlexDRxIsr[instance], (isr_t*) 0);
    INT_SYS_InstallHandler(s_uartLINFlexDTxIntVec[instance], g_uartLINFlexDTxIsr[instance], (isr_t*) 0);
    INT_SYS_InstallHandler(s_uartLINFlexDErrIntVec[instance], g_uartLINFlexDErrIsr[instance], (isr_t*) 0);
#elif (FEATURE_LINFlexD_ORED_INT_LINES)
    INT_SYS_InstallHandler(s_uartLINFlexDIntVec[instance], g_uartLINFlexDIsr[instance], (isr_t*) 0);
#endif

    /* Enable LINFlexD interrupts */
#if (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)
    INT_SYS_EnableIRQ(s_uartLINFlexDRxIntVec[instance]);
    INT_SYS_EnableIRQ(s_uartLINFlexDTxIntVec[instance]);
    INT_SYS_EnableIRQ(s_uartLINFlexDErrIntVec[instance]);
#elif (FEATURE_LINFlexD_ORED_INT_LINES)
    INT_SYS_EnableIRQ(s_uartLINFlexDIntVec[instance]);
#endif

    /* Enable error interrupts */
    LINFlexD_SetInterruptMode(base, LINFlexD_FRAME_ERROR_INT, true);
    LINFlexD_SetInterruptMode(base, LINFlexD_BUFFER_OVERRUN_INT, true);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_Deinit
 * Description   : This function shuts down the UART by disabling interrupts and
 *                 transmitter/receiver.
 *
 * Implements    : LINFlexD_UART_DRV_Deinit_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_Deinit(uint32_t instance)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    clock_names_t instanceClkName = s_uartLINFlexDClkNames[instance];
    uint32_t uartSourceClock;
    LINFlexD_Type * base;
    const linflexd_uart_state_t * uartState;

    base = s_uartLINFlexDBase[instance];
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    (void)CLOCK_SYS_GetFreq(instanceClkName, &uartSourceClock);

    /* Check if current instance is already de-initialized or is gated.*/
    DEV_ASSERT(s_uartLINFlexDStatePtr[instance] != NULL);
    DEV_ASSERT(uartSourceClock != 0U);

    /* Disable error interrupts */
    LINFlexD_SetInterruptMode(base, LINFlexD_FRAME_ERROR_INT, false);
    LINFlexD_SetInterruptMode(base, LINFlexD_BUFFER_OVERRUN_INT, false);

    /* Restore default handlers */
#if (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)
    INT_SYS_InstallHandler(s_uartLINFlexDRxIntVec[instance], DefaultISR, (isr_t*) 0);
    INT_SYS_InstallHandler(s_uartLINFlexDTxIntVec[instance], DefaultISR, (isr_t*) 0);
    INT_SYS_InstallHandler(s_uartLINFlexDErrIntVec[instance], DefaultISR, (isr_t*) 0);
#elif (FEATURE_LINFlexD_ORED_INT_LINES)
    INT_SYS_InstallHandler(s_uartLINFlexDIntVec[instance], DefaultISR, (isr_t*) 0);
#endif

    /* Disable LINFlexD interrupts */
#if (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)
    INT_SYS_DisableIRQ(s_uartLINFlexDRxIntVec[instance]);
    INT_SYS_DisableIRQ(s_uartLINFlexDTxIntVec[instance]);
    INT_SYS_DisableIRQ(s_uartLINFlexDErrIntVec[instance]);
#elif (FEATURE_LINFlexD_ORED_INT_LINES)
    INT_SYS_DisableIRQ(s_uartLINFlexDIntVec[instance]);
#endif

    /* Destroy the synchronization objects */
    (void)OSIF_SemaDestroy(&uartState->rxComplete);
    (void)OSIF_SemaDestroy(&uartState->txComplete);

    /* Clear the saved pointer to the state structure */
    s_uartLINFlexDStatePtr[instance] = NULL;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_SendDataBlocking
 * Description   : This function sends data using LINFlexD module in UART mode
 * with blocking method.
 *
 * Implements    : LINFlexD_UART_DRV_SendDataBlocking_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_SendDataBlocking(uint32_t instance,
                                            const uint8_t * txBuff,
                                            uint32_t txSize,
                                            uint32_t timeout)
{
    DEV_ASSERT(txBuff != NULL);
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    linflexd_uart_state_t * uartState;
    status_t retVal;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];
    retVal = STATUS_SUCCESS;

    /* Indicates this is a blocking transaction. */
    uartState->isTxBlocking = true;

    DEV_ASSERT((uartState->txTransferType == LINFlexD_UART_USING_INTERRUPTS) ||
               (uartState->txTransferType == LINFlexD_UART_USING_DMA));

    if (uartState->txTransferType == LINFlexD_UART_USING_INTERRUPTS)
    {
        /* Start the transmission process using interrupts */
        retVal = LINFlexD_UART_DRV_StartSendUsingInterrupts(instance, txBuff, txSize);
    }
#if (FEATURE_LINFlexD_HAS_DMA_ENABLED)
    else
    {
        /* Start the transmission process using DMA */
        retVal = LINFlexD_UART_DRV_StartSendUsingDma(instance, txBuff, txSize);
    }
#endif

    if (retVal == STATUS_SUCCESS)
    {
        /* Wait until to transmit is complete. */
        retVal = OSIF_SemaWait(&uartState->txComplete, timeout);

        /* Finish the transmission if timeout expired */
        if (retVal == STATUS_TIMEOUT)
        {
            uartState->isTxBlocking = false;
            uartState->transmitStatus = STATUS_TIMEOUT;

            if (uartState->txTransferType == LINFlexD_UART_USING_INTERRUPTS)
            {
                LINFlexD_UART_DRV_CompleteSendUsingInterrupts(instance);
            }
#if (FEATURE_LINFlexD_HAS_DMA_ENABLED)
            else
            {
                LINFlexD_UART_DRV_CompleteSendUsingDma(((void *)instance), DMA_CHN_NORMAL);
            }
#endif
        }
    }

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_SendDataPolling
 * Description   : This function sends data using LINFlexD module in UART mode
 * with Polling method.
 *
 * Implements    : LINFlexD_UART_DRV_SendDataPolling_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_SendDataPolling(uint32_t instance,
                                            const uint8_t * txBuff,
                                            uint32_t txSize)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);
    DEV_ASSERT(txBuff != NULL);
    DEV_ASSERT(txSize > 0U);
    LINFlexD_Type * base;

    linflexd_uart_state_t * uartState;
    status_t retVal = STATUS_SUCCESS;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];
    base = s_uartLINFlexDBase[instance];
    /* Check the validity of the parameters */
    DEV_ASSERT(txSize > 0U);
    DEV_ASSERT((uartState->wordLength <= LINFlexD_UART_8_BITS) ||
               ((txSize & 1U) == 0U));
    /* Check it's not busy transmitting data from a previous function call */
    if (uartState->isTxBusy)
    {
        return STATUS_BUSY;
    }
    /* Initialize the module driver state structure */
    uartState->txBuff = txBuff;
    uartState->txSize = txSize;
    uartState->isTxBusy = true;
    uartState->transmitStatus = STATUS_BUSY;

    /* Enable the transmitter */
    LINFlexD_SetTransmitterState(base, true);

    LINFlexD_ClearStatusFlag(base, LINFlexD_UART_DATA_TRANSMITTED_FLAG);
    /* Transmit the first word */
    LINFlexD_UART_DRV_PutData(instance);
    while (uartState->txSize > 0U)
    {
        if (LINFlexD_GetStatusFlag(base, LINFlexD_UART_DATA_TRANSMITTED_FLAG))
        {
            /* Clear the flag */
            LINFlexD_ClearStatusFlag(base, LINFlexD_UART_DATA_TRANSMITTED_FLAG);
            /* Send data */
            LINFlexD_UART_DRV_PutData(instance);
        }
        if(LINFlexD_GetStatusFlag(base, (linflexd_uart_status_flag_t)(LINFlexD_UART_BUFFER_OVERRUN_FLAG |
                                                                      LINFlexD_UART_FRAME_ERROR_FLAG)))
        {
            /* abort the transmission */
            retVal = STATUS_ERROR;
            break;
        }

    }

    while(0 == LINFlexD_GetStatusFlag(base, LINFlexD_UART_DATA_TRANSMITTED_FLAG))
    {
        /* Wait until the last data is transmitted */
    }
    /* Disable the transmitter */
    LINFlexD_SetTransmitterState(base, false);
    uartState->isTxBusy = false;
    uartState->transmitStatus = retVal;

    return retVal;

}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_SendData
 * Description   : This function sends data using LINFlexD module in UART mode
 * with non-blocking method.
 *
 * Implements    : LINFlexD_UART_DRV_SendData_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_SendData(uint32_t instance,
                                    const uint8_t * txBuff,
                                    uint32_t txSize)
{
    status_t retVal;
    DEV_ASSERT(txBuff != NULL);
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    linflexd_uart_state_t * uartState;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Indicates this is a non-blocking transaction. */
    uartState->isTxBlocking = false;

    DEV_ASSERT((uartState->txTransferType == LINFlexD_UART_USING_INTERRUPTS) ||
                  (uartState->txTransferType == LINFlexD_UART_USING_DMA));

    if (uartState->txTransferType == LINFlexD_UART_USING_INTERRUPTS)
    {
        /* Start the transmission process using interrupts */
        retVal = LINFlexD_UART_DRV_StartSendUsingInterrupts(instance, txBuff, txSize);
    }
#if (FEATURE_LINFlexD_HAS_DMA_ENABLED)
    else
    {
       /* Start the transmission process using DMA */
       retVal = LINFlexD_UART_DRV_StartSendUsingDma(instance, txBuff, txSize);
    }
#endif
    /* Start the transmission process */
    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_GetTransmitStatus
 * Description   : This function returns whether the previous UART transmit has
 * finished. When performing non-blocking transmit, the user can call this
 * function to ascertain the state of the current transmission:
 * in progress (or busy) or complete (success). In addition, if the transmission
 * is still in progress, the user can obtain the number of words that have been
 * currently transferred.
 *
 * Implements    : LINFlexD_UART_DRV_GetTransmitStatus_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_GetTransmitStatus(uint32_t instance, uint32_t * bytesRemaining)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    const linflexd_uart_state_t * uartState;
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    if (bytesRemaining != NULL)
    {
        /* Fill in the number of bytes yet to be transferred and update the return value if needed */
        if (uartState->isTxBusy)
        {
            /* Fill in the bytes not transferred yet. */
            if (uartState->txTransferType == LINFlexD_UART_USING_INTERRUPTS)
            {
                /* In interrupt-based communication, the remaining bytes are retrieved
                 * from the state structure
                 */
                *bytesRemaining = uartState->txSize;
            }
#if (FEATURE_LINFlexD_HAS_DMA_ENABLED)
            else
            {
                /* In DMA-based communication, the remaining bytes are retrieved
                 * from the current DMA trigger loop count
                 */
                *bytesRemaining = DMA_DRV_GetRemainingTriggerIterationsCount(uartState->txDMAChannel);
            }
#endif
        }
        else
        {
            *bytesRemaining = 0;
        }
    }

    return uartState->transmitStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_AbortSendingData
 * Description   : This function terminates an non-blocking UART transmission
 * early. During a non-blocking UART transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 *
 * Implements    : LINFlexD_UART_DRV_AbortSendingData_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_AbortSendingData(uint32_t instance)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    linflexd_uart_state_t * uartState;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Check if a transfer is running. */
    if (!uartState->isTxBusy)
    {
        return STATUS_SUCCESS;
    }

    /* Update the tx status */
    uartState->transmitStatus = STATUS_UART_ABORTED;

    /* Stop the running transfer. */
    if (uartState->txTransferType == LINFlexD_UART_USING_INTERRUPTS)
    {
        LINFlexD_UART_DRV_CompleteSendUsingInterrupts(instance);
    }
#if (FEATURE_LINFlexD_HAS_DMA_ENABLED)
    else
    {
        LINFlexD_UART_DRV_CompleteSendUsingDma(((void *)instance), DMA_CHN_NORMAL);
    }
#endif

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_ReceiveDataBlocking
 * Description   : Retrieves data from the LINFlexD module in UART mode with
 * blocking method.
 *
 * Implements    : LINFlexD_UART_DRV_ReceiveDataBlocking_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_ReceiveDataBlocking(uint32_t instance,
                                               uint8_t * rxBuff,
                                               uint32_t rxSize,
                                               uint32_t timeout)
{
    DEV_ASSERT(rxBuff != NULL);
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    linflexd_uart_state_t * uartState;
    status_t retVal;

    retVal = STATUS_SUCCESS;
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Indicates this is a blocking transaction. */
    uartState->isRxBlocking = true;

    DEV_ASSERT((uartState->rxTransferType == LINFlexD_UART_USING_INTERRUPTS) ||
               (uartState->rxTransferType == LINFlexD_UART_USING_DMA));

    if (uartState->rxTransferType == LINFlexD_UART_USING_INTERRUPTS)
    {
        /* Start the reception process using interrupts */
        retVal = LINFlexD_UART_DRV_StartReceiveUsingInterrupts(instance, rxBuff, rxSize);
    }
#if (FEATURE_LINFlexD_HAS_DMA_ENABLED)
    else
    {
        /* Start the reception process using DMA */
        retVal = LINFlexD_UART_DRV_StartReceiveUsingDma(instance, rxBuff, rxSize);
    }
#endif

    if (retVal == STATUS_SUCCESS)
    {
        /* Wait until the reception is complete. */
        retVal = OSIF_SemaWait(&uartState->rxComplete, timeout);

        /* Finish the reception if timeout expired */
        if (retVal == STATUS_TIMEOUT)
        {
            uartState->isRxBlocking = false;
            uartState->receiveStatus = STATUS_TIMEOUT;

            if (uartState->rxTransferType == LINFlexD_UART_USING_INTERRUPTS)
            {
                LINFlexD_UART_DRV_CompleteReceiveUsingInterrupts(instance);
            }
#if (FEATURE_LINFlexD_HAS_DMA_ENABLED)
            else
            {
                LINFlexD_UART_DRV_CompleteReceiveUsingDma(((void *)instance), DMA_CHN_NORMAL);
            }
#endif
        }
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_ReceiveDataPolling
 * Description   : Retrieves data from the LINFlexD module in UART mode with
 * polling method.
 *
 * Implements    : LINFlexD_UART_DRV_ReceiveDataPolling_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_ReceiveDataPolling(uint32_t instance,
                                               uint8_t * rxBuff,
                                               uint32_t rxSize)
{
    DEV_ASSERT(rxBuff != NULL);
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    linflexd_uart_state_t * uartState;
    status_t retVal = STATUS_SUCCESS;
    LINFlexD_Type * base;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];
    base = s_uartLINFlexDBase[instance];
    /* Check the validity of the parameters */
    DEV_ASSERT(rxSize > 0U);
    DEV_ASSERT((uartState->wordLength <= LINFlexD_UART_8_BITS) ||
               ((rxSize & 1U) == 0U));

    /* Check driver is not busy receiving data from a previous asynchronous call */
    if (uartState->isRxBusy)
    {
        return STATUS_BUSY;
    }

    /* Initialize the module driver state struct to indicate transfer in progress
     * and with the buffer and byte count data. */
    uartState->isRxBusy = true;
    uartState->rxBuff = rxBuff;
    uartState->rxSize = rxSize;
    uartState->receiveStatus = STATUS_BUSY;

    /* Enable the receiver */
    LINFlexD_SetReceiverState(base, true);

    while (uartState->rxSize > 0U)
    {
        if (LINFlexD_GetStatusFlag(base, LINFlexD_UART_DATA_RECEPTION_COMPLETE_FLAG))
        {
            /* Retrieve the data */
            LINFlexD_UART_DRV_GetData(instance);
            /* Clear the flag */
            LINFlexD_ClearStatusFlag(base, LINFlexD_UART_DATA_RECEPTION_COMPLETE_FLAG);
            LINFlexD_ClearStatusFlag(base, LINFlexD_UART_MESSAGE_BUFFER_FULL_FLAG);
        }

        /* Check for errors on received data */
        if (LINFlexD_GetStatusFlag(base, LINFlexD_UART_FRAME_ERROR_FLAG))
        {
            retVal = STATUS_UART_FRAMING_ERROR;
            /* Clear the flag */
            LINFlexD_ClearStatusFlag(base, LINFlexD_UART_FRAME_ERROR_FLAG);
            break;
        }
        if (LINFlexD_GetStatusFlag(base, LINFlexD_UART_BUFFER_OVERRUN_FLAG))
        {
            retVal = STATUS_UART_RX_OVERRUN;
            /* Clear the flag */
            LINFlexD_ClearStatusFlag(base, LINFlexD_UART_BUFFER_OVERRUN_FLAG);
            break;
        }
    }

    uartState->isRxBusy = false;
    /* Disable the UART receiver */
    LINFlexD_SetReceiverState(base, false);
    /* clear receive flag and release MB */
    LINFlexD_ClearStatusFlag(base, (linflexd_uart_status_flag_t)(LINFlexD_UART_DATA_RECEPTION_COMPLETE_FLAG | 
                                   LINFlexD_UART_MESSAGE_BUFFER_FULL_FLAG));
    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_ReceiveData
 * Description   : Retrieves data from the LINFlexD module in UART mode with
 * non-blocking method.
 *
 * Implements    : LINFlexD_UART_DRV_ReceiveData_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_ReceiveData(uint32_t instance,
                                       uint8_t * rxBuff,
                                       uint32_t rxSize)
{
    DEV_ASSERT(rxBuff != NULL);
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    status_t retVal;
    linflexd_uart_state_t * uartState;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Indicates this is a non-blocking transaction. */
    uartState->isRxBlocking = false;

    DEV_ASSERT((uartState->rxTransferType == LINFlexD_UART_USING_INTERRUPTS) ||
               (uartState->rxTransferType == LINFlexD_UART_USING_DMA));

    if (uartState->rxTransferType == LINFlexD_UART_USING_INTERRUPTS)
    {
        /* Start the transmission process using interrupts */
        retVal = LINFlexD_UART_DRV_StartReceiveUsingInterrupts(instance, rxBuff, rxSize);
    }
#if (FEATURE_LINFlexD_HAS_DMA_ENABLED)
    else
    {
        /* Start the transmission process using interrupts */
        retVal = LINFlexD_UART_DRV_StartReceiveUsingDma(instance, rxBuff, rxSize);
    }
#endif

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_GetReceiveStatus
 * Description   : This function returns whether the previous UART receive is
 * complete. When performing a non-blocking receive, the user can call this
 * function to ascertain the state of the current receive progress: in progress
 * or complete. In addition, if the receive is still in progress, the user can
 * obtain the number of words that have not yet been received.
 *
 * Implements    : LINFlexD_UART_DRV_GetReceiveStatus_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_GetReceiveStatus(uint32_t instance, uint32_t * bytesRemaining)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    const linflexd_uart_state_t * uartState;
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    if (bytesRemaining != NULL)
    {
        if (uartState->isRxBusy)
        {
            /* Fill in the number of bytes yet to be received and update the return value if needed */
            if (uartState->rxTransferType == LINFlexD_UART_USING_INTERRUPTS)
            {
                /* In interrupt-based communication, the remaining bytes are retrieved
                 * from the state structure
                 */
                *bytesRemaining = uartState->rxSize;
            }
#if (FEATURE_LINFlexD_HAS_DMA_ENABLED)
            else
            {
                /* In DMA-based communication, the remaining bytes are retrieved
                 * from the current DMA trigger loop count
                 */
                 *bytesRemaining = DMA_DRV_GetRemainingTriggerIterationsCount(uartState->rxDMAChannel);
            }
#endif
        }
        else
        {
            *bytesRemaining = 0;
        }
    }

    return uartState->receiveStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_AbortReceivingData
 * Description   : Terminates a non-blocking receive early.
 *
 * Implements    : LINFlexD_UART_DRV_AbortReceivingData_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_AbortReceivingData(uint32_t instance)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    linflexd_uart_state_t * uartState;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Check if a transfer is running. */
    if (!uartState->isRxBusy)
    {
        return STATUS_SUCCESS;
    }

    /* Update the rx status */
    uartState->receiveStatus = STATUS_UART_ABORTED;

    /* Stop the running transfer. */
    if (uartState->rxTransferType == LINFlexD_UART_USING_INTERRUPTS)
    {
        LINFlexD_UART_DRV_CompleteReceiveUsingInterrupts(instance);
    }
#if (FEATURE_LINFlexD_HAS_DMA_ENABLED)
    else
    {
        LINFlexD_UART_DRV_CompleteReceiveUsingDma(((void *)instance), DMA_CHN_NORMAL);
    }
#endif

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_SetTxBuffer
 * Description   : Sets the driver internal reference to the tx buffer.
 *                 Can be called from the tx callback to provide a different
 *                 buffer for continuous transmission.
 *
 * Implements    : LINFlexD_UART_DRV_SetTxBuffer_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_SetTxBuffer(uint32_t instance,
                                       const uint8_t * txBuff,
                                       uint32_t txSize)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);
    DEV_ASSERT(txBuff != NULL);
    DEV_ASSERT(txSize > 0U);

    linflexd_uart_state_t * uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];
    uartState->txBuff = txBuff;
    uartState->txSize = txSize;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_SetRxBuffer
 * Description   : Sets the driver internal reference to the rx buffer.
 *                 Can be called from the rx callback to provide a different
 *                 buffer for continuous reception.
 *
 * Implements    : LINFlexD_UART_DRV_SetRxBuffer_Activity
 *END**************************************************************************/
status_t LINFlexD_UART_DRV_SetRxBuffer(uint32_t instance,
                                       uint8_t * rxBuff,
                                       uint32_t rxSize)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);
    DEV_ASSERT(rxBuff != NULL);
    DEV_ASSERT(rxSize > 0U);

    linflexd_uart_state_t * uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];
    uartState->rxBuff = rxBuff;
    uartState->rxSize = rxSize;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_RxIRQHandler
 * Description   : Rx interrupt handler for UART.
 * This handler uses the rx buffer stored in the state structure to receive
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *END**************************************************************************/
void LINFlexD_UART_DRV_RxIRQHandler(uint32_t instance)
{
    linflexd_uart_state_t * uartState;
    LINFlexD_Type * base;

    base = s_uartLINFlexDBase[instance];
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Exit if there is no reception in progress */
    if (!uartState->isRxBusy)
    {
        return;
    }

    /* Retrieve the data */
    LINFlexD_UART_DRV_GetData(instance);

    /* Check if this was the last byte in the current buffer */
    if (uartState->rxSize == 0U)
    {
        /* Invoke the callback when the buffer is finished;
         * Application can provide another buffer inside the callback by calling LINFlexD_UART_DRV_SetRxBuffer */
        if (uartState->rxCallback != NULL)
        {
            uartState->rxCallback(uartState, UART_EVENT_RX_FULL, uartState->rxCallbackParam);
        }
    }

    /* Finish reception if this was the last byte received */
    if (uartState->rxSize == 0U)
    {
        /* Complete transfer (disable rx logic) */
        LINFlexD_UART_DRV_CompleteReceiveUsingInterrupts(instance);
        LINFlexD_SetInterruptMode(base, LINFlexD_UART_TIMEOUT_ERROR_INT, false);

        /* Invoke callback if there is one */
        if (uartState->rxCallback != NULL)
        {
            uartState->rxCallback(uartState, UART_EVENT_END_TRANSFER, uartState->rxCallbackParam);
        }
    }
    else 
    {
        LINFlexD_ClearStatusFlag(base, LINFlexD_UART_TIMEOUT_FLAG);
        LINFlexD_SetInterruptMode(base, LINFlexD_UART_TIMEOUT_ERROR_INT, true);
    }

    /* Clear the flag */
    LINFlexD_ClearStatusFlag(base, LINFlexD_UART_DATA_RECEPTION_COMPLETE_FLAG);
    LINFlexD_ClearStatusFlag(base, LINFlexD_UART_MESSAGE_BUFFER_FULL_FLAG);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_TxIRQHandler
 * Description   : Tx interrupt handler for UART.
 * This handler uses the tx buffer stored in the state structure to transmit
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *END**************************************************************************/
void LINFlexD_UART_DRV_TxIRQHandler(uint32_t instance)
{
    linflexd_uart_state_t * uartState;
    LINFlexD_Type * base;

    base = s_uartLINFlexDBase[instance];
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Exit if there is no transmission in progress */
    if (!uartState->isTxBusy)
    {
        return;
    }

    /* Check if there are any more bytes to send */
    if (uartState->txSize > 0U)
    {
        /* Send data */
        LINFlexD_UART_DRV_PutData(instance);

        /* Clear the flag */
        LINFlexD_ClearStatusFlag(base, LINFlexD_UART_DATA_TRANSMITTED_FLAG);
    }
    else
    {
        /* Invoke the callback when the buffer is finished;
         * Application can provide another buffer inside the callback by calling LINFlexD_UART_DRV_SetTxBuffer */
        if (uartState->txCallback != NULL)
        {
            uartState->txCallback(uartState, UART_EVENT_TX_EMPTY, uartState->txCallbackParam);
        }

        /* If there is no more data to send, complete the transmission */
        if (uartState->txSize == 0U)
        {
            LINFlexD_UART_DRV_CompleteSendUsingInterrupts(instance);

            /* Call the callback to notify application that the transfer is complete */
            if (uartState->txCallback != NULL)
            {
                uartState->txCallback(uartState, UART_EVENT_END_TRANSFER, uartState->txCallbackParam);
            }

            /* Clear the flag */
            LINFlexD_ClearStatusFlag(base, LINFlexD_UART_DATA_TRANSMITTED_FLAG);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_ErrIRQHandler
 * Description   : Error interrupt handler for UART.
 * This handler calls the user callback to treat error conditions.
 *
 *END**************************************************************************/
void LINFlexD_UART_DRV_ErrIRQHandler(uint32_t instance)
{
    linflexd_uart_state_t * uartState;
    LINFlexD_Type * base;

    base = s_uartLINFlexDBase[instance];
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Update the reception status according to the error occurred */
    if (LINFlexD_GetStatusFlag(base, LINFlexD_UART_BUFFER_OVERRUN_FLAG))
    {
        /* Update the status */
        uartState->receiveStatus = STATUS_UART_RX_OVERRUN;
        /* Clear the flag */
        LINFlexD_ClearStatusFlag(base, LINFlexD_UART_BUFFER_OVERRUN_FLAG);
    }
    else if (LINFlexD_GetStatusFlag(base, LINFlexD_UART_FRAME_ERROR_FLAG))
    {
        /* Update the status */
        uartState->receiveStatus = STATUS_UART_FRAMING_ERROR;
        /* Clear the flag */
        LINFlexD_ClearStatusFlag(base, LINFlexD_UART_FRAME_ERROR_FLAG);
    }
    else
    {
        /* This branch should never be reached - avoid MISRA violations */
        uartState->receiveStatus = STATUS_ERROR;
    }

    /* Terminate the current reception */
    if (uartState->rxTransferType == LINFlexD_UART_USING_INTERRUPTS)
    {
        LINFlexD_UART_DRV_CompleteReceiveUsingInterrupts(instance);
    }
#if (FEATURE_LINFlexD_HAS_DMA_ENABLED)
    else
    {
        LINFlexD_UART_DRV_CompleteReceiveUsingDma(((void *)instance), DMA_CHN_NORMAL);
    }
#endif

    /* Invoke the callback, if any */
    if (uartState->errorCallback != NULL)
    {
        uartState->errorCallback(uartState, UART_EVENT_ERROR, uartState->errorCallbackParam);
    }
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_RxTOHandler
 * Description   : Interrupt handler for UART IDLE.
 *
 *END**************************************************************************/
void LINFlexD_UART_DRV_RxTOHandler(uint32_t instance)
{
    linflexd_uart_state_t * uartState;
    LINFlexD_Type * base;

    base = s_uartLINFlexDBase[instance];
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Exit if there is no reception in progress */
    if (!uartState->isRxBusy)
    {
        return;
    }

    /* Invoke callback if there is one */
    if (uartState->rxCallback != NULL)
    {
        uartState->rxCallback(uartState, UART_EVENT_TIMEOUT, uartState->rxCallbackParam);
    }

    /* Complete transfer (disable rx logic) */
    LINFlexD_UART_DRV_CompleteReceiveUsingInterrupts(instance);

    /* Clear the flag */
    LINFlexD_ClearStatusFlag(base, LINFlexD_UART_TIMEOUT_FLAG);
    base->LINIER &= ~LINFlexD_LINIER_TOIE(1U);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_IRQHandler
 * Description   : Interrupt handler for UART.
 * This handler uses the buffers stored in the state structure to transfer
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *END**************************************************************************/
void LINFlexD_UART_DRV_IRQHandler(uint32_t instance)
{
    const LINFlexD_Type * base;

    base = s_uartLINFlexDBase[instance];

    /* Handle the error interrupts when error interrupt triggered */
    if(LINFlexD_GetStatusFlag(base, (linflexd_uart_status_flag_t)(LINFlexD_UART_BUFFER_OVERRUN_FLAG | 
                                    LINFlexD_UART_FRAME_ERROR_FLAG)))
    {
        LINFlexD_UART_DRV_ErrIRQHandler(instance);
        return;
    }

    /* Handle receive data full interrupt */
    if (LINFlexD_IsInterruptEnabled(base, LINFlexD_DATA_RECEPTION_COMPLETE_INT))
    {
        if (LINFlexD_GetStatusFlag(base, LINFlexD_UART_DATA_RECEPTION_COMPLETE_FLAG))
        {
            LINFlexD_UART_DRV_RxIRQHandler(instance);
        }
    }

    /* Handle transmitter data register empty interrupt */
    if (LINFlexD_IsInterruptEnabled(base, LINFlexD_DATA_TRANSMITTED_INT))
    {
        if (LINFlexD_GetStatusFlag(base, LINFlexD_UART_DATA_TRANSMITTED_FLAG))
        {
            LINFlexD_UART_DRV_TxIRQHandler(instance);
        }
    }

    if (LINFlexD_IsInterruptEnabled(base, LINFlexD_UART_TIMEOUT_ERROR_INT))
    {
        if (LINFlexD_GetStatusFlag(base, LINFlexD_UART_TIMEOUT_FLAG))
        {
            LINFlexD_UART_DRV_RxTOHandler(instance);
        }
    }

}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_StartSendUsingInterrupts
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static status_t LINFlexD_UART_DRV_StartSendUsingInterrupts(uint32_t instance,
                                                           const uint8_t * txBuff,
                                                           uint32_t txSize)
{
    LINFlexD_Type * base;
    linflexd_uart_state_t * uartState;

    base = s_uartLINFlexDBase[instance];
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Check it's not busy transmitting data from a previous function call */
    if (uartState->isTxBusy)
    {
        return STATUS_BUSY;
    }

    DEV_ASSERT(txSize > 0U);

    /* Initialize the module driver state structure */
    uartState->txBuff = txBuff;
    uartState->txSize = txSize;
    uartState->isTxBusy = true;
    uartState->transmitStatus = STATUS_BUSY;

    /* Enable the transmitter */
    LINFlexD_SetTransmitterState(base, true);

    /* Clear the tx empty flag to make sure the transmission of the first byte
     * doesn't occur right after enabling the tx interrupt
     */
    LINFlexD_ClearStatusFlag(base, LINFlexD_UART_DATA_TRANSMITTED_FLAG);

    /* Enable transmission complete interrupt */
    LINFlexD_SetInterruptMode(base, LINFlexD_DATA_TRANSMITTED_INT, true);

    /* Transmit the first word */
    LINFlexD_UART_DRV_PutData(instance);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_StartReceiveUsingInterrupts
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static status_t LINFlexD_UART_DRV_StartReceiveUsingInterrupts(uint32_t instance,
                                                              uint8_t * rxBuff,
                                                              uint32_t rxSize)
{
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);
    DEV_ASSERT(rxBuff != NULL);

    linflexd_uart_state_t * uartState;
    LINFlexD_Type * base;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];
    base = s_uartLINFlexDBase[instance];

    /* Check it's not busy receiving data from a previous function call */
    if ((uartState->isRxBusy) && (!uartState->rxCallback))
    {
        return STATUS_BUSY;
    }

    DEV_ASSERT(rxSize > 0U);

    /* Initialize the module driver state struct to indicate transfer in progress
     * and with the buffer and byte count data. */
    uartState->isRxBusy = true;
    uartState->rxBuff = rxBuff;
    uartState->rxSize = rxSize;
    uartState->receiveStatus = STATUS_BUSY;

    /* Enable the receiver */
    LINFlexD_SetReceiverState(base, true);

    /* Enable receive data full interrupt */
    LINFlexD_SetInterruptMode(base, LINFlexD_DATA_RECEPTION_COMPLETE_INT, true);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_CompleteSendUsingInterrupts
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LINFlexD_UART_DRV_CompleteSendUsingInterrupts(uint32_t instance)
{
    LINFlexD_Type * base;
    linflexd_uart_state_t * uartState;

    base = s_uartLINFlexDBase[instance];
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Disable transmission complete interrupt */
    LINFlexD_SetInterruptMode(base, LINFlexD_DATA_TRANSMITTED_INT, false);

    /* Disable the transmitter */
    LINFlexD_SetTransmitterState(base, false);

    /* Signal the synchronous completion object. */
    if (uartState->isTxBlocking)
    {
        (void)OSIF_SemaPost(&uartState->txComplete);
    }

    /* Update the information of the module driver state */
    uartState->isTxBusy = false;

    /* If the current transmission hasn't been aborted, update the status */
    if (uartState->transmitStatus == STATUS_BUSY)
    {
        uartState->transmitStatus = STATUS_SUCCESS;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_CompleteReceiveUsingInterrupts
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LINFlexD_UART_DRV_CompleteReceiveUsingInterrupts(uint32_t instance)
{
    linflexd_uart_state_t * uartState;
    LINFlexD_Type * base;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];
    base = s_uartLINFlexDBase[instance];

    /* Disable receive data full interrupt. */
    LINFlexD_SetInterruptMode(base, LINFlexD_DATA_RECEPTION_COMPLETE_INT, false);

    /* Disable the receiver */
    LINFlexD_SetReceiverState(base, false);

    /* Signal the synchronous completion object. */
    if (uartState->isRxBlocking)
    {
        (void)OSIF_SemaPost(&uartState->rxComplete);
    }

    /* Update the information of the module driver state */
    uartState->isRxBusy = false;

    /* If the current reception hasn't been aborted and no error occurred, update the status */
    if (uartState->receiveStatus == STATUS_BUSY)
    {
        uartState->receiveStatus = STATUS_SUCCESS;
    }
}

#if (FEATURE_LINFlexD_HAS_DMA_ENABLED)
/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_StartSendDataUsingDma
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data using DMA transfers.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static status_t LINFlexD_UART_DRV_StartSendUsingDma(uint32_t instance,
                                                    const uint8_t * txBuff,
                                                    uint32_t txSize)
{
    LINFlexD_Type * base;
    linflexd_uart_state_t * uartState;

    base = s_uartLINFlexDBase[instance];
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Check it's not busy transmitting data from a previous function call */
    if (uartState->isTxBusy)
    {
        return STATUS_BUSY;
    }

    /* Check the validity of the parameters */
    DEV_ASSERT(txSize > 0U);
    if(!((uartState->wordLength == LINFlexD_UART_7_BITS) || (uartState->wordLength == LINFlexD_UART_8_BITS)))
    {
        /* The size of the buffer should be an even number for DMA transfers with 15/16 bits word length */
        DEV_ASSERT((txSize & 1U) == 0U);
    }

    /* Update state structure */
    uartState->txBuff = txBuff;
    uartState->txSize = 0U;
    uartState->isTxBusy = true;
    uartState->transmitStatus = STATUS_BUSY;

    /* Configure the transfer control descriptor for the DMA channel */
    if((uartState->wordLength == LINFlexD_UART_7_BITS) || (uartState->wordLength == LINFlexD_UART_8_BITS))
    {
        (void)DMA_DRV_ConfigMultiBlockTransfer(uartState->txDMAChannel, DMA_TRANSFER_MEM2PERIPH, (uint32_t)txBuff,
                                                (uint32_t)(&base->DATA.DATA8[0]), DMA_TRANSFER_SIZE_1B,
                                                1U, txSize, true);
    }
    else
    {
        (void)DMA_DRV_ConfigMultiBlockTransfer(uartState->txDMAChannel, DMA_TRANSFER_MEM2PERIPH, (uint32_t)txBuff,
                                                (uint32_t)(&base->DATA.DATA16[0]), DMA_TRANSFER_SIZE_2B,
                                                2U, txSize >> 1U, true);
    }

    /* Call driver function to end the transmission when the DMA transfer is done */
    (void)DMA_DRV_InstallCallback(uartState->txDMAChannel,
                                   (dma_callback_t)(LINFlexD_UART_DRV_CompleteSendUsingDma),
                                   (void*)(instance));

    /* Start the DMA channel */
    (void)DMA_DRV_StartChannel(uartState->txDMAChannel);

    /* Enable the transmitter */
    LINFlexD_SetTransmitterState(base, true);

    /* Enable tx DMA requests for the current instance */
#if (FEATURE_LINFlexD_HAS_DIFFERENT_MEM_MAP)
    if (s_LINFlexDInstHasFilters[instance])
    {
        base->DMATXE = 1U;
    }
    else
    {
        ((LINFlexD_0IFCR_Type *)base)->DMATXE = 1U;
    }
#else
    base->DMATXE = 1U;
#endif

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_StartReceiveDataUsingDma
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data using DMA transfers.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static status_t LINFlexD_UART_DRV_StartReceiveUsingDma(uint32_t instance,
                                                       uint8_t * rxBuff,
                                                       uint32_t rxSize)
{
    LINFlexD_Type * base;
    linflexd_uart_state_t * uartState;

    base = s_uartLINFlexDBase[instance];
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Check it's not busy transmitting data from a previous function call */
    if (uartState->isRxBusy)
    {
        return STATUS_BUSY;
    }

    DEV_ASSERT(rxSize > 0U);
    if(!((uartState->wordLength == LINFlexD_UART_7_BITS) || (uartState->wordLength == LINFlexD_UART_8_BITS)))
    {
           /* The size of the buffer should be an even number for DMA transfers with 15/16 bits word length */
           DEV_ASSERT((rxSize & 1U) == 0U);
    }

    /* Update the state structure */
    uartState->rxBuff = rxBuff;
    uartState->rxSize = 0U;
    uartState->isRxBusy = true;
    uartState->receiveStatus = STATUS_BUSY;

    /* Configure the transfer control descriptor for the DMA channel */
    if((uartState->wordLength == LINFlexD_UART_7_BITS) || (uartState->wordLength == LINFlexD_UART_8_BITS))
    {
        (void)DMA_DRV_ConfigMultiBlockTransfer(uartState->rxDMAChannel, DMA_TRANSFER_PERIPH2MEM,
                                (uint32_t)(&base->DATA.DATA8[4]), (uint32_t)rxBuff, DMA_TRANSFER_SIZE_1B,
                                1U, rxSize, true);
    }
    else
    {
        (void)DMA_DRV_ConfigMultiBlockTransfer(uartState->rxDMAChannel, DMA_TRANSFER_PERIPH2MEM,
                                (uint32_t)(&base->DATA.DATA16[2]), (uint32_t)rxBuff, DMA_TRANSFER_SIZE_2B,
                                2U, rxSize >> 1U, true);
    }

    /* Call driver function to end the reception when the DMA transfer is done */
    (void)DMA_DRV_InstallCallback(uartState->rxDMAChannel,
                                   (dma_callback_t)(LINFlexD_UART_DRV_CompleteReceiveUsingDma),
                                   (void*)(instance));

    /* Start the DMA channel */
    (void)DMA_DRV_StartChannel(uartState->rxDMAChannel);

    /* Flush the rx FIFO to discard any junk data received while the driver was idle */
    LINFlexD_UART_DRV_FlushRxFifo(base);

    /* Enable the receiver */
    LINFlexD_SetReceiverState(base, true);

    /* Enable rx DMA requests for the current instance */
#if (FEATURE_LINFlexD_HAS_DIFFERENT_MEM_MAP)
    if (s_LINFlexDInstHasFilters[instance])
    {
        base->DMARXE = 1U;
    }
    else
    {
        ((LINFlexD_0IFCR_Type *)base)->DMARXE = 1U;
    }
#else
    base->DMARXE = 1U;
#endif

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_CompleteSendDataUsingDma
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the DMA requests. This is a callback for DMA trigger loop
 * completion, so it must match the DMA callback signature.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LINFlexD_UART_DRV_CompleteSendUsingDma(void * parameter, dma_chn_status_t status)
{
    (void)status;

    uint32_t instance;
    LINFlexD_Type * base;
    linflexd_uart_state_t * uartState;

    instance = ((uint32_t)parameter);
    base = s_uartLINFlexDBase[instance];
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Invoke the callback when the buffer is finished;
     * Application can provide another buffer inside the callback by calling LINFlexD_UART_DRV_SetTxBuffer */
    if (uartState->transmitStatus == STATUS_BUSY)
    {
        if (uartState->txCallback != NULL)
        {
            /* Pass the state structure as parameter for internal information retrieval */
            uartState->txCallback(uartState, UART_EVENT_TX_EMPTY, uartState->txCallbackParam);
        }
    }

    /* If the callback has updated the tx buffer, update the DMA descriptor to continue the transfer;
     * otherwise, stop the current transfer.
     */
    if (uartState->txSize > 0U)
    {
        /* Set the source address and the number of transfer loops (bytes to be transfered) */
        DMA_DRV_SetSrcAddr(uartState->txDMAChannel, (uint32_t)(uartState->txBuff));
        DMA_DRV_SetTriggerLoopIterationCount(uartState->txDMAChannel, uartState->txSize);

        /* Now that this tx is set up, clear remaining bytes count */
        uartState->txSize = 0U;

        /* Re-start the channel */
        (void)DMA_DRV_StartChannel(uartState->txDMAChannel);
    }
    else
    {
        /* Disable tx DMA requests for the current instance */
    #if (FEATURE_LINFlexD_HAS_DIFFERENT_MEM_MAP)
        if (s_LINFlexDInstHasFilters[instance])
        {
            base->DMATXE = 0U;
        }
        else
        {
            ((LINFlexD_0IFCR_Type *)base)->DMATXE = 0U;
        }
    #else
        base->DMATXE = 0U;
    #endif

        /* Disable the transmitter */
        LINFlexD_SetTransmitterState(base, false);

        /* Release the DMA channel */
        (void)DMA_DRV_StopChannel(uartState->txDMAChannel);

        /* Signal the synchronous completion object. */
        if (uartState->isTxBlocking)
        {
            (void)OSIF_SemaPost(&uartState->txComplete);
        }

        /* Update the busy flag */
        uartState->isTxBusy = false;

        /* If the current reception hasn't been aborted, update the status */
        if (uartState->transmitStatus == STATUS_BUSY)
        {
            uartState->transmitStatus = STATUS_SUCCESS;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_CompleteReceiveDataUsingDma
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the DMA requests. This is a callback for DMA trigger loop
 * completion, so it must match the DMA callback signature.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LINFlexD_UART_DRV_CompleteReceiveUsingDma(void * parameter, dma_chn_status_t status)
{
    (void)status;

    uint32_t instance;
    LINFlexD_Type * base;
    linflexd_uart_state_t * uartState;

    instance = ((uint32_t)parameter);
    base = s_uartLINFlexDBase[instance];
    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];

    /* Release the DMA channel */
    (void)DMA_DRV_StopChannel(uartState->rxDMAChannel);

    /* Invoke the callback when the buffer is finished */
    if (uartState->receiveStatus == STATUS_BUSY)
    {
        /* Application can provide another buffer inside the callback by calling LINFlexD_UART_DRV_SetRxBuffer */
        if (uartState->rxCallback != NULL)
        {
            uartState->rxCallback(uartState, UART_EVENT_RX_FULL, uartState->rxCallbackParam);
        }
    }

    /* If the callback has updated the rx buffer, update the DMA descriptor to continue the transfer;
     * otherwise, stop the current transfer.
     */
    if (uartState->rxSize > 0U)
    {
        /* Set the source address and the number of transfer loops (bytes to be transfered) */
        DMA_DRV_SetDestAddr(uartState->rxDMAChannel, (uint32_t)(uartState->rxBuff));
        DMA_DRV_SetTriggerLoopIterationCount(uartState->rxDMAChannel, uartState->rxSize);

        /* Now that this rx is set up, clear remaining bytes count */
        uartState->rxSize = 0U;

        /* Re-start the channel */
        (void)DMA_DRV_StartChannel(uartState->rxDMAChannel);
    }
    else
    {
        /* Disable rx DMA requests for the current instance */
    #if (FEATURE_LINFlexD_HAS_DIFFERENT_MEM_MAP)
        if (s_LINFlexDInstHasFilters[instance])
        {
            base->DMARXE = 0U;
        }
        else
        {
            ((LINFlexD_0IFCR_Type *)base)->DMARXE = 0U;
        }
    #else
        base->DMARXE = 0U;
    #endif

        /* Disable the receiver */
        LINFlexD_SetReceiverState(base, false);

        /* Signal the synchronous completion object. */
        if (uartState->isRxBlocking)
        {
            (void)OSIF_SemaPost(&uartState->rxComplete);
        }

        /* Update the information of the module driver state */
        uartState->isRxBusy = false;

        /* If the current reception hasn't been aborted, update the status and call the callback */
        if (uartState->receiveStatus == STATUS_BUSY)
        {
            uartState->receiveStatus = STATUS_SUCCESS;

            /* Call the callback to notify application that the transfer is complete */
            if (uartState->rxCallback != NULL)
            {
                uartState->rxCallback(uartState, UART_EVENT_END_TRANSFER, uartState->rxCallbackParam);
            }
        }
    }
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_PutData
 * Description   : Write data to the buffer register, according to configured
 * word length.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LINFlexD_UART_DRV_PutData(uint32_t instance)
{
    linflexd_uart_state_t * uartState;
    LINFlexD_Type * base;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];
    base = s_uartLINFlexDBase[instance];

    if((uartState->wordLength == LINFlexD_UART_7_BITS) || (uartState->wordLength == LINFlexD_UART_8_BITS))
    {
        /* Transmit the data */
        LINFlexD_SetTxDataBuffer1Byte(base, *(uartState->txBuff));
        /* Update the state structure */
        ++uartState->txBuff;
        --uartState->txSize;
    }
    else
    {
        /* Transmit the data and update state structure */
        if(uartState->txSize == 1U)
        {
            LINFlexD_SetTxDataBuffer2Bytes(base, (uint16_t)(*uartState->txBuff));
            ++uartState->txBuff;
            --uartState->txSize;
        }
        else
        {
            LINFlexD_SetTxDataBuffer2Bytes(base, *((const uint16_t*)uartState->txBuff));
            /* Move the pointer twice */
            ++uartState->txBuff;
            ++uartState->txBuff;
            uartState->txSize -= 2U;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_GetData
 * Description   : Read data from the buffer register, according to configured
 * word length.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LINFlexD_UART_DRV_GetData(uint32_t instance)
{
    linflexd_uart_state_t * uartState;
    const LINFlexD_Type * base;

    uartState = (linflexd_uart_state_t *)s_uartLINFlexDStatePtr[instance];
    base = s_uartLINFlexDBase[instance];

    if((uartState->wordLength == LINFlexD_UART_7_BITS) || (uartState->wordLength == LINFlexD_UART_8_BITS))
    {
        /* Get the data */
        *(uartState->rxBuff) = LINFlexD_GetRxDataBuffer1Byte(base);
        /* Update the state structure */
        ++uartState->rxBuff;
        --uartState->rxSize;
    }
    else
    {
        /* Get the data and update state structure */
        if(uartState->rxSize == 1U)
        {
            *(uartState->rxBuff) = (uint8_t)(LINFlexD_GetRxDataBuffer2Bytes(base));
            ++uartState->rxBuff;
            --uartState->rxSize;
        }
        else
        {
            *((uint16_t*)(uartState->rxBuff)) = LINFlexD_GetRxDataBuffer2Bytes(base);
            /* Move the pointer twice */
            ++uartState->rxBuff;
            ++uartState->rxBuff;
            uartState->rxSize -= 2U;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_FlushRxFifo
 * Description   : Flushes the rx FIFO.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LINFlexD_UART_DRV_FlushRxFifo(const LINFlexD_Type *base)
{
    uint16_t dummy;

    volatile const uint8_t *fifoBase;

    /* Get the address of the FIFO */
    fifoBase = (volatile const uint8_t *)(&(base->DATA.DATA32[1]));

    /* Four dummy reads, to flush the FIFO contents */
    dummy = (uint16_t)(*fifoBase);
    dummy = (uint16_t)(*fifoBase);
    dummy = (uint16_t)(*fifoBase);
    dummy = (uint16_t)(*fifoBase);
    (void)dummy;
}
/*******************************************************************************
 * EOF
 ******************************************************************************/

