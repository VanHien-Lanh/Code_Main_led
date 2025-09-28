#ifndef __SONIX_APP_H__
#define __SONIX_APP_H__

#include "hal_systick.h"
#include "sn34f78x_hal.h"

extern GPIO_Init_T GPIO3_PIN3_INIT;

extern GPIO_Init_T GPIO3_PIN4_INIT;

uint32_t init(void);
uint32_t uninit(void);
void     Error_Handler(void);
void     SystemClock_Config(void);
/* USER INC & DEF BEGIN */

/* USER INC & DEF END */

#endif //__SONIX_APP_H__
