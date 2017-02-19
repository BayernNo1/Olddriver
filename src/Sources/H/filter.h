#ifndef _FILTER_H_
#define _FILTER_H_
#include "common.h"
#include "includes.h"
extern struct CCD CCD1;
void filter(struct CCD *cdd);// unsigned char *data, unsigned char *filter_data);
void peakfilter(struct CCD *ccd);
int32 threshold(unsigned char *data, int32 average);
#endif