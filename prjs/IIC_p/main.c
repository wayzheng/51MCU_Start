#include <REGX52.H>
#include "delay.h"
#include "key.h"
#include "LCD1602.h"
#include "I2C.h"
#include "AT24C02.h"

unsigned char Data;

void main() {
	LCD_Init();
	LCD_ShowString(1, 1, "Number:");
//	AT24C02_WriteByte(1, 122);
//	Delay(10);
	Data = AT24C02_ReadByte(1);
	LCD_ShowNum(2, 1, Data, 3);
	while(1) {
		
	}
}