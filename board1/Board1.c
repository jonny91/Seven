#include <STC89C5xRC.H>
#include "BackRoom.h"
#include "Board1.h"
#include "uart.h"
#include "mp3.h"


void start();
void init();
void firstOpen();
void put();

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
				start();
				break;
			case 1:
				firstOpen();
				break;
			case 2:
				put();
				break;
		}
	}			
}

void init()
{
	P00 = 0; //进门电磁锁
	P01 = 0;
	P02 = 0;
	P03 = 0;//开过电磁锁
	P04 = 0;
	P05 = 0;
	P06 = 0;//ABC对应摆放
	P20 = 1;//第二个房间的门
	P07 = 0;//D对应摆放
	P21 = 1;//第三个房间的门
	P11 = 0;//E对应摆放
	P22 = 1;//第四个房间的门
	P23 = 0;//第四个房间激活FH的牌子摆放
	P24 = 1;//手铐开关输出
	P25 = 0;
	P26 = 0;//FH对应摆放
	P27 = 1;//第一个房间的门
}

void start()
{
	//关门了
	if(P00 == 1)
	{
		delay_ms(5000);
		if(P00 == 1)
		{
			play_mp3(0,MUSCI_INDOOR);
			setStep(1);
		}
	}
}

void firstOpen() //ABC都开过柜子
{
	int isA = 0;
	int isB = 0;
	int isC = 0;
	while(1)
	{
		if(P01 == 1)
		{
			isA = 1;
		}
		if(P02 == 1)
		{
			isB = 1;
		}
		if(P03 == 1)
		{
			isC = 1;
		}
		//三个柜子都开过了
		if((isA == 1)&&(isB == 1)&&(isC == 1))
		{
			delay_ms(50);
			if((isA == 1)&&(isB == 1)&&(isC == 1))
			{
				setStep(2);
				return;
			}
		}
	}
}

int isEnter0 = 0;
int isEnter1 = 0;
int isEnter2 = 0;

void put()
{
	while(1)
	{
        //ABC三个对应摆放都放着
        if((P04 == 1)&&(P05 == 1)&&(P06 == 1)&&(isEnter0 == 0))
        {
            delay_ms(50);
            if((P04 == 1)&&(P05 == 1)&&(P06 == 1)&&(isEnter0 == 0))
            {
                isEnter0 = 1;
                P20 = 0;//打开第二个房间的门
                play_mp3(0,MUSIC_OUTDOOR2);//触发录音203(正确反馈和下一组机关提示)
                continue;
            }
        }
        
        if((P07 == 1)&&(P04 == 1)&&(P05 == 1)&&(P06 == 1)&&(isEnter1 == 0))
        {
            delay_ms(50);
            if((P07 == 1)&&(P04 == 1)&&(P05 == 1)&&(P06 == 1)&&(isEnter1 == 0))
            {
                isEnter1 = 1;
                P21 = 0;//打开房间3的门
                play_mp3(0,MUSIC_OUTDOOR3);
                continue;
            }
        }
        
        if((P11 == 1)&&(P07 == 1)&&(P04 == 1)&&(P05 == 1)&&(P06 == 1)&&(isEnter2 == 0))
        {
            delay_ms(50);
            if((P11 == 1)&&(P07 == 1)&&(P04 == 1)&&(P05 == 1)&&(P06 == 1)&&(isEnter2 == 0))
            {
                isEnter2 = 1;
                P22 = 0;//打开房间4的门
                play_mp3(0,MUSIC_OUTDOOR4);
                continue;
            }
        }
        
        //P23开关开着 P25 P26对应摆放放对了
        if((P23 == 1)&&(P25 == 1)&&(P26 == 1)&&(P11 == 1)&&(P07 == 1)&&(P04 == 1)&&(P05 == 1)&&(P06 == 1))
        {
            delay_ms(50);
            if((P23 == 1)&&(P25 == 1)&&(P26 == 1)&&(P11 == 1)&&(P07 == 1)&&(P04 == 1)&&(P05 == 1)&&(P06 == 1))
            {
                P24 = 0;//关闭手铐开关
                
                P27 = 0;//打开门
                play_mp3(0,MUSIC_POLICE_WIN);//警察胜利
                setStep(3);
                return;
            }
        }


	}	
}
