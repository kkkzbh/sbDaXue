


#include<iostream>

inline void print(int n,char c)
{
    for(int i = 1; i <= n;++i) std::cout << c;
}

inline void print()
{
    std::cout << "--";
}

inline void ent()
{
    std::cout << '\n';
}

inline void print(int n)
{
    for(int i = 1; i <= n;++i) std::cout << "o*";
}

void print(int n,int cnt)
{
    if(n != 4)
    {
        print(n,'o');
        print(n,'*');
        print();
        print(cnt);
        ent();
        ++cnt;
        print(n - 1,'o');
        print();
        print(n - 1,'*');
        print(cnt);
        ent();
        print(n - 1,cnt);
    }
    else
    {
        print(4,'o');
        print(4,'*');
        print();
        print(cnt);
        ent();
        std::cout << "ooo--***o*";
        print(cnt);
        ent();
        std::cout << "ooo*o**--*";
        print(cnt);
        ent();
        std::cout << "o--*o**oo*";
        print(cnt);
        ent();
        std::cout << "o*o*o*--o*";
        print(cnt);
        ent();
        std::cout << "--o*o*o*o*";
        print(cnt);
    }
}

int main()
{
    std::ios::sync_with_stdio(false),std::cout.tie(nullptr),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    print(n,0);

    return 0;
}
