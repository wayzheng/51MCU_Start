#include <REGX52.H>

/**
  *@brief  定时器0初始化，1ms中断一次
  *@param  无
  *@retval 无
  */
void Timer0_Init(void)
{
    // 配置 Timer0 为模式1，16位定时器
    TMOD &= 0xF0;    // 清除 Timer0 的控制位，保留 Timer1
    TMOD |= 0x01;    // Timer0 工作在模式1

    // 定时 1ms，假设晶振 12MHz，传统 12T 模式
    TH0 = (65536 - 1000) / 256;
    TL0 = (65536 - 1000) % 256;

    TF0 = 0;         // 清除溢出标志
    TR0 = 1;         // 启动 Timer0

    ET0 = 1;         // 允许 Timer0 中断
    EA  = 1;         // 开启总中断
    PT0 = 0;         // Timer0 中断优先级低
}

// 定时器模版
/*
void Timer0_Routine(void) interrupt 1
{
    static unsigned int T0Count = 0;

    TH0 = (65536 - 1000) / 256;
    TL0 = (65536 - 1000) % 256;

    T0Count++;

    if (T0Count >= 1000)
    {
        T0Count = 0;
        P2_0 = ~P2_0;
    }
}
*/
