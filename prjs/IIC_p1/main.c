#include <REGX52.H>
#include "delay.h"
#include "key.h"
#include "Nixie.h"
#include "Timer0.h"
#include "I2C.h"
#include "AT24C02.h"


unsigned char KeyNum;
unsigned char Temp;
unsigned char Minute, Second, MiniSecond;
bit RunFlag;

void main() {
	
	Timer0_Init(); 
	
	while(1) {
		 KeyNum = Key();
		
		
				if(KeyNum == 1) {
					RunFlag = !RunFlag;
				}
				if(KeyNum == 2) {
					Minute = 0;
					MiniSecond = 0;
					Second = 0;
				}
				if(KeyNum == 3) {
					AT24C02_WriteByte(0, MiniSecond);
					Delay(5);
					AT24C02_WriteByte(1, Second);
					Delay(5);
					AT24C02_WriteByte(2, Minute);
					Delay(5);
				}
				if(KeyNum == 4) {
					MiniSecond = AT24C02_ReadByte(0);
					Second = AT24C02_ReadByte(1);
					Minute = AT24C02_ReadByte(2);
				}
					
			 Nixie_SetBuf(1, Minute / 10);
			 Nixie_SetBuf(2, Minute % 10);
			 Nixie_SetBuf(3, 11);
			 Nixie_SetBuf(4, Second / 10);
			 Nixie_SetBuf(5, Second % 10);
			 Nixie_SetBuf(6, 11);
			 Nixie_SetBuf(7, MiniSecond / 10);
			 Nixie_SetBuf(8, MiniSecond % 10);		 
	}
}

void Sec_Loop(void) {
	if (RunFlag) {
		MiniSecond++;
		if (MiniSecond >= 100) {
			MiniSecond = 0;
			Second++;
			if (Second >= 60) {
				Minute++;
				Second = 0;
				if (Minute >= 60) {
					Minute = 0;
				}
			}
		}
	};
}

void Timer0_Routine() interrupt 1{
	static unsigned int T0Count1 = 0; // 保证退出函数的时候不丢失数据
	static unsigned int T0Count2 = 0;
	static unsigned int T0Count3 = 0;
	TH0 = 64535 / 256; // 重新赋初始值
	TH1 = 64535 % 256;
	T0Count1++;
	if (T0Count1 >= 10) {
		T0Count1 = 0;
		Key_Loop();
	}
	T0Count2++;
	if (T0Count2 >= 2) {
		T0Count2 = 0;
		Nixie_Loop();
	}
	T0Count3++;
	if (T0Count3 >= 10) {
		T0Count3 = 0;
		Sec_Loop();
	}
		
}