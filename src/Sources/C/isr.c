/*****************************************************
�жϺ���
�޸����ڣ�2016��7��
��Ȩ������Ŷ���
******************************************************/
//-------------------------------------------------------------------------*
// �ļ���: isr.c                                                           *
// ˵  ��: �жϴ�������                                                  *
//-------------------------------------------------------------------------*
#include "MK60N512VMD100.h "
#include "includes.h"
extern struct CCD CCD1;

//-------------------------------------------------------------------------*
//������: PIT0_isr                                                        *
//��  ��: ���ƺ����ж�1ms                                                   *
//˵  ��: ֱ����ת����ٶȿ���                                             *
//-------------------------------------------------------------------------*
void PIT0_isr(void)
{
  disable_pit_interrupt(PIT0); //���ж�
  if((PIT_TFLG(0)&PIT_TFLG_TIF_MASK)!=0)
  {
    PIT_TFLG(0) |= PIT_TFLG_TIF_MASK; //���жϱ�־
  }
  static int cnt = 0;
  cnt++;
  if (cnt == 12) cnt = 0;
  if (cnt == 8)
    findline(&CCD1,1);
  enable_pit_interrupt(PIT0);
}


//-------------------------------------------------------------------------*
//������: PIT1_isr                                                         *
//��  ��: 100ms����ɨ��,LEDˢ���ж�����                                            *
//˵  ��: ��                                                               *
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
    PIT_TFLG(1) |= PIT_TFLG_TIF_MASK;  //���жϱ�־
  }
 // ʱ�Ӳ��Գ���
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
  //gpio_ctrl(PORTA,19,0); //��ɫ���Ե�
  
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
  //2017��2��19�ղ���filter�����뿪��2���Ʒ����������˲�ǰ�����˲���
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
  
  // 2017-2-20����findline��OLED���ͼ�⵽�������߽�
  char test_edge[] = "l = 000 r = 000";
  test_edge[4] = '0'+CCD1.left/100;
  test_edge[5] = '0'+(CCD1.left/10)%10;
  test_edge[6] = '0'+CCD1.left%10;
  test_edge[12]= '0'+CCD1.right/100; 
  test_edge[13]= '0'+(CCD1.right/10)%10;
  test_edge[14]= '0'+CCD1.right%10;
  LCD_P8x16Str(0,6,test_edge);  
  
  //����ͣ��
 /* if(uart_re1(UART2,&emergency_stop))
  {
    emergency_stop=1;
  }*/
  
   //��������ɨ�����
  SW_num=KPScan();
  if (SW_num == 1)
  {
      FTM0_C6V=0;
      FTM0_C7V=200;
      FTM0_C4V=200;
      FTM0_C5V=0;
  }
  
 /* // �������ز���
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
  
  /*//�⹩���ѹ
  Supply_Voltage=hw_ad_once(0,14,12)/391.0;
  
  //��ʾ�����Է�ҳ
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
  else  //����Ϩ��
  {
    LCD_CLS();
  }
  
  //������ʱ
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
  
  //�ܳ���ʱ
  if(timing_begin == 1 && stop_line == 0)
  {
    time_run++;
  }
  
  //gpio_ctrl(PORTA,19,1); //��ɫ���Ե�*/
  
  enable_pit_interrupt(PIT1);
}
