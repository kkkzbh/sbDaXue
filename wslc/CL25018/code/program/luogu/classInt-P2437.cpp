

#ifdef P2437

%:include<iostream>
#include<cstring>
%:include<utility>

class Int
{
    friend Int operator+(const Int& a,const Int& b);
    friend std::ostream& operator<<(std::ostream& os,const Int& x);
private:
    static constexpr int size = 2000 + 10;
    int* a = nullptr;
    int digit = 0;
public:
    Int() = default;
    explicit Int(const std::string& s) :a(new int[s.size() * 2]) ,digit(s.size())
    {
        int sz = s.size();
        for(int i = sz - 1;i >= 0;--i)
        {
            a[sz - i] = s[i] - '0';
        }
    }
    explicit Int(int x) : a(new int[size]{0,x}),digit(1){}
    Int(Int&& x) noexcept : a(x.a),digit(x.digit)
    {
        x.a = nullptr;
    }
    void print()
    {
        for(int i = 0; i < size;++i)
        {
            std::cout << a[i] << ' ';
        }
        std::cout << '\n';
    }
    void clear()
    {
        memset(a + 1,0,sizeof(int) * digit);
        digit = 0;
    }
    Int& operator +=(const Int& x)
    {
        if(!a) a = new int[size]{};
        int max = digit > x.digit ? digit : x.digit;
        for(int i = 1; i <= max;++i)
        {
            a[i] += x.a[i];
            a[i + 1] += a[i] / 10;
            a[i] %= 10;
        }
        digit = a[max + 1] ? max + 1 : max;
        return *this;
    }
    Int& operator=(Int&& x) noexcept
    {
        if(this != &x)
        {
            if(!a) delete[] a;
            a = x.a;
            x.a = nullptr;
            x.digit = 0;
        }
        return *this;
    }
    Int& operator=(int x)
    {
        if(!a) a = new int[size]{0,x};
        else
        {
            clear();
            a[0] = 0;
            a[1] = x;
        }
        return *this;
    }
    void swap(Int& x)
    {
        int* tmp = x.a;
        x.a = a;
        a = tmp;
        int d = x.digit;
        x.digit = digit;
        digit = d;
    }
    ~Int()
    {
        delete[] a;
    }
};

Int operator+(const Int& a,const Int& b)
{
    Int x;
    x += a;
    x += b;
    return x;
}

std::ostream& operator<<(std::ostream& os,const Int& x)
{
    int it = x.digit;
    while(it >= 1) os << x.a[it--];
    return os;
}

int main()
{
    int m,n;
    std::cin >> m >> n;
    int dis = n - m + 1;
    Int a(1);
    Int b(0);
    Int c;
    for(int i = 1; i <= dis;++i)
    {
        c += a;
        c += b;
        c.swap(b);
        c.swap(a);
        c.clear();
    }
    std::cout << b;

    return 0;
}

#endif