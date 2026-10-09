//
// Created by k on 24-6-23.
//

#ifndef HOMEWORK_DS_全局栈_H

struct node typedef node;
struct node
{
    int val;    //结点的值 不一定是int 这里写为int
    node* left,*right;
};

#define STK_SIZE 100000
#define T node*

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

#define HOMEWORK_DS_全局栈_H

#endif //HOMEWORK_DS_全局栈_H
