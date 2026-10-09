#pragma once

#include"comparator.h"
#include"vector.hpp"
using size_t = unsigned long long;
#define _UP(A) (((A)-1)/2)
#define _LEFT(A) (2*(A)+1)
#define _RIGHT(A) (2*(A)+2)

template<class T,class V = vector<T>,class U = less<T>>
class heap
{
private:
    V tr;
    U cmp;
    void adjust_up(const T& ele,size_t top);
    void adjust_down(const T& ele,size_t top);
public:
    heap();
    ~heap();
    void push(const T& ele);
    T& top();
    void pop();
    bool empty();
    size_t size();
    void create(int x);
};


template<class T,class V,class U>
heap<T,V,U>::heap() : tr(),cmp(){}

template<class T,class V,class U>
heap<T,V,U>::~heap(){}

template<class T,class V,class U>
inline void heap<T,V,U>::push(const T& ele)
{
    tr.push_back(ele);
    size_t top = tr.size() - 1;
    adjust_up(ele,top);
}

template<class T,class V,class U>
void heap<T,V,U>::adjust_up(const T& ele,size_t top)
{
    while(top && cmp(tr[_UP(top)],ele))
    {
        tr[top] = tr[_UP(top)];
        top = _UP(top);
    }
    tr[top] = ele;
}

template<class T,class V,class U>
inline T& heap<T,V,U>::top()
{
    return tr[0];
}

template<class T,class V,class U>
void heap<T,V,U>::pop()
{
    if(tr.empty())
        return;
    T tmp = tr[tr.size()-1];
    tr.pop_back();
    adjust_down(tmp,0);
}

template<class T,class V,class U>
void heap<T,V,U>::adjust_down(const T& ele,size_t top)
{
    size_t it = _LEFT(top);
    while(it <= tr.size()-1)
    {
        if(it != tr.size()-1 && cmp(tr[it],tr[it+1]))
            it++;
        if(cmp(tr[it],ele)) break;
        else
        {
            tr[top] = tr[it];
            top = it;
            it = _LEFT(top);
        }
    }
    tr[top] = ele;
}

template<class T,class V,class U>
inline bool heap<T,V,U>::empty()
{
    return tr.empty();
}

template<class T,class V,class U>
inline size_t heap<T,V,U>::size()
{
    return tr.size();
}


template<class T,class V,class U>
void heap<T,V,U>::create(int x)
{
    T value;
    for(int i = 0;i<x;++i)
    {
        std::cin >> value;
        tr.push_back(value);
    }
    for(int top = _UP((tr.size()-1));top != -1;--top)
    {
        value = tr[top];
        adjust_down(value,top);
    }
}