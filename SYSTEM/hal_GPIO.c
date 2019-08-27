#include "hal_gpio.h"

void GPIO_CommonConfig(void)
{ 
	RCC->AHBENR  |= 1 << 17;							//IO端口A使能
	GPIOA->MODER &= ~(0x03 << (4 * 2));	//清除
	GPIOA->MODER |= (0x01 << (4 * 2));	//0x01 = 输出模式， 4 = 引脚  模式占2位
	
	GPIOA->OSPEEDR &= ~(0x03 <<(4 * 2));//清除速率
	GPIOA->OSPEEDR |= (0x00 <<(4 * 2)); //0x00 = 10M 低速， 4 = 引脚  模式占2位
	
	GPIOA->OTYPER &= ~(0x01 <<(4 ));//清除速率
	GPIOA->OTYPER |= (0x00 <<(4 )); //0x00 = 推挽输出， 4 = 引脚 	
	
	GPIOA->PUPDR &= ~(0x03 <<(4 * 2));//清除上拉/下拉
	GPIOA->PUPDR |= (0x01 <<(4 * 2)); //0x01 = 上拉 ， 4 = 引脚  模式占2位
	
}

/**
	* @brief  GPIO 引脚初始化
	* @param 	
	* @retval
	*/
void GPIO_Pin_init(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	
	
	GPIO_Common_Config(GPIOA,GPIO_Pin_4,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_NOPULL);
	
}



