

#include<iostream>
#include<format>
#include"Tree_158.hpp"

class SV : public BST<int>
{
private:
    static int max(int a,int b,int c)
    {
        return a > b ? a > c ? a : c : b > c ? b : c;
    }
    static int max(int a,int b)
    {
        return a > b ? a : b;
    }
    int for_fmax_recursion(node* it)
    {
        int a = it->element;
        int b = a,c = a;
        if(it->left) b = for_fmax_recursion(it->left);
        if(it->right) c = for_fmax_recursion(it->right);
        return max(a,b,c);
    }
    int for_fmax_no_recursion(node* it)
    {
        auto stack = new node*[sz + 10];
        auto top = 0;
        int m = it->element;
        while(top  || it)
        {
            if(it)
            {
                stack[top++] = it;
                it = it->left;
            }
            else
            {
                it = stack[--top];
                m = max(m,it->element);
                it = it->right;         //没必要在非递归这里优化 最多优化一个赋值 但代价不小
            }                           //对于递归的 则是能不去探空 就不去探空
        }
        delete[] stack;
        return m;
    }
public:
    void fmax()
    {
        if(empty())
        {
            std::cout << "空的怎么找最大值！\n";
            return;
        }
        std::cout << std::format("recursion version find the max-value is {}\n", for_fmax_recursion(tr));
        std::cout << std::format("non-recursion version find the max-value is {}\n", for_fmax_no_recursion(tr));
    }
};

int main()
{
    SV a;
    a.ini2();
    a.fmax();

    return 0;
}