#include <REGX52.H>
/**
  *@brief 定时器初始化 1ms
  *@param 无
  *@retvel 无
  */
void Timer1_Init(){
	// 使用定时器1
	// TMOD进行配置 来对定时器的模式来进行配置 工作在模式1
	// TMOD = 0x01; // 0000_0001
	TMOD = TMOD & 0x0F; // 将TMOD的低四位清零 并将高四位进行保持不变
	TMOD = TMOD | 0x01; // 前七位保持不变，将最后的一位变为1
	// 上面两句实现了将TMOD置为0x01的操作 因为TMOD只支持段寻址不支持位寻址
	// 对TCON来进行配置 对timer来进行配置
	TF1	= 0; // 清除TF0标志
	TR1 = 1; // 定时器从0开始计时
	TH1 = 0xFF; // 得到高位
	TL1 = 0xA4; // 得到低位
	
	ET1 = 1; // 允许中断
	EA = 1;  // 允许总中断
	PT1 = 0; // 中断优先级为0
}

// 定时器模版
/*
void Timer1_Routine() interrupt 3{
	static unsigned int T0Count = 0; // 保证退出函数的时候不丢失数据
	TH1 = 64535 / 256; // 重新赋初始值
	TL1 = 64535 % 256;
	T0Count++;
	if (T0Count >= 1000) {
		P2_0 = ~P2_0;
		T0Count = 0;
	}
}
*/
