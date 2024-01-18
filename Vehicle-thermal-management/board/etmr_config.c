
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
 * @file etmr_config.c
 * @brief 
 * 
 */


#include <stddef.h>
#include "etmr_config.h"

/*
 * Common
*/

/*
 * MC
*/


/*
 * PWM
*/

etmr_pwm_ch_param_t ETMR_PWM_Config0IndChConfig[1]={
    {
        .hwChannelId=6,
        .polarity=eTMR_POLARITY_NORMAL,
        .pwmSrcInvert=false,
        .align=eTMR_PWM_RIGHT_EDGE_ALIGN,
        .channelInitVal=0,
        .typeOfUpdate=eTMR_PWM_UPDATE_IN_DUTY_CYCLE,
        .dutyCycle=16384,
        .offset=0,
        .enableSecondChannelOutput=false,
        .secondChannelPolarity=eTMR_POLARITY_NORMAL,
        .enableDoubleSwitch=false,
        .evenDeadTime=0,
        .oddDeadTime=0,
    },
};

etmr_fault_param_t ETMR_PWM_Config0FaultConfig={
    .pwmFaultInterrupt=false,
    .faultFilterSampleCounter=0,
    .faultFilterSamplePeriod=0,
    .faultInputStrentch=0,
    .pwmRecoveryOpportunity=eTMR_FAULT_PWM_RECOVERY_DISABLED,
    .pwmAutoRecoveryMode=eTMR_MANUAL_CLEAR_FAULT_FLAG_THEN_AUTO_RECOVERY,
    .faultMode=eTMR_FAULT_WITH_CLK,
    .etmrFaultChannelParam=
    {
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
        {
            .faultChannelEnabled=false,
            .faultInputPolarity=eTMR_FAULT_SIGNAL_HIGH,
        },
    },
    .safeState={
        eTMR_LOW_STATE,
        eTMR_LOW_STATE,
        eTMR_LOW_STATE,
        eTMR_LOW_STATE,
    }
};


etmr_pwm_param_t ETMR_PWM_Config0={
    .nNumPwmChannels=1,
    .mode=eTMR_PWM_MODE,
    .uFrequencyHZ=100,
    .counterInitValFromInitReg=true,
    .cntVal=0,
    .pwmChannelConfig=ETMR_PWM_Config0IndChConfig,
    .faultConfig=&ETMR_PWM_Config0FaultConfig,
};


/*
 * IC
*/




etmr_ic_ch_param_t ETMR_IC_Config0InputCh[1]={
    {
        .hwChannelId=0,
        .edge=eTMR_DUAL_EDGES,
        .measurementType=eTMR_PERIOD_MEASUREMENT,
        .filterSampleCounter=0,
        .filterSamplePeriod=0,
        .interruptEnable=false,
        .dmaEnable=true,
        .enableNotification=false,
        .channelsCallbacks=NULL,
        .channelsCallbacksParams=NULL,
    },
};

etmr_ic_param_t ETMR_IC_Config0={
    .numChannels=1,
    .countValue=65535,
    .inputChConfig=ETMR_IC_Config0InputCh,
};


/*
 * OC
*/


/*
 * QD
*/


