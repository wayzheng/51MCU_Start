#include "Delay.h"
#include <REGX52.H>  // 由于后面的操作对寄存器进行了操作 所以需要包括这个头文件来进行操作

unsigned char NixieTable[12] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00, 0x40};

unsigned char Nixie_Buffer[9] = {0, 10, 10, 10, 10, 10, 10, 10, 10};

void Nixie_SetBuf(unsigned char Location, unsigned char Number) {
	Nixie_Buffer[Location] = Number;
}
void Nixie_Scan(unsigned char Location, unsigned char Number) {	
	P0 = 0x00;
	switch (Location){
		case 1: P2_4 = 1; P2_3 = 1; P2_2 = 1; break;
		case 2: P2_4 = 1; P2_3 = 1; P2_2 = 0; break;
		case 3: P2_4 = 1; P2_3 = 0; P2_2 = 1; break;
		case 4: P2_4 = 1; P2_3 = 0; P2_2 = 0; break;
		case 5: P2_4 = 0; P2_3 = 1; P2_2 = 1; break;
		case 6: P2_4 = 0; P2_3 = 1; P2_2 = 0; break;
		case 7: P2_4 = 0; P2_3 = 0; P2_2 = 1; break;
		case 8: P2_4 = 0; P2_3 = 0; P2_2 = 0; break;
	}
	P0 = NixieTable[Number];

}

void Nixie_Loop() {
	static unsigned char i = 1;
	Nixie_Scan(i, Nixie_Buffer[i]);
	i++;
	if (i > 8) {i = 1;}
}
 