
#include"utility.h"
#include<cstring>

auto to_int(uint64 i,const std::string& data) -> int
{
    int c{};
    uint64 sz{ data.size() - i };
    for(uint64 _{}; _ < 32ull and _ < sz; ++_)
    {
        c <<= 1;
        c |= (data[i++] ^ 48);
    }
    if(sz < 32ull)
    {
        c <<= 32 - static_cast<int>(sz);
    }
    return c;
}

auto to_int(uint64 i,const char* data) -> int
{
    int c{};
    uint64 sz{ strlen(data) };
    for(uint64 _{}; _ < 32ull and _ < sz; ++_)
    {
        c <<= 1;
        c |= (data[i++] ^ 48);
    }
    if(sz < 32ull)
    {
        c <<= 32 - static_cast<int>(sz);
    }
    return c;
}
