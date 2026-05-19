#include <REGX52.H>
// 独立按键来控制led来显示二进制
void Delayxms(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;
	while(xms--) { //后置减减 先进行判断 然后再进行自减操作
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

void main() {
	unsigned char LEDNum = 0;
	while(1) {
		if (P3_1 == 0) {
			Delayxms(20);
			while (P3_1 == 0);
			Delayxms(20);
			// 一开始是1111_1111
			// P2++; // 通过led显示来判断按键的按下的次数 以二进制的形式来进行显示
			
			LEDNum++;
			P2 = ~LEDNum;
		}
	}
}