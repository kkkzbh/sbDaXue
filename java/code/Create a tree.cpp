


//这个只是我闲来无事 做测试
//就是给定一个先序 中序 后序 层序后的遍历序列 生成一棵树
//OK了也是OK了啊  此问题无解  因为解不唯一




#ifdef ABANDON
//*****************************text     one *****************************//
//没有思路

#include<iostream>
#include<stdio.h>

#define MAX


class tree
{
private:
    int x;
    tree* left;
    tree* right;
    int preorder[MAX];
    int top;
    int t;
public:
    tree(int n = 0) : x(n),left(nullptr),right(nullptr),top(-1),t(-1){}
    void c()
    {
        while(std::cin >> preorder[++top]);
    }
    void preod(tree* it)
    {
        if(!it)
            return;
        std::cout << x << ' ';
        it->left->preod(it->left);
        it->right->preod(it->right);
    }
    auto create(tree* it) -> tree*
    {
        if(t-1 != top)
            it = new tree(preorder[++t]);
        it->left = create(it->left);
        it->right = create(it->right);
        return it;
    }
};

class Tree      //其实有时候没有必要开一个tree去管理了 直接主函数拿个指针操作即可
{
private:
    tree* root;

public:
    Tree() : root(nullptr){}
    inline void pr()
    {
        root = root->preod(root);
    }
};

auto main() -> int
{
    freopen("data.dat","r",stdin);


    return 0;
}

#endif























