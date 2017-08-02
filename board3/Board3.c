#include <STC89C5xRC.H>
#include "BackRoom.h"
#include "Board3.h"
#include "uart.h"
#include "mp3.h"


void init();
void checkPuzzle();
void shoot();
void initShootLight();
void handLockOrCard();
void shoot2();

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
				checkPuzzle();
				break;
			case 1:
				shoot();
				break;
			case 2:
				handLockOrCard();
				break;
			case 3:
				shoot2();
				break;
		}
	}			
}

void init()
{
	//拼图机关输入
	P00 = 0;

	initShootLight();


	//10个激光的输入
	P20 = 0;
	P21 = 0;
	P22 = 0;
	P23 = 0;
	P24 = 0;
	P25 = 0;
	P26 = 0;
	P27 = 0;
	P03 = 0;
	P04 = 0;

	//激光正确 打开柜门
	P05 = 1;

	//手铐输入
	P06 = 0;
	//牌子感应开关
	P07 = 1;
	//手铐开关输入
	P32 = 0;

	//2个激光灯
	P33 = 1;
	P35 = 1;
	//2个激光输入
	P34 = 0;
	P36 = 0;
	//最后的门
	P37 = 1;
}

void checkPuzzle()
{
	if(P00 == 1)
	{
		delay_ms(50);
		if(P00 == 1)
		{
			setStep(1);
			play_mp3(0,PUZZLE_CORRECT);//拼图正确
			return;
		}
	}
}

void initShootLight()
{
	//激光的灯
	P10 = 1;
	P11 = 1;
	P12 = 1;
	P13 = 1;
	P14 = 1;
	P15 = 1;
	P16 = 1;
	P17 = 1;
	P01 = 1;
	P02 = 1;
}

void shoot()
{
	int shootStep = 0;
	while(1)
	{
		initShootLight();
		switch(shootStep)
		{
			case 0:
				P10 = 0;
				if(P20 == 1)
				{
					shootStep = 1;
				}
				break;
			case 1:
				P11 = 0;
				if(P21 == 1)
				{
					shootStep = 2;
				}
				break;
			case 2:
				P12 = 0;
				if(P22 == 1)
				{
					shootStep = 3;
				}
				break;
			case 3:
				P13 = 0;
				if(P23 == 1)
				{
					shootStep = 4;
				}
				break;
			case 4:
				P14 = 0;
				if(P24 == 1)
				{
					shootStep = 5;
				}
				break;
			case 5:
				P15 = 0;
				if(P25 == 1)
				{
					shootStep = 6;
				}
				break;
			case 6:
				P16 = 0;
				if(P26 == 1)
				{
					shootStep = 7;
				}		
				break;
			case 7:
				P17 = 0;
				if(P27 == 1)
				{
					shootStep = 8;
				}
				break;
			case 8:
				P01 = 0;
				if(P03 == 1)
				{
					shootStep = 9;
				}		
				break;
			case 9:
				P02 = 0;
				if(P04 == 1)
				{
					shootStep = 10;
				}
				break;
			case 10:
				P05 = 0;
				setStep(2);
				return;
		}
	}
}

void handLockOrCard()
{
	//手铐输入
	if((P32 == 0)&& (P06 == 1))
	{
		//牌子感应关闭
		P07 = 0;
		//照2个灯
		setStep(3);
		return;
	}
}

void shoot2()
{
	int shootStep = 0;

	while(1)
	{
		P33 = 1;
		P35 = 1;
		switch(shootStep)
		{
			case 0:
				P33 = 0;
				if(P34 == 1)
				{
					shootStep = 1;
				}
				break;
			case 1:
				P35 = 0;
				if(P36 == 1)
				{
					shootStep = 2;
				}
				break;
			case 2:
				setStep(4);
				//打开最后的门
				P37 = 0;
				return;
		}
	}

	return;
}