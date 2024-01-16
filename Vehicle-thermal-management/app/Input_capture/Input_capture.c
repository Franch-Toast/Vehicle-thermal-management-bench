/*
 * @Author: Franch-Toast
 * @Date: 2024-01-04 21:29:55
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-01-16 19:35:45
 * @Description: 
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood. 
 * Welcome to communicate with each other!
 */

#include "Input_capture.h"
#include "UART/printf/printf.h"
#include "etmr_ic_driver.h"
#include "etmr_hw_access.h"

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
    // .syncMethod = NULL,
    .outputTrigConfig = NULL,
    .isTofIntEnabled = false,
};

// 输入捕获初始化
void Input_capture_init(void)
{
    eTMR_DRV_Deinit(eTMR_IC_INST);
    eTMR_DRV_Init(eTMR_IC_INST,&ETMR_IC_USER_CONFIG_info,&etmrState_IC);
    // eTMR_DRV_DeinitInputCapture(eTMR_IC_INST, &ETMR_IC_Config0);
    eTMR_DRV_InitInputCapture(eTMR_IC_INST, &ETMR_IC_Config0);
}

// 输入捕获使能
void Input_capture_Start(void)
{
    eTMR_DRV_Enable(eTMR_IC_INST);
    // eTMR_DRV_EnableChnInt(eTMR_IC_INST, ETMR_IC_Config0.inputChConfig[0].hwChannelId);
}

// 输入捕获失能
void Input_capture_Stop(void)
{
    eTMR_DRV_Disable(eTMR_IC_INST);
}

void Input_capture_get_pulse_frequncy(float *frequency)
{
    uint32_t pulse[2] = {0,0};
    // status_t status = STATUS_SUCCESS;
    while(1) // 如果没有两个边沿没有捕获完成就一直在这里等待捕获完成
    {
        eTMR_DRV_InputCaptureHandler(eTMR_IC_INST,0);// 主动调用函数，如果捕获完成会把捕获完成标志位置1，在该函数中计算了脉宽！
        if(eTMR_DRV_GetInputCaptureComplete(eTMR_IC_INST,0))// 检查捕获完成标志位是否置1
        {
            pulse[0] = eTMR_DRV_GetInputCapturePositivePulseCount(eTMR_IC_INST, 0);
            // 获取正脉宽
            pulse[1] = eTMR_DRV_GetInputCaptureNegativePulseCount(eTMR_IC_INST, 0);
            // 获取负脉宽
            eTMR_DRV_ClearInputCaptureComplete(eTMR_IC_INST,0);
            // 清楚标志位
            break;
        }
    }
    
    *frequency = eTMR_DRV_GetFrequency(eTMR_IC_INST) / (pulse[1] + pulse[0]);
    // 计算捕获的频率，并保存在外部传入的指针地址，给外部使用
    PRINTF("input capture frequncy is %f Hz.\n",*frequency);
    PRINTF("pulse[0] = %d , pulse[1] = %d \n",pulse[0],pulse[1]);
}