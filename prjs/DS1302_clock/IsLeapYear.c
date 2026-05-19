/**
  *@brief 判断是否是闰年
  *@param 年份
  *@retvel 返回是否是闰年的判断结果 1 表示是 0 表示不是
  */
unsigned char IsLeapYear(unsigned char year)
{
    unsigned int y;

    y = 2000 + year;   // 例如 DS1302_Time[0] = 24 表示 2024 年

    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/**
  *@brief 获取当前年当前月的最大天数
  *@param 年份 月份
  *@retvel 天数 闰年2月返回29 非闰年2月返回28
  */
unsigned char GetMonthDays(unsigned char year, unsigned char month)
{
    switch (month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;

        case 4:
        case 6:
        case 9:
        case 11:
            return 30;

        case 2:
            if (IsLeapYear(year))
            {
                return 29;
            }
            else
            {
                return 28;
            }

        default:
            return 31;
    }
}