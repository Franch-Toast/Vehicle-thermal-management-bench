
/*
 *  Copyright 2020-2023 Yuntu Microelectronics co.,ltd
 *  All rights reserved.
 * 
 *  YUNTU Confidential. This software is owned or controlled by YUNTU and may only be
 *  used strictly in accordance with the applicable license terms. By expressly
 *  accepting such terms or by downloading, installing, activating and/or otherwise
 *  using the software, you are agreeing that you have read, and that you agree to
 *  comply with and are bound by, such license terms. If you do not agree to be
 *  bound by the applicable license terms, then you may not retain, install,
 *  activate or otherwise use the software. The production use license in
 *  Section 2.3 is expressly granted for this software.
 * 
 * @file dma_config.c
 * @brief 
 * 
 */


#include <stddef.h>
#include "dma_config.h"


/*dma_config0*/


const dma_channel_config_t dma_config0 = {
    .virtChnConfig=0,
    .source=DMA_REQ_Disabled,
    .callback=NULL,
    .callbackParam=NULL,
};


const dma_channel_config_t *const dmaChnConfigArray[NUM_OF_CONFIGURED_DMA_CHANNEL] = {
    &dma_config0,
};

const dma_user_config_t dmaController_InitConfig = {
    .haltOnError = false
};

dma_chn_state_t dma_config0_State;



dma_chn_state_t *const dmaChnState[NUM_OF_CONFIGURED_DMA_CHANNEL]={
    &dma_config0_State,
};

dma_state_t dmaState;