

#include<iostream>
#include<array>
#include<algorithm>
#include<utility>

constexpr int M_size{ 1000 + 2 };
constexpr int N{ 4 * M_size };

struct node
{
    int x1,y1;
    int x2,y2;
};

struct side
{
    int x1,x2;
    int y;
    bool tag;   //false = in   true = out
};

std::array<node,M_size> a;
std::array<std::array<int,N>,N> diff;
std::array<int,N> dis;
int t{ 1 };
std::array<side,2 * N> sd;
int sdt{ 1 };

std::pair<int,int> get(std::pair<int,int> p)
{
    p.first = std::lower_bound(dis.begin() + 1,dis.begin() + t,p.first) - dis.begin();
    p.second = std::lower_bound(dis.begin() + 1,dis.begin() + t,p.second) - dis.begin();
    return p;
}

int distance(int y,int cei)
{
    int l{ 1 },r{ 1 };
    int ret{};
    while(r <= cei)
    {
        while (l <= cei and !diff[l][y])
            ++l;
        r = l;
        while(r <= cei and diff[r][y])
            ++r;
        ret += dis[r - 1] - dis[l];
        l = r;
    }
    return ret;
}

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    int n;
    std::cin >> n;
    for(int i{ 1 }; i <= n; ++i)
    {
        std::cin >> a[i].y1 >> a[i].x2 >> a[i].y2 >> a[i].x1;
        dis[t++] = a[i].x1;
        dis[t++] = a[i].y1;
        dis[t++] = a[i].x2;
        dis[t++] = a[i].y2;
        sd[sdt++] = { a[i].x1,a[i].x2,a[i].y1,false };
        sd[sdt++] = { a[i].x1,a[i].x2,a[i].y2,true };
    }
    std::sort(dis.begin() + 1,dis.begin() + t);
    std::sort(sd.begin() + 1,sd.begin() + sdt,[](const side& a,const side& b) -> bool
    {
        if(a.y != b.y)
            return a.y < b.y;
        return (a.x2 - a.x1) - (b.x2 - b.x1);
    });
    t = std::unique(dis.begin() + 1,dis.begin() + t) - dis.begin();
    for(int i{ 1 }; i <= n; ++i)
    {
        std::pair<int,int> st{ get(std::make_pair(a[i].x1,a[i].y1)) };
        std::pair<int,int> ed{ get(std::make_pair(a[i].x2,a[i].y2)) };
        diff[st.first][st.second] += 1;
        diff[st.first][ed.second + 1] -= 1;
        diff[ed.first + 1][st.second] -= 1;
        diff[ed.first + 1][ed.second + 1] += 1;
    }
    for(int i{ 1 },cei{ n << 2 }; i <= cei; ++i)
        for(int j{ 1 }; j <= cei; ++j)
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];

    for(int i{ 1 },cei{ n << 2 }; i <= cei; ++i)
    {
        for (int j{ 1 }; j <= cei; ++j)
            std::cout << diff[i][j] << ' ';
        std::cout << '\n';
    }

    long long ans{};
    for(int i{ 1 },cei{ n << 1 },pos{},width{}; i <= cei; ++i)
    {
        if(sd[i].y != pos)
        {
            ans += (dis[sd[i].y] - dis[pos]) * width;
            if(sd[i].tag)
                width = distance(sd[i].y + 1,cei << 1);
            else
                width = distance(sd[i].y,cei << 1);
            pos = sd[i].y;
        }
    }
    std::cout << ans;

    return 0;
}