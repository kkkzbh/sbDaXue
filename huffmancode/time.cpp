//
// Created by k on 24-6-4.
//

#include"time"

M_t M_time;

//typedef struct
//{
//	char tm_sec[SEC];	//当前秒
//	char tm_min[MIN];	//当前分
//	char tm_hour[HOUR];	//当前时
//	char tm_mday[MDAY];	//当前月中的天
//	char tm_mon[MON];	//当前月
//	char tm_year[YEAR];	//当前年
//	char tm_wday[WDAY];	//当前星期
//	char tm_yday[YDAY];	//当前年的第几天
//	char tm_isdst[ISDST];	//当前是否是夏令时 我不知道这什么玩意
//	char hms[HMS];	//时:分:秒   它大概是这个字符串
//	char ymd[YMD];	//年 月 日   它大概是这个字符串
//	char ymd_hms[YMD_HMS]; //年 月 日 时:分:秒
//	char ymd_w_hms[YMD_W_HMS]; //年 月 日 星期 时:分:秒
//	//如果要添加别的形式的时间 可以跟我说
//}TIME;

TIME* refresh_time(TIME* TIM)
{
    if (NULL == TIM)
    {
        perror("TIM == NULL!! ");
        return NULL;
    }
    time_t current_time = 0;
    time(&current_time);
    INT_TIME* t = localtime(&current_time);
    strftime(TIM->tm_year, sizeof(TIM->tm_year), "%Y", t);
    strftime(TIM->tm_mon, sizeof(TIM->tm_mon), "%m", t);
    strftime(TIM->tm_mday, sizeof(TIM->tm_mday), "%d", t);
    strftime(TIM->tm_hour, sizeof(TIM->tm_hour), "%H", t);
    strftime(TIM->tm_min, sizeof(TIM->tm_min), "%M", t);
    strftime(TIM->tm_sec, sizeof(TIM->tm_sec), "%S", t);
    strftime(TIM->tm_wday, sizeof(TIM->tm_wday), "%a", t);
    strftime(TIM->tm_yday, sizeof(TIM->tm_yday), "%j", t);
    strftime(TIM->tm_isdst, sizeof(TIM->tm_isdst), "%Z", t);
    strftime(TIM->hms, sizeof(TIM->hms), "%H:%M:%S", t);
    strftime(TIM->ymd, sizeof(TIM->ymd), "%Y %m %d", t);
    strftime(TIM->ymd_w_hms, sizeof(TIM->ymd_w_hms), "%Y %m %d %wday %H:%M:%S", t);
    strftime(TIM->ymd_hms, sizeof(TIM->ymd_hms), "%Y %m %d %H:%M:%S", t);
    return TIM;
}

TIME* referesh()
{
    return refresh_time(M_time.tim);
}