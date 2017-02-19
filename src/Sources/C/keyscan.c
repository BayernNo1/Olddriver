/*****************************************************
按键开关控制底层函数
修改日期：2016年7月
版权：浙大电磁二队
******************************************************/
#include "keyscan.h"
#include "includes.h"

uint8 BO_num[5];   //拨码开关状态记录数组
uint8 KP_flage;
uint8 SW_num;

//------------------------------------------------------------------------------
//函数名：KPInit
//功  能：键盘初始化函数
//参  数：无
//返  回：无
//说  明：
//------------------------------------------------------------------------------
void KPInit(void)
{
  //gpio_init(PORTA,19,1,1);//单片机外围调试灯，输出引脚  //未使用
  //gpio_init(PORTB,17,0,1);//停车信号检测

  //按键
  gpio_init(PORTC, 4, 0, 1);
  gpio_init(PORTC, 5, 0, 1);  
  gpio_init(PORTC, 6, 0, 1);
  gpio_init(PORTC, 7, 0, 1); 
  gpio_init(PORTB,23, 0, 1); 
  
  //拨码开关
  gpio_init(PORTC, 8, 0, 1);
  gpio_init(PORTC, 9, 0, 1);
  gpio_init(PORTC,10, 0, 1);
  gpio_init(PORTC,11, 0, 1);       
}

//------------------------------------------------------------------------------
//函数名：KPScan
//功  能：键盘扫描函数
//参  数：无
//返  回：按键开关的值
//说  明：
//------------------------------------------------------------------------------

uint8 KPScan(void)
{
    uint8 KP_return,KP_return_old;
    uint8 KP_temp;
    
    //扫描拨码开关
    KP_temp =gpio_get(PTC,11);
    if(KP_temp==0)
      BO_num[4]=0;    
    else BO_num[4]=1;
    
    KP_temp =gpio_get(PTC, 9);
    if(KP_temp==0)
      BO_num[3]=0;
    else BO_num[3]=1;
    
    KP_temp =gpio_get(PTC,10);
    if(KP_temp==0)
      BO_num[2]=0;
    else BO_num[2]=1;
    
    KP_temp =gpio_get(PTC, 8);
    if(KP_temp==0)
      BO_num[1]=0;
    else BO_num[1]=1;
    
    //扫描按键
    if(gpio_get(PTB,23)==0)
      KP_return=1;
    else if(gpio_get(PTC,7)==0)
      KP_return=2;
    else if(gpio_get(PTC,6)==0)
      KP_return=3;
    else if(gpio_get(PTC,5)==0)
      KP_return=4;
    else if(gpio_get(PTC,4)==0)
      KP_return=5;
    else KP_return=0;
    
    KP_return_old=KP_return;
    
    //再次扫描按键
    if(gpio_get(PTB,23)==0)
      KP_return=1;  //sw1    
    else if(gpio_get(PTC,7)==0)
      KP_return=2;  //sw2   
    else if(gpio_get(PTC,6)==0)
      KP_return=3;  //sw3
    else if(gpio_get(PTC,5)==0)
      KP_return=4;  //sw4 
    else if(gpio_get(PTC,4)==0)
      KP_return=5;  //sw5
    else KP_return=0;
    
    if(KP_return==KP_return_old)//两次扫描到的键盘值相等
    {
      return KP_return;
    }
    else return 0;
}

//-------------------------------------------------------------------------*
//函数名: flag_control                                                      *
//功  能: 按键控制程序                                           *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*
/*void SwitchControl()
{
 
  if(BO_num[1] == 1)    
  {
    gyro_bias_on=0;
    gyro_bias_ok=0;
    ramp_test_on=0;
  }
  else 
  {
    gyro_bias_on=1;
    ramp_test_on=1;
  }

  if(BO_num[2] == 0)    
  {
    motor_on = 1;
  }
  else   
  {
    motor_on = 0;
  }

  if(BO_num[3] == 0)   
  {
    direction_on = 1;
  }
  else
  {
    direction_on = 0;
  }

  if(BO_num[4] == 0)   
  {
    speed_on=1;
  }
  else
  {
    speed_on=0;
  }


  if(SW_num == 1) 
  {
      page++;
      LCD_CLS();
  }
  if(page == 5)
  {
      page=0;
  }
}
*/


//------------------------------------------------------------------------------
//函数名：DelayMs
//功  能：ms延时程序
//参  数：延时长度time_cnt
//返  回：无
//说  明：延时程序，输入1代表1ms
//备  注：
//------------------------------------------------------------------------------
void DelayMs(int32 time_cnt)
{
  int32 ii,jj;
  if(time_cnt < 1)
    time_cnt = 1;
  for(ii = 0;ii < time_cnt;ii++)
    for(jj = 0;jj < 20000;jj++);
}

//------------------------------------------------------------------------------
//函数名：DelayUs
//功  能：us延时程序
//参  数：延时长度time_cnt
//返  回：无
//说  明：延时程序，输入1代表1us
//备  注：
//------------------------------------------------------------------------------
void DelayUs(int32 time_cnt)
{
  int32 ii;
  time_cnt = time_cnt * 10;
  if(time_cnt < 1)
    time_cnt = 1; 
  for(ii = 0;ii < time_cnt;ii++)
  {
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
  }
}
    
    