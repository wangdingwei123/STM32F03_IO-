#include "hal_pwm.h"



PWM_TypeDef  PWM_Structure;


void TIM14_PWM_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	
	GPIO_Common_Config(GPIOA,GPIO_Pin_4,GPIO_Speed_50MHz,GPIO_Mode_AF,GPIO_OType_PP,GPIO_PuPd_UP);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource4,GPIO_AF_4);
	
	TIM_DeInit(TIM14);
	TIM_InternalClockConfig(TIM14);//采用内部时钟给TIM3提供时钟源
	
	/* ARR寄存器用来配置频率，此处配置为 10 Khz */
	PWM_Structure.TimerPeriod = (SystemCoreClock / 10000) -1;//4800 -1
	
	TIMx_Common_Config(TIM14,PWM_Structure.TimerPeriod,10-1,TIM_CKD_DIV1,TIM_CounterMode_Up,0);
	
	/*Channel 1 Configuration in PWM mode  PA4*/
	PWM_Structure.TIM_OCInitStruct.TIM_OCMode 			= TIM_OCMode_PWM1;
	PWM_Structure.TIM_OCInitStruct.TIM_OutputState 	= TIM_OutputState_Enable;
	PWM_Structure.TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable; 
	PWM_Structure.TIM_OCInitStruct.TIM_OCPolarity 	= TIM_OCPolarity_Low;
	PWM_Structure.TIM_OCInitStruct.TIM_OCNPolarity 	= TIM_OCNPolarity_High;
	PWM_Structure.TIM_OCInitStruct.TIM_OCIdleState 	= TIM_OCIdleState_Set;
	PWM_Structure.TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM14,&PWM_Structure.TIM_OCInitStruct);  
	 
	PWM_OutputVlot(TIM14,3300);
	
	TIM_CtrlPWMOutputs(TIM14,ENABLE);
	TIM_Cmd(TIM14,ENABLE);
	
	
	
}


void  PWM_OutputVlot(TIM_TypeDef * TIMx,uint16_t dutyfactor)
{
	PWM_Structure.Channel1Pulse = (uint16_t )(((uint32_t)dutyfactor *(PWM_Structure.TimerPeriod - 1))/3300);
	PWM_Structure.TIM_OCInitStruct.TIM_Pulse = PWM_Structure.Channel1Pulse;
  if((TIMx == TIM1) || (TIMx == TIM15) || (TIMx == TIM16) || (TIMx == TIM17))
	{
		TIMx->CCR1 = PWM_Structure.Channel1Pulse;
	}
}


