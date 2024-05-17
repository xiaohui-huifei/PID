#include "iic.h"
#include "SysTick.h"

/*******************************************************************************
* �� �� ��         : IIC_Init
* ��������		   : IIC��ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void iic_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(IIC_SCL_PORT_RCC|IIC_SDA_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=IIC_SCL_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(IIC_SCL_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_PIN;
	GPIO_Init(IIC_SDA_PORT,&GPIO_InitStructure);
	
	IIC_SCL=1;
	IIC_SDA=1;	
}

/*******************************************************************************
* �� �� ��         : SDA_OUT
* ��������		   : SDA�������	   
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void SDA_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(IIC_SDA_PORT,&GPIO_InitStructure);
}

/*******************************************************************************
* �� �� ��         : SDA_IN
* ��������		   : SDA��������	   
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void SDA_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(IIC_SDA_PORT,&GPIO_InitStructure);
}

/*******************************************************************************
* �� �� ��       : iic_start
* ��������		 : ����IIC��ʼ�ź�
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void iic_start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
//	delay_10us(1);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
//	delay_10us(1);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ��������
}

/*******************************************************************************
* �� �� ��         : iic_stop
* ��������		   : ����IICֹͣ�ź�   
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void iic_stop(void)
{	
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	IIC_SCL=1; 
//	delay_10us(1); 
	IIC_SDA=1;//����I2C���߽����ź�
//	delay_10us(1);		
}

/*******************************************************************************
* �� �� ��         : iic_ack
* ��������		   : ����ACKӦ��  
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void iic_ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
//	delay_10us(1);
	IIC_SCL=1;
//	delay_10us(1);
	IIC_SCL=0;
}

/*******************************************************************************
* �� �� ��         : iic_nack
* ��������		   : ����NACK��Ӧ��  
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void iic_nack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
//	delay_10us(1);
	IIC_SCL=1;
//	delay_10us(1);
	IIC_SCL=0;
}


/*******************************************************************************
* �� �� ��         : iic_wait_ack
* ��������		   : �ȴ�Ӧ���źŵ���   
* ��    ��         : ��
* ��    ��         : 1������Ӧ��ʧ��
        			 0������Ӧ��ɹ�
*******************************************************************************/
u8 iic_wait_ack(void)
{
	u8 tempTime=0;
	
	IIC_SDA=1;
//	delay_10us(1);
	SDA_IN();      //SDA����Ϊ����  	   
	IIC_SCL=1;
//	delay_10us(1);	 
	while(READ_SDA)
	{
		tempTime++;
		if(tempTime>250)
		{
			iic_stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;	
}

/*******************************************************************************
* �� �� ��         : iic_write_byte
* ��������		   : IIC����һ���ֽ� 
* ��    ��         : dat������һ���ֽ�
* ��    ��         : ��
*******************************************************************************/
void iic_write_byte(u8 dat)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        if((dat&0x80)>0) //0x80  1000 0000
			IIC_SDA=1;
		else
			IIC_SDA=0;
        dat<<=1; 	  
//		delay_10us(1);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
//		delay_10us(1); 
		IIC_SCL=0;	
//		delay_10us(1);
    }	 
}

/*******************************************************************************
* �� �� ��         : iic_read_byte
* ��������		   : IIC��һ���ֽ� 
* ��    ��         : ack=1ʱ������ACK��ack=0������nACK 
* ��    ��         : Ӧ����Ӧ��
*******************************************************************************/
u8 iic_read_byte(u8 ack)
{
	u8 i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
//        delay_10us(1);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
//		delay_10us(1); 
    }					 
    if (!ack)
        iic_nack();//����nACK
    else
        iic_ack(); //����ACK   
    return receive;
}

