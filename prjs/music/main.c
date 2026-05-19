#include <REGX52.H>
#include "Timer0.h"
#include "Delay.h"
#include "key.h"
#include "Nixie.h"
#include "Buzzer.h"

unsigned int i;
unsigned char KeyNum;

void main() {
	
	Nixie(1, 0);
	while(1) {
		KeyNum = key();
		if (KeyNum) {
			Buzzer_Time(100);
		}
	}
}