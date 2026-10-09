#pragma once

#include"tree.hpp"

template<class T>
class BST
{
protected:
    list::tree<T>* tr;
public:
    BST();
    BST(const BST<T>& tr) = delete;
    virtual ~BST();
    list::tree<T>* find(const T& ele) const;
    list::tree<T>* max() const;
    list::tree<T>* min() const;
    const list::tree<T>* get() const;
    virtual void insert(const T& ele);
    void preorder();
    void inorder();
    void postorder();
    void queorder();
    virtual void del(const T& ele);
};


template<class T>
BST<T>::BST(): tr(nullptr) {}

template<class T>
BST<T>::~BST()
{
    delete tr;
}

template<class T>
inline void BST<T>::preorder()
{
    tr->preorder();
}
template<class T>
inline void BST<T>::inorder()
{
    tr->inorder();
}
template<class T>
inline void BST<T>::postorder()
{
    tr->postorder();
}
template<class T>
inline void BST<T>::queorder()
{
    tr->queorder();
}

template<class T>
inline const list::tree<T>* BST<T>::get() const
{
    return tr;
}



template<class T>
list::tree<T>* BST<T>::find(const T& ele) const
{
    list::tree<T>* it = tr;
    while(it)
    {
        if(ele > it->element)
            it = it->right;
        else if(ele < it->element)
            it = it->left;
        else
            break;
    }
    return it;
}

template<class T>
list::tree<T>* BST<T>::max() const
{
    list::tree<T>* it = this;
    while(it->right)
        it = it->right;
    return it;
}

template<class T>
list::tree<T>* BST<T>::min() const
{
    list::tree<T>* it = this;
    while(it->left)
        it = it->left;
    return it;
}

template<class T>
void BST<T>::insert(const T& ele)
{
    if(!tr)
    {
        tr = new list::tree<T>(ele);
        return;
    }
    list::tree<T>** lastv = &tr;
    list::tree<T>* it = tr;
    int find = 0;
    while(!find)
    {
        if(ele > it->element)
        {
            lastv = &it->right;
            it = it->right;
        }
        else if(ele < it->element)
        {
            lastv = &it->left;
            it = it->left;
        }
        else
        {
            find = 1;
        }
        if(!it)
        {
            *lastv = new list::tree<T>(ele);
            find = 1;
        }
    }
}

template<class T>
void BST<T>::del(const T& ele)
{
    list::tree<T>* it = tr;
    list::tree<T>** lastv = nullptr;
    while(it)
    {
        if(ele > it->element)
        {
            lastv = &it->right;
            it = it->right;
        }
        else if(ele < it->element)
        {
            lastv = &it->left;
            it = it->left;
        }
        else
            break;
    }
    if(!it)
        return;
    if(it->left && it->right)
    {
        list::tree<T>* tmp = it->right;
        lastv = &it->right;
        while(tmp->left)
        {
            lastv = &tmp->left;
            tmp = tmp->left;
        }
        it->element = tmp->element;
        *lastv = tmp->right;
        delete tmp;
    }
    else if(it->left)
    {
        list::tree<T>* tmp = it;
        *lastv = it->left;
        delete tmp;
    }
    else
    {
        list::tree<T>*tmp = it;
        *lastv = it->right;
        delete tmp;
    }
}








