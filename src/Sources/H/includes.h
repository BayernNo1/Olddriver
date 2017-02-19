//-------------------------------------------------------------------------*
//�ļ���: includes.h                                                       *
//˵  ��: ��ͷ�ļ�,���ļ�����:                                             *
//        ������(main)�ļ����õ���ͷ�ļ����ⲿ�����������йس�������       *
//-------------------------------------------------------------------------*
#ifndef INCLUDE_H_
#define INCLUDE_H_

//1 ͷ�ļ�
//1.1ͨ��ͷ�ļ�
#include "common.h"            //ͨ�ú���ͷ�ļ�
        
//1.2��������Ӳ������ͷ�ļ�(������ģ��)      
#include "sysinit.h" 
#include "uart.h"                   
#include "Pit.h"
#include "gpio.h"
#include "math.h"
#include "adc.h"
//#include "Debug.h"
//#include "Control.h"
#include "keyscan.h"
#include "oled.h"
#include "Ftm.h"
//#include "Flash.h"

//#include "functions.h"
#include "vectors.h"
#include "ccd.h"
#include "filter.h"

struct CCD {
  /*int16 right_array[10], left_array[10], angle_array[10], statearray[10]; 
  //right_array, left_array:��¼֮ǰ���ұ߽��ֵ
  //angle_array, state_array:��¼֮ǰ״̬���ͽǶȣ�
  int16 zuo, you, cross, type, right_cross, left_cross, shizi, average, mistake_flag, thresh, max_left, max_right;
  //zuo, you:״̬�� cross:ʮ�� type:���� right_cross:
  int16 error1, error2, left_turn, right_turn, left_line, right_line, width;
  int16 max_voltage, state, pre_left, pre_right, pre_angle, pre_state, angle;
  int16 left, right, center, pre_white_left, pre_white_right;
  unsigned char image[128], filter_image[128], sendData[128];
  int16 jiben_array[128];*/
  int16 average;//ƽ��ֵ
  int16 thresh;//��ֵ
  int16 mistake_flag;//���б�־
  int16 max_voltage; //��������ЧӦ���������ֵ
  int16 cos_array[128];//��������ЧӦ�Ĳ���
  unsigned char data[128], filter_data[128];//ԭ���ݣ��˲�������
};

extern uint8 BO_num[5];
extern struct CCD CCD1;
#endif
