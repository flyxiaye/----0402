/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   FreeRTOS v9.0.0 + STM32 工程模版
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"  
#include "./sram/bsp_sram.h"	  
#include "./lcd/bsp_nt35510_lcd.h"
#include "./systick/bsp_SysTick.h"
#include "./touch/gt9xx.h"
#include "./tim/bsp_general_tim.h"
#include "timer.h"
#include "oMenu.h"
#include "OLED.h"
#include "gpio.h"
#include "max31865.h"
#include "pwm.h"

#include "GUI.h"
#include "DIALOG.h"
extern void gui_init(void);
extern void gui_loop(void);
/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{
  //初始化外部SRAM  
//  FSMC_SRAM_Init();
  
  /*CRC和emWin没有关系，只是他们为了库的保护而做的，这样STemWin的库只能用在ST的芯片上面，别的芯片是无法使用的。 */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);  
//  TIM3_Int_Init(999,83); 	//1KHZ 定时器3设置为1ms

//	TIMx_Configuration(); 		//TIM3 输出PWM
	
  /* LED初始化 */
//	LED_GPIO_Config();
	
	/* 电磁阀，继电器初始化 */
	SYS_GPIO_Config();
	
	TIM3_PWM_Init(999, 839);
	
	OLED_Init();
	/* 配置串口1为：115200 8-N-1 */
	Debug_USART_Config();
	
	
  MAX31865_Init();
	MAX31865_Cfg();
	
  /* 初始化GUI */
	GUI_Init();
  
  /* 触摸屏初始化 */
  GTP_Init_Panel();
  
  /* 初始化定时器 */
	SysTick_Init();
  TIM4_Int_Init(999,839);		//1KHZ 定时器4设置为10ms
//  GUI_CURSOR_Show();
  gui_init();
//  printf("\r\n ********** emwin DEMO *********** \r\n");
  
  while(1)
  {
		gui_loop();
		Menu();
  }
}


/*********************************************END OF FILE**********************/

