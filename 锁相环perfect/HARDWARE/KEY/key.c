#include "stm32f4xx.h"
#include "key.h"
#include "main.h"
#include "delay.h"

uint8_t R3,R2,R1,R0;
uint8_t C3,C2,C1,C0;

GPIO_InitTypeDef GPIO_InitStructure_KEY;

void R_O_UP()
{
	GPIO_InitStructure_KEY.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure_KEY.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_KEY.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure_KEY.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure_KEY.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_0|GPIO_Pin_1;	//R3 R2 R1 R0
 	GPIO_Init(GPIOE, &GPIO_InitStructure_KEY);
	GPIO_InitStructure_KEY.GPIO_Pin = GPIO_Pin_13;	//R3 R2 R1 R0
 	GPIO_Init(GPIOC, &GPIO_InitStructure_KEY);
	
	GPIO_SetBits(GPIOE,GPIO_Pin_6);
	GPIO_SetBits(GPIOE,GPIO_Pin_0);
	GPIO_SetBits(GPIOE,GPIO_Pin_1);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
}
void R_I_DOWN()
{
	GPIO_InitStructure_KEY.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure_KEY.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_KEY.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure_KEY.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉

	GPIO_InitStructure_KEY.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_0|GPIO_Pin_1;	//R3 R2 R1 R0
 	GPIO_Init(GPIOE, &GPIO_InitStructure_KEY);
	GPIO_InitStructure_KEY.GPIO_Pin = GPIO_Pin_13;	//R3 R2 R1 R0
 	GPIO_Init(GPIOC, &GPIO_InitStructure_KEY);
	
}
void C_O_UP()
{
	GPIO_InitStructure_KEY.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure_KEY.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_KEY.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure_KEY.GPIO_PuPd = GPIO_PuPd_UP;//上拉

	GPIO_InitStructure_KEY.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	//C3  C1 C0
 	GPIO_Init(GPIOE, &GPIO_InitStructure_KEY);

	GPIO_SetBits(GPIOE,GPIO_Pin_2);
	GPIO_SetBits(GPIOE,GPIO_Pin_3);
	GPIO_SetBits(GPIOE,GPIO_Pin_4);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
}
void C_I_DOWN()
{
	GPIO_InitStructure_KEY.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure_KEY.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_KEY.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure_KEY.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉

	GPIO_InitStructure_KEY.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	//C3  C1 C0
 	GPIO_Init(GPIOE, &GPIO_InitStructure_KEY);
}

uint8_t is_key_down()
{
	R_O_UP();
	C_I_DOWN();
	
	C3=GPIO_ReadInputDataBit(GPIOE,C3_Pin);
	C2=GPIO_ReadInputDataBit(GPIOE,C2_Pin);	
	C1=GPIO_ReadInputDataBit(GPIOE,C1_Pin);
	C0=GPIO_ReadInputDataBit(GPIOE,C0_Pin);	
	
	return (C3||C2||C1||C0);
}
void Clear_CR()
{
	R3=0;
	R2=0;
	R1=0;
	R0=0;
	C3=0;
	C2=0;
	C1=0;
	C0=0;
}


void key_command_callback(Key_HandleTypeDef* key)
{
	char result = '#';
	if(is_key_down())
	{
		delay_ms(20);
		if(is_key_down())
		{
			C_O_UP();
			R_I_DOWN();
			
			R3=GPIO_ReadInputDataBit(GPIOE,R3_Pin);			
			R2=GPIO_ReadInputDataBit(GPIOC,R2_Pin);				
			R1=GPIO_ReadInputDataBit(GPIOE,R1_Pin);
			R0=GPIO_ReadInputDataBit(GPIOE,R0_Pin);	
			
			if(R3)
			{
				if(C0)
                {   
					result = '1';
				}
				if(C1)
				{
					result = '2';
				}
				if(C2)
				{
					result = '3';
				}
				if(C3)
				{
					result = '4';
            }
            }
			if(R2)
			{
				
				if(C0)
				{
					result = '5';
				}
				if(C1)
				{
					result = '6';
				}
				if(C2)
				{
					result = '7';
				}
				if(C3)
				{
					result = '8';
				}
			}	

			if(R1)
			{

				if(C0)
				{
					result = '9';
				}
				if(C1)
				{
					result = '0';
				}
				if(C2)
				{
					result = '.';
				}
				if(C3)
				{
					result = '-';
				}
			}			
			if(R0)
			{
				if(C0)
				{
					result = 'N';
				}
				if(C1)
				{
					result = 'F';
				}
				if(C2)
				{
					result = 'B';
				}
				if(C3)
				{
					result = 'S';
				}
			}

		}
		//while(is_key_down());
	}
	Clear_CR();
	key->key_num=result;
}
