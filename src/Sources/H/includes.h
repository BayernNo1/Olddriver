//-------------------------------------------------------------------------*
//文件名: includes.h                                                       *
//说  明: 总头文件,本文件包含:                                             *
//        主函数(main)文件中用到的头文件、外部函数声明及有关常量命名       *
//-------------------------------------------------------------------------*
#ifndef INCLUDE_H_
#define INCLUDE_H_

//1 头文件
//1.1通用头文件
#include "common.h"            //通用函数头文件
        
//1.2包含面向硬件对象头文件(即构件模块)      
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
  //right_array, left_array:记录之前左右边界的值
  //angle_array, state_array:记录之前状态（和角度）
  int16 zuo, you, cross, type, right_cross, left_cross, shizi, average, mistake_flag, thresh, max_left, max_right;
  //zuo, you:状态量 cross:十字 type:类型 right_cross:
  int16 error1, error2, left_turn, right_turn, left_line, right_line, width;
  int16 max_voltage, state, pre_left, pre_right, pre_angle, pre_state, angle;
  int16 left, right, center, pre_white_left, pre_white_right;
  unsigned char image[128], filter_image[128], sendData[128];
  int16 jiben_array[128];*/
  int16 average;//平均值
  int16 thresh;//阈值
  int16 mistake_flag;//误判标志
  int16 max_voltage; //消除余弦效应参数的最大值
  int16 cos_array[128];//消除余弦效应的参数
  unsigned char data[128], filter_data[128];//原数据，滤波后数据
};

extern uint8 BO_num[5];
extern struct CCD CCD1;
#endif
