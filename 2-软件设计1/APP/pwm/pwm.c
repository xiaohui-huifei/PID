#include "pwm.h" // 引入PWM输出相关的头文件
#include "pid.h" // 引入PID控制相关的头文件


// 初始化定时器函数
void Time_init(void) 
{
    NVIC_InitTypeDef  NVIC_InitStructure; // 定义NVIC初始化结构体
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; // 定义定时器基本初始化结构体
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 使能TIM2时钟
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); // 设置NVIC优先级分组
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; // 设置TIM2中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; // 设置响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // 使能中断通道
    NVIC_Init(&NVIC_InitStructure); // 初始化NVIC
    
    TIM_TimeBaseStructure.TIM_Period = 1000; // 设置自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1); // 设置时钟预分频数
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); // 初始化定时器基本结构
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 使能定时器更新中断
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 清除TIM2的中断待处理位
    TIM_Cmd(TIM2,ENABLE); // 使能TIM2
}

// TIM2中断服务函数
void TIM2_IRQHandler(void) 
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)) // 检查TIM2更新中断发生与否
    {
        pid.C1ms++; // pid中的1ms计数器递增
        //Alert(); // 调用报警函数，根据温湿度数据控制LED和蜂鸣器
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 清除TIM2中断标志位
    }
}

// 初始化定时器和PWM函数
void TimePwm_init(int arr,int psc) 
{
    GPIO_InitTypeDef GPIO_InitStructure; // 定义GPIO初始化结构体
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; // 定义定时器基本初始化结构体
    TIM_OCInitTypeDef  TIM_OCInitStructure; // 定义定时器输出比较初始化结构体
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE); // 使能GPIOB和AFIO复用功能时钟
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); // 重映射TIM3部分引脚
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; // 设置GPIOB的第5个引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 设置为复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 设置GPIO速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure); // 初始化GPIO
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // 使能TIM3时钟
    
    TIM_TimeBaseStructure.TIM_Period = arr; // 设置自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = psc; // 设置时钟预分频数
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); // 初始化定时器基本结构
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; // 设置为PWM模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 使能输出
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; // 输出极性为低
		//TIM_OCInitStructure.TIM_Pulse = arr * 0.75; // 设置占空比为75%
    TIM_OC2Init(TIM3, &TIM_OCInitStructure); // 初始化定时器输出比较结构
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); // 使能TIM3预装载寄存器
    TIM_Cmd(TIM3, ENABLE); // 使能TIM3
}

