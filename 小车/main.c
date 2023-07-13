#include <REGX52.H>
#include "UART.H"
#include "ACTION.H"
#include "TIMER0.H"
#include "TRACK_FINDING.H"
#include "DODGE.H"

unsigned char Flag=0,PWM_Flag=10,Mod_Flag=1;

void main()
{
	Timer0_Init();
	action_Init();
	Uart_Init();
	while(1)
	{
		if(Mod_Flag==1)//蓝牙模式
		{
			if(Flag==0)
			{
				action_stop();
			}
			if(Flag==1)
			{
				action_stright();
			}
			if(Flag==2)
			{
				action_retreat();		
			}
			if(Flag==3)
			{
				action_left();		
			}
			if(Flag==4)
			{
				action_right();		
			}
		}
		if(Mod_Flag==2)//寻迹模式
		{
			PWM_Flag=20;
			Track_Finding();
		}
		if(Mod_Flag==3)//避障模式
		{
			PWM_Flag=15;
			Dodge();
		}
	}
}

/**********************************************************************************
   *  @brief 
   *  @param 
   *  @retval 
**********************************************************************************/

void PWM_Routine() interrupt 1 //PWM调速
{
	static unsigned char Tcount=0;
	TL0 = 0xA4;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值
	Tcount++;
	if(Tcount>=100)
	{
		Tcount=0;
	}
	if(Tcount<PWM_Flag)
	{
		PWM_On();
	}
	else
	{
		PWM_Off();
	}

}

/**********************************************************************************
   *  @brief 
   *  @param 
   *  @retval 
**********************************************************************************/

void Bluetooth_Routine() interrupt 4 //蓝牙控制
{
	unsigned char count=0;
	if(RI==1)
	{
		count=SBUF-48;
		Uart_Send(count+48);
		switch(count)
		{
			//运动控制
			case 0:Flag=0;break;//停止
			case 1:Flag=1;break;//前进
			case 2:Flag=2;break;//后退
			case 3:Flag=3;break;//左转
			case 4:Flag=4;break;//右转
			//档位控制
			case 5:PWM_Flag=20;break;//一档
			case 6:PWM_Flag=60;break;//二档
			case 7:PWM_Flag=100;break;//三档
			//模式控制
			case 8:Mod_Flag=1;break;//蓝牙模式
			case 9:Mod_Flag=2;break;//循迹模式
			case 10:Mod_Flag=3;break;//避障模式
		}
		RI=0;
	}
}