#include <REGX52.H>

// 按下按键实现移位功能
// 延时一毫秒
void Delay(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;
	unsigned int m;
	for (m = 0; m < xms; m++){
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}


void main() {
	unsigned char NUMled = 0;
	P2 = 0xFE;
	while (1) {
		if (P3_1 == 0) {
			Delay(20);
			while(P3_1 == 0);
			Delay(20);
			
			if (NUMled == 7) {
				NUMled = 0;
			}
			else {
				NUMled++;
			}
			P2 = ~(0x01 << NUMled);
		}
		if (P3_0 == 0) {
			Delay(20);
			while(P3_0 == 0);
			Delay(20);
			
			if (NUMled == 0) {
				NUMled = 7;
			}
			else {
				NUMled--;
			}
			P2 = ~(0x01 << NUMled);
		}
	}
}