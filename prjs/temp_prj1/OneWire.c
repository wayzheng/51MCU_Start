#include <REGX52.H>

sbit OneWire_DQ = P3 ^ 7;

bit OneWire_Init(void) {
	unsigned char i;
	bit AckBit;
	EA = 0;
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	i = 227; while (--i); // Delay 500us  11.0592Mhz  
	OneWire_DQ = 1;
	i = 29; while (--i); // Delay 70us 11.0592Mhz
	AckBit = OneWire_DQ;
	i = 227; while (--i); // Delay 500us 11.0592Mhz
	EA = 1;
	return AckBit;
}

void OneWire_SendBit(bit Bit) {
	unsigned char j;
	EA = 0; // 关闭中断
	OneWire_DQ = 0;
	j = 2; while(--j);
	OneWire_DQ = Bit;
	j = 22; while(--j);
	OneWire_DQ = 1;
	EA = 1;
}
	

bit OneWire_ReceiveBit (void) {
	unsigned char k;
	bit Bit;
	EA = 0;
	OneWire_DQ = 0;
	k = 1; while(--k); // Delay 5us
	OneWire_DQ = 1;
	k = 1; while(--k); // Delay 5us
	Bit = OneWire_DQ;
	k = 20; while(--k); // Delay 50us 
	EA = 1;
	return Bit;
}

void OneWire_SendByte(unsigned char Byte) {
	unsigned char i;
	for (i = 0; i < 8; i++) {
		OneWire_SendBit(Byte & (0x01 << i));
	}
}

unsigned char OneWire_ReceiveByte(void) {
	unsigned char i;
	unsigned char Byte = 0x00;
	for (i = 0; i < 8; i++) {
		if (OneWire_ReceiveBit()) {
			Byte |= 0x01 << i;
		}
	}
	return Byte;
}