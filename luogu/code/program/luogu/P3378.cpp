#include<iostream>
#include<array>
#include<algorithm>

template<typename T,typename cmp = decltype([](const T& a,const T& b){ return a < b; })>
struct priority_queue
{
    constexpr static int M_size{ 500000 + 2 };

    std::array<T,M_size> a;
    int tp{};

    priority_queue() = default;

    priority_queue(std::initializer_list<T> il)
    {
        for(const T& it : il)
            a[tp++] = it;
        adj();
    }

    template<typename M_iterator>
    priority_queue(M_iterator st,M_iterator ed)
    {
        for(; st != ed; ++st)
            a[tp++] = *st;
        adj();
    }

    template<typename M_iterator>
    priority_queue(M_iterator st,int n)
    {
        for(int i{}; i != n; ++i)
            a[tp++] = *st++;
        adj();
    }

    void push(const T& val)
    {
        adj_up(tp++,val);
    }

    void push(T&& val)
    {
        adj_up(tp++,std::forward<T>(val));
    }

    T& top()
    {
        return a[0];
    }

    void pop()
    {
        adj_down(0,std::move(a[--tp]));
    }

    [[nodiscard]]
    int size() const noexcept
    {
        return tp;
    }

    [[nodiscard]]
    bool empty() const noexcept
    {
        return !tp;
    }

private:

    void adj_up(int it,const T& val)
    {
        for(; it and cmp{}(a[up(it)],val); it = up(it))
            a[it] = std::move(a[up(it)]);
        a[it] = val;
    }

    void adj_up(int it,T&& val)
    {
        for(; it and cmp{}(a[up(it)],val); it = up(it))
            a[it] = std::move(a[up(it)]);
        a[it] = std::forward<T>(val);
    }

    void adj_down(int it,T&& val)
    {
        int rt{ left(it) };
        while(rt < tp)
        {
            if(rt != tp - 1 and cmp{}(a[rt],a[rt + 1]))
                ++rt;
            if(cmp{}(a[rt],val))
                break;
            else
            {
                a[it] = std::move(a[rt]);
                it = rt;
                rt = left(it);
            }
        }
        a[it] = std::forward<T>(val);
    }

    void adj()
    {
        for(int it{ up(tp - 1) }; it != -1; --it)
        {
            adj_down(it,std::move(a[it]));
        }
    }

    constexpr static int up(int i)
    {
        return (i - 1) >> 1;
    }

    constexpr static int left(int i)
    {
        return (i << 1) + 1;
    }

    constexpr static int right(int i)
    {
        return (i << 1) +  2;
    }

};

priority_queue<int,std::greater<>> que;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    for(int i{ 1 },op; i <= n; ++i)
    {
        std::cin >> op;
        if(op == 1)
        {
            int val;
            std::cin >> val;
            que.push(val);
        }
        else if(op == 2)
        {
            std::cout << que.top() << '\n';
        }
        else if(op == 3)
        {
            que.pop();
        }
    }


    return 0;
}