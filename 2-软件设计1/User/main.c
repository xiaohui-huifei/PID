#include "system.h"
#include "app_demo.h" 


int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	
	appdemo_show();
	
	while(1)
	{ 
			
	}
}
