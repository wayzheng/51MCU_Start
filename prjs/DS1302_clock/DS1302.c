#include <REGX52.H>

sbit DS1302_SCLK = P3 ^ 6;
sbit DS1302_IO = P3 ^ 4;
sbit DS1302_CE = P3 ^ 5;
// 定义写地址
#define DS1302_SECOND 0x80
#define DS1302_MINUTE 0x82
#define DS1302_HOUR 0x84
#define DS1302_DATE 0x86
#define DS1302_MONTH 0x88
#define DS1302_DAY 0x8A
#define DS1302_YEAR 0x8C

#define DS1302_Write_Protect 0x8E

unsigned char DS1302_Time[] = {26, 5, 16, 17, 3, 30, 6};

/**
  *@brief 对变量进行初始化 
  *@param 时钟信号 使能信号
  *@retvel
  */
void DS1302_Init(void) {
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}

/**
  *@brief 写数据
  *@param Command 给出指令以及位置，Data 给出写的数据
  *@retvel
  */
void DS1302_WriteByte(unsigned char Command, unsigned char Data) {
	unsigned char i;
	DS1302_CE = 1; 
//	DS1302_IO = Command & 0x01;
//	DS1302_SCLK = 1;
//	DS1302_SCLK = 0;
//	
//	DS1302_IO = Command & 0x02;
//	DS1302_SCLK = 1;
//	DS1302_SCLK = 0;
// 	通过使用for循环来进行操作
	for (i = 0; i < 8; i++) {
		DS1302_IO = (Command & (0x01 << i)) ? 1 : 0;
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	
	for (i = 0; i < 8; i++) {
		DS1302_IO = Data & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	DS1302_CE = 0;
}

/**
  *@brief 对位置进行读取
  *@param Command 给出指令
  *@retvel 返回的是读取到的数据
  */
unsigned char DS1302_ReadByte(unsigned char Command) {
	unsigned char Data = 0x00; // 局部变量要进行初始化
	unsigned char i;
	Command |= 0x01;
	DS1302_CE = 1;
	for (i = 0; i < 8; i++) {
		DS1302_IO = (Command & (0x01 << i)) ? 1 : 0;	
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}
//		DS1302_SCLK = 0;
//		DS1302_SCLK = 1;
//		if (DS1302_IO) {
//			Data = Data | 0x01;
//		}
//		DS1302_SCLK = 0;
//		DS1302_SCLK = 1;
//		if (DS1302_IO) {
//			Data = Data | 0x01;
//		}
	for (i = 0; i < 8; i++) {
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		if (DS1302_IO) {
			Data = Data | (0x01 << i);
		}
	}
	DS1302_CE = 0;
	DS1302_IO = 0;
	return Data;
}

/**
*@brief 对DS1302_Time数组继续设置，将十进制转化为BCD码来进行写进去
  *@param 无
  *@retvel 无
  */
void DS1302_SetTime(void) {
	// 关闭写保护机制
	DS1302_WriteByte(DS1302_Write_Protect, 0x00); 
	// 十进制转化为BCD码的格式
	DS1302_WriteByte(DS1302_YEAR, DS1302_Time[0] / 10 * 16 + DS1302_Time[0] % 10); 
	DS1302_WriteByte(DS1302_MONTH, DS1302_Time[1] / 10 * 16 + DS1302_Time[1] % 10);
	DS1302_WriteByte(DS1302_DATE, DS1302_Time[2] / 10 * 16 + DS1302_Time[2] % 10);
	DS1302_WriteByte(DS1302_HOUR, DS1302_Time[3] / 10 * 16 + DS1302_Time[3] % 10);
	DS1302_WriteByte(DS1302_MINUTE, DS1302_Time[4] / 10 * 16 + DS1302_Time[4] % 10);
	DS1302_WriteByte(DS1302_SECOND, DS1302_Time[5] / 10 * 16 + DS1302_Time[5] % 10);
	DS1302_WriteByte(DS1302_DAY, DS1302_Time[6] / 10 * 16 + DS1302_Time[6] % 10);
}
/**
  *@brief 读取时钟信号并对DS1202_Time来来进行更新
  *@param 无
  *@retvel
  */
void DS1302_ReadTime(void) {
	
	DS1302_Time[0] = DS1302_ReadByte(DS1302_YEAR) / 16 * 10 + DS1302_ReadByte(DS1302_YEAR) % 16;
	DS1302_Time[1] = DS1302_ReadByte(DS1302_MONTH) / 16 * 10 + DS1302_ReadByte(DS1302_MONTH) % 16;
	DS1302_Time[2] = DS1302_ReadByte(DS1302_DATE) / 16 * 10 + DS1302_ReadByte(DS1302_DATE) % 16;
	DS1302_Time[3] = DS1302_ReadByte(DS1302_HOUR) / 16 * 10 + DS1302_ReadByte(DS1302_HOUR) % 16;
	DS1302_Time[4] = DS1302_ReadByte(DS1302_MINUTE) / 16 * 10 + DS1302_ReadByte(DS1302_MINUTE) % 16;
	DS1302_Time[5] = DS1302_ReadByte(DS1302_SECOND) / 16 * 10 + DS1302_ReadByte(DS1302_SECOND) % 16;
	DS1302_Time[6] = DS1302_ReadByte(DS1302_DAY) / 16 * 10 + DS1302_ReadByte(DS1302_DAY) % 16;
	
}