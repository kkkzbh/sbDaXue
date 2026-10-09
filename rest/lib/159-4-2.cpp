


#include<iostream>
#include"Tree_158.hpp"

class SV : public BST<int>
{
private:
    static void for_solve(node* it,node** last)
    {
        if(it->left)
            for_solve(it->left,last);
        if(!it->left && !it->right)
        {
            if(*last) (*last)->right = it;
            *last = it;
            std::cout << "发现一个叶节点 : " << it->element << '\n';
        }
        if(it->right)
            for_solve(it->right,last);
    }
public:
    void solve()
    {
        if(!tr) return;
        node* l = nullptr;
        for_solve(tr,&l);
    }
    void check_print()
    {
        node* it = tr;
        while(it->left) it = it->left;
        while(it)
        {
            std::cout << it->element << ' ';
            it = it->right;
        }
        std::cout << "\n";
    }
};

int main()
{
    SV a;
    a.ini();
    a.solve();
    a.check_print();

    return 0;
}