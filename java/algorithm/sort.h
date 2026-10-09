#pragma once

#include"../lib/comparator.h"
#include"swap.h"

template<class T,class U = less<T>>
void select_sort(T* a,T* b,const U& cmp = less<T>())
{
    for(T* it = a;it != b-1;++it)
    {
        T* obj = it;
        for(T* tm = it+1;tm != b;++tm)
        {
            if(cmp(*tm,*obj))
            {
                obj = tm;
            }
        }
        if(obj != it)
        {
            swap(*it,*obj);
        }
    }
}

template<class T,class U = less<T>>
void bubble_sort(T* a,T* b,const U& cmp = less<T>())
{
    int find = 1;
    for(T* it = b - 1;it != a;--it)
    {
        find = 1;
        for(T* tm = a;tm != it;++tm)
        {
            if(cmp(tm+1,tm))
            {
                swap(tm+1,tm);
                find = 0;
            }
        }
        if(find) break;
    }
}

template<class T,class U = less<T>>
void insert_sort(T* a,T* b,const U& cmp = less<T>())
{
    int tmp = 0;
    T* tm = nullptr;
    for(T* it = a+1;it != b;++it)
    {
        tmp = *it;
        for(tm = it;tm != a && cmp(tmp,*(tm-1));--tm)
        {
            *tm = *(tm-1);
        }
        *tm = tmp;
    }
}

template<class T,class U = less<T>>
void shell_sort(T* a,T* b,const U& cmp = less<T>())
{
    int sedgwick[] = {929,505,209,109,41,19,5,1,0};
    int top = -1;
    while(sedgwick[++top] >= b-a);
    int tmp = 0;
    T* tm = nullptr;
    for(int delta = sedgwick[top];delta != 0;delta = sedgwick[++top])
    {
        for(T* it = a + delta;it < b;++it)
        {
            tmp = *it;
            for(tm = it;tm - delta >= a && cmp(&tmp,tm-delta); tm -= delta)
            {
                *tm = *(tm - delta);
            }
            *tm = tmp;
        }
    }
}

template<class T>
static void perc_down(T* a,int top,int N)
{
    int it = 2*top + 1;
    int value = a[top];
    while(it < N)
    {
        if(it != N-1 && a[it] < a[it+1])
        {
            ++it;
        }
        if(value >= a[it]) break;
        else
        {
            a[top] = a[it];
            top = it;
            it = 2*top + 1;
        }
    }
    a[top] = value;
}

template<class T,class U = less<T>>
void heap_sort(T* a,T* b,const U& cmp = less<T>())
{
    for(int i = ((b-a)-2)/2;i >= 0;--i)
    {
        perc_down(a,i,b-a);
    }
    for(int i = b-a-1;i != 0;--i)
    {
        swap(a,a+i);
        perc_down(a,0,i);
    }
}

template<class T,class U>
static void delete_merge(T* begin,T* mid,T* end,T* tmp,const U& cmp)
{
    T* ita = begin;
    T* itb = mid;
    int top = -1;
    while(ita != mid && itb != end)
    {
        if(cmp(itb,ita)) tmp[++top] = *itb++;
        else tmp[++top] = *ita++;
    }
    while(ita != mid) tmp[++top] = *ita++;
    while(itb != end) tmp[++top] = *itb++;
    top = -1;
    while(begin != end) *begin++ = tmp[++top];
}


template<class T,class U>
static void delete_msort(T* begin,T* end,T* tmp,const U& cmp)
{
    if(begin+1 != end)
    {
        delete_msort(begin,begin + (end-begin)/2,tmp,cmp);
        delete_msort(begin + (end-begin)/2,end,tmp,cmp);
        delete_merge(begin,begin + (end-begin)/2,end,tmp,cmp);
    }
}

template<class T,class U = less<T>>
void delete_merge_sort(T* a,T* b,const U& cmp = less<T>())
{
    T* tmp = new T[b-a];
    delete_msort(a,b,tmp,cmp);
    delete[] tmp;
}

template<class T,class U>
static void merge(int a,int mid,int b,T* A,T* tmp,const U& cmp)
{
    int ita = a;
    int itb = mid;
    int top = a-1;
    while(ita != mid && itb != b)
    {
        if(cmp(A[itb],A[ita])) tmp[++top] = A[itb++];
        else tmp[++top] = A[ita++];
    }
    while(ita != mid) tmp[++top] = A[ita++];
    while(itb != b) tmp[++top] = A[itb++];
}

template<class T,class U>
static void msort(T*a,T*b,T*tmp,int length,const U& cmp)
{
    int it;
    for(it = 0;it + 2*length< b-a;it += 2*length)
    {
        merge(it,it+length,it+2*length,a,tmp,cmp);
    }
    if(it + length < b-a) merge(it,it+length,b-a,a,tmp,cmp);
    else while(it != b-a) tmp[it++] = a[it];
}

template<class T,class U = less<T>>
void merge_sort(T* a,T* b,const U& cmp = less<T>())
{
    T* tmp = new T[b-a];
    int length = 1;
    while(length < b-a)
    {
        msort(a,b,tmp,length,cmp);
        length *= 2;
        msort(tmp,tmp + (b - a),a,length,cmp);  //不论怎么说 最终哪怕上次排好了 这个msort也会倒回去
        length *= 2;
    }
    delete[] tmp;
}

template<class T,class U>
static T median3(T *a,T *b,const U& cmp)
{
    T* mid = a + (b-a)/2;
    if(cmp(mid,a)) swap(mid,a);
    if(cmp(b-1,a)) swap(b-1,a);
    if(cmp(b-1,mid)) swap(b-1,mid);
    if(a != b - 2)
        swap(mid,b-2);
    return *(b-2);
}

template<class T,class U = less<T>>
void quick_sort(T* a,T* b,const U& cmp = less<T>())
{
    static const int cutoff = (b-a)/2;
    if(b-a > cutoff)
    {
        T pivot = median3(a,b,cmp);
        T* ita = a;
        T* itb = b-2;
        while(ita < itb)
        {
            while(cmp(*++ita,pivot)){}
            while(cmp(pivot,*--itb)){}
            if(ita < itb) swap(ita,itb);
            else break;
        }
        swap(ita,b-2);
        quick_sort(a,ita,cmp);
        quick_sort(ita+1,b,cmp);
    }
    else
        insert_sort(a,b,cmp);
}

template<class T,class U = less<T>>
void insert_sort(int* table,int n,T* data,const U& cmp = less<T>())
{
    for(int i = 1;i<n;++i)
    {
        int it;
        int tmp = table[i];
        for(it = i;it != 0 && cmp(data[tmp],data[table[it-1]]);--it)
        {
            table[it] = table[it-1];
        }
        table[it] = tmp;
    }
}

template<class T,class U>
static T median3(int* table,int n,T* data,const U& cmp)
{
    int mid = n/2;
    if(cmp(data[table[mid]],data[table[0]])) swap(table[mid],table[0]);
    if(cmp(data[table[n-1]],data[table[0]])) swap(table[n-1],table[0]);
    if(cmp(data[table[n-1]],data[table[mid]])) swap(table[n-1],table[mid]);
    if(0 != n-2)
        swap(table[n-2],table[mid]);
    return data[table[n-2]];
}

template<class T,class U = less<T>>
void quick_sort(int* table,int n,T* data,const U& cmp = less<T>())
{
    static const int cutoff = n/4;
    if(n >= cutoff)
    {
        T pivot = median3(table,n,data,cmp);
        int ita = 0;
        int itb = n-2;
        while(ita < itb)
        {
            while (cmp(data[table[++ita]],pivot));
            while (cmp(pivot,data[table[--itb]]));
            if(ita < itb) swap(table[ita],table[itb]);
        }
        swap(table[ita],table[n-2]);
        quick_sort(table,ita,data,cmp);
        quick_sort(table + ita + 1,n-ita-1,data,cmp);
    }
    else
    {
        insert_sort(table,n,data,cmp);
    }
}

template<class T>
void table_sort(int* table,int n,T* data)
{
    int top;
    T tmp;
    int tmptop;
    while(true)
    {
        top = 0;
        while(top == table[top] && top != n) ++top;
        if(n == top) break;
        tmp = data[top];
        do
        {
            data[top] = data[table[top]];
            tmptop = table[top];
            table[top] = top;
            top = tmptop;
        }while(table[top] != table[table[top]]);
        data[top] = tmp;
        table[top] = top;
    }
}

static int get_digit(int x,int digit)
{
    int ret = x % 10;
    while(--digit)
    {
        x /= 10;
        ret = x%10;
    }
    return ret;
}

void LSDradix_sort(int* a,int* b,const int n = 9)
{
    struct node
    {
        int value;
        node* next;
        node():next(nullptr){}
        node(int x):value(x),next(nullptr){}
    };
    struct bucket
    {
        node* front;
        node* back;
        bucket():front(nullptr),back(nullptr){}
        void push_back(node* x)
        {
            if(!front)
            {
                front = back = x;
                return;
            }
            back->next = x;
            back = x;
        }
    }bucket[10];
    int* itb = b;
    node* list = new node(*--itb);
    node* tmp = nullptr;
    while(a != itb)
    {
        tmp = new node(*--itb);
        tmp->next = list;
        list = tmp;
    }
    int digitv;
    node* it = nullptr;
    for(int digit = 1;digit <= n;++digit)
    {
        it = list;
        while(it)
        {
            digitv = get_digit(it->value, digit);
            bucket[digitv].push_back(it);
            tmp = it,it = it->next,tmp->next = nullptr;
        }
        list = nullptr;
        for(int D = 9;D >= 0;--D)
        {
            if(bucket[D].front)
            {
                bucket[D].back->next = list;
                list = bucket[D].front;
                bucket[D].front = bucket[D].back = nullptr;
            }
        }
    }
    it = list;
    while(it)
    {
        *a++ = it->value;
        tmp = it;
        it = it->next;
        delete tmp;
    }
}

void MSDradix_sort(int* a,int* b,const int n = 9)
{
    if(n == 0) return;
    struct node
    {
        int value;
        node* next;
        node():next(nullptr){}
        node(int x):value(x),next(nullptr){}
    };
    struct bucket
    {
        node* front;
        node* back;
        bucket():front(nullptr),back(nullptr){}
        void push_back(node* x)
        {
            if(!front)
            {
                front = back = x;
                return;
            }
            back->next = x;
            back = x;
        }
        int pop()
        {
            node* tmp = front;
            int v = tmp->value;
            if(front == back)
            {
                front = back = nullptr;
                delete tmp;
                return v;
            }
            front = front->next;
            delete tmp;
            return v;
        }
    }bucket[10];
    int* itb = b;
    node* list = new node(*--itb);
    node* tmp;
    while(a != itb)
    {
        tmp = new node(*--itb);
        tmp->next = list;
        list = tmp;
    }
    node* it = list;
    int digitv;
    while(it)
    {
        digitv = get_digit(it->value,n);
        bucket[digitv].push_back(it);
        tmp = it;
        it = it->next;
        tmp->next = nullptr;
    }
    int* ita = a;
    for(int i = 0;i<10;++i)
    {
        if(bucket[i].front)
        {
            while (bucket[i].front)
            {
                *itb++ = bucket[i].pop();
            }
            MSDradix_sort(ita,itb,n-1);
            ita = itb;
        }
    }
}

