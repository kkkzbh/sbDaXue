

struct fenwick
{

    using value_type = int;
    using Container = std::vector<std::vector<value_type>>;

    auto row() const noexcept -> int
    { return d1.size(); }

    auto cow() const noexcept -> int
    { return d1[0].size(); }

    fenwick(std::integral auto n,std::integral auto m) :
        d1(n + 1,std::vector<value_type>(m + 1,0)),
        d2(n + 1,std::vector<value_type>(m + 1,0)),
        d3(n + 1,std::vector<value_type>(m + 1,0)),
        d4(n + 1,std::vector<value_type>(m + 1,0)) {}

    auto add(int x,int y,auto val) noexcept -> void
    {
        ++x,++y;
        auto v1 = value_type{ val };
        auto v2 = v1 * x;
        auto v3 = v1 * y;
        auto v4 = v1 * x * y;
        for(auto i = x; i < row(); i += i & -i) {
            for(auto j = y; j < cow(); j += j & -j) {
                d1[i][j] += v1;
                d2[i][j] += v2;
                d3[i][j] += v3;
                d4[i][j] += v4;
            }
        }
    }

    auto add(int x1,int y1,int x2,int y2,auto val) noexcept -> void
    {
        add(x1,y1,val);
        add(x1,y2 + 1,-val);
        add(x2 + 1,y1,-val);
        add(x2 + 1,y2 + 1,val);
    }

    auto sum(int x,int y) const noexcept -> value_type
    {
        ++x,++y;
        auto v1 = std::int64_t{};
        auto v2 = std::int64_t{};
        auto v3 = std::int64_t{};
        auto v4 = std::int64_t{};
        for(auto i = x; i; i -= i & -i) {
            for(auto j = y; j; j -= j & -j) {
                v1 += d1[i][j];
                v2 += d2[i][j];
                v3 += d3[i][j];
                v4 += d4[i][j];
            }
        }
        ++x,++y;
        return v1 * x * y - v2 * y - v3 * x + v4;
    }

    auto sum(int x1,int y1,int x2,int y2) const -> value_type
    { return sum(x2,y2) - sum(x2,y1 - 1) - sum(x1 - 1,y2) + sum(x1 - 1,y1 - 1); }

    Container d1,d2,d3,d4;
    /*
     *  (n + 1)(m + 1)
     *  (n + 1)    *j
     *  (m + 1)    *i
     *  *i         *j
     */
};