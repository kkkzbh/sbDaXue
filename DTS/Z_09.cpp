

#include<iostream>
constexpr int size = 1e5 + 10;

template<typename T>
void swap(T* a,T* b)
{
    T c = *a;
    *a = *b;
    *b = c;
}

template<typename T>
void swap(T& a,T& b)
{
    T c = a;
    a = b;
    b = c;
}

template<typename T>
void insert_sort(T* beg,T* end)
{
    for(T* it = beg + 1; it < end;++it)
    {
        T* back = it;
        T tmp = *back;
        while(back != beg && tmp < *(back - 1))
        {
            *back = *(back - 1);
            --back;
        }
        *back = tmp;
    }
}

template<typename T>
T mediea3(T *a,T *b)
{
    --b;
    if(a == b) return *a;
    T* mid = a + (b - a) / 2;
    if(*mid < *a) swap(a,mid);
    if(*b < *a) swap(b,a);
    if(*b < *mid) swap(b,mid);
    swap(mid,b-1);
    return *(b-1);
}

template<typename T>
void quick_sort(T* a,T* b)
{
    static const int cutoff = (b - a) / 4 > 100 ? (b - a) / 4 : 100;
    if(b - a >= cutoff)
    {
        T pivot = mediea3(a,b);
        T* ita = a;
        T* itb = b - 2;
        while(ita < itb)
        {
            while(*++ita < pivot);
            while(*--itb > pivot);
            if(ita < itb) swap(ita,itb);
        }
        swap(ita,b-2);
        quick_sort(a,ita);
        quick_sort(ita + 1,b);
    }
    else
    {
        insert_sort(a,b);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    int arr[size];
    for(int i = 1; i <= n;++i)
    {
        std::cin >> arr[i];
    }
    quick_sort(arr + 1,arr + 1 + n);
    for(int i = 1,flag = 1; i <= n;++i)
    {
        if(flag) flag = 0; else std::cout << ' ';
        std::cout << arr[i];
    }

    return 0;
}