
#if 0
#include<iostream>

bool isdelete(int n,int x,int y)
{
    return n >= x && n <= y;
}

int main()
{
    int a[100]{1,2,2,7,8,9,12,14,15,19,21,22,22,29};
    int n = 13; //数组大小
    int x = 12; //随便定的删除范围x
    int y = 22; //y
    int slow = 0;   //慢指针
    int fast = 0;   //快指针
    int end = 14;   //数组结尾尾后指针
    std::cout << "删除前\n";
    for(int i = 0; i != end;++i)
    {
        std::cout << a[i] << ' ';
    }
    while(fast != end)
    {
        if(isdelete(a[fast],x,y)) ++fast;
        else a[slow++] = a[fast++];
    }
    std::cout << "\n删除后\n";
    for(int i = 0; i != slow;++i)
    {
        std::cout << a[i] << ' ';
    }


    return 0;
}

#endif

#if 0
#include<iostream>

template<typename T>
struct node
{
    T element;
    node* next = nullptr;
    node() = default;
    explicit node(const T& ele) : element(ele){}
};

template<typename T>
class list
{
    using size_type = std::size_t;
private:
    node<T>* head = new node<T>();
    node<T>* rear = head;
    size_type sz = 0;
public:
    list() = default;
    void push_back(const T& ele)
    {
        rear->next = new node<T>(ele);
        rear = rear->next;
        ++sz;
    }
    void del_range(const T& x,const T& y)
    {
        auto func = [&x,&y](const T& ele) -> bool
        {
            return ele >= x && ele <= y;
        };
        node<T>* front = head;
        node<T>* it = head->next;
        while(it)
        {
            if(func(it->element))
            {
                node<T>* tmp = it;
                front->next = it->next;
                it = it->next;
                delete tmp;
            }
            else
            {
                front = it;
                it = it->next;
            }
        }
    }
    void print()
    {
        node<T>* it = head->next;
        while(it)
        {
            std::cout << it->element << ' ';
            it = it->next;
        }
        std::cout << '\n';
    }
};

int main()
{
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(7);
    l.push_back(8);
    l.push_back(9);
    l.push_back(10);
    l.push_back(11);
    l.push_back(12);
    l.push_back(13);
    l.push_back(13);
    l.push_back(19);
    l.push_back(24);
    l.push_back(27);
    l.push_back(27);
    l.push_back(33);
    std::cout << "删除前\n";
    l.print();
    l.del_range(11,24);
    std::cout << "删除后\n";
    l.print();

    return 0;
}

#endif