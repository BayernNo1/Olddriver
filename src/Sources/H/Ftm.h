#ifndef __FTM_H__
#define __FTM_H__

#include "common.h"  
//#include "control.h"

//K60引脚宏定义
//#define LEFT_PHA  PORTB_PCR18
//#define LEFT_PHB  PORTB_PCR19
//#define RIGHT_PHA PORTB_PCR0 //改用A12，并改用ALT7
//#define RIGHT_PHB PORTB_PCR1 //改用A13，并改用ALT7

//K60引脚宏定义
#define LEFT_POS  PORTD_PCR4
#define LEFT_NEG  PORTD_PCR5
#define RIGHT_POS PORTD_PCR6
#define RIGHT_NEG PORTD_PCR7

#define CTR       PORTB_PCR1

void pwm_init(void);
void quad_init(void);

#endif 

