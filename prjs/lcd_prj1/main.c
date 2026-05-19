#include "LCD1602.h"
#include "delay.h"
int Result;
void main(void) {
	int i = 0;
	LCD_Init();
	LCD_ShowChar(1, 1, 'A');
	LCD_ShowString(1, 3, "Hello");
	LCD_ShowNum(1, 9, 123, 3);
	LCD_ShowHexNum(2, 1, 0x1F, 2);
	LCD_ShowBinNum(2, 4, 0xAA, 8);
	Result = 1 + 1;
	LCD_ShowNum(2, 13, Result, 1);
	while(1) {
		for (i = 0; i < 10; i++) {
			LCD_ShowNum(2, 15, i, 1);
			delay(1000);
		}
	}
}