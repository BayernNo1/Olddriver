/*****************************************************
PIT底层函数
修改日期：2016年7月
版权：浙大电磁二队
******************************************************/
//文件名称：Pit.c
//功能概要：K60 pit底层驱动程序文件
//==============================================================================   
#include "Pit.h"
/*==============================================================================
  周期定时器PIT说明：
  周期中断定时器模块PIT是一组可以用来产生中断和触发DMA通道的定时器
  %%%%%%%%%%%%共有PIT0~PIT3四个通道，对应的IRQ中断号为68~71
  PIT模块配置包括以下寄存器：
  1、PIT模块控制寄存器PIT_MCR
  2、定时器加载值寄存器PIT_LDVALn
  3、当前定时器值寄存器PIT_CVALn
  4、定时器控制寄存器PIT_TCTRLn
  5、定时器标志寄存器PIT_TFLGn

  若要使能PIT模块工作，要设置以下几个寄存器
  1、SIM_SCGC6开启门控之中
  2、PIT_MCR的MDIS=0，使能模块时钟（必须在其他设置完成之前使能）

  PIT模块是采用减法计时的，加载值存储在寄存器PIT_CVALn中，每当定时器递减计数至0，
  将产生一个脉冲触发标志位TIF。

  如果想在调试模式下禁止PIT模块，则需设置PIT_MCR中的FRZ=1。在软件开发中，允许开发
  者停止计时器，查看系统当前状态，然后继续操作。

  定时器值寄存器PIT_CVALn中的值时可以随时读取的

  若想开启定时器开始计数，则需设置PIT_TCTRL中的TEN=1

  关于PIT模块中断的设置，需要考虑以下两个寄存器
  1、PIT_TCTRL中的中断使能标志位TIE=1
  2、开启相应的IRQ中断号的通道中断
  此时，如果计数器计数到0，便会触发并置位中断标志位，进入中断。别忘了在中断服务
  函数中清零标志位。清零方法是向该位写入1。

  PIT模块的时钟源:periph_clk_khz
                                                                   
==============================================================================*/

//==============================================================================
//函数名称: pit_init                                                         
//函数返回: 无                                          
//参数说明: pitno:表示pit通道号。  
//	   timeout:表示定时溢出开始递减的值,该PIT计数使用总线时钟75MHz          
//功能概要: 初始化PIT        
//==============================================================================
void pit_init(uint8 pitno,uint32 timeout)
{
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;              //使能PIT时钟
  PIT_MCR &= ~(PIT_MCR_MDIS_MASK);              //使能PIT模块时钟
  PIT_MCR |= PIT_MCR_FRZ_MASK;                  //调试模式下禁止
  PIT_LDVAL(pitno) = timeout;                   //设置周期
  PIT_TCTRL(pitno) |= PIT_TCTRL_TEN_MASK;       //使能pit模块运行
  PIT_TCTRL(pitno) &= ~(PIT_TCTRL_TIE_MASK);    //关pit中断
}
    
//==============================================================================
//函数名称: enable_pit_interrupt                                                     
//函数返回: 无                                              
//参数说明: pitno: 表示pit通道号      
//功能概要: 开启PIT的IRQ中断                                                                                                     
//==============================================================================
void enable_pit_interrupt(uint8 pitno)
{
  PIT_TCTRL(pitno)|=(PIT_TCTRL_TIE_MASK); //开pit中断
  switch(pitno)
  {
    case 0:
    enable_irq(68);			      //开接收引脚的IRQ中断
    break;
    case 1:
    enable_irq(69);			      //开接收引脚的IRQ中断
    break;
    case 2:
    enable_irq(70);			      //开接收引脚的IRQ中断
    break;
    case 3:
    enable_irq(71);			      //开接收引脚的IRQ中断
    break;
  }
}

//==============================================================================
//函数名称: disable_pit_interrupt                                                     
//函数返回: 无                                              
//参数说明: pitno: 表示pit通道号      
//功能概要: 关闭PIT的IRQ中断                                                                                               
//==============================================================================
void disable_pit_interrupt(uint8 pitno)
{
  PIT_TCTRL(pitno)&=~(PIT_TCTRL_TIE_MASK);  //关pit中断
  switch(pitno)
  {
    case 0:
    disable_irq(68);	        //关接收引脚的IRQ中断
    break;
    case 1:
    disable_irq(69);		      //关接收引脚的IRQ中断
    break;
    case 2:
    disable_irq(70);		      //关接收引脚的IRQ中断
    break;
    case 3:
    disable_irq(71);		      //关接收引脚的IRQ中断
    break;
  }
}