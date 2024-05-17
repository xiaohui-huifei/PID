//#include "stm32f10x.h"
//#include "pid.h"
//#include "ds18b20.h" // �������ͷ�ļ��а������¶ȶ�ȡ����

//// ����Ŀ���¶Ⱥ�H�ſ�������
//#define TARGET_TEMPERATURE 25.0f // Ŀ���¶ȣ�����Ϊ25���϶�
//#define H_BRIDGE_IN1 GPIO_Pin_0 // H�ſ�������IN1
//#define H_BRIDGE_IN2 GPIO_Pin_1 // H�ſ�������IN2

//// PID������ʵ��
//PID pid;

//// ��ʼ��ϵͳ
//void System_Init(void)
//{
//    // ��ʼ��GPIO����ʱ����ADC��
//    GPIO_Init();
//    TIM3_CH2_PWM_Init();
//    Adc_Init();
//    // ��ʼ��PID������
//    PID_Init();
//}

//// ������
//int main(void)
//{
//    // ϵͳ��ʼ��
//    System_Init();

//    // ��ѭ��
//    while (1)
//    {
//        // ��ȡ��ǰ�¶�
//        float current_temperature = DS18B20_GetTemperture();	

//        // ִ��PID����
//        float pid_output = PID_Calc();

//        // ����PID�������H��������·��PWM�ź�
//        if(pid_output > 0)
//        {
//            // ���²���
//            GPIO_SetBits(GPIO_Pin_6, H_BRIDGE_IN1); // ����H��IN1�ߵ�ƽ
//            GPIO_ResetBits(GPIO_Pin_7, H_BRIDGE_IN2); // ����H��IN2�͵�ƽ
//            TIM_SetCompare1(TIM1, pid_output); // ����PWMռ�ձ�
//        }
//        else
//        {
//            // ���²���
//            GPIO_ResetBits(GPIO_Pin_6, H_BRIDGE_IN1); // ����H��IN1�͵�ƽ
//            GPIO_SetBits(GPIO_Pin_7, H_BRIDGE_IN2); // ����H��IN2�ߵ�ƽ
//            TIM_SetCompare1(TIM1, -pid_output); // ����PWMռ�ձ�
//        }

//    }
//}
