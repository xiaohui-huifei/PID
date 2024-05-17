/*
作者：嗨小易（QQ：3443792007）
版权：本教程版权归嗨小易（QQ：3443792007）所有，未经授权不得转载、摘编或用于其他商业用途！！！
	  一经发现，后果自负！！！
*/

#ifndef _ds18b20_H
#define _ds18b20_H

#include "system.h"
#include "math.h"


#define B 3950
#define RN 4.7
#define TN 298.15
#define BaseVol 3.3



////IO操作函数											   



float DS18B20_GetTemperture(u16 adcx);	//获取温度
void Adc_Init (void);//初始化adc
float Get_adc(u8 ch);//获得ADC的值
u16 Get_adcaverage(u8 ch,u8 times);




#endif

