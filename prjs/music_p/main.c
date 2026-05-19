#include <REGX52.H>
#include "Timer0.h"
#include "Delay.h"

#define SPEED 500

// 获取Buzzer对应的位值并进行处理
sbit Buzzer = P2 ^ 5;

unsigned int code FreqTable[36] = {
    /* 中音区 */
    63777, 63872, 63969, 64054, 64140, 64216,
    64291, 64360, 64426, 64489, 64547, 64607,

    /* 高音区 */
    64655, 64704, 64751, 64795, 64837, 64876,
    64913, 64948, 64981, 65012, 65042, 65070,

    /* 倍高音区 */
    65095, 65120, 65143, 65166, 65187, 65206,
    65224, 65242, 65259, 65274, 65289, 65303
};

#define R   255   // 休止符

/* 中音区 */
#define M1  0     // 中音1 Do
#define M1S 1
#define M2  2     // 中音2 Re
#define M2S 3
#define M3  4     // 中音3 Mi
#define M4  5     // 中音4 Fa
#define M4S 6
#define M5  7     // 中音5 Sol
#define M5S 8
#define M6  9     // 中音6 La
#define M6S 10
#define M7  11    // 中音7 Si

/* 高音区 */
#define H1  12
#define H1S 13
#define H2  14
#define H2S 15
#define H3  16
#define H4  17
#define H4S 18
#define H5  19
#define H5S 20
#define H6  21
#define H6S 22
#define H7  23

/* 倍高音区 */
#define HH1 24
#define HH2 26
#define HH3 28
#define HH4 29
#define HH5 31
#define HH6 33
#define HH7 35

unsigned int ReloadValue;

unsigned char Music_Twinkle_Note[] = {
    M1, M1, M5, M5, M6, M6, M5,
    M4, M4, M3, M3, M2, M2, M1,

    M5, M5, M4, M4, M3, M3, M2,
    M5, M5, M4, M4, M3, M3, M2,

    M1, M1, M5, M5, M6, M6, M5,
    M4, M4, M3, M3, M2, M2, M1
};

unsigned char Music_Twinkle_Beat[] = {
    1, 1, 1, 1, 1, 1, 2,
    1, 1, 1, 1, 1, 1, 2,

    1, 1, 1, 1, 1, 1, 2,
    1, 1, 1, 1, 1, 1, 2,

    1, 1, 1, 1, 1, 1, 2,
    1, 1, 1, 1, 1, 1, 2
};

/**
  *@brief 设置对应音节的频率 利用定时起来进行产生
	*@param 对应的音节0 到 35 还有一个 255表示停顿
  *@retvel 无
  */

void Buzzer_SetNote(unsigned char note)
{
    if (note == R)
    {
        TR0 = 0;
        Buzzer = 0;
        return;
    }

    ReloadValue = FreqTable[note];

    TH0 = ReloadValue >> 8;
    TL0 = ReloadValue & 0xFF;

    TR0 = 1; // 每演奏一次就将定时器进行关闭
}
/**
  *@brief 按照一定的时间来进行播放
	*@param 简谱的每一个音节组成的数组 简谱的每一个音播放的时间 简谱的整个的长度
  *@retvel 无
  */

void PlayMusic(unsigned char *note, unsigned char *beat, unsigned char len)
{
    unsigned char i;

    for (i = 0; i < len; i++)
    {
        Buzzer_SetNote(note[i]);

        Delay(beat[i] * SPEED);

        TR0 = 0;
        Buzzer = 0;

        Delay(100);
    }
}
/**
  *@brief 主函数 来进行音乐的播放
  *@param
  *@retvel
  */
void main() {
	Timer0_Init(); // 定时器进行初始化
	while(1) {
		PlayMusic(Music_Twinkle_Note,Music_Twinkle_Beat,sizeof(Music_Twinkle_Note));
		Delay(2000);
	}
}

// 终端函数 产生对应的频率
void Timer0_Routine(void) interrupt 1
{
    TH0 = ReloadValue / 256;
    TL0 = ReloadValue % 256;
		Buzzer = !Buzzer; // 产生一个特定频率的之中
}