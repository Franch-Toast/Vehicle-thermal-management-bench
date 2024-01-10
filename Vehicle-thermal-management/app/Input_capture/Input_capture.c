/*
 * @Author: Franch-Toast
 * @Date: 2024-01-04 21:29:55
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-01-06 22:33:22
 * @Description: 
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood. 
 * Welcome to communicate with each other!
 */

#include "Input_capture.h"
#include "UART/printf/printf.h"
#include "etmr_ic_driver.h"

etmr_state_t etmrState_IC;

#define IC_CLK_PRESCALER    60 // 暂定分频系数为60
// #define IC_CLK_FREQUENCY    120000000U //快速总线时钟为120 MHz               

/* etmr sync configuration */
etmr_pwm_sync_t eTMR_ICSyncConfig_1 = {
    .regSyncFreq = 0,
    .regSyncSel = REG_SYNC_WITH_MOD,
    .cntInitSyncSel = CNT_SYNC_WITH_REG,
    .maskOutputSyncSel = CHMASK_SYNC_WITH_REG,
    .regSyncTrigSrc = DISABLE_TRIGGER,
    .cntInitSyncTrigSrc = DISABLE_TRIGGER,
    .maskOutputSyncTrigSrc = DISABLE_TRIGGER,
    // .hwTrigRegLoadEnable = false,
};

etmr_user_config_t ETMR_IC_USER_CONFIG_info={
    .etmrClockSource = eTMR_CLOCK_SOURCE_INTERNALCLK,
    .etmrPrescaler = IC_CLK_PRESCALER, 
    .debugMode = false,
    .syncMethod = &eTMR_ICSyncConfig_1,
    .outputTrigConfig = NULL,
    .isTofIntEnabled = false,
};

// 输入捕获初始化
void Input_capture_init(void)
{
    eTMR_DRV_Deinit(eTMR_IC_INST);
    eTMR_DRV_Init(eTMR_IC_INST,&ETMR_IC_USER_CONFIG_info,&etmrState_IC);

    eTMR_DRV_InitInputCapture(eTMR_IC_INST, &ETMR_IC_Config0);
}

// 输入捕获使能
void Input_capture_Start(void)
{
    eTMR_DRV_Enable(eTMR_IC_INST);
}

// 输入捕获失能
void Input_capture_Stop(void)
{
    eTMR_DRV_Disable(eTMR_IC_INST);
}

void Input_capture_get_pulse_frequncy(float *frequency)
{
    uint8_t cnt = 0;
    uint32_t pulse[2];
    while((2-cnt) && eTMR_DRV_GetInputCaptureComplete(eTMR_IC_INST,4))
    {
        pulse[cnt] = eTMR_DRV_GetInputCapturePositivePulseCount(eTMR_IC_INST, 4);
        eTMR_DRV_ClearInputCaptureComplete(eTMR_IC_INST,4);
        cnt++;
    }
    *frequency = eTMR_DRV_GetFrequency(eTMR_IC_INST) / (pulse[1] - pulse[0]);
    PRINTF("input capture frequncy is %f Hz",*frequency);
    // eTMR_DRV_ClearInputCaptureCount(eTMR_IC_INST);
}
