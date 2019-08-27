#include "usart.h"




/**
	* @brief  USART ��ʼ��
	* @param 	baud ������
	* @retval
	*/
void USART1_Init(uint32_t baud)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	/*USART1�Ķ˿�����*/
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);	//����PA9�ɵڶ�����
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);
	
	GPIO_Common_Config(GPIOA,GPIO_Pin_9|GPIO_Pin_10,GPIO_Speed_50MHz,GPIO_Mode_AF,GPIO_OType_PP,GPIO_PuPd_UP);
	
	USART_Common_Config(USART1,baud,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,\
											USART_Mode_Rx|USART_Mode_Tx,USART_HardwareFlowControl_None);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);	//ʹ�ܽ����ж�
	USART_Cmd(USART1,ENABLE);
	
	NVIC_Common_Config(USART1_IRQn,0x02,ENABLE);	
}
/**
	* @brief  USART �жϷ�����
	* @param 	
	* @retval
	*/
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		USART_SendData(USART1,USART_ReceiveData(USART1));
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	}
}















//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)
//��׼����Ҫ��֧�ֺ���    
struct __FILE
{	
	int handle;
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
};
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x)
{
	x = x;
}
//�ض���fputc����
int fputc(int ch,FILE *f)
{
	while(!(USART1->ISR &(1<<7))){}
	USART1->TDR = ch;
	return (ch);
}

#endif 










