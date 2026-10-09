

#include<stdio.h>
#include<math.h>
#include<stdlib.h>


typedef struct s
{
	int op;
	double x;
}s;

typedef struct
{
	int i;
	int j;
	double x;
	double y;
}opa;

void oprator(double* x,double* y,double oprator,double top)
{
	if(top == 1)
	{
		*x *= oprator;
		*y *= oprator; 
	}
	else
	{
		double xx = *x;
		double yy = *y;
		*x = xx*cos(oprator) - yy*sin(oprator);
		*y = xx*sin(oprator) + yy*cos(oprator);
	}
}


int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	s* ps = (s*)malloc(n*sizeof(s));
	for(int i = 0;i<n;i++)
	{
		scanf("%d %lf",&ps[i].op,&ps[i].x);
	}
	
	opa* popa = (opa*)malloc(m*sizeof(opa));
	
	for(int i = 0;i<m;i++)
	{
		scanf("%d %d %lf %lf",&popa[i].i,&popa[i].j,&popa[i].x,&popa[i].y);
	}
	
	for(int i = 0;i < m;i++)
	{
		double x = popa[i].x;
		double y = popa[i].y;
		for(int j = popa[i].i;j<=popa[i].j;j++)
		{
			oprator(&x,&y,ps[j-1].x,ps[j-1].op);
		}
		printf("%lf %lf\n",x,y);
	}
	
	
	return 0;
}
