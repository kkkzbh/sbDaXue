#pragma once


#include"bstree.h"

template<typename T>
struct avlnode : public bsnode<T>
{
    std::size_t hei{ 1 };
    using bsnode<T>::bsnode;
};


template<typename T,typename M_cmp = less<T>>
struct avltree : public bstree<T,M_cmp>
{
    using bstree<T>::head;
    using typename bstree<T>::node;
    using avlnode = avlnode<T>;
#define act(A) (cast<avlnode>(A))

    avltree() = default;

    void insert(const T& val) override
    {

    }

    void erase(const T& val) override
    {

    }

    void sinistrogyration(node* it)
    {

    }

    void dextrorotation(node* it)
    {

    }

};

