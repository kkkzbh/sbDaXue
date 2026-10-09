#include<stdio.h>
#include<math.h>

struct x
{
int q;
int p;
double x1;
double x2;	
};

int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	double t[100000][2] = {0};
	int i, j;
	for(i = 0;i<n;i++)
	{
		scanf("%lf %lf",&t[i][0],&t[i][1]);
	}
	//double a[10000][4] = {0};
	struct x a[10000];
	for(j = 0;j<m;j++)
	{
		//scanf("%lf %lf %lf %lf",&a[j][0],&a[j][1],&a[j][2],&a[j][3]);
		scanf("%d %d %lf %lf",&a[j].p,&a[j].q,&a[j].x1,&a[j].x2);
	}
	for(j = 0;j<m;j++)
	{/*
		for(i=a[j][0]-1;i<=a[j][1]-1;i++)
		{
			if(t[i][0] == 1)
			{
				a[j][2] *= t[i][1];
				a[j][3] *= t[i][1];
				
				
			}
			else
			{
				double x = a[j][2];
				double y = a[j][3];
				a[j][2] = x*cos(t[i][1])-y*sin(t[i][1]);
				a[j][3] = x*sin(t[i][1])+ y*cos(t[i][1]);
				
			}
		}
		*/
		for(i = a[j].p-1;i<=a[j].q-1;i++)
		{
			if(t[i][0] == 1)
			{
				a[j].x1 *= t[i][1];
				a[j].x2 *= t[i][1];
			}
			else
			{
				double x = a[j].x1;
				double y = a[j].x2;
				a[j].x1 = x*cos(t[i][1])-y*sin(t[i][1]);
				a[j].x2 = x*sin(t[i][1])+ y*cos(t[i][1]);
			}
		}
	}
	for(j = 0;j<m;j++)
	{
		//printf("%lf %lf\n",a[j][2],a[j][3]);
		printf("%lf %lf\n",a[j].x1,a[j].x2);
	}
	
	
	return 0;
 } 
