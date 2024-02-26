#include "Task.h"


/* 任务句柄 */
static TaskHandle_t Task_0x00_Handle = NULL;




extern linflexd_frame_t linMasterFrame;


/*
 * 任务0 ：
    1.停止台架的运行，任务中对已经开启的任务进行通信，关闭不断传输数据的任务
    2.关闭受控的部件，这里主要是压缩机和水泵
    3.向上位机发送响应，通知上位机关闭台架的结果
*/
void Task_0x00(void* parameter)
{
    /*这里是任务间通信的代码，代码暂无*/



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

    if(linMasterFrame.data[1] == 0) // 压缩机转速降低至0
    {
        uint8_t responce2upper[4] = {0x0A, 0x00, 0x01 ,0x0D};// 发送数据码为 0x01 ，表示关闭成功
    }
    else{
        uint8_t responce2upper[4] = {0x0A, 0x00, 0x00 ,0x0D};// 发送数据码为 0x00 ，表示关闭失败
    }
    LINFlexD_UART_DRV_SendDataPolling(2, &responce2upper, 4);
    vTaskDelete(AppTaskCreate_Handle); //删除自身
}


