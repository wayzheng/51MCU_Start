#include <REGX52.H>

// 按键的消抖方式
// 通过使用delay延时10ms来进行消抖

void Delaymms(unsigned int m)	//@11.0592MHz
{
	unsigned char data i, j;
	while (m) {
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		m--;
	}
}


void main() {
		while (1) {
				if (P3_1 == 0) {
					Delaymms(20); // 延时20ms 然后再监视按键的状态来进行进一步的判断
					while(P3_1 == 0); // 如果按下按键 一直保持不动
					Delaymms(20); // 发生抖动的时候 也就是要变成1的时候 延时20ms 对稳定状态进行监视
					
					P2_0 = ~P2_0;
				}
				else {
					P2_0 = P2_0;
				}
		}
}
