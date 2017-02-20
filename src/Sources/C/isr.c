/*****************************************************
中断函数
修改日期：2016年7月
版权：浙大电磁二队
******************************************************/
//-------------------------------------------------------------------------*
// 文件名: isr.c                                                           *
// 说  明: 中断处理函数集                                                  *
//-------------------------------------------------------------------------*
#include "MK60N512VMD100.h "
#include "includes.h"
extern struct CCD CCD1;

//-------------------------------------------------------------------------*
//函数名: PIT0_isr                                                        *
//功  能: 控制函数中断1ms                                                   *
//说  明: 直立、转向和速度控制                                             *
//-------------------------------------------------------------------------*
void PIT0_isr(void)
{
  disable_pit_interrupt(PIT0); //关中断
  if((PIT_TFLG(0)&PIT_TFLG_TIF_MASK)!=0)
  {
    PIT_TFLG(0) |= PIT_TFLG_TIF_MASK; //清中断标志
  }
  static int cnt = 0;
  cnt++;
  if (cnt == 12) cnt = 0;
  if (cnt == 8)
    findline(&CCD1,1);
  enable_pit_interrupt(PIT0);
}


//-------------------------------------------------------------------------*
//函数名: PIT1_isr                                                         *
//功  能: 100ms键盘扫描,LED刷新中断例程                                            *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*
void PIT1_isr(void)
{
//unsigned char blue_buffer[4];
unsigned char get;
uint8 bluestop;
static char testch[]="00";
  static  char test_time[]="00:00";

  //uint8 get;
  int j;
static int count_time = 0;
  disable_pit_interrupt(PIT1);
  if((PIT_TFLG(1)&PIT_TFLG_TIF_MASK)!=0)
  {
    PIT_TFLG(1) |= PIT_TFLG_TIF_MASK;  //清中断标志
  }
 // 时钟测试程序
  count_time ++;
  if (count_time == 10)
  {
     count_time = 0;
     test_time[4]++;
     if(test_time[4]=='9'+1)
     {
       test_time[4] = '0';
     }
  }
   LCD_P8x16Str(0,0,test_time);
  //gpio_ctrl(PORTA,19,0); //蓝色测试灯
  
   get=uart_re1(FreeCarsUARTPort, &bluestop);
   if (get==1)
   {
      FTM0_C6V=0;
      FTM0_C7V=0;
      FTM0_C4V=0;
      FTM0_C5V=0;
      testch[0]='0'+bluestop/16;
      testch[1]='0'+bluestop%16;
   LCD_P8x16Str(0,2,testch);
      
   }
   
  CCD1_scan();
  filter(&CCD1);
  char test_filter_1[] = "post";
  char test_filter_2[] = "pre";    
  //2017年2月19日测试filter，拨码开关2控制发送蓝牙是滤波前还是滤波后
  if(BO_num[2] == 0){
   for(j = 0 ;j < 128; j++){
      uart_send1(FreeCarsUARTPort, (CCD1.filter_data[j]));
    }
   uart_send1(FreeCarsUARTPort,0xff);
   LCD_P8x16Str(0,4,test_filter_1);   
  }
  else if(BO_num[2] == 1){
   for(j = 0 ;j < 128; j++){
      uart_send1(FreeCarsUARTPort, (CCD1.data[j]));
    }
   uart_send1(FreeCarsUARTPort,0xff); 
   LCD_P8x16Str(0,4,test_filter_2);  
  }
  
  // 2017-2-20测试findline：OLED发送检测到的赛道边界
  char test_edge[] = "l = 000 r = 000";
  test_edge[4] = '0'+CCD1.left/100;
  test_edge[5] = '0'+(CCD1.left/10)%10;
  test_edge[6] = '0'+CCD1.left%10;
  test_edge[12]= '0'+CCD1.right/100; 
  test_edge[13]= '0'+(CCD1.right/10)%10;
  test_edge[14]= '0'+CCD1.right%10;
  LCD_P8x16Str(0,6,test_edge);  
  
  //蓝牙停车
 /* if(uart_re1(UART2,&emergency_stop))
  {
    emergency_stop=1;
  }*/
  
   //按键开关扫描控制
  SW_num=KPScan();
  if (SW_num == 1)
  {
      FTM0_C6V=0;
      FTM0_C7V=200;
      FTM0_C4V=200;
      FTM0_C5V=0;
  }
  
 /* // 按键开关测试
  test_kp[1]='0'+BO_num[1];
  test_kp[2]='0'+BO_num[2];
  test_kp[3]='0'+BO_num[3];
  test_kp[4]='0'+BO_num[4];
  test_kp[6]='0'+SW_num;
  if(SW_num==5)
  {
    point_cnt ++;
  }
  test_time[9]='0'+point_cnt/100;
  test_time[10]='0'+(point_cnt/10)%10;
  test_time[11]='0'+point_cnt%10;
  LCD_P8x16Str(0,6,test_kp);
    */
  //SwitchControl();
  
  /*//测供电电压
  Supply_Voltage=hw_ad_once(0,14,12)/391.0;
  
  //显示屏调试翻页
  if(speed_begin == 0)
  {
    if(page == 1)
    {
      DirectionDebugPage1();
    }
    else if(page == 0)
    {
      AngleDebugPage1();

    }
    else if(page == 2)
    {
      DirectionDebugPage2();
    }
    else if(page == 4)
    {
      AngleDebugPage2();
    }
    else if(page == 3)
    {
      SpeedDebugPage1();
    }
  }
  else  //起跑熄屏
  {
    LCD_CLS();
  }
  
  //起跑延时
  if(motor_on ==1 && speed_on == 1)
  {
    if(speed_delay < 10)
    {
      speed_delay++;
    }
    else
    {
      speed_begin=1;
    }
  }
  
  //跑车计时
  if(timing_begin == 1 && stop_line == 0)
  {
    time_run++;
  }
  
  //gpio_ctrl(PORTA,19,1); //蓝色测试灯*/
  
  enable_pit_interrupt(PIT1);
}
