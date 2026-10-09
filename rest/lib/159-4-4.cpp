

#include<iostream>
#include<format>
#include"Tree_158.hpp"

class SV : public BST<int>
{
private:
    int for_depth(node* it)
    {
        if(!it) return 0;
        return max(for_depth(it->left) , for_depth(it->right)) + 1;
    }
    int max(int a,int b)
    {
        return a > b ? a : b;
    }
public:
    int depth()
    {
        return for_depth(tr);
    }
};

int main()
{
    SV a;
    a.ini2();
    std::cout << std::format("The depth of tree is {}\n",a.depth());


    return 0;
}