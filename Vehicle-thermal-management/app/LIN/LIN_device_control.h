#ifndef _LIN_DEVICE_CONTROL_H_
#define _LIN_DEVICE_CONTROL_H_

#include "Task.h"
#include "LIN.h"
#include "string.h"
#include "FreeRTOS.h"
#include "semphr.h"


/************************************ 压缩机通讯 ************************************/


/* 更改压缩机的转速，变相等于开启压缩机 */
uint8_t Compressor_Set_Speed(uint16_t speed, uint16_t limit_power);
/* 关闭压缩机 */
uint8_t Compressor_Shutdown(void);
/* 获取压缩机状态 */
uint8_t Compressor_Get_info(void);



/************************************ 电子膨胀阀通讯 ************************************/

/* 更改电子膨胀阀的开度 */
uint8_t Expansion_valve_Set_Open(uint16_t open);

/* 获取电子膨胀阀状态 */
uint8_t Compressor_Get_info(void)

/************************************ 三通阀通讯 ************************************/



/************************************ 四通阀通讯 ************************************/






/************************************ WPTC通讯 ************************************/



#endif