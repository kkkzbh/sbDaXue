


#include<iostream>

//struct node
//{
//    int index = 0;
//    int power = 0;
//    node* next = nullptr;
//    node() = default;
//    node(int i,int p) : index(i),power(p){}
//};
//
//class list
//{
//private:
//    node* head = new node();
//    node* back = head;
//public:
//    void push_back(int i,int p)
//    {
//        back->next = new node(i,p);
//        back = back->next;
//    }
//    void derivation()
//    {
//        node* it = head->next;
//        while(it)
//        {
//            it->index *= it->power--;
//            it = it->next;
//        }
//    }
//    void print()
//    {
//        node* it = head->next;
//        int flag = 1;
//        while(it)
//        {
//            if(flag) flag = 0; else std::cout << ' ';
//            std::cout << it->index << ' ' << it->power;
//            it = it->next;
//        }
//    }
//};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int i,p;
    int flag = 1;
    while(std::cin >> i >> p)
    {
        if(!p) break;
        if(i)
        {
            if (flag) flag = 0; else std::cout << ' ';
            std::cout << i * p << ' ' << p - 1;
        }
    }
    if(flag) std::cout << 0 << ' ' << 0;
    return 0;
}