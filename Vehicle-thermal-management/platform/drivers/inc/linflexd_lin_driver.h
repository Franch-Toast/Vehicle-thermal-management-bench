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
 * @file linflexd_lin_driver.h
 */

#ifndef LINFlexD_DRIVER_LIN_H
#define LINFlexD_DRIVER_LIN_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdbool.h>
#include <stddef.h>
#include "device_registers.h"
#include "status.h"
#include "interrupt_manager.h"
#include "osif.h"

/*!
 * @addtogroup linflexd_lin
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAKE_PARITY  0U
#define CHECK_PARITY 1U

/*!
 * @brief Callback function to get time interval in nanoseconds
 *
 * Implements : linflexd_timer_get_time_interval_t_Class
 */
typedef uint32_t (*linflexd_timer_get_time_interval_t)(uint32_t *nanoSeconds);

/*!
 * @brief The node function for LINFlexD mode
 *
 * Implements : linflexd_node_function_t_Class
 */
typedef enum
{
    LINFlexD_SLAVE = 0U,        /*!< Node acts as a slave in LINFlexD mode */
    LINFlexD_MASTER = 1U,       /*!< Node acts as a master in LINFlexD mode */
} linflexd_node_function_t;

/*!
 * @brief The checksum type for LINFlexD
 *
 * Implements : linflexd_cs_t_Class
 */
typedef enum
{
    LIN_ENHANCED_CHECKSUM = 0,    /*!< LINFlexD enhanced checksum method */
    LIN_CLASSIC_CHECKSUM = 1     /*!< LINFlexD classical checksum method */
} linflexd_cs_t;

/*!
 * @brief Response type for LINFlexD
 *
 * Implements : linflexd_response_t_Class
 */
typedef enum
{
    LIN_MASTER_RESPONSE = 0,    /*!< LIN master send response, slave receive */
    LIN_SLAVE_RESPONSE = 1,    /*!< LIN slave send response, master receive */
    LIN_SLAVE_TO_SLAVE = 2     /*!< LIN slave send response, slave receive
                                        Master only send out header */
} linflexd_response_t;

/*! 
 * @brief LINFlexD direction: for BIDR register
 *
 * Implements : linflexd_direction_t_Class
 */
typedef enum
{
    LINFlexD_RX = 0U,        /*!< Receive frames in LIN */
    LINFlexD_TX = 1U         /*!< Transmit frames in LIN */
} linflexd_direction_t;

/*!
 * @brief LIN hardware id filter configuration structure
 *
 * Implements : linflexd_id_filter_config_t_Class
 */
typedef struct
{
    bool filterEnable;                      /*!< Enable the id filters */
    bool maskEnable;                        /*!< Mask enable for filter pairs */
    uint8_t dataFieldLength;                /*!< LIN frame data length */
    linflexd_direction_t direction;         /*!< The direction of data field */
    linflexd_cs_t checksumType;             /*!< LIN Checksum method */
    uint8_t id;                            /*!< LIN ID */
    uint8_t data[8];                        /*!< LIN Data pointer */
} linflexd_id_filter_config_t;

/*!
 * @brief LIN frame data structure
 *
 * Implements : linflexd_frame_t_Class
 */
typedef struct
{
    uint8_t id;                                 /*!< LIN ID */
    linflexd_cs_t checksumType;                 /*!< LIN Checksum method */
    linflexd_response_t responseType;           /*!< LIN frame response type */
    uint8_t dataLength;                         /*!< LIN frame data length */
    uint8_t data[8];                            /*!< LIN Data pointer */
} linflexd_frame_t;

/*!
 * @brief Defines types for an enumerating event related to an Identifier.
 *
 * Implements : linflexd_event_id_t_Class
 */
typedef enum
{
    LINFlexD_NO_EVENT = 0x00U,    /*!< No event yet */
    LINFlexD_STUCK_ZERO_ERROR_EVENT = 0x01U,    /*!< Stuck at zero */
    LINFlexD_OUTPUT_COMPARE_EVENT = 0x02U,   /*!< Output compare happened */
    LINFlexD_BIT_ERROR_EVENT = 0x03U,    /*!< Bit error happened */
    LINFlexD_CHECKSUM_ERROR_EVENT = 0x04U,    /*!< Checksum byte is incorrect */
    LINFlexD_SYNC_ERROR_EVENT = 0x05U,    /*!< Sync field is incorrect */
    LINFlexD_BREAK_DELIMITER_ERROR_EVENT = 0x06U,    /*!< Break delimiter is incorrect */
    LINFlexD_PID_PARITY_ERROR_EVENT = 0x07U,    /*!< PID parity check is incorrect */
    LINFlexD_FRAME_ERROR_EVENT = 0x08U,    /*!< Framing Error */
    LINFlexD_RX_OVERRUN_ERROR_EVENT = 0x09U,    /*!< RX overrun flag */
    LINFlexD_NOISE_ERROR_EVENT = 0x0AU,    /*!< Noise detected */
    LINFlexD_AUTOSYNC_COMP_EVENT = 0x0BU,    /*!< Auto sync complete */

    LINFlexD_WAKEUP_EVENT = 0x11U,    /*!< Wakeup event */
    LINFlexD_HEADER_RECEIVED_EVENT = 0x12U,    /*!< Header received event */
    LINFlexD_DATA_RECEIVED_EVENT = 0x13U,    /*!< Data reception complete event */
    LINFlexD_DATA_SENT_EVENT = 0x14U,     /*!< Data transmission complete event */
    LINFlexD_RECEIVE_EDGE_DETECTION_EVENT = 0x15U    /*!< Receive edge detection event  */
} linflexd_event_id_t;

/*!
 * @brief Define type for an enumerating LIN Node state.
 *
 * Implements : linflexd_node_state_t_Class
 */
typedef enum
{
    LINFlexD_NODE_STATE_SLEEP_MODE = 0x00U,    /*!< Sleep mode state */
    LINFlexD_NODE_STATE_INIT = 0x01U,    /*!< Initialized state */
    LINFlexD_NODE_STATE_IDLE = 0x02U,    /*!< Idle state */
    LINFlexD_NODE_STATE_BREAK_PROGRESS = 0x03U,    /*!< Send/Receive break field ongoing state */
    LINFlexD_NODE_STATE_BREAK_COMPLETED = 0x04U,    /*!< Send/Receive break field complete state */
    LINFlexD_NODE_STATE_RECV_SYNC = 0x05U,    /*!< Receive the synchronization byte state */
    LINFlexD_NODE_STATE_PID = 0x06U,    /*!< Send/Receive PID state */
    LINFlexD_NODE_STATE_HEADER = 0x07U,    /*!< Send/Receive header state */
    LINFlexD_NODE_STATE_DATA = 0x08U,    /*!< Send/Receive data state */
    LINFlexD_NODE_STATE_CHECKSUM = 0x09U,    /*!< Send/Receive checksum state */
    LINFlexD_NODE_STATE_UNINIT = 0xFFU     /*!< Uninitialized state */
} linflexd_node_state_t;

/*!
 * @brief Define type for an enumerating LIN break size.
 *
 * Implements : linflexd_break_length_t_Class
 */
typedef enum
{
    LINFlexD_BREAK_10_BIT = 0x00U,    /*!< LIN break 10 bits */
    LINFlexD_BREAK_11_BIT = 0x01U,    /*!< LIN break 11 bits */
    LINFlexD_BREAK_12_BIT = 0x02U,    /*!< LIN break 12 bits */
    LINFlexD_BREAK_13_BIT = 0x03U,    /*!< LIN break 13 bits */
    LINFlexD_BREAK_14_BIT = 0x04U,    /*!< LIN break 14 bits */
    LINFlexD_BREAK_15_BIT = 0x05U,    /*!< LIN break 15 bits */
    LINFlexD_BREAK_16_BIT = 0x06U,    /*!< LIN break 16 bits */
    LINFlexD_BREAK_17_BIT = 0x07U,    /*!< LIN break 17 bits */
    LINFlexD_BREAK_18_BIT = 0x08U,    /*!< LIN break 18 bits */
    LINFlexD_BREAK_19_BIT = 0x09U,    /*!< LIN break 19 bits */
    LINFlexD_BREAK_20_BIT = 0x10U,    /*!< LIN break 20 bits */
    LINFlexD_BREAK_21_BIT = 0x11U,    /*!< LIN break 21 bits */
    LINFlexD_BREAK_22_BIT = 0x12U,    /*!< LIN break 22 bits */
    LINFlexD_BREAK_23_BIT = 0x13U,    /*!< LIN break 23 bits */
    LINFlexD_BREAK_36_BIT = 0x14U,    /*!< LIN break 36 bits */
    LINFlexD_BREAK_50_BIT = 0x15U,    /*!< LIN break 50 bits */
} linflexd_break_length_t;

/*!
 * @brief LIN Driver callback function type
 *
 * Implements : linflexd_callback_t_Class
 */
typedef void (*linflexd_callback_t)(uint32_t instance, void *linState);

/*!
 * @brief Runtime state of the LIN driver.
 *
 * Note that the caller provides memory for the driver state structures during
 * initialization because the driver does not statically allocate memory.
 *
 * Implements : linflexd_state_t_Class
 */
typedef struct
{
    linflexd_callback_t Callback;                   /*!< Callback function to invoke after receiving a byte or transmitting a byte. */
    uint8_t currentId;                              /*!< Current ID */
    volatile uint8_t rxSize;                        /*!< The number of bytes to be received. */
    uint8_t *rxBuff;                               /*!< The buffer of received data. */
    volatile linflexd_event_id_t currentEventId;    /*!< Current Event ID Event */
    volatile linflexd_node_state_t currentNodeState; /*!< Current Node state */
    uint32_t linSourceClockFreq;                    /*!< Frequency of the source clock for LIN */
    volatile bool isBlocking;                       /*!< True if transmit is blocking transaction. */
    volatile uint32_t errorStatus;                  /*!< The value of LINESR */
    semaphore_t completed;                          /*!< Used to wait for LIN interface ISR to complete transmission.*/
} linflexd_state_t;

/*!
 * @brief LIN hardware configuration structure
 *
 * Implements : linflexd_user_config_t_Class
 */
typedef struct
{
    uint32_t baudRate;                              /*!< baudrate of LIN Hardware Interface to configure */
    bool nodeFunction;                              /*!< Node function as Master or Slave */
    linflexd_break_length_t breakLength;            /*!< Break length, only for master mode */
    bool autobaudEnable;                            /*!< Enable Autobaud feature, only for slave mode */
    bool timeoutEnable;                             /*!< Enable Timeout feature */
    uint8_t responseTimeoutValue;                   /*!< Timeout value for response */
    uint8_t headerTimeoutValue;                     /*!< Timeout value for header */
    uint8_t filterCount;                            /*!< Actual filters used */
    linflexd_id_filter_config_t *slaveFilterCfgPtr; /*!< Slave filter configurations, only for slave mode */
    uint8_t *classicID;                             /*!< List of IDs use classic checksum */
    uint8_t numOfClassicID;                         /*!< Number of IDs use classic checksum */
} linflexd_user_config_t;


/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LIN DRIVER
 * @{
 */

/*!
 * @brief Initializes an instance LIN Hardware Interface for LIN Network.
 *
 * The caller provides memory for the driver state structures during initialization.
 * The user must select the LIN Hardware Interface clock source in the application to initialize the LIN Hardware Interface.
 *
 * @param instance LIN Hardware Interface instance number
 * @param linUserConfig user configuration structure of type #linflexd_user_config_t
 * @param linCurrentState pointer to the LIN Hardware Interface driver state structure
 * @return operation status:
 *         - STATUS_SUCCESS : Operation was successful.
 *         - STATUS_ERROR   : Operation failed due to semaphores initialize error.
 */
status_t LINFlexD_DRV_Init(uint32_t instance,
                           linflexd_user_config_t *linUserConfig,
                           linflexd_state_t *linCurrentState);

/*!
 * @brief Shuts down the LIN Hardware Interface by disabling interrupts and transmitter/receiver.
 *
 * @param instance LIN Hardware Interface instance number
 * @return void
 */
void LINFlexD_DRV_Deinit(uint32_t instance);

/*!
 * @brief Sets the baud rate for LIN communication.
 *
 * This function computes the fractional and integer parts of the baud rate divisor
 * to obtain the desired baud rate using the current protocol clock.
 *
 * @param instance LINFlexD instance number
 * @param baudrate desired baud rate
 * @return An error code or STATUS_SUCCESS
 */
status_t LINFlexD_DRV_SetBaudRate(uint32_t instance, uint32_t baudrate);

/*!
 * @brief Initializes the LIN user configuration structure with default values.
 *
 * This function initializes a configuration structure received from the application
 * with default values.
 * for linUserConfig. Users can see detail in doxygen.
 *
 * @param[in] isMaster Node function:
                - true if node is MASTER
                - false if node is SLAVE
 * @param[out] linUserConfig the default configuration
 * @return void
 */
void LINFlexD_DRV_GetDefaultConfig(bool isMaster,
                                   linflexd_user_config_t *linUserConfig);

/*!
 * @brief Installs callback function that is used for LINFlexD_DRV_IRQHandler.
 *
 * @note After a callback is installed, it bypasses part of the LIN Hardware Interface IRQHandler logic.
 * Therefore, the callback needs to handle the indexes of txBuff and txSize.
 *
 * @param instance LIN Hardware Interface instance number.
 * @param function the LIN receive callback function.
 * @return Former LIN callback function pointer.
 */
linflexd_callback_t LINFlexD_DRV_InstallCallback(uint32_t instance,
                                                 linflexd_callback_t function);

/*!
 * @brief Sends Frame out through the LIN Hardware Interface using blocking method.
 *  This function will calculate the checksum byte and send it with the frame data.
 *  Blocking means that the function does not return until the transmission is complete.
 *  This function returns STATUS_ERROR if txSize is not in range from 1 to 8.
 *  This function return STATUS_BUSY if the hardware is busy.
 *  This function wait until the transmission is complete. 
 *  If the transmission is successful, it will return STATUS_SUCCESS. 
 *  If not, it will return STATUS_TIMEOUT.
 *
 * @param instance LIN Hardware Interface instance number
 * @param frame   Frame configuration
 * @param timeoutMSec timeout value in milliseconds
 * @return operation status:
 *         - STATUS_ERROR   : Error happens.
 *         - STATUS_BUSY    : The hardware is busy.
 *         - STATUS_SUCCESS : The transmission is successful.
 *         - STATUS_TIMEOUT : The transmission isn't successful.
 */
status_t LINFlexD_DRV_MasterTransferBlocking(uint32_t instance, linflexd_frame_t *frame, uint32_t timeoutMSec);

/*!
 * @brief Sends frame data out through the LIN Hardware Interface using non-blocking method.
 *  This enables an a-sync method for transmitting data.
 *  Non-blocking  means that the function returns immediately.
 * @param instance LIN Hardware Interface instance number
 * @param frame   Frame configuration
 * @return operation status:
 *         - STATUS_SUCCESS : The transmission is successful.
 *         - STATUS_BUSY    : Operation failed due to isBusBusy is currently true.
 *         - STATUS_ERROR   : Operation failed due to txSize is equal to 0 or greater than 8
 *                            or node's current state is in SLEEP mode
 */
status_t LINFlexD_DRV_MasterTransfer(uint32_t instance, linflexd_frame_t *frame);

/*!
 * @brief LIN Slave send/receive frame after header is received.
 *        This function should be called in LIN callbacks to process lin header
 *        receive event.
 *
 * @param instance LIN Hardware Interface instance number
 * @param frame  Frame configuration
 * @return operation status:
 *         - STATUS_SUCCESS : The receives frame data is successful.
 *         - STATUS_TIMEOUT : The checksum is incorrect.
 *         - STATUS_BUSY    : Bus busy flag is true.
 *         - STATUS_ERROR   : Operation failed due is equal to 0 or greater than 8 or
 *                            node's current state is in SLEEP mode
 */
status_t LINFlexD_DRV_SlaveResponse(uint32_t instance, linflexd_frame_t *frame);

/*!
 * @brief Stop data reception if the frame does not concern the node.
 * Call it after receive header, used in LIN slave mode with id software-filtered.
 *
 * @param instance LIN Hardware Interface instance number
 * @return function always return STATUS_SUCCESS
 */
status_t LINFlexD_DRV_DataDiscard(uint32_t instance);

/*!
 * @brief Aborts an on-going non-blocking transmission/reception.
 *  While performing a non-blocking transferring data, users can call this function
 *  to terminate immediately the transferring.
 *
 * @param instance LIN Hardware Interface instance number
 * @return function always return STATUS_SUCCESS
 */
status_t LINFlexD_DRV_AbortTransferData(uint32_t instance);

/*!
 * @brief Puts current LIN node to sleep mode
 * This function changes current node state to LINFlexD_NODE_STATE_SLEEP_MODE
 *
 * @param instance LIN Hardware Interface instance number
 * @return function always return STATUS_SUCCESS
 */
status_t LINFlexD_DRV_GoToSleepMode(uint32_t instance);

/*!
 * @brief Puts current LIN node to Idle state
 * This function changes current node state to LINFlexD_NODE_STATE_IDLE
 *
 * @param instance LIN Hardware Interface instance number
 * @return function always return STATUS_SUCCESS
 */
status_t LINFlexD_DRV_GotoIdleState(uint32_t instance);

/*!
 * @brief Sends a wakeup signal through the LIN Hardware Interface
 *
 * @param instance LIN Hardware Interface instance number
 * @return operation status:
 *         - STATUS_SUCCESS : Bus busy flag is false.
 *         - STATUS_BUSY    : Bus busy flag is true.
 */
status_t LINFlexD_DRV_SendWakeupSignal(uint32_t instance);

/*!
 * @brief Get the current LIN node state
 *
 * @param instance LIN Hardware Interface instance number
 * @return current LIN node state
 */
linflexd_node_state_t LINFlexD_DRV_GetCurrentNodeState(uint32_t instance);

/*!
 * @brief Callback function for Timer Interrupt Handler
 * Users may use (optional, not required) LINFlexD_DRV_TimeoutService to check if timeout has occurred during non-blocking frame data
 * transmission and reception. User may initialize a timer (for example FTM) in Output Compare Mode
 * with period of 500 micro seconds (recommended). In timer IRQ handler, call this function.
 *
 * @param instance LIN Hardware Interface instance number
 * @return void
 */
void LINFlexD_DRV_TimeoutService(uint32_t instance);

/*!
 * @brief Set Value for Timeout Counter that is used in LINFlexD_DRV_TimeoutService
 *
 * @param instance LIN Hardware Interface instance number
 * @param timeoutValue  Timeout Value to be set
 * @return void
 */
void LINFlexD_DRV_SetTimeoutCounter(uint32_t instance,
                                    uint32_t timeoutValue);

/*!
 * @brief Enables LIN hardware interrupts.
 *
 * @param instance LIN Hardware Interface instance number.
 * @return function always return STATUS_SUCCESS.
 */
status_t LINFlexD_DRV_EnableIRQ(uint32_t instance);

/*!
 * @brief Disables LIN hardware interrupts.
 *
 * @param instance LIN Hardware Interface instance number
 * @return function always return STATUS_SUCCESS.
 */
status_t LINFlexD_DRV_DisableIRQ(uint32_t instance);

/*!
 * @brief Interrupt handler for LIN Hardware Interface.
 *
 * @param instance LIN Hardware Interface instance number
 * @return void
 */
void LINFlexD_DRV_IRQHandler(uint32_t instance);

/*!
 * @brief Handle ID filter for auto transmission.
 *
 * @param instance LIN Hardware Interface instance number
 * @param direction The direction of current transmission.
 * @return void
 */
void LINFlexD_LIN_DRV_FilterResponse(uint32_t instance, linflexd_direction_t direction);

/*!
 * @brief Get match ID of filter.
 *
 * @param instance LIN Hardware Interface instance number
 * @return The match ID
 */
uint8_t LINFlexD_GetFilterMatchId(uint32_t instance);

/*!
 * @brief Get checksum type of current frame.
 *
 * @param instance LIN Hardware Interface instance number
 * @param ID The ID of current frame.
 * @return The checksum type
 */
linflexd_cs_t LINFlexD_DRV_GetChecksumType(uint32_t instance, uint8_t ID);

/*!
 * @brief Makes or checks parity bits. If action is checking parity, the function
 * returns ID value if parity bits are correct or 0xFF if parity bits are incorrect. If action
 * is making parity bits, then from input value of ID, the function returns PID.
 * This is not a public API as it is called by other API functions.
 *
 * @param PID PID byte in case of checking parity bits or ID byte in case of making parity bits.
 * @param typeAction: 1 for Checking parity bits, 0 for making parity bits
 * @return Value has 8 bit:
 *         - 0xFF : Parity bits are incorrect,
 *         - ID   : Checking parity bits are correct.
 *         - PID  : typeAction is making parity bits.
 */
uint8_t LINFlexD_DRV_ProcessParity(uint8_t PID, uint8_t typeAction);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* LINFlexD_DRIVER_LIN_H */
/******************************************************************************/
/* EOF */
/******************************************************************************/
