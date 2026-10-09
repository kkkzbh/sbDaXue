#pragma once

#include<initializer_list>
using size_t = unsigned long long;
#define __SIZE__ 20

template<class T>
class vector
{
private:
    T* element;
    size_t _size;
    size_t _capcity;
    void realloc();
    void realloc(int);
public:
    vector();
    vector(size_t n);
    vector(size_t n,const T& ele);
    vector(std::initializer_list<T>);
    ~vector();
    void push_back(const T& ele);
    void pop_back();
    size_t size() const;
    size_t capcity() const;
    bool empty() const;
    void clear();
    void resize(size_t n,const T& ele = T());
    T& operator[](const size_t top);
    const T& operator[](const size_t top) const;
    vector<T>& operator=(const vector<T>& vec);
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
};

template<class T>
inline vector<T>::vector() : element(new T[__SIZE__]),_size(0),_capcity(__SIZE__){}

template<class T>
inline vector<T>::vector(size_t n) : element(new T[n+__SIZE__]),_size(n),_capcity(n+__SIZE__){}

template<class T>
inline vector<T>::vector(size_t n,const T& ele) : element(new T[n+__SIZE__]),_size(n),_capcity(n+__SIZE__)
{
    for(int i = 0;i<n;++i)
    {
        element[i] = ele;
    }
}

template<class T>
inline vector<T>::vector(std::initializer_list<T> list) : element(new T[__SIZE__ + list.size()]),_size(list.size()),_capcity(__SIZE__ + list.size())
{
    int top = -1;
    for(auto &it : list)
    {
        element[++top] = it;
    }
}

template<class T>
inline vector<T>::~vector()
{
    delete[] element;
}

template<class T>
void vector<T>::realloc()
{
    T* tmp = element;
    element = new T[(_capcity += __SIZE__)];
    for(int i = 0;i<_size;++i)
    {
        element[i] = tmp[i];
    }
    delete[] tmp;
}

template<class T>
void vector<T>::realloc(int)
{
    T* tmp = element;
    element = new T[(_capcity -= __SIZE__)];
    for(int i = 0;i<_size;++i)
    {
        element[i] = tmp[i];
    }
    delete[] tmp;
}

template<class T>
inline void vector<T>::push_back(const T& ele)
{
    if(_size == _capcity)
        realloc();
    element[_size++] = ele;
}

template<class T>
inline void vector<T>::pop_back()
{
    if(!_size)
        return;
    if(_size == _capcity - 2*__SIZE__)
        realloc(0);
    --_size;
}

template<class T>
inline size_t vector<T>::size() const
{
    return _size;
}

template<class T>
inline size_t vector<T>::capcity() const
{
    return _capcity;
}

template<class T>
inline bool vector<T>::empty() const
{
    return _size == 0;
}

template<class T>
inline void vector<T>::clear()
{
    _size = 0;
}

template<class T>
inline void vector<T>::resize(size_t n,const T& ele)
{
    if(n <= _size)
        _size = n;
    else
    {
        T* tmp = element;
        element = new T[n];
        for(int i = 0;i<_size;++i)
        {
            element[i] = ele;
        }
        delete[] tmp;
    }
}

template<class T>
inline T& vector<T>::operator[](const size_t top)
{
    return element[top];
}

template<class T>
inline const T& vector<T>::operator[](const size_t top) const
{
    return element[top];
}

template<class T>
vector<T>& vector<T>::operator=(const vector<T>& vec)
{
    if(this != &vec)
    {
        T* tmp = element;
        element = new T[vec._capcity];
        _size = vec._size;
        _capcity = vec._capcity;
        for(int i = 0;i<_size;++i)
        {
            element[i] = vec.element[i];
        }
        delete[] tmp;
    }
    return *this;
}

template<class T>
inline T* vector<T>::begin()
{
    return element;
}

template<class T>
inline T* vector<T>::end()
{
    return element + _size;
}

template<class T>
inline const T* vector<T>::begin() const
{
    return element;
}

template<class T>
inline const T* vector<T>::end() const
{
    return element + _size;
}
