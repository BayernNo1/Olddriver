/*****************************************************
GPIO底层函数
修改日期：2016年7月
版权：浙大电磁二队
******************************************************/
//-------------------------------------------------------------------------*
// 文件名: gpio.c                                                          *
// 说  明: gpio驱动程序文件                                                *
//-------------------------------------------------------------------------*

#include "gpio.h"     //包含gpio头文件


void exti_init(void)
{
  //开启各个GPIO口的转换时钟
  SIM_SCGC5 = SIM_SCGC5_PORTA_MASK 
            | SIM_SCGC5_PORTB_MASK 
            | SIM_SCGC5_PORTC_MASK 
            | SIM_SCGC5_PORTD_MASK 
            | SIM_SCGC5_PORTE_MASK;
   //2 关中断

  //IO口中断模式设置过程如下
  SIM_SCGC5|=SIM_SCGC5_PORTE_MASK;// 启用PORTE时钟
  PORTE_PCR4=1<<8 | 0xa<<16| 1;  // GPIO , 下降边沿触发 ,开启上拉电阻 
  GPIOE_PDDR&=~(1<<4);              // 中断必须是输入模式
  enable_irq(91);                 // 启用PORT中断
}


//-------------------------------------------------------------------------*
//函数名: gpio_init                                                        *
//功  能: 初始化gpio                                                       * 
//参  数: port:端口名                                                      *
//        index:指定端口引脚                                               *
//        dir:引脚方向,0=输入,1=输出                                       * 
//        data:初始状态,0=低电平,1=高电平                                  *                                                            *
//-------------------------------------------------------------------------*
void gpio_init (GPIO_MemMapPtr port, int index, int dir,int data)
{
   PORT_MemMapPtr p;
   switch((uint32)port)
   {
     case 0x400FF000u:
         p = PORTA_BASE_PTR;
         break;
     case 0x400FF040u:
         p = PORTB_BASE_PTR;
         break;
     case 0x400FF080u:
         p = PORTC_BASE_PTR;
         break;
     case 0x400FF0C0u:
         p = PORTD_BASE_PTR;
         break;
     case 0x400FF100u:
         p = PORTE_BASE_PTR;
         break;
     default:
         break;
   }
   PORT_PCR_REG(p,index)=(0|PORT_PCR_MUX(1));

   if(dir == 1)//output
   {
       GPIO_PDDR_REG(port) |= (1<<index);
       if(data == 1)//output
          GPIO_PDOR_REG(port) |= (1<<index);
       else
          GPIO_PDOR_REG(port) &= ~(1<<index);
   } 
   else
     GPIO_PDDR_REG(port) &= ~(1<<index);
}

//-------------------------------------------------------------------------* 
//函数名: gpio_ctrl                                                        *
//功  能: 设置引脚状态                                                     *
//参  数: port:端口名                                                      *
//        index:指定端口引脚                                                 *
//        data: 状态,0=低电平,1=高电平                                     *                                                            *
//-------------------------------------------------------------------------*
void gpio_ctrl (GPIO_MemMapPtr port, int index, int data)
{
    if(data == 1)//output
       GPIO_PDOR_REG(port) |= (1<<index);
    else
       GPIO_PDOR_REG(port) &= ~(1<<index);
}

//-----------------------------------------------------------------------* 
//函数名: gpio_reverse                                                   *
//功  能: 改变引脚状态                                                   *
//参  数: port:端口名;                                                   *
//        index:指定端口引脚                                             *                                                            *
//-----------------------------------------------------------------------*
void gpio_reverse (GPIO_MemMapPtr port, int index)
{
    GPIO_PDOR_REG(port) ^= (1<<index);
}


//----------------------------------------------------------------
//函数名：gpio_get
//功能：指定引脚的状态
//参数：port：端口号   pin：引脚号
//----------------------------------------------------------------

uint8 gpio_get(uint8 port,uint8 pin)
{
  uint8 i;
  
  GPIO_MemMapPtr pt=gpio_get_pt_addr(port);
  
  i=BGET(pin,GPIO_PDIR_REG(pt));
  return i;
}

//----------------------------------------------------------
//函数名：gpio_get_port_addr
//----------------------------------------------------------
PORT_MemMapPtr gpio_get_port_addr(uint8 port)
{
  PORT_MemMapPtr p;
  
  switch(port)
  {
    case PTA:
      p=PORTA_BASE_PTR;
      break;
    case PTB:
      p=PORTB_BASE_PTR;
          break;
    case PTC:
      p=PORTC_BASE_PTR;
          break;
    case PTD:
      p=PORTD_BASE_PTR;
          break;
    case PTE:
      p=PORTE_BASE_PTR;
          break;
    default:
      return 0;
  }
  return p;
}


//----------------------------------------------------------
//函数名：gpio_get_port_addr
//----------------------------------------------------------
GPIO_MemMapPtr gpio_get_pt_addr(uint8 port)
{
  GPIO_MemMapPtr p;
  
  switch(port)
  {
    case PTA:
      p=PTA_BASE_PTR;
      break;
    case PTB:
      p=PTB_BASE_PTR;
          break;
    case PTC:
      p=PTC_BASE_PTR;
          break;
    case PTD:
      p=PTD_BASE_PTR;
          break;
    case PTE:
      p=PTE_BASE_PTR;
          break;
    default:
      return 0;
  }
  return p;
}
    