

#if 0

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

#if 0

#include<iostream>

constexpr char move[]{'\0','a','b','c'};

void hanoi(int n,int a,int b,int c)
{
    if(!n) return;
    std::cout << move[a] << " -> " << move[c] << '\n';
    hanoi(n - 1,a,c,b);
    hanoi(1,a,b,c);
    hanoi(n - 1,b,a,c);
}

int main()
{
    int n; std::cin >> n;
    hanoi(n,1,2,3);

    return 0;
}

#endif

#if 0



#include<iostream>
#include<stack>
#include<algorithm>

constexpr int size = 4;

char post[]{'\0','a','b','c'};

class stack
{
private:
    std::stack<int> stk[size];
    int n;
public:
    explicit stack(int N) : n(N)
    {
        for(int i = N;i != 0;--i) stk[1].push(i);
    }
    void move(const int src,const int dst)
    {
        std::cout << post[src] << " -> " << post[dst] << '\n';
        stk[dst].push(stk[src].top());
        stk[src].pop();
    }
    std::stack<int>& operator[](std::size_t index){ return stk[index];}
};

int main()
{
    std::size_t n; std::cin >> n;
    stack stk(n);
    if(n & 1) std::swap(post[2],post[3]);
    int src = 1;
    int dst = 2;
    while(true)
    {
        stk.move(src,dst);
        src = dst;
        dst = dst % 3 + 1;
        if(stk[src].size() == n) break;
        int left = (src + 1 ) % 3 + 1;
        int right = src % 3 + 1;
        if(stk[left].empty()) stk.move(right,left);
        else if(stk[right].empty()) stk.move(left,right);
        else if(stk[left].top() > stk[right].top()) stk.move(right,left);
        else stk.move(left,right);
    }

    return 0;
}

#endif