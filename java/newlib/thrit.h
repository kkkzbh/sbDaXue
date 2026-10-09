#pragma once

#include"thr_binary_tree.h"

template<typename T>
struct Thr_basic_It
{
    friend bool operator==(const Thr_basic_It& It1,const Thr_basic_It& It2) noexcept
    {
        return It1.it == It2.it;
    }

    using thrnode = thrnode<T>;
    using node = basic_node<T>;

    node* it{ nullptr };

    Thr_basic_It() = default;
    explicit Thr_basic_It(node* ptr) : it(ptr){}

    T& operator*() const noexcept
    {
        return it->val;
    }

    operator node*() const noexcept
    {
        return it;
    }

    operator thrnode*() const noexcept
    {
        return reinterpret_cast<thrnode*>(it);
    }

    node* point() const noexcept
    {
        return it;
    }
};

template<typename T>
struct Thr_pre_It : public Thr_basic_It<T>
{
    using typename Thr_basic_It<T>::node;
    using typename Thr_basic_It<T>::thrnode;
    using Thr_basic_It<T>::Thr_basic_It;
    using Thr_basic_It<T>::it;

    Thr_pre_It& operator++() noexcept
    {
        if(cast<thrnode>(it)->ltag || !it->left)
            it = it->right;
        else
            it = it->left;
        return *this;
    }

    Thr_pre_It operator++(int) noexcept
    {
        Thr_pre_It tmp = *this;
        ++*this;
        return tmp;
    }

};

template<typename T>
struct Thr_in_It : public Thr_basic_It<T>
{
    using typename Thr_basic_It<T>::node;
    using typename Thr_basic_It<T>::thrnode;
    using Thr_basic_It<T>::Thr_basic_It;
    using Thr_basic_It<T>::it;

    Thr_in_It& operator++()
    {
        if(cast<thrnode>(it)->rtag || !it->right)
            it = it->right;
        else
        {
            it = it->right;
            while(!cast<thrnode>(it)->ltag)
                it = it->left;
        }
        return *this;
    }

    Thr_in_It operator++(int)
    {
        Thr_in_It tmp = *this;
        ++*this;
        return tmp;
    }
};

template<typename T>
struct Thr_post_It : public Thr_basic_It<T>
{
    using typename Thr_basic_It<T>::node;
    using typename Thr_basic_It<T>::thrnode;
    using Thr_basic_It<T>::Thr_basic_It;
    using Thr_basic_It<T>::it;

};

template<typename T>
struct Thr_post_rIt : public Thr_basic_It<T>
{
    using typename Thr_basic_It<T>::node;
    using typename Thr_basic_It<T>::thrnode;
    using Thr_basic_It<T>::Thr_basic_It;
    using Thr_basic_It<T>::it;

    Thr_post_rIt& operator++()
    {
        if(!cast<thrnode>(it)->rtag && it->right)
            it = it->right;
        else
            it = it->left;
        return *this;
    }

    Thr_post_rIt operator++(int)
    {
        Thr_post_rIt tmp = *this;
        ++*this;
        return tmp;
    }
};