#ifndef _pwm_H
#define _pwm_H

#include "SysTick.h" // ����ϵͳ��ص�ͷ�ļ�

// ��������
void Time_init(void); // ��ʼ����ʱ��
void TimePwm_init(int arr,int psc); // ��ʼ����ʱ����PWM

#endif