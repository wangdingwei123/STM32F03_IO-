#include "serial.h"
#include "usart.h"

uint8_t Serial_Data;

/**
	* @brief 模拟串行通讯 输入引脚初始化
	* @param 
	* @retval
	*/
void Serial_Rx_Init(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	GPIO_Common_Config(GPIOA,GPIO_Pin_5,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP);	//Tx
	GPIO_Common_Config(GPIOA,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_IN,GPIO_OType_PP,GPIO_PuPd_UP); 	//Rx
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource6);
	EXTI_ClearITPendingBit(EXTI_Line6);
	
	NVIC_Common_Config(EXTI4_15_IRQn,0x01,ENABLE);
	EXTI_Common_Config(EXTI_Line6,EXTI_Mode_Interrupt,EXTI_Trigger_Falling,ENABLE);
	EXTI_ClearITPendingBit(EXTI_Line6);	
}
/**
	* @brief 模拟串行通讯的开始位
	* @param time 时间
	* @retval
	*/
void Serial_Write_Start_Bit(uint32_t timer)
{
	Tx_Pin() = 0;
	delay_us(timer);
}
/**
	* @brief 模拟串行通讯的停止位
	* @param time 时间
	* @retval
	*/
void Serial_Write_Stop_Bit(uint32_t timer)
{
	Tx_Pin() = 1;
	delay_us(timer);
}
/**
	* @brief 模拟串行通讯的数据位
	* @param[i] data 数据
	* @param[i] time 时间
	* @retval
	*/
void Serial_Write_Data(u8 data,u32 timer)
{
	uint8_t i,bit;
	Serial_Write_Start_Bit(timer);
	for(i=0;i<8;i++)
	{
		bit = (data >> i)&0x01;
		if(bit == 0)Tx_Pin() = 0;
		else Tx_Pin() = 1;
		delay_us(timer);
	}
	Serial_Write_Stop_Bit(timer);
}
/**
	* @brief  发送模拟串行通讯的数据
	* @param[i] data 数据缓存
	* @param[i] time 时间
	* @retval
	*/
void Serial_Write_String(uint8_t *data,uint8_t len,uint32_t timer)
{
	uint8_t i;
	for(i=0;i<len;i++)
	{
		Serial_Write_Data(data[i],timer);
	}
}
/**
	* @brief 读取模拟串行通讯的数据
	* @param[i] data 数据缓存
	* @param[i] time 时间
	* @retval
	* 可修改为中断获取起始位
	*/
uint8_t Serial_Read_Data(uint32_t timer)
{
	uint8_t i=9,data;
	if(Rx_Pin() == 0)
	{
		delay_us(timer);	//起始位
		while(i--)
		{
			data >>=1;
			if(Rx_Pin() == 1)data |= 0x80;
			delay_us(timer);
		}
	}
	return data;
}
/**
	* @brief 外部中断
	* @param 
	* @retval
	*/
void EXTI4_15_IRQHandler(void)
{
	u8 i =9;
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
		NVIC->ICER[0] = (uint32_t)0x01 << (EXTI4_15_IRQn& (uint8_t)0x1F);	//失能中断
		EXTI_ClearITPendingBit(EXTI_Line6);
		delay_us(30);//开始位
		while(i--)
		{
			Serial_Data >>=1;
			if(Rx_Pin() == 1)
			{		
				Serial_Data |=0x80; 
			}
			delay_us(104);
		}   
	}
	EXTI_ClearITPendingBit(EXTI_Line6);
  NVIC->ISER[0] = (uint32_t)0x01 << (EXTI4_15_IRQn & (uint8_t)0x1F);
}

