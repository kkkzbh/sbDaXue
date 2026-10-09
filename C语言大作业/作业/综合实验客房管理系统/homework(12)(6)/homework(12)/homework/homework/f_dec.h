#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#include"guest_room.h"
#include"account.h"
#include"statistics.h"
#include"Sort.h"

// ANSI 转义码定义颜色
#define RED_TEXT     "\033[1;31m"
#define GREEN_TEXT   "\033[1;32m"
#define BLUE_TEXT    "\033[1;34m"
#define WHITE_TEXT   "\033[0m"

//写str真的累死我了快
#define cpy(A,B) strcpy(A,B)
#define cmp(A,B) strcmp(A,B)


////////函数声明部分


//创建一个user_manage 对象
user_manage* CreateUserManage();

//创建一个room_manage 对象
room_manage* CreateRoomManage();

//创建一个Reserve_manage 对象
Reserve_manage* CreateReserve();

//主界面的菜单
void menu_main(user_manage* usm);

//用户管理界面	//排版待定 先暂时能看就行
void menu_person(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);

//客房管理界面	//排版待定 先暂时能看就行
void menu_room(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);

//登记用户信息
void register_person(user_manage* usm);

//开辟user_manage对象的内存
int UsmAlloc(user_manage* usm);
int RomAlloc(room_manage* rom);
int Resalloc(Reserve_manage* Res);

//作为主要操作区的函数
void action();

//登记房子信息
void register_room(room_manage* rom);

//登记预定房间信息
void register_res(user_manage* usm, room_manage* rom, Reserve_manage* Res);

void menu_Reserve(user_manage* usm,room_manage* rom,acc_data* data,Reserve_manage* Res);

int FindSpareRoom(const char* type, const char* remark, user_manage* usm, room_manage* rom, Reserve_manage* Res);


void oper_person_Adm(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);

void opra_room_Adm(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);

void opra_Reserve_Adm(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);



void getUserInfo(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);

void menu_register_res(user_manage* usm, room_manage* rom, Reserve_manage* Res);

void op_unadm(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);

void menu_main_unadm(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);


void my_register(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);


void CheckOutRoom(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);

void getRoomInfo(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);

void getResInfo(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);


/////////////////////////////////////////////////acc的函数声明





//建立一个账号数据库
acc_data* CreateAccData();



//调整内存
int DataAlloc(acc_data* data);



//查找账号数据库 检验是否可登录账号
int FindAcc(acc_data* data, const char* acc_num, const char* password, int* sz);




//实际上 输入密码是一个非常困难的事情
//所以我要额外用一个函数去实现输入密码
void enter_password(char* password);






void login(user_manage* usm,room_manage* rom, acc_data* data,Reserve_manage* Res);		//登录账号






void register_account(acc_data* data, user_manage* usm);		//注册账号



void menu_login();



//检查是否注册了同样的账号 重了返回 1 ！
int check(const char* acc_num, acc_data* data);


void start(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);

void Exit(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);

void m_log(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res);

void op(user_manage* usm, room_manage* rom, acc_data* data, Reserve_manage* Res,DATA_BASE* base,DATE* dat);

void logout();






















