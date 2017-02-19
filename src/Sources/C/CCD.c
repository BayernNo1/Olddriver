#include "includes.h"


//CCD                                                 //不甚明了
uint8 ccd_ad[128];
int ccd_ad5[128];
int ccd_ad2[128];
int ccd_ad6[128];
int ccd_ad7[128];
int16 d_ccd[128];
int16 d1_ccd[128];
uint8 count_ccd;
uint8 scan_ok;
uint16 temp_int;



void ccd_init()
{
    gpio_init(PTB_BASE_PTR,2,1,0); //CCD1 SI
    gpio_init(PTB_BASE_PTR,0,1,0); //CCD1 CLK
    //20161230 晚 只调了CCD1，CCD2和CCD3都没调
    gpio_init(PTB_BASE_PTR,10,1,0); //CCD2 CLK
    gpio_init(PTB_BASE_PTR,20,1,0); //CCD2 SI
    gpio_init(PTB_BASE_PTR,22,1,0);//CCD3 CLK
    gpio_init(PTC_BASE_PTR,1,1,0);//CCD3 SI
    gpio_init(PTA_BASE_PTR,17,0,0);//hongwai1
    gpio_init(PTD_BASE_PTR,1,0,0);//hongwai2
    gpio_init(PTA_BASE_PTR,19,1,1); //led
    
}

void delay()
{
    unsigned int i;
    for(i=0; i<10; i++)
    {
    asm("nop");
    }
}

void CCD_start(void)
{
    unsigned char i;
    TSL1401_SI(1);         /* SI  = 1 */
    delay();
    TSL1401_CLK(1);        /* CLK = 1 */
    delay();
    TSL1401_SI(0);         /* SI  = 0 */
    delay();
    TSL1401_CLK(0);        /* CLK = 0 */
    for(i=0; i<127; i++)
    {
        delay();
        delay();
        TSL1401_CLK(1);    /* CLK = 1 */
        delay();
        delay();
        TSL1401_CLK(0);    /* CLK = 0 */
    }
    delay();
    delay();
    TSL1401_CLK(1);        /* CLK = 1 */
    delay();
    delay();
    TSL1401_CLK(0);        /* CLK = 0 */
}

void CCD2_start(void)
{
    unsigned char i;
    TSL1401_SI2(1);         /* SI  = 1 */
    delay();
    TSL1401_CLK2(1);        /* CLK = 1 */
    delay();
    TSL1401_SI2(0);         /* SI  = 0 */
    delay();
    TSL1401_CLK2(0);        /* CLK = 0 */
    for(i=0; i<127; i++)
    {
        delay();
        delay();
        TSL1401_CLK2(1);    /* CLK = 1 */
        delay();
        delay();
        TSL1401_CLK2(0);    /* CLK = 0 */
    }
    delay();
    delay();
    TSL1401_CLK2(1);        /* CLK = 1 */
    delay();
    delay();
    TSL1401_CLK2(0);        /* CLK = 0 */
}

void CCD1_scan(void)
{
    uint8 i;
    //开始SI
    TSL1401_SI(0) ;
    TSL1401_CLK(0);
    delay();
    TSL1401_SI(1);
    delay();
    TSL1401_CLK(1);
    delay();
    TSL1401_SI(0);
    delay();
    count_ccd = 1;
    TSL1401_CLK(0);
    //采集第2~128个点
    for(i=0; i<128; i++)
    {
        delay();
        TSL1401_CLK(1);
        delay();
        //temp_int=adc_once(1, 8, 12); //老板子
        temp_int=hw_ad_once(0, 13, 12); //新板子
        CCD1.data [i] = (byte)(temp_int>>4);
        //cd_ad[i] = (byte)(temp_int);
        TSL1401_CLK(0);
        count_ccd++;
    }
    //发送第129个clk
    delay();
    TSL1401_CLK(1);
    delay();
    TSL1401_CLK(0);
    delay();
}

void CCD2_scan(void)
{
    uint8 i;
    //开始SI
    TSL1401_SI2(0) ;
    TSL1401_CLK2(0);
    delay();
    TSL1401_SI2(1);
    delay();
    TSL1401_CLK2(1);
    delay();
    TSL1401_SI2(0);
    delay();
    count_ccd = 2;
    TSL1401_CLK2(0);
    //采集第2~128个点
    for(i=0; i<128; i++)
    {
        delay();
        TSL1401_CLK2(1);
        delay();
        temp_int=hw_ad_once(1, 15, 12);
        ccd_ad2[i] = (byte)(temp_int>>4);
        TSL1401_CLK2(0);
        count_ccd++;
    }
    //发送第129个clk
    delay();
    TSL1401_CLK2(1);
    delay();
    TSL1401_CLK2(0);
    delay();
    scan_ok=1;
}