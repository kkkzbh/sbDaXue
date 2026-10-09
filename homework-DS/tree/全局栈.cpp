


#define STK_SIZE 100000
#define T int

T stack[STK_SIZE];
int pb;

void push(T v)
{
    stack[pb++] = v;
}
T top()
{
    return stack[pb - 1];
}
int empty()
{
    return pb == 0;
}
void pop()
{
    --pb;
}
int size()
{
    return pb;
}