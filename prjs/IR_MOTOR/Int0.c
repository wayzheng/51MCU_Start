#include <REGX52.H>

void Int0_Init(void) {
		// 配置外部中断
	
	IT0 = 1;
	IE0 = 0;
	EX0 = 1;
	EA = 1;
	PX0 = 1;
}
//中断器模版
//// 下降沿就是会触发外部中断，通过按键来产生下降沿 通过实验现象也可以看出按钮按下并松手会产生多个下降沿，从而达到多个++
//void Int0_Routine(void) interrupt 0 {
//	Num++;
//}