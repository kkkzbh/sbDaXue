#pragma once


template<typename T>
struct less
{
    bool operator()(const T& l,const T& r)
    {
        return l < r;
    }
};

template<typename T>
struct greater
{
    bool operator()(const T& l,const T& r)
    {
        return l > r;
    }
};