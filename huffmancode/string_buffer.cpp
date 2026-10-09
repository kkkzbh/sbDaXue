



#include "string_buffer.h"

auto string_buffer::operator+=(const char* str) noexcept -> string_buffer&
{
    push(str);
    return *this;
}

auto string_buffer::operator+=(const char c) noexcept -> string_buffer&
{
    push(c);
    return *this;
}

string_buffer::operator bool () const
{
    return !empty();
}

auto string_buffer::push(const char* str) noexcept -> void
{
    while((s[r] = *str++))
    {
        ++r;
        ++sz;
        r %= buffer_size;
    }
}

auto string_buffer::push(const char c) noexcept -> void
{
    s[r++] = c;
    ++sz;
    r %= buffer_size;
}

auto string_buffer::ignore() -> void  // the define is base in the realize of compress
{
    l = (l + 1) % buffer_size;
    --sz;
}

auto string_buffer::pop() -> void
{
    ignore();
}

auto string_buffer::move(uint64 dis) -> void
{
    l = (l + dis) % buffer_size;
    sz -= dis;
}

auto string_buffer::get() -> char
{
    char ret{ s[l] };
    ignore();
    return ret;
}

auto string_buffer::make() -> std::string
{
    std::string ret;
    for(uint64 beg{ l },end{ r }; beg != end; beg = (beg + 1) % buffer_size)
    {
        ret.push_back(s[beg]);
    }
    return ret;
}

auto string_buffer::to_int() -> int
{
    int c{};
    uint64 sz{ size() };
    for(uint64 _{}; _ < 32ull and _ < sz; ++_)
    {
        c <<= 1;
        c |= (get() ^ 48);
    }
    if(sz < 32ull)
    {
        c <<= 32 - static_cast<int>(sz);
    }
    return c;
}

[[nodiscard]]
auto string_buffer::size() const -> uint64
{
    return sz;
}

[[nodiscard]]
auto string_buffer::empty() const noexcept -> bool
{
    return l == r;
}

auto string_buffer::begin() -> iterator
{
    return { s + l,s };
}

auto string_buffer::end() -> iterator
{
    return { s + r,s };
}