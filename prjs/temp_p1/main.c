#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "key.h"
#include "AT24C02.h"
#include "DS18B20.h"

float T;
char THight;
char TLow;

unsigned char KeyNum;

void main() {
	KeyNum = key();
	LCD_Init();
	LCD_ShowString(1, 1, "T:");
	LCD_ShowString(2, 1, "TH:");
	LCD_ShowString(2, 9, "TL:");
	while (1) {
		// 温度读取及显示
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		if (T < 0) {
			LCD_ShowChar(1, 3, '-');
			T = -T;
		}
		else {
			LCD_ShowChar(1, 3, '+');
		}
		LCD_ShowNum(1, 4, T, 3);
		LCD_ShowChar(1, 7, '.');
		LCD_ShowNum(1, 8, (unsigned long)(T * 100 + 0.5) % 100, 2);
		if (KeyNum) {
			if (KeyNum == 1) {
				THight++;
			}
			if (KeyNum == 2) {
				THight--;
			}
			if (KeyNum == 3) {
				TLow++;
			}
			if (KeyNum == 4) {
				TLow--;
			}
			// 阈值判断及显示
			LCD_ShowSignedNum(2, 4, THight, 3);
			LCD_ShowSignedNum(2, 12, TLow, 3);
		}
	} 
}