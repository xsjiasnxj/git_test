#include "stm32f4xx.h"
#include "disp.h"
#include "OLED.h"
#include "global.h"

void disp_title()
{
	if(mode==0)
	{
		OLED_ShowString(0,0,"SingleMode",8);
	}
	else
	{
		OLED_ShowString(0,0,"ParallelMode",8);
	}
}


void disp_others()
{
	if(mode==0&&page==0)
	{
		OLED_ShowString(0,16,"Uo set:",8);
	}
	else if(mode==0&&page==1)
	{
		OLED_ShowString(0,16,"Uo real:",8);
		OLED_ShowString(0,32,"Io real:",8);
	}
	else if(mode==1&&page==0)
	{
		OLED_ShowString(0,16,"Uo set:",8);
		OLED_ShowString(0,32,"KIo set:",8);
	}
	else if(mode==1&&page==1)
	{
		OLED_ShowString(0,16,"Uo real:",8);
		OLED_ShowString(0,32,"Io1 real:",8);
		OLED_ShowString(0,48,"Io2 real:",8);
	}
	
}

void disp_real()
{

}
