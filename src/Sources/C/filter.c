#include "filter.h"
/**********
filter：对CCD采集的数据进行均值滤波处理、消除余弦效应并进行降噪处理
功能：输入CCD结构ccd和ccd滤波前数据data，结果放在ccd -> filter_data中
***********/
void filter(struct CCD *ccd)//, unsigned char *data, unsigned char *filter_data)
{
  uint8 i;
  int temp;
  int16 max_voltage = 0, min_voltage = 255;
  for (i = 0; i < 128; i++){
    switch (i)
    {
    case 0:temp = ccd -> max_voltage * ccd -> data[0] / ccd -> cos_array[i];break;
    case 1:temp = ccd -> max_voltage * ccd -> data[1] / ccd -> cos_array[i];break;
    case 126:temp = ccd -> max_voltage * ccd -> data[126] / ccd -> cos_array[i];break;
    case 127:temp = ccd -> max_voltage * ccd -> data[127] / ccd -> cos_array[i];break;
    default:
      temp = ccd -> max_voltage * ( ccd -> data[i - 2] + ccd -> data[i - 1] + ccd -> data[i] + ccd -> data[i + 1] + ccd -> data[i + 2]) / 5 / ccd->cos_array[i];
      break;
    }
    if (temp > 255)
       temp = 255;
    ccd -> filter_data[i] = temp;
    }
  ccd->mistake_flag = 0;
  peakfilter(ccd);//, ccd -> filter_data);//降噪处理
  for(i = 12; i < 115; i++){
      if (ccd -> filter_data[i] > max_voltage)
         max_voltage = ccd -> filter_data[i];
      if (ccd -> filter_data[i] < min_voltage)
         min_voltage = ccd -> filter_data[i];
    }
  ccd->average = threshold(ccd -> filter_data, (max_voltage + min_voltage)/2);

}
/**********
threshold：计算阈值
功能：输入滤波前的数据，和均值滤波后平均值，返回阈值
***********/
int32 threshold(unsigned char *data, int32 average){
  int count_white = 0, count_black = 0, sum_white = 0, sum_black= 0, i;
  for(i = 5;i <= 122; i++){
    if(data[i] > average){
      count_white ++;
      sum_white += data[i];
    }
    else if (data[i] < average){
      count_black ++;
      sum_black += data[i];
    }
  }
  return (sum_black / count_black + sum_white / count_white)/2;  
}
void peakfilter(struct CCD *ccd)//, unsigned char *data)
{
  int i, j, k, flag, left_position, right_position;
  int32 temp;
  j = 12;
  flag = 0;
  while(j < 115){
    for(i = j;i <= 115; i++){
      temp = ccd -> filter_data[i];
      if (temp >= ccd -> thresh){
        if (!flag){
          flag = 1;
          left_position = i;
        }
      }
      if (flag == 1){
        if(temp < ccd -> thresh){
          right_position = i;
          if(right_position - left_position <= 10){
              for(k = left_position; k <= right_position; k++)
                ccd -> filter_data[k]=ccd -> thresh - 2;
              j = right_position;
              break;
          }
          else{
            j = i;
            break;
          }
        }
      }
      if(i == 115)
        j = i;
    }
    flag = 0;
  }
}
      