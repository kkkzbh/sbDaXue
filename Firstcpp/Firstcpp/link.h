#pragma once

#include "Head.h"

typedef int Elmtype;
#define TEST 15

typedef struct olink
{
	Elmtype Note;
	struct olink* Next;
}Note;

typedef struct olink* pNote;
typedef struct olink* oLink;

/////////////////////////////////////////////////////////////////////
using Elment = int;

struct tlink
{
	struct tlink* Last{ nullptr };
	Elment Note{ 0 };
	struct tlink* Next{ nullptr };
};

using Tnote = struct tlink;
using Pnote = struct tlink*;
using Last = struct tlink*;
using Next = struct tlink*;


using poly = struct poly
{
	double coeff{ 0 };
	double index{ 0 };
	shared_ptr<poly> Next{ nullptr };
};

using polyptr = shared_ptr<poly>;


enum o_select
{
	ENLINK = 1,
	INLINK,
	PRINTLINK,
	INSERT,
	REMOVE,
	EXCHANGE,

};

enum t_select
{
	PUSH = 1,
	PRINT,
	SWAP,
	PRINT2,

};


//当需要使用单链表程序时 加载此函数
pNote o_Link();

//创建一个单链表 返回指向其的地址(头指针)
oLink CreateLink();

//检查单链表是否为空 若是返回1 否则返回0
int isEmpty(oLink List);

//在链表末端插入一个值		//返回插入结点指针！
pNote EnLink(Elmtype X, oLink List);

//在链表首段插入一个值
pNote InLink(Elmtype X, oLink List);

//打印单链表所有的值
void PrintLink(oLink List);

//插入一个值 链表
pNote Insert(Elmtype X, int location, oLink List);
pNote Insert_(Elmtype x, pNote p);

//清空一个链表
void RemoveLink(oLink List);

//打印List1链表 其中仅打印某些位置 这些位置是List2种的所有数
void PrintLost(oLink List1, oLink List2);
void PrintLost_(oLink List1, oLink List2);

//交换指定位置与后一位置两个元素的位置 只通过指针
void Exchange(unsigned location, oLink List);
void Exchange_(unsigned location, oLink List);

//取交集
oLink Intersection(oLink List1, oLink List2);
oLink Intersection_(oLink List1, oLink List2);






//当需要使用双链表程序时 加载此函数
Pnote t_link();

//创建一个双链表 返回头指针
Pnote CreateTlink();

//往双链表的第一个位置插入元素n  //返回插入的值的结点指针
Pnote Push(Elment n, Pnote List);

//打印全部元素
void Print(Pnote List);

//交换给定位置的元素与它后一元素的位置 纯指针交换
void Swap(unsigned location, Pnote List);
void Swap_(unsigned location, Pnote List);

//逆向打印List 双链表
void Print2(Pnote List);















//创建一个多项式
polyptr Create();

//加数
polyptr PushPoly(double cof, double idx, polyptr position);

//打印
void PrintPoly(polyptr Poly);

//求和
polyptr ADD(polyptr Poly1, polyptr Poly2);

//求积
polyptr MUL(polyptr Poly1, polyptr Poly2);