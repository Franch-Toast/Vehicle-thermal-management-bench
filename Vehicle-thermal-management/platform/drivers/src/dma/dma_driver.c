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


#include "dma_irq.h"
#include "clock_manager.h"
#include "interrupt_manager.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/


/*! @brief Array of base addresses for DMA instances. */
static DMA_Type *const s_dmaBase[DMA_INSTANCE_COUNT] = DMA_BASE_PTRS;

/*! @brief Array of default DMA channel interrupt handlers. */
static const IRQn_Type s_dmaIrqId[FEATURE_DMA_VIRTUAL_CHANNELS_INTERRUPT_LINES] = DMA_CHN_IRQS;

#ifdef FEATURE_DMA_HAS_ERROR_IRQ
/*! @brief Array of default DMA error interrupt handlers. */
static const IRQn_Type s_dmaErrIrqId[FEATURE_DMA_VIRTUAL_ERROR_INTERRUPT_LINES] = DMA_ERROR_IRQS;
#endif /* FEATURE_DMA_HAS_ERROR_IRQ */


#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
/*! @brief Array for DMA & DMAMUX clock sources. */
static const clock_names_t s_dmaClockNames[DMA_INSTANCE_COUNT] = FEATURE_DMA_CLOCK_NAMES;
#endif /* (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT) */

/*! @brief DMA global structure to maintain DMA state */
static dma_state_t *s_virtEdmaState;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DMA_DRV_ClearIntStatus(uint8_t virtualChannel);

static void DMA_DRV_ClearSoftwareCTS(dma_software_cts_t *scts);

static void DMA_DRV_ClearStructure(uint8_t *sructPtr, size_t size);

#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)

static bool DMA_DRV_ValidTransferSize(dma_transfer_size_t size);

#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_Init
 * Description   : Initializes the DMA module.
 *
 * Implements    : DMA_DRV_Init_Activity
 *END**************************************************************************/
status_t DMA_DRV_Init(dma_state_t *dmaState,
                      const dma_user_config_t *userConfig,
                      dma_chn_state_t *const chnStateArray[],
                      const dma_channel_config_t *const chnConfigArray[],
                      uint32_t chnCount)
{
    uint32_t index;
    DMA_Type *dmaRegBase = NULL;
    IRQn_Type irqNumber;
    status_t dmaStatus = STATUS_SUCCESS;
    status_t chnInitStatus;
#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    uint32_t freq = 0U;
    status_t clockManagerStatus;
#endif

    /* Check the state and configuration structure pointers are valid */
    DEV_ASSERT((dmaState != NULL) && (userConfig != NULL));

    /* Check the module has not already been initialized */
    DEV_ASSERT(s_virtEdmaState == NULL);

#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    /* Check that DMA and DMAMUX modules are clock gated on */
    for (index = 0U; index < (uint32_t) DMA_INSTANCE_COUNT; index++)
    {
        clockManagerStatus = CLOCK_SYS_GetFreq(s_dmaClockNames[index], &freq);
        DEV_ASSERT(clockManagerStatus == STATUS_SUCCESS);
    }
#endif /* (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT) */

    /* Save the runtime state structure for the driver */
    s_virtEdmaState = dmaState;

    /* Clear the state structure. */
    DMA_DRV_ClearStructure((uint8_t *) s_virtEdmaState, sizeof(dma_state_t));

    /* Init all DMA instances */
    for (index = 0U; index < (uint32_t) DMA_INSTANCE_COUNT; index++)
    {
        dmaRegBase = s_dmaBase[index];

        /* Init DMA module on hardware level. */
        DMA_Init(dmaRegBase);

        /* Set 'Halt on error' configuration */
        DMA_SetHaltOnErrorCmd(dmaRegBase, userConfig->haltOnError);
    }

#if defined FEATURE_DMA_HAS_ERROR_IRQ
    /* Enable the error interrupts for DMA module. */
    for (index = 0U; index < (uint32_t) FEATURE_DMA_VIRTUAL_ERROR_INTERRUPT_LINES; index++)
    {
        /* Enable channel interrupt ID. */
        irqNumber = s_dmaErrIrqId[index];
        INT_SYS_EnableIRQ(irqNumber);
    }
#endif

    /* Register all dma channel interrupt handlers into vector table. */
    for (index = 0U; index < (uint32_t) FEATURE_DMA_VIRTUAL_CHANNELS_INTERRUPT_LINES; index++)
    {
        /* Enable channel interrupt ID. */
        irqNumber = s_dmaIrqId[index];
        INT_SYS_EnableIRQ(irqNumber);
    }

#ifdef FEATURE_DMAMUX_AVAILABLE
    /* Initialize all DMAMUX instances */
    DMAMUX_Init(dmaRegBase);
#endif

    /* Initialize the channels based on configuration list */
    if ((chnStateArray != NULL) && (chnConfigArray != NULL))
    {
        for (index = 0U; index < chnCount; index++)
        {
            chnInitStatus = DMA_DRV_ChannelInit(chnStateArray[index], chnConfigArray[index]);
            if (chnInitStatus != STATUS_SUCCESS)
            {
                dmaStatus = chnInitStatus;
            }
        }
    }

    return dmaStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_Deinit
 * Description   : Deinitialize DMA.
 *
 * Implements    : DMA_DRV_Deinit_Activity
 *END**************************************************************************/
status_t DMA_DRV_Deinit(void)
{
    uint32_t index;
    IRQn_Type irqNumber;
    const dma_chn_state_t *chnState = NULL;

#if defined FEATURE_DMA_HAS_ERROR_IRQ
    /* Disable the error interrupts for DMA module. */
    for (index = 0U; index < (uint32_t) FEATURE_DMA_VIRTUAL_ERROR_INTERRUPT_LINES; index++)
    {
        /* Enable channel interrupt ID. */
        irqNumber = s_dmaErrIrqId[index];
        INT_SYS_DisableIRQ(irqNumber);
    }
#endif

    if (s_virtEdmaState != NULL)
    {
        /* Release all dma channel. */
        for (index = 0U; index < (uint32_t) FEATURE_DMA_VIRTUAL_CHANNELS; index++)
        {
            /* Release all channels. */
            chnState = s_virtEdmaState->virtChnState[index];
            if (chnState != NULL)
            {
                (void) DMA_DRV_ReleaseChannel(chnState->virtChn);
            }
        }
        for (index = 0U; index < (uint32_t) FEATURE_DMA_VIRTUAL_CHANNELS_INTERRUPT_LINES; index++)
        {
            /* Disable channel interrupts. */
            irqNumber = s_dmaIrqId[index];
            INT_SYS_DisableIRQ(irqNumber);
        }
    }

    s_virtEdmaState = NULL;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ChannelInit
 * Description   : Initialize DMA channel.
 *
 * Implements    : DMA_DRV_ChannelInit_Activity
 *END**************************************************************************/
status_t DMA_DRV_ChannelInit(dma_chn_state_t *dmaChannelState,
                             const dma_channel_config_t *dmaChannelConfig)
{
    /* Check the state and configuration structure pointers are valid */
    DEV_ASSERT((dmaChannelState != NULL) && (dmaChannelConfig != NULL));

    /* Check if the module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check the channel has not already been allocated */
    DEV_ASSERT(s_virtEdmaState->virtChnState[dmaChannelConfig->virtChnConfig] == NULL);

    /* Check if the channel defined by user in the channel configuration structure is valid */
    DEV_ASSERT(dmaChannelConfig->virtChnConfig < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(dmaChannelConfig->virtChnConfig);

    /* Get DMA channel from virtual channel */
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(dmaChannelConfig->virtChnConfig);

    /* Get virtual channel value */
    uint8_t virtualChannel = dmaChannelConfig->virtChnConfig;

    /* Get status */
    status_t retStatus;

    /* Load corresponding DMA instance pointer */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];

    /* Reset the channel state structure to default value. */
    DMA_DRV_ClearStructure((uint8_t *) dmaChannelState, sizeof(dma_chn_state_t));

#ifdef FEATURE_DMAMUX_AVAILABLE
    retStatus = DMA_DRV_SetChannelRequestAndTrigger(dmaChannelConfig->virtChnConfig,
                                                    (uint8_t) dmaChannelConfig->source);
#endif

    /* Clear the CTS registers for this channel */
    DMA_CTSClearReg(dmaRegBase, dmaChannel);

#ifdef FEATURE_DMAMUX_AVAILABLE
    if (retStatus == STATUS_SUCCESS)
#endif
    {
        /* Set virtual channel state */
        s_virtEdmaState->virtChnState[virtualChannel] = dmaChannelState;
        /* Set virtual channel value */
        s_virtEdmaState->virtChnState[virtualChannel]->virtChn = virtualChannel;
        /* Set virtual channel status to normal */
        s_virtEdmaState->virtChnState[virtualChannel]->status = DMA_CHN_NORMAL;

        /* Enable error interrupt for this channel */
        DMA_SetErrorIntCmd(dmaRegBase, dmaChannel, true);

        /* Set the channel priority, as defined in the configuration, only if fixed arbitration mode is selected */
        // if ((DMA_GetChannelArbitrationMode(dmaRegBase) == DMA_ARBITRATION_FIXED_PRIORITY) &&
        //     (dmaChannelConfig->channelPriority != DMA_CHN_DEFAULT_PRIORITY))
        // {
        //     DMA_SetChannelPriority(dmaRegBase, dmaChannel, dmaChannelConfig->channelPriority);
        // }
        /* Install the user callback */
        retStatus = DMA_DRV_InstallCallback(dmaChannelConfig->virtChnConfig, dmaChannelConfig->callback,
                                            dmaChannelConfig->callbackParam);
    }

    return retStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_InstallCallback
 * Description   : Register callback function and parameter.
 *
 * Implements    : DMA_DRV_InstallCallback_Activity
 *END**************************************************************************/
status_t DMA_DRV_InstallCallback(uint8_t virtualChannel,
                                 dma_callback_t callback,
                                 void *parameter)
{
    /* Check the channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check the channel is allocated */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    s_virtEdmaState->virtChnState[virtualChannel]->callback = callback;
    s_virtEdmaState->virtChnState[virtualChannel]->parameter = parameter;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ReleaseChannel
 * Description   : Free DMA channel's hardware and software resource.
 *
 * Implements    : DMA_DRV_ReleaseChannel_Activity
 *END**************************************************************************/
status_t DMA_DRV_ReleaseChannel(uint8_t virtualChannel)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check the DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Get pointer to channel state */
    dma_chn_state_t *chnState = s_virtEdmaState->virtChnState[virtualChannel];

    /* Check that virtual channel is initialized */
    DEV_ASSERT(chnState != NULL);

    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];

    /* Stop dma channel. */
    DMA_SetDmaRequestCmd(dmaRegBase, dmaChannel, false);

    /* Reset the channel state structure to default value. */
    DMA_DRV_ClearStructure((uint8_t *) chnState, sizeof(dma_chn_state_t));

    s_virtEdmaState->virtChnState[virtualChannel] = NULL;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ClearIntStatus
 * Description   : Clear done and interrupt retStatus.
 *
 *END**************************************************************************/
static void DMA_DRV_ClearIntStatus(uint8_t virtualChannel)
{
    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_ClearDoneStatusFlag(dmaRegBase, dmaChannel);
    DMA_ClearIntStatusFlag(dmaRegBase, dmaChannel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ClearSoftwareCTS
 * Description   : Clear the software cts structure.
 *
 *END**************************************************************************/
static void DMA_DRV_ClearSoftwareCTS(dma_software_cts_t *scts)
{
    DMA_DRV_ClearStructure((uint8_t *) scts, sizeof(dma_software_cts_t));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_IRQHandler
 * Description   : DMA IRQ handler.
 *END**************************************************************************/
void DMA_DRV_IRQHandler(uint8_t virtualChannel)
{
    const dma_chn_state_t *chnState = s_virtEdmaState->virtChnState[virtualChannel];
    if (chnState != NULL)
    {
        if (chnState->callback != NULL)
        {
            chnState->callback(chnState->parameter, chnState->status);
        }
    }
    DMA_DRV_ClearIntStatus(virtualChannel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ErrorIRQHandler
 * Description   : DMA error IRQ handler
 *END**************************************************************************/
void DMA_DRV_ErrorIRQHandler(uint8_t virtualChannel)
{
    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_SetDmaRequestCmd(dmaRegBase, dmaChannel, false);
    dma_chn_state_t *chnState = s_virtEdmaState->virtChnState[virtualChannel];
    if (chnState != NULL)
    {
        chnState->status = DMA_CHN_ERROR;
        if (chnState->callback != NULL)
        {
            chnState->callback(chnState->parameter, chnState->status);
        }
        DMA_DRV_ClearIntStatus(virtualChannel);
        DMA_ClearErrorIntStatusFlag(dmaRegBase, dmaChannel);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ConfigSingleBlockTransfer
 * Description   : Configures a DMA single block transfer.
 *
 * Implements    : DMA_DRV_ConfigSingleBlockTransfer_Activity
 *END**************************************************************************/
status_t DMA_DRV_ConfigSingleBlockTransfer(uint8_t virtualChannel,
                                           dma_transfer_type_t type,
                                           uint32_t srcAddr,
                                           uint32_t destAddr,
                                           dma_transfer_size_t transferSize,
                                           uint32_t dataBufferSize)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    /* Check if the value passed for 'transferSize' is valid */
    DEV_ASSERT(DMA_DRV_ValidTransferSize(transferSize));
#endif

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    status_t retStatus = STATUS_SUCCESS;

    /* Compute the transfer offset, based on transfer size.
     * The number of bytes transferred in each source read/destination write
     * is obtained with the following formula:
     *    source_read_size = 2^SSIZE
     *    destination_write_size = 2^DSIZE
     */
    uint8_t transferOffset = (uint8_t) (1U << ((uint8_t) transferSize));

    /* Check that source address and destination address are valid */
    DEV_ASSERT((srcAddr % transferOffset) == 0U);
    DEV_ASSERT((destAddr % transferOffset) == 0U);

    /* The number of bytes to be transferred (buffer size) must
     * be a multiple of the source read/destination write size
     */
    if ((dataBufferSize % transferOffset) != 0U)
    {
        retStatus = STATUS_ERROR;
    }

    if (retStatus == STATUS_SUCCESS)
    {
        /* Clear transfer control descriptor for the current channel */
        DMA_CTSClearReg(dmaRegBase, dmaChannel);

#ifdef FEATURE_DMA_ENGINE_STALL
        /* Configure the DMA Engine to stall for a number of cycles after each R/W */
        DMA_CTSSetEngineStall(dmaRegBase, dmaChannel, DMA_ENGINE_STALL_4_CYCLES);
#endif

        DMA_SetTransferLoopMappingCmd(dmaRegBase, true);

        /* Configure source and destination addresses */
        DMA_CTSSetSrcAddr(dmaRegBase, dmaChannel, srcAddr);
        DMA_CTSSetDestAddr(dmaRegBase, dmaChannel, destAddr);

        /* Set transfer size (1B/2B/4B/16B/32B) */
        DMA_CTSSetAttribute(dmaRegBase, dmaChannel, DMA_MODULO_OFF, DMA_MODULO_OFF, transferSize, transferSize);

        /* Configure source/destination offset. */
        switch (type)
        {
            case DMA_TRANSFER_PERIPH2MEM:
                DMA_CTSSetSrcOffset(dmaRegBase, dmaChannel, 0);
                DMA_CTSSetDestOffset(dmaRegBase, dmaChannel, (int8_t) transferOffset);
                break;
            case DMA_TRANSFER_MEM2PERIPH:
                DMA_CTSSetSrcOffset(dmaRegBase, dmaChannel, (int8_t) transferOffset);
                DMA_CTSSetDestOffset(dmaRegBase, dmaChannel, 0);
                break;
            case DMA_TRANSFER_MEM2MEM:
                DMA_CTSSetSrcOffset(dmaRegBase, dmaChannel, (int8_t) transferOffset);
                DMA_CTSSetDestOffset(dmaRegBase, dmaChannel, (int8_t) transferOffset);
                break;
            case DMA_TRANSFER_PERIPH2PERIPH:
                DMA_CTSSetSrcOffset(dmaRegBase, dmaChannel, 0);
                DMA_CTSSetDestOffset(dmaRegBase, dmaChannel, 0);
                break;
            default:
                /* This should never be reached - all the possible values have been handled. */
                break;
        }

        /* Set the total number of bytes to be transfered */
        DMA_CTSSetNbytes(dmaRegBase, dmaChannel, dataBufferSize);

        /* Set major iteration count to 1 (single block mode) */
        DMA_CTSSetTriggerCount(dmaRegBase, dmaChannel, 1U);

        /* Enable interrupt when the transfer completes */
        DMA_CTSSetMajorCompleteIntCmd(dmaRegBase, dmaChannel, true);

        /* Set virtual channel status to normal */
        s_virtEdmaState->virtChnState[virtualChannel]->status = DMA_CHN_NORMAL;
    }

    return retStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ConfigMultiBlockTransfer
 * Description   : Configures a DMA single block transfer.
 *
 * Implements    : DMA_DRV_ConfigMultiBlockTransfer_Activity
 *END**************************************************************************/
status_t DMA_DRV_ConfigMultiBlockTransfer(uint8_t virtualChannel,
                                          dma_transfer_type_t type,
                                          uint32_t srcAddr,
                                          uint32_t destAddr,
                                          dma_transfer_size_t transferSize,
                                          uint32_t blockSize,
                                          uint32_t blockCount,
                                          bool disableReqOnCompletion)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    status_t retStatus;

#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    /* Compute the transfer offset, based on transfer size.
     * The number of bytes transferred in each source read/destination write
     * is obtained with the following formula:
     *    source_read_size = 2^SSIZE
     *    destination_write_size = 2^DSIZE
     */
    uint8_t transferOffset = (uint8_t) (1U << ((uint8_t) transferSize));

    /* Check that source address and destination address are valid */
    DEV_ASSERT((srcAddr % transferOffset) == 0U);
    DEV_ASSERT((destAddr % transferOffset) == 0U);
#endif /* (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT) */

    /* Configure the transfer for one data block */
    retStatus = DMA_DRV_ConfigSingleBlockTransfer(virtualChannel, type, srcAddr, destAddr, transferSize, blockSize);

    if (retStatus == STATUS_SUCCESS)
    {
        DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];

        /* Set the number of data blocks */
        DMA_CTSSetTriggerCount(dmaRegBase, dmaChannel, blockCount);

        /* Enable/disable requests upon completion */
        DMA_CTSSetDisableDmaRequestAfterCTSDoneCmd(dmaRegBase, dmaChannel, disableReqOnCompletion);
    }

    return retStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ConfigLoopTransfer
 * Description   : Configures the DMA transfer in a loop.
 *
 * Implements    : DMA_DRV_ConfigLoopTransfer_Activity
 *END**************************************************************************/
status_t DMA_DRV_ConfigLoopTransfer(uint8_t virtualChannel,
                                    const dma_transfer_config_t *transferConfig)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Check the transfer configuration structure is valid */
    DEV_ASSERT(transferConfig != NULL);

#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    /* Compute the transfer offset, based on transfer size.
     * The number of bytes transferred in each source read/destination write
     * is obtained with the following formula:
     *    source_read_size = 2^SSIZE
     *    destination_write_size = 2^DSIZE
     */
    uint8_t srcTransferOffset = (uint8_t) (1U << ((uint8_t) transferConfig->srcTransferSize));
    uint8_t destTransferOffset = (uint8_t) (1U << ((uint8_t) transferConfig->destTransferSize));

    /* Check that source address and destination address are valid */
    DEV_ASSERT((transferConfig->srcAddr % srcTransferOffset) == 0U);
    DEV_ASSERT((transferConfig->destAddr % destTransferOffset) == 0U);
#endif /* (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT) */

    /* Check the transfer/trigger loop properties are defined */
    DEV_ASSERT(transferConfig->loopTransferConfig != NULL);

    /* If the modulo feature is enabled, check alignment of addresses */
    DEV_ASSERT((transferConfig->srcModulo == DMA_MODULO_OFF) ||
               ((transferConfig->srcAddr % (((uint32_t) 1U) << (uint32_t) transferConfig->srcModulo)) == 0U));
    DEV_ASSERT((transferConfig->destModulo == DMA_MODULO_OFF) ||
               ((transferConfig->destAddr % (((uint32_t) 1U) << (uint32_t) transferConfig->destModulo)) == 0U));

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);


    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];

    DMA_SetTransferLoopMappingCmd(dmaRegBase, true);
    /* Write the configuration in the transfer control descriptor registers */
    DMA_DRV_PushConfigToReg(virtualChannel, transferConfig);

    /* Set virtual channel status to normal */
    s_virtEdmaState->virtChnState[virtualChannel]->status = DMA_CHN_NORMAL;

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ConfigRamReloadTransfer
 * Description   : Configure DMA for ram reload operation
 *
 * Implements    : DMA_DRV_ConfigRamReloadTransfer_Activity
 *END**************************************************************************/
status_t DMA_DRV_ConfigRamReloadTransfer(uint8_t virtualChannel,
                                         dma_software_cts_t *scts,
                                         dma_transfer_size_t transferSize,
                                         uint32_t bytesOnEachRequest,
                                         const dma_ram_reload_list_t *srcList,
                                         const dma_ram_reload_list_t *destList,
                                         uint8_t ctsCount)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Check the input arrays for ram reload operation are valid */
    DEV_ASSERT((scts != NULL) && (srcList != NULL) && (destList != NULL));

#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)
    /* Check if the value passed for 'transferSize' is valid */
    DEV_ASSERT(DMA_DRV_ValidTransferSize(transferSize));
#endif

    uint8_t i;
    uint16_t transferOffset;
    uint32_t sctsAlignedAddr = SCTS_ADDR(scts);
    dma_software_cts_t *dmaSwTcdAddr = (dma_software_cts_t *) sctsAlignedAddr;
    dma_loop_transfer_config_t dmaLoopConfig;
    dma_transfer_config_t dmaTransferConfig;
    status_t retStatus = STATUS_SUCCESS;

    /* Set virtual channel status to normal */
    s_virtEdmaState->virtChnState[virtualChannel]->status = DMA_CHN_NORMAL;

    /* Compute the transfer offset, based on transfer size.
     * The number of bytes transferred in each source read/destination write
     * is obtained with the following formula:
     *    source_read_size = 2^SSIZE
     *    destination_write_size = 2^DSIZE
     */
    transferOffset = (uint16_t) (1UL << ((uint16_t) transferSize));

    /* The number of bytes to be transferred on each request must
     * be a multiple of the source read/destination write size
     */
    if ((bytesOnEachRequest % transferOffset) != 0U)
    {
        retStatus = STATUS_ERROR;
    }

    /* Clear the configuration structures before initializing them. */
    DMA_DRV_ClearStructure((uint8_t *) (&dmaTransferConfig), sizeof(dma_transfer_config_t));
    DMA_DRV_ClearStructure((uint8_t *) (&dmaLoopConfig), sizeof(dma_loop_transfer_config_t));

    /* Configure the transfer for ram reload mode. */
    dmaTransferConfig.srcLastAddrAdjust = 0;
    dmaTransferConfig.destLastAddrAdjust = 0;
    dmaTransferConfig.srcModulo = DMA_MODULO_OFF;
    dmaTransferConfig.destModulo = DMA_MODULO_OFF;
    dmaTransferConfig.srcTransferSize = transferSize;
    dmaTransferConfig.destTransferSize = transferSize;
    dmaTransferConfig.transferLoopByteCount = bytesOnEachRequest;
    dmaTransferConfig.interruptEnable = true;
    dmaTransferConfig.ramReloadEnable = true;
    dmaTransferConfig.loopTransferConfig = &dmaLoopConfig;
    dmaTransferConfig.loopTransferConfig->srcOffsetEnable = false;
    dmaTransferConfig.loopTransferConfig->dstOffsetEnable = false;
    dmaTransferConfig.loopTransferConfig->transferLoopChnLinkEnable = false;
    dmaTransferConfig.loopTransferConfig->triggerLoopChnLinkEnable = false;

    /* Copy ram reload lists to transfer configuration*/
    for (i = 0U; (i < ctsCount) && (retStatus == STATUS_SUCCESS); i++)
    {
        dmaTransferConfig.srcAddr = srcList[i].address;
        dmaTransferConfig.destAddr = destList[i].address;
        if ((srcList[i].length != destList[i].length) || (srcList[i].type != destList[i].type))
        {
            retStatus = STATUS_ERROR;
            break;
        }
        dmaTransferConfig.loopTransferConfig->triggerLoopIterationCount = srcList[i].length / bytesOnEachRequest;

        switch (srcList[i].type)
        {
            case DMA_TRANSFER_PERIPH2MEM:
                /* Configure Source Read. */
                dmaTransferConfig.srcOffset = 0;
                /* Configure Dest Write. */
                dmaTransferConfig.destOffset = (int16_t) transferOffset;
                break;
            case DMA_TRANSFER_MEM2PERIPH:
                /* Configure Source Read. */
                dmaTransferConfig.srcOffset = (int16_t) transferOffset;
                /* Configure Dest Write. */
                dmaTransferConfig.destOffset = 0;
                break;
            case DMA_TRANSFER_MEM2MEM:
                /* Configure Source Read. */
                dmaTransferConfig.srcOffset = (int16_t) transferOffset;
                /* Configure Dest Write. */
                dmaTransferConfig.destOffset = (int16_t) transferOffset;
                break;
            case DMA_TRANSFER_PERIPH2PERIPH:
                /* Configure Source Read. */
                dmaTransferConfig.srcOffset = 0;
                /* Configure Dest Write. */
                dmaTransferConfig.destOffset = 0;
                break;
            default:
                /* This should never be reached - all the possible values have been handled. */
                break;
        }

        /* Configure the pointer to next software CTS structure; for the last one, this address should be 0 */
        if (i == ((uint8_t) (ctsCount - 1U)))
        {
            dmaTransferConfig.ramReloadNextDescAddr = 0U;
        } else
        {
            dma_software_cts_t *ptNextAddr = &dmaSwTcdAddr[i];
            dmaTransferConfig.ramReloadNextDescAddr = ((uint32_t) ptNextAddr);
        }

        if (i == 0U)
        {
            /* Push the configuration for the first descriptor to registers */
            DMA_DRV_PushConfigToReg(virtualChannel, &dmaTransferConfig);
        } else
        {
            /* Copy configuration to software CTS structure */
            DMA_DRV_PushConfigToSCTS(&dmaTransferConfig, &dmaSwTcdAddr[i - 1U]);
        }
    }

    return retStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_StartChannel
 * Description   : Starts an DMA channel.
 *
 * Implements    : DMA_DRV_StartChannel_Activity
 *END**************************************************************************/
status_t DMA_DRV_StartChannel(uint8_t virtualChannel)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Enable requests for current channel */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_SetDmaRequestCmd(dmaRegBase, dmaChannel, true);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_StopChannel
 * Description   : Stops an DMA channel.
 *
 * Implements    : DMA_DRV_StopChannel_Activity
 *END**************************************************************************/
status_t DMA_DRV_StopChannel(uint8_t virtualChannel)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Disable requests for current channel */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_SetDmaRequestCmd(dmaRegBase, dmaChannel, false);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetChannelRequestAndTrigger
 * Description   : Sets DMA channel request source in DMAMUX and controls
 *                 the DMA channel periodic triggering.
 *
 * Implements    : DMA_DRV_SetChannelRequestAndTrigger_Activity
 *END**************************************************************************/
status_t DMA_DRV_SetChannelRequestAndTrigger(uint8_t virtualChannel,
                                             uint8_t request)
{
    /* Check the virtual channel number is valid */
    DEV_ASSERT(virtualChannel < (uint32_t) FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

#ifdef FEATURE_DMAMUX_AVAILABLE
    /* Get request index for the corresponding DMAMUX instance */
    uint8_t dmaMuxRequest = (uint8_t) FEATURE_DMAMUX_REQ_SRC_TO_CH(request);

    /* Get DMAMUX channel for the selected request */
    uint8_t dmaMuxChannel = (uint8_t) FEATURE_DMAMUX_DMA_CH_TO_CH(virtualChannel);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Disable requests for current channel */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    /* Set request and trigger */
    //DMAMUX_SetChannelCmd(dmaMuxRegBase, dmaMuxChannel, false);
    DMAMUX_SetChannelSource(dmaRegBase, dmaMuxChannel, dmaMuxRequest);
    //DMAMUX_SetChannelCmd(dmaMuxRegBase, dmaMuxChannel, true);

    return STATUS_SUCCESS;
#else
    (void)virtualChannel;    
    (void)request;
    (void)enableTrigger;    
    return STATUS_UNSUPPORTED;
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ClearCTS
 * Description   : Clears all registers to 0 for the hardware CTS.
 *
 * Implements    : DMA_DRV_ClearCTS_Activity
 *END**************************************************************************/
void DMA_DRV_ClearCTS(uint8_t virtualChannel)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Clear the CTS memory */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_CTSClearReg(dmaRegBase, dmaChannel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetSrcAddr
 * Description   : Configures the source address for the DMA channel.
 *
 * Implements    : DMA_DRV_SetSrcAddr_Activity
 *END**************************************************************************/
void DMA_DRV_SetSrcAddr(uint8_t virtualChannel,
                        uint32_t address)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Set channel CTS source address */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_CTSSetSrcAddr(dmaRegBase, dmaChannel, address);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetSrcOffset
 * Description   : Configures the source address signed offset for the DMA channel.
 *
 * Implements    : DMA_DRV_SetSrcOffset_Activity
 *END**************************************************************************/
void DMA_DRV_SetSrcOffset(uint8_t virtualChannel,
                          int16_t offset)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Set channel CTS source offset */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_CTSSetSrcOffset(dmaRegBase, dmaChannel, offset);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetSrcReadChunkSize
 * Description   : Configures the source read data chunk size (transferred in a read sequence).
 *
 * Implements    : DMA_DRV_SetSrcReadChunkSize_Activity
 *END**************************************************************************/
void DMA_DRV_SetSrcReadChunkSize(uint8_t virtualChannel,
                                 dma_transfer_size_t size)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Set channel CTS source transfer size */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_CTSSetSrcTransferSize(dmaRegBase, dmaChannel, size);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetSrcLastAddrAdjustment
 * Description   : Configures the source address last adjustment.
 *
 * Implements    : DMA_DRV_SetSrcLastAddrAdjustment_Activity
 *END**************************************************************************/
void DMA_DRV_SetSrcLastAddrAdjustment(uint8_t virtualChannel,
                                      int32_t adjust)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Set channel CTS source last adjustment */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_CTSSetSrcLastAdjust(dmaRegBase, dmaChannel, adjust);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetDestLastAddrAdjustment
 * Description   : Configures the source address last adjustment.
 *
 * Implements    : DMA_DRV_SetDestLastAddrAdjustment_Activity
 *END**************************************************************************/
void DMA_DRV_SetDestLastAddrAdjustment(uint8_t virtualChannel,
                                       int32_t adjust)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Set channel CTS source last adjustment */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_CTSSetDestLastAdjust(dmaRegBase, dmaChannel, adjust);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetDestAddr
 * Description   : Configures the destination address for the DMA channel.
 *
 * Implements    : DMA_DRV_SetDestAddr_Activity
 *END**************************************************************************/
void DMA_DRV_SetDestAddr(uint8_t virtualChannel,
                         uint32_t address)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Set channel CTS destination address */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_CTSSetDestAddr(dmaRegBase, dmaChannel, address);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetDestOffset
 * Description   : Configures the destination address signed offset for the DMA channel.
 *
 * Implements    : DMA_DRV_SetDestOffset_Activity
 *END**************************************************************************/
void DMA_DRV_SetDestOffset(uint8_t virtualChannel,
                           int16_t offset)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Set channel CTS destination offset */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_CTSSetDestOffset(dmaRegBase, dmaChannel, offset);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetDestWriteChunkSize
 * Description   : Configures the destination data chunk size (transferred in a write sequence).
 *
 * Implements    : DMA_DRV_SetDestWriteChunkSize_Activity
 *END**************************************************************************/
void DMA_DRV_SetDestWriteChunkSize(uint8_t virtualChannel,
                                   dma_transfer_size_t size)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Set channel CTS source transfer size */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_CTSSetDestTransferSize(dmaRegBase, dmaChannel, size);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetTransferLoopBlockSize
 * Description   : Configures the number of bytes to be transferred in each service request of the channel.
 *
 * Implements    : DMA_DRV_SetTransferLoopBlockSize_Activity
 *END**************************************************************************/
void DMA_DRV_SetTransferLoopBlockSize(uint8_t virtualChannel,
                                      uint32_t nbytes)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Set channel CTS transfer loop block size */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_CTSSetNbytes(dmaRegBase, dmaChannel, nbytes);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetTriggerLoopIterationCount
 * Description   : Configures the number of trigger loop iterations.
 *
 * Implements    : DMA_DRV_SetTriggerLoopIterationCount_Activity
 *END**************************************************************************/
void DMA_DRV_SetTriggerLoopIterationCount(uint8_t virtualChannel,
                                          uint32_t majorLoopCount)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Set the trigger loop iteration count */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_CTSSetTriggerCount(dmaRegBase, dmaChannel, majorLoopCount);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_GetRemainingTriggerIterationsCount
 * Description   : Returns the remaining trigger loop iteration count.
 *
 * Implements    : DMA_DRV_GetRemainingTriggerIterationsCount_Activity
 *END**************************************************************************/
uint32_t DMA_DRV_GetRemainingTriggerIterationsCount(uint8_t virtualChannel)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Retrieve the number of transfer loops yet to be triggered */
    const DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    uint32_t count = DMA_CTSGetCurrentTriggerCount(dmaRegBase, dmaChannel);

    return count;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetRamReloadLink
 * Description   : Configures the memory address of the next CTS, in ram reload mode.
 *
 * Implements    : DMA_DRV_SetRamReloadLink_Activity
 *END**************************************************************************/
void DMA_DRV_SetRamReloadLink(uint8_t virtualChannel,
                              uint32_t nextCTSAddr)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Configures the memory address of the next CTS */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_CTSSetRamReloadLink(dmaRegBase, dmaChannel, nextCTSAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_DisableRequestsOnTransferComplete
 * Description   : Disables/Enables the DMA request after the trigger loop completes for the CTS.
 *
 * Implements    : DMA_DRV_DisableRequestsOnTransferComplete_Activity
 *END**************************************************************************/
void DMA_DRV_DisableRequestsOnTransferComplete(uint8_t virtualChannel,
                                               bool disable)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Disables/Enables the DMA request upon CTS completion */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_CTSSetDisableDmaRequestAfterCTSDoneCmd(dmaRegBase, dmaChannel, disable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ConfigureInterrupt
 * Description   : Disables/Enables the channel interrupt requests.
 *
 * Implements    : DMA_DRV_ConfigureInterrupt_Activity
 *END**************************************************************************/
void DMA_DRV_ConfigureInterrupt(uint8_t virtualChannel,
                                dma_channel_interrupt_t intSrc,
                                bool enable)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Disables/Enables the channel interrupt requests. */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    switch (intSrc)
    {
        case DMA_CHN_ERR_INT:
            /* Enable channel interrupt request when error conditions occur */
            DMA_SetErrorIntCmd(dmaRegBase, dmaChannel, enable);
            break;
        case DMA_CHN_HALF_MAJOR_LOOP_INT:
            /* Enable channel interrupt request when major iteration count reaches halfway point */
            DMA_CTSSetMajorHalfCompleteIntCmd(dmaRegBase, dmaChannel, enable);
            break;
        case DMA_CHN_MAJOR_LOOP_INT:
            /* Enable channel interrupt request when major iteration count reaches zero */
            DMA_CTSSetMajorCompleteIntCmd(dmaRegBase, dmaChannel, enable);
            break;
        default:
            /* This branch should never be reached if driver API is used properly */
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_CancelTransfer
 * Description   : Cancels the running transfer for this channel.
 *
 * Implements    : DMA_DRV_CancelTransfer_Activity
 *END**************************************************************************/
void DMA_DRV_CancelTransfer(bool error)
{
    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    uint32_t dmaInstance;

    for (dmaInstance = 0U; dmaInstance < (uint32_t) DMA_INSTANCE_COUNT; dmaInstance++)
    {
        /* Cancel the running transfer. */
        DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
        if (error)
        {
            DMA_CancelTransferWithError(dmaRegBase);
        } else
        {
            DMA_CancelTransfer(dmaRegBase);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_TriggerSwRequest
 * Description   : Triggers a sw request for the current channel.
 *
 * Implements    : DMA_DRV_TriggerSwRequest_Activity
 *END**************************************************************************/
void DMA_DRV_TriggerSwRequest(uint8_t virtualChannel)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    /* Trigger the channel transfer. */
    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];
    DMA_TriggerChannelStart(dmaRegBase, dmaChannel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_PushConfigToSCTS
 * Description   : Copy the configuration to the software CTS structure.
 *
 * Implements    : DMA_DRV_PushConfigToSCTS_Activity
 *END**************************************************************************/
void DMA_DRV_PushConfigToSCTS(const dma_transfer_config_t *config,
                              dma_software_cts_t *scts)
{
    if ((config != NULL) && (scts != NULL))
    {
        /* Clear the array of software CTSs passed by the user */
        DMA_DRV_ClearSoftwareCTS(scts);

        /* Set the software CTS fields */
        scts->ATTR = (uint16_t) (DMA_CTS_TCR_SMOD(config->srcModulo) | DMA_CTS_TCR_SSIZE(config->srcTransferSize) |
                                 DMA_CTS_TCR_DMOD(config->destModulo) | DMA_CTS_TCR_DSIZE(config->destTransferSize));
        scts->SADDR = config->srcAddr;
        scts->SOFF = config->srcOffset;
        scts->BCNT = config->transferLoopByteCount;
        scts->STO = config->srcLastAddrAdjust;
        scts->DADDR = config->destAddr;
        scts->DOFF = config->destOffset;
        scts->TCNT = (uint16_t) config->loopTransferConfig->triggerLoopIterationCount;
        if (config->ramReloadEnable)
        {
            scts->RAM_LOAD_ADDR = (int32_t) config->ramReloadNextDescAddr;
        } else
        {
            scts->RAM_LOAD_ADDR = config->destLastAddrAdjust;
        }
        scts->CSR = (uint16_t) (((config->interruptEnable ? 1UL : 0UL) << DMA_CTS_CSR_TDINT_SHIFT) |
                                ((config->ramReloadEnable ? 1UL : 0UL) << DMA_CTS_CSR_RLDEN_SHIFT));
        scts->TCNTRV = (uint16_t) config->loopTransferConfig->triggerLoopIterationCount;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_PushConfigToReg
 * Description   : Copy the configuration to the CTS registers.
 *
 * Implements    : DMA_DRV_PushConfigToReg_Activity
 *END**************************************************************************/
void DMA_DRV_PushConfigToReg(uint8_t virtualChannel,
                             const dma_transfer_config_t *cts)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    /* Check the transfer configuration structure is valid */
    DEV_ASSERT(cts != NULL);

    /* Get DMA instance from virtual channel */
    uint8_t dmaInstance = (uint8_t) FEATURE_DMA_VCH_TO_INSTANCE(virtualChannel);

    /* Get DMA channel from virtual channel*/
    uint8_t dmaChannel = (uint8_t) FEATURE_DMA_VCH_TO_CH(virtualChannel);

    DMA_Type *dmaRegBase = s_dmaBase[dmaInstance];

    /* Clear CTS registers */
    DMA_CTSClearReg(dmaRegBase, dmaChannel);

#ifdef FEATURE_DMA_ENGINE_STALL
    /* Configure the DMA Engine to stall for a number of cycles after each R/W */
    DMA_CTSSetEngineStall(dmaRegBase, dmaChannel, DMA_ENGINE_STALL_4_CYCLES);
#endif

    /* Set source and destination addresses */
    DMA_CTSSetSrcAddr(dmaRegBase, dmaChannel, cts->srcAddr);
    DMA_CTSSetDestAddr(dmaRegBase, dmaChannel, cts->destAddr);
    /* Set source/destination modulo feature and transfer size */
    DMA_CTSSetAttribute(dmaRegBase, dmaChannel, cts->srcModulo, cts->destModulo,
                        cts->srcTransferSize, cts->destTransferSize);
    /* Set source/destination offset and last adjustment; for ram reload operation, destination
     * last adjustment is the address of the next CTS structure to be loaded by the DMA engine */
    DMA_CTSSetSrcOffset(dmaRegBase, dmaChannel, cts->srcOffset);
    DMA_CTSSetDestOffset(dmaRegBase, dmaChannel, cts->destOffset);
    DMA_CTSSetSrcLastAdjust(dmaRegBase, dmaChannel, cts->srcLastAddrAdjust);

    if (cts->ramReloadEnable)
    {
        DMA_CTSSetRamReloadCmd(dmaRegBase, dmaChannel, true);
        DMA_CTSSetRamReloadLink(dmaRegBase, dmaChannel, cts->ramReloadNextDescAddr);
    } else
    {
        DMA_CTSSetRamReloadCmd(dmaRegBase, dmaChannel, false);
        DMA_CTSSetDestLastAdjust(dmaRegBase, dmaChannel, cts->destLastAddrAdjust);
    }

    /* Configure channel interrupt */
    DMA_CTSSetMajorCompleteIntCmd(dmaRegBase, dmaChannel, cts->interruptEnable);

    /* If loop configuration is available, copy transfer/trigger loop setup to registers */
    if (cts->loopTransferConfig != NULL)
    {
        DMA_CTSSetSrcMinorLoopOffsetCmd(dmaRegBase, dmaChannel, cts->loopTransferConfig->srcOffsetEnable);
        DMA_CTSSetDestMinorLoopOffsetCmd(dmaRegBase, dmaChannel, cts->loopTransferConfig->dstOffsetEnable);
        DMA_CTSSetTransferLoopOffset(dmaRegBase, dmaChannel, cts->loopTransferConfig->triggerLoopOffset);
        DMA_CTSSetNbytes(dmaRegBase, dmaChannel, cts->transferLoopByteCount);

        DMA_CTSSetChannelLoopLink(dmaRegBase, dmaChannel, cts->loopTransferConfig->transferLoopChnLinkNumber,
                                  cts->loopTransferConfig->transferLoopChnLinkEnable);
        DMA_CTSSetChannelTriggerLink(dmaRegBase, dmaChannel, cts->loopTransferConfig->triggerLoopChnLinkNumber,
                                     cts->loopTransferConfig->triggerLoopChnLinkEnable);

        DMA_CTSSetTriggerCount(dmaRegBase, dmaChannel, cts->loopTransferConfig->triggerLoopIterationCount);
    } else
    {
        DMA_CTSSetNbytes(dmaRegBase, dmaChannel, cts->transferLoopByteCount);
    }
}

#if defined (CUSTOM_DEVASSERT) || defined (DEV_ERROR_DETECT)

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ValidTransferSize
 * Description   : Check if the transfer size value is legal (0/1/2/4/5).
 *
 *END**************************************************************************/
static bool DMA_DRV_ValidTransferSize(dma_transfer_size_t size)
{
    bool isValid;
    switch (size)
    {
        case DMA_TRANSFER_SIZE_1B:
        case DMA_TRANSFER_SIZE_2B:
        case DMA_TRANSFER_SIZE_4B:
#ifdef FEATURE_DMA_TRANSFER_SIZE_8B
            case DMA_TRANSFER_SIZE_8B:
#endif
#ifdef FEATURE_DMA_TRANSFER_SIZE_16B
            case DMA_TRANSFER_SIZE_16B:
#endif
#ifdef FEATURE_DMA_TRANSFER_SIZE_32B
            case DMA_TRANSFER_SIZE_32B:
#endif
#ifdef FEATURE_DMA_TRANSFER_SIZE_64B
            case DMA_TRANSFER_SIZE_64B:
#endif
            isValid = true;
            break;
        default:
            isValid = false;
            break;
    }
    return isValid;
}

#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_GetChannelStatus
 * Description   : Returns the DMA channel retStatus.
 *
 * Implements    : DMA_DRV_GetChannelStatus_Activity
 *END**************************************************************************/
dma_chn_status_t DMA_DRV_GetChannelStatus(uint8_t virtualChannel)
{
    /* Check that virtual channel number is valid */
    DEV_ASSERT(virtualChannel < FEATURE_DMA_VIRTUAL_CHANNELS);

    /* Check that DMA module is initialized */
    DEV_ASSERT(s_virtEdmaState != NULL);

    /* Check that virtual channel is initialized */
    DEV_ASSERT(s_virtEdmaState->virtChnState[virtualChannel] != NULL);

    return s_virtEdmaState->virtChnState[virtualChannel]->status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_GetDmaRegBaseAddr
 * Description   : Returns the DMA register base address.
 *
 * Implements    : DMA_DRV_GetDmaRegBaseAddr
 *END**************************************************************************/
DMA_Type *DMA_DRV_GetDmaRegBaseAddr(uint32_t instance)
{
    /* Check that instance is valid */
    DEV_ASSERT(instance < DMA_INSTANCE_COUNT);

    return s_dmaBase[instance];
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ClearStructure
 * Description   : Clears all bytes at the passed structure pointer.
 *
 *END**************************************************************************/
static void DMA_DRV_ClearStructure(uint8_t *sructPtr, size_t size)
{
    while (size > 0U)
    {
        *sructPtr = 0;
        sructPtr++;
        size--;
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

