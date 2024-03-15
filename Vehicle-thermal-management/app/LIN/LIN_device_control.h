/*
 * @Author: Franch-Toast
 * @Date: 2024-02-29 20:19:10
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-03-04 16:41:04
 * @Description: 
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood. 
 * Welcome to communicate with each other!
 */
#ifndef _LIN_DEVICE_CONTROL_H_
#define _LIN_DEVICE_CONTROL_H_

#include "Task.h"
#include "LIN.h"
#include "string.h"
#include "FreeRTOS.h"
#include "semphr.h"


/************************************ 压缩机通讯 ************************************/

/* 更改压缩机的转速，变相等于开启压缩机 */
uint8_t Compressor_Set_Speed(uint8_t speed, uint8_t limit_power);
/* 关闭压缩机 */
uint8_t Compressor_Shutdown(void);
/* 获取压缩机状态 */
uint8_t Compressor_Get_info(void);

/************************************ 电子膨胀阀通讯 ************************************/

/* 更改电子膨胀阀的开度 */
uint8_t Expansion_valve_Set_Open(uint16_t open);

/* 获取电子膨胀阀状态 */
uint8_t Expansion_valve_Get_info(void);

/************************************ 三通阀通讯 ************************************/

/* 更改三通阀的比例开度 */
uint8_t Three_way_valve_Set_Open(uint8_t instance, uint8_t pos, uint8_t index);

/* 获取比例三通阀状态 */
uint8_t Three_way_valve_Get_info(uint8_t instance, uint8_t index);

/************************************ 四通阀通讯 ************************************/

/* 更改四通阀的开关状态 */
uint8_t Four_way_valve_Set_Open(uint8_t instance, uint8_t mode, uint8_t index); // mode 只有两种取值

/* 获取比例三通阀状态 */
uint8_t Four_way_valve_Get_info(uint8_t instance, uint8_t index);

/************************************ WPTC通讯 ************************************/

/* 开启WPTC加热，并设置温度 */
uint8_t WPTC_Set_Temperature(uint8_t instance, uint8_t temperature, uint8_t heat_power, uint8_t index);

/* 获取WPTC状态 */
uint8_t WPTC_Get_info(uint8_t instance, uint8_t index); // 输入的是第instance个WPTC，instance = 1 or 2

/* 关闭温度 */
uint8_t WPTC_Shutdown(uint8_t instance, uint8_t index);

#endif