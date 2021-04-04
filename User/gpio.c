#include "gpio.h"


 /**
  * @brief  初始化控制的IO
  * @param  无
  * @retval 无
  */
void SYS_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd ( VALVE1_GPIO_CLK|
	                           VALVE2_GPIO_CLK|
	                           VALVE3_GPIO_CLK|
														 RELAY1_GPIO_CLK|
														 RELAY2_GPIO_CLK, ENABLE); 


		/*设置引脚模式为输出模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*设置引脚的输出类型为推挽输出*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*设置引脚为上拉模式*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

		/*设置引脚速率为2MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		
		/*选择要控制的GPIO引脚*/															   
		
		GPIO_InitStructure.GPIO_Pin = VALVE1_PIN;	
		/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
		GPIO_Init(VALVE1_GPIO_PORT, &GPIO_InitStructure);	
		
    /*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = VALVE2_PIN;	
    GPIO_Init(VALVE2_GPIO_PORT, &GPIO_InitStructure);	
    
    /*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = VALVE3_PIN;	
    GPIO_Init(VALVE3_GPIO_PORT, &GPIO_InitStructure);	
		
		/*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = RELAY1_PIN;	
    GPIO_Init(RELAY1_GPIO_PORT, &GPIO_InitStructure);	
		
		/*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = RELAY2_PIN;	
    GPIO_Init(RELAY2_GPIO_PORT, &GPIO_InitStructure);	
		
		/*全部设置为低电平*/
		GPIO_ALL_INIT;		
}
