

#include<cstdio>


template<typename T>
struct stack
{
    constexpr static std::size_t M_BUFFER_SIZE = 200000;
    using size_type = std::size_t;
    using value = T;
    T buffer[M_BUFFER_SIZE];
    size_type Top = 0;

    void push(const T& val){ buffer[Top++] = val;}
    void pop(){ --Top;}
    T& top(){ return buffer[Top - 1]; }
    bool empty(){ return !Top;}
    size_type size(){ return Top; }
    void clear(){ Top = 0; }
};

struct buffer
{
    constexpr static std::size_t max_size = 200000;
    char buffer[max_size]{};
    char* start = buffer;
    char* end = start;

    int gc()
    {
        if(start == end)
            end = (start = buffer) + fread(buffer,1,max_size,stdin);
        return *start++;
    }
    void mf(){ ++start; }
    void mb(){ --start; }
    int c(){ return *start; }
    int last(){ return *(start - 2); }
};
buffer buf;
inline int gc(){ return buf.gc(); }
inline int last(){ return buf.last(); }
inline void mb(){ buf.mb(); }

int hash(int c)
{
    switch(c)
    {
        case '(': return 0;
        case '+':
        case '-': return 1;break;
        case '*':
        case '/': return 2; break;
        default: return 10; break;
    }
}

int isdigit(int c){ return c >= '0' && c <= '9'; }

bool isnum(int c)
{
    return isdigit(c) || c == '.' || (c == '+' || c == '-') && ( (buf.start - buf.buffer < 0 ) || (!isdigit(last())) && last() != ')');
}

bool flag = 1;

int main()
{
    stack<char> stk;
    char c;
    while((c = static_cast<char>(gc())) != '\n')
    {
        if(c == '(') stk.push(c);
        else if(isnum(c))
        {
            if(flag) flag = false; else printf(" ");
            if(c != '+') printf("%c",c);
            while(isnum((c = gc()))) printf("%c",c);
            mb();
        }
        else if(c == ')')
        {
            while(stk.top() != '(')
            {
                if(flag) flag = false; else printf(" ");
                printf("%c",stk.top());
                stk.pop();
            }
            stk.pop();
        }
        else if(hash(c) < hash(stk.top()))
        {
            while(!stk.empty() && hash(stk.top()) >= hash(c))
            {
                if(flag) flag = false; else printf(" ");
                printf("%c",stk.top());
                stk.pop();
            }
            stk.push(c);
        }
        else stk.push(c);
    }
    while(!stk.empty())
    {
        if(flag) flag = false; else printf(" ");
        printf("%c",stk.top());
        stk.pop();
    }

    return 0;
}
