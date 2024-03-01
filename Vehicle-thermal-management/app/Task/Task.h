/*
 * @Author: Franch-Toast
 * @Date: 2024-02-25 22:17:21
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-03-01 12:19:35
 * @Description:
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood.
 * Welcome to communicate with each other!
 */
#ifndef _TASK_H_
#define _TASK_H_

#include "stdint.h"
#include "FreeRTOS.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "linflexd_lin_driver.h"
#include "linflexd_uart_driver.h"
#include "PWM.h"
#include "LIN.h"
#include "queue.h"
#include "semphr.h"
#include "UART.h"

/* 定义台架的状态结构体 */
typedef struct
{
    uint8_t three_way_valve_status;        // 三通阀状态
    uint8_t four_way_valve_status;         // 四通阀状态
    Compressor_status_t Compressor_status; // 压缩机状态
    // uint8_t water_pump_duty;         // 水泵占空比
} Workbench_status_t;

/* 压缩机状态结构体 */
typedef struct
{
    uint8_t compressor_status;       // 压缩机开启状态
    uint8_t compressor_speed;        // 压缩机转速
    uint8_t compressor_limit_power;  // 压缩机允许最大功率
    uint8_t temperature_basic_board; // 基板温度
    uint8_t temperature_IGBT;        // 基板温度
    uint16_t compressor_voltage;     // 压缩机供电电压
    uint16_t compressor_current;     // 压缩机电流
} Compressor_status_t;

/*
 * 主任务 ：
    1.在未收到信号量的时候阻塞
    2.收到信号量后，获取队列缓冲区中的数据
    3.对指令码进行解析，存放到数据帧结构体中
    4.使用消息队列将数据帧传递给对应的任务或置位标志位唤醒任务
    5.循环任务
*/
void Task_main(void *parameter);

/*
    * 任务0 ：
    1.等待被主任务唤醒
    2.关闭受控的部件，这里主要是压缩机和水泵
    3.等待一段时间后，让Task02继续通信，观察压缩机和水泵的情况
    4.确认压缩机停转后，对Task02进行通信，中断传输数据
    5.循环等待被唤醒
*/
void Task_0x00(void *parameter);

/*
 * 任务1 ：
    1.获取传输得到的各控制器预设数据，使用消息队列获取数据
    2.逐一对所有的控制器进行预设数据的填充
    3.运行台架（压缩机等）
    4.置位事件组，唤醒Task02
    5.循环阻塞等待下一次设置参数
*/
void Task_0x01(void *parameter);

/*
 * 任务2 ：
    1.等待被Task01唤醒
    2.向所有部件获取状态
    3.对数据进行组包，向上位机发送数据包
    4.循环，直到被Task00事件挂起
*/
void Task_0x02(void *parameter);

#endif
