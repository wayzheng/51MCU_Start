#include <REGX52.H>
/**
*@brief 串口初始化 波特率为4800 @ 11.0592Mhz
  *@param 无
  *@retvel 无
  */
void UART_Init() {
	SCON = 0x40;
	PCON |= 0x80;		//使能波特率倍速位SMOD
	// uart只能对定时器1
	// TMOD进行配置 来对定时器的模式来进行配置 工作在模式1
	// TMOD = 0x01; // 0000_0001
	TMOD = TMOD & 0x0F; // 工作再模式1的配置
	TMOD = TMOD | 0x20; // 
	// 上面两句实现了将TMOD置为0x01的操作 因为TMOD只支持段寻址不支持位寻址
	// 对TCON来进行配置 对timer来进行配置
	TF0	= 0; // 清除TF0标志
	TR0 = 1; // 定时器从0开始计时
	TH0 = 64535 / 256; // 得到高位
	TL0 = 64535 % 256 + 1; // 得到低位
	TL1 = 0xF4;			//设置定时初始值
	TH1 = 0xF4;			//设置定时重载值	
	ET0 = 1; // 允许中断
	EA = 1;  // 允许总中断
	PT0 = 0; // 中断优先级为0
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
}

/**
  *@brief 串口发送一个字节数据
  *@param Byte 8bits 就是要发送的一个字节的数据
  *@retvel 无
  */
void UART_SendByte(unsigned char Byte) {
	SBUF = Byte;
	while(TI == 0);
	TI = 0;
}