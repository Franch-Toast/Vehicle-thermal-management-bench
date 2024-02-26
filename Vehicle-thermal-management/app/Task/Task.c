
#include "Task.h"
#include "FreeRTOS.h"
#include "event_group.h"

/* 任务句柄 */
static TaskHandle_t Task_0x00_Handle = NULL;

/* 定义事件标志组 */
static EventGroupHandle_t deleteTask01EventGroup;

extern linflexd_frame_t linMasterFrame;
extern Workbench_status_t Workbench_status;




/*
 * 任务0 ：
    1.停止台架的运行，任务中对已经开启的任务进行通信，关闭不断传输数据的任务
    2.关闭受控的部件，这里主要是压缩机和水泵
    3.向上位机发送响应，通知上位机关闭台架的结果
    4.删除自身
*/
void Task_0x00(void* parameter)
{
    /*这里是任务间通信的代码，代码暂无*/
    deleteTask01EventGroup = xEventGroupCreate();
    xEventGroupSetBits(deleteTask01EventGroup, BIT(0)); // 设置事件标志通知Task_0x01可以删除自身

    // EventBits_t bits = xEventGroupWaitBits(deleteTask01EventGroup, BIT(0), pdTRUE, pdFALSE, 0);

    /* 使水泵停转，调整占空比为10% */
    PWM_Changedutycycle(0.1);

    /* 使压缩机停转，根据通讯矩阵的内容写死通讯帧 */
    linMasterFrame.id = 0x30;
    linMasterFrame.data[2] = 0x00; // 第三个字节为 0 即可停机
    LIN_Master_Send_Frame();

    linMasterFrame.id = 0x12;
    vTaskDelay(100000);// 延时一段时间，让压缩机的转速降低
    LIN_Master_Receive_Frame();

    /* 向上位机发送响应，通知上位机关闭台架的结果 */

    if (linMasterFrame.data[1] == 0) // 压缩机转速降低至0
    {
        responce2upper[4] = {0x0A, 0x00, 0x01 ,0xFF};// 发送数据码为 0x01 ，表示关闭成功
        LINFlexD_UART_DRV_SendDataPolling(2, &responce2upper, 4);
    }
    else{
        responce2upper[4] = {0x0A, 0x00, 0x00 ,0xFF};// 发送数据码为 0x00 ，表示关闭失败
        LINFlexD_UART_DRV_SendDataPolling(2, &responce2upper, 4);
    }
    vTaskDelete(Task_0x00_Handle); // 删除自身
}

/*
 * 任务1 ：
    1.获取传输得到的各控制器预设数据（应该在主任务接收到的时候就直接完成）
    2.逐一对所有的控制器进行预设数据的填充
    3.运行台架
    4.开启Task_0x02，向上位机传输数据
    5.删除自身
*/
void Task_0x01(void *parameter)
{
    /*这里是任务间通信的代码，代码暂无*/

    EventBits_t bits = xEventGroupWaitBits(deleteTask2EventGroup, BIT(0), pdTRUE, pdFALSE, 0);
    if (bits & BIT(0))
    {
        vTaskDelete(NULL);// 删除自身
    }

    /* 使水泵停转，调整占空比为10% */
    PWM_Changedutycycle(0.1);

    /* 使压缩机停转，根据通讯矩阵的内容写死通讯帧 */
    linMasterFrame.id = 0x30;
    linMasterFrame.data[2] = 0x00; // 第三个字节为 0 即可停机
    LIN_Master_Send_Frame();

    linMasterFrame.id = 0x12;
    vTaskDelay(100000); // 延时一段时间，让压缩机的转速降低
    LIN_Master_Receive_Frame();

    /* 向上位机发送响应，通知上位机关闭台架的结果 */

    if (linMasterFrame.data[1] == 0) // 压缩机转速降低至0
    {
        uint8_t responce2upper[4] = {0x0A, 0x00, 0x01, 0xFF}; // 发送数据码为 0x01 ，表示关闭成功
    }
    else
    {
        uint8_t responce2upper[4] = {0x0A, 0x00, 0x00, 0xFF}; // 发送数据码为 0x00 ，表示关闭失败
    }
    LINFlexD_UART_DRV_SendDataPolling(2, &responce2upper, 4);
    vTaskDelete(AppTaskCreate_Handle); // 删除自身
}
