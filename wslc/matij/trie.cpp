struct trie
{

    auto static map(char c) -> int
    {
        return c - 'a';
    }

    auto insert(std::string_view str) -> void
    {
        auto u = 1;
        ++pass[u];
        for(auto c : str) {
            auto i = map(c);
            if(not a[u][i]) {
                a[u][i] = cnt++;
            }
            u = a[u][i];
            ++pass[u];
        }
        ++end[u];
    }

    [[nodiscard]]
    auto count(std::string_view str) const -> i64
    {
        auto u = 1;
        auto ans = 0ll;
        for(auto c : str) {
            auto i = map(c);
            if(not a[u][i]) {
                return ans;
            }
            u = a[u][i];
            ans += pass[u];
            ans %= MOD;
        }
        return ans;
    }

    auto erase(std::string_view str) -> void
    {
        auto u = 1;
        for(auto c : str) {
            auto i = map(c);
            if(not --pass[a[u][i]]) {
                a[u][i] = 0;
                return;
            }
            u = a[u][i];
        }
        --end[u];
    }


    auto constexpr static first = 1;
    int cnt = first + 1;
    auto constexpr static N = 2500000;
    std::array<std::array<int,26>,N> static inline a{};
    std::array<int,N> static inline end{};
    std::array<int,N> static inline pass{};
};