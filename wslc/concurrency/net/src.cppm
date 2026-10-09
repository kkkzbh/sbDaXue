module;

#include <bit>

export module net;

export auto constexpr ton(auto v)
{
    using enum std::endian;
    if constexpr(native == little) {
        v = std::byteswap(v);
    }
    return v;
}