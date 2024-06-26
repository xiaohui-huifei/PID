#ifndef _iic_H
#define _iic_H

#include "system.h"

/*  IIC_SCL时钟端口、引脚定义 */
#define IIC_SCL_PORT 			GPIOB   
#define IIC_SCL_PIN 			(GPIO_Pin_3)
#define IIC_SCL_PORT_RCC		RCC_APB2Periph_GPIOB

/*  IIC_SDA时钟端口、引脚定义 */
#define IIC_SDA_PORT 			GPIOB  
#define IIC_SDA_PIN 			(GPIO_Pin_4)
#define IIC_SDA_PORT_RCC		RCC_APB2Periph_GPIOB

//IO操作函数	 
#define IIC_SCL    PBout(3) //SCL
#define IIC_SDA    PBout(4) //SDA	 
#define READ_SDA   PBin(4)  //输入SDA

//IIC所有操作函数
void iic_init(void);            //初始化IIC的IO口				 
void iic_start(void);			//发送IIC开始信号
void iic_stop(void);	  		//发送IIC停止信号
void iic_write_byte(u8 txd);	//IIC发送一个字节
u8 iic_read_byte(u8 ack);		//IIC读取一个字节
u8 iic_wait_ack(void); 			//IIC等待ACK信号
void iic_ack(void);				//IIC发送ACK信号
void iic_nack(void);			//IIC不发送ACK信号
void iic_send_ack(u8 b_ACK);


#endif
