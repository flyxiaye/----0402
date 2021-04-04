#include  "keyboard.h"
#include "./systick/bsp_SysTick.h"

char g_Key = -1;


//*      Key_Scan(void)
//*	@brief:		获取矩阵键盘的引脚状态，每个按键返回特定的值
//*	@param:		void
//*	@return:	1~9 未按下键盘时返回-1 
//* @note:    void
//*
int Key_Scan(void)
{   
    char Scan_Result;
	
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOE, ENABLE); 

		/*设置引脚模式为输出模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	  
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;	
		GPIO_Init(GPIOE, &GPIO_InitStructure);	
		GPIO_ResetBits(GPIOE, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
		
		/*设置引脚模式为输入模式*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 		
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;	
    GPIO_Init(GPIOE, &GPIO_InitStructure);	

    
    Scan_Result=GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1);
    Scan_Result+=GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)<<1;    
    Scan_Result+=GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)<<2;
    
    if(Scan_Result != 0x07)
    {
        Delay_10us(200);
        Scan_Result=Scan_Result<<4;
			
				/*设置引脚模式为输出模式*/
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
				GPIO_Init(GPIOE, &GPIO_InitStructure);	
				GPIO_ResetBits(GPIOE, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
				
				/*设置引脚模式为输入模式*/
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 		
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;	
				GPIO_Init(GPIOE, &GPIO_InitStructure);	
		        
        Delay_10us(100);
        Scan_Result+=GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4);
        Delay_10us(100);
        Scan_Result+=GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)<<1;
        Delay_10us(100);
        Scan_Result+=GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6)<<2;
        
        switch(Scan_Result)
        { 
        case 0x33: return 3;
        case 0x35: return 6;
        case 0x36: return 9;
        case 0x53: return 2;
        case 0x55: return 5;
        case 0x56: return 8;
        case 0x63: return 1;
        case 0x65: return 4;
        case 0x66: return 7;
        default :break;
        }       
    } 
    return -1;
}


//*    Key_Check(void)
//*	@brief:		检测上升沿
//*	@param:		void
//*	@return:	刚按下去时返回实际健值 未按下或按下不放时返回-1； 
//* @note:    void
//*


int Key_Check(void)
{
    char last_Key;
    static char temp_Key = -1;

    last_Key = temp_Key;
    temp_Key = (char)Key_Scan();
    if(temp_Key != last_Key)
    {
        return last_Key;
    }
    return -1;         
}




