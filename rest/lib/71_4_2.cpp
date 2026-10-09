#include<iostream>

constexpr int size = 1e4;

class table
{
private:
    int data[size]{};
    int top = 0;
public:
    table() : data{1,5,7,9,12,14,15,36,99},top(9){}
    void insert(int x);
    void print();
    void redup();
};

void table::insert(int x)
{
    if(top == size)
    {
        std::cerr << "The table is full!\n";
        return;
    }
    int it = 0;
    while(it != top && x > data[it]) ++it;
    for(int i = top; i != it;--i)
    {
        data[i] = data[i - 1];
    }
    data[it] = x;
    ++top;
}

void table::print()
{
    for(int i = 0; i != top;++i)
    {
        std::cout << data[i] << ' ';
    }
}

void table::redup()
{
    int slow = 1;
    int fast = 1;
    while(fast != top)
    {
        if(data[fast - 1] != data[fast])
        {
            if(fast != slow) data[slow++] = data[fast++];
            else
            {
                ++slow;
                ++fast;
            }
        }
        else ++fast;
    }
    top = slow;
}

int main()
{
    table a;
    a.insert(5);
    a.insert(5);
    a.insert(9);
    a.print();
    std::cout << '\n';
    a.redup();
    a.print();
    std::cout << '\n';


    return 0;
}