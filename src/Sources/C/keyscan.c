/*****************************************************
�������ؿ��Ƶײ㺯��
�޸����ڣ�2016��7��
��Ȩ������Ŷ���
******************************************************/
#include "keyscan.h"
#include "includes.h"

uint8 BO_num[5];   //���뿪��״̬��¼����
uint8 KP_flage;
uint8 SW_num;

//------------------------------------------------------------------------------
//��������KPInit
//��  �ܣ����̳�ʼ������
//��  ������
//��  �أ���
//˵  ����
//------------------------------------------------------------------------------
void KPInit(void)
{
  //gpio_init(PORTA,19,1,1);//��Ƭ����Χ���Եƣ��������  //δʹ��
  //gpio_init(PORTB,17,0,1);//ͣ���źż��

  //����
  gpio_init(PORTC, 4, 0, 1);
  gpio_init(PORTC, 5, 0, 1);  
  gpio_init(PORTC, 6, 0, 1);
  gpio_init(PORTC, 7, 0, 1); 
  gpio_init(PORTB,23, 0, 1); 
  
  //���뿪��
  gpio_init(PORTC, 8, 0, 1);
  gpio_init(PORTC, 9, 0, 1);
  gpio_init(PORTC,10, 0, 1);
  gpio_init(PORTC,11, 0, 1);       
}

//------------------------------------------------------------------------------
//��������KPScan
//��  �ܣ�����ɨ�躯��
//��  ������
//��  �أ��������ص�ֵ
//˵  ����
//------------------------------------------------------------------------------

uint8 KPScan(void)
{
    uint8 KP_return,KP_return_old;
    uint8 KP_temp;
    
    //ɨ�貦�뿪��
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
    
    //ɨ�谴��
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
    
    //�ٴ�ɨ�谴��
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
    
    if(KP_return==KP_return_old)//����ɨ�赽�ļ���ֵ���
    {
      return KP_return;
    }
    else return 0;
}

//-------------------------------------------------------------------------*
//������: flag_control                                                      *
//��  ��: �������Ƴ���                                           *
//˵  ��: ��                                                               *
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
//��������DelayMs
//��  �ܣ�ms��ʱ����
//��  ������ʱ����time_cnt
//��  �أ���
//˵  ������ʱ��������1����1ms
//��  ע��
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
//��������DelayUs
//��  �ܣ�us��ʱ����
//��  ������ʱ����time_cnt
//��  �أ���
//˵  ������ʱ��������1����1us
//��  ע��
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
    
    