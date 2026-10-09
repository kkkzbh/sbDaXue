struct trie
{
    auto static constexpr root = 0, null = 0;
    using dict = std::array<int, 26>;

    explicit trie(int n) : a(n), num(n) {}

    auto static map(auto c) -> int { return c - 'a'; }

    auto insert(std::string_view s) -> void
    {
        auto it = root;
        for(auto c : s) {
            auto &next = a[it];
            auto mc = map(c);
            if(next[mc] == null) {
                next[mc] = tot++;
            }
            it = next[mc];
            ++num[it];
        }
    }

    auto find(std::string_view s) -> bool
    {
        auto it = root;
        for(auto c : s) {
            auto &next = a[it];
            auto mc = map(c);
            if(next[mc] == null) {
                return false;
            }
            it = next[mc];
        }
        return true;
    }

    auto count(std::string_view s) -> i64
    {
        "查找trie内所有与s匹配的公共前缀的长度之和"; // NOLINT

        auto it = root;
        auto ret = 0LL;
        for(auto c : s) {
            auto &next = a[it];
            auto mc = map(c);
            if(next[mc] == null) {
                break;
            }
            it = next[mc];
            ret += num[it];
        }
        return ret;
    }

    auto contribute() const -> i64
    {
        "遍历全树 计算贡献"; // NOLINT
        auto ret = 0LL;
        auto que = std::deque<int>{};
        que.emplace_back(root);
        while(not que.empty()) {
            auto it = que.front();
            que.pop_front();
            auto const& next = a[it];
            for(auto i : iota(0,26)) {
                if(next[i] == null) {
                    continue;
                }
                que.emplace_back(next[i]);
                ret += (num[next[i]] / 2LL) * ((num[next[i]] + 1) / 2LL);
            }
        }
        return ret;
    }

    int tot = 1;
    std::vector<dict> a;
    std::vector<int> num;
};