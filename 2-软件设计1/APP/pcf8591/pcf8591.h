/*
作者：嗨小易（QQ：3443792007）
版权：本教程版权归嗨小易（QQ：3443792007）所有，未经授权不得转载、摘编或用于其他商业用途！！！
	  一经发现，后果自负！！！
*/

#ifndef __PCF8591_H
#define __PCF8591_H

#include "system.h"


#define PCF8591_WRITEADDR 0x90	   //写地址
#define PCF8591_READADDR  0x91	   //读地址

void pcf8591_init(void);
void pcf8591_write_data(u8 dat);
u8 pcf8591_read_data(void);
u8 pcf8591_read_adcvalue(u8 ch);
void pcf8591_set_dac_out(u8 dacnum);
#endif
