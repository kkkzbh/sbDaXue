#pragma once

struct note
{
    int x;
    note* next;

    note(int n = 0):x(n),next(nullptr){}
};

class List
{
private:
    note* head;
    int len;

public:
    List();
    List(const List & L);
    ~List();

    List& push_back(int n);
    note* push_back(int n,note* it);
    List& push_in(int n);
    void print();
    void Swap(int pos1,int pos2);
    void Swap(int pos);
    void Sort();
    List& operator=(const List & L);

public:
    friend List operator&(List& L1,List& L2);
    friend List operator^(List& L1,List& L2);
};


List operator&(List& L1,List& L2);

List operator^(List& L1,List& L2);


