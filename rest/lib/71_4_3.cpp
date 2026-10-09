


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
    void del(int left,int right);
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
    std::cout << '\n';
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

void table::del(int left,int right)
{
    int *slow = data;
    int *fast = data;
    int *end = data + top;
    while(fast != end)
    {
        if(*fast >= left && *fast <= right) ++fast;
        else *slow++ = *fast++;
    }
    top = slow - data;
}

int main()
{
    table a;
    a.insert(9);
    a.print();
    a.del(2,10);
    a.print();

    return 0;
}