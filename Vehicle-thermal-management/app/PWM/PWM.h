#ifndef __PWM_H__
#define __PWM_H__

#include "etmr_config.h"

#define eTMR_INST           (0U)

// PWM 初始化
void PWM_init(void);

// PWM使能，发送信号
void PWM_Start(void);

// PWM失能，停止发送信号
void PWM_Stop(void);

// PWM占空比调节
void PWM_Changedutycycle(float duty_cycle);




#endif