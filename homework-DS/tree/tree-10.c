

/***** 算法思路 *****/
#if 0

利用后序序列确定树根 中序序列确定左右子树 递归的解决这个问题
    我将设计一个递归算法 该算法要求传入两个序列 该算法会返回一个树根(指针)
    树采用双链表结构实现
    算法分底层实现和接口函数
#endif
#include<stdio.h>
#include<stdlib.h>
/***** 数据类型定义 *****/

typedef struct node node;
struct node
{
    char val;   // 假定值为char
    node *left,*right;
};

/***** 算法实现  *****/

node* make(char v)
{
    node* it = malloc(sizeof(node)); // C语言不需要强转
    it->val = v;
    it->left = it->right = NULL;
    return it;
}
// l - r是范围 作用于in  root是根结点 作用于 post
node* solve(int l,int r,int root,char in[],char post[])
{
    if(l == r)  return NULL; //判空
    int rt = l;
    while(in[rt] != post[root]) ++rt; // 用 rt 划分 in
    node* it = make(post[root]);
    it->left = solve(l,rt,root - r + rt,in,post);
    it->right = solve(rt + 1,r,root - 1,in,post);
    return it;
}

node* face(char in[],char post[],int n) // 假定数组下标0 - n-1
{
    return solve(0,n,n - 1,in,post); // [l,r) 左开右闭
}