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
 * @file dma_hw_access.h
 */

#ifndef DMA_HW_ACCESS_H
#define DMA_HW_ACCESS_H

#include <stdint.h>
#include <stdbool.h>
#include "dma_driver.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#ifdef FEATURE_DMA_ENGINE_STALL
/*!
 * @brief Specifies the number of cycles the DMA Engine is stalled.
 */
typedef enum
{
    DMA_ENGINE_STALL_0_CYCLES = 0,
    DMA_ENGINE_STALL_4_CYCLES = 2,
    DMA_ENGINE_STALL_8_CYCLES = 3
} dma_engine_stall_t;
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name DMA hw access module level functions
 * @{
 */

/*!
 * @brief Initializes DMA module to known state.
 *
 * @param base Register base address for DMA module.
 */
void DMA_Init(DMA_Type *base);

/*!
 * @brief Cancels the remaining data transfer.
 *
 * This function stops the executing channel and forces the transfer loop
 * to finish. The cancellation takes effect after the last write of the
 * current read/write sequence. The CX clears itself after the cancel has
 * been honored. This cancel retires the channel normally as if the minor
 * loop had completed.
 *
 * @param base Register base address for DMA module.
 */
void DMA_CancelTransfer(DMA_Type *base);

/*!
 * @brief Cancels the remaining data transfer and treats it as an error condition.
 *
 * This function stops the executing channel and forces the transfer loop
 * to finish. The cancellation takes effect after the last write of the
 * current read/write sequence. The CX clears itself after the cancel has
 * been honoured. This cancel retires the channel normally as if the minor
 * loop had completed. Additional thing is to treat this operation as an error
 * condition.
 *
 * @param base Register base address for DMA module.
 */
void DMA_CancelTransferWithError(DMA_Type *base);

/*!
 * @brief Halts or does not halt the DMA module when an error occurs.
 *
 * An error causes the HALT bit to be set. Subsequently, all service requests are ignored until the
 * HALT bit is cleared.
 *
 * @param base Register base address for DMA module.
 * @param haltOnError Halts (true) or not halt (false) DMA module when an error occurs.
 */
static inline void DMA_SetHaltOnErrorCmd(DMA_Type *base, bool haltOnError)
{
    uint32_t regValTemp;
    regValTemp = base->CTRL;
    regValTemp &= ~(DMA_CTRL_POE_MASK);
    regValTemp |= DMA_CTRL_POE(haltOnError ? 1UL : 0UL);
    base->CTRL = regValTemp;
}

/*! @} */

/*!
 * @name DMA HAL driver configuration and operation
 * @{
 */
/*!
 * @brief Enables/Disables the transfer loop mapping.
 *
 * This function enables/disables the transfer loop mapping feature.
 * If enabled, the BCNT is redefined to include the individual enable fields and the BCNT field. The
 * individual enable fields allow the transfer loop offset to be applied to the source address, the
 * destination address, or both. The BCNT field is reduced when either offset is enabled.
 *
 * @param base Register base address for DMA module.
 * @param enable Enables (true) or Disable (false) transfer loop mapping.
 */
static inline void DMA_SetTransferLoopMappingCmd(DMA_Type *base, bool enable)
{
    uint32_t regValTemp;
    regValTemp = base->CTRL;
    regValTemp &= ~(DMA_CTRL_LOEN_MASK);
    regValTemp |= DMA_CTRL_LOEN(enable ? 1UL : 0UL);
    base->CTRL = regValTemp;
}

/*!
 * @brief Enables/Disables the error interrupt for channels.
 *
 * @param base Register base address for DMA module.
 * @param channel Channel indicator.
 * @param enable Enable(true) or Disable (false) error interrupt.
 */
void DMA_SetErrorIntCmd(DMA_Type *base, uint8_t channel, bool enable);

/*!
 * @brief Gets the DMA error interrupt status.
 *
 * @param base Register base address for DMA module.
 * @return 32 bit variable indicating error channels. If error happens on DMA channel n, the bit n
 * of this variable is '1'. If not, the bit n of this variable is '0'.
 */
static inline uint32_t DMA_GetErrorIntStatusFlag(const DMA_Type *base)
{
    return base->CHEIF;
}

/*!
 * @brief Clears the error interrupt status for the DMA channel or channels.
 *
 * @param base Register base address for DMA module.
 * @param channel Channel indicator.
 */
static inline void DMA_ClearErrorIntStatusFlag(DMA_Type *base, uint8_t channel)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->CHEIF = 0x01 << channel;
}

/*!
 * @brief Enables/Disables the DMA request for the channel or all channels.
 *
 * @param base Register base address for DMA module.
 * @param enable Enable(true) or Disable (false) DMA request.
 * @param channel Channel indicator.
 */
void DMA_SetDmaRequestCmd(DMA_Type *base, uint8_t channel, bool enable);

/*!
 * @brief Clears the done status for a channel or all channels.
 *
 * @param base Register base address for DMA module.
 * @param channel Channel indicator.
 */
static inline void DMA_ClearDoneStatusFlag(DMA_Type *base, uint8_t channel)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->DONE = 0x01 << (uint8_t) channel;
}

/*!
 * @brief Triggers the DMA channel.
 *
 * @param base Register base address for DMA module.
 * @param channel Channel indicator.
 */
static inline void DMA_TriggerChannelStart(DMA_Type *base, uint8_t channel)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->CTS[channel].CSR |= DMA_CTS_CSR_START_MASK;
}

/*!
 * @brief Clears the interrupt status for the DMA channel or all channels.
 *
 * @param base Register base address for DMA module.
 * @param channel Channel indicator.
 */
static inline void DMA_ClearIntStatusFlag(DMA_Type *base, uint8_t channel)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->CHTLDIF = 0x01 << (uint8_t) channel;
}

/*! @} */

/*!
 * @name DMA HAL driver CTS configuration functions
 * @{
 */

/*!
 * @brief Clears all registers to 0 for the hardware CTS.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 */
void DMA_CTSClearReg(DMA_Type *base, uint8_t channel);

#ifdef FEATURE_DMA_ENGINE_STALL

/*!
 * @brief Configures DMA engine to stall for a number of cycles after each R/W.
 *
 * @param base Register base address for DMA module.
 * @param channel Channel indicator.
 * @param cycles Number of cycles the DMA engine is stalled after each R/W.
 */
static inline void DMA_CTSSetEngineStall(DMA_Type *base, uint8_t channel, dma_engine_stall_t cycles)
{
#ifdef DEV_ERROR_DETECT
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->CTS[channel].CSR;
    regValTemp &= ~(DMA_CTS_CSR_BWC_MASK);
    regValTemp |= DMA_CTS_CSR_BWC(cycles);
    base->CTS[channel].CSR = regValTemp;
}

#endif

/*!
 * @brief Configures the source address for the hardware CTS.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param address The pointer to the source memory address.
 */
static inline void DMA_CTSSetSrcAddr(DMA_Type *base, uint8_t channel, uint32_t address)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->CTS[channel].SADDR = address;
}

/*!
 * @brief Configures the source address signed offset for the hardware CTS.
 *
 * Sign-extended offset applied to the current source address to form the next-state value as each
 * source read is complete.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param offset signed-offset for source address.
 */
static inline void DMA_CTSSetSrcOffset(DMA_Type *base, uint8_t channel, int16_t offset)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->CTS[channel].SOFF = (uint16_t) offset;
}

/*!
 * @brief Configures the transfer attribute for the DMA channel.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param srcModulo enumeration type for an allowed source modulo. The value defines a specific address range
 * specified as the value after the SADDR + SOFF calculation is performed on the original register
 * value. Setting this field provides the ability to implement a circular data. For data queues
 * requiring power-of-2 size bytes, the queue should start at a 0-modulo-size address and the SMOD
 * field should be set to the appropriate value for the queue, freezing the desired number of upper
 * address bits. The value programmed into this field specifies the number of the lower address bits
 * allowed to change. For a circular queue application, the SOFF is typically set to the transfer
 * size to implement post-increment addressing with SMOD function restricting the addresses to a
 * 0-modulo-size range.
 * @param destModulo Enum type for an allowed destination modulo.
 * @param srcTransferSize Enum type for source transfer size.
 * @param destTransferSize Enum type for destination transfer size.
 */
void DMA_CTSSetAttribute(
    DMA_Type *base, uint8_t channel,
    dma_modulo_t srcModulo, dma_modulo_t destModulo,
    dma_transfer_size_t srcTransferSize, dma_transfer_size_t destTransferSize);

/*!
 * @brief Sets the source transfer size.
 *
 * Configures the source data read transfer size (1/2/4/16/32 bytes).
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param size Source transfer size.
 */
static inline void DMA_CTSSetSrcTransferSize(DMA_Type *base, uint8_t channel, dma_transfer_size_t size)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->CTS[channel].TCR;
    regValTemp &= (uint16_t) (~(DMA_CTS_TCR_SSIZE_MASK));
    regValTemp |= (uint16_t) (DMA_CTS_TCR_SSIZE((uint16_t) size));
    base->CTS[channel].TCR = regValTemp;
}

/*!
 * @brief Sets the destination transfer size.
 *
 * Configures the destination data write transfer size (1/2/4/16/32 bytes).
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param size Destination transfer size.
 */
static inline void DMA_CTSSetDestTransferSize(DMA_Type *base, uint8_t channel, dma_transfer_size_t size)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->CTS[channel].TCR;
    regValTemp &= (uint16_t) (~(DMA_CTS_TCR_DSIZE_MASK));
    regValTemp |= (uint16_t) (DMA_CTS_TCR_DSIZE((uint16_t) size));
    base->CTS[channel].TCR = regValTemp;
}

/*!
 * @brief Configures the nbytes for the DMA channel.
 *
 * Note here that user need firstly configure the transfer loop mapping feature and then call this
 * function.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param nbytes Number of bytes to be transferred in each service request of the channel
 */
void DMA_CTSSetNbytes(DMA_Type *base, uint8_t channel, uint32_t nbytes);

/*!
 * @brief Enables/disables the source transfer loop offset feature for the CTS.
 *
 * Configures whether the transfer loop offset is applied to the source address
 * upon transfer loop completion.
 * NOTE: EMLM bit needs to be enabled prior to calling this function, otherwise
 * it has no effect.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param enable Enables (true) or disables (false) source transfer loop offset.
 */
static inline void DMA_CTSSetSrcMinorLoopOffsetCmd(DMA_Type *base, uint8_t channel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    if (((base->CTRL >> DMA_CTRL_LOEN_SHIFT) & 1U) != 0U)
    {
        uint32_t regValTemp;
        regValTemp = base->CTS[channel].BCNT.LOEN;
        regValTemp &= ~(DMA_CTS_BCNT_LOEN_SLOE_MASK);
        regValTemp |= DMA_CTS_BCNT_LOEN_SLOE(enable ? 1UL : 0UL);
        base->CTS[channel].BCNT.LOEN = regValTemp;
    }
}

/*!
 * @brief Enables/disables the destination transfer loop offset feature for the CTS.
 *
 * Configures whether the transfer loop offset is applied to the destination address
 * upon transfer loop completion.
 * NOTE: EMLM bit needs to be enabled prior to calling this function, otherwise
 * it has no effect.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param enable Enables (true) or disables (false) destination transfer loop offset.
 */
static inline void DMA_CTSSetDestMinorLoopOffsetCmd(DMA_Type *base, uint8_t channel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    if (((base->CTRL >> DMA_CTRL_LOEN_SHIFT) & 1U) != 0U)
    {
        uint32_t regValTemp;
        regValTemp = base->CTS[channel].BCNT.LOEN;
        regValTemp &= ~(DMA_CTS_BCNT_LOEN_DLOE_MASK);
        regValTemp |= DMA_CTS_BCNT_LOEN_DLOE(enable ? 1UL : 0UL);
        base->CTS[channel].BCNT.LOEN = regValTemp;
    }
}

/*!
 * @brief Configures the transfer loop offset for the CTS.
 *
 * Configures the offset value. If neither source nor destination offset is enabled,
 * offset is not configured.
 * NOTE: EMLM bit needs to be enabled prior to calling this function, otherwise
 * it has no effect.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param offset Minor loop offset
 */
void DMA_CTSSetTransferLoopOffset(DMA_Type *base, uint8_t channel, int32_t offset);

/*!
 * @brief Configures the last source address adjustment for the CTS.
 *
 * Adjustment value added to the source address at the completion of the major iteration count. This
 * value can be applied to restore the source address to the initial value, or adjust the address to
 * reference the next data structure.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param size adjustment value
 */
static inline void DMA_CTSSetSrcLastAdjust(DMA_Type *base, uint8_t channel, int32_t size)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->CTS[channel].STO = (uint32_t) size;
}

/*!
 * @brief Configures the destination address for the CTS.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param address The pointer to the destination address.
 */
static inline void DMA_CTSSetDestAddr(DMA_Type *base, uint8_t channel, uint32_t address)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->CTS[channel].DADDR = address;
}

/*!
 * @brief Configures the destination address signed offset for the CTS.
 *
 * Sign-extended offset applied to the current source address to form the next-state value as each
 * destination write is complete.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param offset signed-offset
 */
static inline void DMA_CTSSetDestOffset(DMA_Type *base, uint8_t channel, int16_t offset)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->CTS[channel].DOFF = (uint16_t) offset;
}

/*!
 * @brief Configures the last source address adjustment.
 *
 * This function adds an adjustment value added to the source address at the completion of the major
 * iteration count. This value can be applied to restore the source address to the initial value, or
 * adjust the address to reference the next data structure.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param adjust adjustment value
 */
static inline void DMA_CTSSetDestLastAdjust(DMA_Type *base, uint8_t channel, int32_t adjust)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    base->CTS[channel].DTO_RLD.DTO = (uint32_t) adjust;
}

/*!
 * @brief Configures the memory address for the next transfer CTS for the CTS.
 *
 *
 * This function enables the ram reload feature for the CTS and configures the next
 * CTS's address. This address points to the beginning of a 0-modulo-32 byte region containing
 * the next transfer CTS to be loaded into this channel. The channel reload is performed as the
 * major iteration count completes. The ram reload address must be 0-modulo-32-byte. Otherwise,
 * a configuration error is reported.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param nextCTSAddr The address of the next CTS to be linked to this CTS.
 */
void DMA_CTSSetRamReloadLink(DMA_Type *base, uint8_t channel, uint32_t nextCTSAddr);

/*!
 * @brief Enables/Disables the ram reload feature for the CTS.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param enable Enables (true) /Disables (false) ram reload feature.
 */
static inline void DMA_CTSSetRamReloadCmd(DMA_Type *base, uint8_t channel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->CTS[channel].CSR;
    regValTemp &= (uint16_t) ~(DMA_CTS_CSR_RLDEN_MASK);
    regValTemp |= (uint16_t) DMA_CTS_CSR_RLDEN(enable ? 1UL : 0UL);
    base->CTS[channel].CSR = regValTemp;
}

/*!
 * @brief Configures the major channel link the CTS.
 *
 * If the major link is enabled, after the trigger loop counter is exhausted, the DMA engine initiates a
 * channel service request at the channel defined by these six bits by setting that channel start
 * bits.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param majorLinkChannel channel number for major link
 * @param enable Enables (true) or Disables (false) channel major link.
 */
static inline void DMA_CTSSetChannelTriggerLink(DMA_Type *base, uint8_t channel, uint32_t majorLinkChannel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->CTS[channel].CSR;
    regValTemp &= (uint16_t) ~(DMA_CTS_CSR_TLKCH_MASK);
    regValTemp |= (uint16_t) DMA_CTS_CSR_TLKCH(majorLinkChannel);
    base->CTS[channel].CSR = regValTemp;
    regValTemp = base->CTS[channel].CSR;
    regValTemp &= (uint16_t) ~(DMA_CTS_CSR_TLKEN_MASK);
    regValTemp |= (uint16_t) DMA_CTS_CSR_TLKEN(enable ? 1UL : 0UL);
    base->CTS[channel].CSR = regValTemp;
}

/*!
 * @brief Disables/Enables the DMA request after the trigger loop completes for the CTS.
 *
 * If disabled, the DMA hardware automatically clears the corresponding DMA request when the
 * current major iteration count reaches zero.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param disable Disable (true)/Enable (false) DMA request after CTS complete.
 */
static inline void DMA_CTSSetDisableDmaRequestAfterCTSDoneCmd(DMA_Type *base, uint8_t channel, bool disable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->CTS[channel].CSR;
    regValTemp &= (uint16_t) ~(DMA_CTS_CSR_DREQ_MASK);
    regValTemp |= (uint16_t) DMA_CTS_CSR_DREQ(disable ? 1UL : 0UL);
    base->CTS[channel].CSR = regValTemp;
}

/*!
 * @brief Enables/Disables the half complete interrupt for the CTS.
 *
 * If set, the channel generates an interrupt request by setting the appropriate bit in the
 * interrupt register when the current major iteration count reaches the halfway point. Specifically,
 * the comparison performed by the DMA engine is (TCNT == (TCNTRV >> 1)). This half-way point
 * interrupt request is provided to support the double-buffered schemes or other types of data movement
 * where the processor needs an early indication of the transfer's process.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param enable Enable (true) /Disable (false) half complete interrupt.
 */
static inline void DMA_CTSSetMajorHalfCompleteIntCmd(DMA_Type *base, uint8_t channel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->CTS[channel].CSR;
    regValTemp &= (uint16_t) ~(DMA_CTS_CSR_THDINT_MASK);
    regValTemp |= (uint16_t) DMA_CTS_CSR_THDINT(enable ? 1UL : 0UL);
    base->CTS[channel].CSR = regValTemp;
}

/*!
 * @brief Enables/Disables the interrupt after the trigger loop completes for the CTS.
 *
 * If enabled, the channel generates an interrupt request by setting the appropriate bit in the
 * interrupt register when the current major iteration count reaches zero.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param enable Enable (true) /Disable (false) interrupt after CTS done.
 */
static inline void DMA_CTSSetMajorCompleteIntCmd(DMA_Type *base, uint8_t channel, bool enable)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMA_CHANNELS);
#endif
    uint16_t regValTemp;
    regValTemp = base->CTS[channel].CSR;
    regValTemp &= (uint16_t) ~(DMA_CTS_CSR_TDINT_MASK);
    regValTemp |= (uint16_t) DMA_CTS_CSR_TDINT(enable ? 1UL : 0UL);
    base->CTS[channel].CSR = regValTemp;
}

/*!
 * @brief Sets the channel minor link for the CTS.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param linkChannel Channel to be linked on transfer loop complete.
 * @param enable Enable (true)/Disable (false) channel minor link.
 */
void DMA_CTSSetChannelLoopLink(DMA_Type *base, uint8_t channel, uint32_t linkChannel, bool enable);

/*!
 * @brief Sets the major iteration count according to transfer loop channel link setting.
 *
 * Note here that user need to first set the transfer loop channel link and then call this function.
 * The execute flow inside this function is dependent on the transfer loop channel link setting.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @param count trigger loop count
 */
void DMA_CTSSetTriggerCount(DMA_Type *base, uint8_t channel, uint32_t count);

/*!
 * @brief Returns the current major iteration count.
 *
 * Gets the current major iteration count according to transfer loop channel link settings.
 *
 * @param base Register base address for DMA module.
 * @param channel DMA channel number.
 * @return current iteration count
 */
uint32_t DMA_CTSGetCurrentTriggerCount(const DMA_Type *base, uint8_t channel);

#ifdef FEATURE_DMAMUX_AVAILABLE

/*!
 * @brief Initializes the DMAMUX module to the reset state.
 *
 * Initializes the DMAMUX module to the reset state.
 *
 * @param base Register base address for DMAMUX module.
 */
void DMAMUX_Init(DMA_Type *base);

#endif


#ifdef FEATURE_DMAMUX_AVAILABLE

/*!
 * @brief Configures the DMA request for the DMAMUX channel.
 *
 * Selects which DMA source is routed to a DMA channel. The DMA sources are defined in the file
 * <MCU>_Features.h
 *
 * @param base Register base address for DMAMUX module.
 * @param channel DMAMUX channel number.
 * @param source DMA request source.
 */
static inline void DMAMUX_SetChannelSource(DMA_Type *base, uint8_t channel, uint8_t source)
{
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    DEV_ASSERT(channel < FEATURE_DMAMUX_CHANNELS);
#endif
    base->CHMUX[channel] = source;
}

#endif

/*!
 * @brief Returns DMA Register Base Address.
 *
 * Gets the address of the selected DMA module.
 *
 * @param instance DMA instance to be returned.
 * @return DMA register base address
 */
DMA_Type *DMA_DRV_GetDmaRegBaseAddr(uint32_t instance);

#if defined(__cplusplus)
}
#endif

#endif /* DMA_HW_ACCESS_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/


