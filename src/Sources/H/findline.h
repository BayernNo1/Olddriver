#ifndef _FINDLINE_H_
#define _FINDLINE_H_
#include "common.h"
#include "includes.h"

void findline(struct CCD *ccd,int num);
#define edge 8 // 跳变沿差值（待实际测量）
#define edgecount 5 // 跳变沿检测计数（待实际测量）
extern struct CCD CCD1;

#endif