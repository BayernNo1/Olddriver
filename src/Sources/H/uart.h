//-------------------------------------------------------------------------*
// �ļ���: uart.h                                                          *
// ˵  ��: uart����ͷ�ļ�                                                  *
//-------------------------------------------------------------------------*

#ifndef __UART_H__
#define __UART_H__
	
//1 ͷ�ļ�
#include "common.h"
#include "includes.h"

#define FreeCarsUARTPort UART0
//#define FreeCarsUARTPort UART2
#define FreeCarsIRQ      IRQ_UART0


//FreeCars��λ�� ����������ʾ�� ����ͨ������������λ�����øı�
#define UartDataNum      17

//���²�Ҫ�޸�
#define UartRxBufferLen  100
#define UartRxDataLen    41           //FreeCars��λ�����͸�������MCU���գ���Ҫ��
#define UartRxCmdLen     7	      //FreeCars��λ�������������ݳ��ȣ���Ҫ��

#define UartCmdNum  SerialPortRx.Buffer[SerialPortRx.Stack-3]//�����
#define UartCmdData SerialPortRx.Buffer[SerialPortRx.Stack-2]//��������
//�������ݵĳ���ֻҪ�����鳤��Ϊ26=22+3+1������Ϊ���뷢���ַ���ȡ��ͳһ
//ȡ���ݵĳ������ַ����ĳ�����ȣ������ڷ��������ǻ�෢����һЩ
//��Чλ������Ӱ�첻���

typedef struct 
{
  int Stack;
  uint8 Data;
  uint8 PreData;
  uint8 Buffer[UartRxBufferLen];
  uint8 Enable;
  uint8 Check;
}SerialPortType;

extern uint8 uSendBuf[UartDataNum*2];
extern SerialPortType SerialPortRx;
extern double UartData[9];

//2 �궨��
//2.1 ���ںź궨��
#define UART0 UART0_BASE_PTR
#define UART1 UART1_BASE_PTR
#define UART2 UART2_BASE_PTR
#define UART3 UART3_BASE_PTR
#define UART4 UART4_BASE_PTR
#define UART5 UART5_BASE_PTR

//2.2 ��������irq�ź궨��
#define UART0irq 45
#define UART1irq 47
#define UART2irq 49
#define UART3irq 51
#define UART4irq 53
#define UART5irq 55


//3 ��������
//-------------------------------------------------------------------------*
//������: uart_init                                                        *
//��  ��: ��ʼ��uartxģ�顣                                                *
//��  ��: uartch:���ں�                                                    *
//        sysclk:ϵͳ����ʱ�ӣ���MHzΪ��λ                                 *
//        baud:�����ʣ���9600��38400�ȣ�һ����˵���ٶ�Խ����ͨ��Խ��       *                                                                *
//-------------------------------------------------------------------------*
void uart_init (UART_MemMapPtr uartch, uint32 sysclk, uint32 baud);

//-------------------------------------------------------------------------*
//������: uart_re1                                                         *
//��  ��: ���н���1���ֽ�                                                  *
//��  ��: uartch: ���ں�                                                   *
//         ch:    ���յ����ֽ�                                             *
//��  ��: �ɹ�:1;ʧ��:0                                                    *                                                                *
//-------------------------------------------------------------------------*
uint8 uart_re1 (UART_MemMapPtr uartch,uint8 *ch);

//-------------------------------------------------------------------------*
//������: uart_send1                                                       *
//��  ��: ���з���1���ֽ�                                                  *
//��  ��: uartch: ���ں�                                                   *
//         ch:    Ҫ���͵��ֽ�                                             *                                                               *
//-------------------------------------------------------------------------*
void uart_send1 (UART_MemMapPtr uartch, uint8 ch);

//-------------------------------------------------------------------------*
//������: uart_reN                                                         *
//��  ��: ���� ����n���ֽ�                                                 *
//��  ��: uartch: ���ں�                                                   *
//        buff: ���ջ�����                                                 *
//		  len:���ճ���                                                 *
//��  ��: 1:�ɹ�;0:ʧ��                                                    *                                                                *
//-------------------------------------------------------------------------*
uint8  uart_reN (UART_MemMapPtr uartch ,uint8* buff,uint16 len);

//-------------------------------------------------------------------------*
//������: uart_sendN                                                       *
//��  ��: ���� ����n���ֽ�                                                 *
//��  ��: uartch: ���ں�                                                   *
//        buff: ���ͻ�����                                                 *
//		  len:���ͳ���                                                 *                                                         *
//-------------------------------------------------------------------------*
void uart_sendN (UART_MemMapPtr uartch ,uint8* buff,uint16 len);


//-------------------------------------------------------------------------*
//������: enableuartreint                                                  *
//��  ��: �����ڽ����ж�                                                   *
//��  ��: uartch: ���ں�                                                   *
//        irqno: ��Ӧirq��                                                 *                                                                 *
//-------------------------------------------------------------------------*
void enableuartreint(UART_MemMapPtr uartch,uint8 irqno);


//-------------------------------------------------------------------------*
//������: disableuartreint                                                 *
//��  ��: �ش��ڽ����ж�                                                   *
//��  ��: uartch: ���ں�                                                   *
//        irqno: ��Ӧirq��                                                 *                                                               *
//-------------------------------------------------------------------------*
void disableuartreint(UART_MemMapPtr uartch,uint8 irqno);
    

void push(uint8 chanel,uint16 data);
void sendDataToScope(void);

uint8 UartGetOneByte(UART_MemMapPtr uartch);


extern uint8 BO_num[5];
extern struct CCD CCD1;
    
#endif 
