#include <REGX52.H>
#include "Delay.h"
#include "MatrixLED.h"

sbit RCK = P3 ^ 5; // RCLK
sbit SCK = P3 ^ 6;
sbit SER = P3 ^ 4;

#define MATRIX_LED_PORT P0

// 将数组放在flash中，而不是放在ram中来进行存储 通过这种方式来来进行修改之后就会导致变量无法进行修改
signed char code Animation[]=
{
	0x00,0x00,0x1B,0x3C,0xF8,0xFC,0x3B,0x00,0x00,0x1B,0x3C,0xFC,0xFF,0x3A,0x00,0x00,
	0x00,0x00,0x0B,0x1C,0x7C,0x7E,0x1B,0x00,0x00,0x1B,0x3C,0xFC,0xFF,0x3A,0x00,0x00
};



void main() {
	unsigned char i;
	unsigned char offset = 0;
	unsigned char count = 0;
	MatrixLED_Init();
	
	while(1){
		for (i = 0; i < 8; i++) {	
			MatrixLED_ShowColumn(i, Animation[i + offset]);
		}
		count++;
		if (count > 100) {
			count = 0;
			offset += 8;
			if (offset > 24) {
				offset = 0;
			}
		}
	}
}