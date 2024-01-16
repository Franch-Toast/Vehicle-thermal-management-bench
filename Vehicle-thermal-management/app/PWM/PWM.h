/*
 * @Author: Franch-Toast
 * @Date: 2024-01-03 17:25:45
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-01-15 20:28:17
 * @Description: 
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood. 
 * Welcome to communicate with each other!
 */
#ifndef __PWM_H__
#define __PWM_H__

#include "etmr_config.h"

#define eTMR_PWM_INST           (1U)

// PWM 初始化
void PWM_init(void);

// PWM使能，发送信号
void PWM_Start(void);

// PWM失能，停止发送信号
void PWM_Stop(void);

// PWM占空比调节
void PWM_Changedutycycle(float duty_cycle);




#endif