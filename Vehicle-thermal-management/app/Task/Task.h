/*
 * @Author: Franch-Toast
 * @Date: 2024-02-25 22:17:21
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-02-25 22:17:57
 * @Description: 
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood. 
 * Welcome to communicate with each other!
 */
#ifndef _TASK_H_
#define _TASK_H_

#include "stdint.h"

/* 定义串口传输帧结构体 */
typedef struct 
{
    uint8_t data_length;// 数据的长度
    uint8_t data[10]; // 数据内容，这里暂时给10的大小
}serial_data_frame_t;




/*
 * 任务0 ：
    1.停止台架的运行，任务中对已经开启的任务进行通信，关闭不断传输数据的任务
    2.关闭受控的部件，这里主要是压缩机和水泵
    3.向上位机发送响应，通知上位机关闭台架的结果
*/
void Task_0x00(void* parameter);


#endif
