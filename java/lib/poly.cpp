

#include"poly.h"


poly::poly() : _head(nullptr),_size(0){}

poly::~poly()
{
    poly_note* it = _head;
    poly_note* tmp = nullptr;
    while(it)
    {
        tmp = it;
        it = it->next;
        delete tmp;
    }
}

poly::poly(const poly& pol)
{
    poly_note* itb = pol._head;
    _head = new poly_note(itb->index,itb->power);
    poly_note* ita = _head;
    itb = itb->next;
    while(itb)
    {
        insert(itb->index,itb->power,ita);
        ita = ita->next;
        itb = itb->next;
    }
}

poly& poly::operator=(const poly& pol)
{
    if(this != &pol)
    {
        poly_note* it = _head;
        poly_note* tmp = nullptr;
        while(it)
        {
            tmp = it;
            it = it->next;
            delete tmp;
        }
        poly_note* itb = pol._head;
        _head = new poly_note(itb->index,itb->power);
        poly_note* ita = _head;
        itb = itb->next;
        while(itb)
        {
            insert(itb->index,itb->power,ita);
            ita = ita->next;
            itb = itb->next;
        }
    }
    return *this;
}

poly operator+(const poly& pola,const poly& polb)
{
    poly pol;
    pol._head = new poly_note(0,0);
    poly_note* tmp = pol._head;
    poly_note* it = pol._head;
    poly_note* ita = pola._head;
    poly_note* itb = polb._head;
    while(ita && itb)
    {
        if(ita->power > itb->power)
        {
            pol.insert(ita->index,ita->power,it);
            it = it->next;
            ita = ita->next;
        }
        else if(ita->power == itb->power)
        {
            pol.insert(ita->index + itb->index,ita->power,it);
            it = it->next;
            ita = ita->next;
            itb = itb->next;
        }
        else
        {
            pol.insert(itb->index,itb->power,it);
            it = it->next;
            itb = itb->next;
        }
    }
    ita = ita ? ita : itb;
    for(;ita;it = it->next,ita = ita->next)
        pol.insert(ita->index,ita->power,it);
    pol._head = tmp->next;
    delete tmp;
    return pol;
}

poly operator*(const poly& pola,const poly& polb)
{
    poly pol;
    pol._head = new poly_note(0,0);
    poly_note* tmp = pol._head;
    poly_note* it = pol._head;
    poly_note* ita = pola._head;
    poly_note* itb = polb._head;
    while(ita)
    {
        itb = polb._head;
        it = pol._head;
        while(itb)
        {
            for(;it->next && it->next->power > ita->power+itb->power;it = it->next);
            if(it->next && it->next->power == ita->power+itb->power)
            {
                it->next->index += ita->index*itb->index;
            }
            else
            {
                pol.insert(ita->index*itb->index,ita->power+itb->power,it);
            }
            itb = itb->next;
            it = it->next;
        }
        ita = ita->next;
    }
    pol._head = tmp->next;
    delete tmp;
    return pol;
}


void poly::push(double idx,double pow)
{
    if(!idx)
        return;
    poly_note* it = new poly_note(0,0);
    poly_note* tmp = it;
    it->next = _head;
    for(;it->next && pow < it->next->power;it=it->next);
    if(it->next && pow == it->next->power)
    {
        it->next->index += idx;
        if(!idx)
        {
            poly_note* tmp = it->next;
            it->next = tmp->next;
            delete tmp;
        }
        else _size++;
    }
    else
    {
        insert(idx,pow,it);
    }
    _head = tmp->next;
    delete tmp;
}

static void show_power(int x)
{
    #define MAX 100
    const char* _utf[] = {"\u2070","\u00B9","\u00B2","\u00B3","\u2074","\u2075","\u2076",
                    "\u2077","\u2078","\u2079"};
    int stack[MAX] = {0};
    int top = -1;
    while(x)
    {
        stack[++top] = x%10;
        x/=10;
    }
    while(top != -1)
    {
        std::cout << _utf[stack[top--]];
    }
}

void poly::print() const
{

    poly_note* it = _head;
    int find = 1;
    while(it)
    {
        if(find) find = 0;
        else std::cout << " + ";
        if(1 != it->index)
            std::cout << it->index;
        if(it->power)
        {   
            std::cout << 'x';
            show_power((int)it->power);
        }
        it = it->next;
    }
}

