#ifndef __LIN_H__
#define __LIN_H__

#include "stdint.h"
#include "linflexd_lin_config.h"

#define LINFlexD_Master         (1)
#define LINMaserRecvDone        (1)
#define LINMasterSendDone       (2)
#define LINMasterError          (3)

/* 
currentEvent = 1 means master recv done, 
currentEvent = 2 means master send done,
currentEvent = 3 means error happens
*/
extern volatile uint8_t currentEvent;


// LIN主机 初始化
void LIN_MASTER_init(void);

// LIN主机 发送帧
void LIN_Master_Send_Frame();

// LIN主机 接收帧
void LIN_Master_Receive_Frame();





#endif