#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"
#include "key.h"
#include "Timer0.h"
#include "IsLeapYear.h"

unsigned char KeyNum;
unsigned char Mode;
unsigned char TimeSelect;
unsigned char TimeSetFlashFlag;

void TimeShow(void) {
		DS1302_ReadTime(); // 进行读取时间之后，并对DS1302_Time数组进行更新
		LCD_ShowNum(1, 1, DS1302_Time[0], 2);
		LCD_ShowNum(1, 4, DS1302_Time[1], 2);
		LCD_ShowNum(1, 7, DS1302_Time[2], 2);
		LCD_ShowNum(2, 1, DS1302_Time[3], 2);
		LCD_ShowNum(2, 4, DS1302_Time[4], 2);
		LCD_ShowNum(2, 7, DS1302_Time[5], 2);
		LCD_ShowNum(2, 10, DS1302_Time[6], 1);
		
}

void TimeSet(void) {

		if (KeyNum == 2) {
			TimeSelect++;
			TimeSelect %= 7; // 加加并越界清零
		}
		if (KeyNum == 3) {
			DS1302_Time[TimeSelect]++;
			if (DS1302_Time[0] > 99) {DS1302_Time[0] = 0;}
			if (DS1302_Time[1] > 12) {DS1302_Time[1] = 1;}
			if (DS1302_Time[2] > GetMonthDays(DS1302_Time[0], DS1302_Time[1])) {DS1302_Time[2] = 1;}
			if (DS1302_Time[3] > 23) {DS1302_Time[3] = 0;}
			if (DS1302_Time[4] > 59) {DS1302_Time[4] = 0;}
			if (DS1302_Time[5] > 59) {DS1302_Time[5] = 0;}
			if (DS1302_Time[6] > 7) {DS1302_Time[6] = 1;}
		}
		if (KeyNum == 4) {
			DS1302_Time[TimeSelect]--;

			if (DS1302_Time[0] > 99)
			{
					DS1302_Time[0] = 99;
			}

			if (DS1302_Time[1] == 0)
			{
					DS1302_Time[1] = 12;
			}
			// 对日进行下界越界的判断
			if (DS1302_Time[2] == 0)
			{
					DS1302_Time[2] = GetMonthDays(DS1302_Time[0], DS1302_Time[1]);
			}
			else if (DS1302_Time[2] > GetMonthDays(DS1302_Time[0], DS1302_Time[1])) {
				DS1302_Time[2] = 1;
			}

			if (DS1302_Time[3] > 23)
			{
					DS1302_Time[3] = 23;
			}

			if (DS1302_Time[4] > 59)
			{
					DS1302_Time[4] = 59;
			}

			if (DS1302_Time[5] > 59)
			{
					DS1302_Time[5] = 59;
			}

			if (DS1302_Time[6] == 0)
			{
					DS1302_Time[6] = 7;
			}
		}
		if (TimeSelect == 0 && TimeSetFlashFlag == 1) {
			LCD_ShowString(1, 1, "  ");
		}
		else {
		LCD_ShowNum(1, 1, DS1302_Time[0], 2);
		}
		if (TimeSelect == 1 && TimeSetFlashFlag == 1) {
			LCD_ShowString(1, 4, "  ");
		}
		else {
			LCD_ShowNum(1, 4, DS1302_Time[1], 2);
		}
		if (TimeSelect == 2 && TimeSetFlashFlag == 1) {
			LCD_ShowString(1, 7, "  ");
		}
		else {
			LCD_ShowNum(1, 7, DS1302_Time[2], 2);
		}
		if (TimeSelect == 3 && TimeSetFlashFlag == 1) {
			LCD_ShowString(2, 1, "  ");
		}
		else {
			LCD_ShowNum(2, 1, DS1302_Time[3], 2);
		}
		if (TimeSelect == 4 && TimeSetFlashFlag == 1) {
			LCD_ShowString(2, 4, "  ");
		}
		else {
			LCD_ShowNum(2, 4, DS1302_Time[4], 2);
		}
		if (TimeSelect == 5 && TimeSetFlashFlag == 1) {
			LCD_ShowString(2, 7, "  ");
		}
		else {
			LCD_ShowNum(2, 7, DS1302_Time[5], 2);
		}
		if (TimeSelect == 6 && TimeSetFlashFlag == 1) {
			LCD_ShowString(2, 10, " ");
		}
		else {
			LCD_ShowNum(2, 10, DS1302_Time[6], 1);
		}
		
		switch (TimeSelect) {
			case 0: {LCD_ShowString(1, 10, "YEAR   "); break;}
			case 1: {LCD_ShowString(1, 10, "MONTH  "); break;}
			case 2: {LCD_ShowString(1, 10, "DATE   "); break;}
			case 3: {LCD_ShowString(1, 10, "HOUR   "); break;}
			case 4: {LCD_ShowString(1, 10, "MINUTE "); break;}
			case 5: {LCD_ShowString(1, 10, "SECOND "); break;}
			case 6: {LCD_ShowString(1, 10, "WEEKDAY"); break;}
		}
		if (TimeSetFlashFlag) {
			LCD_ShowString(2, 12, "SET ");
		}
		else {
			LCD_ShowString(2, 12, "TIME");
		}
}

void main() {
	Timer0_Init();
	LCD_Init();
	DS1302_Init();
	LCD_ShowString(1, 1, "  -  -  ");
	LCD_ShowString(2, 1, "  :  :  [ ] ");
	DS1302_SetTime();  // 设置时钟，只进行一次

	while(1){
		KeyNum = key();
		if (KeyNum == 1) {
			if (Mode == 0) {Mode = 1;}
			else if (Mode == 1) {Mode = 0;DS1302_SetTime();LCD_ShowString(2, 12, "    ");} // 对展示的时间进行刷新 并将原始的字符串进行更新
		}
		switch (Mode) {
			case 0: TimeShow(); break;
			case 1: TimeSet(); break;
		}
	}
}


void Timer0_Routine(void) interrupt 1
{
    static unsigned int T0Count = 0;

    TH0 = (65536 - 1000) / 256;
    TL0 = (65536 - 1000) % 256;

    T0Count++;

    if (T0Count >= 500)
    {
        T0Count = 0;
        TimeSetFlashFlag = !TimeSetFlashFlag; // 每隔0.5秒对逻辑进行取反操作来进行更新
    }
}