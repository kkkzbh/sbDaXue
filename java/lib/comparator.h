#pragma once

template<class T>
class less
{
public:
    inline bool operator()(const T& a,const T& b) const
    {
        return a < b;
    }
    inline bool operator()(const T* a,const  T* b) const
    {
        return *a < *b;
    }
};

template<class T>
class greater
{
public:
    inline bool operator()(const T& a,const T& b) const
    {
        return a > b;
    }
    inline bool operator()(const T* a,const T* b) const
    {
        return *a > *b;
    }
};




