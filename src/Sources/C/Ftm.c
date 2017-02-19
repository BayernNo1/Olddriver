/*****************************************************
FTM�ײ㺯��
�޸����ڣ�2016��7��
��Ȩ������Ŷ���
******************************************************/
#include "Ftm.h"

/*==========================================================================
FTM1c0 PWM�����ʼ������
The edge-aligned mode is selected when (QUADEN = 0), (DECAPEN = 0), (COMBINE
= 0), (CPWMS = 0), and (MSnB = 1).  
K60P144M100SF2RM.pdf  P1011 39.4.6 Edge-Aligned PWM (EPWM) Mode
The EPWM period is determined by (MOD - CNTIN + 0x0001) and the pulse width
(duty cycle) is determined by (CnV - CNTIN).
//==========================================================================*/
void pwm_init(void)
{      	
  //SIM_SOPT4|=SIM_SOPT4_FTM1FLT0_MASK;        
  /* Turn on all port clocks */
  //SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
    
  /* Enable the function on PT */
  LEFT_POS  = PORT_PCR_MUX(0x4)| PORT_PCR_DSE_MASK;      
  LEFT_NEG  = PORT_PCR_MUX(0x4)| PORT_PCR_DSE_MASK;
  RIGHT_POS = PORT_PCR_MUX(0x4)| PORT_PCR_DSE_MASK;
  RIGHT_NEG = PORT_PCR_MUX(0x4)| PORT_PCR_DSE_MASK;
  
  CTR = PORT_PCR_MUX(0x3)| PORT_PCR_DSE_MASK;//���PWM

  SIM_SCGC6|=SIM_SCGC6_FTM0_MASK;//ʹ��FTM0ʱ��      
  SIM_SCGC6|=SIM_SCGC6_FTM1_MASK;//ʹ��FTM1ʱ��
  
  //change MSnB = 1  
  FTM0_C4SC |= FTM_CnSC_ELSB_MASK;
  FTM0_C4SC &= ~FTM_CnSC_ELSA_MASK;
  FTM0_C4SC |= FTM_CnSC_MSB_MASK;     

  FTM0_C5SC |= FTM_CnSC_ELSB_MASK;
  FTM0_C5SC &= ~FTM_CnSC_ELSA_MASK;
  FTM0_C5SC |= FTM_CnSC_MSB_MASK; 

  FTM0_C6SC |= FTM_CnSC_ELSB_MASK;
  FTM0_C6SC &= ~FTM_CnSC_ELSA_MASK;
  FTM0_C6SC |= FTM_CnSC_MSB_MASK; 

  FTM0_C7SC |= FTM_CnSC_ELSB_MASK;
  FTM0_C7SC &= ~FTM_CnSC_ELSA_MASK;
  FTM0_C7SC |= FTM_CnSC_MSB_MASK; 

  FTM1_C1SC |= FTM_CnSC_ELSB_MASK;
  FTM1_C1SC &= ~FTM_CnSC_ELSA_MASK;
  FTM1_C1SC |= FTM_CnSC_MSB_MASK; 

  //FTM1_SC = FTM_SC_PS(0) | FTM_SC_CLKS(1);
  //FTM1_SC=0X0F;     
  FTM0_SC = FTM_SC_PS(7) | FTM_SC_CLKS(1);//???not enable the interrupt mask   0x0c
  
  FTM1_SC = FTM_SC_PS(7) | FTM_SC_CLKS(1);//???not enable the interrupt mask   0x0c
  //FTM1_SC=0X1F;       //BIT5  0 FTM counter operates in up counting mode.
                        //1 FTM counter operates in up-down counting mode.      
  //BIT43 FTM1_SC|=FTM1_SC_CLKS_MASK;
                        //00 No clock selected (This in effect disables the FTM counter.)
                        //01 System clock
                        //10 Fixed frequency clock
                        //11 External clock
  //BIT210 FTM1_SC|=FTM1_SC_PS_MASK; 
                        //100M          MOD=2000;     MOD=4000;   MOD=1000; 
                        //000 Divide by 1---12KHZ     6K          24k
                        //001 Divide by 2--- 6KHZ
                        //010 Divide by 4--- 3K
                        //011 Divide by 8--- 1.5K
                        //100 Divide by 16---750
                        //101 Divide by 32---375
                        //110 Divide by 64---187.5HZ
                        //111 Divide by 128--93.75hz             

  FTM0_MODE |= FTM_MODE_WPDIS_MASK;
  FTM1_MODE |= FTM_MODE_WPDIS_MASK;
   //BIT1   Initialize the Channels Output
  //FTMEN is bit 0, need to set to zero so DECAPEN can be set to 0
  FTM0_MODE &= ~1;
  FTM1_MODE &= ~1;
   //BIT0   FTM Enable
   //0 Only the TPM-compatible registers (first set of registers) can be used without any restriction. Do not use the FTM-specific registers.
   //1 All registers including the FTM-specific registers (second set of registers) are available for use with no restrictions.

  FTM0_OUTMASK=0X0F;   //0 Channel output is not masked. It continues to operate normally.
                       //1 Channel output is masked. It is forced to its inactive state.
  FTM1_OUTMASK=0XFD;

  FTM0_COMBINE=0;      //Function for Linked Channels (FTMx_COMBINE)
  FTM0_OUTINIT=0;
  FTM0_EXTTRIG=0;      //FTM External Trigger (FTMx_EXTTRIG)
  FTM0_POL=0;          //Channels Polarity (FTMx_POL)
                       //0 The channel polarity is active high.
                       //1 The channel polarity is active low. 
  FTM1_COMBINE=0;      //Function for Linked Channels (FTMx_COMBINE)
  FTM1_OUTINIT=0;
  FTM1_EXTTRIG=0;      //FTM External Trigger (FTMx_EXTTRIG)
  FTM1_POL=0;          //Channels Polarity (FTMx_POL)
                       //0 The channel polarity is active high.
                       //1 The channel polarity is active low.
  
  //Set Edge Aligned PWM
  FTM0_QDCTRL &=~FTM_QDCTRL_QUADEN_MASK;
  FTM1_QDCTRL &=~FTM_QDCTRL_QUADEN_MASK;
  //QUADEN is Bit 1, Set Quadrature Decoder Mode (QUADEN) Enable to 0,   (disabled)
  //FTM0_SC = 0x16; //Center Aligned PWM Select = 0, sets FTM Counter to operate in up counting mode,
  //it is field 5 of FTMx_SC (status control) - also setting the pre-scale bits here

  FTM0_INVCTRL=0;     //��ת����
  FTM0_SWOCTRL=0;     //����������F TM Software Output Control (FTMx_SWOCTRL)
  FTM0_PWMLOAD=0;     //FTM PWM Load
                      //BIT9: 0 Loading updated values is disabled.
                      //1 Loading updated values is enabled.
  FTM1_INVCTRL=0;     //��ת����
  FTM1_SWOCTRL=0;     //����������F TM Software Output Control (FTMx_SWOCTRL)
  FTM1_PWMLOAD=0;     //FTM PWM Load
                      //BIT9: 0 Loading updated values is disabled.
                      //1 Loading updated values is enabled.
  FTM0_CNTIN=0;        //Counter Initial Value
  FTM1_CNTIN=0;
  FTM0_MOD=4000;       //Modulo value,The EPWM period is determined by (MOD - CNTIN + 0x0001) 
                       //��������ʱ�ӳ�ʼ�����������Եõ�4��Ƶ��Ƶ�ʣ�ϵͳ60MƵ��ʱ��PWMƵ����15M,�Դ�����
                       //PMWƵ��=XϵͳƵ��/4/(2^FTM1_SC_PS)/FTM1_MOD
  FTM1_MOD=4000;
  
  FTM0_C4V=0;        //���� the pulse width(duty cycle) is determined by (CnV - CNTIN).
  FTM0_C5V=0;
  FTM0_C6V=0;
  FTM0_C7V=0;
  
  FTM1_C1V=0;
  
  FTM0_CNT=0;          //ֻ�е�16λ����
  FTM1_CNT=0;
}

//��������ʼ������
//
//

//void quad_init()
//{
    /*�����˿�ʱ��*/
    //SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;  
    /*ѡ��ܽŸ��ù���*/
//    LEFT_PHA  = PORT_PCR_MUX(0x6);//alt6 FTM���ܸ���
//    LEFT_PHB  = PORT_PCR_MUX(0x6);
//    RIGHT_PHA = PORT_PCR_MUX(0x6);
//    RIGHT_PHB = PORT_PCR_MUX(0x6);
    /*ʹ��FTM1��FTM2ʱ��*/
//    SIM_SCGC6|=SIM_SCGC6_FTM1_MASK;
//    SIM_SCGC3|=SIM_SCGC3_FTM2_MASK;
    
//    FTM1_MOD = 10000;//�ɸ�����Ҫ����
//    FTM2_MOD = 10000;//������ֵ
/*
    FTM1_CNTIN = 0;
    FTM2_CNTIN = 0;

    FTM1_MODE |= FTM_MODE_WPDIS_MASK; //��ֹд����
    FTM2_MODE |= FTM_MODE_WPDIS_MASK; //��ֹд����
    FTM1_MODE |= FTM_MODE_FTMEN_MASK; //FTMEN=1,�ر�TPM����ģʽ������FTM���й���
    FTM2_MODE |= FTM_MODE_FTMEN_MASK; //FTMEN=1,�ر�TPM����ģʽ������FTM���й���

    FTM1_QDCTRL &= ~FTM_QDCTRL_QUADMODE_MASK; //ѡ������ģʽΪA����B�����ģʽ
    FTM1_QDCTRL |= FTM_QDCTRL_QUADEN_MASK; //ʹ����������ģʽ
    FTM2_QDCTRL &= ~FTM_QDCTRL_QUADMODE_MASK; //ѡ������ģʽΪA����B�����ģʽ
    FTM2_QDCTRL |= FTM_QDCTRL_QUADEN_MASK; //ʹ����������ģʽ

    FTM1_SC |= FTM_SC_CLKS(3);  //ѡ���ⲿʱ��
//   FTM1_CONF |=FTM_CONF_BDMMODE(3); //�ɸ�����Ҫѡ��
    FTM2_SC |= FTM_SC_CLKS(3);
//   FTM2_CONF |=FTM_CONF_BDMMODE(3);
}*/