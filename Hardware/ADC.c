#include "stm32f10x.h"                  // Device header

void AD_Init (void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
//GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&GPIO_InitStructure);
//ADC	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4,1,ADC_SampleTime_239Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_DataAlign =ADC_DataAlign_Right;//右对齐
	ADC_InitStructure.ADC_Mode =ADC_Mode_Independent;//单ADC
	ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_T1_CC1 ;//定时器触发
	ADC_InitStructure.ADC_ContinuousConvMode =DISABLE ;//单次
	ADC_InitStructure.ADC_NbrOfChannel =1;
	ADC_InitStructure.ADC_ScanConvMode =DISABLE ;//非扫描
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);
//上电后校准
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)==SET);
}
//每次采样
uint16_t AD_GetVaule(void)
{
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);	
    return ADC_GetConversionValue(ADC1);//读取数据寄存器会自动清除标志位
}
