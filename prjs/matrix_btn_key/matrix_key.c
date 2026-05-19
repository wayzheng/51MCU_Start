#include <REGX52.H>
#include "delay.h"
unsigned char Matrix_Key() {
	unsigned char key_number = 0;
	// 数码管扫描
	P1 = 0xFF;
	P1_3 = 0; // 第一列
	if (P1_7 == 0) {Delay(20); while(P1_7 == 0); key_number = 1;};
	if (P1_6 == 0) {Delay(20); while(P1_6 == 0); key_number = 5;};
	if (P1_5 == 0) {Delay(20); while(P1_5 == 0); key_number = 9;};
	if (P1_4 == 0) {Delay(20); while(P1_4 == 0); key_number = 13;};
	
	P1 = 0xFF;
	P1_2 = 0; // 第二列
	if (P1_7 == 0) {Delay(20); while(P1_7 == 0); key_number = 2;};
	if (P1_6 == 0) {Delay(20); while(P1_6 == 0); key_number = 6;};
	if (P1_5 == 0) {Delay(20); while(P1_5 == 0); key_number = 10;};
	if (P1_4 == 0) {Delay(20); while(P1_4 == 0); key_number = 14;};
	
	P1 = 0xFF;
	P1_1 = 0; // 第三列
	if (P1_7 == 0) {Delay(20); while(P1_7 == 0); key_number = 3;};
	if (P1_6 == 0) {Delay(20); while(P1_6 == 0); key_number = 7;};
	if (P1_5 == 0) {Delay(20); while(P1_5 == 0); key_number = 11;};
	if (P1_4 == 0) {Delay(20); while(P1_4 == 0); key_number = 15;};
	
	P1 = 0xFF;
	P1_0 = 0; // 第四列
	if (P1_7 == 0) {Delay(20); while(P1_7 == 0); key_number = 4;};
	if (P1_6 == 0) {Delay(20); while(P1_6 == 0); key_number = 8;};
	if (P1_5 == 0) {Delay(20); while(P1_5 == 0); key_number = 12;};
	if (P1_4 == 0) {Delay(20); while(P1_4 == 0); key_number = 16;};
	
	return key_number;
}