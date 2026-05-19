#include <REGX52.H>
#include "Delay.h"
sbit RCK = P3 ^ 5; // RCLK
sbit SCK = P3 ^ 6;
sbit SER = P3 ^ 4;

#define MATRIX_LED_PORT P0
/**
  *@brief 74HC595写入一个字节
  *@param 要写入的字节
  *@retvel 
  */
void _74HC595_WriteByte(unsigned char Byte) {
//	SER = Byte&0x80; // 非零即1
//	SCK = 1;
//	SCK = 0;
//	SER = Byte&0x40;
//	SCK = 1;
//	SCK = 0;
//	SER = Byte&0x20;
//	SCK = 1;
//	SCK = 0;
//	SER = Byte&0x10;
//	SCK = 1;
//	SCK = 0;
	
	unsigned char i;
	for (i = 0; i < 8; i++) {
		SER = Byte & (0x80 >> i);
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;
	RCK = 0;
}

/**
	*@brief led显示屏显示一列的数据 
*@param 第一个参数是要选择的列，范围是0到7，0在最左边，第二个参数是显示参数，选择的列的数据，高位在上，1表示亮，表示的是灭
  *@retvel
 */
void MatrixLED_ShowColumn(unsigned char Column, unsigned char Data) {
	_74HC595_WriteByte(Data);
	P0 = ~(0x80>>Column);
}


void main() {
	SCK = 0;
	RCK = 0;

	while(1){
		MatrixLED_ShowColumn(0, 0x3C);
		Delay(1);
		MatrixLED_ShowColumn(1, 0x42);
		Delay(1);
		MatrixLED_ShowColumn(2, 0xA9);
		MatrixLED_ShowColumn(3, 0x85);
		MatrixLED_ShowColumn(4, 0x85);
		MatrixLED_ShowColumn(5, 0xA9);
		MatrixLED_ShowColumn(6, 0x62);
		MatrixLED_ShowColumn(7, 0x3C);
	}
}