

template<std::integral T>
fun constexpr lg2(T n) noexcept -> int
{
    int log{};
    if constexpr(sizeof(T) >= 8)
    { if (n >= T{ 1 } << 32) { n >>= 32; log += 32; } }
    if constexpr(sizeof(T) >= 4)
    { if (n >= T{ 1 } << 16) { n >>= 16; log += 16; } }
    if constexpr(sizeof(T) >= 2)
    { if (n >= T{ 1 } << 8) { n >>= 8; log += 8; } }
    if (n >= T{ 1 } << 4) { n >>= 4; log += 4; }
    if (n >= T{ 1 } << 2) { n >>= 2; log += 2; }
    if (n >= T{ 1 } << 1) { log += 1; }
    return log;
}