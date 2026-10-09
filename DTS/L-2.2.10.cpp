


#include<iostream>

constexpr char ans[][5]{"NO\n","YES\n"};
constexpr int size = 1000 + 10;

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
    int m,n,k;
    std::cin >> m >> n >> k;
    stack<int> stk(m);
    int a[size]{};
    for(int j = 1; j <= k;++j)
    {
        for(int i{1}; i <= n;++i) std::cin >> a[i];
        for(int i{1},v{1}; v <= n;)
        {
            if(!stk.empty() && stk.top() == a[v]) ++v,stk.pop();
            else if(!stk.full() && i <= n) stk.push(i++);
            else break;
        }
        std::cout << ans[stk.empty()];
        stk.clear();
    }

    return 0;
}