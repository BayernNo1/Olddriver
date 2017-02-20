#include "findline.h"
/****
findline函数，用于道路类型检测
****/
void findline(struct CCD *ccd,int num)
{
  int i,count1,count2;
  int flag_rise = 0 , flag_fall = 0 , flag_white = 0;
  int edge_left = 0 , edge_right = 127;
  int position_left , position_right;
  int leftedge_max , rightedge_max , leftedge_sec , rightedge_sec;
  int range_sec , range_max;
  int16 temp;
  
  count1 = 0;
  count2 = 0;
  range_sec = 0;
  range_max = 0;
  
  //检测白色区域
  for(i = 5 ; i <= 122 ; i++)
  {
    if (i <= 120)
    {
      temp = ccd ->filter_data[i+2] - ccd ->filter_data[i];//检测上升沿
      if(temp >= edge) count1++;
      else count1 = 0;
      if(count1 == edgecount)
      {
         flag_rise = 1;
         edge_left = i;
      }
    }
    if (i >= 7)
    {
      temp = ccd ->filter_data[i-2] - ccd ->filter_data[i];//检测下降沿
      if(temp >= edge) count2++;
      else count2 = 0;
      if(count2 == edgecount)
      {
         flag_fall = 1;
         edge_right = i;
      }
    }
    if(( ccd->filter_data[i] > ccd->thresh) && (!flag_white))
    {
      flag_white = 1;
      position_left = i;
    }
    if(flag_white)
    {
      if (ccd->filter_data[i] <= ccd->thresh)
      {
        position_right = i;
        if ((position_right - position_left >= 30) || (position_left <10)/*左丢线*/)
        {
          if (position_right - position_left > range_max)
          {
            range_sec = range_max;
            leftedge_sec = leftedge_max;
            rightedge_sec = rightedge_max;
            leftedge_max = position_left;
            rightedge_max = position_right;
            range_max = position_right - position_left;
          }
          else if (position_right - position_left > range_sec)
          {
            range_sec = position_right - position_left;
            leftedge_sec = position_left;
            rightedge_sec = position_right;
          }
        }
        flag_white = 0;
      }
    }
  }
  if (flag_rise && flag_fall && 
      (edge_right - edge_left < 80/*参数待调*/) && 
      (edge_right > edge_left) && (range_sec == 0))
  {
    ccd->thresh = ccd->average;
  }
  if(flag_white)//右丢线处理
  {
    if (122 - position_left > range_max)
    {
      range_sec = range_max;
      leftedge_sec = leftedge_max;
      rightedge_sec = rightedge_max;
      leftedge_max = position_left;
      rightedge_max = 122;
      range_max = 122 - position_left;
    }
    else if (122 - position_left > range_sec)
    {
      range_sec = 122 - position_left;
      leftedge_sec = position_left;
      rightedge_sec = 122;
    }
  }
  //临时测试使用
  ccd->left = leftedge_max;
  ccd->right = rightedge_max;
}