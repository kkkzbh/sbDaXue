#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#if 0
算法思路
假定编号1-n, 从1-n作为开头dfs遍历图
如果两次经过相同结点 就是回路
#endif

/***** 数据类型 *****/
typedef int T;
#define SIZE 100000  // 足够大
T a[SIZE];  /* 结点值 */ int n;  /* 结点个数 */ int m[SIZE][SIZE];  // 领接矩阵
int vis[SIZE],path[SIZE];  // 是否遍历 和 路径数组
int p,find;  // 当前深度 和 是否找到回路

/***** 算法 *****/

void print()
{   //for(int i = 0; i < p; ++i) printf("%d ",path[i]); return;

}

void dfs(int i)
{   if(find == 1) return;
    path[p++] = i;
    if(vis[i] == 1){ find = 1; print(); return; }
    else
    {   vis[i] = 1; int j = 1;
        for(; j <= n; ++j)
            if(m[i][j] != 0) dfs(j);
        vis[j] = 0;
        --p;
    }
}

void solve()
{ memset(vis,0,sizeof(vis)); memset(path,0,sizeof(path)); p = 0;
    for(int i = 1; i <= n; ++i) dfs(i);
}