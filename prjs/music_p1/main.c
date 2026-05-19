#include <REGX52.H>
#include "Timer0.h"
#include "Delay.h"

#define SPEED 500
#define GUXIANG_LEN  (sizeof(Music_GuXiang_Note) / sizeof(Music_GuXiang_Note[0]))
	
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

#define R   255     // 休止符

/* 1 = G */

/* 低音区 */
#define L5  2       // 低音5 = D4
#define L6  4       // 低音6 = E4
#define L7  6       // 低音7 = F#4

/* 中音区 */
#define M1  7       // 中音1 = G4
#define M2  9       // 中音2 = A4
#define M3  11      // 中音3 = B4
#define M4  12      // 中音4 = C5
#define M5  14      // 中音5 = D5
#define M6  16      // 中音6 = E5
#define M7  18      // 中音7 = F#5

/* 高音区 */
#define H1  19      // 高音1 = G5
#define H2  21      // 高音2 = A5
#define H3  23      // 高音3 = B5
#define H4  24      // 高音4 = C6
#define H5  26      // 高音5 = D6
#define H6  28      // 高音6 = E6
#define H7  30      // 高音7 = F#6

/* 倍高音区 */
#define HH1 31      // 倍高音1 = G6
#define HH2 33      // 倍高音2 = A6
#define HH3 35      // 倍高音3 = B6

unsigned int ReloadValue;

unsigned char code Music_GuXiang_Note[] = {
    /* 前奏 */
    M5, M5, M5, M5,

    /* 第一段 */
    M3, M5, M6, M3, M1,
    M2, M5, M5,
    M3, M6, M6,
    M2, M7, M3, M5,

    M6,
    M7, M6, M5,
    M3,
    R, L5, L6, M1,

    M2, M3, M2, M1, L6,
    M3, R, L5, L6, M1,
    M2, M3, M2, M1, L5,
    M5, M3, R, L5, L6, M1,

    M2, M3, M2, M1, L6,
    M3, R, L5, L6, M1,
    M2, M3, M2, M1,
    M6, M5,

    M6, M5, M6, M5,
    M5, M3, R, M3, R, M5,
    M6, M5, M6, M5,
    M5, M3, R, M1, M3,

    M2, M1, M2, M1, L6,
    M3, M1, M3,
    M2, M1, M2, M3, M2, M1,
    M6, M7, H1, H2,

    M3, M2, M1,
    M2, M3, M7, H1, H2,
    M3, M6, M6, M5, M4, M3,
    M2, M7, M5, M2, M3,

    M5, M3, M7, M5, M2, M7, M5, M3,
    M3, R, L5, L6, M1,

    /* 第二段重复主旋律 */
    M2, M3, M2, M1, L6,
    M3, R, L5, L6, M1,
    M2, M3, M2, M1, L5,
    M5, M3, R, L5, L6, M1,

    M2, M3, M2, M1, L6,
    M3, R, L5, L6, M1,
    M2, M3, M2, M1,
    M6, M5,

    M6, M5, M6, M5,
    M5, M3, R, M3, R, M5,
    M6, M5, M6, M5,
    M5, M3, R, M1, M3,

    M2, M1, M2, M1, L6,
    M3, M1, M3,
    M2, M1, M2, M3, M2, M1,

    /* 高音段 */
    M6, R, L5, L6, H1,
    H2, H3, H2, H1, H6,
    H3, R, L5, L6, H1,
    H2, H3, H2, H1, M5,

    M5, H3, R, L5, L6, H1,
    H2, H3, H2, H1, H6,
    H3, R, L5, L6, M5,
    M6, H1, H2, H3, H2, H1,

    M6, R, L5, L6, H1,
    H2, H3, H2, H1, H6,
    H3, R, L5, L6, H1,
    H2, H3, H2, H1, M5,

    M5, H3, R, L5, L6, H1,
    H2, H3, H2, H1, H6,

    /* 结尾 */
    H3, R, L5, L6, H1,
    H2, H3, H2, H1,
    M6, R, L5, L6, H1,
    M6,
    M6
};

unsigned char code Music_GuXiang_Beat[] = {
    /* 前奏 */
    4, 4, 4, 4,

    /* 第一段 */
    2, 1, 1, 1, 1,
    2, 1, 1,
    2, 1, 1,
    1, 1, 1, 1,

    4,
    2, 1, 1,
    4,
    1, 1, 1, 1,

    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1, 1,

    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1,
    2, 1, 1, 1,
    3, 1,

    2, 1, 1, 1,
    2, 1, 1, 1, 1, 1,
    2, 1, 1, 1,
    2, 1, 1, 1, 1,

    1, 1, 1, 1, 2,
    2, 1, 1,
    1, 1, 1, 1, 1, 1,
    2, 1, 1, 1,

    2, 1, 1,
    1, 1, 2, 1, 1,
    1, 1, 1, 1, 1, 1,
    1, 1, 2, 1, 1,

    1, 1, 1, 1, 1, 1, 1, 1,
    2, 1, 1, 1, 1,

    /* 第二段重复主旋律 */
    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1, 1,

    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1,
    2, 1, 1, 1,
    3, 1,

    2, 1, 1, 1,
    2, 1, 1, 1, 1, 1,
    2, 1, 1, 1,
    2, 1, 1, 1, 1,

    1, 1, 1, 1, 2,
    2, 1, 1,
    1, 1, 1, 1, 1, 1,

    /* 高音段 */
    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1,

    2, 1, 1, 1, 1, 1,
    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1,

    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1,
    2, 1, 1, 1, 1,

    2, 1, 1, 1, 1, 1,
    2, 1, 1, 1, 1,

    /* 结尾 */
    2, 1, 1, 1, 1,
    2, 1, 1, 1,
    2, 1, 1, 1, 1,
    4,
    4
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
		PlayMusic(Music_GuXiang_Note,Music_GuXiang_Beat,GUXIANG_LEN);
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