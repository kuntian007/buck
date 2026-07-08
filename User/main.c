#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "ADC.h"
#include "Delay.h"

float Target=2978.0,Actual,Out;
float Kp=0.3,Ki=0.05;
float error,error_i;
uint16_t duty;
int main(void)
{
	PWM_Init();
    AD_Init();
	error_i=0;
	while(1){
		Actual=AD_GetVaule();
		error=Target-Actual;
		error_i+=error;//误差积分
		//积分限幅，防积分饱和
		if(error_i > 3000) error_i = 3000;
		if(error_i < -3000) error_i = -3000;
		Out=Kp*error+Ki*error_i;//PI计算
		
	    duty=80+(uint16_t)Out;
		// 占空比限幅
        if(duty > 98) duty = 98;
        if(duty < 2)  duty = 2;
		PWM_SetCompare(duty);//更新PWM
		
		Delay_ms(10);
	}
	
}
