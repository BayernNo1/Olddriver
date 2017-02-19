#include "includes.h"

#define TSL1401_CLK(x) gpio_ctrl(PTB_BASE_PTR, 0, x)
#define TSL1401_SI(x) gpio_ctrl(PTB_BASE_PTR, 2, x)
#define TSL1401_CLK2(x) gpio_ctrl(PTB_BASE_PTR, 20, x)
#define TSL1401_SI2(x) gpio_ctrl(PTB_BASE_PTR, 10, x)
#define TSL1401_CLK3(x) gpio_ctrl(PTC_BASE_PTR, 1, x)
#define TSL1401_SI3(x) gpio_ctrl(PTB_BASE_PTR, 22, x)

extern uint8 ccd_ad[128];
void CCD1_scan(void);
void CCD2_scan(void);
extern void ccd_init(void);
void CCD_start(void);
void delay();
void CCD2_start(void);


extern struct CCD CCD1;