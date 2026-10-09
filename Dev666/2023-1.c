#include<stdio.h>
#define MAX 100

int main()
{
	int m,n;
	scanf("%d %d",&n,&m);
	int i;
	int a[MAX][2] = {0};
	for(i = 0;i<n;i++)
	{
		scanf("%d %d",&a[i][0],&a[i][1]);
	}
	int j;
	int b[MAX][2] = {0};
	for(j = 0;j<m;j++)
	{
		scanf("%d %d",&b[j][0],&b[j][1]);
	}
	for(j = 0;j<m;j++)
	{
		for(i = 0; i<n; i++)
		{
			b[j][0] += a[i][0];
			b[j][1] += a[i][1];
		}
	}
	for(j = 0;j<m;j++)
	printf("%d %d\n",b[j][0],b[j][1]);
	
	return 0;
}
