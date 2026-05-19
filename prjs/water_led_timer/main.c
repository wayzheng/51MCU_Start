#include "Timer0.h" 
#include <REGX52.H>
#include "Key.h"
#include <INTRINS.H>

unsigned char KeyNum;
unsigned char LEDMode;

void main() {
	P2 = 0xFE; // 使得最低位0 点亮最低位
	Timer0_Init();
	while(1) {
		KeyNum = key();
		if (KeyNum) {
			if (KeyNum == 1) {
				LEDMode++;
				if (LEDMode >= 2) LEDMode = 0;
			}
		}
	}
}


void Timer0_Routine() interrupt 1{
	static unsigned int T0Count = 0; // 保证退出函数的时候不丢失数据
	TH0 = 64535 / 256; // 重新赋初始值
	TH1 = 64535 % 256;
	T0Count++;
	if (T0Count >= 500) {
		T0Count = 0;
		if (LEDMode == 0) {
			P2 = _crol_(P2, 1);
		}
		else if (LEDMode == 1) {
			P2 = _cror_(P2, 1);
		}
	}
}