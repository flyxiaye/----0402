#ifndef __GENERAL_TIM_H
#define	__GENERAL_TIM_H

#include "stm32f4xx.h"

#define GENERAL_OCPWM_PIN             GPIO_Pin_9             
#define GENERAL_OCPWM_GPIO_PORT       GPIOC                   
#define GENERAL_OCPWM_GPIO_CLK        RCC_AHB1Periph_GPIOC
#define GENERAL_OCPWM_PINSOURCE				GPIO_PinSource9
#define GENERAL_OCPWM_AF							GPIO_AF_TIM3

#define GENERAL_TIM           		    TIM3
#define GENERAL_TIM_CLK       		    RCC_APB1Periph_TIM3

#define GENERAL_TIM_IRQn					    TIM3_IRQn
#define GENERAL_TIM_IRQHandler        TIM3_IRQHandler


void TIMx_Configuration(void);

#endif /* __GENERAL_TIM_H */

