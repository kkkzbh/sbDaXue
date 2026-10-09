#pragma once

template<class T>
inline void swap(T& a,T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template<class T>
inline void swap(T* a,T* b)
{
    T tmp = *a;
    *a = *b;
    *b = tmp;
}