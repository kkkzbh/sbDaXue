


#include<iostream>
#include"Tree_158.hpp"

class SV : public BST<int>
{
private:
    int for_count(node* it)
    {
        if(!it) return 0;
        return 1 + for_count(it->left) + for_count(it->right);
    }
public:
    int count()
    {
        return for_count(tr);
    }
};

int main()
{
    SV a;
    a.insert(5);
    a.insert(7);
    a.insert(3);
    a.insert(9);
    a.insert(2);
    a.insert(1);
    a.insert(10);
    a.inorder();
    //插入了7个元素 理论值 n = 7;
    std::cout << a.count();

    return 0;
}
