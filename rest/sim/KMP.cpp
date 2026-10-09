

#include"../std"

static int* init_next(const std::string& s)
{
    auto sz = s.size();
    auto next = new int[sz];
    next[0] = -1;
    int it = -1;
    int i = 1;
    while(i < sz)
    {
        if(it == -1 || s[i] == s[it])
        {
            next[i++] = ++it;
        }
        else it = next[it];
    }
    return next;
}

auto find_sub_str(const std::string &s,const std::string &sub,int i = 0)
{
    auto next = init_next(sub);
    auto its = s.begin() + i;
    auto sub_it = sub.begin();
    auto sub_size = sub.size();
    const auto end = s.end();
    while(its != end)
    {
        if(sub_it == sub.begin() - 1 || *its == *sub_it)
        {
            ++its;
            ++sub_it;
        }
        else sub_it = sub.begin() + next[sub_it - sub.begin()];
        if(sub_it == sub.end())
        {
            break;
        }
    }
    delete[] next;
    return its - sub_size;
}

int main()
{
    std::ifstream is("../std.in");
    std::string s;
    is >> s;
    auto x = s.begin() - 1;
    auto it = find_sub_str(s,"cao");
    std::cout << static_cast<char>(*it);

    return 0;
}