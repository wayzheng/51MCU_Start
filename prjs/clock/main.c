#include "LCD1602.h"
#include "Timer0.h"
#include <REGX52.H>
#include "Delay.h"

unsigned char Sec;
unsigned char Min;
unsigned char Hour;
void main() {
	Timer0_Init();
	LCD_Init();
	LCD_ShowString(1, 1, "Clock:");

	while(1) {
		LCD_ShowString(2, 8, ":");
		LCD_ShowString(2, 5, ":");
		LCD_ShowNum(2, 6, Min, 2);
		LCD_ShowNum(2, 9, Sec, 2);
		if (Hour < 10) {
			LCD_ShowString(2, 3, " ");
			LCD_ShowNum(2, 4, Hour, 1);
		}
		else {
			LCD_ShowNum(2, 3, Hour, 2);
		}
	}
}

void Timer0_Routine() interrupt 1{
	static unsigned int T0Count = 0; // 保证退出函数的时候不丢失数据 如果没有static 那每次执行这个操作的时候会导致要重新对T0Count赋值 static 保证了这个变量只初始化一次，以后每次进入到中断函数，他都是会保留上一次的值
	TH0 = 64535 / 256; // 重新赋初始值
	TL0 = 64535 % 256 + 1;
	T0Count++;
	if (T0Count >= 1) {
		Sec++;
		T0Count = 0;
		if (Sec >= 60) {
			Min++;
			Sec = 0;
			if (Min >= 60) {
				Hour++;
				Min = 0;
				if (Hour >= 24) {
					Hour = 0;
				}
			}
		}
	}
}
