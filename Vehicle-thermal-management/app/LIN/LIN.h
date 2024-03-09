#ifndef __LIN_H__
#define __LIN_H__

#include "stdint.h"
#include "linflexd_lin_config.h"

#define LIN0_Master (0)
#define LIN1_Master (1)
#define LINMaserRecvDone (1)
#define LINMasterSendDone (2)
#define LINMasterError (3)

/*
currentEvent = 1 means master recv done,
currentEvent = 2 means master send done,
currentEvent = 3 means error happens
*/
extern volatile uint8_t currentEvent;

// LIN主机 初始化
void LIN_MASTER_init(void);

// LIN主机 发送帧
status_t LIN_Master_Send_Frame(uint32_t instance);

// LIN主机 接收帧
status_t LIN_Master_Receive_Frame(uint32_t instance);

#endif