#include "motor_init.h"
#include "sys.h"

//电机驱动引脚初始化
void motor_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); 
	                                                                     	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = 999; 
	TIM_TimeBaseStructure.TIM_Prescaler = 0; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);

  TIM_CtrlPWMOutputs(TIM2,ENABLE);

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	
	TIM_Cmd(TIM2, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 
	GPIO_SetBits(GPIOA,GPIO_Pin_4);					
}


