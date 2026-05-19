#include <REGX52.H>

sbit I2C_SCL = P2 ^ 1;
sbit I2C_SDA = P2 ^ 0;
/**
  *@brief 开始阶段，SCL高电平期间，SDA从高电平切换到低电平
  *@param 无
  *@retvel 无
  */
void I2C_Start(void) {
	I2C_SDA = 1;
	I2C_SCL = 1;
	I2C_SDA = 0;
	I2C_SCL = 0;
}
/**
  *@brief 结束阶段 SCL高电平期间 SDA从低电平切换到高电平
  *@param 无
  *@retvel 无
  */
void I2C_Stop(void) {
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
}
/**
	*@brief 发送一个字节 从高位到低位依次来进行提取
	*@param 发送的字节
  *@retvel 无
  */
void I2C_SendByte(unsigned char Byte) {
	unsigned char i;
	for (i = 0; i < 8; i++) {
		I2C_SDA = Byte & (0x80 >> i);
		I2C_SCL = 1;
		I2C_SCL = 0;
	}
}
/**
  *@brief I2C接收一个字节
  *@param 无
  *@retvel 返回接收的一个字节
  */
//unsigned char I2C_ReceiveByte(void) {
//	unsigned char i;
//	unsigned char Byte;
//	I2C_SDA = 1;
//	I2C_SCL = 1;
//	for (i = 0; i < 8; i++) {
//		if (I2C_SDA) {
//			Byte |= (0x80 >> i);
//		}
//		I2C_SCL = 0;
//	}	
//	return Byte;
//}

unsigned char I2C_ReceiveByte(void)
{
	unsigned char i;
	unsigned char Byte = 0;

	I2C_SDA = 1;   // 释放 SDA，让从机控制 SDA

	for (i = 0; i < 8; i++)
	{
		I2C_SCL = 1;   // 第 i 位开始采样

		if (I2C_SDA)
		{
			Byte |= (0x80 >> i);
		}

		I2C_SCL = 0;   // 结束这一位
	}

	return Byte;
}

/**
  *@brief I2C发送一个应答位
	*@param AckBit 应答位 1为非应答 0位应答
  *@retvel 无
  */
void I2C_SendAck(bit AckBit) {
	I2C_SDA = AckBit;
	I2C_SCL = 1;
	I2C_SCL = 0;
}
/**
	*@brief I2C接收一个应答位
  *@param 无
	*@retvel 接收到的应答位
  */
bit I2C_ReceiveAck(void) {
	bit AckBit;
	I2C_SDA = 1;
	I2C_SCL = 1;
	if (I2C_SDA) {AckBit = 1;}
	else {AckBit = 0;}
	I2C_SCL = 0;
	return AckBit;
}