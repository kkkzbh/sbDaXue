



#include<iostream>

struct buffer
{
    constexpr static int size = 200 + 2;
    char buf[size];
    char* st,*ed;
    buffer() : st(buf),ed(st + fread(buf,1,size,stdin)){}
}buf;
char gc()
{
    if(buf.st == buf.ed) return 0;
    return *buf.st++;
}

template<typename T>
struct stack
{
    constexpr static int SIZE = 200 + 2;
    T val[SIZE];
    std::size_t tp = 0;

    void push(const T& v){ val[tp++] = v; }
    void pop(){ --tp; }
    T& top(){ return val[tp - 1]; }
    bool empty(){ return !tp; }
    std::size_t size(){ return tp; }
};

template<typename T>
struct vector
{
    using iterator = T*;
    T* buf = new T;
    T* ed = buf;
    T* cap = buf + 1;

    void ra(std::size_t sz)
    {
        T* tmp = new T[sz];
        T* it = tmp;
        cap = tmp + sz;
        for(T* i = buf; i != ed;++i) *it++ = std::move(*i);
        ed = it;
        buf = tmp;
    }
    void push_back(const T& v)
    {
        if(ed == cap) ra((cap - buf) << 1);
        *ed++ = v;
    }
    T* begin(){ return buf; }
    T* end(){ return ed; }
};

bool isleft(int c)
{
    return c == '(' || c == '[';
}

bool isright(int c)
{
    return c == ')' || c == ']';
}

bool isok(int c,int cb)
{
    return c == ')' && cb == '(' || c == ']' && cb == '[';
}

#if 0

前面的做法没有什么问题
后面的输出 很坏的情况下为n苹方 但有sz优化 以及提前匹配break 有了一定的优化
不过还可以进一步优化 我是懒的改了
额外开一个数组(空间换时间) 存储的信息为 是否匹配成功 这样就不用去遇到一个 '('或'[' 通过搜索 判断其是否是匹配成功的

#endif

int main()
{
    stack<char> stk;
    vector<char> vec;
    char c;
    while(c = gc()) // n
    {
        if(isleft(c)) stk.push(c),vec.push_back(c);
        else if(isright(c))
        {
            if(stk.empty() || !isok(c,stk.top()))
            {
                if(c == ')') vec.push_back('('),vec.push_back(')');
                else vec.push_back('['),vec.push_back(']');
            }
            else vec.push_back(c),stk.pop();
        }
    }
    auto it = vec.begin();
    auto sz = stk.size();
    while(it != vec.end())   // n -> n*n
    {
        bool flag = true;
        if(isright(*it)) std::cout << *it++;
        else
        {
            if (sz) //根据栈的大小 得知有几个没匹配上的 那么搜索判断当前左扩是否是匹配上的
            {
                int cnt{1};
                if (*it == '(')
                {
                    for (auto i = it + 1; i != vec.end(); ++i)
                    {
                        if (*i == '(') ++cnt;
                        else if (*i == ')') --cnt;
                        if(!cnt) break;
                    }
                }
                else
                {
                    for (auto i = it + 1; i != vec.end(); ++i)
                    {
                        if (*i == '[') ++cnt;
                        else if (*i == ']') --cnt;
                        if(!cnt) break;
                    }
                }
                if (cnt) flag = false,--cnt;
            }
            if (flag) std::cout << *it++;
            else
            {
                if (*it == '(') std::cout << "()";
                else std::cout << "[]";
                ++it;
            }
        }
    }

    return 0;
}