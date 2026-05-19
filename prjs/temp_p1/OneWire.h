#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

bit OneWire_Init(void);
unsigned char OneWire_ReceiveByte(void);
void OneWire_SendByte(unsigned char Byte);
void OneWire_SendBit(bit Bit);		
bit OneWire_ReceiveBit (void);

#endif