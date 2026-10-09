#pragma once

namespace BS
{

template<class T>
inline bool less(const T& a,const T& b)
{
    return a < b;
}

template<class T>
inline bool greater(const T& a,const T& b)
{
    return a > b;
}

template<class it,class T>
it BinarySearch(it first,it end,const T& value,bool cmp(const T&,const T&) = less<T>)
{
    if(first == end)
    {
        if(*first == value)
            return first;
        else
            return nullptr;
    }
    it mid = nullptr;
    while(first <= end)
    {
        mid = first + ((end-first)/2);
        if(*mid == value)
            return mid;
        else if(cmp(*mid,value))
        {
            first = ++mid;
        }
        else
        {
            end = --mid;
        }
    }
    return nullptr;
}

}

