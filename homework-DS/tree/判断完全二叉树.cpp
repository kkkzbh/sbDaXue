

#if 0

开一个队列 层序遍历
一直遍历 直到遇到左儿子为空的结点 对剩余所有结点执行
1) 若不是叶子 则返回false
若能到这里 返回true

#endif

/***** 数据类型定义 *****/

#include"全局队列.cpp"  // 开个队列

typedef struct node node;
struct node
{
    int val; //假定值为val
    node *left,*right;
};

/***** 算法实现 *****/

int is_ctree(node* tree)
{
    if(!tree)
    {
        return 0;
    }
    int tag = 1;
}