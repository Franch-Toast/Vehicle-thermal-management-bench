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
 * @file linflexd_hw_access.h
 */

#ifndef LINFlexD_HW_ACCESS_H
#define LINFlexD_HW_ACCESS_H

#include "device_registers.h"
#include "linflexd_uart_driver.h"
#include "linflexd_lin_driver.h"
#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEFAULT_OSR 16U
#define BAUDRATE_FRACTION_WIDTH LINFlexD_LINFBRR_FBR_WIDTH

typedef float float32_t;

/*! @brief LINFlexD mode: UART/LIN. */
typedef enum
{
    LINFlexD_LIN_MODE = 0U,
    LINFlexD_UART_MODE = 1U
} linflexd_mode_t;

/*! @brief UART Mode: FIFO/BUFFER. */
typedef enum
{
    LINFlexD_UART_RXTX_BUFFER_MODE = 0U,
    LINFlexD_UART_RXTX_FIFO_MODE = 1U
} linflexd_uart_rxtx_mode_t;

/*! @brief LINFlexD state. */
typedef enum
{
    LINFlexD_STATE_SLEEP_MODE = 0U,
    LINFlexD_STATE_INIT_MODE = 1U,
    LINFlexD_STATE_IDLE_MODE = 2U,
    LINFlexD_STATE_SYNC_BREAK = 3U,
    LINFlexD_STATE_SYNC_DEL = 4U,
    LINFlexD_STATE_SYNC_FIELD = 5U,
    LINFlexD_STATE_IDENTIFIER_FIELD = 6U,
    LINFlexD_STATE_HEADER_RX_TX = 7U,
    LINFlexD_STATE_DATA_RX_TX = 8U,
    LINFlexD_STATE_CHECKSUM = 9U
} linflexd_hw_state_t;

/*! @brief UART Status flags.
 *  These identifiers provide both mask and shift for status bits in UARTSR register.
 */
typedef enum
{
    LINFlexD_UART_NOISE_FLAG = LINFlexD_UARTSR_NF_MASK,
    LINFlexD_UART_DATA_TRANSMITTED_FLAG = LINFlexD_UARTSR_DTF_TFF_MASK,
    LINFlexD_UART_DATA_RECEPTION_COMPLETE_FLAG = LINFlexD_UARTSR_DRF_RFE_MASK,
    LINFlexD_UART_TIMEOUT_FLAG = LINFlexD_UARTSR_TO_MASK,
    LINFlexD_UART_WAKEUP_FLAG = LINFlexD_UARTSR_WUF_MASK,
    LINFlexD_UART_RECEIVER_INPUT_STATE_FLAG = LINFlexD_UARTSR_RDI_MASK,
    LINFlexD_UART_BUFFER_OVERRUN_FLAG = LINFlexD_UARTSR_BOF_MASK,
    LINFlexD_UART_FRAME_ERROR_FLAG = LINFlexD_UARTSR_FEF_MASK,
    LINFlexD_UART_MESSAGE_BUFFER_FULL_FLAG = LINFlexD_UARTSR_RMB_MASK,
    LINFlexD_UART_PARITY_ERROR_FLAG = LINFlexD_UARTSR_PE_MASK,
    LINFlexD_UART_OUTPUT_COMPARE_FLAG = LINFlexD_UARTSR_OCF_MASK,
    LINFlexD_UART_STUCK_AT_ZERO_FLAG = LINFlexD_UARTSR_SZF_MASK,
} linflexd_uart_status_flag_t;

/*! @brief LIN Status flags.
 *  These identifiers provide both mask and shift for status bits in LINSR register.
 */
typedef enum
{
#if (FEATURE_LINFlexD_HAS_RED_IRQ)
    LINFlexD_LIN_RECEIVE_EDGE_DETECTION_FLAG = LINFlexD_LINSR_REDF_MASK,
#endif /* FEATURE_LINFlexD_HAS_RED_IRQ */
    LINFlexD_LIN_RELEASE_MESSAGE_BUFFER_FLAG = LINFlexD_LINSR_RMB_MASK,
    LINFlexD_LIN_RX_DATA_START_FLAG = LINFlexD_LINSR_DRBNE_MASK,
    LINFlexD_LIN_WAKEUP_FLAG = LINFlexD_LINSR_WUF_MASK,
    LINFlexD_LIN_DATA_RECEPTION_COMPLETE_FLAG = LINFlexD_LINSR_DRF_MASK,
    LINFlexD_LIN_DATA_TRANSMITTED_FLAG = LINFlexD_LINSR_DTF_MASK,
    LINFlexD_LIN_HEADER_RECEIVED_FLAG = LINFlexD_LINSR_HRF_MASK
} linflexd_lin_status_flag_t;

/*! @brief LINFlexD interrupts.
 *  These identifiers provide both mask and shift for the interrupt enable bits in LINIER register.
 */
typedef enum
{
    LINFlexD_HEADER_RECEIVED_INT = LINFlexD_LINIER_HRIE_MASK,
    LINFlexD_DATA_TRANSMITTED_INT = LINFlexD_LINIER_DTIE_MASK,
    LINFlexD_DATA_RECEPTION_COMPLETE_INT = LINFlexD_LINIER_DRIE_MASK,
    LINFlexD_UART_TIMEOUT_ERROR_INT = LINFlexD_LINIER_TOIE_MASK,
    LINFlexD_WAKEUP_INT = LINFlexD_LINIER_WUIE_MASK,
    LINFlexD_LIN_STATE_INT = LINFlexD_LINIER_LSIE_MASK,
    LINFlexD_BUFFER_OVERRUN_INT = LINFlexD_LINIER_BOIE_MASK,
    LINFlexD_FRAME_ERROR_INT = LINFlexD_LINIER_FEIE_MASK,
    LINFlexD_HEADER_ERROR_INT = LINFlexD_LINIER_HEIE_MASK,
    LINFlexD_CHECKSUM_ERROR_INT = LINFlexD_LINIER_CEIE_MASK,
    LINFlexD_BIT_ERROR_INT = LINFlexD_LINIER_BEIE_MASK,
    LINFlexD_OUTPUT_COMPARE_INT = LINFlexD_LINIER_OCIE_MASK,
    LINFlexD_STUCK_AT_ZERO_INT = LINFlexD_LINIER_SZIE_MASK,
#if (FEATURE_LINFlexD_HAS_RED_IRQ)
    LINFlexD_RECEIVE_EDGE_DETECTION_INT = LINFlexD_LINIER_REDIE_MASK,
#if (FEATURE_LINFlexD_HAS_STA_IRQ)
    LINFlexD_START_DETECTION_INT = LINFlexD_LINIER_SDIE_MASK,
#endif

#endif /* FEATURE_LINFlexD_HAS_RED_IRQ */
} linflexd_interrupt_t;

/*! @brief LINFlexD error status flag.
 *  These identifiers provide both mask and shift for the status flag bits in LINESR register.
 */
typedef enum
{
    LINFlexD_LIN_NOISE_FLAG = LINFlexD_LINESR_NF_MASK,
    LINFlexD_LIN_BUFFER_OVERRUN_FLAG = LINFlexD_LINESR_BOF_MASK,
    LINFlexD_LIN_FRAMING_ERROR_FLAG = LINFlexD_LINESR_FEF_MASK,
    LINFlexD_LIN_ID_PARITY_ERROR_FLAG = LINFlexD_LINESR_IDPEF_MASK,
    LINFlexD_LIN_BREAK_DELIMITER_ERROR_FLAG = LINFlexD_LINESR_SDEF_MASK,
    LINFlexD_LIN_SYNC_FIELD_ERROR_FLAG = LINFlexD_LINESR_SFEF_MASK,
    LINFlexD_LIN_CHECKSUM_ERROR_FLAG = LINFlexD_LINESR_CEF_MASK,
    LINFlexD_LIN_BIT_ERROR_FLAG = LINFlexD_LINESR_BEF_MASK,
    LINFlexD_LIN_OUTPUT_COMPARE_FLAG = LINFlexD_LINESR_OCF_MASK,
    LINFlexD_LIN_STUCK_AT_ZERO_FLAG = LINFlexD_LINESR_SZF_MASK,
} linflexd_lin_error_status_flag_t;

#if defined(__cplusplus)
extern "C"
{
#endif

    /*!
     * @brief Requests LINFlexD module to enter init mode.
     *
     * This function enters initialization mode.
     *
     * @param base LINFlexD base pointer.
     */
    static inline void LINFlexD_EnterInitMode(LINFlexD_Type *base)
    {
        uint32_t regValTemp;

        regValTemp = base->LINCR1;
        /* Exit sleep mode */
        regValTemp &= ~(LINFlexD_LINCR1_SLEEP_MASK);
        /* Enter init mode. */
        regValTemp |= LINFlexD_LINCR1_INIT(1UL);
        base->LINCR1 = regValTemp;
    }

    /*!
     * @brief Requests LINFlexD module to enter normal mode.
     *
     * This function enters normal mode. *
     *
     * @param base LINFlexD base pointer.
     */
    static inline void LINFlexD_EnterNormalMode(LINFlexD_Type *base)
    {
        uint32_t regValTemp;

        regValTemp = base->LINCR1;
        /* Exit sleep mode */
        regValTemp &= ~(LINFlexD_LINCR1_SLEEP_MASK);
        regValTemp &= ~(LINFlexD_LINCR1_INIT_MASK);
        /* Exit init mode. */
        base->LINCR1 = regValTemp;
    }

    /*!
     * @brief Requests LINFlexD module to enter sleep mode.
     *
     * This function enters sleep mode. *
     *
     * @param base LINFlexD base pointer.
     * @param enable LINFlexD sleep mode enable.
     */
    static inline void LINFlexD_SetSleepMode(LINFlexD_Type *base, bool enable)
    {
        uint32_t regValTemp;

        regValTemp = base->LINCR1;
        regValTemp |= LINFlexD_LINCR1_SLEEP(enable ? 1U : 0U);
        base->LINCR1 = regValTemp;
    }
    /*!
     * @brief Get LINFlexD module sleep mode.
     *
     * This function get sleep mode status. *
     *
     * @param base LINFlexD base pointer.
     */
    static inline bool LINFlexD_GetSleepMode(LINFlexD_Type *base)
    {
        return (bool)((base->LINCR1 & LINFlexD_LINCR1_SLEEP_MASK) != 0);
    }

    /*!
     * @brief Sets the LINFlexD mode.
     *
     * This function sets LIN MASTER or SLAVE mode, based on the parameter received.
     *
     * @param base LINFlexD base pointer.
     * @param masterMode LINFlexD lin mode - LIN_MASTER/LIN_SLAVE.
     */
    static inline void LINFlexD_Init(LINFlexD_Type *base, bool masterMode, linflexd_break_length_t breakLength)
    {
        base->LINCR1 = LINFlexD_LINCR1_NLSE(1U)           /* capture lin state */
                       | LINFlexD_LINCR1_CCD(0U)          /* hardware checksum */
                       | LINFlexD_LINCR1_CFD(0U)          /* hardware checksum sent by default */
                       | LINFlexD_LINCR1_LASE(0U)         /* disable auto synchronization */
                       | LINFlexD_LINCR1_AUTOWU(1U)       /* automatic wakeup enable */
                       | LINFlexD_LINCR1_MBL(breakLength) /* master send break length */
                       | LINFlexD_LINCR1_BF(0x1U)         /* Bypass receive filter */
                       | LINFlexD_LINCR1_LBKM(0x0U)       /* Disable loop back mode */
                       | LINFlexD_LINCR1_SSBL(0x1U)       /* 10 bit break length detect */
                       | LINFlexD_LINCR1_RBLM(0x1U)       /* Lock rx buffer overrun */
                       | LINFlexD_LINCR1_INIT(0x1U)       /* Keep in init mode */
                       | LINFlexD_LINCR1_MME(masterMode); /* set master or slave mode */
        
    }
    /*!
     * @brief Sets the LINFlexD interrupt mode.
     *
     * This function sets LIN default interrupt mode.
     *
     * @param base LINFlexD base pointer.
     */
    static inline void LINFlexD_IntInit(LINFlexD_Type *base)
    {
        base->LINIER =    LINFlexD_LINIER_SZIE(0U)      /* Stuck at zero interrupt enable */
                          | LINFlexD_LINIER_OCIE(1U)      /* Output Compare Interrupt enable */
                          | LINFlexD_LINIER_BEIE(1U)      /* Bit error */
                          | LINFlexD_LINIER_CEIE(1U)      /* Checksum error */
                          | LINFlexD_LINIER_HEIE(1U)      /* Header error */
                          | LINFlexD_LINIER_FEIE(1U)      /* Frame error */
                          | LINFlexD_LINIER_BOIE(1U)      /* Buffer overrun error */
                          | LINFlexD_LINIER_LSIE(0U)      /* LIN state change */
                          | LINFlexD_LINIER_WUIE(1U)      /* Wakeup interrupt */
                          | LINFlexD_LINIER_TOIE(1U)      /* Timeout interrupt enable */
                          | LINFlexD_LINIER_DRIE(1U)      /* Data reception complete */
                          | LINFlexD_LINIER_DTIE(1U)      /* Data transmitted complete */
                          | LINFlexD_LINIER_HRIE(1U);     /* Header received */
    }

    /*!
     * @brief Sets the LINFlexD autosynchronization,.
     *
     * This function sets autosynchronization.
     *
     * @param base LINFlexD base pointer.
     * @param enable autosynchronization enable.
     */
    static inline void LINFlexD_AutoSyncEnable(LINFlexD_Type *base, bool enable)
    {
        uint32_t regValTemp;

        regValTemp = base->LINCR1;
        regValTemp &= ~(LINFlexD_LINCR1_LASE_MASK);
        regValTemp |= LINFlexD_LINCR1_LASE((uint32_t)enable);
        base->LINCR1 = regValTemp;
    }

    /*!
     * @brief Sets the LINFlexD BIDR direction.
     *
     * This function sets LIN master transfer direction, based on the parameter received.
     *
     * @param base LINFlexD base pointer.
     * @param dir LINFlexD direction
     */
    static inline void LINFlexD_SetLinDirection(LINFlexD_Type *base, linflexd_direction_t dir)
    {
        uint32_t regValTemp;

        regValTemp = base->BIDR;
        regValTemp &= ~(LINFlexD_BIDR_DIR_MASK);
        regValTemp |= LINFlexD_BIDR_DIR((uint32_t)dir);
        base->BIDR = regValTemp;
    }
    /*!
     * @brief Sets the LINFlexD BIDR data length
     *
     * This function sets LIN transfer size, based on the parameter received.
     *
     * @param base LINFlexD base pointer.
     * @param size LINFlexD data size
     */
    static inline void LINFlexD_SetLinDataLength(LINFlexD_Type *base, uint8_t size)
    {
        uint32_t regValTemp;

        regValTemp = base->BIDR;
        regValTemp &= ~(LINFlexD_BIDR_DFL_MASK);
        regValTemp |= LINFlexD_BIDR_DFL(size - 1);
        base->BIDR = regValTemp;
    }
    /*!
     * @brief Sets the LINFlexD BIDR Register
     *
     * This function sets LIN transfer, based on the parameter received.
     *
     * @param base LINFlexD base pointer.
     * @param id LINFlexD ID
     * @param size LINFlexD data size
     * @param dir LINFlexD direction
     * @param ccs Classic checksum or enhanced checksum selected.
     */
    static inline void LINFlexD_SetLinBIDR(LINFlexD_Type *base,
                                           uint8_t id,
                                           uint8_t size,
                                           int8_t dir,
                                           int8_t ccs)
    {
        base->BIDR = LINFlexD_BIDR_DFL(size - 1U) |
                     LINFlexD_BIDR_DIR(dir) |
                     LINFlexD_BIDR_CCS(ccs) |
                     LINFlexD_BIDR_ID(id);
    }
    /*!
     * @brief Sets the LINFlexD Set Header Request
     *
     * This function sets LIN transfer size, based on the parameter received.
     *
     * @param base LINFlexD base pointer.
     */
    static inline void LINFlexD_SetHeaderRequest(LINFlexD_Type *base)
    {
        base->LINCR2 |= LINFlexD_LINCR2_HTRQ_MASK;
    }
    /*!
     * @brief Sets the LINFlexD Set Data Request
     *
     *
     * @param base LINFlexD base pointer.
     */
    static inline void LINFlexD_SetDataRequest(LINFlexD_Type *base)
    {
        base->LINCR2 |= LINFlexD_LINCR2_DTRQ_MASK;
    }
    /*!
     * @brief Sets the LINFlexD Wakeup Request
     *
     * @param base LINFlexD base pointer.
     */
    static inline void LINFlexD_SetWakeupRequest(LINFlexD_Type *base)
    {
        base->LINCR2 |= LINFlexD_LINCR2_WURQ_MASK;
    }
    /*!
     * @brief Enable/Disable Data Discard Request
     *
     * This function enable or disable LIN discard received data.
     *
     * @param base LINFlexD base pointer.
     * @param enable Discard data enable.
     */
    static inline void LINFlexD_DataDiscard(LINFlexD_Type *base, bool enable)
    {
        uint32_t reg = base->LINCR2;
        reg &= ~(LINFlexD_LINCR2_DDRQ_MASK);
        base->LINCR2 = reg | (LINFlexD_LINCR2_DDRQ(enable));
    }
    /*!
     * @brief Enable/Disable Transfer abort request
     *
     * This function enable or disable LIN transfer abort.
     *
     * @param base LINFlexD base pointer.
     * @param enable Abort transfer enable.
     */
    static inline void LINFlexD_SetTransferAbort(LINFlexD_Type *base, bool enable)
    {
        base->LINCR2 |= LINFlexD_LINCR2_ABRQ_MASK;
        uint32_t reg = base->LINCR2;
        reg &= ~(LINFlexD_LINCR2_ABRQ_MASK);
        base->LINCR2 = reg | LINFlexD_LINCR2_ABRQ(enable);
    }
    /*!
     * @brief Get Transfer abort request
     *
     * This function get LIN transfer abort status.
     *
     * @param base LINFlexD base pointer.
     */
    static inline bool LINFlexD_GetTransferAbort(LINFlexD_Type *base)
    {
        return ((base->LINCR2 & LINFlexD_LINCR2_ABRQ_MASK) != 0U);
    }

    /*!
     * @brief Sets the LINFlexD BIDR id
     *
     * This function sets LIN transfer id, based on the parameter received.
     *
     * @param base LINFlexD base pointer.
     * @param id LINFlexD id
     */
    static inline void LINFlexD_SetLinBidrID(LINFlexD_Type *base, uint8_t id)
    {
        uint32_t regValTemp;

        regValTemp = base->BIDR;
        regValTemp &= ~(LINFlexD_BIDR_ID_MASK);
        regValTemp |= LINFlexD_BIDR_ID(id);
        base->BIDR = regValTemp;
    }

    /*!
     * @brief Gets the LINFlexD BIDR id
     *
     * This function gets LIN transfer id, based on the parameter received.
     *
     * @param base LINFlexD base pointer.
     * @return LINFlexD id
     */
    static inline uint8_t LINFlexD_GetLinBidrID(LINFlexD_Type *base)
    {
        return (uint8_t)((base->BIDR & LINFlexD_BIDR_ID_MASK) >> LINFlexD_BIDR_ID_SHIFT);
    }

    /*!
     * @brief Sets the LINFlexD mode.
     *
     * This function sets LIN or UART mode, based on the parameter received.
     *
     * @param base LINFlexD base pointer.
     * @param mode LINFlexD mode - UART/LIN.
     */
    static inline void LINFlexD_SetMode(LINFlexD_Type *base, linflexd_mode_t mode)
    {
        uint32_t regValTemp;

        regValTemp = base->UARTCR;
        regValTemp &= ~(LINFlexD_UARTCR_UART_MASK);
        regValTemp |= LINFlexD_UARTCR_UART((uint32_t)mode);
        base->UARTCR = regValTemp;
    }

    /*!
     * @brief Returns the current LINFlexD state.
     *
     * This function returns the state of the LINFlexD instance. The possible states are:
     *    - Sleep mode
     *    - Init mode
     *    - Idle mode
     *    - Sync Break Reception/Transmission
     *    - Sync Delimiter Reception/Transmission
     *    - Sync Field Reception/Transmission
     *    - Identifier Field Reception/Transmission
     *    - Header Reception/Transmission
     *    - Data Reception/Transmission
     *    - Checksum Reception/Transmission
     *
     * @param base LINFlexD base pointer.
     * @return LINFlexD mode - UART/LIN.
     */
    static inline linflexd_hw_state_t LINFlexD_GetLinState(const LINFlexD_Type *base)
    {
        uint8_t state = (uint8_t)((base->LINSR & LINFlexD_LINSR_LINS_MASK) >> LINFlexD_LINSR_LINS_SHIFT);
        return (linflexd_hw_state_t)state;
    }

    /*!
     * @brief Sets the word length.
     *
     * This function sets the word length in UART mode.
     * Should be called only when the module is in init mode.
     *
     * @param base LINFlexD base pointer.
     * @param length UART mode word length.
     */
    static inline void LINFlexD_SetUartWordLength(LINFlexD_Type *base, linflexd_uart_word_length_t length)
    {
        uint32_t regValTemp;

        regValTemp = base->UARTCR;
        regValTemp &= ~(LINFlexD_UARTCR_WL0_MASK);
        regValTemp |= LINFlexD_UARTCR_WL0((uint32_t)length & 1U);
        regValTemp &= ~(LINFlexD_UARTCR_WL1_MASK);
        regValTemp |= LINFlexD_UARTCR_WL1(((uint32_t)length >> 1U) & 1U);
        base->UARTCR = regValTemp;
    }

    /*!
     * @brief Enables/disables parity bit.
     *
     * This function enables or disables the parity bit from UART bytes.
     * Should be called only when the module is in init mode.
     *
     * @param base LINFlexD base pointer.
     * @param enable true - enable parity queuing/checking, false - disable parity queuing/checking.
     */
    static inline void LINFlexD_SetParityControl(LINFlexD_Type *base, bool enable)
    {
        uint32_t regValTemp;

        regValTemp = base->UARTCR;
        regValTemp &= ~(LINFlexD_UARTCR_PCE_MASK);
        regValTemp |= LINFlexD_UARTCR_PCE(enable ? 1UL : 0UL);
        base->UARTCR = regValTemp;
    }

    /*!
     * @brief Sets parity type.
     *
     * This function sets the type of parity to be used for UART bytes. Available options are:
     *    - odd
     *    - even
     *    - always 0
     *    - always 1
     * Should be called only when the module is in init mode.
     *
     * @param base LINFlexD base pointer.
     * @param parityType the type of parity.
     */
    static inline void LINFlexD_SetParityType(LINFlexD_Type *base, linflexd_uart_parity_type_t parityType)
    {
        uint32_t regValTemp;

        regValTemp = base->UARTCR;
        regValTemp &= ~(LINFlexD_UARTCR_PC0_MASK);
        regValTemp |= LINFlexD_UARTCR_PC0((uint32_t)parityType & 1U);
        regValTemp &= ~(LINFlexD_UARTCR_PC1_MASK);
        regValTemp |= LINFlexD_UARTCR_PC1(((uint32_t)parityType >> 1U) & 1U);
        base->UARTCR = regValTemp;
    }

    /*!
     * @brief Enables/disables transmitter.
     *
     * This function enables or disables the UART transmitter, based on the parameter received.
     * Should be called only when the module is in UART mode.
     *
     * @param base LINFlexD base pointer.
     * @param enable enable/disable transmitter.
     */
    static inline void LINFlexD_SetTransmitterState(LINFlexD_Type *base, bool enable)
    {
        uint32_t regValTemp;

        regValTemp = base->UARTCR;
        regValTemp &= ~(LINFlexD_UARTCR_TxEn_MASK);
        regValTemp |= LINFlexD_UARTCR_TxEn(enable ? 1UL : 0UL);
        base->UARTCR = regValTemp;
    }

    /*!
     * @brief Enables/disables receiver.
     *
     * This function enables or disables the UART receiver, based on the parameter received.
     * Should be called only when the module is in UART mode.
     *
     * @param base LINFlexD base pointer.
     * @param enable enable/disable receiver.
     */
    static inline void LINFlexD_SetReceiverState(LINFlexD_Type *base, bool enable)
    {
        uint32_t regValTemp;

        regValTemp = base->UARTCR;
        regValTemp &= ~(LINFlexD_UARTCR_RxEn_MASK);
        regValTemp |= LINFlexD_UARTCR_RxEn(enable ? 1UL : 0UL);
        base->UARTCR = regValTemp;
    }

    /*!
     * @brief Sets the transmission mode (FIFO/Buffer).
     *
     * This function sets the transmission mode (FIFO/Buffer).
     * Should be called only when the module is in init mode.
     *
     * @param base LINFlexD base pointer.
     * @param mode tx mode: FIFO/Buffer.
     */
    static inline void LINFlexD_SetTxMode(LINFlexD_Type *base, linflexd_uart_rxtx_mode_t mode)
    {
        uint32_t regValTemp;

        regValTemp = base->UARTCR;
        regValTemp &= ~(LINFlexD_UARTCR_TFBM_MASK);
        regValTemp |= LINFlexD_UARTCR_TFBM((uint32_t)mode);
        base->UARTCR = regValTemp;
    }

    /*!
     * @brief Sets the reception mode (FIFO/Buffer).
     *
     * This function sets the reception mode (FIFO/Buffer).
     * Should be called only when the module is in init mode.
     *
     * @param base LINFlexD base pointer.
     * @param mode rx mode: FIFO/Buffer.
     */
    static inline void LINFlexD_SetRxMode(LINFlexD_Type *base, linflexd_uart_rxtx_mode_t mode)
    {
        uint32_t regValTemp;

        regValTemp = base->UARTCR;
        regValTemp &= ~(LINFlexD_UARTCR_RFBM_MASK);
        regValTemp |= LINFlexD_UARTCR_RFBM((uint32_t)mode);
        base->UARTCR = regValTemp;
    }

    /*!
     * @brief Sets the reception data field length/FIFO depth.
     *
     * This function sets either the reception data field length or the number of bytes in the Rx FIFO, according to
     * the current reception mode.
     *
     * @param base LINFlexD base pointer.
     * @param length data field length/FIFO depth.
     */
    static inline void LINFlexD_SetRxDataFieldLength(LINFlexD_Type *base, uint8_t length)
    {
        uint32_t regValTemp;

        regValTemp = base->UARTCR;
        regValTemp &= ~(LINFlexD_UARTCR_RDFL_RFC_MASK);
        regValTemp |= LINFlexD_UARTCR_RDFL_RFC(length);
        base->UARTCR = regValTemp;
    }

    /*!
     * @brief Sets the transmission data field length/FIFO depth.
     *
     * This function sets either the transmission data field length or the number of bytes in the Tx FIFO, according to
     * the current transmission mode.
     * Should be called only when the module is in init mode.
     *
     * @param base LINFlexD base pointer.
     * @param length data field length/FIFO depth.
     */
    static inline void LINFlexD_SetTxDataFieldLength(LINFlexD_Type *base, uint8_t length)
    {
        uint32_t regValTemp;

        regValTemp = base->UARTCR;
        regValTemp &= ~(LINFlexD_UARTCR_TDFL_TFC_MASK);
        regValTemp |= LINFlexD_UARTCR_TDFL_TFC(length);
        base->UARTCR = regValTemp;
    }

    /*!
     * @brief Sets the number of stop bits for Rx.
     *
     * This function sets the number of stop bits for received bytes.
     *
     * @param base LINFlexD base pointer.
     * @param stopBitsCount number of stop bits.
     */
    static inline void LINFlexD_SetRxStopBitsCount(LINFlexD_Type *base, linflexd_uart_stop_bits_count_t stopBitsCount)
    {
        uint32_t regValTemp;

        regValTemp = base->UARTCR;
        regValTemp &= ~(LINFlexD_UARTCR_SBUR_MASK);
        regValTemp |= LINFlexD_UARTCR_SBUR(stopBitsCount);
        base->UARTCR = regValTemp;
    }

    /*!
     * @brief Sets the Monitor idle state.
     *
     * This function sets the uart Monitor idle state.
     *
     * @param base LINFlexD base pointer.
     * @param enable enable/disable receiver.
     */
    static inline void LINFlexD_SetMonitorIdleState(LINFlexD_Type *base, bool enable)
    {
        uint32_t regValTemp;

        regValTemp = base->UARTCR;
        regValTemp &= ~(LINFlexD_UARTCR_MIS_MASK);
        regValTemp |= LINFlexD_UARTCR_MIS(enable ? 1UL : 0UL);
        base->UARTCR = regValTemp;
    }

    /*!
     * @brief Sets the Monitor idle state.
     *
     * This function sets the uart disable timeout.
     *
     * @param base LINFlexD base pointer.
     * @param enable enable/disable receiver.
     */
    static inline void LINFlexD_SetDisableTimeout(LINFlexD_Type *base, bool enable)
    {
        uint32_t regValTemp;

        regValTemp = base->UARTCR;
        regValTemp &= ~(LINFlexD_UARTCR_DTU_MASK);
        regValTemp |= LINFlexD_UARTCR_DTU(enable ? 1UL : 0UL);
        base->UARTCR = regValTemp;
    }

    /*!
     * @brief Sets fractional baud rate.
     *
     * This function configures the bits that decide the fractional part of the LIN Baud Rate.
     * Should be called only when the module is in init mode.
     *
     * @param base LINFlexD base pointer.
     * @param fbr fractional baud rate.
     */
    static inline void LINFlexD_SetFractionalBaudRate(LINFlexD_Type *base, uint8_t fbr)
    {
        uint32_t regValTemp;

        regValTemp = base->LINFBRR;
        regValTemp &= ~(LINFlexD_LINFBRR_FBR_MASK);
        regValTemp |= LINFlexD_LINFBRR_FBR(fbr);
        base->LINFBRR = regValTemp;
    }

    /*!
     * @brief Gets fractional baud rate.
     *
     * This function returns the bits that decide the fractional part of the LIN Baud Rate.
     *
     * @param base LINFlexD base pointer.
     * @return fractional baud rate.
     */
    static inline uint8_t LINFlexD_GetFractionalBaudRate(const LINFlexD_Type *base)
    {
        return (uint8_t)((base->LINFBRR & LINFlexD_LINFBRR_FBR_MASK) >> LINFlexD_LINFBRR_FBR_SHIFT);
    }

    /*!
     * @brief Sets integer baud rate.
     *
     * This function configures the bits that decide the integer part of the LIN Baud Rate.
     * Should be called only when the module is in init mode.
     *
     * @param base LINFlexD base pointer.
     * @param fbr integer baud rate.
     */
    static inline void LINFlexD_SetIntegerBaudRate(LINFlexD_Type *base, uint32_t ibr)
    {
        uint32_t regValTemp;

        regValTemp = base->LINIBRR;
        regValTemp &= ~(LINFlexD_LINIBRR_IBR_MASK);
        regValTemp |= LINFlexD_LINIBRR_IBR(ibr);
        base->LINIBRR = regValTemp;
    }

    /*!
     * @brief Gets integer baud rate.
     *
     * This function returns the bits that decide the integer part of the LIN Baud Rate.
     *
     * @param base LINFlexD base pointer.
     * @return integer baud rate.
     */
    static inline uint32_t LINFlexD_GetIntegerBaudRate(const LINFlexD_Type *base)
    {
        return (uint32_t)((base->LINIBRR & LINFlexD_LINIBRR_IBR_MASK) >> LINFlexD_LINIBRR_IBR_SHIFT);
    }

    /*!
     * @brief Sets timeout enable.
     *
     * This function enable or disable timeout feature for LIN mode.
     *
     * @param base LINFlexD base pointer.
     * @param enable enable/disable timeout.
     */
    static inline void LINFlexD_EnableTimeout(LINFlexD_Type *base, const bool enable)
    {
        if (enable)
        {
            base->LINTCSR = LINFlexD_LINTCSR_IOT(1U) |
                            LINFlexD_LINTCSR_TOCE(1U) |
                            LINFlexD_LINTCSR_MODE(0U);
        }
        else
        {
            base->LINTCSR = LINFlexD_LINTCSR_IOT(0U) |
                            LINFlexD_LINTCSR_TOCE(0U) |
                            LINFlexD_LINTCSR_MODE(1U);
        }
    }
    /*!
     * @brief Sets timeout value.
     *
     * This function set lin response and header timeout value.
     *
     * @param base LINFlexD base pointer.
     * @param responseTimeout response timeout value.
     * @param headerTimeout header timeout value.
     */
    static inline void LINFlexD_SetTimeoutValue(LINFlexD_Type *base,
                                                const uint8_t responseTimeout,
                                                const uint8_t headerTimeout)
    {
        base->LINTOCR = LINFlexD_LINTOCR_RTO(responseTimeout) |
                        LINFlexD_LINTOCR_HTO(headerTimeout);
    }

    /*!
     * @brief Sets the number of stop bits for Tx.
     *
     * This function sets the number of stop bits for transmitted bytes.
     * Should be called only when the module is in init mode.
     *
     * @param base LINFlexD base pointer.
     * @param defaultOffset - true - use the memory map defined in the header file to access the register;
     *                      - false - use custom memory map to access the register.
     * @param stopBitsCount number of stop bits.
     */
    static inline void LINFlexD_SetTxStopBitsCount(LINFlexD_Type *base, linflexd_uart_stop_bits_count_t stopBitsCount,
                                                   bool defaultOffset)
    {
        uint32_t regValTemp;

#if (FEATURE_LINFlexD_HAS_DIFFERENT_MEM_MAP)
        if (!defaultOffset)
        {
            regValTemp = ((LINFlexD_0IFCR_Type *)base)->GCR;
            regValTemp &= ~(LINFlexD_GCR_STOP_MASK);
            regValTemp |= LINFlexD_GCR_STOP(stopBitsCount);
            ((LINFlexD_0IFCR_Type *)base)->GCR = regValTemp;
        }
        else
        {
            regValTemp = base->GCR;
            regValTemp &= ~(LINFlexD_GCR_STOP_MASK);
            regValTemp |= LINFlexD_GCR_STOP(stopBitsCount);
            base->GCR = regValTemp;
        }
#else
    (void)defaultOffset;
    regValTemp = base->GCR;
    regValTemp &= ~(LINFlexD_GCR_STOP_MASK);
    regValTemp |= LINFlexD_GCR_STOP(stopBitsCount);
    base->GCR = regValTemp;
#endif
    }

    /*!
     * @brief Clears an UART interrupt flag.
     *
     * This function clears the UART status flag received as parameter.
     *
     * @param base LINFlexD base pointer.
     * @param flag UART status flag.
     */
    static inline void LINFlexD_ClearStatusFlag(LINFlexD_Type *base, linflexd_uart_status_flag_t flag)
    {
        base->UARTSR = flag;
    }
    /*!
     * @brief Clears an LIN interrupt flag.
     *
     * This function clears the LIN status flag received as parameter.
     *
     * @param base LINFlexD base pointer.
     * @param flag LIN status flag.
     */
    static inline void LINFlexD_ClearLinStatusFlag(LINFlexD_Type *base, linflexd_lin_status_flag_t flag)
    {
        base->LINSR = flag;
    }
    /*!
     * @brief Clears an LIN error interrupt flag.
     *
     * This function clears the LIN error status flag received as parameter.
     *
     * @param base LINFlexD base pointer.
     * @param flag LIN error status flag.
     */
    static inline void LINFlexD_ClearLinErrorStatusFlag(LINFlexD_Type *base, linflexd_lin_error_status_flag_t flag)
    {
        base->LINESR = flag;
    }

    /*!
     * @brief Returns an UART interrupt flag.
     *
     * This function returns the value of the UART status flag received as parameter.
     *
     * @param base LINFlexD base pointer.
     * @param flag LIN status flag.
     * @return true - UART status flag set, false - UART status flag reset.
     */
    static inline bool LINFlexD_GetStatusFlag(const LINFlexD_Type *base, linflexd_uart_status_flag_t flag)
    {
        return ((base->UARTSR & (uint32_t)flag) != 0U);
    }
    /*!
     * @brief Returns an LIN interrupt flag.
     *
     * This function returns the value of the LIN status flag received as parameter.
     *
     * @param base LINFlexD base pointer.
     * @param flag LIN status flag.
     * @return true - LIN status flag set, false - LIN status flag reset.
     */
    static inline bool LINFlexD_GetLinStatusFlag(const LINFlexD_Type *base, linflexd_lin_status_flag_t flag)
    {
        return ((base->LINSR & (uint32_t)flag) != 0U);
    }
    /*!
     * @brief Returns an LIN error interrupt flag.
     *
     * This function returns the value of the LIN error status flag received as parameter.
     *
     * @param base LINFlexD base pointer.
     * @param flag LIN error status flag.
     * @return true - LIN error status flag set, false - LIN erro status flag reset.
     */
    static inline bool LINFlexD_GetLinErrorStatusFlag(const LINFlexD_Type *base, linflexd_lin_error_status_flag_t flag)
    {
        return ((base->LINESR & (uint32_t)flag) != 0U);
    }

    /*!
     * @brief Enables/disables an UART interrupt.
     *
     * This function configures whether the UART event will trigger an interrupt.
     *
     * @param base LINFlexD base pointer.
     * @param intSrc UART interrupt source.
     * @param enable true - enable interrupt, false - disable interrupt.
     */
    static inline void LINFlexD_SetInterruptMode(LINFlexD_Type *base, linflexd_interrupt_t intSrc, bool enable)
    {
        uint32_t regValTemp;

        regValTemp = base->LINIER;
        if (enable)
        {
            regValTemp |= (uint32_t)intSrc;
        }
        else
        {
            regValTemp &= ~(uint32_t)intSrc;
        }
        base->LINIER = regValTemp;
    }

    /*!
     * @brief Returns the state of an UART interrupt.
     *
     * This function returns whether the UART event will trigger an interrupt.
     *
     * @param base LINFlexD base pointer.
     * @param intSrc UART interrupt source.
     * @return true - interrupt enabled, false - interrupt disabled.
     */
    static inline bool LINFlexD_IsInterruptEnabled(const LINFlexD_Type *base, uint32_t intSrc)
    {
        return ((base->LINIER & intSrc) != 0U);
    }

    /*!
     * @brief Sets the first byte of the tx data buffer.
     *
     * This function writes one byte to the tx data buffer.
     *
     * @param base LINFlexD base pointer.
     * @param data data byte.
     */
    static inline void LINFlexD_SetTxDataBuffer1Byte(LINFlexD_Type *base, uint8_t data)
    {
        base->DATA.DATA8[0] = data;
    }

    /*!
     * @brief Sets the byte array of the tx data buffer.
     *
     * This function writes given bytes to the tx data buffer.
     *
     * @param base LINFlexD base pointer.
     * @param data data bytes array.
     * @param size data bytes array size.
     */
    static inline void LINFlexD_SetTxDataArray(LINFlexD_Type *base, const uint8_t *data, uint8_t size)
    {
        uint8_t i = 0;
        for (i = 0; i < size; i++)
        {
            base->DATA.DATA8[i] = data[i];
        }
    }

    /*!
     * @brief Gets the byte array of the rx data buffer.
     *
     * This function writes given bytes to the rx data buffer.
     *
     * @param base LINFlexD base pointer.
     * @param data data bytes array.
     * @param size data bytes array size.
     */
    static inline void LINFlexD_GetRxDataArray(LINFlexD_Type *base, uint8_t *data, uint8_t size)
    {
        uint8_t i = 0;
        for (i = 0; i < size; i++)
        {
            data[i] = base->DATA.DATA8[i];
        }
    }

    /*!
     * @brief Sets the first half-word of the tx data buffer.
     *
     * This function writes two bytes to the tx data buffer.
     *
     * @param base LINFlexD base pointer.
     * @param data data half-word.
     */
    static inline void LINFlexD_SetTxDataBuffer2Bytes(LINFlexD_Type *base, uint16_t data)
    {
        base->DATA.DATA16[0] = data;
    }

    /*!
     * @brief Gets the first byte of the rx data buffer.
     *
     * This function retrieves one byte from the rx data buffer.
     *
     * @param base LINFlexD base pointer.
     * @return data byte.
     */
    static inline uint8_t LINFlexD_GetRxDataBuffer1Byte(const LINFlexD_Type *base)
    {
        return base->DATA.DATA8[4];
    }

    /*!
     * @brief Gets the first half-word of the rx data buffer.
     *
     * This function retrieves two bytes from the rx data buffer.
     *
     * @param base LINFlexD base pointer.
     * @return data half-word.
     */
    static inline uint16_t LINFlexD_GetRxDataBuffer2Bytes(const LINFlexD_Type *base)
    {
        return base->DATA.DATA16[2];
    }

    /*!
     * @brief Config the ID filters.
     *
     * This function config each ID filters by config.
     *
     * @param base LINFlexD base pointer.
     * @param config ID filter items.
     */
    static inline void LINFlexD_ConfigIdFilter(LINFlexD_Type *base, uint8_t filterCount,
                                               linflexd_id_filter_config_t config[])
    {
        uint16_t index, ifer = 0, ifmr = 0;
        for (index = 0; index < filterCount; index++)
        {
            if (!config[index].filterEnable)
            {
                continue;
            }
            ifer |= config[index].filterEnable << index;
            ifmr |= config[index].maskEnable << (uint8_t)(index / 2);
            /* Be careful of DFL out of range or equal 0 */
            base->IFCR[index] = LINFlexD_IFCR_DFL(config[index].dataFieldLength - 1) |
                                LINFlexD_IFCR_DIR(config[index].direction) |
                                LINFlexD_IFCR_CCS(config[index].checksumType) |
                                LINFlexD_IFCR_ID(config[index].id);
            /* If any filter enable, disable bypass */
            base->LINCR1 &= ~LINFlexD_LINCR1_BF_MASK;
        }
        base->IFER = LINFlexD_IFER_FACT(ifer);
        base->IFMR = LINFlexD_IFMR_IFM(ifmr);
    }

    /*!
     * @brief Get IFMI.
     *
     * This function get ID filter match index.
     *
     * @param base LINFlexD base pointer.
     * @return data byte.
     */
    static inline uint8_t LINFlexD_GetFilterMatchIndex(LINFlexD_Type *base)
    {
        return (base->IFMI & LINFlexD_IFMI_IFMI_MASK);
    }

#if defined(__cplusplus)
}
#endif

#endif /* LINFlexD_HW_ACCESS_H */
