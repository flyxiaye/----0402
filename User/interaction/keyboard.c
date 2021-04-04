#include  "keyboard.h"
#include "./systick/bsp_SysTick.h"

char g_Key = -1;


//*      Key_Scan(void)
//*	@brief:		��ȡ������̵�����״̬��ÿ�����������ض���ֵ
//*	@param:		void
//*	@return:	1~9 δ���¼���ʱ����-1 
//* @note:    void
//*
int Key_Scan(void)
{   
    char Scan_Result;
	
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOE, ENABLE); 

		/*��������ģʽΪ���ģʽ*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	  
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;	
		GPIO_Init(GPIOE, &GPIO_InitStructure);	
		GPIO_ResetBits(GPIOE, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
		
		/*��������ģʽΪ����ģʽ*/
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
			
				/*��������ģʽΪ���ģʽ*/
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
				GPIO_Init(GPIOE, &GPIO_InitStructure);	
				GPIO_ResetBits(GPIOE, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
				
				/*��������ģʽΪ����ģʽ*/
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
//*	@brief:		���������
//*	@param:		void
//*	@return:	�հ���ȥʱ����ʵ�ʽ�ֵ δ���»��²���ʱ����-1�� 
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




