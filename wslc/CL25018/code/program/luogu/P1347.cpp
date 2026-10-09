


#include<iostream>
#include<array>
#include<queue>
#include<bitset>

#define ci(A) ((A) ^ 64)

constexpr int L_size{ 26 };
constexpr int M_size{ L_size + 2 };
constexpr int null{ -1 };
constexpr int S_size{ 600 + 2 };

int n,m;
std::array<int,M_size> a;
std::array<int,S_size> to;
std::array<int,S_size> next;
int top;
std::array<int,M_size> id;
std::array<int,M_size> od;
std::bitset<M_size> vis;
std::array<char,M_size> ans;
int tp;

auto Pre_ = []() -> int
{
    a.fill(null);
    return 0;
}();

void push(int src,int dst)
{
    to[top] = dst;
    next[top] = a[src];
    a[src] = top++;
}

int tps(int count)
{
    std::queue<int> que;
    bool full{};
    for(int i{ 1 }; i <= n; ++i)
        if(!id[i] && od[i])
        {
            que.push(i);
            ans[tp++] = i - 1 + 'A';
        }
    std::array<int,M_size> i = id;
    int cnt{};
    while(!que.empty())
    {
        if(que.size() > 1)
            full = true;
        int v = que.front();
        que.pop();
        ++cnt;
        for(int it{ a[v] }; it != null; it = next[it])
            if(!--i[to[it]])
            {
                que.push(to[it]);
                ans[tp++] = to[it] - 1 + 'A';
            }
    }
    if(cnt != count)
        return -1;
    else if(!full && cnt == n)
        return 1;
    return 0;
}

int main()
{
    scanf("%d %d",&n,&m);
    int i{ 1 };
    for(int cnt{}; i <= m; ++i)
    {
        char x,y;
        scanf(" %c<%c",&x,&y);
        int cx = ci(x);
        int cy = ci(y);
        if(!vis[cx])
        {
            vis.set(cx);
            ++cnt;
        }
        if(!vis[cy])
        {
            vis.set(cy);
            ++cnt;
        }
        ++id[cy];
        ++od[cx];
        push(cx,cy);
        if(int sec = tps(cnt); sec == 1)
        {
            printf("Sorted sequence determined after %d relations: %s.", i, ans.data());
            break;
        }
        else if(sec == -1)
        {
            printf("Inconsistency found after %d relations.",i);
            break;
        }
        tp = 0;
    }
    if(i > m)
    {
        printf("Sorted sequence cannot be determined.");
    }

    return 0;
}