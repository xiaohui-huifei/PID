

#include "app_demo.h"
#include "SysTick.h"
#include "key.h"
#include "lcd1602.h"
#include "pcf8591.h"
#include "ds18b20.h"
#include "led.h"
#include "beep.h"
#include "pid.h"
#include "pwm.h" // 引入PWM输出相关的头文件
#include "stm32f10x_tim.h" // 包含控制定时器的头文件

unsigned int wd;
	unsigned int set =30;
unsigned int sz=0;
unsigned int on=0;
unsigned int num=0;
//相关控制模块管脚定义
#define JW	PBout(12)
#define JR 	PBout(13)
#define PERIOD    400 // 定义PWM周期
#define PRESCALER 36000 // 定义PWM预分频值

float adcx;
//float adc = round(adcx * 10) / 10;

void ctrl_pin_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13;  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	   /* 初始化GPIO */
	GPIO_SetBits(GPIOB,GPIO_Pin_12);   
	GPIO_SetBits(GPIOB,GPIO_Pin_13);   
}

//区间映射
u8 cal_map(u8 x, u8 in_min, u8 in_max, u8 out_min, u8 out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



//系统初始界面显示
void sys_open_show(void)
{
	lcd1602_clear();
	lcd1602_show_string(0,0,"    Temp:    c    ");
	lcd1602_show_string(0,1,"     Set:  c    ");
}

//系统数据获取
void sys_data_get(void)
{
	static u8 i=0;

	while(1)
	{
		adcx=Get_adcaverage(ADC_Channel_1,10);
		pid.Pv=DS18B20_GetTemperture(adcx);
		//温度获取
		i++;
		if(i%10==0)
			wd=DS18B20_GetTemperture(adcx);

		break;
	}	
}

//系统数据显示
void sys_data_show(void)
{
		//温度显示
		lcd1602_show_nums(9,0,wd,2,0);
		PID_Calc();
		if(sz==1)
		{
			//温度阈值显示
			lcd1602_show_nums(9,1,set,2,0);
		}
		else
		{
			 lcd1602_show_num(9,1,' ',0);
			 lcd1602_show_num(10,1,' ',0);
		}

}

//系统数据设置
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

//系统功能控制
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
//应用控制系统
// 在主循环中调用PID_Calc()函数，以计算PID控制器的输出值
void appdemo_show(void)
{
    Time_init(); // 初始化定时器
    KEY_Init();
    BEEP_Init();
    Adc_Init();
    ctrl_pin_init();
    pcf8591_init();
    lcd1602_init(); // LCD1602初始化
    PID_Init();
    wd = DS18B20_GetTemperture(adcx);
    sys_open_show(); // 系统初始界面显示
    TimePwm_init(PERIOD - 1, PRESCALER); // 初始化PWM输出

    while (1)
    {
        sys_data_get(); // 系统数据获取
			
         pid.Sv=set; // 用户设定温度
        // 在每次循环中调用PID_Calc()函数，计算PID控制器的输出值
        PID_Calc();
        
        // 根据PID控制器的输出值更新PWM的占空比
        num = (((pid.OUT * PERIOD) / pid.pwmcycle) - 1);
        TIM_SetCompare2(TIM3, num);
        
        // 更新LCD上显示的系统数据
        sys_data_show(); 
        
        sys_data_set(); // 系统数据设置
        sys_fun_ctrl(); // 系统功能控制
    }
}
