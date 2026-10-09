

#if 0

算法思路
答案的全局变量有点low,一般肯定能不用全局就不用全局 这里使用二级指针表示前驱
二级指针为空 表示无前驱
先序遍历二叉树 遍历到叶子 执行链接算法

最终为了考试方便 打算能开全局就开全局

#endif

#include<stdio.h>   // 用宏NULL
#include<stdbool.h>  // !!! 引入bool !!!

/***** 数据类型定义 *****/

#define and &&  // 定义 and

struct node typedef node;
struct node
{
    int val;
    node* left,*right;
};

node* head;  // 链表头指针

/***** 算法实现 *****/

// 判断是否是叶子
bool is_leaf(node* it)
{
    return !it->left and !it->right;
}

// 底层实现
void M_make_list(node* it,node** pre)
{
    if(!it) // 空
    {
        return;
    }
    if(is_leaf(it)) // 是叶子
    {
        if(pre)    //有前驱
        {
            (*pre)->right = it;
            pre = &it;
        }
        else
        {
            pre = &it;
            head = it;  // 修改 head
        }
    }
    M_make_list(it->left,pre);
    M_make_list(it->right,pre);
}

// 接口 不增加调用者负担
node* make_list(node* root)
{
    node** ptr = NULL;
    M_make_list(root,ptr);
    return head;
}