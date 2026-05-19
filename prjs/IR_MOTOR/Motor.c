#include <REGX52.H>
#include "Timer1.h"
#include "key.h"

sbit Motor = P1 ^ 0;

unsigned char Counter, Compare;

void Motor_Init(void) {
	Timer1_Init();
}

void Motor_SetSpeed(unsigned char Speed) {
	Compare = Speed;
}

void Timer1_Routine() interrupt 3{
	// static unsigned int T0Count = 0; // 保证退出函数的时候不丢失数据
	static unsigned int Count0;
	TL1 = 0xA4; // 重新赋初始值
	TH1 = 0xFF;
	Counter++;
	Counter %= 100;
	if (Counter < Compare) {
		Motor = 1;
	}
	else {
		Motor = 0;
	}
	Count0++;
	if (Count0 >= 200) { // 每隔20ms对btn进行检测是否按下并进行更新值
		Key_Loop();
		Count0 = 0;
	}
}