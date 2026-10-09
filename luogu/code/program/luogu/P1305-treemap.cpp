

#include<iostream>
#include<format>
#include<unordered_map>
#include<utility>
#include<stack>

template<typename... Args>
void print(const std::string_view fmt_str,Args&&... args)
{
    fputs(std::vformat(fmt_str,std::make_format_args(args...).c_str(),stdout));
}

void print(char c)
{
    fputc(c,stdout);
}

std::unordered_map<char,std::pair<char,char>> map;

void preorder(char root)
{
    std::stack<char> stk;
    stk.push(root);
    print(root);
    char it = stk.top();
    while(!stk.empty())
    {
        auto tmp = map[it];
        while(tmp.first != '*')
        {
            it = tmp.first;
            stk.push(it);
            print(it);
            tmp = map[it];
        }
        while(!stk.empty() && tmp.second == '*')
        {
            stk.pop();
            if(!stk.empty())
            {
                it = stk.top();
                tmp = map[it];
            }
        }
        if(!stk.empty()) 
        {
            stk.pop();
            it = tmp.second;
            stk.push(it);
            print(it);
        }
    }

}

int main()
{
    freopen("../in.in","r",stdin);
    freopen("../out.out","w",stdout);
    int n;
    std::cin >> n;
    char root;
    for(int _{}; _ != n;++_)
    {
        char a,b,c;
        std::cin >> a >> b >> c;
        if(!_) root = a;
        map.emplace(a,std::make_pair(b,c));
    }
    preorder(root);

    
    return 0;
}