#ifndef _led_H
#define _led_H

#include "system.h"

/*  LEDʱ�Ӷ˿ڡ����Ŷ��� */
#define LED1_PORT 			GPIOB   
#define LED1_PIN 			GPIO_Pin_14
#define LED1_PORT_RCC		RCC_APB2Periph_GPIOB

#define LED1 PBout(14)  		


void LED_Init(void);


#endif
