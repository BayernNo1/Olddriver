#ifndef _CONTROL_H_
#define _CONTROL_H_
#include "common.h"
#include "includes.h"

#define SPEED_LIMIT 200
void Set_Speed(int16 speed_left, int16 speed_right);
void Servo_Turn(int16 angle);
int16 Calculate_Angle(struct CCD *ccd);


#endif