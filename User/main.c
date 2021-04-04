/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   FreeRTOS v9.0.0 + STM32 ����ģ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
int main(void)
{
  //��ʼ���ⲿSRAM  
//  FSMC_SRAM_Init();
  
  /*CRC��emWinû�й�ϵ��ֻ������Ϊ�˿�ı��������ģ�����STemWin�Ŀ�ֻ������ST��оƬ���棬���оƬ���޷�ʹ�õġ� */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);  
//  TIM3_Int_Init(999,83); 	//1KHZ ��ʱ��3����Ϊ1ms

//	TIMx_Configuration(); 		//TIM3 ���PWM
	
  /* LED��ʼ�� */
//	LED_GPIO_Config();
	
	/* ��ŷ����̵�����ʼ�� */
	SYS_GPIO_Config();
	
	TIM3_PWM_Init(999, 839);
	
	OLED_Init();
	/* ���ô���1Ϊ��115200 8-N-1 */
	Debug_USART_Config();
	
	
  MAX31865_Init();
	MAX31865_Cfg();
	
  /* ��ʼ��GUI */
	GUI_Init();
  
  /* ��������ʼ�� */
  GTP_Init_Panel();
  
  /* ��ʼ����ʱ�� */
	SysTick_Init();
  TIM4_Int_Init(999,839);		//1KHZ ��ʱ��4����Ϊ10ms
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

