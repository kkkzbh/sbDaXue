#pragma once

#include<iostream>

template<typename T>
struct node
{
    T element;
    node* left = nullptr;
    node* right = nullptr;
    node() = default;
    explicit node(const T& ele) : element(ele){}
    explicit node(T &&ele) : element(ele){}
};

template<typename T>
class tree
{
private:
    using size_type = std::size_t;
    void for_inorder(node<T>* it)
    {
        if(!it) return;
        for_inorder(it->left);
        std::cout << it->element << ' ';
        for_inorder(it->right);
    }
protected:
    node<T>* tr = nullptr;
    size_type sz = 0;
public:
    tree() = default;
    tree(tree&& t) noexcept : tr(t){t = nullptr;}
    virtual ~tree()
    {
        if(tr)
        {
            if(tr->left) delete tr->left;
            if(tr->right) delete tr->right;
            delete tr;
        }
    }
    virtual void insert(const T& ele) = 0;
    void inorder()
    {
        for_inorder(tr);
        std::cout << '\n';
    }
    size_type size(){ return sz;}
    bool empty(){ return sz == 0;}
};

template<typename T>
class BST : public tree<T>       //BST. using for Book homework
{
public:
    using node = node<T>;
    using tree<T>::tr;
    using tree<T>::sz;
    void insert(const T& ele) override
    {
        if(!tr) tr = new node(ele);
        else
        {
            node *it = tr;
            while(true)
            {
                if (it->element < ele)
                {
                    if (it->right) it = it->right;
                    else
                    {
                        it->right = new node(ele);
                        ++sz;
                        break;
                    }
                }
                else if (ele < it->element)
                {
                    if (it->left) it = it->left;
                    else
                    {
                        it->left = new node(ele);
                        ++sz;
                        break;
                    }
                }
            }
        }
    }
    void ini()
    {
        insert(5);
        insert(7);
        insert(9);
        insert(2);
        insert(1);
        insert(0);
        insert(-2);
        insert(-7);
        insert(99);
        insert(321);
    }
    void ini2()
    {
        insert(7);
        insert(9);
        insert(6);
        insert(2);
        insert(3);
        insert(10);
        insert(11);
        insert(14);
        insert(13);
    }
};