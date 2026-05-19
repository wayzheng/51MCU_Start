#ifndef __MATRIXLED_H__
#define __MATRIXLED_H__

void MatrixLED_ShowColumn(unsigned char Column, unsigned char Data);
void _74HC595_WriteByte(unsigned char Byte);
void MatrixLED_Init();
#endif