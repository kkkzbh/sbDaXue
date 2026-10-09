

#include<iostream>

struct node
{
    int x;
    node* next;
    explicit node(int n = 0) : x(n),next(nullptr){}
};

class list
{
private:
    node* head;
    node* back;
    std::size_t sz;
public:
    list() : head(new node()),back(head),sz(0){}
    void push_back(int x)
    {
        back->next = new node(x);
        back = back->next;
    }
    void reverse()
    {
        if(head == back) return;
        back = head->next;
        node* it = head->next;
        head->next = nullptr;
        while(it)
        {
            node* tmp = it->next;
            it->next = head->next;
            head->next = it;
            it = tmp;
        }
    }
    void print()
    {
        node* it = head->next;
        while(it)
        {
            std::cout << it->x << ' ';
            it = it->next;
        }
    }
};


int main()
{
    list l;
    for(int i = 1; i <= 5;++i)
    {
        l.push_back(i);
    }
    l.reverse();
    l.push_back(999);
    l.print();

    return 0;
}