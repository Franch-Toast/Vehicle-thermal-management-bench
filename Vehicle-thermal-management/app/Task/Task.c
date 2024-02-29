
#include "Task.h"

/* 任务句柄 */
TaskHandle_t Task_main_Handle = NULL;
TaskHandle_t Task_0x00_Handle = NULL;
TaskHandle_t Task_0x01_Handle = NULL;
TaskHandle_t Task_0x02_Handle = NULL;

/* 上位机指令传输信号量句柄 */
SemaphoreHandle_t Get_upper_order_Handle = NULL;

/* 主任务向 Task01 传输数据使用的消息队列句柄 */
QueueHandle_t Message_queue_main2Task0x01 = NULL;

/* 定义事件标志组 */
EventGroupHandle_t HangTask01EventGroup = NULL;

/* 定义互斥信号量，用于保护LIN传输帧 */
SemaphoreHandle_t MuxSem_Handle = NULL;



/* 声明LIN通讯帧与台架状态结构体 */
extern linflexd_frame_t linMasterFrame;
extern Workbench_status_t Workbench_status;

/* 串口发送数据帧结构体，大小为 11 Bytes */
extern Serial_data_frame_t serial_data_frame;

/*
 * 主任务 ：
    1.在未收到信号量的时候阻塞
    2.收到信号量后，获取队列缓冲区中的数据
    3.对指令码进行解析，存放到数据帧结构体中
    4.使用消息队列将数据帧传递给对应的任务或置位标志位唤醒任务
    5.循环任务
*/
void Task_main(void *parameter)
{
    BaseType_t xReturn = pdPASS;

    while (1)
    {
        xReturn = xSemaphoreTake(Get_upper_order_Handle, portMAX_DELAY);

        if (xReturn == pdPASS) // 说明不为空
        {
            if (RingBuff_Read_frame() > 0)
            {
                if (serial_data_frame.data[0] == 0x0A && serial_data_frame.data[serial_data_frame.data_length - 1] == 0xFF) // 满足帧定义
                {
                    if (serial_data_frame.data[1] == 0x01) // 唤醒Task01
                    {
                        // LINFlexD_UART_DRV_SendDataPolling(2, serial_data_frame.data, serial_data_frame.data_length);
                        xQueueSend(Message_queue_main2Task0x01, &serial_data_frame, 1000);
                    }
                    else if (serial_data_frame.data[1] == 0x00) // 唤醒Task00
                    {
                        // xEventGroupClearBits(HangTask01EventGroup,0x01); // bit0被清除
                        xEventGroupSetBits(HangTask01EventGroup, 0x02); // bit1 置1
                    }
                }
            }
        }
    }
}

/*
    * 任务0 ：
    1.等待被主任务唤醒
    2.关闭受控的部件，这里主要是压缩机和水泵
    3.等待一段时间后，让Task02继续通信，观察压缩机和水泵的情况
    4.确认压缩机停转后，对Task02进行通信，中断传输数据
    5.循环等待被唤醒
*/
void Task_0x00(void *parameter)
{
    while (1)
    {
        /* 等待主任务唤醒 */
        xEventGroupWaitBits(HangTask01EventGroup, 0x02, pdTRUE, pdFALSE, portMAX_DELAY); // 仅一位标志位，无需获取返回值，清除事件标志位

        // /* 使水泵停转，调整占空比为10% */
        // PWM_Changedutycycle(0.1);

        // /* 使压缩机停转，根据通讯矩阵的内容写死通讯帧 */
        // linMasterFrame.id = 0x30;
        // linMasterFrame.data[2] = 0x00; // 第三个字节为 0 即可停机
        // LIN_Master_Send_Frame();

        // /* 为确保停机，向压缩机读取转速数据 */
        // linMasterFrame.id = 0x12;
        // vTaskDelay(100000);// 延时一段时间，让压缩机的转速降低
        // LIN_Master_Receive_Frame();

        // /* 向上位机发送响应，通知上位机关闭台架的结果 */

        // if (linMasterFrame.data[1] == 0) // 压缩机转速降低至0
        // {
        //     uint8_t responce2upper[4] = {0x0A, 0x00, 0x01 ,0xFF};// 发送数据码为 0x01 ，表示关闭成功
        //     LINFlexD_UART_DRV_SendDataPolling(2, responce2upper, 4);
        // }
        // else{
        //     uint8_t responce2upper[4] = {0x0A, 0x00, 0x00, 0xFF}; // 发送数据码为 0x00 ，表示关闭失败
        //     LINFlexD_UART_DRV_SendDataPolling(2, responce2upper, 4);
        // }

        uint8_t responce2upper[4] = {0x0A, 0x00, 0x00, 0xFF}; // 发送数据码为 0x00 ，表示关闭失败
        LINFlexD_UART_DRV_SendDataPolling(2, responce2upper, 4);

        /* 等待一段时间，观察数据是否递减 */
        // vTaskDelay(2000);

        /* 清除已经置位的事件标志通知Task_0x01挂起自身，停止向上位机发送 */
        xEventGroupClearBits(HangTask01EventGroup, 0x01); // bit0被清除
    }
}

/*
 * 任务1 ：
    1.获取传输得到的各控制器预设数据，使用消息队列获取数据
    2.逐一对所有的控制器进行预设数据的填充
    3.运行台架（压缩机等）
    4.置位事件组，唤醒Task02
    5.循环阻塞等待下一次设置参数
*/
void Task_0x01(void *parameter)
{
    BaseType_t xReturn = pdTRUE;
    Serial_data_frame_t DataFrame;

    while (1)
    {
        xReturn = xQueueReceive(Message_queue_main2Task0x01, &DataFrame, portMAX_DELAY);

        if (xReturn != pdTRUE)
            continue;

        LINFlexD_UART_DRV_SendDataPolling(2, DataFrame.data, DataFrame.data_length);

        /* 置位事件标志唤醒Task_0x02，开始向上位机发送台架状态 */
        xEventGroupSetBits(HangTask01EventGroup, 0x01); // bit0 置1
    }

    // /*这里是任务间通信的代码，代码暂无*/
    // EventBits_t bits = xEventGroupWaitBits(deleteTask01EventGroup, 0x01, pdTRUE, pdFALSE, 0);
    // if (bits & 0x01)
    // {
    //     vTaskDelete(NULL);// 删除自身
    // }

    // /* 使水泵停转，调整占空比为10% */
    // PWM_Changedutycycle(0.1);

    // /* 使压缩机停转，根据通讯矩阵的内容写死通讯帧 */
    // linMasterFrame.id = 0x30;
    // linMasterFrame.data[2] = 0x00; // 第三个字节为 0 即可停机
    // LIN_Master_Send_Frame();

    // linMasterFrame.id = 0x12;
    // vTaskDelay(100000); // 延时一段时间，让压缩机的转速降低
    // LIN_Master_Receive_Frame();

    // /* 向上位机发送响应，通知上位机关闭台架的结果 */
}

/*
 * 任务2 ：
    1.等待被Task01唤醒
    2.向所有部件获取状态
    3.对数据进行组包，向上位机发送数据包
    4.循环，直到被Task00事件挂起
*/
void Task_0x02(void *parameter)
{
    while (1)
    {
        /* Task01中会置位事件，在获取事件标记后不会清除事件标记，故而只需要等待Task00清除事件标记即可 */
        xEventGroupWaitBits(HangTask01EventGroup, 0x01, pdFALSE, pdFALSE, portMAX_DELAY); // 由于只有一个事件，所以不需要获取返回值来匹配

        uint8_t responce2upper[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10};
        LINFlexD_UART_DRV_SendDataPolling(2, responce2upper, 10);

        /* 等待一段时间后再继续传输，防止数据传输过快，疯狂占用 */
        vTaskDelay(10);
    }
}