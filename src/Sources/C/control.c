#include "control.h"
double p, d = 0.4;
double Kp = 1;//例程PID参数
int16 center_line = 64;
int16 barrier_flag = 0;//障碍标志
int16 servo = 0;
int16 Servo_Current;//日后使用
int16 speed_left, speed_right;
void Servo_Turn(int16 angle)
{
  FTM1_C1V = 920 + (90 - angle) * 120 / 45 - servo;//参数待调120
  Servo_Current = FTM1_C1V;     //差速用变量(可以简化)
}

void Set_Speed(int16 speed_left, int16 speed_right)
{
  if (speed_left > SPEED_LIMIT)
    speed_left = SPEED_LIMIT;
  if (speed_left < -SPEED_LIMIT)
    speed_left = -SPEED_LIMIT;
  if (speed_right > SPEED_LIMIT)
    speed_right = SPEED_LIMIT;
  if (speed_right < -SPEED_LIMIT)
    speed_right = -SPEED_LIMIT;
  if (speed_left >= 0)
  {
    FTM0_C7V = speed_left;
    FTM0_C6V = 0;
  }
  else
  {
    FTM0_C7V = 0;
    FTM0_C6V = -speed_left;
  }
  if (speed_right >= 0)
  {
    FTM0_C4V = speed_right;
    FTM0_C5V = 0;
  }
  else
  {
    FTM0_C4V = 0;
    FTM0_C5V = -speed_right;
  }
}

int16 Calculate_Angle(struct CCD *ccd)
{
  int16 temp;
  if (ccd->state != 5) //例程用
  {
    //障碍检测部分
    if (barrier_flag == 1)
      center_line = 48;
    else if (barrier_flag == 2)
      center_line = 80;
    else
      center_line = 64;
    if (ccd->center - center_line <= 0)
      temp = (int16)(Kp * (center_line - ccd->center) + 90);
    else
      temp = (int16)(90 - Kp * (ccd->center - center_line));//缺少模糊p参数
    //省略ccd->prestate == 5
    if (temp <= ccd->max_angle_right)
      temp = ccd->max_angle_right;
    if (temp >= ccd->max_angle_left)
      temp = ccd->max_angle_left;
  }
  return temp;
}