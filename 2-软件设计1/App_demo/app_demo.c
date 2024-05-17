

#include "app_demo.h"
#include "SysTick.h"
#include "key.h"
#include "lcd1602.h"
#include "pcf8591.h"
#include "ds18b20.h"
#include "led.h"
#include "beep.h"
#include "pid.h"
#include "pwm.h" // ����PWM�����ص�ͷ�ļ�
#include "stm32f10x_tim.h" // �������ƶ�ʱ����ͷ�ļ�

unsigned int wd;
	unsigned int set =30;
unsigned int sz=0;
unsigned int on=0;
unsigned int num=0;
//��ؿ���ģ��ܽŶ���
#define JW	PBout(12)
#define JR 	PBout(13)
#define PERIOD    400 // ����PWM����
#define PRESCALER 36000 // ����PWMԤ��Ƶֵ

float adcx;
//float adc = round(adcx * 10) / 10;

void ctrl_pin_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13;  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	GPIO_SetBits(GPIOB,GPIO_Pin_12);   
	GPIO_SetBits(GPIOB,GPIO_Pin_13);   
}

//����ӳ��
u8 cal_map(u8 x, u8 in_min, u8 in_max, u8 out_min, u8 out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



//ϵͳ��ʼ������ʾ
void sys_open_show(void)
{
	lcd1602_clear();
	lcd1602_show_string(0,0,"    Temp:    c    ");
	lcd1602_show_string(0,1,"     Set:  c    ");
}

//ϵͳ���ݻ�ȡ
void sys_data_get(void)
{
	static u8 i=0;

	while(1)
	{
		adcx=Get_adcaverage(ADC_Channel_1,10);
		pid.Pv=DS18B20_GetTemperture(adcx);
		//�¶Ȼ�ȡ
		i++;
		if(i%10==0)
			wd=DS18B20_GetTemperture(adcx);

		break;
	}	
}

//ϵͳ������ʾ
void sys_data_show(void)
{
		//�¶���ʾ
		lcd1602_show_nums(9,0,wd,2,0);
		PID_Calc();
		if(sz==1)
		{
			//�¶���ֵ��ʾ
			lcd1602_show_nums(9,1,set,2,0);
		}
		else
		{
			 lcd1602_show_num(9,1,' ',0);
			 lcd1602_show_num(10,1,' ',0);
		}

}

//ϵͳ��������
void sys_data_set(void)
{
	u8 key=0;
	
	key=KEY_Scan(0);

	

	if(key==KEY1_PRESS)
	{
		if(set<99)
		{
			set++;
		}			
	}
	else if(key==KEY2_PRESS)
	{
		if(set>0)
		{
			set--;
		}			
	}
	else if(key==KEY3_PRESS)
	{
		if(sz==0)
		{
			sz=1;
			on=1;
		}	
    else if(sz==1)
		{
			sz=0;
		}				
	}
}

//ϵͳ���ܿ���
void sys_fun_ctrl(void)
{
	if(sz==1)
	{
		if(set>=50||set<=0)
		{ 
			BEEP=0;
		}
		else
		{
			BEEP=1;
		}
	}

	
	
	if(on==1)
	{
		if(sz==0)
		{
			if(wd>set)
			{ 
				JW=0;
				JR=1;
			}
			else if(wd<set)
			{ 
				JR=0;
				JW=1;
			}
			else
			{
				JW=1;
				JR=1;
			}
		}
		else
		{
			JW=1;
			JR=1;
		}
	}
//	while(1)
//	{
//	PID_Calc();
//		num=(((pid.OUT*PERIOD)/pid.pwmcycle)-1);
//		TIM_SetCompare2(TIM3,num);
//		sys_data_show();
		//while(Get_adc());
                                                                                                                                                                                 
//	} 
}
//Ӧ�ÿ���ϵͳ
// ����ѭ���е���PID_Calc()�������Լ���PID�����������ֵ
void appdemo_show(void)
{
    Time_init(); // ��ʼ����ʱ��
    KEY_Init();
    BEEP_Init();
    Adc_Init();
    ctrl_pin_init();
    pcf8591_init();
    lcd1602_init(); // LCD1602��ʼ��
    PID_Init();
    wd = DS18B20_GetTemperture(adcx);
    sys_open_show(); // ϵͳ��ʼ������ʾ
    TimePwm_init(PERIOD - 1, PRESCALER); // ��ʼ��PWM���

    while (1)
    {
        sys_data_get(); // ϵͳ���ݻ�ȡ
			
         pid.Sv=set; // �û��趨�¶�
        // ��ÿ��ѭ���е���PID_Calc()����������PID�����������ֵ
        PID_Calc();
        
        // ����PID�����������ֵ����PWM��ռ�ձ�
        num = (((pid.OUT * PERIOD) / pid.pwmcycle) - 1);
        TIM_SetCompare2(TIM3, num);
        
        // ����LCD����ʾ��ϵͳ����
        sys_data_show(); 
        
        sys_data_set(); // ϵͳ��������
        sys_fun_ctrl(); // ϵͳ���ܿ���
    }
}
