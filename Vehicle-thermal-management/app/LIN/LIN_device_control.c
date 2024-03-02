/*
 * @Author: Franch-Toast
 * @Date: 2024-02-29 20:18:57
 * @email: random996@163.com
 * @github: https://github.com/Franch-Toast
 * @LastEditTime: 2024-03-02 19:13:39
 * @Description:
 * Shit Code Manufacturing Machine, a low-level bug production expert myself.
 * The code is terrible but can be barely understood.
 * Welcome to communicate with each other!
 */
#include "LIN_device_control.h"

/* 外部全局变量 */
extern linflexd_frame_t linMasterFrame;
extern SemaphoreHandle_t MuxSem_Handle;
extern Workbench_status_t Workbench_status; // 台架的状态

/************************************ 压缩机通讯 ************************************/

/* 更改压缩机的转速，变相等于开启压缩机 */
uint8_t Compressor_Set_Speed(uint16_t speed, uint16_t limit_power)
{
    status_t status = 0;
    xSemaphoreTake(MuxSem_Handle, portMAX_DELAY); // 加锁

    linMasterFrame.id = 0x30;
    linMasterFrame.dataLength = 7;                        // 七个字节
    memset(linMasterFrame.data, 0, 8);                    // 8个字节内容全部清0
    linMasterFrame.data[0] = (uint8_t)(limit_power / 40); // 第一个字节为压缩机允许功率，放大因数为40
    linMasterFrame.data[1] = (uint8_t)(speed / 50);       // 第二个字节为压缩机转速，放大因数为50
    linMasterFrame.data[2] = 0x01;                        // 第三个字节低两位压缩机允许运行

    status = LIN_Master_Send_Frame(); // 发送帧

    if (status != 0) // 如果发送失败了，则
    {
    }

    xSemaphoreGive(MuxSem_Handle); // 解锁
    return status;
}

/* 关闭压缩机 */
uint8_t Compressor_Shutdown(void)
{
    status_t status = 0;
    xSemaphoreTake(MuxSem_Handle, portMAX_DELAY); // 加锁

    linMasterFrame.id = 0x30;
    linMasterFrame.dataLength = 7;     // 七个字节
    memset(linMasterFrame.data, 0, 8); // 8个字节内容全部清0
    linMasterFrame.data[2] = 0x00;     // 第三个字节低两位压缩机停止运行
    status = LIN_Master_Send_Frame();  // 发送帧

    if (status != 0) // 如果发送失败了，则
    {
    }

    xSemaphoreGive(MuxSem_Handle); // 解锁
    return status;
}

/* 获取压缩机状态 */
uint8_t Compressor_Get_info(void)
{
    status_t status = 0;
    xSemaphoreTake(MuxSem_Handle, portMAX_DELAY); // 加锁

    linMasterFrame.id = 0x12;          // 帧ID为0x12
    linMasterFrame.dataLength = 8;     // 八个字节
    memset(linMasterFrame.data, 0, 8); // 8个字节内容全部清0

    status = LIN_Master_Receive_Frame(); // 接收帧

    if (status != 0) // 如果发送失败了，则
    {
    }

    /* 对接收数据进行解析 */

    Workbench_status.Compressor_status.compressor_speed = linMasterFrame.data[1];                                                // 转速：rpm
    Workbench_status.Compressor_status.temperature_basic_board = linMasterFrame.data[2];                                         // 基板温度：℃
    Workbench_status.Compressor_status.temperature_IGBT = linMasterFrame.data[3];                                                // IGBT温度：℃
    Workbench_status.Compressor_status.compressor_current = ((linMasterFrame.data[4])) | ((linMasterFrame.data[4] & 0x0F) << 8); // 电流：A
    Workbench_status.Compressor_status.compressor_voltage = linMasterFrame.data[6] | ((linMasterFrame.data[7] & 0x03) << 8);     // 电压：V
    Workbench_status.Compressor_status.compressor_status = linMasterFrame.data[7] & 0x38;                                        // 压缩机状态

    xSemaphoreGive(MuxSem_Handle); // 解锁
    return status;
}

/************************************ 电子膨胀阀通讯 ************************************/

/* 更改电子膨胀阀的开度 */
uint8_t Expansion_valve_Set_Open(uint16_t open)
{
    status_t status = 0;
    xSemaphoreTake(MuxSem_Handle, portMAX_DELAY); // 加锁

    linMasterFrame.id = 0x19;
    linMasterFrame.dataLength = 8;     // 8个字节
    memset(linMasterFrame.data, 0, 8); // 8个字节内容全部清0

    linMasterFrame.data[0] = (uint8_t)open; // 第一二个字节为请求位置，两个字节的宽度，但是大小仅允许【0，480】
    linMasterFrame.data[1] = (uint8_t)(open >> 4);

    linMasterFrame.data[2] = 0x01;    // 第三个字节bit0允许使能膨胀阀
    linMasterFrame.data[3] = 0x00;    // 第四个字节3个bit允许是否初始化
    status = LIN_Master_Send_Frame(); // 发送帧

    if (status != 0) // 如果发送失败了，则
    {
    }

    xSemaphoreGive(MuxSem_Handle); // 解锁
    return status;
}

/* 获取电子膨胀阀状态 */
uint8_t Compressor_Get_info(void)
{
    status_t status = 0;
    xSemaphoreTake(MuxSem_Handle, portMAX_DELAY); // 加锁

    linMasterFrame.id = 0x29;          // 帧ID为0x29
    linMasterFrame.dataLength = 8;     // 八个字节
    memset(linMasterFrame.data, 0, 8); // 8个字节内容全部清0

    status = LIN_Master_Receive_Frame(); // 接收帧

    if (status != 0) // 如果发送失败了，则
    {
    }

    /* 对接收数据进行解析 */

    Workbench_status.EXV_status.EXV_CurrentPosition = linMasterFrame.data[2] | (linMasterFrame.data[3] << 8);          // EXV膨胀阀开度:当前位置
    Workbench_status.EXV_status.EXV_status = ((linMasterFrame.data[0] & 0x0C) >> 2) | (linMasterFrame.data[0] & 0x10); // EXV的初始化状态和运行状态，分别为前4bit和后4bit

    xSemaphoreGive(MuxSem_Handle); // 解锁
    return status;
}

/************************************ 三通阀通讯 ************************************/

/* 更改三通阀的比例开度 */
uint8_t Three_way_valve_Set_Open(uint8_t pos)
{
    status_t status = 0;
    xSemaphoreTake(MuxSem_Handle, portMAX_DELAY); // 加锁

    linMasterFrame.id = 0x35;
    linMasterFrame.dataLength = 8;     // 8个字节
    memset(linMasterFrame.data, 0, 8); // 8个字节内容全部清0

    linMasterFrame.data[0] = 0x01; // 第一个字节使能移动
    linMasterFrame.data[1] = pos;   // 第二个字节设定比例，实际值 = pos * 0.4; 故而 FA -> 100


    status = LIN_Master_Send_Frame(); // 发送帧

    if (status != 0) // 如果发送失败了，则
    {
    }

    xSemaphoreGive(MuxSem_Handle); // 解锁
    return status;
}

/* 获取比例三通阀状态 */
uint8_t Three_way_valve_Get_info(void)
{
    status_t status = 0;
    xSemaphoreTake(MuxSem_Handle, portMAX_DELAY); // 加锁

    linMasterFrame.id = 0x32;          // 帧ID为0x32
    linMasterFrame.dataLength = 8;     // 八个字节
    memset(linMasterFrame.data, 0, 8); // 8个字节内容全部清0

    status = LIN_Master_Receive_Frame(); // 接收帧

    if (status != 0) // 如果发送失败了，则
    {
    }

    /* 对接收数据进行解析 */

    Workbench_status.EXV_status.EXV_CurrentPosition = linMasterFrame.data[2] | (linMasterFrame.data[3] << 8);          // EXV膨胀阀开度:当前位置
    Workbench_status.EXV_status.EXV_status = ((linMasterFrame.data[0] & 0x0C) >> 2) | (linMasterFrame.data[0] & 0x10); // EXV的初始化状态和运行状态，分别为前4bit和后4bit

    xSemaphoreGive(MuxSem_Handle); // 解锁
    return status;
}




/************************************ 四通阀通讯 ************************************/

/************************************ WPTC通讯 ************************************/

/* 开启WPTC加热，并设置温度 */
uint8_t WPTC_Set_Temperature(uint8_t instance, uint8_t temperature, uint8_t heat_power)
{
    status_t status = 0;
    xSemaphoreTake(MuxSem_Handle, portMAX_DELAY); // 加锁

    linMasterFrame.id = 0x15;
    linMasterFrame.dataLength = 4;     // 四个字节
    memset(linMasterFrame.data, 0, 8); // 8个字节内容全部清0

    linMasterFrame.data[0] = heat_power;  // 注意请求加热功率heat_power范围为[0,127]
    linMasterFrame.data[1] = 0x01;        // PTC使能
    linMasterFrame.data[2] = temperature; // 注意temperature范围为[0,127]
    // 重置请求、紧急切断、放电请求均为不要求

    status = LIN_Master_Send_Frame(); // 发送帧

    if (status != 0) // 如果发送失败了，则
    {
    }

    xSemaphoreGive(MuxSem_Handle); // 解锁
    return status;
}

/* 获取WPTC状态 */
uint8_t WPTC_Get_info(uint8_t instance)
{
    status_t status = 0;
    xSemaphoreTake(MuxSem_Handle, portMAX_DELAY); // 加锁

    linMasterFrame.id = 0x16;          // 帧ID为0x16
    linMasterFrame.dataLength = 8;     // 八个字节
    memset(linMasterFrame.data, 0, 8); // 8个字节内容全部清0

    status = LIN_Master_Receive_Frame(); // 接收帧

    if (status != 0) // 如果发送失败了，则
    {
    }

    /* 对接收数据进行解析 */

    memcpy(&Workbench_status.WPTC_status[instance], linMasterFrame.data, 4);           // 结构体的成员地址与通讯矩阵中的一致，直接memcpy
    Workbench_status.WPTC_status[instance].PTC_status = linMasterFrame.data[4] & 0x07; // PTC工作状态，3bit

    xSemaphoreGive(MuxSem_Handle); // 解锁
    return status;
}
