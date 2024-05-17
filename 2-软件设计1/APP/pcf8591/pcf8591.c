/*
作者：嗨小易（QQ：3443792007）
版权：本教程版权归嗨小易（QQ：3443792007）所有，未经授权不得转载、摘编或用于其他商业用途！！！
	  一经发现，后果自负！！！
*/

#include "pcf8591.h"
#include "iic.h"

void pcf8591_init(void)
{
	iic_init();
}

void pcf8591_write_data(u8 dat)
{
	iic_start();
	iic_write_byte(PCF8591_WRITEADDR);//发送写器件地址
	iic_wait_ack();
	iic_write_byte(0x40|dat); //发送控制寄存器
	iic_wait_ack();
	iic_stop();	
}

u8 pcf8591_read_data(void)
{
	u8 value=0;

	iic_start();
	iic_write_byte(PCF8591_READADDR);
	iic_wait_ack();
	value=iic_read_byte(0);
	iic_stop();
	return value;
}

//根据指定通道读取ADC数据
//ch：0-3
u8 pcf8591_read_adcvalue(u8 ch)
{
	u8 temp=0;
	pcf8591_write_data(ch);
	temp=pcf8591_read_data();
	return temp;		
}

void pcf8591_set_dac_out(u8 dacnum)
{
	iic_start();
	iic_write_byte(PCF8591_WRITEADDR);//发送写器件地址
	iic_wait_ack();
	iic_write_byte(0x40);
	iic_wait_ack();
	iic_write_byte(dacnum);
	iic_wait_ack();
	iic_stop();		
}
