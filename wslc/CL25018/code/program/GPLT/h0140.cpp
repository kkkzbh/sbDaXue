

import std;

#ifndef ONLINE_JUDGE
#include <cassert>
#endif

auto leap(auto year) noexcept -> bool
{ return year % 4 == 0 and year % 100 != 0 or year % 400 == 0; }

auto constexpr leap_cnt = std::array{ 365,366 };

auto month(auto mm,auto year) noexcept -> int
{
    auto constexpr month_day = std::array { // 1 3 5 7 8 10 12
          0,31,28,31,30,31,30,31,31,30,31,30,31
    };
    if(mm != 2 or not leap(year)) {
        return month_day[mm];
    }
    return 29;
}

struct drop
{

    [[nodiscard]]
    auto first() const noexcept -> bool
    { return dd == 1; }

    auto operator++() noexcept -> void
    {
        if(++dd != month(mm,yy) + 1) {
            return;
        }
        dd = 1;
        if(++mm != 13) {
            return;
        }
        mm = 1;
        ++yy;
    }

    auto friend operator==(drop const& x,drop const& y) noexcept -> bool = default;

    int yy;
    int mm;
    int dd;
};

auto main() noexcept -> int
{
    int yy,mm,dd;
    while(std::cin >> yy >> mm >> dd) {
        auto days = 0;
        #ifndef ONLINE_JUDGE
        assert(mm >= 1 and mm <= 12 and dd >= 1 and dd <= month(mm,yy));
        #endif
        for(auto const i : std::views::iota(1990,yy)) {
            days += leap_cnt[leap(i)];
        }
        for(auto const i : std::views::iota(1,mm)) {
            days += month(i,yy);
        }
        days += dd; // 一共有几天
        #ifndef ONLINE_JUDGE
        {
            auto l = drop{ 1990,1,1 };
            auto r = drop{ yy,mm,dd };
            ++r;
            auto tot = 0;
            while(l != r) {
                ++tot;
                ++l;
            }
            std::println("days = {} tot = {}",days,tot);
            std::fflush(stdout);
            assert(days == tot);
        }
        #endif
        auto pivot = days;
        auto ck = drop{ 1990,1,1 };

        #ifndef ONLINE_JUDGE
        auto bound = drop{ yy,mm,dd };
        ++bound;
        auto ans = 0;
        auto i = 0;
        while(ck != bound) {
            ans += ck.first() or i % 7 == 0 ? 2 : 1;
            ++ck;
            ++i;
        }
        std::println("{}",ans);
        std::println("-------------------");
        #endif

        for(auto i : std::views::iota(0,pivot)) {
            days += i % 7 == 0 or ck.first();
            ++ck;
        }
        std::println("{}",days);
    }
}