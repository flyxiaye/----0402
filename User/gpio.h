#ifndef _GPIO_H_
#define _GPIO_H_

#include "stm32f4xx.h"

#define VALVE1_PIN                  GPIO_Pin_10             
#define VALVE1_GPIO_PORT            GPIOF                            
#define VALVE1_GPIO_CLK             RCC_AHB1Periph_GPIOF

#define VALVE2_PIN                  GPIO_Pin_1                 
#define VALVE2_GPIO_PORT            GPIOC                  
#define VALVE2_GPIO_CLK             RCC_AHB1Periph_GPIOC

#define VALVE3_PIN                  GPIO_Pin_3               
#define VALVE3_GPIO_PORT            GPIOC                 
#define VALVE3_GPIO_CLK             RCC_AHB1Periph_GPIOC

#define RELAY1_PIN                  GPIO_Pin_13               
#define RELAY1_GPIO_PORT            GPIOF    
#define RELAY1_GPIO_CLK             RCC_AHB1Periph_GPIOF


#define RELAY2_PIN                  GPIO_Pin_9               
#define RELAY2_GPIO_PORT            GPIOC    
#define RELAY2_GPIO_CLK             RCC_AHB1Periph_GPIOC

#define ON  0
#define OFF 1


/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//设置为高电平
#define digitalLo(p,i)			 {p->BSRRH=i;}		//输出低电平
#define digitalToggle(p,i)	 {p->ODR ^=i;}		//输出反转状态

/* 定义控制IO的宏 */
#define VALVE1_TOGGLE		digitalToggle(VALVE1_GPIO_PORT,VALVE1_PIN)
#define VALVE1_ON			digitalHi(VALVE1_GPIO_PORT,VALVE1_PIN)
#define VALVE1_OFF				digitalLo(VALVE1_GPIO_PORT,VALVE1_PIN)

#define VALVE2_TOGGLE		digitalToggle(VALVE2_GPIO_PORT,VALVE2_PIN)
#define VALVE2_ON			digitalHi(VALVE2_GPIO_PORT,VALVE2_PIN)
#define VALVE2_OFF				digitalLo(VALVE2_GPIO_PORT,VALVE2_PIN)

#define VALVE3_TOGGLE		digitalToggle(VALVE3_GPIO_PORT,VALVE3_PIN)
#define VALVE3_ON			digitalHi(VALVE3_GPIO_PORT,VALVE3_PIN)
#define VALVE3_OFF				digitalLo(VALVE3_GPIO_PORT,VALVE3_PIN)

#define RELAY1_TOGGLE		digitalToggle(RELAY1_GPIO_PORT,RELAY1_PIN)
#define RELAY1_ON			digitalHi(RELAY1_GPIO_PORT,RELAY1_PIN)
#define RELAY1_OFF				digitalLo(RELAY1_GPIO_PORT,RELAY1_PIN)

#define RELAY2_TOGGLE		digitalToggle(RELAY2_GPIO_PORT,RELAY2_PIN)
#define RELAY2_ON			digitalHi(RELAY2_GPIO_PORT,RELAY2_PIN)
#define RELAY2_OFF				digitalLo(RELAY2_GPIO_PORT,RELAY2_PIN)

#define GPIO_ALL_INIT \
					VALVE1_OFF;\
					VALVE2_OFF;\
					VALVE3_OFF;\
					RELAY1_OFF;\
					RELAY2_OFF;
					
void SYS_GPIO_Config(void);

#endif
