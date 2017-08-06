#include <STC89C5xRC.H>
#include "BackRoom.h"
#include "Board3.h"
#include "uart.h"
#include "mp3.h"


void init();
void checkPuzzle();
void shoot();
void initShootLightOn();
void initShootLightOff();
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

	initShootLightOff();//灯灭


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

void initShootLightOn()//灯亮
{
	//激光的灯
	P10 = 0;
	P11 = 0;
	P12 = 0;
	P13 = 0;
	P14 = 0;
	P15 = 0;
	P16 = 0;
	P17 = 0;
	P01 = 0;
	P02 = 0;
}

void initShootLightOff()//灯灭
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

void shootLightShine()
{
	initShootLightOff();
	delay_ms(100);
	initShootLightOn();
	delay_ms(100);
	initShootLightOff();
	delay_ms(100);
	initShootLightOn();
	delay_ms(100);
	initShootLightOff();
	delay_ms(100);
	initShootLightOn();
	delay_ms(100);
	initShootLightOff();
	delay_ms(100);
	initShootLightOn();
	delay_ms(100);
	initShootLightOff();
}

int shootStep = 0;
void onShootError()
{
	play_mp3(0,SHOOT_ERROR);
	shootLightShine();
	shootStep = 0;
}

void shoot()
{
	initShootLightOff();
	while(1)
	{		
		switch(shootStep)
		{
			case 0:
				P10 = 0;
				if(P20 == 1)
				{
					delay_ms(50);
					if(P20 == 1)
					{
						shootStep = 1;
						
						P10 = 1;
                        
                        delay_ms(3000);
					}
				}
//				if((P21 == 1)||
//				(P22 == 1)||
//				(P23 == 1)||
//				(P24 == 1)||
//				(P25 == 1)||
//				(P26 == 1)||
//				(P27 == 1)||
//				(P03 == 1)||
//				(P04 == 1))
//				{
//					delay_ms(50);
//					if((P21 == 1)||
//					(P22 == 1)||
//					(P23 == 1)||
//					(P24 == 1)||
//					(P25 == 1)||
//					(P26 == 1)||
//					(P27 == 1)||
//					(P03 == 1)||
//					(P04 == 1))
//					{
//						onShootError();
//					}
//				}
				break;
			case 1:
				P11 = 0;
				if(P21 == 1)
				{
					delay_ms(50);
					if(P21 == 1)
					{
						shootStep = 2;
						
						P11 = 1;
                        
                        delay_ms(3000);
					}				
				}
//				if((P20 == 1)||
//				(P22 == 1)||
//				(P23 == 1)||
//				(P24 == 1)||
//				(P25 == 1)||
//				(P26 == 1)||
//				(P27 == 1)||
//				(P03 == 1)||
//				(P04 == 1))
//				{
//					delay_ms(50);
//					if((P20 == 1)||
//					(P22 == 1)||
//					(P23 == 1)||
//					(P24 == 1)||
//					(P25 == 1)||
//					(P26 == 1)||
//					(P27 == 1)||
//					(P03 == 1)||
//					(P04 == 1))
//					{
//						onShootError();
//					}
//				}
				break;
			case 2:
				P12 = 0;
				if(P22 == 1)
				{
					delay_ms(50);
					if(P22 == 1)
					{
						shootStep = 3;
						P12 = 1;
                        delay_ms(3000);
					}
				}
//				if((P20 == 1)||
//				(P21 == 1)||
//				(P23 == 1)||
//				(P24 == 1)||
//				(P25 == 1)||
//				(P26 == 1)||
//				(P27 == 1)||
//				(P03 == 1)||
//				(P04 == 1))
//				{
//					delay_ms(50);
//					if((P20 == 1)||
//					(P21 == 1)||
//					(P23 == 1)||
//					(P24 == 1)||
//					(P25 == 1)||
//					(P26 == 1)||
//					(P27 == 1)||
//					(P03 == 1)||
//					(P04 == 1))
//					{
//						onShootError();
//					}
//				}
				break;
			case 3:
				P13 = 0;
				if(P23 == 1)
				{
					delay_ms(50);
					if(P23 == 1)
					{
						shootStep = 4;
						P13 = 1;
                        delay_ms(3000);
					}
				}
//				if((P21 == 1)||
//				(P22 == 1)||
//				(P20 == 1)||
//				(P24 == 1)||
//				(P25 == 1)||
//				(P26 == 1)||
//				(P27 == 1)||
//				(P03 == 1)||
//				(P04 == 1))
//				{
//					delay_ms(50);
//					if((P21 == 1)||
//					(P22 == 1)||
//					(P20 == 1)||
//					(P24 == 1)||
//					(P25 == 1)||
//					(P26 == 1)||
//					(P27 == 1)||
//					(P03 == 1)||
//					(P04 == 1))
//					{
//						onShootError();
//					}
//				}
				break;
			case 4:
				P14 = 0;
				if(P24 == 1)
				{
					delay_ms(50);
					if(P24 == 1)
					{
						shootStep = 5;
						P14 = 1;
                        delay_ms(3000);
					}
				}
//				if((P21 == 1)||
//				(P22 == 1)||
//				(P23 == 1)||
//				(P20 == 1)||
//				(P25 == 1)||
//				(P26 == 1)||
//				(P27 == 1)||
//				(P03 == 1)||
//				(P04 == 1))
//				{
//					delay_ms(50);
//					if((P21 == 1)||
//					(P22 == 1)||
//					(P23 == 1)||
//					(P20 == 1)||
//					(P25 == 1)||
//					(P26 == 1)||
//					(P27 == 1)||
//					(P03 == 1)||
//					(P04 == 1))
//					{
//						onShootError();
//					}
//				}
				break;
			case 5:
				P15 = 0;
				if(P25 == 1)
				{
					delay_ms(50);
					if(P25 == 1)
					{
						shootStep = 6;
						P15 = 1;
                        delay_ms(3000);
					}
				}
//				if((P21 == 1)||
//				(P22 == 1)||
//				(P23 == 1)||
//				(P24 == 1)||
//				(P20 == 1)||
//				(P26 == 1)||
//				(P27 == 1)||
//				(P03 == 1)||
//				(P04 == 1))
//				{
//					delay_ms(50);
//					if((P21 == 1)||
//					(P22 == 1)||
//					(P23 == 1)||
//					(P24 == 1)||
//					(P20 == 1)||
//					(P26 == 1)||
//					(P27 == 1)||
//					(P03 == 1)||
//					(P04 == 1))
//					{
//						onShootError();
//					}
//				}				
				break;
			case 6:
				P16 = 0;
				if(P26 == 1)
				{
					delay_ms(50);
					if(P26 == 1)
					{
						shootStep = 7;
						P16 = 1;
                        delay_ms(3000);
					}
				}	
//				if((P21 == 1)||
//				(P22 == 1)||
//				(P23 == 1)||
//				(P24 == 1)||
//				(P25 == 1)||
//				(P20 == 1)||
//				(P27 == 1)||
//				(P03 == 1)||
//				(P04 == 1))
//				{
//					delay_ms(50);
//					if((P21 == 1)||
//					(P22 == 1)||
//					(P23 == 1)||
//					(P24 == 1)||
//					(P25 == 1)||
//					(P20 == 1)||
//					(P27 == 1)||
//					(P03 == 1)||
//					(P04 == 1))
//					{
//						onShootError();
//					}
//				}				
				break;
			case 7:
				P17 = 0;
				if(P27 == 1)
				{
					delay_ms(50);
					if(P27 == 1)
					{
						shootStep = 8;
						P17 = 1;
                        delay_ms(3000);
					}
				}
//				if((P21 == 1)||
//				(P22 == 1)||
//				(P23 == 1)||
//				(P24 == 1)||
//				(P25 == 1)||
//				(P26 == 1)||
//				(P20 == 1)||
//				(P03 == 1)||
//				(P04 == 1))
//				{
//					delay_ms(50);
//					if((P21 == 1)||
//					(P22 == 1)||
//					(P23 == 1)||
//					(P24 == 1)||
//					(P25 == 1)||
//					(P26 == 1)||
//					(P20 == 1)||
//					(P03 == 1)||
//					(P04 == 1))
//					{
//						onShootError();
//					}
//				}				
				break;
			case 8:
				P01 = 0;
				if(P03 == 1)
				{
					delay_ms(50);
					if(P03 == 1)
					{
						shootStep = 9;
						P01 = 1;
                        delay_ms(3000);
					}
				}
//				if((P21 == 1)||
//				(P22 == 1)||
//				(P23 == 1)||
//				(P24 == 1)||
//				(P25 == 1)||
//				(P26 == 1)||
//				(P27 == 1)||
//				(P20 == 1)||
//				(P04 == 1))
//				{
//					delay_ms(50);
//					if((P21 == 1)||
//					(P22 == 1)||
//					(P23 == 1)||
//					(P24 == 1)||
//					(P25 == 1)||
//					(P26 == 1)||
//					(P27 == 1)||
//					(P20 == 1)||
//					(P04 == 1))
//					{
//						onShootError();
//					}
//				}				
				break;
			case 9:
				P02 = 0;
				if(P04 == 1)
				{
					delay_ms(50);
					if(P04 == 1)
					{
						shootStep = 10;
						
						P02 = 1;
					}
				}
//				if((P21 == 1)||
//				(P22 == 1)||
//				(P23 == 1)||
//				(P24 == 1)||
//				(P25 == 1)||
//				(P26 == 1)||
//				(P27 == 1)||
//				(P03 == 1)||
//				(P20 == 1))
//				{
//					delay_ms(50);
//					if((P21 == 1)||
//					(P22 == 1)||
//					(P23 == 1)||
//					(P24 == 1)||
//					(P25 == 1)||
//					(P26 == 1)||
//					(P27 == 1)||
//					(P03 == 1)||
//					(P20 == 1))
//					{
//						onShootError();
//					}
//				}
				break;
			case 10:
				P05 = 0;
				play_mp3(0,SHOOT_CORRECT);
                delay_ms(3000);
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
		delay_ms(5000);
		if((P32 == 0)&& (P06 == 1))
		{
			//牌子感应关闭
			P07 = 0;
			//照2个灯
			setStep(3);
			return;
		}
	}
}

void shoot2Shine()
{
	P33 = 0;
	P35 = 0;
	delay_ms(100);
	P33 = 1;
	P35 = 1;
	delay_ms(100);
	P33 = 0;
	P35 = 0;
	delay_ms(100);
	P33 = 1;
	P35 = 1;
	delay_ms(100);
	P33 = 0;
	P35 = 0;
	delay_ms(100);
	P33 = 1;
	P35 = 1;
	delay_ms(100);
	
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
					delay_ms(50);
					if(P34 == 1)
					{
						shootStep = 1;
						P33 = 1;
					}
				}
				if(P36 == 1)
				{
					delay_ms(50);
					if(P36 == 1)
					{
						shootStep = 0;
						play_mp3(0,SHOOT_ERROR_2);
						shoot2Shine();
						delay_ms(1000);
					}
				}
				break;
			case 1:
				setStep(4);
				//打开最后的门
				P37 = 0;
				play_mp3(0,CRIMINAL_WIN);
				return;
		}
	}

	return;
}
