#include <REGX52.H>
#include <INTRINS.H>

void Delay500ms(void)	//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main() {
	P2 = 0xFE; // 1111_1110
	Delay500ms();
	P2 = 0xFD; // 1111_1101
	Delay500ms();
	P2 = 0xFB; // 1111_1011
	Delay500ms();
	P2 = 0xF7; // 1111_0111
	Delay500ms();
	P2 = 0xEF; // 1110_1111
	Delay500ms();
	P2 = 0xDF; // 1101_1111
	Delay500ms();
	P2 = 0xBF; // 1011_1111
	Delay500ms();
	P2 = 0x7F; // 0111_1111
	Delay500ms();
	P2 = 0xBF;
	Delay500ms();
	P2 = 0xDF;
	Delay500ms();
	P2 = 0xEF;
	Delay500ms();
	P2 = 0xF7;
	Delay500ms();
	P2 = 0xFB;
	Delay500ms();
	P2 = 0xFD;
	Delay500ms();
}