#include <REGX52.H>
#include "Delay.h"
#include <INTRINS.h>

sbit Buzzer = P2^5; // 获取第五位 P2 ^ 0就是获取第零位

void Buzzer_Delay500us(void)	//@11.0592MHz
{
	unsigned char data i;
	_nop_();
	i = 227;
	while (--i);
}
/**
  *@brief 蜂鸣器发声多长时间 频率是1kHz
	*@param 发声时间 ms 表示的是发声的时间
  *@retvel 无 NULL
  */
// 此时的时钟频率是1k Hz
void Buzzer_Time(unsigned int ms) {
	unsigned int i;
	for (i = 0; i < ms * 2; i++) {
		Buzzer = !Buzzer;
		Buzzer_Delay500us();
	}
}