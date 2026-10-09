#pragma once


template<class T>
struct list_node
{
    T element;
    list_node<T>* next;

    list_node<T>():element(),next(nullptr){}
    list_node<T>(const T& ele):element(ele),next(nullptr){}
    ~list_node(){delete next;}
};

template<class T>
class it_single_list
{
private:
    list_node<T>* it;
public:
    inline it_single_list():it(nullptr){}
    inline it_single_list(list_node<T>* ite) : it(ite){}
    inline it_single_list(const it_single_list& ite)
    {
        it = ite.it;
    }
    inline ~it_single_list(){}
    inline list_node<T>& operator*()
    {
        return *it;
    }
    inline list_node<T>* operator->()
    {
        return it;
    }
    inline it_single_list& operator=(const list_node<T>* ite)
    {
        it = ite;
        return *this;
    }
    inline it_single_list& operator++()
    {
        it = it->next;
        return *this;
    }
    inline it_single_list operator++(int)
    {
        it_single_list tmp(it);
        it = it->next;
        return tmp;
    }
    inline bool operator==(const it_single_list& ite)
    {
        return it == ite.it;
    }
    inline bool operator!=(const it_single_list& ite)
    {
        return !(*this == ite);
    }
};

template<class T>
class single_list
{
public:
    using iterator = it_single_list<T>;
private:
    list_node<T>* head;
    int _size;
public:
    inline single_list();
    inline ~single_list();
    void push_up(const T& ele);
    void push_back(const T& ele);
    void pop_up();
    void pop_back();
    bool empty();
    inline int size();
    inline iterator begin();
    inline iterator end();
};



template <class T>
single_list<T>::single_list() : head(nullptr),_size(0){}

template <class T>
single_list<T>::~single_list()
{
    delete head;
}

template <class T>
void single_list<T>::push_up(const T &ele)
{
    list_node<T>* tmp = new list_node<T>(ele);
    tmp->next = head;
    head = tmp;
    ++_size;
}

template <class T>
void single_list<T>::push_back(const T &ele)
{
    if(!head)
    {
        head = new list_node<T>(ele);
        ++_size;
        return;
    }
    list_node<T>* it = head;
    while(it->next)
        it = it->next;
    it->next = new list_node<T>(ele);
    ++_size;
}

template <class T>
void single_list<T>::pop_up()
{
    if(head)
    {
        list_node<T>* tmp = head;
        head = head->next;
        --_size;
    }
}

template <class T>
void single_list<T>::pop_back()
{
    if(head)
    {
        list_node<T>* it = head;
        list_node<T>* lastv = nullptr;
        while(it->next)
        {
            lastv = it;
            it = it->next;
        }
        if(lastv)
        {
            delete it;
            lastv->next = nullptr;
        }
        else
        {
            delete head;
            head = nullptr;
        }
    }

}

template <class T>
bool single_list<T>::empty()
{
    return _size == 0;
}

template <class T>
int single_list<T>::size()
{
    return _size;
}

template<class T>
auto single_list<T>::begin() -> iterator
{
    single_list<T>::iterator ite(head);
    return ite;
}

template<class T>
auto single_list<T>::end() -> iterator
{
    single_list<T>::iterator ite;
    return ite;
}


