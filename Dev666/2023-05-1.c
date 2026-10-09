

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int isEqa(char x[8][10],char y[8][10])
{
	int find = 1;
	int i = 0, j = 0;
	for(i=0;i<8 && find;i++)
	{
		for(j=0;j<8 && find;j++)
		{
			if(x[i][j] != y[i][j])
			find = 0;
		}
	}
	return find;
}

int main()
{
	char board[8][10] = {0};
	int n = 0;
	scanf("%d",&n);
	getchar();
	char (*p)[8][10] =(char (*)[8][10])malloc(n*sizeof(char [8][10]));
	int i,j;
	for(j=0;j<n;j++)
	{
		for(i=0;i<8;i++)
		{
			fgets(board[i],sizeof(board[i]),stdin);
			strcpy(p[j][i],board[i]);
		}
	}
	for(i=0;i<n;i++)
	{
		int sum = 0;
		for(j=0;j<=i;j++)
		{
			if(isEqa(p[i],p[j]))
			sum++;
		}
		printf("%d\n",sum);
	}
	free(p);
	p = NULL;

	return 0;
}
