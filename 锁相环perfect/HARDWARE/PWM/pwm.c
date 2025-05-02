#include "stm32f4xx.h"
#include "pwm.h"
#include "global.h"


void set_duty1(float duty)
{
	TIM_SetCompare1(TIM1,(uint32_t)((1-duty)*PWM_PERIOD));

} 
void set_duty2(float duty)
{
	TIM_SetCompare2(TIM1,(uint32_t)((1-duty)*PWM_PERIOD));

} 

