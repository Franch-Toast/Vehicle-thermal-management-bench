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
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

 /* 创建任务句柄 */
static TaskHandle_t AppTaskCreate_Handle = NULL;
/* LED1任务句柄 */
static TaskHandle_t PWM_Task_Handle = NULL;
/* LED2任务句柄 */
static TaskHandle_t Input_capture_Task_Handle = NULL;


/* USER CODE END PV */

/* Private function declare --------------------------------------------------*/
/* USER CODE BEGIN PFDC */

static void AppTaskCreate(void);/* 用于创建任务 */

static void PWM_Task(void* pvParameters);/* LED1_Task任务实现 */
static void Input_capture_Task(void* pvParameters);/* LED2_Task任务实现 */

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
    char test[10] = "Thank God!";
    PRINTF("Fuck this world %d times!\n",100);                                                                     
    PRINTF("There is a %f chance that this code will not have a bug!\n",scale);
    PRINTF("%s\n",test);



    
    BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
    xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* 任务入口函数 */
                    (const char*    )"AppTaskCreate",/* 任务名字 */
                    (uint16_t       )512,  /* 任务栈大小 */
                    (void*          )NULL,/* 任务入口函数参数 */
                    (UBaseType_t    )1, /* 任务的优先级 */
                    (TaskHandle_t*  )&AppTaskCreate_Handle);/* 任务控制块指针 */ 

    /* 启动任务调度 */           
    if(pdPASS == xReturn)
        vTaskStartScheduler();   /* 启动任务，开启调度 */
    else
        return -1;  



    // LIN_MASTER_init();
    // LIN_Master_Send_Frame();


    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    /* 正常不会执行到这里 */  
    while (1)
    {
        /* USER CODE END WHILE */
        /* USER CODE BEGIN 3 */
        // LIN_Master_Receive_Frame();
    }
    /* USER CODE END 3 */
}

static void Board_Init(void)
{
    CLOCK_SYS_Init(g_clockManConfigsArr,CLOCK_MANAGER_CONFIG_CNT,g_clockManCallbacksArr,CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(CLOCK_MANAGER_ACTIVE_INDEX,CLOCK_MANAGER_POLICY_AGREEMENT);
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0,g_pin_mux_InitConfigArr0);
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
    BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
    
    taskENTER_CRITICAL();           //进入临界区
    
    /* 创建LED_Task任务 */
    xReturn = xTaskCreate((TaskFunction_t )PWM_Task, /* 任务入口函数 */
                            (const char*    )"PWM_Task",/* 任务名字 */
                            (uint16_t       )512,   /* 任务栈大小 */
                            (void*          )NULL,	/* 任务入口函数参数 */
                            (UBaseType_t    )2,	    /* 任务的优先级 */
                            (TaskHandle_t*  )&PWM_Task_Handle);/* 任务控制块指针 */
    if(pdPASS == xReturn)
        PRINTF("Create PWM_Task successfully !\r\n");
    
        /* 创建LED_Task任务 */
    xReturn = xTaskCreate((TaskFunction_t )Input_capture_Task, /* 任务入口函数 */
                            (const char*    )"Input_capture_Task",/* 任务名字 */
                            (uint16_t       )512,   /* 任务栈大小 */
                            (void*          )NULL,	/* 任务入口函数参数 */
                            (UBaseType_t    )2,	    /* 任务的优先级 */
                            (TaskHandle_t*  )&Input_capture_Task_Handle);/* 任务控制块指针 */
    if(pdPASS == xReturn)
        PRINTF("Create Input_capture_Task successfully!\r\n");
    
    vTaskDelete(AppTaskCreate_Handle); //删除AppTaskCreate任务
    
    taskEXIT_CRITICAL();            //退出临界区
}

static void PWM_Task(void* parameter)
{	
    PRINTF("Come into PWM_Task successfully !\r\n");
    PWM_Start();

    while (1)
    {
        vTaskDelay(5000);   /* 延时500个tick */
        PWM_Changedutycycle(0.8);// 调整占空比为80%
        PRINTF("PWM duty cycle is 80\%.\r\n");

        PWM_Changedutycycle(0.5);// 调整占空比为50%
        vTaskDelay(5000);   /* 延时500个tick */		 		
        PRINTF("PWM duty cycle is 50\%.\r\n");
    }
}

static void Input_capture_Task(void* parameter)
{	
    
    PRINTF("Come into Input_capture_Task successfully !\r\n");
    // 输入捕获使能
    Input_capture_Start();
    float frequency = 0;
    
    while (1)
    {
        vTaskDelay(500);   /* 延时500个tick */
        Input_capture_get_pulse_frequncy(&frequency);// 获取输入捕获的脉冲频率
        PRINTF("frequency is %f Hz!\n",frequency);
    }
}




/* USER CODE END 4 */
