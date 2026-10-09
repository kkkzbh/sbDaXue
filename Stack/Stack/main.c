

#include "stack.h"


int main()
{
	stack* pint = CreatStack();





	cstack* coprator = CreatStack_char();
	stack* oprator = CreatStack();
	dstack* pdouble = CreatStack_double();






	double tmparr[MAXMUM] = { 0 };
	int count = -1;
	int decp = 0;
	int isdec = 0;






	printf("请输入表达式:>\n");



	char tmp = 0;
	while (tmp = getchar())
	{
		if (tmp >= '0' && tmp <= '9')
		{
			tmparr[++count] = tmp - '0';
			if (isdec)
				decp++;
		}
		else if ('.' == tmp)
		{
			isdec = 1;
		}
		else
		{
			double tmpsum = 0;
			double x = -1;

			for (int i = 0; i <= count-decp ;i++)
			{
				tmpsum += tmparr[i] * pow(10, count - decp - i);
			}
			for (int i = count - decp + 1;i <= count;i++)
			{
				tmpsum += tmparr[i] * pow(10, x--);
			}
			if (-1 != count)
			{
				Push(tmpsum, pint);
				Push_double(tmpsum, pdouble);
			}

			count = -1;
			decp = 0;
			isdec = 0;
			if ('(' == tmp)
			{
				Push_char('(', coprator);
				Push(-1, oprator);
			}
			else if ('\n' == tmp)
			{
				while (-1 != coprator->late)
				{
					char op = POP_char(coprator);
					POP(oprator);
					Caculate(op, pint);
					Caculate_double(op, pdouble);
				}
				break;
			}

			else
			{
				int find = 0;
				while (!find)
				{
					int n = Modify(tmp);
					if (')' != tmp && IsPush(n, oprator))
					{
						Push(n, oprator);
						Push_char(tmp, coprator);
						find = 1;
					}
					else if (')' != tmp)
					{
						char op = POP_char(coprator);
						POP(oprator);
						Caculate(op, pint);
						Caculate_double(op, pdouble);
					}
					else
					{
						char op = 0;
						while ((op = POP_char(coprator)) != '(')
						{
							POP(oprator);
							Caculate(op, pint);
							Caculate_double(op, pdouble);
						}
						POP(oprator);
						find = 1;
					}
				}
			}
		}
	}
	printf("计算结果 : %.4lf\n", POP_double(pdouble));

	system("pause");

	return 0;
}