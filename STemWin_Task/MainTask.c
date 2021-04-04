/**
  *********************************************************************
  * @file    MainTask.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   FreeRTOS v9.0.0 + STM32 ����ģ��
  *********************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
/*******************************************************************************
 * ������ͷ�ļ�
 ******************************************************************************/

#include "./led/bsp_led.h"

/* STemWINͷ�ļ� */
#include "GUI.h"
#include "DIALOG.h"

/*******************************************************************************
 * ����
 ******************************************************************************/
/**
  * @brief GUI������
  * @note ��
  * @param ��
  * @retval ��
  */
void MainTask(void)
{
  GUI_SetBkColor(GUI_BLUE);
  GUI_Clear();
  
  GUI_CURSOR_Show();

  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(GUI_FONT_32B_1);
  
  GUI_DispString("Hello World!\r\nNO RTOS");
  
  while(1)
  {
    LED2_TOGGLE;
    GUI_Delay(1000);
  }
}