

#ifdef _01_1_2

#include<iostream>
#include<stack>

constexpr int D = 4;

char post[D]{'\0','a','b','c'};

template<typename T>
void swap(T& a,T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

static int flag = 1;

class hanio
{
private:
    std::stack<int> stk[D];
    int n;
public:
    explicit hanio(int x) : n(x)
    {
        for(int i = x;i >= 1;--i)
        {
            stk[1].push(i);
        }
    }
    void move(int src,int dst)
    {
        int tmp = stk[src].top();
        stk[src].pop();
        stk[dst].push(tmp);
        if(flag) flag = 0; else std::cout << '\n';
        std::cout << post[src] << " -> " << post[dst];
    }
    std::stack<int>& operator[](int i)
    {
        return stk[i];
    }
};

inline void add(int& n)
{
    ++n;
    if(n > 3) n -= 3;
}

int main()
{
    int n;
    std::cin >> n;
    if(n & 1) swap(post[2],post[3]);
    hanio a(n);
    int src = 1;
    int dst = 2;
    while(true)
    {
        a.move(src,dst);
        if(a[dst].size() == n) break;
        src = dst;
        add(dst);
        int l = src + 1;
        int r = src + 2;
        if(l > 3) l-= 3;
        if(r > 3) r -= 3;
        if(a[l].empty()) a.move(r,l);
        else if(a[r].empty()) a.move(l,r);
        else
        {
            if(a[r].top() > a[l].top()) a.move(l,r);
            else a.move(r,l);
        }
    }

    return 0;
}

#endif
