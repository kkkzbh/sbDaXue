

//#define L_1_10
#ifdef L_1_10

#include<iostream>
#include<iomanip>
#include<map>
#include<set>
#include<cmath>
struct node
{
    int e;
    int p;
    node() = default;
    node(int E,int P) : e(E),p(P){}
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int head;
    int n;
    std::cin >> head >> n;
    int d,p,i;
    std::map<int,node> map;
    while(n--)
    {
        std::cin >> d >> i >> p;
        map.insert(std::make_pair(d,node(i,p)));
    }
    p = head;
    int tp = -1;
    std::map<int,node> del;
    int dp = -1;
    std::set<int> set;
    int ep = -1;
    while(p != -1)
    {
        node& tmp = map[p];
        if(set.find(std::abs(tmp.e)) != set.end())
        {
            if(dp == -1)
            {
                dp = p;
                ep = p;
                del[dp] = tmp;
            }
            else
            {
                del[ep].p = p;
                node& t = del[p];
                t = tmp;
                ep = p;
                t.p = -1;
            }
            auto ite = map.find((p));
            map[tp].p = map[p].p;
            map.erase(ite);
        }
        else
        {
            set.insert(std::abs(tmp.e));
        }
        tp = p;
        p = tmp.p;
    }
    p = head;
    while(p != -1)
    {
        node& tmp = map[p];
        std::cout << std::setw(5) << std::setfill('0') << p << ' ' << tmp.e << ' ';
        if(tmp.p != -1)
            std::cout <<std::setw(5) << std::setfill('0');
        std::cout << tmp.p << '\n';
        p = tmp.p;
    }
    while(dp != -1)
    {
        node& tmp = del[dp];
        std::cout << std::setw(5) << std::setfill('0') << dp << ' ' << tmp.e << ' ';
        if(tmp.p != -1)
            std::cout << std::setw(5) << std::setfill('0');
        std::cout << tmp.p << '\n';
        dp = tmp.p;
    }
    return 0;
}

#endif

#ifdef A

#include<iostream>
#include<iomanip>
#include<cmath>
constexpr int size = 1e5 + 10;

struct node
{
    int e;
    int p;
}G[size];

int h[size];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int head;
    int n;
    std::cin >> head >> n;
    node tmp;
    for(int i = 1,a; i <= n;++i)
    {
        std::cin >> a >> tmp.e >> tmp.p;
        G[a] = tmp;
    }
    int p = head;
    int lastp = -1;
    int fdp = -1;
    int edp = -1;
    while(p != -1)
    {
        if(h[std::abs(G[p].e)])
        {
            if(fdp == -1)
            {
                fdp = edp = p;
                G[lastp].p = G[p].p;
                G[edp].p = -1;
            }
            else
            {
                G[lastp].p = G[p].p;
                G[edp].p = p;
                edp = p;
                G[edp].p = -1;
            }
            p = G[lastp].p;
        }
        else
        {
            h[std::abs(G[p].e)] = 1;
            lastp = p;
            p = G[p].p;
        }
    }
    p = head;
    while(p != -1)
    {
        std::cout << std::setw(5) << std::setfill('0') << p << ' ' << G[p].e << ' ';
        if(G[p].p != -1)
            std::cout << std::setw(5) << std::setfill('0');
        std::cout << G[p].p << '\n';
        p = G[p].p;
    }
    edp = fdp;
    while(edp != -1)
    {
        std::cout << std::setw(5) << std::setfill('0') << edp << ' ' << G[edp].e << ' ';
        if(G[edp].p != -1)
            std::cout << std::setw(5) << std::setfill('0');
        std::cout << G[edp].p << '\n';
        edp = G[edp].p;
    }

    return 0;
}

#endif