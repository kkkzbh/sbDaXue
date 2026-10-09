#pragma once

#include"../algorithm/prime.h"

enum state
{
    Empty,
    Occpuy,
    Delete,
};

template<class T>
struct hash_node
{
    T key;
    state tag = Empty;
    hash_node() = default;
    explicit hash_node(const T& k) : key(k),tag(Occpuy){}
};

template<class T>
class hashtable
{
protected:
    int tablesize;
    hash_node<T>* h;
public:
    explicit hashtable(int size);
    virtual ~hashtable(){delete[] h;}
    virtual int conversion(const T& key) const = 0;
    virtual int find(const T& key) const = 0;
    bool insert(const T& key);
    bool del(const T& key);
    hash_node<T>& visit(int index);
    hash_node<T>& operator[](int index);
};

template<class T>
inline hash_node<T> &hashtable<T>::operator[](int index)
{
    return h[index];
}

template<class T>
inline hashtable<T>::hashtable(int size) : tablesize(nextprime(size)),h(new hash_node<T>[tablesize]){}

template<class T>
inline hash_node<T> &hashtable<T>::visit(int index)
{
    return h[index];
}

template<class T>
inline bool hashtable<T>::insert(const T& key)
{
    int index = find(key);
    if(h[index].tag != Occpuy)
    {
        h[index].key = key;
        h[index].tag = Occpuy;
        return true;
    }
    return false;
}

template<class T>
inline bool hashtable<T>::del(const T &key)
{
    int index = find(key);
    if(h[index].tag == Occpuy)
    {
        h[index].tag = Delete;
        return true;
    }
    return false;
}

//****************************************************************************************************//

class hashint : public hashtable<int>
{
public:
    explicit hashint(int size) : hashtable<int>(size){}
    ~hashint() override = default;
    int conversion(const int& key) const override;
    int find(const int& key) const override;
};

inline int hashint::conversion(const int &key) const
{
    return key % tablesize;
}

int hashint::find(const int& key) const
{
    int conflict_count = 0;
    int index = conversion(key),crix = index;
    int i = 1;
    while(h[index].tag != Empty && h[index].key != key) // (p = p - index % p) p < tablesize 第二个转移公式
    {
        if(++conflict_count & 1)
        {
            index = crix + i * i;
            if(index >= tablesize) index %= tablesize;
        }
        else
        {
            index = crix - i * i;
            while(index < 0) index += tablesize;
            ++i;
        }
    }
    return index;
}



