

#include<iostream>

constexpr int size = 1000 + 10;

class stack
{
private:
    int* stk;
    int* t;
    int maxsize;
public:
    explicit stack(int n) : stk(new int[n]),t(stk),maxsize(n){}
    ~stack(){ delete[] stk; }
    void push(int n)
    {
        *t++ = n;
    }
    void pop()
    {
        --t;
    }
    bool isempty()
    {
        return stk == t;
    }
    bool isfull()
    {
        return t - stk == maxsize;
    }
    int& top()
    {
        return t[-1];
    }
    void clear()
    {
        t = stk;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    int m;
    int k;
    std::cin >> m >> n >> k;
    int a[size];
    int w[size];
    for(int i = 1; i <= n;++i)
    {
        w[i] = i;
    }
    stack stk(m);
    for(int x = 1; x <= k;++x)
    {
        for(int i = 1; i <= n;++i)
        {
            std::cin >> a[i];
        }
        int it = 1;
        int i = 1;
        while(it != n + 1)
        {
            if(!stk.isempty() && stk.top() == it[a])
            {
                stk.pop();
                ++it;
            }
            else if(i != n + 1 && !stk.isfull())
            {
                stk.push(i++[w]);
            }
            else break;
        }
        if(stk.isempty())
        {
            if(x != 1) std::cout << "\n";
            std::cout << "YES";
        }
        else
        {
            if(x != 1) std::cout << "\n";
            std::cout << "NO";
        }
        stk.clear();
        (x == 1)["\n"];
    }

    return 0;
}