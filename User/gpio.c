#include "gpio.h"


 /**
  * @brief  ��ʼ�����Ƶ�IO
  * @param  ��
  * @retval ��
  */
void SYS_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( VALVE1_GPIO_CLK|
	                           VALVE2_GPIO_CLK|
	                           VALVE3_GPIO_CLK|
														 RELAY1_GPIO_CLK|
														 RELAY2_GPIO_CLK, ENABLE); 


		/*��������ģʽΪ���ģʽ*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*��������Ϊ����ģʽ*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

		/*������������Ϊ2MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		
		GPIO_InitStructure.GPIO_Pin = VALVE1_PIN;	
		/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
		GPIO_Init(VALVE1_GPIO_PORT, &GPIO_InitStructure);	
		
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = VALVE2_PIN;	
    GPIO_Init(VALVE2_GPIO_PORT, &GPIO_InitStructure);	
    
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = VALVE3_PIN;	
    GPIO_Init(VALVE3_GPIO_PORT, &GPIO_InitStructure);	
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = RELAY1_PIN;	
    GPIO_Init(RELAY1_GPIO_PORT, &GPIO_InitStructure);	
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = RELAY2_PIN;	
    GPIO_Init(RELAY2_GPIO_PORT, &GPIO_InitStructure);	
		
		/*ȫ������Ϊ�͵�ƽ*/
		GPIO_ALL_INIT;		
}
