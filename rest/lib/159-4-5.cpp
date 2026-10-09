


#include<iostream>
#include<format>
#include"Tree_158.hpp"
#include<queue>

class SV : public BST<int>
{
private:
    static void for_solve(node* it)
    {
        std::queue<node*> que;
        que.push(it);
        int level = 1;
        node* now;
        node* back = it;
        node* target = it;
        while(!que.empty())
        {
            now = que.front();
            que.pop();
            std::cout << std::format("The level of node which value is {} is {}\n",now->element,level);
            if(now->left) que.push(now->left);
            if(now->right) que.push(now->right);
            back = que.back();
            if(now == target)
            {
                ++level;
                target = back;
            }
        }
    }
public:
    void solve()
    {
        if(empty()) std::cout << std::format("The tree is empty!\n");
        for_solve(tr);
    }
};

int main()
{
    SV a;
    a.ini2();
    a.solve();

    return 0;
}