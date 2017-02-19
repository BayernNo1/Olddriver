/*****************************************************
GPIO�ײ㺯��
�޸����ڣ�2016��7��
��Ȩ������Ŷ���
******************************************************/
//-------------------------------------------------------------------------*
// �ļ���: gpio.c                                                          *
// ˵  ��: gpio���������ļ�                                                *
//-------------------------------------------------------------------------*

#include "gpio.h"     //����gpioͷ�ļ�


void exti_init(void)
{
  //��������GPIO�ڵ�ת��ʱ��
  SIM_SCGC5 = SIM_SCGC5_PORTA_MASK 
            | SIM_SCGC5_PORTB_MASK 
            | SIM_SCGC5_PORTC_MASK 
            | SIM_SCGC5_PORTD_MASK 
            | SIM_SCGC5_PORTE_MASK;
   //2 ���ж�

  //IO���ж�ģʽ���ù�������
  SIM_SCGC5|=SIM_SCGC5_PORTE_MASK;// ����PORTEʱ��
  PORTE_PCR4=1<<8 | 0xa<<16| 1;  // GPIO , �½����ش��� ,������������ 
  GPIOE_PDDR&=~(1<<4);              // �жϱ���������ģʽ
  enable_irq(91);                 // ����PORT�ж�
}


//-------------------------------------------------------------------------*
//������: gpio_init                                                        *
//��  ��: ��ʼ��gpio                                                       * 
//��  ��: port:�˿���                                                      *
//        index:ָ���˿�����                                               *
//        dir:���ŷ���,0=����,1=���                                       * 
//        data:��ʼ״̬,0=�͵�ƽ,1=�ߵ�ƽ                                  *                                                            *
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
//������: gpio_ctrl                                                        *
//��  ��: ��������״̬                                                     *
//��  ��: port:�˿���                                                      *
//        index:ָ���˿�����                                                 *
//        data: ״̬,0=�͵�ƽ,1=�ߵ�ƽ                                     *                                                            *
//-------------------------------------------------------------------------*
void gpio_ctrl (GPIO_MemMapPtr port, int index, int data)
{
    if(data == 1)//output
       GPIO_PDOR_REG(port) |= (1<<index);
    else
       GPIO_PDOR_REG(port) &= ~(1<<index);
}

//-----------------------------------------------------------------------* 
//������: gpio_reverse                                                   *
//��  ��: �ı�����״̬                                                   *
//��  ��: port:�˿���;                                                   *
//        index:ָ���˿�����                                             *                                                            *
//-----------------------------------------------------------------------*
void gpio_reverse (GPIO_MemMapPtr port, int index)
{
    GPIO_PDOR_REG(port) ^= (1<<index);
}


//----------------------------------------------------------------
//��������gpio_get
//���ܣ�ָ�����ŵ�״̬
//������port���˿ں�   pin�����ź�
//----------------------------------------------------------------

uint8 gpio_get(uint8 port,uint8 pin)
{
  uint8 i;
  
  GPIO_MemMapPtr pt=gpio_get_pt_addr(port);
  
  i=BGET(pin,GPIO_PDIR_REG(pt));
  return i;
}

//----------------------------------------------------------
//��������gpio_get_port_addr
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
//��������gpio_get_port_addr
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
    