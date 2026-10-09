#pragma once

#include"basic_binary_tree.h"
#include"compare.h"
#include"algotree.h"
#include<stack>

template<typename T>
struct bsnode : public basic_node<T>
{
    std::size_t sz{ 1 };
    using basic_node<T>::basic_node;
};

template<typename T,typename M_cmp = less<T>>
struct bstree : public basic_binary_tree<T>
{
    using typename basic_binary_tree<T>::node;
    using basic_binary_tree<T>::head;
    using bsnode = bsnode<T>;

#define ct(A) (cast<bsnode>(A))

    bstree() = default;

    virtual void insert(const T& val)
    {
        if(!head)
            head = new bsnode{ val };
        else
            M_insert(head,val);
    }

    node** find(const T& val)   //该函数很危险 必要时考虑private
    {
        node** it{ &head };
        while(*it)
        {
            if(M_cmp{}(val,(*it)->val))
                it = &(*it)->left;
            else if(M_cmp{}((*it)->val,val))
                it = &(*it)->right;
            else
                break;
        }
        return it;
    }

    virtual void erase(const T& val)
    {
        node** it{ &head };
        std::stack<node*> stk;
        while(*it)
        {
            stk.push(*it);
            if(M_cmp{}(val,(*it)->val))
                it = &(*it)->left;
            else if(M_cmp{}((*it)->val,val))
                it = &(*it)->right;
            else
                break;
        }
        if(*it)
        {
            while(!stk.empty())
            {
                --ct(stk.top())->sz;
                stk.pop();
            }
        }
        M_erase(it);
    }

    T find_kth(int k)
    {
        node* it{ head };
        while(it)
        {
            if(!it->left && k == 1 || it->left && ct(it->left)->sz == k - 1)
                return it->val;
            else if(!it->left || ct(it->left)->sz < k - 1)
            {
                if(it->left)
                    k -= ct(it->left)->sz + 1;
                it = it->right;
            }
            else
                it = it->left;
        }
    }

private:

    static void M_erase(node** it)
    {
        if((*it)->left && (*it)->right)
        {
            --ct(*it)->sz;
            node** tmp{ &(*it)->right };
            while((*tmp)->left)
            {
                --ct(*tmp)->sz;
                tmp = &(*tmp)->left;
            }
            swap((*it)->val,(*tmp)->val);
            delete ct(*tmp);
            *tmp = nullptr;
        }
        else if((*it)->left)
        {
            node* tmp{ *it };
            (*it) = (*it)->left;
            delete tmp;
        }
        else
        {
            node* tmp{ *it };
            (*it) = (*it)->right;
            delete tmp;
        }
    }

    static void M_insert(node* it,const T& val)
    {
        std::stack<node*> stk;
        bool def{};
        while(!def)
        {
            stk.push(it);
            if(M_cmp{}(val,it->val))
            {
                if(it->left)
                {
                    it = it->left;
                }
                else
                {
                    it->left = new bsnode{ val };
                    break;
                }
            }
            else if(M_cmp{}(it->val,val))
            {
                if(it->right)
                    it = it->right;
                else
                {
                    it->right = new bsnode{ val };
                    break;
                }
            }
            else
                def = true;
        }
        if(!def)
        {
            while(!stk.empty())
            {
                ++ct(stk.top())->sz;
                stk.pop();
            }
        }
    }

};