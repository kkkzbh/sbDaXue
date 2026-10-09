#pragma once
#include<iostream>

struct poly_note
{
    double index;
    double power;

    poly_note* next;
    poly_note(double idx,double pow): index(idx),power(pow),next(nullptr){}
    ~poly_note(){}
};


class poly
{
private:
    poly_note* _head;
    size_t _size;

public:
    poly();
    ~poly();
    poly(const poly& pol);
    void push(double idx,double pow);
    void insert(double idx,double pow,poly_note* pos);
    void print() const;
    poly& operator=(const poly& pol);
    friend poly operator+(const poly& pola,const poly& polb);
    friend poly operator*(const poly& pola,const poly& polb);

};

poly operator+(const poly& pola,const poly& polb);
poly operator*(const poly& pola,const poly& polb);

inline void poly::insert(double idx,double pow,poly_note* pos)
{
    if(!idx)
        return;
    poly_note* tmp = pos->next;
    pos->next = new poly_note(idx,pow);
    pos->next->next = tmp;
    _size++;
}