/*
���ߣ���С�ף�QQ��3443792007��
��Ȩ�����̳̰�Ȩ����С�ף�QQ��3443792007�����У�δ����Ȩ����ת�ء�ժ�������������ҵ��;������
	  һ�����֣�����Ը�������
*/

#ifndef __PCF8591_H
#define __PCF8591_H

#include "system.h"


#define PCF8591_WRITEADDR 0x90	   //д��ַ
#define PCF8591_READADDR  0x91	   //����ַ

void pcf8591_init(void);
void pcf8591_write_data(u8 dat);
u8 pcf8591_read_data(void);
u8 pcf8591_read_adcvalue(u8 ch);
void pcf8591_set_dac_out(u8 dacnum);
#endif
