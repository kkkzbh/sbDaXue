#pragma once

struct note
{
    double index;
    double power;
    note* next;

    note(double idx,double pow) : index(idx) , power(pow),next(nullptr){}
};

class Poly
{
private:
    int len;
    note* head;

public:
    Poly();
    ~Poly();
    Poly(const Poly& P);

    Poly& push_up(double idx,double pow);
    note* push_up(double idx,double pow,note* endpos);
    Poly& operator=(const Poly& P);
    void print();
    void Sort();
    void Swap(note* pos1,note* pos2);

public:
    friend Poly operator+(const Poly& P1,const Poly& P2);
    friend Poly operator*(const Poly& P1,const Poly& P2);
};

Poly operator+(const Poly& P1,const Poly& P2);

Poly operator*(const Poly& P1,const Poly& P2);