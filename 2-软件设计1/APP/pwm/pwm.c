#include "pwm.h" // ����PWM�����ص�ͷ�ļ�
#include "pid.h" // ����PID������ص�ͷ�ļ�


// ��ʼ����ʱ������
void Time_init(void) 
{
    NVIC_InitTypeDef  NVIC_InitStructure; // ����NVIC��ʼ���ṹ��
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; // ���嶨ʱ��������ʼ���ṹ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // ʹ��TIM2ʱ��
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); // ����NVIC���ȼ�����
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; // ����TIM2�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // ������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; // ������Ӧ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // ʹ���ж�ͨ��
    NVIC_Init(&NVIC_InitStructure); // ��ʼ��NVIC
    
    TIM_TimeBaseStructure.TIM_Period = 1000; // �����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1); // ����ʱ��Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); // ��ʼ����ʱ�������ṹ
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // ʹ�ܶ�ʱ�������ж�
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // ���TIM2���жϴ�����λ
    TIM_Cmd(TIM2,ENABLE); // ʹ��TIM2
}

// TIM2�жϷ�����
void TIM2_IRQHandler(void) 
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)) // ���TIM2�����жϷ������
    {
        pid.C1ms++; // pid�е�1ms����������
        //Alert(); // ���ñ���������������ʪ�����ݿ���LED�ͷ�����
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // ���TIM2�жϱ�־λ
    }
}

// ��ʼ����ʱ����PWM����
void TimePwm_init(int arr,int psc) 
{
    GPIO_InitTypeDef GPIO_InitStructure; // ����GPIO��ʼ���ṹ��
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; // ���嶨ʱ��������ʼ���ṹ��
    TIM_OCInitTypeDef  TIM_OCInitStructure; // ���嶨ʱ������Ƚϳ�ʼ���ṹ��
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE); // ʹ��GPIOB��AFIO���ù���ʱ��
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); // ��ӳ��TIM3��������
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; // ����GPIOB�ĵ�5������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // ����Ϊ�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // ����GPIO�ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure); // ��ʼ��GPIO
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // ʹ��TIM3ʱ��
    
    TIM_TimeBaseStructure.TIM_Period = arr; // �����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc; // ����ʱ��Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); // ��ʼ����ʱ�������ṹ
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; // ����ΪPWMģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // ʹ�����
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; // �������Ϊ��
		//TIM_OCInitStructure.TIM_Pulse = arr * 0.75; // ����ռ�ձ�Ϊ75%
    TIM_OC2Init(TIM3, &TIM_OCInitStructure); // ��ʼ����ʱ������ȽϽṹ
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); // ʹ��TIM3Ԥװ�ؼĴ���
    TIM_Cmd(TIM3, ENABLE); // ʹ��TIM3
}

