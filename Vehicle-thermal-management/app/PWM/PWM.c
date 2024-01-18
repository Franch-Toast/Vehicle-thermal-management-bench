/*
 * @Author: Franch-Toast
 * @Date: 2024-01-03 17:25:50
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-01-18 14:31:53
 * @Description: 
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood. 
 * Welcome to communicate with each other!
 */
/*
 * @Author: Franch-Toast
 * @Date: 2024-01-03 17:25:50
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-01-13 16:58:36
 * @Description: 
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood. 
 * Welcome to communicate with each other!
 */

#include "PWM.h"
#include "etmr_config.h"



etmr_state_t etmrState_PWM;


/* etmr sync configuration */
etmr_pwm_sync_t eTMR_PwmSyncConfig_1 = {
    .regSyncFreq = 0,
    .regSyncSel = REG_SYNC_WITH_MOD,
    .cntInitSyncSel = CNT_SYNC_WITH_REG,
    .maskOutputSyncSel = CHMASK_SYNC_WITH_REG,
    .regSyncTrigSrc = DISABLE_TRIGGER,
    .cntInitSyncTrigSrc = DISABLE_TRIGGER,
    .maskOutputSyncTrigSrc = DISABLE_TRIGGER,
    // .hwTrigRegLoadEnable = false,
};

etmr_user_config_t ETMR_PWM_USER_CONFIG_info[1]=
{
    {
        .etmrClockSource = eTMR_CLOCK_SOURCE_INTERNALCLK,  /*!< Select clock source for eTMR */
        .etmrPrescaler = 60,              /*!< eTMR clock prescaler */
        .debugMode = false,                       /*!< true  -- debug mode enabled, counter will stop in debug mode
                                            *   false -- debug mode disabled, counter will continue to run in debug mode */
        .syncMethod = &eTMR_PwmSyncConfig_1,          /*!< etmr sync method */
        .outputTrigConfig = NULL, /*!< etmr output trigger configure */
        .isTofIntEnabled = false,                 /*!< true: enable interrupt, false: disable interrupt */
    }
};



void PWM_init()
{
    eTMR_DRV_Deinit(eTMR_PWM_INST);
    eTMR_DRV_Init(eTMR_PWM_INST,ETMR_PWM_USER_CONFIG_info,&etmrState_PWM);
    eTMR_DRV_InitPwm(eTMR_PWM_INST,&ETMR_PWM_Config0);
}

// PWM使能，发送信号
void PWM_Start()
{
    eTMR_DRV_Enable(eTMR_PWM_INST);
}

// PWM失能，停止发送信号
void PWM_Stop(void)
{
    eTMR_DRV_Disable(eTMR_PWM_INST);
}

// PWM占空比调节
void PWM_Changedutycycle(float duty_cycle)
{
    eTMR_DRV_UpdatePwmChannel(eTMR_PWM_INST, ETMR_PWM_Config0IndChConfig[0].hwChannelId, (uint32_t)(duty_cycle * 0x8000), 0x0000U);
    eTMR_DRV_SetLdok(eTMR_PWM_INST);
    // OSIF_TimeDelay(10);
}


