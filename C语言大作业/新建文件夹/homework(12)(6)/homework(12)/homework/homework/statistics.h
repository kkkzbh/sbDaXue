#ifndef STATISTICS___
#define STATISTICS___

#include<time.h>
#define TIME_ 30

#define SEC 4
#define MIN 4
#define HOUR 4
#define MDAY 4
#define MON 4
#define YEAR 8
#define WDAY 4
#define YDAY 8
#define ISDST 4

#define HMS 12
#define YMD 16

#define YMD_HMS 28
#define YMD_W_HMS 32


#define MINOR 18
#define ADULT 55
#define OLD 100

#define Max(A,B,C) A = A > B ? A : B; A = A > C ? A : C


extern Room;
typedef struct tm INT_TIME;

typedef struct
{
	char tm_sec[SEC];	//当前秒
	char tm_min[MIN];	//当前分
	char tm_hour[HOUR];	//当前时
	char tm_mday[MDAY];	//当前月中的天
	char tm_mon[MON];	//当前月
	char tm_year[YEAR];	//当前年
	char tm_wday[WDAY];	//当前星期
	char tm_yday[YDAY];	//当前年的第几天
	char tm_isdst[ISDST];	//当前是否是夏令时 我不知道这什么玩意
	char hms[HMS];	//时:分:秒   它大概是这个字符串
	char ymd[YMD];	//年 月 日   它大概是这个字符串
	char ymd_hms[YMD_HMS]; //年 月 日 时:分:秒
	char ymd_w_hms[YMD_W_HMS]; //年 月 日 星期 时:分:秒
	//如果要添加别的形式的时间 可以跟我说
}TIME;





typedef struct
{
	//time
	char mday[MDAY];
	char mon[MON];
	char year[YEAR];
	char wday[WDAY];
	char hms[HMS];
	char ymd_hms[YMD_HMS];
	char ymd_w_hms[YMD_W_HMS];



	char ymd[YMD];
	int turnover; //营业额
	int total_number;
	int number_minor;
	int number_adult;
	int number_old;

	int number_male;
	int number_female;

	Room* data_room;
	int sz;
	int maxsz;

	int occ_rate; //入住率 是%的左部分 不是小数


}DATA;


typedef struct
{
	DATA* data;
	int sz;
	int maxsz;
}DATA_BASE;


typedef struct
{
	char (*ymd)[YMD];
	int sz;
	int maxsz;
}DATE;


TIME* CreateTime();

TIME* refresh_time(TIME* TIM);

void DeCreateTime(TIME* TIM);

DATA_BASE* CreateDataBase();

void BaseAlloc(DATA_BASE* base);

void RomAlloc_(DATA* data);

DATE* CreateDate();

void DatAlloc(DATE* dat);

void FindHistoryDat(Reserve_manage* Res, DATE* dat);

void sta(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res, DATA_BASE* base, DATE* dat);

void sta_start(DATA_BASE* base, DATE* dat);

void sta_Exit(DATA_BASE* base, DATE* dat);

void menu_sta(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res, DATA_BASE* base, DATE* dat);

void menu_analyse(DATA_BASE* base, const int i);

#endif