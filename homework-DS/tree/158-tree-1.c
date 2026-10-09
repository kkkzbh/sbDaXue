

#if 0

算法思路
采用递归算法实现
定义谓词 n(x) 表示x的结点个数
left(x) 表示x的左子树
right(x) x的右子树
则该题可以抽象为 n(x) = n(left(x)) + n(right(x)) + 1;
当x为空的时候 定义n(x) = 0;
那么根据这个公式 就可以递归算出答案

#endif

#include<stdio.h>
#include<stdlib.h>

/***** 数据类型定义 *****/

struct node typedef node;   //typedef 可以写中间 相比传统类比定义变量 左 typedef 右 更直观
struct node
{
    int val;    //结点的值 不一定是int 这里写为int
    node* left,*right;
};

/***** 算法实现 *****/

int size(node* root)
{
    if(!root)   //如果是 空
    {
        return 0;
    }
    return size(root->left) + size(root->right) + 1;    // 否则 左 + 右 + 1
}

int main()
{

    return 0;
}