#include <REGX52.H>
/**
  *@brief 定时器初始化 1ms
  *@param 无
  *@retvel 无
  */
void Timer0_Init(){
	// TMOD进行配置 来对定时器的模式来进行配置 工作在模式1
	// TMOD = 0x01; // 0000_0001
	TMOD = TMOD & 0xF0; // 将TMOD的低四位清零 并将高四位进行保持不变
	TMOD = TMOD | 0x01; // 前七位保持不变，将最后的一位变为1
	// 上面两句实现了将TMOD置为0x01的操作 因为TMOD只支持段寻址不支持位寻址
	// 对TCON来进行配置 对timer来进行配置
	TF0	= 0; // 清除TF0标志
	TR0 = 0; // 定时器0不进行计时操作
	TL0 = 0x66; // 得到高位
	TH0 = 0xFC; // 得到低位
//	
//	ET0 = 1; // 允许中断
//	EA = 1;  // 允许总中断
//	PT0 = 0; // 中断优先级为0
	
}

// 定时器模版
/*
void Timer0_Routine() interrupt 1{
	static unsigned int T0Count = 0; // 保证退出函数的时候不丢失数据
	TH0 = 64535 / 256; // 重新赋初始值
	TL0 = 64535 % 256;
	T0Count++;
	if (T0Count >= 1000) {
		P2_0 = ~P2_0;
		T0Count = 0;
	}
}
*/

void Timer0_SetCounter(unsigned int Value) {
	TH0 = Value / 256;
	TL0 = Value % 256;
	
}
unsigned int Timer0_GetCounter(void) {
	return ((TH0<<8) | TL0);
}

void Timer0_Run(unsigned char Flag) {
	TR0 = Flag;	
}
