#include "LCD1602.h"
#include "delay.h"
#include "matrix_key.h"
/**
*@brief 矩阵键盘显示按键的键码 并显示 hello world
  *@param 无
  *@retvel  
  */
unsigned char KeyNum;
void main() {  
	LCD_Init();
	LCD_ShowString(1, 1, "hello world");
	while(1) {
		KeyNum = Matrix_Key();
		if(KeyNum) { // 通过使用if函数来防止最后的显示结果被覆盖
			LCD_ShowNum(2, 1, KeyNum, 2);
		}
	}
} 