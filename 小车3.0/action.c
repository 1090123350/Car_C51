#include <REGX52.H>

sbit IN1 = P3^7;
sbit IN2 = P3^6;
sbit IN3 = P3^5;
sbit IN4 = P3^4;
sbit ENA = P1^3;
sbit ENB = P1^2;

//左轮P3_4 ; P3_5;
//右轮P3_6 ; P3_7;

void action_Init()//初始化，制动状态
{
	IN1=0;IN2=0;
	IN3=0;IN4=0;
}

void action_stright()//前进
{
	IN1=0;IN2=1;//左轮
	IN3=0;IN4=1;//右轮
}

void action_retreat()//后退
{
	IN1=1;IN2=0;//左轮
	IN3=1;IN4=0;//右轮
}

void action_left()//左转
{
	IN1=0;IN2=0;//左轮后退
	IN3=0;IN4=1;//右轮前进
}

void action_right()//右转
{
	IN3=0;IN4=0;//右轮后退
	IN1=0;IN2=1;//左轮前进
}

void action_stop()//停止，两轮均制动
{
	IN1=0;IN2=0;
	IN3=0;IN4=0;
}

void PWM_On()
{
	ENA=1;
	ENB=1;
}

void PWM_Off()
{
	ENA=0;
	ENB=0;
}

void action_stayleft()//原地左转
{
	IN1=1;IN2=0;//左轮后退
	IN3=0;IN4=1;//右轮前进
}

void action_stayright()//原地右转
{
	IN3=1;IN4=0;//右轮后退
	IN1=0;IN2=1;//左轮前进
}

