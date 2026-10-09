

//#define S1_1_4
#ifdef S1_1_4

#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<stack>

int main()
{
    std::string s;
    std::string ans;
    std::cin >> s >> ans;
    std::vector<std::pair<int,int>> a;
    std::stack<char> stk;
    auto s1 = s.begin();
    auto e1 = s.end();
    auto s2 = ans.begin();
    auto e2 = ans.end();
    while(s2 != e2)
    {
        if(s1!= e1 && *s2 == *s1)
        {
            a.emplace_back(1,2);
            ++s2;
            ++s1;
        }
        else if(stk.empty() && s1 != e1)
        {
            stk.push(*s1++);
            a.emplace_back(1,3);
        }
        else if(stk.top() == *s2)
        {
            stk.pop();
            ++s2;
            a.emplace_back(3,2);
        }
        else if(s1 != e1)
        {
            stk.push(*s1++);
            a.emplace_back(1,3);
        }
        else break;
    }
    if(s2 != e2)
    {
        std::cout << "Are you kidding me?";
    }
    else
    {
        for(auto it : a)
        {
            std::cout << it.first << "->" << it.second << '\n';
        }
    }

    return 0;
}


#endif