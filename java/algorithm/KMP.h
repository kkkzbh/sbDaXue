#pragma once

#include<string>
#include<vector>

static std::vector<std::string::size_type> __next_array(const std::string& str) noexcept
{
    std::vector<std::string::size_type> next(str.size() >= 2ull ? str.size() + 1 : 3ull);
    next[0] = -1;
    next[1] = 0;
    std::string::size_type i = 2,pos = 0;
    while(i <= str.size())
    {
        if(str[i - 1] == str[pos])
            next[i++] = ++pos;
        else if(pos)
            pos = next[pos];
        else
            next[i++] = 0;
    }
    return next;
}

static std::vector<std::string::size_type> M_Next;
std::string::size_type find(const std::string& str,const std::string& substr,std::string::size_type i = 0)
{
    static const std::string* _pointer{};
    if(_pointer != &substr)
    {
        M_Next = __next_array(substr);
        _pointer = &substr;
    }
    std::string::size_type pos{};
    while(i < str.size() && pos != substr.size())
    {
        if(str[i] == substr[pos])
            ++i,++pos;
        else if(pos)
            pos = M_Next[pos];
        else
            ++i;
    }
    if(pos == substr.size())
        return i - pos;
    return std::string::npos;
}

void clear_next() { M_Next.clear(); }
auto& get_next() { return M_Next; }
