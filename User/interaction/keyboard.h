#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "stm32f4xx.h"


int Key_Scan(void);
int Key_Check(void);
void INTR_Keyboard_Init(void);
extern char g_Key;


#endif
