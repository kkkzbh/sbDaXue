

#ifdef L_1_7

#include<iostream>

template<typename T>
struct node
{
    T element;
    node* next = nullptr;
    node() = default;
    explicit node(T ele) : element(ele){}
};

template<typename T>
class list;

template<typename T>
std::istream& operator>>(std::istream& is,list<T>& l);

template<typename T>
void ins(const list<T>& l1,const list<T>& l2);

template<typename T>
class list
{
public:
    using size_type = std::size_t;
    friend std::istream& operator>><T>(std::istream& is,list<T>& l);
    friend void ins<T>(const list<T>& l1,const list<T>& l2);
private:
    node<T>* head;
    node<T>* back;
    size_type size;
public:
    list() : head(new node<T>()),back(head),size(0){}
    void push_back(T ele)
    {
        back->next = new node<T>(ele);
        back = back->next;
        ++size;
    }
    void print()
    {
        if(empty())
        {
            std::cout << "NULL";
            return;
        }
        node<T>* it = head->next;
        int flag = 1;
        while(it)
        {
            if(flag) flag = 0; else std::cout << ' ';
            std::cout << it->element;
            it = it->next;
        }
    }
    bool empty()
    {
        return size == 0;
    }
};

template<typename T>
std::istream& operator>>(std::istream& is,list<T>& l)
{
    int tmp;
    while(true)
    {
        is >> tmp;
        if(tmp < 0) break;
        l.push_back(tmp);
    }
    return is;
}

template<typename T>
void ins(const list<T>& l1,const list<T>& l2)
{
    list<T> l;
    node<T>* ita = l1.head->next;
    node<T>* itb = l2.head->next;
    while(ita && itb)
    {
        if(ita->element > itb->element) itb = itb->next;
        else if(ita->element < itb->element) ita = ita->next;
        else
        {
            l.push_back(ita->element);
            ita = ita->next;
            itb = itb->next;
        }
    }
    l.print();
}

int main()
{
    list<int> l1;
    list<int> l2;
    std::cin >> l1;
    std::cin >> l2;
    ins(l1,l2);

    return 0;
}

#endif
