

import std;

using namespace std::views;

template<typename T>
struct ntree
{

    ntree(std::span<T> in,std::span<T> back) noexcept
    : n{ static_cast<int>(in.size()) },l1{},l2{},in{ in },back{ back }
    {
        auto const& val = back[n - 1];
        lazy = std::distance(in.begin(),std::ranges::find(in,val));
    }

    [[nodiscard]]
    auto root() const noexcept -> int // using for back
    { return l2 + n - 1; }

    [[nodiscard]]
    auto has_left() const noexcept -> bool
    { return lazy != l1; }

    [[nodiscard]]
    auto left() const noexcept -> ntree
    {
        auto ret = ntree {
            lazy - l1,l1,l2,
            static_cast<int>(std::distance(in.begin(),std::find(in.begin() + l1,in.begin() + lazy,back[l2 + lazy - l1 - 1]))),
            in,back
        };
        return ret;
    }

    [[nodiscard]]
    auto has_right() const noexcept -> bool
    { return lazy != l1 + n - 1; }

    [[nodiscard]]
    auto right() const noexcept -> ntree
    {
        auto ret = ntree {
            n - lazy + l1 - 1,lazy + 1,l2 + lazy - l1,
            static_cast<int>(std::distance(in.begin(),std::find(in.begin() + lazy + 1,in.begin() + n + l1,back[l2 + n - 2]))),
            in,back,
        };
        return ret;
    }

    int n;
    int l1,l2; // l1 为 in  l2 为 back
    int lazy;
    std::span<T> in,back;

private:

    ntree(int n,int l1,int l2,int lazy,std::span<T> in,std::span<T> back) noexcept
    : n{ n },l1{ l1 },l2{ l2 },lazy{ lazy },in{ in },back{ back } {}

};

template<typename T>
ntree(std::span<T>,std::span<T>) -> ntree<T>;

auto main() noexcept -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    auto in = std::vector(n,0),back = in;
    #define scan(X) \
        std::ranges::for_each(X,[](auto& val){ std::cin >> val; });
    scan(in);
    scan(back);
    auto root = ntree{ std::span(in),std::span(back) };

    auto que = std::queue<decltype(root)>{};

    que.push(root);
    std::cout << "R: ";
    while(not que.empty()) {
        for(auto bound = static_cast<int>(que.size()); auto i : iota(0,bound)) {
            auto it = que.front();
            que.pop();
            if(i + 1 == bound) {
                std::cout << back[it.root()] << ' ';
            }
            if(it.has_left()) {
                que.push(it.left());
            }
            if(it.has_right()) {
                que.push(it.right());
            }
        }
    }
    std::cout << '\n';
    que.push(root);
    std::cout << "L: ";
    while(not que.empty()) {
        for(auto bound = static_cast<int>(que.size()); auto i : iota(0,bound)) {
            auto it = que.front();
            que.pop();
            if(i == 0) {
                std::cout << back[it.root()] << ' ';
            }
            if(it.has_left()) {
                que.push(it.left());
            }
            if(it.has_right()) {
                que.push(it.right());
            }
        }
    }


}