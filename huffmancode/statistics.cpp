

#include"statistics.h"


auto word_frequency(const std::string_view path) -> std::array<uint64,ch_size>
{
    std::ifstream ifs{ path.data(), std::ios::binary };    //打开文件
    if(!ifs)
    {
        throw std::invalid_argument{ std::string{} + "can not open the file with path : " + path.data() };
    }
    char c;
    std::array<uint64,ch_size> a{};
#ifdef OPTIMISE

    uint64 sum{};
#endif

    while(ifs.get(c))
    {
        ++a[static_cast<uint8>(c)]; //统计词频
#ifdef OPTIMISE
        ++sum;  // 统计总个数
#endif
    }

#ifdef OPTIMISE

    a[sum_index] = sum; //  存有总数

#endif

    return a;   //析构自动关闭文件...
}

auto tuple_frequency(const std::string_view path) -> map<tuple,uint>
{

    std::ifstream ifs{ path.data(), std::ios::binary };    //打开文件
    if(!ifs)
    {
        throw std::invalid_argument{ std::string{} + "can not open the file with path : " + path.data() };
    }

    map<tuple,uint> map;

    tuple tuple;
    while(ifs.read(reinterpret_cast<char*>(&tuple),sizeof(tuple)))
    {
        auto it{ map.find(tuple) };
        if(it != map.end())
        {
            ++it->second;
        }
        else
        {
            map.insert(std::make_pair(tuple,1));
        }
    }

    return map;

}