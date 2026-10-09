


#include<iostream>

template<typename T>
struct node
{
    T val;
    node* next = nullptr;
    node() = default;
    node(const T& v) : val(v){}
};

template<typename T>
struct __It
{
    using node = node<T>;
    node* it;
    __It(node* const &i){ it = i; }
    __It& operator++(){ it = it->next; return *this; }
    node* operator->(){ return it; }
    operator node*(){ return it; }
    void destruct(){ delete it; }
};

template<typename T>
struct list
{
    using node = node<T>;
    using size_type = std::size_t;
    using iterator = __It<T>;
    node* head = new node();
    node* back = head;
    size_type sz = 0;
    list(){ back->next =head; }
    void push_back(const T& v)
    {
        back = back->next = new node(v);
        back->next = head->next;
        ++sz;
    }
    iterator erase(iterator& fr)
    {
        if(fr->next == back) back = fr;
        if(!sz) back = head;
        iterator tmp = fr->next;
        fr = fr->next = tmp->next;
        --sz;
        tmp.destruct();
        return fr;
    }
    iterator begin(){ return iterator(head->next); }
    template<typename ...Args>
    void emplace_back(Args... args)
    {
        back = back->next = new node(args...);
        back->next = head->next;
        ++sz;
    }
    size_type size(){ return sz; }
    bool empty(){ return !sz; }
};

int main()
{
    list<int> l;
    int n,cnt;
    std::cin >> n >> cnt;
    for(int i = 1; i <= n;++i) l.push_back(i);
    auto it = l.begin();
    while(!l.empty())
    {
        std::cout << it->next->val << ' ';
        l.erase(it);
    }

    return 0;
}