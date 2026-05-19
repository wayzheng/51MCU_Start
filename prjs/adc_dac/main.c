#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "XPT2046.h"

unsigned int ADValue1, ADValue2, ADValue3;

void main() {
	LCD_Init();
	// 使用的时候需要将DS18B20给拔掉
	LCD_ShowString(1, 1, "ADJ");
	LCD_ShowString(1, 7, "NTC");
	LCD_ShowString(1, 13, "RG");
	while(1) {
		ADValue1 = XPT2046_ReadAD(XPT2046_XP_12);
		LCD_ShowNum(2, 1, ADValue1, 4);
		Delay(10);
		ADValue2 = XPT2046_ReadAD(XPT2046_YP_12);
		LCD_ShowNum(2, 7, ADValue2, 4);
		Delay(10);
		ADValue3 = XPT2046_ReadAD(XPT2046_VBAT_12);
		LCD_ShowNum(2, 13, ADValue3, 4);
		Delay(10);		
	}
}