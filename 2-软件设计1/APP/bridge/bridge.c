//#include "stm32f10x.h"
//#include "pid.h"
//#include "ds18b20.h" // 假设这个头文件中包含了温度读取函数

//// 定义目标温度和H桥控制引脚
//#define TARGET_TEMPERATURE 25.0f // 目标温度，假设为25摄氏度
//#define H_BRIDGE_IN1 GPIO_Pin_0 // H桥控制引脚IN1
//#define H_BRIDGE_IN2 GPIO_Pin_1 // H桥控制引脚IN2

//// PID控制器实例
//PID pid;

//// 初始化系统
//void System_Init(void)
//{
//    // 初始化GPIO、定时器、ADC等
//    GPIO_Init();
//    TIM3_CH2_PWM_Init();
//    Adc_Init();
//    // 初始化PID控制器
//    PID_Init();
//}

//// 主程序
//int main(void)
//{
//    // 系统初始化
//    System_Init();

//    // 主循环
//    while (1)
//    {
//        // 读取当前温度
//        float current_temperature = DS18B20_GetTemperture();	

//        // 执行PID计算
//        float pid_output = PID_Calc();

//        // 根据PID输出控制H桥驱动电路和PWM信号
//        if(pid_output > 0)
//        {
//            // 升温操作
//            GPIO_SetBits(GPIO_Pin_6, H_BRIDGE_IN1); // 设置H桥IN1高电平
//            GPIO_ResetBits(GPIO_Pin_7, H_BRIDGE_IN2); // 设置H桥IN2低电平
//            TIM_SetCompare1(TIM1, pid_output); // 设置PWM占空比
//        }
//        else
//        {
//            // 降温操作
//            GPIO_ResetBits(GPIO_Pin_6, H_BRIDGE_IN1); // 设置H桥IN1低电平
//            GPIO_SetBits(GPIO_Pin_7, H_BRIDGE_IN2); // 设置H桥IN2高电平
//            TIM_SetCompare1(TIM1, -pid_output); // 设置PWM占空比
//        }

//    }
//}
