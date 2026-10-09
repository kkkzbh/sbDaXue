#pragma once
#include<iostream>

template<class T>
struct q_note
{
    T element;
    q_note* next;

    q_note(T n = 0):element(n),next(nullptr){}
    ~q_note(){}
}; 

template<class T>
class queue
{
private:
    q_note<T>* _front;
    q_note<T>* _back;
    size_t _size;
public:
    queue();
    ~queue();
    inline void push(T ele);
    inline void pop();
    inline T front();
    inline T back();
    inline size_t size();
    inline bool empty();
};

template<class T>
inline T queue<T>::front()
{
    return _front->element;
}

template<class T>
inline T queue<T>::back()
{
    return _back->element;
}

template<class T>
inline size_t queue<T>::size()
{
    return _size;
}


template<class T>
queue<T>::queue() : _size(0),_front(nullptr),_back(nullptr){}

template<class T>
queue<T>::~queue()
{
    q_note<T>* it = _front;
    q_note<T>* tmp = it;
    while(it)
    {
        tmp = it;
        it = it->next;
        delete tmp;
    }
}

template<class T>
void queue<T>::push(T ele)
{
    if(!_size)
    {
        _back = new q_note<T>(ele);
        _front = _back;
        _size++;
    }
    else
    {
        _back->next = new q_note<T>(ele);
        _back = _back->next;
        _size++;
    }
}

template<class T>
void queue<T>::pop()
{
    if(!_size)
    {
        std::cerr << "The queue is empty!\n";
        return;
    }
    else if(1 == _size)
    {
        delete _front;
        _front = _back = nullptr;
        _size--;
    }
    else
    {
        q_note<T>* tmp = _front;
        _front = _front->next;
        _size--;
        delete tmp;
    }
}

template<class T>
inline bool queue<T>::empty()
{
    return _size == 0;
}



