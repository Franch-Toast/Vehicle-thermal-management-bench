#ifndef __INPUT_CAPTURE_H__
#define __INPUT_CAPTURE_H__


#include "etmr_config.h"

#define eTMR_IC_INST           (1U)

// 输入捕获初始化
void Input_capture_init(void);

// 输入捕获使能
void Input_capture_Start(void);

// 输入捕获失能
void Input_capture_Stop(void);

// 获取输入捕获的脉冲频率
void Input_capture_get_pulse_frequncy(float *frequency);



#endif