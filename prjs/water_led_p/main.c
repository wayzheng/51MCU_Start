#include <REGX52.H>
// —”≥Ÿ“ª∫¡√Î
void Delay1ms(void)	//@11.0592MHz
{
	unsigned char data i, j;

	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}


void Delayims(unsigned int i) {
	unsigned int m;
	for (m = 0; m < i; m++) {
		Delay1ms();
	}
}
  
void main(void) {
	while(1) {
		P2 = 0xFE;
		Delayims(50);
		P2 = 0x7F;
		Delayims(500);
	}
}
