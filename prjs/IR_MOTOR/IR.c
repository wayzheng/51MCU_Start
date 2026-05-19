#include <REGX52.H>
#include "Timer0.h"
#include "Int0.h"

unsigned int IR_Time;
unsigned char IR_State;

unsigned char IR_Data[4];
unsigned char IR_PData;
unsigned char Timer_SetCounter;
unsigned char IR_DataFlag;
unsigned char IR_RepeatFlag;
unsigned char IR_Address;
unsigned char IR_Command;

void IR_Init(void) {
	Timer0_Init();
	Int0_Init();
	
}

unsigned char IR_GetDataFlag(void) {
	if (IR_DataFlag) {
		IR_DataFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_GetRepeatFlag(void) {
	if (IR_RepeatFlag) {
		IR_RepeatFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_GetAddress(void) {
	return IR_Address;
}

unsigned char IR_GetCommand(void) {
	return IR_Command;
}

void Int0_Routine(void) interrupt 0 {
	if (IR_State == 0) {
		Timer0_SetCounter(0);
		Timer0_Run(1);
		IR_State = 1;
	}
	else if (IR_State == 1) {
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if (IR_Time > 11981 && IR_Time < 12902) {
			IR_State = 2;
		}
		else if (IR_Time > 9907  && IR_Time < 10829) {
			IR_RepeatFlag = 1;
			Timer0_Run(0);
			IR_State = 0;
		}
		else {
			IR_State = 1;
		}
	}
	else if (IR_State == 2) {
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if (IR_Time > 571 && IR_Time < 1493) {
			IR_Data[IR_PData / 8] &= ~(0x01 << (IR_PData % 8));  
			IR_PData++;
		}
		else if (IR_Time > 1613 && IR_Time < 2535) {
			IR_Data[IR_PData / 8] |= (0x01 << (IR_PData % 8));
			IR_PData++;
		}
		else {
			IR_PData = 0;
			IR_State = 1;
		}
		if (IR_PData >= 32) {
			IR_PData = 0;
			if ((IR_Data[0] == ~IR_Data[1]) && (IR_Data[2] == ~IR_Data[3])) {
				IR_DataFlag = 1;
				IR_Address = IR_Data[0];
				IR_Command = IR_Data[2];
			}
			Timer0_Run(0);
			IR_State = 0;
		}
	}
}