


#include<iostream>
#include<string>

std::string s;
size_t it;
std::string ans;
size_t level;

#define TAB   \
    for(int i{}; i != level;++i)  \
        ans += "  ";

#define IG   \
    while(it != s.size() && s[it] == ' ') ++it;

#define WOFUL   \
    (s.substr(it,2) == "if" || s.substr(it,4) == "else" ||   \
    s.substr(it,5) == "while" || s.substr(it,3) == "for")

#define IF (s.substr(it,2) == "if")
#define ELSE (s.substr(it,4) == "else")
#define WHILE (s.substr(it,5) == "while")
#define FOR (s.substr(it,3) == "for")

void solve();
void For();
void M();
void While();
void IE();

void block()
{
    ans.push_back('\n');
    TAB
    ans.push_back(s[it++]);
    ans.push_back('\n');
    ++level;
    IG
    TAB
    while(it != s.size())
    {
        if(s[it] == '}')
            break;
        solve();
    }
    --level;
    ans.pop_back();
    ans.pop_back();
    ans.push_back(s[it++]);
    IG
    TAB
}

void M()
{
    while(s[it] != ')')
        ans.push_back(s[it++]);
    ans.push_back(s[it++]);
    IG
    if(s[it] == '{')
    {
        ans += " {\n";
        ++it;
        ++level;
        IG
        TAB
        while(it != s.size())
        {
            if(s[it] == '}')
                break;
            solve();
        }
        --level;
        ans.pop_back();
        ans.pop_back();
        ans.push_back(s[it++]);
        ans.push_back('\n');
        TAB
    }
    else
    {
        ans += " {\n";
        ++level;
        TAB
        if(WOFUL)
        {
            For();
            s.pop_back();
            s.pop_back();
            s.push_back('}');
            s.push_back('\n');
            --level;
            TAB
        }
        else
        {
            while(s[it] != ';')
                ans.push_back(s[it++]);
            ans.push_back(s[it++]);
            IG
            ans.push_back('\n');
            --level;
            TAB
            ans.push_back('}');
            ans.push_back('\n');
            TAB
        }
    }
}

void For()
{
    ans += "for ";
    it += 3;
    IG
    M();
}

void While()
{
    ans += "while ";
    it += 5;
    IG
    M();
}

void IE()
{
    ans += "if ";
    it += 2;
    IG
    M();
    ans += "else";
    it += 4;
    IG
    if(s[it] == '{')
    {
        ans += " {\n";
        ++it;
        ++level;
        IG
        TAB
        while(it != s.size())
        {
            if(s[it] == '}')
                break;
            solve();
        }
        ans.push_back('\n');
        --level;
        TAB
        ans.push_back(s[it++]);
        ans.push_back('\n');
        TAB
    }
        ans += " {\n";
        ++level;
        TAB
        if(IF)
        {
            IE();
            ans.pop_back();
            ans.pop_back();
            ans.push_back('}');
            ans.push_back('\n');
            --level;
            TAB
        }
        else if(WHILE)
        {
            While();
            ans.pop_back();
            ans.pop_back();
            ans.push_back('}');
            ans.push_back('\n');
            --level;
            TAB
        }
        else if(FOR)
        {
            For();
            ans.pop_back();
            ans.pop_back();
            ans.push_back('}');
            ans.push_back('\n');
            --level;
            TAB
        }
        else
        {
            while(s[it] != ';')
                ans.push_back(s[it++]);
            ans.push_back(s[it++]);
            IG
            ans.push_back('\n');
            --level;
            TAB
            ans.push_back('}');
            ans.push_back('\n');
            TAB
        }
}

void solve()
{
    if(s[it] == '{')
    {
        block();
    }
    else if(s[it] == ';')
    {
        ans.push_back(s[it++]);
        IG
        ans.push_back('\n');
        TAB
    }
    else if(IF)
    {
        IE();
    }
    else if(FOR)
    {
        For();
    }
    else if(WHILE)
    {
        While();
    }
    else
    {
        ans.push_back(s[it++]);
    }
}

int main()
{
    freopen("../in.in","r",stdin);
    freopen("../out.out","w",stdout);
    std::getline(std::cin,s);
    IG
    while(s[it] != ')')
        ans.push_back(s[it++]);
    ans.push_back(s[it++]);
    IG
    while(it != s.size())
        solve();
    std::cout << ans;


    return 0;
}