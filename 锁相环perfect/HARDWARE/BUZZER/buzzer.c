#include "stm32f4xx.h"
#include "delay.h"
#include "gpio.h"

void beep(uint8_t beep_ms)
{
	
	BUZZER=0;
	delay_ms(2);
	BUZZER=1;
	delay_ms(beep_ms);
	BUZZER=0;
	
}