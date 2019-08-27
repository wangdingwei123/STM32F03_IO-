#include "stm32f0xx.h"
#include "hal_GPIO.h"
#include "hal_sys.h"
#include "usart.h"
#include "serial.h"


int main(void)
{
	Delay_Init();
	GPIO_CommonConfig();
	USART1_Init(115200);
	Serial_Rx_Init();
	while(1)
	{ 
		delay_ms(500); 	
		LED = 1;
		delay_ms(500); 		
		LED = 0;
	}
}

