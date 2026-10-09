

#include<iostream>
#include<array>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>

#define ctoi(C) (C ^ 96)

constexpr int M_size{ 1000 + 2 };
constexpr int L_size{ 26 + 2 };
constexpr int L_len{ 26 };

std::array<std::vector<std::pair<int,std::string>>,L_size> a;
std::array<int,L_size> id;
int n;

int cnt;
std::string ans;
bool flag;
void dfs(int it)
{
    if(cnt == n)
    {
        flag = true;
        return;
    }
    for(auto&& i : a[it])
    {
        if(i.first > 0)
        {
            ans.append(i.second);
            ans.push_back('.');
            i.first = -i.first;
            ++cnt;
            dfs(-i.first);
            if(flag)
                return;
            else
            {
                i.first = -i.first;
                ans.pop_back();
                ans.erase(ans.size() - i.second.size());
                --cnt;
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(0),std::cin.tie(0);
    std::cin >> n;
    for(int i{ 1 }; i <= n; ++i)
    {
        std::string s;
        std::cin >> s;
        ++id[ctoi(s.back())];
        a[ctoi(s.front())].emplace_back(ctoi(s.back()),std::move(s));
    }
    for(int i{ 1 }; i <= L_len; ++i)
        std::sort(a[i].begin(),a[i].end(),
                  [i](const auto& p1,const auto& p2) -> bool
                  {
                      return p1.second < p2.second;
                  });
    int st{},ed{};
    bool tag{};
    for(int i{ 1 }; i <= L_len; ++i)
    {
        if(id[i] - a[i].size() == -1)
        {
            if(st)
            {
                tag = true;
                break;
            }
            st = i;
        }
        else if(id[i] - a[i].size() == 1)
        {
            if(ed)
            {
                tag = true;
                break;
            }
            ed = i;
        }
        else if(id[i] != a[i].size())
        {
            tag = true;
            break;
        }
    }
    if(!tag)
    {
        if(st)
            dfs(st);
        else
            for(int i{ 1 }; i <= L_len; ++i)
            {
                if(!a[i].empty())
                {
                    dfs(i);
                    break;
                }
            }
    }
    if(ans.empty())
        std::cout << "***";
    else
    {
        ans.pop_back();
        std::cout << ans;
    }

    return 0;
}