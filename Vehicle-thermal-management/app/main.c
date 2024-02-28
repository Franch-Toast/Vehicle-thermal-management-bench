/* USER CODE BEGIN Header */
/* you can remove the copyright */

/*
 *  Copyright 2020-2023 Yuntu Microelectronics co.,ltd
 *  All rights reserved.
 *
 *  YUNTU Confidential. This software is owned or controlled by YUNTU and may only be
 *  used strictly in accordance with the applicable license terms. By expressly
 *  accepting such terms or by downloading, installing, activating and/or otherwise
 *  using the software, you are agreeing that you have read, and that you agree to
 *  comply with and are bound by, such license terms. If you do not agree to be
 *  bound by the applicable license terms, then you may not retain, install,
 *  activate or otherwise use the software. The production use license in
 *  Section 2.3 is expressly granted for this software.
 *
 * @file main.c
 * @brief
 *
 */

/* USER CODE END Header */
#include "sdk_project_config.h"
/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "UART.h"
#include "PWM.h"
#include "Input_capture.h"
#include "LIN.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Task.h"
#include "queue.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define QUEUE_LEN 4   // 消息队列中能存放多少个消息
#define QUEUE_SIZE 11 // 消息队列中的一个消息的长度，即一个数据帧结构体的长度

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */


/* 创建任务句柄 */
static TaskHandle_t AppTaskCreate_Handle = NULL;
/* 任务句柄，在Task.c中创建 */
extern TaskHandle_t Task_main_Handle;
extern TaskHandle_t Task_0x00_Handle;
extern TaskHandle_t Task_0x01_Handle;
extern TaskHandle_t Task_0x02_Handle;

/* 通信用句柄 */
extern QueueHandle_t Message_queue_main2Task0x01; // 主任务向Task01通信用消息队列句柄
extern SemaphoreHandle_t Get_upper_order_Handle;   // 串口接收二值信号量
extern EventGroupHandle_t HangTask01EventGroup; // 挂起Task01用事件组句柄

/* 台架状态结构体 */
Workbench_status_t Workbench_status;

/* USER CODE END PV */

/* Private function declare --------------------------------------------------*/
/* USER CODE BEGIN PFDC */

static void AppTaskCreate(void); /* 用于创建任务的任务 */
static void COM_init(void); // 用于初始化通信方式

/* USER CODE END PFDC */
static void Board_Init(void);

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */
    /* USER CODE END 1 */
    Board_Init();
    /* USER CODE BEGIN 2 */

    float scale = 0.99;
    char *test = "Thank God!";
    PRINTF("Fuck this world %d times!\n", 100);
    PRINTF("There is a %f chance that this code will not have a bug!\n", scale);
    PRINTF("%s\n", test);

    BaseType_t xReturn = pdPASS;                                  /* 定义一个创建信息返回值，默认为pdPASS */
    xReturn = xTaskCreate((TaskFunction_t)AppTaskCreate,          /* 任务入口函数 */
                          (const char *)"AppTaskCreate",          /* 任务名字 */
                          (uint16_t)512,                          /* 任务栈大小 */
                          (void *)NULL,                           /* 任务入口函数参数 */
                          (UBaseType_t)1,                         /* 任务的优先级 */
                          (TaskHandle_t *)&AppTaskCreate_Handle); /* 任务控制块指针 */

    /* 启动任务调度 */
    if (pdPASS == xReturn)
        vTaskStartScheduler(); /* 启动任务，开启调度 */
    else
        return -1;

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    while (1)
    {
        /* USER CODE END WHILE */
        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

static void Board_Init(void)
{
    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(CLOCK_MANAGER_ACTIVE_INDEX, CLOCK_MANAGER_POLICY_AGREEMENT);
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

    /* 通讯方式初始化 */
    COM_init();
    /* 串口功能初始化 */
    UART_init();
    /* 输入捕获初始化 */
    Input_capture_init();
    /* PWM功能初始化 */
    PWM_init();

}

/* USER CODE BEGIN 4 */
static void AppTaskCreate(void)
{
    BaseType_t xReturn = pdPASS; /* 定义一个创建信息返回值，默认为pdPASS */

    taskENTER_CRITICAL(); // 进入临界区

    /* 创建串口测试任务 */
    xReturn = xTaskCreate((TaskFunction_t)Task_main,          /* 任务入口函数 */
                          (const char *)"Task_main",          /* 任务名字 */
                          (uint16_t)512,                        /* 任务栈大小 */
                          (void *)NULL,                         /* 任务入口函数参数 */
                          (UBaseType_t)1,                       /* 任务的优先级 */
                          (TaskHandle_t *)&Task_main_Handle); /* 任务控制块指针 */

    xReturn = xTaskCreate((TaskFunction_t)Task_0x01,          /* 任务入口函数 */
                        (const char *)"Task_0x01",          /* 任务名字 */
                        (uint16_t)512,                          /* 任务栈大小 */
                        (void *)NULL,                           /* 任务入口函数参数 */
                        (UBaseType_t)1,                         /* 任务的优先级 */
                        (TaskHandle_t *)&Task_0x01_Handle); /* 任务控制块指针 */
    xReturn = xTaskCreate((TaskFunction_t)Task_0x02,          /* 任务入口函数 */
                        (const char *)"Task_0x02",          /* 任务名字 */
                        (uint16_t)512,                          /* 任务栈大小 */
                        (void *)NULL,                           /* 任务入口函数参数 */
                        (UBaseType_t)1,                         /* 任务的优先级 */
                        (TaskHandle_t *)&Task_0x02_Handle); /* 任务控制块指针 */
    if (pdPASS == xReturn)
        PRINTF("System start successfully !\r\n");

    vTaskDelete(AppTaskCreate_Handle); // 删除AppTaskCreate任务

    taskEXIT_CRITICAL(); // 退出临界区
}

static void COM_init(void)
{
    /* 创建二值信号量 */
    Get_upper_order_Handle = xSemaphoreCreateBinary();
    if (Get_upper_order_Handle != NULL)
        PRINTF("二值信号量创建成功！\n");

    /* 消息队列创建初始化 */
    Message_queue_main2Task0x01 = xQueueCreate(QUEUE_LEN, QUEUE_SIZE);

    /* 事件组创建初始化 */
    HangTask01EventGroup = xEventGroupCreate();
}

/* USER CODE END 4 */
