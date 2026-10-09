

#include<vector>
#include<string>
#include<string_view>

constexpr static std::size_t M_prime{ 521ull };
constexpr static std::vector<std::size_t> Make_table(std::size_t sz = 1000002)
{
    std::vector<std::size_t> vec(sz);
    vec[0] = 1;
    for(std::size_t i{ 1 }; i <= sz; ++i)
    {
        vec[i] = vec[i - 1] * M_prime;
    }
    return vec;
}
const std::vector<std::size_t> M_table = Make_table();

static std::vector<std::size_t> M_HashStr(const std::string_view str)
{
    std::vector<std::size_t> hash(str.size() + 1);
    for(std::size_t i{ 1 },cei{ str.size() }; i <= cei; ++i)
    {
        hash[i] = hash[i - 1] * M_prime + str[i - 1];
    }
    return hash;
}

static std::vector<std::size_t> M_hash;
static std::size_t hash(std::size_t pos,std::size_t count)
{
    return M_hash[pos + count] - M_hash[pos] * M_table[count];
}

std::size_t hash(const std::string_view str)
{
    std::size_t ret{};
    for(int i{}; i != str.size();++i)
    {
        ret *= M_prime;
        ret += str[i];
    }
    return ret;
}

std::size_t find(const std::string_view str,const std::string_view sub,std::size_t i = 0)
{
    if(str.size() < sub.size())
        return std::string::npos;
    static std::string_view::const_pointer M_pointer{};
    if(M_pointer != str.data())
    {
        M_hash = M_HashStr(str);
        M_pointer = str.data();
    }
    std::size_t cei{ str.size() - sub.size()};
    auto val = hash(sub);
    while(i <= cei && val != hash(i,sub.size()))
        ++i;
    if(cei < i)
        return std::string::npos;
    return i;
}