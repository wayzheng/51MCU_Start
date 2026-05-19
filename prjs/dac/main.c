#include <REGX52.H>
#include "delay.h"
#include "key.h"
#include "Timer0.h"
#include "Nixie.h"

sbit LED = P2 ^ 0;
//unsigned char Counter;
//unsigned char Compare;
//unsigned char KeyNum;
//unsigned char Speed;

//void main() {
//	Timer0_Init();
//	Compare = 0;
//	while(1) {
//		KeyNum = Key();
//		if (KeyNum == 1) {
//			Speed++;
//			Speed %= 8;
//			if (Speed == 0) {Compare = 0;}
//			if (Speed == 1) {Compare = 10;}
//			if (Speed == 2) {Compare = 25;}
//			if (Speed == 3) {Compare = 40;}
//			if (Speed == 4) {Compare = 50;}
//			if (Speed == 5) {Compare = 75;}
//			if (Speed == 6) {Compare = 90;}
//			if (Speed == 7) {Compare = 100;}
//		}
//		if (KeyNum == 2) {
//			Speed = 0;
//			Compare = 0;
//		}
//		if (KeyNum == 3) {
//			if (Speed == 0) {Speed = 0;}
//			else {Speed--;}
//			if (Speed == 0) {Compare = 0;}
//			if (Speed == 1) {Compare = 10;}
//			if (Speed == 2) {Compare = 25;}
//			if (Speed == 3) {Compare = 40;}
//			if (Speed == 4) {Compare = 50;}
//			if (Speed == 5) {Compare = 75;}
//			if (Speed == 6) {Compare = 90;}
//			if (Speed == 7) {Compare = 100;}	
//		}
//		Nixie(1, Speed);
//	}
//	
//}

unsigned char Counter, Compare;
unsigned char i;

void main() {
	Timer0_Init();
	while(1) {
		for (i = 0; i < 100; i++) {
			Compare = i;
			Delay(10);
		}
		for (i = 100; i > 0; i--) {
			Compare = i;
			Delay(10);
		}
	}
}

void Timer0_Routine() interrupt 1{
	// static unsigned int T0Count = 0; // 保证退出函数的时候不丢失数据
	static unsigned int Count0;
	TL0 = 0xA4; // 重新赋初始值
	TH0 = 0xFF;
	Counter++;
	Counter %= 100;
	if (Counter < Compare) {
		LED = 1;
	}
	else {
		LED = 0;
	}
	Count0++;
	if (Count0 >= 200) { // 每隔20ms对btn进行检测是否按下并进行更新值
		Key_Loop();
		Count0 = 0;
	}
	
}