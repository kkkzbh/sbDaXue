//
// Created by k on 24-6-23.
//


// 求最大值
#define MAX(A,B) ((A) > (B) ? (A) : (B))
//求最小值
#define MIN(A,B) ((A) < (B) ? (A) : (B))

//交换

#define T int**
void swap(T* a,T* b)
{
    T c = *a;
    *a = *b;
    *b = c;
}