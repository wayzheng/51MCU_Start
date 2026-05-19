#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "key.h"
#include "AT24C02.h"
#include "DS18B20.h"
#include "Timer0.h"

float T;
float T_Show;
char THight;
char TLow;

unsigned char KeyNum;

void main() {
	DS18B20_ConvertT();
	Delay(1000);
	THight = AT24C02_ReadByte(0);
	TLow = AT24C02_ReadByte(1);
	if (THight > 125 || TLow < -55 || THight <= TLow) {THight = 20; TLow = 15;}
	LCD_Init();
	LCD_ShowString(1, 1, "T:");
	LCD_ShowString(2, 1, "TH:");
	LCD_ShowString(2, 9, "TL:");
	LCD_ShowSignedNum(2, 4, THight, 3);
	LCD_ShowSignedNum(2, 12, TLow, 3);
	Timer0_Init();
	while (1) {
		KeyNum = Key();
		// 温度读取及显示
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		if (T < 0) {
			LCD_ShowChar(1, 3, '-');
			T_Show = -T;
		}
		else {
			LCD_ShowChar(1, 3, '+');
			T_Show = T;
		}
		LCD_ShowNum(1, 4, T_Show, 3);
		LCD_ShowChar(1, 7, '.');
		LCD_ShowNum(1, 8, (unsigned long)(T_Show * 100 + 0.5) % 100, 2);
		if (KeyNum) {
			if (KeyNum == 1) {
				THight++;
				if (THight > 125) {THight = 125;}
			}
			if (KeyNum == 2) {
				THight--;
				if (THight < TLow) {THight++;}
			}
			if (KeyNum == 3) {
				TLow++;
				if (TLow > THight) {TLow--;}
			}
			if (KeyNum == 4) {
				TLow--;
				if (TLow < -55) {TLow = -55;}
			}
			// 阈值判断及显示
			LCD_ShowSignedNum(2, 4, THight, 3);
			LCD_ShowSignedNum(2, 12, TLow, 3);
			AT24C02_WriteByte(0, THight);
			AT24C02_WriteByte(1, TLow);
		}
		if (T > THight) {
			LCD_ShowString(1, 13, "OV:H");
		}
		else if (T < TLow) {
			LCD_ShowString(1, 13, "OV:L");
		}
		else {
			LCD_ShowString(1, 13, "OV:N");
		}
	} 
}


void Timer0_Routine() interrupt 1{
	static unsigned int T0Count = 0; // 保证退出函数的时候不丢失数据
	TH0 = 64535 / 256; // 重新赋初始值
	TH1 = 64535 % 256;
	T0Count++;
	if (T0Count >= 20) {
		Key_Loop();
		T0Count = 0;
	}
}