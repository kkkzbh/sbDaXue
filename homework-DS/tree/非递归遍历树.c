

#include"全局栈.h"

/***** 算法思路 *****/
#if 0

    如果栈不空或者指针不空则重复下面操作
    1)若指针不空 指针入栈 指针往左走
    2)指针回到栈顶 弹出栈顶元素 指针往右走

    先序在1)插入操作 中序在2)插入操作

#endif

void temp(node* root)
{
    node* it = root;
    while(!empty() || it)
    {
        if(it)
        {
            push(it);
            it = it->left;
        }
        else
        {
            it = top();
            pop();
            it = it->right;
        }
    }
}