#include <REGX52.H>
#include "delay.h"
#include "key.h"
#include "Timer1.h"
#include "Nixie.h"
#include "Timer0.h"
#include "IR.h"
#include "Int0.h"
#include "Motor.h"

sbit Motor = P1 ^ 0;
extern unsigned char Counter;
extern unsigned char Compare;
unsigned char Command;
unsigned char Speed;

void main() {
	Motor_Init();
	IR_Init();
	Compare = 0;
	while(1) {
		if (IR_GetDataFlag()) {
			Command = IR_GetCommand();
			if (Command == IR_VOL_ADD) {
				Speed++;
				Speed %= 8;
				if (Speed == 0) {Motor_SetSpeed(0);}
				if (Speed == 1) {Motor_SetSpeed(10);}
				if (Speed == 2) {Motor_SetSpeed(25);}
				if (Speed == 3) {Motor_SetSpeed(40);}
				if (Speed == 4) {Motor_SetSpeed(50);}
				if (Speed == 5) {Motor_SetSpeed(75);}
				if (Speed == 6) {Motor_SetSpeed(90);}
				if (Speed == 7) {Motor_SetSpeed(100);}
			}
			else if (Command == IR_0) {
				Speed = 0;
				Compare = 0;
			}
			else if (Command == IR_VOL_MINUS) {
				if (Speed == 0) {Speed = 0;}
				else {Speed--;}
				if (Speed == 0) {Motor_SetSpeed(0);}
				if (Speed == 1) {Motor_SetSpeed(10);}
				if (Speed == 2) {Motor_SetSpeed(25);}
				if (Speed == 3) {Motor_SetSpeed(40);}
				if (Speed == 4) {Motor_SetSpeed(50);}
				if (Speed == 5) {Motor_SetSpeed(75);}
				if (Speed == 6) {Motor_SetSpeed(90);}
				if (Speed == 7) {Motor_SetSpeed(100);}
			}
			else if (Command == IR_4) {
				Speed = 4;
				Motor_SetSpeed(75);
			}
		}
	  Nixie(1, Speed);
	}
	
}