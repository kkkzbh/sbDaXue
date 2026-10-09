

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
struct queue
{
    using node = node<T>;
    using size_type = std::size_t;
    node* head = new node();
    node* bk = head;
    size_type sz = 0;
    size_type cap = 0;

    explicit queue(size_type capicity) : cap(capicity){}
    void push_back(const T& v)
    {
        if(sz == cap)
        {
            node* tmp = head->next;
            head->next = tmp->next;
            delete tmp;
            --sz;
        }
        bk = bk->next = new node(v);
        ++sz;
    }
    bool find(const T& v)
    {
        node* it = head->next;
        while(it && it->val != v) it = it->next;
        if(it) return true;
        return false;
    }
};

int main()
{
    int m,n;
    std::cin >> m >> n;
    queue<int> que(m);
    int v;
    int cnt{};
    for(int i = 1; i <= n;++i)
    {
        std::cin >> v;
        if(!que.find(v)) que.push_back(v),++cnt;
    }
    std::cout << cnt;

    return 0;
}