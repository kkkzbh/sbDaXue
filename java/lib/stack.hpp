#pragma once

#define SIZE 15
#define __size__ _top+1
using size_t = unsigned long long;

template<class T>
class stack
{
private:
    T* element;
    int _top;
    size_t multiple;
    void realloc();
    void realloc(int);
public:
    stack();
    ~stack();
    void push(const T& ele);
    void pop();
    T& top();
    bool empty();
};


template<class T>
stack<T>::stack() :multiple(1),element(new T[SIZE]()),_top(-1){}



template<class T>
stack<T>::~stack()
{
    delete[] element;
}

template<class T>
void stack<T>::realloc()
{
    T* tmp = element;
    element = new T[++multiple * SIZE]();
    for(int i = 0;i<=_top;++i)
    {
        element[i] = tmp[i];
    }
    delete[] tmp;
}

template<class T>
void stack<T>::realloc(int)
{
    T* tmp = element;
    element = new T[--multiple * SIZE]();
    for(int i = 0;i<=_top;++i)
    {
        element[i] = tmp[i];
    }
    delete[] tmp;
}

template<class T>
void stack<T>::push(const T& ele)
{
    if(__size__ == multiple*SIZE)
        realloc();
    element[++_top] = ele;
}

template<class T>
void stack<T>::pop()
{
    if(-1 != _top)
        --_top;
    if(__size__ == (multiple-2)*SIZE)
        realloc(0);
}

template<class T>
inline T& stack<T>::top()
{ 
    return element[_top];
}

template<class T>
inline bool stack<T>::empty()
{
    return _top == -1;
}

