#pragma once

struct Dnote
{
    int x;
    Dnote* last;
    Dnote* next;

    Dnote(int n = 0):x(n),last(nullptr),next(nullptr){}
};

class DList
{
private:
    Dnote* head;
    int len;

public:
    DList();
    ~DList();
    DList& push_back(int n);
    DList& push_in(int n);
    void print();
    void Swap(int pos);
    void print(int);
};