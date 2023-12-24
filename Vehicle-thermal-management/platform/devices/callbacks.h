/*
 * Copyright 2020-2022 Yuntu Microelectronics co.,ltd
 * All rights reserved.
 *
 * YUNTU Confidential. This software is owned or controlled by YUNTU and may only
 * be used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 */

#ifndef CALLBACKS_H
#define CALLBACKS_H
#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

 /*!
 * @brief Define the enum of the events which can trigger I2C slave callback
 *
 * This enum should include the events for all platforms
 */
typedef enum
{
    I2C_SLAVE_EVENT_RX_FULL = 0x00U,
    I2C_SLAVE_EVENT_TX_EMPTY = 0x01U,
    I2C_SLAVE_EVENT_TX_REQ = 0x02U,
    I2C_SLAVE_EVENT_RX_REQ = 0x03U,
    I2C_SLAVE_EVENT_STOP = 0X04U,
}i2c_slave_event_t;

 /*!
 * @brief Define the enum of the events which can trigger I2C master callback
 *
 * This enum should include the events for all platforms
 *
 */
typedef enum
{
    I2C_MASTER_EVENT_TX_END                            = 0x0U,
    I2C_MASTER_EVENT_RX_END                            = 0x1U,
    I2C_MASTER_EVENT_FIFO_ERROR_REQ                    = 0x2U,
    I2C_MASTER_EVENT_ARBITRATION_LOST_ERROR            = 0x3U,
    I2C_MASTER_EVENT_NACK_DETECT                       = 0x4U,
    I2C_MASTER_EVENT_END_TRANSFER                      = 0x5U,
}i2c_master_event_t;


/* Callback for all peripherals which supports I2C features for slave mode */
typedef void (*i2c_slave_callback_t)(i2c_slave_event_t event, void *userData);

/* Callback for all peripherals which supports I2C features for master mode */
typedef void (*i2c_master_callback_t)(i2c_master_event_t event, void *userData);

/* Define the enum of the events which can trigger SPI callback
 * This enum should include the events for all platforms
 */
typedef enum
{
    SPI_EVENT_END_TRANSFER = 0
} spi_event_t;

/* Callback for all peripherals which supports SPI features */
typedef void (*spi_callback_t)(void *driverState, spi_event_t event, void *userData);

/*!
 * @brief Define the enum of the events which can trigger UART callback
 *
 * This enum should include the events for all platforms
 *
 * Implements : uart_event_t_Class
 */
typedef enum
{
    UART_EVENT_RX_FULL      = 0x00U,    /*!< Rx buffer is full */
    UART_EVENT_TX_EMPTY     = 0x01U,    /*!< Tx buffer is empty */
    UART_EVENT_END_TRANSFER = 0x02U,    /*!< The current transfer is ending */
    UART_EVENT_ERROR        = 0x03U,    /*!< An error occured during transfer */
    UART_EVENT_TIMEOUT      = 0x04U,    /*!< Uart TimeOut */

} uart_event_t;

/*!
 * @brief Callback for all peripherals which support UART features
 *
 * Implements : uart_callback_t_Class
 */
typedef void (*uart_callback_t)(void *driverState, uart_event_t event, void *userData);


/* Callback for all peripherals which support TIMING features */
typedef void (*timer_callback_t)(void *userData);


/*! @brief Defines a structure used to pass information to the ADC PAL callback
 *
 * Implements : adc_callback_info_t_Class
 */
typedef struct
{
    uint32_t groupIndex;         /*!< Index of the group executing the callback. */
    uint16_t resultBufferTail;   /*!< Offset of the most recent conversion result in the result buffer. */
} adc_callback_info_t;

/*! @brief Defines the callback used to be called by ADC PAL after the last conversion result in a group
 * has been copied to the result buffer.
 */
typedef void (* const adc_callback_t)(const adc_callback_info_t * const callbackInfo, void * userData);


/*! @brief Define the enum of the events which can trigger CAN callback
 *  This enum should include the events for all platforms
 *  Implements : can_event_t_Class
 */
typedef enum {
    CAN_EVENT_RX_COMPLETE,     /*!< A frame was received in the configured Rx buffer. */
    CAN_EVENT_TX_COMPLETE,     /*!< A frame was sent from the configured Tx buffer. */
    CAN_EVENT_SELF_WAKEUP      /*!< A Self wake up event. */
} can_event_t;

/*! @brief Callback for all peripherals which support CAN features
 * Implements : can_callback_t_Class
 */
typedef void (*can_callback_t)(uint32_t instance,
                               can_event_t eventType,
                               uint32_t objIdx,
                               void *driverState);

/*!
 * @brief Callback for security modules
 * Implements : security_callback_t_Class
 */
typedef void (*security_callback_t)(uint32_t completedCmd, void *callbackParam);

/* Define the enum of the events which can trigger the output compare callback */
typedef enum
{
    OC_EVENT_GENERATION_OUTPUT_COMPLETE = 0x00U    /*!< Generation output signal is completed */
} oc_event_t;

/* Callback for all peripherals which support OC feature */
typedef void (*oc_callback_t)(oc_event_t event, void *userData);
/* Define the enum of the events which can trigger the input capture callback */
typedef enum
{
    IC_EVENT_MEASUREMENT_COMPLETE = 0x00U    /*!< Capture input signal is completed */
} ic_event_t;

/* Callback for all peripherals which support IC feature */
typedef void (*ic_callback_t)(ic_event_t event, void *userData);

#endif /* CALLBACKS_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
