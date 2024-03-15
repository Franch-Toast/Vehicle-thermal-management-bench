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
 * @file linflexd_lin_driver.c
 *
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "linflexd_lin_driver.h"
#include "linflexd_lin_irq.h"
#include "linflexd_hw_access.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Array of pointers to LINFlexD driver runtime state structures */
static linflexd_state_t * s_LINFlexDStatePtr[LINFlexD_INSTANCE_COUNT] = {NULL};

/* Table to save LINFlexD user config structure pointers */
static linflexd_user_config_t * s_LINFlexDUserconfigPtr[LINFlexD_INSTANCE_COUNT] = {NULL};

/*! @brief Table of base addresses for LINFlexD instances. */
static LINFlexD_Type * const s_LINFlexDBase[LINFlexD_INSTANCE_COUNT] = LINFlexD_BASE_PTRS;

static const clock_names_t s_LINFlexDClkName[LINFlexD_INSTANCE_COUNT] = LINFlexD_CLOCK_NAMES;

#if (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)
/*! @brief Tables to save LINFlexD IRQ vectors defined in the header file */
static const IRQn_Type s_LINFlexDRxIntVec[LINFlexD_INSTANCE_COUNT] = LINFlexD_RX_IRQS;
static const IRQn_Type s_LINFlexDTxIntVec[LINFlexD_INSTANCE_COUNT] = LINFlexD_TX_IRQS;
static const IRQn_Type s_LINFlexDErrIntVec[LINFlexD_INSTANCE_COUNT] = LINFlexD_ERR_IRQS;
#elif (FEATURE_LINFlexD_ORED_INT_LINES)
/*! @brief Table to save LINFlexD IRQ vectors defined in the header file */
static const IRQn_Type s_LINFlexDIntVec[LINFlexD_INSTANCE_COUNT] = LINFlexD_IRQS;
#endif

/*******************************************************************************
 * Internal Functions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_Init
 * Description   : This function initializes a LIN Hardware Interface for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, ungate the clock to LIN Hardware Interface, initialize the
 * module to user defined settings and default settings, configure the IRQ state
 * structure and enable the module-level interrupt to the core, and enable the
 * LIN Hardware Interface transmitter and receiver.
 * The following is an example of how to set up the linflexd_state_t and the
 * linflexd_user_config_t parameters and how to call the LINFlexD_DRV_Init function
 * by passing in these parameters:
 *    linflexd_user_config_t linUserConfig
 *    linUserConfig.baudRate = 9600
 *    linUserConfig.nodeFunction = SLAVE
 *    linUserConfig.autobaudEnable = true
 *    linflexd_state_t linState
 *    LINFlexD_DRV_Init(instance, (linflexd_user_config_t *) &linUserConfig, (linflexd_state_t *) &linState)
 *
 * Implements    : LINFlexD_DRV_Init_Activity
 *END**************************************************************************/
status_t LINFlexD_DRV_Init(uint32_t instance,
                      linflexd_user_config_t * linUserConfig,
                      linflexd_state_t * linCurrentState)
{
    /* Assert parameters. */
    DEV_ASSERT(linUserConfig && linCurrentState);
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    uint32_t linSourceClockFreq = 0U;
    status_t retVal = STATUS_SUCCESS;

    /* Get base address of the UART instance. */
    LINFlexD_Type * base = s_LINFlexDBase[instance];

    /* Get the LIN clock as configured in the clock manager */
    (void)CLOCK_SYS_GetFreq(s_LINFlexDClkName[instance], &linSourceClockFreq);

    /* Check if current instance is clock gated off. */
    DEV_ASSERT(linSourceClockFreq > 0U);

    /* Check if current instance is already initialized. */
    DEV_ASSERT(s_LINFlexDStatePtr[instance] == NULL);

    /* Save runtime structure pointer. */
    s_LINFlexDStatePtr[instance] = linCurrentState;

    /* Save LIN user config structure pointer. */
    s_LINFlexDUserconfigPtr[instance] = linUserConfig;

    /* Clear linSourceClockFreq value */
    linCurrentState->linSourceClockFreq = linSourceClockFreq;

    /* Create txCompleted and rxCompleted semaphores as counting, with init value is 0 */
    if (OSIF_SemaCreate(&linCurrentState->completed, 0) != STATUS_SUCCESS)
    {
        retVal = STATUS_ERROR;
    }
    else
    {
        /* Request init mode and wait until the mode entry is complete */
        LINFlexD_EnterInitMode(base);
        while (LINFlexD_GetLinState(base) != LINFlexD_STATE_INIT_MODE) {}

        /* 让其进入bit error仍然坚持发送 */
        base->LINCR2 &= ~LINFlexD_LINCR2_IOBE(1U);
        
        /* Set linflexd to lin mode */
        LINFlexD_Init(base, (bool)(linUserConfig->nodeFunction), (linflexd_break_length_t)(linUserConfig->breakLength));
        /* Set break length */

        /* config ID filters for each */
        LINFlexD_ConfigIdFilter(base, linUserConfig->filterCount, linUserConfig->slaveFilterCfgPtr);
        /* configure timeout value */
        LINFlexD_EnableTimeout(base, (bool)(linUserConfig->timeoutEnable));
        LINFlexD_SetTimeoutValue(base, linUserConfig->responseTimeoutValue, linUserConfig->headerTimeoutValue);

        /* if autobaud is enabled */
        if ((linUserConfig->autobaudEnable) && (linUserConfig->nodeFunction == (bool)LINFlexD_SLAVE))
        {
            /* Setting Slave's baudrate to 19200 will help Slave node */
            /* always detect LIN Break from Master */
            linUserConfig->baudRate = 19200U;
            LINFlexD_AutoSyncEnable(base, true);
        }

        /* Set baud rate to User's value */
        (void)LINFlexD_DRV_SetBaudRate(instance, linUserConfig->baudRate);

        /* Default interrupt enable setup */
        LINFlexD_IntInit(base);

        /* Default disable call back */
        linCurrentState->Callback = NULL;
        /* Install handlers */
#if (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)
        INT_SYS_InstallHandler(s_LINFlexDRxIntVec[instance], g_LINFlexDRxIsr[instance], (isr_t*) 0);
        INT_SYS_InstallHandler(s_LINFlexDTxIntVec[instance], g_LINFlexDTxIsr[instance], (isr_t*) 0);
        INT_SYS_InstallHandler(s_LINFlexDErrIntVec[instance], g_LINFlexDErrIsr[instance], (isr_t*) 0);
#elif (FEATURE_LINFlexD_ORED_INT_LINES)
        INT_SYS_InstallHandler(s_LINFlexDIntVec[instance], g_LinLINFlexDIsr[instance], (isr_t*) 0);
#endif

        /* Enable LINFlexD interrupts */
#if (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)
        INT_SYS_EnableIRQ(s_LINFlexDRxIntVec[instance]);
        INT_SYS_EnableIRQ(s_LINFlexDTxIntVec[instance]);
        INT_SYS_EnableIRQ(s_LINFlexDErrIntVec[instance]);
#elif (FEATURE_LINFlexD_ORED_INT_LINES)
        INT_SYS_EnableIRQ(s_LINFlexDIntVec[instance]);
#endif
        LINFlexD_EnterNormalMode(base);
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_Deinit
 * Description   : This function shuts down the LIN Hardware Interface by disabling interrupts and
 *                 transmitter/receiver.
 *
 * Implements    : LINFlexD_DRV_Deinit_Activity
 *END**************************************************************************/
void LINFlexD_DRV_Deinit(uint32_t instance)
{
    /* Assert parameters. */
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    /* Get the current LIN state of this UART instance. */
    linflexd_state_t * linCurrentState = s_LINFlexDStatePtr[instance];

    /* Check if current instance is already de-initialized or is gated.*/
    DEV_ASSERT(linCurrentState != NULL);
    DEV_ASSERT(linCurrentState->linSourceClockFreq > 0U);

    /* Destroy semaphores. */
    (void)OSIF_SemaDestroy(&linCurrentState->completed);

    /* Disable LINFlexD interrupts */
#if (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)
    INT_SYS_DisableIRQ(s_LINFlexDRxIntVec[instance]);
    INT_SYS_DisableIRQ(s_LINFlexDTxIntVec[instance]);
    INT_SYS_DisableIRQ(s_LINFlexDErrIntVec[instance]);
#elif (FEATURE_LINFlexD_ORED_INT_LINES)
    INT_SYS_DisableIRQ(s_LINFlexDIntVec[instance]);
#endif

    /* Clear our saved pointer to the LIN state structure */
    s_LINFlexDStatePtr[instance] = NULL;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_UART_DRV_SetBaudRate
 * Description   : This function sets the baud rate for UART communication.
 *
 * Implements    : LINFlexD_UART_DRV_SetBaudRate_Activity
 *END**************************************************************************/
status_t LINFlexD_DRV_SetBaudRate(uint32_t instance, uint32_t baudrate)
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

    instanceClkName = s_LINFlexDClkName[instance];
    base = s_LINFlexDBase[instance];
    (void)CLOCK_SYS_GetFreq(instanceClkName, &uartSourceClock);

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
 * Function Name : LINFlexD_DRV_GetDefaultConfig
 * Description   : This function initializes a configuration structure received
 * from the application with default values.
 *
 * Implements    : LINFlexD_DRV_GetDefaultConfig_Activity
 *END**************************************************************************/
void LINFlexD_DRV_GetDefaultConfig(bool isMaster,
                              linflexd_user_config_t * linUserConfig)
{
    linUserConfig->baudRate = 19200;            /*!< Default baud rate */
    linUserConfig->nodeFunction = isMaster ? LINFlexD_MASTER : LINFlexD_SLAVE;        /*!< default as slave node */
    linUserConfig->autobaudEnable = true;       /*!< Enable auto baudrate by default */

}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_InstallCallback
 * Description   : This function installs the callback function that is used for LINFlexD_DRV_IRQHandler.
 * Pass in Null pointer as callback will uninstall.
 *
 * Implements    : LINFlexD_DRV_InstallCallback_Activity
 *END**************************************************************************/
linflexd_callback_t LINFlexD_DRV_InstallCallback(uint32_t instance,
                                       linflexd_callback_t function)
{
    /* Assert parameters. */
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    /* Get the current LIN state of this UART instance. */
    linflexd_state_t * linCurrentState = s_LINFlexDStatePtr[instance];

    /* Get the current callback function. */
    linflexd_callback_t currentCallback = linCurrentState->Callback;

    /* Install new callback function. */
    linCurrentState->Callback = function;

    return currentCallback;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_MasterTransferBlocking
 * Description   : This function sends frame through the LIN Hardware Interface using
 * non-blocking method. This function will calculate the checksum byte and send it with the
 * frame data. The function will return immediately after calling this function. If data size
 * is equal to 0 or greater than 8 then the function will return STATUS_ERROR. If isBusBusy is
 * currently true then the function will return STATUS_BUSY.
 *
 * Implements    : LIN_DRV_SendFrame_Activity
 *END**************************************************************************/
status_t LINFlexD_DRV_MasterTransferBlocking(uint32_t instance, linflexd_frame_t *frame, uint32_t timeoutMSec)
{
    linflexd_state_t * linState;
    status_t status;

    linState = (linflexd_state_t *)s_LINFlexDStatePtr[instance];
    linState->isBlocking = true;
    status = LINFlexD_DRV_MasterTransfer(instance, frame);
    if (STATUS_SUCCESS == status)
    {
        if (OSIF_SemaWait(&linState->completed, timeoutMSec) == STATUS_TIMEOUT)
        {
            status = STATUS_TIMEOUT;
            LINFlexD_DRV_AbortTransferData(instance);
        }
    }
    linState->isBlocking = false;
    return status;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_MasterTransfer
 * Description   : This function sends frame through the LIN Hardware Interface using
 * non-blocking method. This function will calculate the checksum byte and send it with the
 * frame data. The function will return immediately after calling this function. If data size
 * is equal to 0 or greater than 8 then the function will return STATUS_ERROR. If isBusBusy is
 * currently true then the function will return STATUS_BUSY.
 *
 * Implements    : LIN_DRV_SendFrame_Activity
 *END**************************************************************************/
status_t LINFlexD_DRV_MasterTransfer(uint32_t instance, linflexd_frame_t *frame)
{
    /* Assert parameters. */
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    status_t retVal = STATUS_SUCCESS;
    linflexd_direction_t bidr = LINFlexD_RX; 
    /* Get base address of the LINFlexD instance. */
    LINFlexD_Type * base = s_LINFlexDBase[instance];
    /* Get the current LIN state of this UART instance. */
    linflexd_state_t * linCurrentState = s_LINFlexDStatePtr[instance];
    
    /* Check if current instance is already de-initialized or is gated.*/
    DEV_ASSERT(linCurrentState != NULL);

    /* Check if txSize > 8 or equal to 0 */
    if ((8U < frame->dataLength ) || (0U == frame->dataLength || 0x3FU < frame->id))
    {
        return STATUS_ERROR;
    }
    /* Check if the LIN Bus is IDLE */
    if (LINFlexD_GetLinState(base) != LINFlexD_STATE_IDLE_MODE)
    {
        return  STATUS_BUSY;
    }
    /* Master Response */
    if (LIN_MASTER_RESPONSE == frame->responseType)
    {
        /* fill data to tx buffer */
        LINFlexD_SetTxDataArray(base, frame->data, frame->dataLength);
        bidr = LINFlexD_TX;
    }
    else if (LIN_SLAVE_TO_SLAVE == frame->responseType)
    {
        LINFlexD_DataDiscard(base, true);
    }
    else
    {
        /* Slave response, data from slave to master */
        LINFlexD_DataDiscard(base, false);
        /* Clear RDC */
        LINFlexD_ClearLinStatusFlag(base, LINFlexD_LIN_RX_DATA_START_FLAG);
        /* Update receive data buffer */
        linCurrentState->rxBuff = frame->data;
        linCurrentState->rxSize = frame->dataLength;

    }
    
    LINFlexD_SetLinBIDR(base, frame->id, frame->dataLength, bidr, frame->checksumType);
    /* Set header request to start transmission */
    LINFlexD_SetHeaderRequest(base);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LIN_DRV_SlaveResponse
 * Description   : This function sends out slave data through the LIN Hardware Interface
 * non-blocking method. This function will calculate the checksum byte and send it with the
 * frame data. The function will return immediately after calling this function. If data size
 * is equal to 0 or greater than 8 then the function will return STATUS_ERROR. If isBusBusy is
 * currently true then the function will return STATUS_BUSY.
 *
 * Implements    : LIN_DRV_SendFrame_Activity
 *END**************************************************************************/
status_t LINFlexD_DRV_SlaveResponse(uint32_t instance, linflexd_frame_t *frame)
{
    /* Assert parameters. */
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);
    DEV_ASSERT(frame->responseType < LIN_SLAVE_TO_SLAVE);

    /* Get base address of the LINFlexD instance. */
    LINFlexD_Type * base = s_LINFlexDBase[instance];
    /* Get the current LIN state of this UART instance. */
    linflexd_state_t * linCurrentState = s_LINFlexDStatePtr[instance];

    /* Check if header is received. */
    if (0 == (base->LINSR & LINFlexD_LINSR_HRF_MASK))
    {
        /* Function called when no header received */
        return STATUS_LINFlexD_NO_HEADER_RECEIVED;
    }
    if (LIN_SLAVE_RESPONSE == frame->responseType)
    {
        /* Slave send response data. */
        /* fill data to tx buffer */
        LINFlexD_SetTxDataArray(base, frame->data, frame->dataLength);
    }
    else
    {
        /* LIN slave receive response data. */
        /* Update receive data buffer */
        linCurrentState->rxBuff = frame->data;
        linCurrentState->rxSize = frame->dataLength;
    }
    /* Update direction, data length and checksum type. */
    LINFlexD_SetLinBIDR(base, frame->id, frame->dataLength, frame->responseType, frame->checksumType);
    if (LIN_SLAVE_RESPONSE == frame->responseType)
    {
        /* Set data request to start transmission */
        LINFlexD_SetDataRequest(base);
    }
    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_DataDiscard
 * Description   : Stop data reception if the frame does not concern the node.
 * Call it after receive header, used in LIN slave mode with id software-filtered.
 *
 * Implements    : LINFlexD_DRV_DataDiscard_Activity
 *END**************************************************************************/
status_t LINFlexD_DRV_DataDiscard(uint32_t instance)
{
    /* Assert parameters. */
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    /* Get base address of the LINFlexD instance. */
    LINFlexD_Type * base = s_LINFlexDBase[instance];

    LINFlexD_DataDiscard(base, true);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_AbortTransferData
 * Description   : Aborts an ongoing non-blocking transmission/reception.
 * While performing a non-blocking transferring data, users can call this
 * function to terminate immediately the transferring.
 *
 * Implements    : LINFlexD_DRV_AbortTransferData_Activity
 *END**************************************************************************/
status_t LINFlexD_DRV_AbortTransferData(uint32_t instance)
{
    /* Assert parameters. */
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    /* Get base address of the LINFlexD instance. */
    LINFlexD_Type * base = s_LINFlexDBase[instance];

    LINFlexD_SetTransferAbort(base, true);
    for (uint32_t i = 0; i < FEATURE_LINFlexD_TIMEOUT_LOOPS; i++) 
    {
        if (false == LINFlexD_GetTransferAbort(base))
        {
            return STATUS_SUCCESS;
        }
    }
    return STATUS_LINFlexD_ABORT_TIMEOUT;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_GoToSleepMode
 * Description   : This function puts current LIN node to sleep mode.
 * This function changes current node state to LINFlexD_NODE_STATE_SLEEP_MODE.
 *
 * Implements    : LINFlexD_DRV_GoToSleepMode_Activity
 *END**************************************************************************/
status_t LINFlexD_DRV_GoToSleepMode(uint32_t instance)
{
    /* Assert parameters. */
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    /* Get base address of the LINFlexD instance. */
    LINFlexD_Type * base = s_LINFlexDBase[instance];

    DEV_ASSERT (false == LINFlexD_GetSleepMode(base));

    /* Clear previous flags. */
    LINFlexD_ClearLinStatusFlag(base, LINFlexD_LIN_WAKEUP_FLAG);
    /* Enable wakeup interrupt */
    LINFlexD_SetInterruptMode(base, LINFlexD_WAKEUP_INT, true);
#if (FEATURE_LINFlexD_HAS_RED_IRQ)
    /* Clear previous flags. */
    LINFlexD_ClearLinStatusFlag(base, LINFlexD_LIN_RECEIVE_EDGE_DETECTION_FLAG);
    /* Enable wakeup interrupt */
    LINFlexD_SetInterruptMode(base, LINFlexD_RECEIVE_EDGE_DETECTION_INT, true);
#endif /* FEATURE_LINFlexD_HAS_RED_IRQ */
    /* Request to sleep mode. */
    LINFlexD_SetSleepMode(base, true);
    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_GotoIdleState
 * Description   : This function puts current node to Idle state.
 *
 * Implements    : LINFlexD_DRV_GoToIdleState_Activity
 *END**************************************************************************/
status_t LINFlexD_DRV_GotoIdleState(uint32_t instance)
{
    /* Assert parameters. */
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    /* Get base address of the LINFlexD instance. */
    LINFlexD_Type * base = s_LINFlexDBase[instance];
    /* Clear previous flags. */
    LINFlexD_ClearLinStatusFlag(base, LINFlexD_LIN_WAKEUP_FLAG);
    /* Exit sleep mode. */
    LINFlexD_SetSleepMode(base, false);
    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_SendWakeupSignal
 * Description   : This function sends a wakeup signal through the LIN interface.
 *
 * Implements    : LINFlexD_DRV_SendWakeupSignal_Activity
 *END**************************************************************************/
status_t LINFlexD_DRV_SendWakeupSignal(uint32_t instance)
{
    /* Assert parameters. */
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    /* Get base address of the LINFlexD instance. */
    LINFlexD_Type * base = s_LINFlexDBase[instance];
    DEV_ASSERT (false == LINFlexD_GetSleepMode(base));
    LINFlexD_SetWakeupRequest(base);
    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_GetCurrentNodeState
 * Description   : This function gets the current LIN node state.
 *
 * Implements    : LINFlexD_DRV_GetCurrentNodeState_Activity
 *END**************************************************************************/
linflexd_node_state_t LINFlexD_DRV_GetCurrentNodeState(uint32_t instance)
{
    /* Assert parameters. */
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);

    /* Get base address of the LINFlexD instance. */
    LINFlexD_Type * base = s_LINFlexDBase[instance];
    return (linflexd_node_state_t)LINFlexD_GetLinState(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_EnableIRQ
 * Description   : This function enables LIN hardware interrupts.
 *
 * Implements    : LINFlexD_DRV_EnableIRQ_Activity
 *END**************************************************************************/
status_t LINFlexD_DRV_EnableIRQ(uint32_t instance)
{
    /* Assert parameters. */
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);
    /* Enable LINFlexD interrupts */
#if (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)
    INT_SYS_EnableIRQ(s_LINFlexDRxIntVec[instance]);
    INT_SYS_EnableIRQ(s_LINFlexDTxIntVec[instance]);
    INT_SYS_EnableIRQ(s_LINFlexDErrIntVec[instance]);
#elif (FEATURE_LINFlexD_ORED_INT_LINES)
    INT_SYS_EnableIRQ(s_LINFlexDIntVec[instance]);
#endif

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_DisableIRQ
 * Description   : This function disables LIN hardware interrupts.
 *
 * Implements    : LINFlexD_DRV_DisableIRQ_Activity
 *END**************************************************************************/
status_t LINFlexD_DRV_DisableIRQ(uint32_t instance)
{
    /* Assert parameters. */
    DEV_ASSERT(instance < LINFlexD_INSTANCE_COUNT);
    /* Disable LINFlexD interrupts */
#if (FEATURE_LINFlexD_RX_TX_ERR_INT_LINES)
    INT_SYS_DisableIRQ(s_LINFlexDRxIntVec[instance]);
    INT_SYS_DisableIRQ(s_LINFlexDTxIntVec[instance]);
    INT_SYS_DisableIRQ(s_LINFlexDErrIntVec[instance]);
#elif (FEATURE_LINFlexD_ORED_INT_LINES)
    INT_SYS_DisableIRQ(s_LINFlexDIntVec[instance]);
#endif
    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_IRQHandler
 * Description   : Interrupt handler for LIN Hardware Interface.
 * This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 * Implements    : LINFlexD_DRV_IRQHandler_Activity
 *END**************************************************************************/
void LINFlexD_LIN_DRV_IRQHandler(uint32_t instance)
{
    const LINFlexD_Type * base;

    base = s_LINFlexDBase[instance];

    /* Handle receive interrupt */
    /* header received(HRIE, Header transmit with RX dir), data received(DRIE), 
     * LIN State switch, wakeup interrupt (WUIE)*/
    if (LINFlexD_IsInterruptEnabled(base, 
                            (LINFlexD_LINIER_DRIE_MASK | 
                            LINFlexD_LINIER_HRIE_MASK | 
                            LINFlexD_LINIER_WUIE_MASK
#if (FEATURE_LINFlexD_HAS_RED_IRQ)
                            | LINFlexD_LINIER_REDIE_MASK
#endif /* FEATURE_LINFlexD_HAS_RED_IRQ */
                            )))
    {
        LINFlexD_LIN_DRV_RxIRQHandler(instance);
    }

    /* Handle transmitter data register empty interrupt */
    /* Data transition(DTIE), Header transmit with TX dir and matching */
    if (LINFlexD_IsInterruptEnabled(base, LINFlexD_DATA_TRANSMITTED_INT))
    {
        LINFlexD_LIN_DRV_TxIRQHandler(instance);
    }

    /* Handle the error interrupts if no rx/tx interrupt was triggered */
    LINFlexD_LIN_DRV_ErrIRQHandler(instance);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_LIN_DRV_RxIRQHandler
 * Description   : Rx interrupt handler for LIN.
 * This handler uses the rx buffer stored in the state structure to receive
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *END**************************************************************************/
void LINFlexD_LIN_DRV_RxIRQHandler(uint32_t instance)
{
    linflexd_state_t * linState;
    LINFlexD_Type * base;

    base = s_LINFlexDBase[instance];
    linState = (linflexd_state_t *)s_LINFlexDStatePtr[instance];

    /* Handle receive data interrupt */
    if (LINFlexD_GetLinStatusFlag(base, LINFlexD_LIN_DATA_RECEPTION_COMPLETE_FLAG))
    {
        /* Handle ID filter for receiving. */
        LINFlexD_LIN_DRV_FilterResponse(instance, LINFlexD_RX);
        /* Retrieve the data */
        LINFlexD_GetRxDataArray(base, linState->rxBuff, linState->rxSize);
        /* Release receive data flag. */
        LINFlexD_ClearLinStatusFlag(base, LINFlexD_LIN_DATA_RECEPTION_COMPLETE_FLAG);
        /* Release receive data message buffer. */
        LINFlexD_ClearLinStatusFlag(base, LINFlexD_LIN_RELEASE_MESSAGE_BUFFER_FLAG);
        /* Release receive header flag. */
        LINFlexD_ClearLinStatusFlag(base, LINFlexD_LIN_HEADER_RECEIVED_FLAG);

        /* Signal the synchronous completion object. */
        if (linState->isBlocking)
        {
            (void)OSIF_SemaPost(&linState->completed);
        }
        linState->currentId = LINFlexD_GetLinBidrID(base);
        linState->currentEventId = LINFlexD_DATA_RECEIVED_EVENT;
        /* Invoke the callback when the buffer is finished; */
        if (NULL != linState->Callback)
        {
            linState->Callback(instance, linState);
        }
    }
    /* Handle receive header interrupt */
    if (LINFlexD_GetLinStatusFlag(base, LINFlexD_LIN_HEADER_RECEIVED_FLAG))
    {
        linState->currentEventId = LINFlexD_HEADER_RECEIVED_EVENT;
        linState->currentId = LINFlexD_GetLinBidrID(base);
        /* Handle ID filter for sending. */
        LINFlexD_LIN_DRV_FilterResponse(instance, LINFlexD_TX);
        /* Invoke the callback when the header received; */
        if (NULL != linState->Callback)
        {
            linState->Callback(instance, linState);
        }
        /* Clear the flag */
        LINFlexD_ClearLinStatusFlag(base, LINFlexD_LIN_HEADER_RECEIVED_FLAG);
    }
    /* Handle wakeup interrupt */
    if (LINFlexD_GetLinStatusFlag(base, LINFlexD_LIN_WAKEUP_FLAG))
    {
        linState->currentEventId = LINFlexD_WAKEUP_EVENT;
        /* Clear previous flags. */
        LINFlexD_ClearLinStatusFlag(base, LINFlexD_LIN_WAKEUP_FLAG);
        /* Disable wake up interrupt */
        LINFlexD_SetInterruptMode(base, LINFlexD_WAKEUP_INT, false);
        /* Exit sleep mode. */
        LINFlexD_SetSleepMode(base, false);
        /* Invoke the callback when the wakeup detected */
        if (NULL != linState->Callback)
        {
            linState->Callback(instance, linState);
        }
    }
#if (FEATURE_LINFlexD_HAS_RED_IRQ)
    /* Handle receive edge detection interrupt */
    if (LINFlexD_GetLinStatusFlag(base, LINFlexD_LIN_RECEIVE_EDGE_DETECTION_FLAG))
    {
        linState->currentEventId = LINFlexD_RECEIVE_EDGE_DETECTION_EVENT;
        /* Clear previous flags. */
        LINFlexD_ClearLinStatusFlag(base, LINFlexD_LIN_RECEIVE_EDGE_DETECTION_FLAG);
        /* Disable RDF interrupt */
        LINFlexD_SetInterruptMode(base, LINFlexD_RECEIVE_EDGE_DETECTION_INT, false);
        /* Exit sleep mode. */
        LINFlexD_SetSleepMode(base, false);
        /* Invoke the callback when the receive edge detected */
        if (NULL != linState->Callback)
        {
            linState->Callback(instance, linState);
        }
    }
#endif /* FEATURE_LINFlexD_HAS_RED_IRQ */
}
/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_LIN_DRV_TxIRQHandler
 * Description   : Tx interrupt handler for LIN.
 * This handler uses the tx buffer stored in the state structure to transmit
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *END**************************************************************************/
void LINFlexD_LIN_DRV_TxIRQHandler(uint32_t instance)
{
    linflexd_state_t * linState;
    LINFlexD_Type * base;

    base = s_LINFlexDBase[instance];
    linState = (linflexd_state_t *)s_LINFlexDStatePtr[instance];

    /* Handle transmit data interrupt */
    if (LINFlexD_GetLinStatusFlag(base, LINFlexD_LIN_DATA_TRANSMITTED_FLAG))
    {
        /* Signal the synchronous completion object. */
        if (linState->isBlocking)
        {
            (void)OSIF_SemaPost(&linState->completed);
        }
        /* Invoke the callback when the buffer is finished; */
        linState->currentEventId = LINFlexD_DATA_SENT_EVENT;
        if (NULL != linState->Callback)
        {
            linState->Callback(instance, linState);
        }
    }
    /* Clear the flag */
    LINFlexD_ClearLinStatusFlag(base, LINFlexD_LIN_DATA_TRANSMITTED_FLAG);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_LIN_DRV_ErrIRQHandler
 * Description   : Rx interrupt handler for LIN.
 * This handler uses the rx buffer stored in the state structure to receive
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *END**************************************************************************/
void LINFlexD_LIN_DRV_ErrIRQHandler(uint32_t instance)
{
    linflexd_state_t * linState;
    LINFlexD_Type * base;

    base = s_LINFlexDBase[instance];
    linState = (linflexd_state_t *)s_LINFlexDStatePtr[instance];
    if (base->LINESR)
    {
        linState->errorStatus = base->LINESR;
        /* get the received size for LIN event frame*/
        linState->rxSize -= ((base->LINSR&LINFlexD_LINSR_RDC_MASK) >> LINFlexD_LINSR_RDC_SHIFT);
        /* Check output compare event  */
        if (LINFlexD_GetLinErrorStatusFlag(base, LINFlexD_LIN_OUTPUT_COMPARE_FLAG))
        {
            linState->currentEventId = LINFlexD_OUTPUT_COMPARE_EVENT;
            base->LINESR |= LINFlexD_LIN_OUTPUT_COMPARE_FLAG;
        }else if(LINFlexD_GetLinErrorStatusFlag(base, LINFlexD_LIN_BUFFER_OVERRUN_FLAG))
        {
            linState->currentEventId = LINFlexD_CHECKSUM_ERROR_EVENT;
            base->LINESR |= LINFlexD_LIN_BUFFER_OVERRUN_FLAG;
        }else if(LINFlexD_GetLinErrorStatusFlag(base, LINFlexD_LIN_FRAMING_ERROR_FLAG))
        {
            linState->currentEventId = LINFlexD_FRAME_ERROR_EVENT;
            base->LINESR |= LINFlexD_LIN_FRAMING_ERROR_FLAG;
        }else if(LINFlexD_GetLinErrorStatusFlag(base, LINFlexD_LIN_ID_PARITY_ERROR_FLAG))
        {
            linState->currentEventId = LINFlexD_PID_PARITY_ERROR_EVENT;
            base->LINESR |= LINFlexD_LIN_ID_PARITY_ERROR_FLAG;
        }else if(LINFlexD_GetLinErrorStatusFlag(base, LINFlexD_LIN_BREAK_DELIMITER_ERROR_FLAG))
        {
            linState->currentEventId = LINFlexD_BREAK_DELIMITER_ERROR_EVENT;
            base->LINESR |= LINFlexD_LIN_BREAK_DELIMITER_ERROR_FLAG;
        }else if(LINFlexD_GetLinErrorStatusFlag(base, LINFlexD_LIN_SYNC_FIELD_ERROR_FLAG))
        {
            linState->currentEventId = LINFlexD_SYNC_ERROR_EVENT;
            base->LINESR |= LINFlexD_LIN_SYNC_FIELD_ERROR_FLAG;
        }else if(LINFlexD_GetLinErrorStatusFlag(base, LINFlexD_LIN_CHECKSUM_ERROR_FLAG))
        {
            linState->currentEventId = LINFlexD_CHECKSUM_ERROR_EVENT;
            base->LINESR |= LINFlexD_LIN_CHECKSUM_ERROR_FLAG;
        }else if(LINFlexD_GetLinErrorStatusFlag(base, LINFlexD_LIN_BIT_ERROR_FLAG))
        {
            linState->currentEventId = LINFlexD_BIT_ERROR_EVENT;
            base->LINESR |= LINFlexD_LIN_BIT_ERROR_FLAG;
        }else if(LINFlexD_GetLinErrorStatusFlag(base, LINFlexD_LIN_STUCK_AT_ZERO_FLAG))
        {
            linState->currentEventId = LINFlexD_STUCK_ZERO_ERROR_EVENT;
            base->LINESR |= LINFlexD_LIN_STUCK_AT_ZERO_FLAG;
        }

        if (NULL != linState->Callback)
        {
            linState->Callback(instance, linState);
        }
    }
}

/*FUNCTION**********************************************************************
 * 
 * Function Name : LINFlexD_LIN_DRV_FilterResponse
 * Description   : Handle ID filter for LIN.
 * This function is used when ID Filter enable and auto sending or receving.
 * 
 *END**************************************************************************/
void LINFlexD_LIN_DRV_FilterResponse(uint32_t instance, linflexd_direction_t direction)
{
    uint8_t index;
    linflexd_user_config_t * linUserConfig;
    linflexd_id_filter_config_t * linIdFilterConfig;
    linflexd_state_t * linState;
    LINFlexD_Type * base;

    base = s_LINFlexDBase[instance];
    linUserConfig = (linflexd_user_config_t *)s_LINFlexDUserconfigPtr[instance];
    linState = (linflexd_state_t *)s_LINFlexDStatePtr[instance];

    /* id filter used in slave mode */
    if (linUserConfig->nodeFunction != LINFlexD_SLAVE)
    {
        return;
    }

    index = LINFlexD_GetFilterMatchIndex(base);
    /* if no ID match, index equal 0. */
    if (index == 0)
    {
        return;
    }
    linIdFilterConfig = &(linUserConfig->slaveFilterCfgPtr[index-1]);
    /* exclude slave rx in header interrupt */
    if (linIdFilterConfig->direction != direction)
    {
        return;
    }
    else
    {
        if (direction == LINFlexD_RX)
        {
            /* set pointer to linIdFilterConfig items */
            linState->rxBuff = linIdFilterConfig->data;
            linState->rxSize = linIdFilterConfig->dataFieldLength;
        }
        else
        {
            /* Slave send response data. */
            /* fill data to tx buffer */
            LINFlexD_SetTxDataArray(base, linIdFilterConfig->data, linIdFilterConfig->dataFieldLength);
            /* Set data request to start transmission */
            LINFlexD_SetDataRequest(base);
        }
    }
}

/*FUNCTION**********************************************************************
 * 
 * Function Name : LINFlexD_GetFilterMatchId
 * Description   : Get current match ID.
 * This function is used when ID Filter enable and ID getting.
 * 
 *END**************************************************************************/
uint8_t LINFlexD_GetFilterMatchId(uint32_t instance)
{
    uint8_t index;
    LINFlexD_Type * base;
    linflexd_user_config_t * linUserConfig;
    base = s_LINFlexDBase[instance];
    linUserConfig = (linflexd_user_config_t *)s_LINFlexDUserconfigPtr[instance];

    index = LINFlexD_GetFilterMatchIndex(base);
    DEV_ASSERT(index != 0);
    return (linUserConfig->slaveFilterCfgPtr[index-1].id);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_GetChecksumType
 * Description   : Check if frame use classic checksum.
 *
 * Implements    : LINFlexD_DRV_GetChecksumType_Activity
 *END**************************************************************************/
linflexd_cs_t LINFlexD_DRV_GetChecksumType(uint32_t instance, uint8_t ID)
{
    /* Get list of PIDs use classic checksum. */
    const uint8_t *classicID = s_LINFlexDUserconfigPtr[instance]->classicID;
    const uint8_t numOfClassicID = s_LINFlexDUserconfigPtr[instance]->numOfClassicID;
    uint8_t i = 0;
    linflexd_cs_t type = LIN_ENHANCED_CHECKSUM;

    if(numOfClassicID == 255U)
    {
        /* All frame use classic checksum */
        type = LIN_CLASSIC_CHECKSUM;
    }
    else
    {
        if(classicID != NULL)
        {
            for (i = 0U; i < numOfClassicID; i++)
            {
                if(ID == classicID[i])
                {
                    type = LIN_CLASSIC_CHECKSUM;
                    break;
                }
            }
        }
    }
    
    /* For PID is 0x3C (ID 0x3C) or 0x7D (ID 0x3D) or 0xFE (ID 0x3E) or 0xBF (ID 0x3F)
     * apply classic checksum and apply enhanced checksum for other PID */
    if ((0x3CU == ID) && (0x3DU != ID) && (0x3EU != ID) && (0x3FU != ID))
    {
        type = LIN_CLASSIC_CHECKSUM;
    }
    return type;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : BIT
 * Description   : Return bit B in byte A
 * This is not a public API as it is called by other API functions.
 *
 *END**************************************************************************/
static inline uint8_t BIT(uint8_t A,
                          uint8_t B)
{
    return (uint8_t) ((A >> B) & 0x01U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFlexD_DRV_ProcessParity
 * Description   : Makes or checks parity bits. If action is checking parity, the function
 * returns ID value if parity bits are correct or 0xFF if parity bits are incorrect. If action
 * is making parity bits, then from input value of ID, the function returns PID.
 * This is not a public API as it is called by other API functions.
 *
 * Implements    : LINFlexD_DRV_ProcessParity_Activity
 *END**************************************************************************/
uint8_t LINFlexD_DRV_ProcessParity(uint8_t PID,
                              uint8_t typeAction)
{
    uint8_t parity;
    uint8_t retVal;

    parity = (uint8_t) (((0xFFU & (BIT(PID, 0U) ^ BIT(PID, 1U) ^ BIT(PID, 2U) ^ BIT(PID, 4U))) << 6U) |
                        ((0xFFU ^ (BIT(PID, 1U) ^ BIT(PID, 3U) ^ BIT(PID, 4U) ^ BIT(PID, 5U))) << 7U));

    /* Check if action is checking parity bits */
    if (CHECK_PARITY == typeAction)
    {
        /* If parity bits are incorrect */
        if ((PID & 0xC0U) != parity)
        {
            /* Return 0xFF if parity bits are incorrect */
            retVal = 0xFFU;
        }
            /* If parity bits are correct */
        else
        {
            /* Return ID if parity bits are correct */
            retVal = (uint8_t) (PID & 0x3FU);
        }
    }
    /* If action is making parity bits */
    else
    {
        /* Return PID in case of making parity bits */
        retVal = (uint8_t) (PID | parity);
    }

    return retVal;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
