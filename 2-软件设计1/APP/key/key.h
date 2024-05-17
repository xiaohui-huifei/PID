
#ifndef _key_H
#define _key_H


#include "system.h"
 
#define KEY1_PIN   			GPIO_Pin_8    	
#define KEY2_PIN    		GPIO_Pin_11  	
#define KEY3_PIN    		GPIO_Pin_9    	
#define KEY4_PIN  			GPIO_Pin_12 

#define KEY_PORT 			GPIOC			

//使用位操作定义
#define KEY1 	PCin(8)
#define KEY2 	PCin(11)
#define KEY3 	PCin(9)
#define KEY4 	PCin(12)

//定义各个按键值  
#define KEY1_PRESS 		1
#define KEY2_PRESS		2
#define KEY3_PRESS		3
#define KEY4_PRESS		4
 
void KEY_Init(void);
u8 KEY_Scan(u8 mode);

#endif
