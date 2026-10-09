


#include "stack.h"


cstack* CreatStack_char()
{
	cstack* p = (cstack*)calloc(1,sizeof(cstack));
	if (NULL == p)
	{
		printf("内存不足，无法开辟栈\n");
		return NULL;
	}
	p->late = -1;
	return p;
}

stack* CreatStack()
{
	stack* p = (stack*)malloc(sizeof(stack));
	if (NULL == p)
	{
		printf("内存不足，无法开辟栈\n");
		return NULL;
	}
	p->late = -1;
	return p;
}

dstack* CreatStack_double()
{
	dstack* p = (dstack*)malloc(sizeof(dstack));
	if (NULL == p)
	{
		printf("内存不足，无法开辟栈\n");
		return NULL;
	}
	p->late = -1;
	return p;
}

void Push_char(char x,cstack* stack)
{
	if (stack->late == MAXMUM - 1)
	{
		printf("栈满\n");
		return;
	}
	stack->data[++stack->late] = x;
}

void Push(int x, stack* stack)
{
	if (stack->late == MAXMUM - 1)
	{
		printf("栈满\n");
		return;
	}
	stack->data[++stack->late] = x;
}

void Push_double(double x, dstack* stack)
{
	if (stack->late == MAXMUM - 1)
	{
		printf("栈满\n");
		return;
	}
	stack->data[++stack->late] = x;
}

int IsPush(int x,stack* stack)
{
	if (-1 == stack->late || x > stack->data[stack->late])
		return 1;
	else return 0;
}

int Modify(char x)
{
	if ('+' == x || '-' == x)
		return 1;
	if ('*' == x || '/' == x)
		return 2;
	if ('^' == x)
		return 3;
}

int POP(stack* stack)
{
	if (-1 == stack->late)
	{
		printf("栈空 操作不合法！\n");
		return -111;
	}
	return stack->data[stack->late--];
}

char POP_char(cstack* stack)
{
	if (-1 == stack->late)
	{
		printf("栈空 操作不合法！\n");
		return '\0';
	}
	return stack->data[stack->late--];
}

double POP_double(dstack* stack)
{
	if (-1 == stack->late)
	{
		printf("栈空 操作不合法！\n");
		return -111;
	}
	return stack->data[stack->late--];
}

void Caculate(char op, stack* stack)
{
	int x1 = POP(stack);
	int x2 = POP(stack);
	int ret = 0;
	switch (op)
	{
	case '+':

		ret = x2 + x1;
		Push(ret, stack);
		break;
	case '-':
		ret = x1 - x1;
		Push(ret, stack);
		break;
	case '*':
		ret = x2 * x1;
		Push(ret, stack);
		break;
	case '/':
		ret = x2 / x1;
		Push(ret, stack);
		break;
	case '^':
		ret = Pow(x2, x1);
		Push(ret, stack);
		break;
	}
}

void Caculate_double(char op, dstack* stack)
{
	double x1 = POP_double(stack);
	double x2 = POP_double(stack);
	double ret = 0;
	switch (op)
	{
	case '+':

		ret = x2 + x1;
		Push_double(ret, stack);
		break;
	case '-':
		ret = x2 - x1;
		Push_double(ret, stack);
		break;
	case '*':
		ret = x2 * x1;
		Push_double(ret, stack);
		break;
	case '/':
		ret = x2 / x1;
		Push_double(ret, stack);
		break;
	case '^':
		ret = pow(x2, x1);
		Push_double(ret, stack);
		break;
	}
}

double Pow(double x, int y)
{
	double tmp = x;
	if (0 == y)
		return 1.0;
	else if (y > 0)
	{
		for (int i = 1;i < y;i++)
		{
			x *= tmp;
		}
		return x;
	}
	else
	{
		for (int i = 0; i >= y; i--)
		{
			x /= tmp;
		}
		return x;
	}
}