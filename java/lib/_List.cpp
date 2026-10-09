
#include<iostream>
#include "_List.h"

List::List() : len(0),head(nullptr){}

List::List(const List & L)
{
    len = L.len;
    note* itb = L.head;
    head = new note(itb->x);
    note* ita = head;
    itb = itb->next;
    while(itb)
    {
        push_back(itb->x,ita);
        ita = ita->next;
        itb = itb->next;
    }
}


List::~List()
{
    note* it = head;
    while(it)
    {
        note* tmp = it;
        it = it->next;
        delete tmp;
    }
}

inline List& List::push_back(int n)
{
    if(!head)
    {
        head = new note(n);
        ++len;
        return *this;
    }
    note* it = head;
    while(it->next)
    {
       it = it->next;
    }
    note* tmp = new note(n);
    it->next = tmp;
    ++len;
    return *this;
}

inline note* List::push_back(int n,note* it)
{
    if(it && it->next)
    {
        std::cerr << "请确保传入末指针\n";
        return it;
    }
    else if(!it)
    {
        it = new note(n);
        return it;
    }
    else
    {
        it->next = new note(n);
        return it->next;
    }
}



List& List::push_in(int n)
{
    note* tmp = new note(n);
    tmp->next = head;
    head = tmp;
    ++len;
    return *this;
}

void List::print()
{
    if(!head)
        return;
    note* it = head;
    while(it)
    {
        std::cout << it->x << ' ';
        it = it->next;
    }
    std::cout << '\n';
}


void List::Swap(int pos1,int pos2)
{
    if(pos1 > len || pos2 > len || pos1< 1 || pos2 < 1 || pos1 == pos2)
    {
        std::cerr << "输入不合法！\n";
        return;
    }
    note* it1 = head;
    note* it2 = head;
    for(int i = 1;i < pos1 - 1;it1 = it1->next,i++);
    for(int i = 1;i < pos2 - 1;it2 = it2->next,i++);
    note* max = pos1 > pos2 ? it1 : it2;
    note* min = pos1 > pos2 ? it2 : it1;
    if(pos1 == 1 || pos2 == 1)
    {
        head = max->next;
        note* tmp = head->next;
        head->next = min->next == head ? min : min->next;
        max->next = min;
        min->next = tmp;
        return;
    }
    note* pmax = max->next;
    note* pmin = min->next;
    note* tmp = pmax->next;
    min->next = pmax;
    pmax->next = pmin->next == pmax ? pmin : pmin->next;
    max->next = pmin;
    pmin->next = tmp;
}


void List::Swap(int pos)
{
    if(pos < 1 || pos > len -1)
    {
        std::cerr << "输入不合法!\n";
        return;
    }
    note* it = head;
    for(int i = 1;i<pos - 1;it = it->next,i++);
    if(pos == 1)
    {
        note* tmp = it->next->next;
        note* tmphead = it->next;
        it->next->next = head;
        head->next = tmp;
        head = tmphead;
        return;
    }
    note* p = it->next;
    note* tmp = p->next->next;
    it->next = p->next;
    p->next->next = p;
    p->next = tmp;
}

void List::Sort()
{
    for(note* it = head;it; it = it->next)
    {
        int min = it->x;
        note* tmp = it;
        for(note* ita = it->next;ita;ita = ita->next)
        {
            if(ita->x < min)
            {
                min = ita->x;
                tmp = ita;
            }
        }
        if(tmp != it)
        {
        tmp->x = it->x ^ tmp->x;
        it->x = it->x ^ tmp->x;
        tmp->x = it->x ^ tmp->x;
        }
    }
}

List operator^(List& L1,List& L2)
{
    List L;
    note* it = L.head;
    for(note* it1 = L1.head,*it2 = L2.head;it1 && it2;)
    {
        if(it1->x == it2->x)
        {
            it = L.push_back(it1->x,it);
            it1 = it1->next;
            it2 = it2->next;
        }
        else if(it1->x > it2->x)
        {
            it2 = it2->next;
        }
        else
        {
            it1 = it1->next;
        }
    }
    return L;
}

List operator&(List& L1,List& L2)
{
    List L;
    note* it1 = L1.head;
    note *it2 = L2.head;
    note* it = L.head;
    while(it1 && it2)
    {
        if(it1->x > it2->x)
        {
            it = L.push_back(it2->x,it);
            it2 = it2->next;
        }
        else if(it1->x < it2->x)
        {
            it = L.push_back(it1->x,it);
            it1 = it1->next;
        }
        else
        {
            it = L.push_back(it1->x,it);
            it1 = it1->next;
            it2 = it2->next;
        }
    }
    it1 = it1 ? it1 : it2;
    while(it1)
    {
        it = L.push_back(it1->x,it);
        it1 = it1->next;
    }
    return L;
}

List& List::operator=(const List & L)
{
    note* it = head;
    while(it)
    {
        note* tmp = it;
        it = it->next;
        delete tmp;
    }
    len = L.len;
    note* itb = L.head;
    head = new note(itb->x);
    note* ita = head;
    itb = itb->next;
    while(itb)
    {
        push_back(itb->x,ita);
        ita = ita->next;
        itb = itb->next;
    }
    return *this;
}
