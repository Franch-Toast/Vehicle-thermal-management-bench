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
* @file dma_driver.h
*/

#if !defined(DMA_DRIVER_H)
#define DMA_DRIVER_H

#include "device_registers.h"
#include "status.h"
#include <stddef.h>

/*!
 * @addtogroup dma_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Macro for the memory size needed for the software CTS.
 *
 * Software CTS is aligned to 32 bytes. We don't need a software CTS structure for the first
 * descriptor, since the configuration is pushed directly to registers.
 * To make sure the software CTS can meet the DMA module requirement regarding alignment,
 * allocate memory for the remaining descriptors with extra 31 bytes.
 */
#define SCTS_SIZE(number)           (((number) * 32U) - 1U)
#define SCTS_ADDR(address)          (((uint32_t)address + 31UL) & ~0x1FUL)

/*!
 * @brief Macro for accessing the least significant bit of the ERR register.
 *
 * The erroneous channels are retrieved from ERR register by subsequently right
 * shifting all the ERR bits + "AND"-ing the result with this mask.
 */
#define DMA_ERR_LSB_MASK           1U

/*! @brief DMA channel interrupts.
 * Implements : dma_channel_interrupt_t_Class
 */
typedef enum
{
    DMA_CHN_ERR_INT = 0U,         /*!< Error interrupt */
    DMA_CHN_HALF_MAJOR_LOOP_INT,  /*!< Half trigger loop interrupt. */
    DMA_CHN_MAJOR_LOOP_INT        /*!< Complete trigger loop interrupt. */
} dma_channel_interrupt_t;


/*! @brief DMA modulo configuration
 * DMA source/destination address modulo value when address changes.
 * Implements : dma_modulo_t_Class
 */
typedef enum
{
    DMA_MODULO_OFF = 0U,
    DMA_MODULO_2B,
    DMA_MODULO_4B,
    DMA_MODULO_8B,
    DMA_MODULO_16B,
    DMA_MODULO_32B,
    DMA_MODULO_64B,
    DMA_MODULO_128B,
    DMA_MODULO_256B,
    DMA_MODULO_512B,
    DMA_MODULO_1KB,
    DMA_MODULO_2KB,
    DMA_MODULO_4KB,
    DMA_MODULO_8KB,
    DMA_MODULO_16KB,
    DMA_MODULO_32KB,
    DMA_MODULO_64KB,
    DMA_MODULO_128KB,
    DMA_MODULO_256KB,
    DMA_MODULO_512KB,
    DMA_MODULO_1MB,
    DMA_MODULO_2MB,
    DMA_MODULO_4MB,
    DMA_MODULO_8MB,
    DMA_MODULO_16MB,
    DMA_MODULO_32MB,
    DMA_MODULO_64MB,
    DMA_MODULO_128MB,
    DMA_MODULO_256MB,
    DMA_MODULO_512MB,
    DMA_MODULO_1GB,
    DMA_MODULO_2GB
} dma_modulo_t;

/*! @brief DMA transfer configuration
 * Note: in L/Z series DMA_TRANSFER_SIZE_16B and DMA_TRANSFER_SIZE_32B are not supported.
 * Implements : dma_transfer_size_t_Class
 */
typedef enum
{
    DMA_TRANSFER_SIZE_1B = 0x0U,
    DMA_TRANSFER_SIZE_2B = 0x1U,
    DMA_TRANSFER_SIZE_4B = 0x2U,
    DMA_TRANSFER_SIZE_8B = 0x3U,
    DMA_TRANSFER_SIZE_16B = 0x4U,
    DMA_TRANSFER_SIZE_32B = 0x5U,
    DMA_TRANSFER_SIZE_64B = 0x6U,
} dma_transfer_size_t;

/*!
 * @brief The user configuration structure for the DMA driver.
 *
 * Use an instance of this structure with the DMA_DRV_Init() function. This allows the user to configure
 * settings of the DMA peripheral with a single function call.
 * Implements : dma_user_config_t_Class
 */
typedef struct
{
    bool haltOnError;           /*!< Any error causes the HALT bit to set. Subsequently, all
                                 service requests are ignored until the HALT bit is cleared. */
} dma_user_config_t;

/*!
 * @brief Channel status for DMA channel.
 *
 * A structure describing the DMA channel status. The user can get the status by callback parameter
 * or by calling DMA_DRV_getStatus() function.
 * Implements : dma_chn_status_t_Class
 */
typedef enum
{
    DMA_CHN_NORMAL = 0U,           /*!< DMA channel normal state. */
    DMA_CHN_ERROR                  /*!< An error occurred in the DMA channel. */
} dma_chn_status_t;

/*!
 * @brief Definition for the DMA channel callback function.
 *
 * Prototype for the callback function registered in the DMA driver.
 * Implements : dma_callback_t_Class
 */
typedef void (*dma_callback_t)(void *parameter, dma_chn_status_t status);

/*! @brief Data structure for the DMA channel state.
 * Implements : dma_chn_state_t_Class
 */
typedef struct
{
    uint8_t virtChn;                     /*!< Virtual channel number. */
    dma_callback_t callback;            /*!< Callback function pointer for the DMA channel. It will
                                              be called at the DMA channel complete and DMA channel
                                              error. */
    void *parameter;                     /*!< Parameter for the callback function pointer. */
    volatile dma_chn_status_t status;   /*!< DMA channel status. */
} dma_chn_state_t;

/*!
 * @brief The user configuration structure for the an DMA driver channel.
 *
 * Use an instance of this structure with the DMA_DRV_ChannelInit() function. This allows the user to configure
 * settings of the DMA channel with a single function call.
 * Implements : dma_channel_config_t_Class
 */
typedef struct
{
    uint8_t virtChnConfig;                   /*!< DMA virtual channel number */
    dma_request_source_t source;             /*!< Selects the source of the DMA request for this channel */
    dma_callback_t callback;                /*!< Callback that will be registered for this channel */
    void *callbackParam;                    /*!< Parameter passed to the channel callback */
} dma_channel_config_t;

/*! @brief A type for the DMA transfer.
 * Implements : dma_transfer_type_t_Class
 */
typedef enum
{
    DMA_TRANSFER_PERIPH2MEM = 0U,   /*!< Transfer from peripheral to memory */
    DMA_TRANSFER_MEM2PERIPH,        /*!< Transfer from memory to peripheral */
    DMA_TRANSFER_MEM2MEM,           /*!< Transfer from memory to memory */
    DMA_TRANSFER_PERIPH2PERIPH      /*!< Transfer from peripheral to peripheral */
} dma_transfer_type_t;

/*! @brief Data structure for configuring a discrete memory transfer.
 * Implements : dma_ram_reload_list_t_Class
 */
typedef struct
{
    uint32_t address;           /*!< Address of buffer. */
    uint32_t length;            /*!< Length of buffer. */
    dma_transfer_type_t type;  /*!< Type of the DMA transfer */
} dma_ram_reload_list_t;

/*!
 * @brief Runtime state structure for the DMA driver.
 *
 * This structure holds data that is used by the DMA peripheral driver to manage
 * multi DMA channels.
 * The user passes the memory for this run-time state structure and the DMA
 * driver populates the members.
 * Implements : dma_state_t_Class
 */
typedef struct
{
    dma_chn_state_t *volatile virtChnState[(uint32_t) FEATURE_DMA_VIRTUAL_CHANNELS];   /*!< Pointer array storing channel state. */
} dma_state_t;

/*!
 * @brief DMA loop transfer configuration.
 *
 * This structure configures the basic transfer/trigger loop attributes.
 * Implements : dma_loop_transfer_config_t_Class
 */
typedef struct
{
    uint32_t triggerLoopIterationCount;   /*!< Number of trigger loop iterations. */
    bool srcOffsetEnable;                 /*!< Selects whether the transfer loop offset is applied to the
                                                 source address upon transfer loop completion. */
    bool dstOffsetEnable;                 /*!< Selects whether the transfer loop offset is applied to the
                                                 destination address upon transfer loop completion. */
    int32_t triggerLoopOffset;            /*!< Sign-extended offset applied to the source or destination address
                                                 to form the next-state value after the transfer loop completes. */
    bool transferLoopChnLinkEnable;       /*!< Enables channel-to-channel linking on transfer loop complete. */
    uint8_t transferLoopChnLinkNumber;    /*!< The number of the next channel to be started by DMA
                                                 engine when transfer loop completes. */
    bool triggerLoopChnLinkEnable;        /*!< Enables channel-to-channel linking on trigger loop complete. */
    uint8_t triggerLoopChnLinkNumber;     /*!< The number of the next channel to be started by DMA
                                                 engine when trigger loop completes. */
} dma_loop_transfer_config_t;

/*!
 * @brief DMA transfer size configuration.
 *
 * This structure configures the basic source/destination transfer attribute.
 * Implements : dma_transfer_config_t_Class
 */
typedef struct
{
    uint32_t srcAddr;                                   /*!< Memory address pointing to the source data. */
    uint32_t destAddr;                                  /*!< Memory address pointing to the destination data. */
    dma_transfer_size_t srcTransferSize;                /*!< Source data transfer size. */
    dma_transfer_size_t destTransferSize;               /*!< Destination data transfer size. */
    int16_t srcOffset;                                  /*!< Sign-extended offset applied to the current source address
                                                           to form the next-state value as each source read/write
                                                           is completed. */
    int16_t destOffset;                                 /*!< Sign-extended offset applied to the current destination
                                                           address to form the next-state value as each source
                                                           read/write is completed. */
    int32_t srcLastAddrAdjust;                          /*!< Last source address adjustment. */
    int32_t destLastAddrAdjust;                         /*!< Last destination address adjustment. Note here it is only
                                                           valid when ram reload feature is not enabled. */
    dma_modulo_t srcModulo;                             /*!< Source address modulo. */
    dma_modulo_t destModulo;                            /*!< Destination address modulo. */
    uint32_t transferLoopByteCount;                    /*!< Number of bytes to be transferred in each service request
                                                           of the channel. */
    bool ramReloadEnable;                               /*!< Enable ram reload feature. */
    uint32_t ramReloadNextDescAddr;                     /*!< The address of the next descriptor to be used, when
                                                           ram reload feature is enabled.
                                                           Note: this value is not used when ram reload
                                                           feature is disabled. */
    bool interruptEnable;                               /*!< Enable the interrupt request when the trigger loop
                                                           count completes */
    dma_loop_transfer_config_t *loopTransferConfig;     /*!< Pointer to loop transfer configuration structure
                                                           (defines transfer/trigger loop attributes)
                                                           Note: this field is only used when transfer loop mapping is
                                                           enabled from DMA configuration. */
} dma_transfer_config_t;

/*! @brief DMA CTS
 * DMA CTS structure, reflects DMA CTS configuration registers.
 * Implements : dma_software_cts_t_Class
 */
typedef struct
{
    uint32_t SADDR;             /*!< Source address */
    int16_t SOFF;               /*!< Source offset */
    uint16_t ATTR;              /*!< Transfer attributes */
    uint32_t BCNT;              /*!< One loop transfer byte count */
    int32_t STO;                /*!< Source trigger loop offset */
    uint32_t DADDR;             /*!< Destination address */
    int16_t DOFF;               /*!< Destination offset */
    uint16_t TCNT;              /*!< Trigger loop transfer count */
    int32_t RAM_LOAD_ADDR;      /*!< RAM load address */
    uint16_t CSR;               /*!< Control/status register */
    uint16_t TCNTRV;            /*!< Trigger loop counter value */
} dma_software_cts_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
  * @name DMA Peripheral Driver
  * @{
  */

/*!
  * @name DMA peripheral driver module level functions
  * @{
  */

/*!
 * @brief Initializes the DMA module.
 *
 * This function initializes the run-time state structure to provide the DMA channel allocation
 * release, protect, and track the state for channels. This function also resets the DMA modules,
 * initializes the module to user-defined settings and default settings.
 * @param dmaState The pointer to the DMA peripheral driver state structure. The user passes
 * the memory for this run-time state structure and the DMA peripheral driver populates the
 * members. This run-time state structure keeps track of the DMA channels status. The memory must
 * be kept valid before calling the DMA_DRV_DeInit.
 * @param userConfig User configuration structure for DMA peripheral drivers. The user populates the
 * members of this structure and passes the pointer of this structure into the function.
 * @param chnStateArray Array of pointers to run-time state structures for DMA channels;
 * will populate the state structures inside the DMA driver state structure.
 * @param chnConfigArray Array of pointers to channel initialization structures.
 * @param chnCount The number of DMA channels to be initialized.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t DMA_DRV_Init(dma_state_t *dmaState,
                      const dma_user_config_t *userConfig,
                      dma_chn_state_t *const chnStateArray[],
                      const dma_channel_config_t *const chnConfigArray[],
                      uint32_t chnCount);

/*!
 * @brief De-initializes the DMA module.
 *
 * This function resets the DMA module to reset state and disables the interrupt to the core.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t DMA_DRV_Deinit(void);

/*! @} */

/*!
  * @name DMA peripheral driver channel management functions
  * @{
  */

/*!
 * @brief Initializes an DMA channel.
 *
 * This function initializes the run-time state structure for a DMA channel, based on user
 * configuration. It will request the channel, set up the channel priority and install the
 * callback.
 *
 * @param dmaChannelState Pointer to the DMA channel state structure. The user passes
 * the memory for this run-time state structure and the DMA peripheral driver populates the
 * members. This run-time state structure keeps track of the DMA channel status. The memory must
 * be kept valid before calling the DMA_DRV_ReleaseChannel.
 * @param dmaChannelConfig User configuration structure for DMA channel. The user populates the
 * members of this structure and passes the pointer of this structure into the function.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t DMA_DRV_ChannelInit(dma_chn_state_t *dmaChannelState,
                             const dma_channel_config_t *dmaChannelConfig);

/*!
 * @brief Releases an DMA channel.
 *
 * This function stops the DMA channel and disables the interrupt of this channel. The channel state
 * structure can be released after this function is called.
 *
 * @param virtualChannel DMA virtual channel number.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t DMA_DRV_ReleaseChannel(uint8_t virtualChannel);

/*! @} */

/*!
  * @name DMA peripheral driver transfer setup functions
  * @{
  */

/*!
 * @brief Copies the channel configuration to the CTS registers.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param cts Pointer to the channel configuration structure.
 */
void DMA_DRV_PushConfigToReg(uint8_t virtualChannel,
                             const dma_transfer_config_t *cts);

/*!
 * @brief Copies the channel configuration to the software CTS structure.
 *
 * This function copies the properties from the channel configuration to the software CTS structure; the address
 * of the software CTS can be used to enable ram reload operation (pointer to the next CTS).

 * @param config Pointer to the channel configuration structure.
 * @param scts Pointer to the software CTS structure.
 */
void DMA_DRV_PushConfigToSCTS(const dma_transfer_config_t *config,
                              dma_software_cts_t *scts);

/*!
 * @brief Configures a simple single block data transfer with DMA.
 *
 * This function configures the descriptor for a single block transfer.
 * The function considers contiguous memory blocks, thus it configures the CTS
 * source/destination offset fields to cover the data buffer without gaps,
 * according to "transferSize" parameter (the offset is equal to the number of
 * bytes transferred in a source read/destination write).
 *
 * NOTE: For memory-to-peripheral or peripheral-to-memory transfers, make sure
 * the transfer size is equal to the data buffer size of the peripheral used,
 * otherwise only truncated chunks of data may be transferred (e.g. for a
 * communication IP with an 8-bit data register the transfer size should be 1B,
 * whereas for a 32-bit data register, the transfer size should be 4B). The
 * rationale of this constraint is that, on the peripheral side, the address
 * offset is set to zero, allowing to read/write data from/to the peripheral
 * in a single source read/destination write operation.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param type Transfer type (M->M, P->M, M->P, P->P).
 * @param srcAddr A source register address or a source memory address.
 * @param destAddr A destination register address or a destination memory address.
 * @param transferSize The number of bytes to be transferred on every DMA write/read.
 *        Source/Dest share the same write/read size.
 * @param dataBufferSize The total number of bytes to be transferred.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS
 */
status_t DMA_DRV_ConfigSingleBlockTransfer(uint8_t virtualChannel,
                                           dma_transfer_type_t type,
                                           uint32_t srcAddr,
                                           uint32_t destAddr,
                                           dma_transfer_size_t transferSize,
                                           uint32_t dataBufferSize);

/*!
 * @brief Configures a multiple block data transfer with DMA.
 *
 * This function configures the descriptor for a multi-block transfer.
 * The function considers contiguous memory blocks, thus it configures the CTS
 * source/destination offset fields to cover the data buffer without gaps,
 * according to "transferSize" parameter (the offset is equal to the number of
 * bytes transferred in a source read/destination write). The buffer is divided
 * in multiple block, each block being transferred upon a single DMA request.
 *
 * NOTE: For transfers to/from peripherals, make sure
 * the transfer size is equal to the data buffer size of the peripheral used,
 * otherwise only truncated chunks of data may be transferred (e.g. for a
 * communication IP with an 8-bit data register the transfer size should be 1B,
 * whereas for a 32-bit data register, the transfer size should be 4B). The
 * rationale of this constraint is that, on the peripheral side, the address
 * offset is set to zero, allowing to read/write data from/to the peripheral
 * in a single source read/destination write operation.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param type Transfer type (M->M, P->M, M->P, P->P).
 * @param srcAddr A source register address or a source memory address.
 * @param destAddr A destination register address or a destination memory address.
 * @param transferSize The number of bytes to be transferred on every DMA write/read.
 *        Source/Dest share the same write/read size, one bus transfer byte count.
 * @param blockSize The total number of bytes inside a block, one trigger loop byte count.
 * @param blockCount The total number of data blocks (one block is transferred upon a DMA request).
 * @param disableReqOnCompletion This parameter specifies whether the DMA channel should
 *        be disabled when the transfer is complete (further requests will remain untreated).
 *
 * @return STATUS_ERROR or STATUS_SUCCESS
 */
status_t DMA_DRV_ConfigMultiBlockTransfer(uint8_t virtualChannel,
                                          dma_transfer_type_t type,
                                          uint32_t srcAddr,
                                          uint32_t destAddr,
                                          dma_transfer_size_t transferSize,
                                          uint32_t blockSize,
                                          uint32_t blockCount,
                                          bool disableReqOnCompletion);

/*!
 * @brief Configures the DMA transfer in loop mode.
 *
 * This function configures the DMA transfer in a loop chain. The user passes a block of memory into this
 * function that configures the loop transfer properties (transfer/trigger loop count, address offsets, channel linking).
 * The DMA driver copies the configuration to CTS registers, only when the loop properties are set up correctly
 * and transfer loop mapping is enabled for the DMA module.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param transferConfig Pointer to the transfer configuration structure; this structure defines fields for setting
 * up the basic transfer and also a pointer to a memory structure that defines the loop chain properties (minor/major).
 *
 * @return STATUS_ERROR or STATUS_SUCCESS
 */
status_t DMA_DRV_ConfigLoopTransfer(uint8_t virtualChannel,
                                    const dma_transfer_config_t *transferConfig);

/*!
 * @brief Configures the DMA transfer in a ram reload mode.
 *
 * This function configures the descriptors into a single-ended chain. The user passes blocks of memory into
 * this function. The interrupt is triggered only when the last memory block is completed. The memory block
 * information is passed with the dma_ram_reload_list_t data structure, which can tell
 * the memory address and length.
 * The DMA driver configures the descriptor for each memory block, transfers the descriptor from the
 * first one to the last one, and stops.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param scts Array of empty software CTS structures. The user must prepare this memory block. We don't need a
 * software CTS structure for the first descriptor, since the configuration is pushed directly to registers.The "scts"
 * buffer must align with 32 bytes; if not, an error occurs in the DMA driver. Thus, the required
 * memory size for "scts" is equal to ctsCount * size_of(dma_software_cts_t) - 1; the driver will take
 * care of the memory alignment if the provided memory buffer is big enough. For proper allocation of the
 * "scts" buffer it is recommended to use SCTS_SIZE macro.
 * @param transferSize The number of bytes to be transferred on every DMA write/read.
 * @param bytesOnEachRequest Bytes to be transferred in each DMA request.
 * @param srcList Data structure storing the address, length and type of transfer (M->M, M->P, P->M, P->P) for
 * the bytes to be transferred for source memory blocks. If the source memory is peripheral, the length
 * is not used.
 * @param destList Data structure storing the address, length and type of transfer (M->M, M->P, P->M, P->P) for
 * the bytes to be transferred for destination memory blocks. In the memory-to-memory transfer mode, the
 * user must ensure that the length of the destination ram reload list is equal to the source
 * ram reload list. If the destination memory is a peripheral register, the length is not used.
 * @param ctsCount The number of CTS memory blocks contained in the ram reload list.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS
 */
status_t DMA_DRV_ConfigRamReloadTransfer(uint8_t virtualChannel,
                                         dma_software_cts_t *scts,
                                         dma_transfer_size_t transferSize,
                                         uint32_t bytesOnEachRequest,
                                         const dma_ram_reload_list_t *srcList,
                                         const dma_ram_reload_list_t *destList,
                                         uint8_t ctsCount);

/*!
 * @brief Cancel the running transfer.
 *
 * This function cancels the current transfer, optionally signalling an error.
 *
 * @param bool error If true, an error will be logged for the current transfer.
 */
void DMA_DRV_CancelTransfer(bool error);

/*! @} */

/*!
  * @name DMA Peripheral driver channel operation functions
  * @{
  */
/*!
 * @brief Starts an DMA channel.
 *
 * This function enables the DMA channel DMA request.
 *
 * @param virtualChannel DMA virtual channel number.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t DMA_DRV_StartChannel(uint8_t virtualChannel);

/*!
 * @brief Stops the DMA channel.
 *
 * This function disables the DMA channel DMA request.
 *
 * @param virtualChannel DMA virtual channel number.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t DMA_DRV_StopChannel(uint8_t virtualChannel);

/*!
 * @brief Configures the DMA request for the DMA channel.
 *
 * Selects which DMA source is routed to a DMA channel. The DMA sources are defined in the file
 * <MCU>_Features.h
 *
 * @param virtualChannel DMA virtual channel number.
 * @param request DMA request source.
 *
 * @return STATUS_SUCCESS or STATUS_UNSUPPORTED.
 */
status_t DMA_DRV_SetChannelRequestAndTrigger(uint8_t virtualChannel,
                                             uint8_t request);

/*!
 * @brief Clears all registers to 0 for the channel's CTS.
 *
 * @param virtualChannel DMA virtual channel number.
 */
void DMA_DRV_ClearCTS(uint8_t virtualChannel);

/*!
 * @brief Configures the source address for the DMA channel.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param address The pointer to the source memory address.
 */
void DMA_DRV_SetSrcAddr(uint8_t virtualChannel, uint32_t address);

/*!
 * @brief Configures the source address signed offset for the DMA channel.
 *
 * Sign-extended offset applied to the current source address to form the next-state value as each
 * source read is complete.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param offset Signed-offset for source address.
 */
void DMA_DRV_SetSrcOffset(uint8_t virtualChannel, int16_t offset);

/*!
 * @brief Configures the source data chunk size (transferred in a read sequence).
 *
 * Source data read transfer size (1/2/4/16/32 bytes).
 *
 * @param virtualChannel DMA virtual channel number.
 * @param size Source transfer size.
 */
void DMA_DRV_SetSrcReadChunkSize(uint8_t virtualChannel,
                                 dma_transfer_size_t size);

/*!
 * @brief Configures the source address last adjustment.
 *
 * Adjustment value added to the source address at the completion of the major iteration count. This
 * value can be applied to restore the source address to the initial value, or adjust the address to
 * reference the next data structure.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param adjust Adjustment value.
 */
void DMA_DRV_SetSrcLastAddrAdjustment(uint8_t virtualChannel,
                                      int32_t adjust);

/*!
 * @brief Configures the destination address for the DMA channel.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param address The pointer to the destination memory address.
 */
void DMA_DRV_SetDestAddr(uint8_t virtualChannel, uint32_t address);

/*!
 * @brief Configures the destination address signed offset for the DMA channel.
 *
 * Sign-extended offset applied to the current destination address to form the next-state value as each
 * destination write is complete.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param offset signed-offset
 */
void DMA_DRV_SetDestOffset(uint8_t virtualChannel, int16_t offset);

/*!
 * @brief Configures the destination data chunk size (transferred in a write sequence).
 *
 * Destination data write transfer size (1/2/4/16/32 bytes).
 *
 * @param virtualChannel DMA virtual channel number.
 * @param size Destination transfer size.
 */
void DMA_DRV_SetDestWriteChunkSize(uint8_t virtualChannel,
                                   dma_transfer_size_t size);

/*!
 * @brief Configures the destination address last adjustment.
 *
 * Adjustment value added to the destination address at the completion of the major iteration count. This
 * value can be applied to restore the destination address to the initial value, or adjust the address to
 * reference the next data structure.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param adjust Adjustment value.
 */
void DMA_DRV_SetDestLastAddrAdjustment(uint8_t virtualChannel,
                                       int32_t adjust);

/*!
 * @brief Configures the number of bytes to be transferred in each service request of the channel.
 *
 * Sets the number of bytes to be transferred each time a request is received (one trigger loop iteration).
 * This number needs to be a multiple of the source/destination transfer size, as the data block will be
 * transferred within multiple read/write sequences (transfer loops).
 *
 * @param virtualChannel DMA virtual channel number.
 * @param nbytes Number of bytes to be transferred in each service request of the channel
 */
void DMA_DRV_SetTransferLoopBlockSize(uint8_t virtualChannel,
                                      uint32_t nbytes);

/*!
 * @brief Configures the number of trigger loop iterations.
 *
 * Sets the number of trigger loop iterations; each trigger loop iteration will be served upon a request
 * for the current channel, transferring the data block configured for the transfer loop (BCNT).
 *
 * @param virtualChannel DMA virtual channel number.
 * @param majorLoopCount Number of trigger loop iterations.
 */
void DMA_DRV_SetTriggerLoopIterationCount(uint8_t virtualChannel,
                                          uint32_t majorLoopCount);

/*!
 * @brief Returns the remaining trigger loop iteration count.
 *
 * Gets the number transfer loops yet to be triggered (trigger loop iterations).
 *
 * @param virtualChannel DMA virtual channel number.
 * @return number of trigger loop iterations yet to be triggered
 */
uint32_t DMA_DRV_GetRemainingTriggerIterationsCount(uint8_t virtualChannel);

/*!
 * @brief Configures the memory address of the next CTS, in ram reload mode.
 *
 * This function configures the address of the next CTS to be loaded form memory, when ram reload
 * feature is enabled. This address points to the beginning of a 0-modulo-32 byte region containing
 * the next transfer CTS to be loaded into this channel. The channel reload is performed as the
 * major iteration count completes. The ram reload address must be 0-modulo-32-byte. Otherwise,
 * a configuration error is reported.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param nextCTSAddr The address of the next CTS to be linked to this CTS.
 */
void DMA_DRV_SetRamReloadLink(uint8_t virtualChannel,
                              uint32_t nextCTSAddr);

/*!
 * @brief Disables/Enables the DMA request after the trigger loop completes for the CTS.
 *
 * If disabled, the DMA hardware automatically clears the corresponding DMA request when the
 * current trigger loop count reaches zero.
 * If enabled, the DMA hardware does not automatically clear the DMA request when the current
 * trigger loop count reaches zero, if new trigger loop arrives, DMA will start new transfer.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param disable Disable (true)/Enable (false) DMA request after CTS complete.
 */
void DMA_DRV_DisableRequestsOnTransferComplete(uint8_t virtualChannel,
                                               bool disable);

/*!
 * @brief Disables/Enables the channel interrupt requests.
 *
 * This function enables/disables error, half trigger loop and complete trigger loop interrupts
 * for the current channel.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param interrupt Interrupt event (error/half trigger loop/complete trigger loop).
 * @param enable Enable (true)/Disable (false) interrupts for the current channel.
 */
void DMA_DRV_ConfigureInterrupt(uint8_t virtualChannel,
                                dma_channel_interrupt_t intSrc,
                                bool enable);

/*!
 * @brief Triggers a software request for the current channel.
 *
 * This function starts a transfer using the current channel (software request).
 *
 * @param virtualChannel DMA virtual channel number.
 */
void DMA_DRV_TriggerSwRequest(uint8_t virtualChannel);

/*! @} */

/*!
  * @name DMA Peripheral callback and interrupt functions
  * @{
  */

/*!
 * @brief Registers the callback function and the parameter for DMA channel.
 *
 * This function registers the callback function and the parameter into the DMA channel state structure.
 * The callback function is called when the channel is complete or a channel error occurs. The DMA
 * driver passes the channel status to this callback function to indicate whether it is caused by the
 * channel complete event or the channel error event.
 *
 * To un-register the callback function, set the callback function to "NULL" and call this
 * function.
 *
 * @param virtualChannel DMA virtual channel number.
 * @param callback The pointer to the callback function.
 * @param parameter The pointer to the callback function's parameter.
 *
 * @return STATUS_ERROR or STATUS_SUCCESS.
 */
status_t DMA_DRV_InstallCallback(uint8_t virtualChannel,
                                 dma_callback_t callback,
                                 void *parameter);

/*! @} */

/*!
  * @name DMA Peripheral driver miscellaneous functions
  * @{
  */
/*!
 * @brief Gets the DMA channel status.
 *
 * @param virtualChannel DMA virtual channel number.
 *
 * @return Channel status.
 */
dma_chn_status_t DMA_DRV_GetChannelStatus(uint8_t virtualChannel);

/*! @} */

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* DMA_DRIVER_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/

