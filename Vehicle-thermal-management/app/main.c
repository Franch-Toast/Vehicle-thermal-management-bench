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
#include "./UART/UART.h"
#include "./PWM/PWM.h"
#include "./Input_capture/Input_capture.h"
#include "LIN.h"
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


/* USER CODE END PV */

/* Private function declare --------------------------------------------------*/
/* USER CODE BEGIN PFDC */
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
    // uint8_t txBuff[TXBuff_LENGTH] = "Fuck this world.",rxBuff[RXBuff_LENGTH];
    // uint8_t rxBuff[100];
    UART_init();
    

    float scale = 0.99;
    char test[10] = "Thank God!";
    PRINTF("Fuck this world %d times!\n",100);
    PRINTF("There is a %f chance that this code will not have a bug!\n",scale);
    PRINTF("%s\n",test);



    float frequency = 0;
    // PRINTF("frequency is %f Hz!\n",frequency);
    // 输入捕获初始化
    // Input_capture_init();

    // // 输入捕获使能
    // Input_capture_Start();

    PWM_init();
    PWM_Start();
    // PWM_Changedutycycle(0.8);// 调整占空比为80%
    // 获取输入捕获的脉冲频率
    // Input_capture_get_pulse_frequncy(&frequency);

    LIN_MASTER_init();
    LIN_Master_Send_Frame();


    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */
        /* USER CODE BEGIN 3 */
        
        LIN_Master_Receive_Frame();
    }
    /* USER CODE END 3 */
}

static void Board_Init(void)
{
    CLOCK_SYS_Init(g_clockManConfigsArr,CLOCK_MANAGER_CONFIG_CNT,g_clockManCallbacksArr,CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(CLOCK_MANAGER_ACTIVE_INDEX,CLOCK_MANAGER_POLICY_AGREEMENT);
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0,g_pin_mux_InitConfigArr0);
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */
