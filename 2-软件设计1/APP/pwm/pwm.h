#ifndef _pwm_H
#define _pwm_H

#include "SysTick.h" // 引入系统相关的头文件

// 函数声明
void Time_init(void); // 初始化定时器
void TimePwm_init(int arr,int psc); // 初始化定时器和PWM

#endif