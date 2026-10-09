


#define QUE_SIZE 1000000
#define T int
// 队列开足够大 非循环队列
T queue[QUE_SIZE];
int l,r;

void push(T val)
{
    queue[r++] = val;
}
T front()
{
    return queue[l];
}
T back()
{
    return queue[r - 1];
}
void pop()
{
    ++l;
}
int empty()
{
    return l == r;
}
int size()
{
    return r - l;
}
