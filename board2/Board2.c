#include <STC89C5xRC.H>
#include "Board2.h"
#include "BackRoom.h"
#include "uart.h"
#include "mp3.h"


void init();
void checkButtonInput();
void light();

int groupSelect_0 = -1;
int groupSelect_1 = -1;
int groupSelect_2 = -1;
int groupSelect_3 = -1;

int groupSelect_0_last = -1;
int groupSelect_1_last = -1;
int groupSelect_2_last = -1;
int groupSelect_3_last = -1;

/*
 * 输出低电平触发
 * 输入高电平触发
 *
 */
void main()
{
	init();
	uart_init();
	mp3_init();

	delay_ms(100);

	while(1)
	{
		switch(step)
		{
			case 0:
				checkButtonInput();
				light();
				if((groupSelect_0_last != groupSelect_0)&&
				(groupSelect_1_last != groupSelect_1)&&
				(groupSelect_2_last != groupSelect_2)&&
				(groupSelect_3_last != groupSelect_3))
				{
					groupSelect_0_last = groupSelect_0;
					groupSelect_1_last = groupSelect_1;
					groupSelect_2_last = groupSelect_2;
					groupSelect_3_last = groupSelect_3;
					
					if((groupSelect_0 == 1)&&(groupSelect_2 == 3)&&(groupSelect_3 == 3)&&(groupSelect_3 == 2))
					{
						P24 = 0;
						play_mp3(0,MUSIC_0);
						setStep(1);
					}
					else
					{
						play_mp3(0,MUSIC_1);
					}
				}
				break;
		}
	}
}

void init()
{
	//分组 2 3 3 2
	//10个按钮输入
	P00 = 0;
	P01 = 0;
	
	P02 = 0;
	P03 = 0;
	P04 = 0;
	
	P05 = 0;
	P06 = 0;
	P07 = 0;
	
	P20 = 0;
	P21 = 0;

	//10个按钮对应的灯
	P10 = 1;
	P11 = 1;
	
	P12 = 1;
	P13 = 1;
	P14 = 1;
	
	P15 = 1;
	P16 = 1;
	P17 = 1;
	
	P22 = 1;
	P23 = 1;

	//电磁柜
	P24 = 1;
}

void checkButtonInput()
{
	if(P00 == 1)
	{
		groupSelect_0 = 1;
		return;
	}
	if(P01 == 1)
	{
		groupSelect_0 = 2;
		return;
	}

	if(P02 == 1)
	{
		groupSelect_1 = 1;
		return;
	}
	if(P03 == 1)
	{
		groupSelect_1 = 2;
		return;
	}
	if(P04 == 1)
	{
		groupSelect_1 = 3;
		return;
	}

	if(P05 == 1)
	{
		groupSelect_2 = 1;
		return;
	}
	if(P06 == 1)
	{
		groupSelect_2 = 2;
		return;
	}
	if(P07 == 1)
	{
		groupSelect_2 = 3;
		return;
	}

	if(P20 == 1)
	{
		groupSelect_3 = 1;
		return;
	}
	if(P21 == 1)
	{
		groupSelect_3 = 2;
		return;
	}
}

void light()
{	
	switch(groupSelect_0)
	{
		case -1:
			P10 = 0;
			P11 = 0;
			break;
		case 1:
			P10 = 1;
			P11 = 0;
			break;
		case 2:
			P10 = 0;
			P11 = 1;
			break;
	}
	switch(groupSelect_1)
	{
		case -1:
			P12 = 0;
			P13 = 0;
			P14 = 0;
			break;
		case 1:
			P12 = 1;
			P13 = 0;
			P14 = 0;
			break;
		case 2:
			P12 = 0;
			P13 = 1;
			P14 = 0;
			break;
		case 3:
			P12 = 0;
			P13 = 0;
			P14 = 1;
			break;
	}
	switch(groupSelect_2)
	{
		case -1:
			P15 = 0;
			P16 = 0;
			P17 = 0;
			break;
		case 1:
			P15 = 1;
			P16 = 0;
			P17 = 0;
			break;
		case 2:
			P15 = 0;
			P16 = 1;
			P17 = 0;
			break;
		case 3:
			P15 = 0;
			P16 = 0;
			P17 = 1;
			break;
	}
	switch(groupSelect_3)
	{
		case -1:
			P22 = 0;
			P23 = 0;
			break;
		case 1:
			P22 = 1;
			P23 = 0;
			break;
		case 2:
			P22 = 0;
			P23 = 1;
			break;
	}
}