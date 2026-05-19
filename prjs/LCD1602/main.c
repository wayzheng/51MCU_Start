#include <REGX52.H>
#include "LCD1602.h"
#include "delay.h"
void main(void) {
	LCD_Init();
//	LCD_ShowChar(2, 3, '\''); // 编译器中会讲'A'自动转化为0x41这个数码  
//	LCD_ShowChar(2, 4, 0x41);
//	LCD_ShowString(2, 6, "HELlO 0!"); // 字符串的最后一个字符都是默认是\0字符 注意不是数字0
	LCD_ShowNum(1, 1, 32, 2);
	LCD_ShowSignedNum(1, 5, 48, 2);
	LCD_ShowHexNum(1, 8, 0xA5, 2);
	LCD_ShowBinNum(2, 1, 0x15, 8);
	LCD_ShowChar(2, 9, 0xDF); // 设置左上角的句号字符
	LCD_ShowChar(2, 10, 0xE0); // 显示 尔法
	LCD_ShowString(1, 16, "Welcome To China !");
	while(1) {
		LCD_WriteCommand(0x18); // 实现左移屏幕的效果
		Delay(500);
	}
}