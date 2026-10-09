

#include<iostream>
#include<format>
#include<stdexcept>
#include"Tree_158.hpp"

class SV : public BST<int>
{
private:
    template<typename T>
    static void swap(T* &a,T* &b)
    {
        T* tmp = a;
        a = b;
        b = tmp;
    }
    static void for_solve(node* it)
    {
        if(it->left) for_solve(it->left);
        if(it->right) for_solve(it->right);
        swap(it->left,it->right);
    }
public:
    void solve()
    {
        if(empty()) throw std::out_of_range("Tree is empty!");
        for_solve(tr);
    }
};

int main()
{
    SV a;
    a.ini2();
    a.inorder();
    a.solve();
    a.inorder();

    return 0;
}