#pragma once

#include"vector.hpp"
#define ROOT -1

namespace disjoint
{

template<class T>
struct disjoint_node
{
    T element;
    int parent;
    disjoint_node(){}
    disjoint_node(const T& ele):element(ele),parent(ROOT){}
};

template<class T>
class disjoint_set
{
private:
    vector<disjoint_node<T>> sets;
public:
    disjoint_set();
    disjoint_set(const disjoint_set& set) = delete;
    void insert(const T& ele);
    int find(const T& ele) const;
    void uni(const T& a,const T& b);
    bool judge(const T& a,const T& b);
};

template<class T>
disjoint_set<T>::disjoint_set():sets(){}

template<class T>
inline void disjoint_set<T>::insert(const T& ele)
{
    sets.push_back(disjoint_node<T>(ele));
}

template<class T>
int disjoint_set<T>::find(const T& ele) const
{
    int i;
    for(i = 0;i<sets.size() && ele != sets[i].element;++i);
    if(i == sets.size()) return -1;
    while(sets[i].parent >= 0)
    {
        i = sets[i].parent;
    }
    return i;
}

template<class T>
void disjoint_set<T>::uni(const T& a,const T& b)
{
    int r1 = find(a);
    int r2 = find(b);
    if(r1 == r2) return;
    if(sets[r1].parent <= sets[r2].parent)
    {
        sets[r1].parent += sets[r2].parent;
        sets[r2].parent = r1;
    }
    else
    {
        sets[r2].parent += sets[r1].parent;
        sets[r1].parent = r2;
    }
}

template<class T>
inline bool disjoint_set<T>::judge(const T& a,const T& b)
{
    return find(a) == find(b);
}

}

namespace array
{

class eff_set
{
private:
    vector<int> sets;
    size_t _size;
public:
    eff_set(size_t n);
    void insert(int x);
    int find(int x);
    void uni(int a,int b);
    bool judge(int a,int b);
};

eff_set::eff_set(size_t n):sets(n){}

inline void eff_set::insert(int x)
{
    sets[x] = ROOT;
}

int eff_set::find(int x)
{
    if(sets[x] < 0)
        return x;
    return sets[x] = find(sets[x]);
}

void eff_set::uni(int a, int b)
{
    int r1 = find(a);
    int r2 = find(b);
    if(r1 == r2) return;
    if(sets[r1] >= sets[r2])
    {
        sets[r1] += sets[r2];
        sets[r2] = r1;
    }
    else
    {
        sets[r2] += sets[r1];
        sets[r1] = r2;
    }
}

inline bool eff_set::judge(int a, int b)
{
    return find(a) == find(b);
}


}













