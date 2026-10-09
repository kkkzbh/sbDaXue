#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#define MAXMUM 15


typedef struct
{
	char data[MAXMUM];
	int late;
}cstack;

typedef struct
{
	int data[MAXMUM];
	int late;
}stack;

typedef struct
{
	double data[MAXMUM];
	int late;
}dstack;


//创建一个空栈 （char)
cstack* CreatStack_char();

//创建一个空栈 (int)
stack* CreatStack();

//创建一个空栈 double
dstack* CreatStack_double();

//压栈char
void Push_char(char x, cstack* stack);

//压栈int
void Push(int x, stack* stack);

//压栈double
void Push_double(double x, dstack* stack);

//修饰操作符
int Modify(char x);

//是否入栈？
int IsPush(int x, stack* stack);

//弹出栈顶元素 int
int POP(stack* stack);

//弹出栈顶元素 char
char POP_char(cstack* stack);

//弹出栈顶元素 double
double POP_double(dstack* stack);

//计算 int
void Caculate(char op, stack* stack);

//计算 double
void Caculate_double(char op, dstack* stack);

//Pow
double Pow(double x, int y);