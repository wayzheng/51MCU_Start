#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"
#include "uart.h"
/**
  *@brief
  *@param
  *@retvel
  */
unsigned char Sec;

void main() {
	UART_Init();
	
	while(1) {
		UART_SendByte(Sec);
		Sec++;
		Delay(1000);
	}
}