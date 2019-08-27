#include "hal_sys.h"


/**
	* @brief  GPIO 共用函数
	* @param 	GPIO_TypeDef
	*					GPIOx x = A ... I
	*					Pinx    =  GPIO_Pin_0...15
	*					GPIO_Speed_xMHz  x = 10,2,50
	*					GPIO_InitTypeDef
	* @retval
	*/
void GPIO_Common_Config(GPIO_TypeDef *GPIOx,uint16_t Pinx,GPIOSpeed_TypeDef Speed,GPIOMode_TypeDef Mode,GPIOOType_TypeDef OType,GPIOPuPd_TypeDef PuPd)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin 	= Pinx;
	GPIO_InitStructure.GPIO_Mode 	= Mode;
	GPIO_InitStructure.GPIO_Speed = Speed;
	GPIO_InitStructure.GPIO_OType = OType;
	GPIO_InitStructure.GPIO_PuPd  = PuPd;
	GPIO_Init(GPIOx,&GPIO_InitStructure);
}
/**
	* @brief  TIMx 定时器共用函数
	* @param 	TIM_TimeBaseInitTypeDef
	*					Period  	=
	*					Prescaler =
	*					Clock 		=
	*					Mode   		=
	*					Repe   		= 
	* @retval
	*/
void TIMx_Common_Config(TIM_TypeDef* TIMx,uint32_t Period,uint16_t Prescaler,uint16_t Clock,uint16_t Mode,uint8_t Repe)
{

  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period 						= Period;
	TIM_TimeBaseStructure.TIM_Prescaler 				=	Prescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision 		= Clock;
	TIM_TimeBaseStructure.TIM_CounterMode 		 	= Mode;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = Repe;
	
	
	TIM_TimeBaseInit(TIMx,&TIM_TimeBaseStructure);
}
/**
	* @brief  NVIC 中断共用函数
	* @param 	NVIC_InitTypeDef
	*         IRQn 中断源
	*					Priority   = 0..3  中断优先级
	*					Cmd        =  ENABLE / DISABLE
	* @retval
	*/
void NVIC_Common_Config(uint8_t IRQn,uint8_t Priority, FunctionalState Cmd)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel 				 = IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = Priority;
	NVIC_InitStructure.NVIC_IRQChannelCmd 		 = Cmd;
	
	NVIC_Init(&NVIC_InitStructure);
}
/**
	* @brief  USART 串口共用函数
	* @param 	USART_InitTypeDef  
	* @retval
	*/
void USART_Common_Config(USART_TypeDef* USARTx,uint32_t BaudRate,uint32_t Word,uint32_t StopBits,uint32_t Parity,uint32_t Mode,uint32_t Flow)
{
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate 	= BaudRate;
	USART_InitStruct.USART_WordLength = Word;
	USART_InitStruct.USART_StopBits 	= StopBits;
	USART_InitStruct.USART_Parity  		= Parity;
	USART_InitStruct.USART_HardwareFlowControl = Flow;
	USART_InitStruct.USART_Mode 		  = Mode;
	USART_Init(USARTx,&USART_InitStruct);
}
/**
	* @brief  EXTI 串口共用函数
	* @param 	EXTI_InitTypeDef  
	* @retval
	*/
void EXTI_Common_Config(uint32_t Line,EXTIMode_TypeDef Mode,EXTITrigger_TypeDef Trigger,FunctionalState Cmd)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = Line;
	EXTI_InitStruct.EXTI_Mode = Mode;
	EXTI_InitStruct.EXTI_Trigger = Trigger;
	EXTI_InitStruct.EXTI_LineCmd = Cmd;
	EXTI_Init(&EXTI_InitStruct);	
}



/**
	* @brief  NVIC 中断共用函数
	* @param 	NVIC_InitTypeDef
	*         IRQn 中断源
	*					Priority   = 0..3  中断优先级
	*					Cmd        =  ENABLE / DISABLE
	* @retval
	*/
//void PWM_Common_Config(TIM_TypeDef* TIMx,uint16_t Mode,uint16_t OutputState,uint16_t OutputNState,uint16_t Pulse,uint16_t OCPolarity,uint16_t OCNPolarity,\
//											 uint16_t OCIdleState,uint16_t OCNIdleState)
//{
//	TIM_OCInitTypeDef TIM_OCInitStruct;
//	
//	TIM_OCInitStruct.TIM_OCMode 		  = Mode;
//	TIM_OCInitStruct.TIM_OutputState  = OutputState;
//	TIM_OCInitStruct.TIM_OutputNState = OutputNState;
//	TIM_OCInitStruct.TIM_OCPolarity   = OCPolarity;
//	TIM_OCInitStruct.TIM_OCNPolarity  = OCNPolarity;
//	TIM_OCInitStruct.TIM_OCIdleState  = OCIdleState;
//	TIM_OCInitStruct.TIM_OCNIdleState = OCNIdleState;	
//	TIM_OCInitStruct.TIM_Pulse  			= Pulse;
////	TIM_OC1Init(TIM14,&TIM_OCInitStruct); 
//}
