#include "LCD1602.h"
#include "delay.h"
#include "matrix_key.h"
/**
*@brief 矩阵键盘显示按键的键码 并显示 hello world
  *@param 无
  *@retvel  
  */
unsigned int PassWord;
unsigned char KeyNum;
unsigned char Count;
void main() {  
	LCD_Init();
	LCD_ShowString(1, 1, "Password: ");
	while(1) {
		KeyNum = Matrix_Key();
		if(KeyNum) { // 通过使用if函数来防止最后的显示结果被覆盖
			if(KeyNum <= 10) { // 如果按键按下从S1~S10 输入密码
				if(Count < 4) {	// 如果输入次数小于4
					PassWord *= 10;
					PassWord += KeyNum % 10; 
					Count++; // 记一次加上1
				}
				LCD_ShowNum(2, 1, PassWord, 4);
			}
			else if(KeyNum == 11) { // 如果S11按键按下 进行确认
				if(PassWord == 2345) {
					LCD_ShowString(1, 11, "OK   ");
					PassWord = 0;
					Count = 0;
					LCD_ShowNum(2, 1, PassWord, 4);
				}
				else {
					LCD_ShowString(1, 11, "Wrong");
					PassWord = 0; // 密码清零
					Count = 0; // 计数清零
					LCD_ShowNum(2, 1, PassWord, 4);
				}
			}
			else if(KeyNum == 12) {
				LCD_ShowString(1, 11, "Reset");
				PassWord = 0;
				Count = 0;
				LCD_ShowNum(2, 1, PassWord, 4);
			}
		}
	}
} 