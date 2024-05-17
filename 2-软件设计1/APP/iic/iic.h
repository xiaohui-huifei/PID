#ifndef _iic_H
#define _iic_H

#include "system.h"

/*  IIC_SCLʱ�Ӷ˿ڡ����Ŷ��� */
#define IIC_SCL_PORT 			GPIOB   
#define IIC_SCL_PIN 			(GPIO_Pin_3)
#define IIC_SCL_PORT_RCC		RCC_APB2Periph_GPIOB

/*  IIC_SDAʱ�Ӷ˿ڡ����Ŷ��� */
#define IIC_SDA_PORT 			GPIOB  
#define IIC_SDA_PIN 			(GPIO_Pin_4)
#define IIC_SDA_PORT_RCC		RCC_APB2Periph_GPIOB

//IO��������	 
#define IIC_SCL    PBout(3) //SCL
#define IIC_SDA    PBout(4) //SDA	 
#define READ_SDA   PBin(4)  //����SDA

//IIC���в�������
void iic_init(void);            //��ʼ��IIC��IO��				 
void iic_start(void);			//����IIC��ʼ�ź�
void iic_stop(void);	  		//����IICֹͣ�ź�
void iic_write_byte(u8 txd);	//IIC����һ���ֽ�
u8 iic_read_byte(u8 ack);		//IIC��ȡһ���ֽ�
u8 iic_wait_ack(void); 			//IIC�ȴ�ACK�ź�
void iic_ack(void);				//IIC����ACK�ź�
void iic_nack(void);			//IIC������ACK�ź�
void iic_send_ack(u8 b_ACK);


#endif
