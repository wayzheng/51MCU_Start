#include <REGX52.H>

void main() {
	
	
	// P2 = 0xFE;
	// 通过直接对位来进行操作
	P2_0 = 1;
	while(1) {
		if ((P3_1 == 0) && (P3_0 == 0)) {
			P2_0 = 0;
		}
		else {
			P2_0 = 1;
		}
	}
		
}