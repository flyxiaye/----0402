#include "max31865.h"
#include "math.h"
//#include "usart.h"

/* MAX31865 初始化 */
void MAX31865_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure ;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG,ENABLE);//MAX31865_CONTROL_PORT相应的GPIO使能

	GPIO_InitStructure.GPIO_Pin = MAX31865_CS|MAX31865_SCLK;//输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50赫兹
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(MAX31865_CONTROL_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = MAX31865_SDI;
	GPIO_Init(MAX31865_CONTROL_PORT2, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = MAX31865_SDO; //|MAX31865_DRDY;//SDO数据输入和DRDY转换状态输入
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//50赫兹
	GPIO_Init(MAX31865_CONTROL_PORT2, &GPIO_InitStructure);
	
	MAX31865_CS_SET;	//初始化取消片选
	MAX31865_SCLK_SET;//时钟置1
}


/* MAX31865 写寄存器 
addr:寄存器地址
data:数据
*/
void MAX31865_Write(unsigned char addr, unsigned char data)
{
	unsigned char i;
	
	MAX31865_CS_CLR;//片选
	for(i=0;i<8;i++)  //写地址
	{
		MAX31865_SCLK_CLR;//时钟拉低
		if(addr&0x80) 
			MAX31865_SDI_SET;
		else 
			MAX31865_SDI_CLR;
		
		MAX31865_SCLK_SET;//时钟拉高
		addr<<=1;
	}
	for(i=0;i<8;i++)  //写数据
	{
		MAX31865_SCLK_CLR;
		if(data&0x80) 
			MAX31865_SDI_SET;
		else 
			MAX31865_SDI_CLR;
		
		MAX31865_SCLK_SET;
		data<<=1;
	}
	MAX31865_CS_SET;//取消片选
}

/* MAX31865 读寄存器 
addr:寄存器地址
*/
unsigned char MAX31865_Read(unsigned char addr)
{
	unsigned char i;
	unsigned char data=0;
	
	MAX31865_CS_CLR;//片选
	for(i=0;i<8;i++)  //写地址
	{
		MAX31865_SCLK_CLR;
		if(addr&0x80) 
			MAX31865_SDI_SET;
		else 
			MAX31865_SDI_CLR;
		MAX31865_SCLK_SET;
		addr<<=1;
	}
	for(i=0;i<8;i++)  //读数据
	{
		MAX31865_SCLK_CLR;
		data<<=1;		
		MAX31865_SCLK_SET;		
		if(MAX31865_SDO_READ) 
			data|=0x01;
		else 
			data|=0x00;
	}
	MAX31865_CS_SET;//取消片选
	return data;
}

/* MAX31865 配置*/		
//0x80，0xC3配置为：BIAS ON,自动，2线，50HZ
//0x80，0xD3配置为：BIAS ON,自动，3线，50HZ
void MAX31865_Cfg(void)
{
	MAX31865_Write(0x80, 0xD3); //0x80，0xD3配置为：BIAS ON,自动，3线，50HZ
}

/* MAX31865 获取温度 */
float MAX31865_GetTemp(void)
{
	unsigned int data;
	float Rt;
	float Rt0 = 100;  //PT100	当温度在0°C时，电阻为100Ω
	float Z1,Z2,Z3,Z4,temp;
	float a = 3.9083e-3;
	float b = -5.775e-7;
	float rpoly;
	
	u16 t;
	
//	MAX31865_Write(0x80, 0xC3);//0x80，0xC3配置为：BIAS ON,自动，2线，50HZ
	
	data=MAX31865_Read(0x01)<<8;
	data|=MAX31865_Read(0x02);
	data>>=1;  //去掉Fault位
	
//	printf("Read=0x%02X\r\n",data);
	
	Rt=(float)data/32767.0*RREF;
	
//	printf("Rt=0x%.1f\r\n",Rt);

	Z1 = -a;
  Z2 = a*a-4*b;
  Z3 = 4*b/Rt0;
  Z4 = 2*b;

  temp = Z2+Z3*Rt;
  temp = (sqrt(temp)+Z1)/Z4;
  
  if(temp>=0) return temp;

  rpoly = Rt;
  temp = -242.02;
  temp += 2.2228 * rpoly;
  rpoly *= Rt;  // square
  temp += 2.5859e-3 * rpoly;
  rpoly *= Rt;  // ^3
  temp -= 4.8260e-6 * rpoly;
  rpoly *= Rt;  // ^4
  temp -= 2.8183e-8 * rpoly;
  rpoly *= Rt;  // ^5
  temp += 1.5243e-10 * rpoly;

  return temp;
}

