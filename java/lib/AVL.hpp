#pragma once

#include"BST.hpp"


template<class T>
class AVL : public BST<T>
{
private:
public:
    AVL();
    AVL(const AVL<T>& tr) = delete;
    virtual ~AVL();
    virtual void insert(const T& ele) override;
    virtual void del(const T& ele) override;

public:
    static list::tree<T>* RightRotation(list::tree<T>* root);
    static list::tree<T>* LeftRotation(list::tree<T>* root);
};

template<class T>
AVL<T>::AVL(){}

template<class T>
AVL<T>::~AVL(){}

template<class T>
void AVL<T>::insert(const T& ele)
{
    if(!this->tr)
    {
        this->tr = new list::tree<T>(ele);
        return;
    }
    struct TMP
    {
        list::tree<T>* it;
        list::tree<T>** lastv;

        TMP():it(nullptr),lastv(nullptr){}
        TMP(list::tree<T>* ptr,list::tree<T>** lv): it(ptr),lastv(lv){}
    };
    stack<TMP> stk;
    stk.push(TMP(this->tr,&this->tr));
    list::tree<T>* it = stk.top().it;
    list::tree<T>** lastv = stk.top().lastv;
    int find = 0;
    while(!find)
    {
        if(ele > it->element)
        {
            lastv = &it->right;
            it = it->right;
            stk.push(TMP(it,lastv));
        }
        else if(ele < it->element)
        {
            lastv = &it->left;
            it = it->left;
            stk.push(TMP(it,lastv));
        }
        else return;
        if(!it)
        {
            it = new list::tree<T>(ele);
            *lastv = it;
            find = 1;
        }
    }
    stk.pop();
    it = stk.top().it;
    lastv = stk.top().lastv;
    int bf = 0;
    int L,R;
    while(!stk.empty() && find)
    {
        bf = (it->left ? it->left->_heigh : 0) - (it->right ? it->right->_heigh : 0);
        if(-2 == bf)    //右
        {
            L = it->right->left ? it->right->left->_heigh : 0;
            R = it->right->right ? it->right->right->_heigh : 0;
            if(L <= R)   //右
            {
                *stk.top().lastv = RightRotation(it);
            }
            else    //左
            {
                it = LeftRotation(it->right);
                it->right->_heigh = it->right->heigh();
                *stk.top().lastv = RightRotation(it);
            }
            find = 0;
        }
        else if(2 == bf) //左
        {
            L = it->left->left ? it->left->left->_heigh : 0;
            R = it->left->right ? it->left->right->_heigh : 0;
            if(L < R)   //右
            {
                it = RightRotation(it->left);
                it->left->_heigh = it->left->heigh();
                *stk.top().lastv = LeftRotation(it);
            }
            else    //左
            {
                *stk.top().lastv = LeftRotation(it);
            }
            find = 0;
        }
        it->_heigh = it->heigh();
        stk.pop();
        it = stk.top().it;
        lastv = stk.top().lastv;
    }
}


template<class T>
list::tree<T>* AVL<T>::RightRotation(list::tree<T>* root)
{
    list::tree<T>* rt = root->right;
    root->right = rt->left;
    rt->left = root;
    return rt;
}

template<class T>
list::tree<T>* AVL<T>::LeftRotation(list::tree<T>* root)
{
    list::tree<T>* rt = root->left;
    root->left = rt->right;
    rt->right = root;
    return rt;
}

template<class T>
void AVL<T>::del(const T& ele)
{
    if(!this->tr)
        return;
    struct TMP
    {
        list::tree<T>* it;
        list::tree<T>** lastv;

        TMP():it(nullptr),lastv(nullptr){}
        TMP(list::tree<T>* ptr,list::tree<T>** lv): it(ptr),lastv(lv){}
    };
    stack<TMP> stk;
    stk.push(TMP(this->tr,&this->tr));
    list::tree<T>* it = stk.top().it;
    list::tree<T>** lastv = stk.top().lastv;
    int find = 0;
    while(!find)
    {
        if(ele > it->element)
        {
            lastv = &it->right;
            it = it->right;
            stk.push(TMP(it,lastv));
        }
        else if(ele < it->element)
        {
            lastv = &it->left;
            it = it->left;
            stk.push(TMP(it,lastv));
        }
        else
        {
            find = 1;
        }
        if(!it)
        {
            return;
        }
    }
    if(it->left && it->right)
    {
        list::tree<T>* tmp = it;
        lastv = &it->right;
        it = it->right;
        stk.push(TMP(it,lastv));
        while(it->left)
        {
            lastv = &it->left;
            it = it->left;
            stk.push(TMP(it,lastv));
        }
        tmp->element = it->element;
    }
    if(it->left)
    {
        *lastv = it->left;
        delete it;
        it = *lastv;
    }
    else
    {
        *lastv = it->right;
        delete it;
        it = *lastv;
    }
    int bf = 0;
    int L,R;
    stk.pop();
    it = stk.top().it;
    lastv = stk.top().lastv;
    while(!stk.empty())
    {
        bf = (it->left ? it->left->_heigh : 0) - (it->right ? it->right->_heigh : 0);
        if(-2 == bf)    //右
        {
            L = it->right->left ? it->right->left->_heigh : 0;
            R = it->right->right ? it->right->right->_heigh : 0;
            if(L < R)   //右
            {
                *stk.top().lastv = RightRotation(it);
            }
            else    //左
            {
                it = LeftRotation(it->right);
                it->right->_heigh = it->right->heigh();
                *stk.top().lastv = RightRotation(it);
            }
        }
        else if(2 == bf) //左
        {
            L = it->left->left ? it->left->left->_heigh : 0;
            R = it->left->right ? it->left->right->_heigh : 0;
            if(L < R)   //右
            {
                it = RightRotation(it->left);
                it->left->_heigh = it->left->heigh();
                *stk.top().lastv = LeftRotation(it);
            }
            else    //左
            {
                *stk.top().lastv = LeftRotation(it);
            }
        }
        it->_heigh = it->heigh();
        stk.pop();
        it = stk.top().it;
        lastv = stk.top().lastv;
    }
}
