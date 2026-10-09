


#include<iostream>
#include<array>
#include<string>

constexpr int size = 1e3 + 10;
const std::string ans[]{"NO\n","YES\n"};

template<typename T>
class stack
{
public:
    using size_type = std::size_t;
private:
    T* array = nullptr;
    T* tp = nullptr;
    T* sz = nullptr;
public:
    explicit stack(size_type n) : array(new T[n]()) , tp(array) , sz(array + n){}
    void push(const T& ele) { *tp++ = ele;}
    void pop() { --tp;}
    T& top() { return *(tp - 1);}
    bool empty() { return tp == array;}
    bool full() { return tp == sz;}
    void clear() { tp = array;}
};

int main()
{
    std::ios::sync_with_stdio(false),std::cout.tie(nullptr),std::cin.tie(nullptr);
    int n,m,k;
    std::cin >> n >> m >> k;
    std::array<int,size> a{};
    stack<int> stk(m);
    for(int i = 1; i <= k;++i)
    {
        for(int j = 1; j <= n;++j) std::cin >> a[j];
        for(int j = 1,v = 1; j <= n;)
        {
            if (j == a[v]) ++j,++v;
            else if (!stk.empty() && stk.top() == j) stk.pop(),++j;
            else if (!stk.full() && v <= n) stk.push(a[v++]);
            else break;
        }
        std::cout << ans[stk.empty()];
        stk.clear();
    }


    return 0;
}
