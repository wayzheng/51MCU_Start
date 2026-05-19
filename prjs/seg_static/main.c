#include <REGX52.H>
unsigned char NixieTubeTable[17] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x00};

	void Delaymms(unsigned char m)	//@11.0592MHz
{
	unsigned char data i, j;
	while (m--) {
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

void NixieTubeDisplay(unsigned char Location, unsigned char Number) {
	switch(Location) {
		case 1: 
			P2_4 = 1; P2_3 = 1; P2_2 = 1; break;
		case 2:
			P2_4 = 1; P2_3 = 1; P2_2 = 0; break;
		case 3:
			P2_4 = 1; P2_3 = 0; P2_2 = 1; break;
		case 4:
			P2_4 = 1; P2_3 = 0; P2_2 = 0; break;
		case 5:
			P2_4 = 0; P2_3 = 1; P2_2 = 1; break;
		case 6:
			P2_4 = 0; P2_3 = 1; P2_2 = 0; break;
		case 7:
			P2_4 = 0; P2_3 = 0; P2_2 = 1; break;
		case 8:
			P2_4 = 0; P2_3 = 0; P2_2 = 0; break;
		default:
			P2_4 = 0; P2_3 = 0; P2_2 = 0; break;
	}
	
	P0 = NixieTubeTable[Number];
	
	Delaymms(1);
	P0 = 0x00;
}
void main() {
	// 引脚冲突也会导致led灯亮起来
	int i;
	while(1) {
		for (i = 0; i < 8; i++) {
			NixieTubeDisplay(i + 1, i + 1);
		}
	}
}