

#include<iostream>
#include<string>
#include<stack>
#include<utility>

constexpr int size = 1000;

int tree[size];

inline int left(int i)
{
    return 2 * i;
}

inline int right(int i)
{
    return 2 * i + 1;
}

inline int up(int i)
{
    return i / 2;
}

void dfs(int it)
{
    static int flag = 1;
    if(!tree[it]) return;
    dfs(left(it));
    dfs(right(it));
    if(flag) flag = 0; else std::cout << ' ';
    std::cout << tree[it];
}

int main()
{
    int n;
    std::cin >> n;
    std::stack<std::pair<int,int>> stk;
    std::string s;
    int it = 1;
    while(n || !stk.empty())
    {
        std::cin >> s;
        if(s[1] == 'u')
        {
            int x;
            std::cin >> x;
            stk.emplace(x,it);
            it = left(it);
        }
        else
        {
            it = stk.top().second;
            tree[it] = stk.top().first;
            stk.pop();
            --n;
            it = right(it);
        }
    }
    dfs(1);

    return 0;
}