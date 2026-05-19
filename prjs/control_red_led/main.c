#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "Timer0.h"
#include "Int0.h"
#include "IR.h"

unsigned char Num;
unsigned int Time;
unsigned int Address;
unsigned int Command;

void main() {
	LCD_Init();
//	LCD_ShowString(1, 1, "A");
	LCD_ShowString(1, 1, "ADDR  CMD  NUM");
	LCD_ShowString(2, 1, "00    00   000");
	IR_Init();
	while(1) {
		if(IR_GetDataFlag() || IR_GetRepeatFlag()) {
			Address = IR_GetAddress();
			Command = IR_GetCommand();
			
			LCD_ShowHexNum(2, 1, Address, 2);
			LCD_ShowHexNum(2, 7, Command, 2);
			
			if (Command == IR_VOL_MINUS) {
				Num--;
			}
			if (Command == IR_VOL_ADD) {
				Num++;
			}
			LCD_ShowNum(2, 12, Num, 3);
		}
	}
}
//// 下降沿就是会触发外部中断，通过按键来产生下降沿 通过实验现象也可以看出按钮按下并松手会产生多个下降沿，从而达到多个++
//void Int0_Routine(void) interrupt 0 {
//	Num--;
//}