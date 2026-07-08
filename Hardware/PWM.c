#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_TIM1,ENABLE);
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	TIM_InternalClockConfig(TIM1);
	//时基单元初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision =TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode =TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period =100-1;//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler =36-1;//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter =0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);
	//输出比较
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode =TIM_OCMode_PWM1;//PWM模式1
	TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;//高电平为有效电平
	TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity =TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse =80;//CCR
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	//死区
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
    TIM_BDTRInitStructure.TIM_OSSRState      = TIM_OSSRState_Disable;
    TIM_BDTRInitStructure.TIM_OSSIState      = TIM_OSSIState_Disable;
    TIM_BDTRInitStructure.TIM_LOCKLevel      = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStructure.TIM_DeadTime       = 14;    // ≈200ns (14 × 13.89ns)
    TIM_BDTRInitStructure.TIM_Break          = TIM_Break_Disable;
    TIM_BDTRInitStructure.TIM_BreakPolarity  = TIM_BreakPolarity_High;
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
    TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	//PA8,CH1通道
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;//复用推挽
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//PB13,CH1N通道
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//MOE置1
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
	TIM_Cmd(TIM1,ENABLE);
}

void PWM_SetCompare(uint16_t cc)
{
    TIM_SetCompare1(TIM1,cc);   // 动态修改占空比，立即生效
}
