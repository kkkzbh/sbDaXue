#pragma once




#define ACCOUNT_NUM 36
#define PASSWORD 16
#define KEY 10


#define TRUE 1
#define FALSE 0


typedef struct account
{
	char account_num[ACCOUNT_NUM];		//账号
	char password[PASSWORD];		//密码
	int adm;		//0为非管理员账号 1为管理员账号
	Person user;   //记录着该账号着的个人信息
}account;


typedef struct acc_data	//存储账号数据的数据库
{
	account* account;
	int sz;
	int maxsz;
}acc_data;










