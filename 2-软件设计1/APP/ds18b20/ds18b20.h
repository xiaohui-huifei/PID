/*
���ߣ���С�ף�QQ��3443792007��
��Ȩ�����̳̰�Ȩ����С�ף�QQ��3443792007�����У�δ����Ȩ����ת�ء�ժ�������������ҵ��;������
	  һ�����֣�����Ը�������
*/

#ifndef _ds18b20_H
#define _ds18b20_H

#include "system.h"
#include "math.h"


#define B 3950
#define RN 4.7
#define TN 298.15
#define BaseVol 3.3



////IO��������											   



float DS18B20_GetTemperture(u16 adcx);	//��ȡ�¶�
void Adc_Init (void);//��ʼ��adc
float Get_adc(u8 ch);//���ADC��ֵ
u16 Get_adcaverage(u8 ch,u8 times);




#endif

