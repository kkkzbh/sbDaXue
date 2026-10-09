
#include<iostream>
#include"_Poly.h"

Poly::Poly() : len(0),head(nullptr){}

Poly::Poly(const Poly& P) : len(P.len)
{
    note* itb = P.head;
    head = new note(itb->index,itb->power);
    note* ita = head;
    itb = itb->next;
    while(itb)
    {
        ita = push_up(itb->index,itb->power,ita);
        itb = itb->next;
    }
}


Poly::~Poly()
{
    note* it = head;
    while(it)
    {
        note* tmp = it;
        it = it->next;
        delete tmp;
    }
}

Poly& Poly::push_up(double idx,double pow)
{
    if(!head)
    {
        head = new note(idx,pow);
        ++len;
        return *this;
    }
    note* it = head;
    while(it->next && it->power != pow)
    {
        it = it->next;
    }
    if(it->power == pow)
    {
        it->index += idx;
    }
    else
    {
        it->next = new note(idx,pow);
        ++len;
    }
    return *this;
}

note* Poly::push_up(double idx,double pow,note* endpos)
{
    if(endpos && endpos->next)
    {
        std::cerr << "请确保传入末指针\n";
        return nullptr;
    }
    endpos->next = new note(idx,pow);
    return endpos->next;
}



Poly operator+(const Poly& P1,const Poly& P2)
{
    note* ita = P1.head;
    note* itb = P2.head;
    Poly P;
    while(ita)
    {
        P.push_up(ita->index,ita->power);
        ita = ita->next;
    }
    while(itb)
    {
        ita = P.head;
        while(ita->power != itb->power && ita->next)
        {
            ita = ita->next;
        }
        if(ita->power == itb->power)
        {
            ita->index += itb->index;
        }
        else
        {
            ita->next = new note(itb->index,itb->power);
        }
        itb = itb->next;
    }
    return P;
}

Poly& Poly::operator=(const Poly& P)
{
    note* ita = head;
    note* itb = P.head;
    while(ita)
    {
        note* tmp = ita;
        ita = ita->next;
        delete tmp;
    }
    len = P.len;
    head = new note(itb->index,itb->power);
    ita = head;
    itb = itb->next;
    while(itb)
    {
        ita = push_up(itb->index,itb->power,ita);
        itb = itb->next;
    }
    return *this;
}

void Poly::print()
{
    note* it = head;
    while(it)
    {
        std::cout << it->index << "x^" << it->power;
        it = it->next;
        if(it) std::cout << " + ";
    }
    std::cout << '\n';
}


Poly operator*(const Poly& P1,const Poly& P2)
{
    Poly P;
    for(note* ita = P1.head;ita;ita = ita->next)
    {
        note* itb = P2.head;
        while(itb)
        {
            P.push_up(ita->index*itb->index,ita->power+itb->power);
            itb = itb->next;
        }
    }
    return P;
}

void Poly::Swap(note* pos1,note* pos2)
{
    if(pos1 == pos2)
    {
        return;
    }
    else if(pos1 == head || pos2 == head)
    {
        note* tmp = pos1 == head ? pos2 : pos1;
        note* ita = head;
        note* itb = head;
        while(itb->next != tmp)
        {
            itb = itb->next;
        }
        note* btmp = tmp->next;
        head = tmp;
        tmp->next = ita->next == tmp ? ita : ita->next;
        itb->next = ita;
        ita->next = btmp;
    }
    note* ita = head;
    note* itb = head;
    int len = 0;
    while(ita->next != pos1)
    {
        ita = ita->next;
        len++;
    }
    while(itb->next != pos2)
    {
        itb = itb->next;
        len--;
    }

}

void Poly::Sort()
{
    for(note* ita = head;ita;ita = ita->next)
    {
        for(note* itb = ita->next;itb;itb = itb->next)
        {

        }
    }
}
