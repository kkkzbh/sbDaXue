
#include<iostream>
#include"DList.h"

DList::DList() : len(0),head(nullptr){}

DList::~DList()
{
    Dnote* it = head;
    while(it)
    {
        Dnote* tmp = it;
        it = it->next;
        delete tmp;
    }
}

DList& DList::push_back(int n)
{
    if(!head)
    {
        head = new Dnote(n);
        ++len;
        return *this;
    }
    Dnote* it = head;
    while(it->next)
    {
        it = it->next;
    }
    it->next = new Dnote(n);
    it->next->last = it;
    ++len;
    return *this;
}

DList& DList::push_in(int n)
{
    Dnote* tmp = new Dnote(n);
    tmp->next = head;
    head->last = tmp;
    head = tmp;
    ++len;
    return *this;
}

void DList::print()
{
    Dnote* it = head;
    while(it)
    {
        std::cout << it->x << ' ';
        it = it->next;
    }
    std::cout << '\n';
}


void DList::Swap(int pos)
{
    if(pos < 1 || pos >= len)
    {
        std::cerr << "输入不合法！\n";
        return;
    }
    Dnote* it = head;
    if(pos == 1)
    {
        Dnote* tmphead = it->next;
        Dnote* tmp = tmphead->next;
        it->next->next = head;
        head->next = tmp;
        head = tmphead;
        tmp->last = it;
        it->last = head;
        head->last = nullptr;
        return;
    }
    for(int i = 1;i<pos - 1;it = it->next,i++);
    Dnote* p = it->next;
    Dnote* tmp = p->next->next;
    it->next = p->next;
    p->next->next = p;
    p->next = tmp;
    tmp->last = p;
    p->last = it->next;
    it->next->last = it;
}

void DList::print(int)
{
    Dnote* it = head;
    while(it->next)
    {
        it = it->next;
    }
    while(it)
    {
        std::cout << it->x << ' ';
        it = it->last;
    }
    std::cout << '\n';
}

