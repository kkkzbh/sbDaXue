#include<stdio.h>

#define MAXMUM 100

typedef struct
{
	double x[MAXMUM]
	int top;
}stack;


int x(char x)
{
	if(x == '1')
	return 801;
}


stack* CreatStack()
{
	stack* ps = (stack*)malloc(sizeof(stack));
	ps->top = -1;
	return ps;
}

void Push(double x,stack* stack)
{
	stack->x[++top] = x;
}

int main()
{
	int n = 0,m = 0;
	double tmp[MAXMUM] = {0};
	char tmp = 0;
	stack* ps = CreatStack();
	
	int ctop = -1;
	char oprator[MAXMUM] = {0};
	
	for((tmp = getchar())!= '\n')
	{
		if(tmp == 'x')
		{
			Push(x(getchar()),ps);
		}
		else
		{
			
		}
	}
	
	return 0;
}
