#pragma once





#define NAME 36
#define SEX 18
#define IDNUM 18
#define PHONE 18
#define VIP 18



#define ID 16
#define TYPE 16
#define LOCATION 16
#define STATE 36



#define RESERVE_TIME 20
#define REMARK 36
#define AUDIT_STATUS 36
#define REVIEW_REPLY 36




#define EXTEND_TIME 16


#define OUT_TIME 16



#define MINIMUM 8
#define ADDCOUNT 8


#define TMP 40

#define divider "--------------------------------------------\n"

#define sm "------------"


#define RETURN '`';


//待.....
enum menu_main
{


};



//某人的历史入住记录存储
typedef struct history
{
	char type[TYPE];	//住的房间类型
	char reserve_time[RESERVE_TIME];	//预定时间
	int price;	 //消费金额
}history;

//一个人的具体信息
typedef struct Person
{
	int index;	//索引
	char name[NAME];	//名称
	char sex[SEX];	//性别
	char idnum[IDNUM];	//身份证号
	char phone[PHONE];	//电话号码
	char vip[VIP];	//会员状态
	history* history;	//历史入住记录  采用指针以malloc的形式开辟数组
	int history_sz;
	int history_maxsz;
}Person;

//用户管理界面 方便查询和添加用户
typedef struct user_manage
{
	Person* user;	//这里采用指针 以calloc的形式创造数组
	int sz;		//这里就单纯作为记录当前有多少人的数量(不是数组的最大大小)
	int maxsz;  //数组大小
}user_manage;

//单个房间的具体信息
typedef struct Room
{
	int index;	//索引
	char id[ID];	//房号
	char type[TYPE];	//房间类型
	char loaction[LOCATION];	//房间位置
	char state[STATE];	//当前状态
	int state_;
	int price;	//价格
}Room;

//房间管理界面 方便查询和添加每个房间
typedef struct room_manage
{
	Room* room;		//这里同样采用指针 以calloc的形式创造数组
	int sz;		//同记录有多少个房间 而不是数组总大小
	int maxsz;  //数组大小
}room_manage;


//订房信息管理 这里集结了每一条用户的订房记录 可以通过此 查询订房信息等
typedef struct Reserve
{
	int index;	//索引
	char name[NAME];	//用户昵称
	char vip[VIP];	//用户会员状态
	int price;	//用户支付金额
	char reserve_time_date[RESERVE_TIME];	//预定时间
	char reserve_time_day[RESERVE_TIME];	//预定时间
	char type[TYPE];
	char remark[REMARK];	//备注
	char phone[PHONE];	//用户手机号码

	char review_reply[REVIEW_REPLY];	//审核回复 [可以暂时先不管这个]
	char audit_status[AUDIT_STATUS];	//审核状态[可以暂时先不管这个]


}Reserve;

typedef struct Reserve_manage
{
	struct Reserve* Reserve;
	int sz;    //当前大小
	int maxsz;  //数组大小
}Reserve_manage;




/// ///////////////////////////////////////////////////////////////实现的程序 可以先到此为止


//续房信息管理 这里有每一条申请续房的记录 可以查询是否有续房的请求
typedef struct extend
{
	int index;	//索引
	int person_index;	//用户索引
	char vip[VIP];	//会员状态
	int price;	//用户支付金额
	
	char remark[REMARK];	//备注
	char extend_time[EXTEND_TIME];	//续房时间
	char name[NAME];	//昵称
	char phone[PHONE];	//用户电话号码

	char review_reply[REVIEW_REPLY];	//审核回复
	char audit_status[AUDIT_STATUS];	//审核状态

	int sz;  //当前大小
	int maxsz;  //数组大小
}extend;



//退房信息管理 这里反正也就是每条退房的信息了 没啥好说的
typedef struct check_out
{
	int index;	//索引
	int person_index;	//用户索引
	char vip[VIP];	//会员状态
	int price;	//用户支付金额

	char remark[REMARK];	//备注
	char out_time[OUT_TIME];	//退房时间
	char name[NAME];	//昵称
	char phone[PHONE];	//用户电话号码

	char review_reply[REVIEW_REPLY];	//审核回复
	char audit_status[AUDIT_STATUS];	//审核状态

	int sz;  //当前大小
	int maxsz;  //数组大小
}check_out;











