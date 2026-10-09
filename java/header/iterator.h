#pragma once

using size_t = unsigned long long;

template<class T,size_t N>
inline const T* begin(const T (&arr)[N])
{
    return arr;
}

template<class T,size_t N>
inline const T* end(const T (&arr)[N])
{
    return arr+N;
}

template<class T,size_t N>
inline T* begin(T (&arr)[N])
{
    return const_cast<T*>(begin(const_cast<const T(&)[N]>(arr)));
}

template<class T,size_t N>
inline T* end(T (&arr)[N])
{
    return const_cast<T*>(end(const_cast<const T(&)[N]>(arr)));
}