


#include"lz77.h"

#include<tuple>
#include"string_buffer.h"
#include<vector>
#include<array>

// 考虑到字符串哈希找字串 以下大量定义 都是与字符串哈希的预设值有关
// 使用constexpr 完成编译期内计算 提高效率

constexpr static uint64 prime{ 521ull };
constexpr static uint64 table_size{ window_length + 1ull };
constexpr static uint64 null{ -1ull };

constexpr static char nullch{ 3 };

auto constexpr static make_table()  // 快速查幂 编译期求值
{
    std::array<uint64,table_size> table;
    table[0] = 1;
    for(uint64 i{ 1 }; i != table_size; ++i)
    {
        table[i] = table[i - 1] * prime;
    }
    return table;
}

constexpr static auto table{ make_table() };


auto lz_compress(const std::string_view file,const std::string_view output) -> bool
{

    std::ifstream is{ file.data(),std::ios::binary };
    if(!is)
    {
        std::cerr << "can not open the file witch path is " << file.data() << std::endl;
        std::cerr << "press enter for continuing...";
        std::cin.ignore();
        std::cin.get();
        return false;
    }
    std::string window; // window 滑动窗口
    std::vector<uint64> window_hash(window_length + 1ull);

    std::string buffer; // 待压缩缓冲区

    tuple tuple;    // 三元组 三个整形 具体定义 见 utility.h

    std::ofstream os{ output.data(),std::ios::binary };

    char c;
    uint64 i{ 1 };  // 这里提前先块读入一部分数据  并不是把全部外存读入！！
    for(; i <= buffer_length and is.get(c); ++i)
    {
        buffer += c;
    }

    // 以下三个函数 是类内lambda
    // make_hash 预处理窗口的哈希值  O(n)
    // get_hash 传入两个参数表示一个子串 快速计算这个字串的哈希值 O(1) 需要先预处理的信息
    // find 返回下标 在 window 中  模式匹配buffer中指定前n个长度的子串

    auto make_hash{ [&window_hash,&window]()
                    {
                        window_hash[0] = 0;
                        for (uint64 i{ 1 }, cei{ window.size() }; i <= cei; ++i)
                        {
                            window_hash[i] = window_hash[i - 1] * prime + window[i - 1];
                        }
                    }};

    auto get_hash{ [&window_hash](uint64 pos,uint64 count) -> uint64
                   {
                        return window_hash[pos + count] - window_hash[pos] * table[count];
                   }};

    auto find{ [&](uint64 key,uint64 len) -> uint64
               {
                    if(window.size() < len)
                    {
                        return null;
                    }
                    for(uint64 i{},cei{ window.size() - len }; i <= cei; ++i)
                    {
                        if(key == get_hash(i,len))
                        {
                            return i;
                        }
                    }
                    return null;
               }};

    // 开始进行lz77 的大流程 遍历buffer 进行动态匹配
    do
    {
        for(uint64 it{},key{},last_fi,cei{ buffer.size() }; it != cei; ++it)
        {
            key *= prime;   // 匹配时 动态计算buffer前n个字串的 哈希值
            key += buffer[it];
            if(uint64 fi{ find(key,it + 1) }; fi == null or it + 1 == cei) // 如果匹配失败了 亦或者是 匹配满了(即buffer整个是window字串)
            {
                if(it)  //如果不是一上来就匹配失败
                {
                    if(fi == null)  // 如果是匹配失败了 并非匹配满了
                    {
                        tuple = std::make_tuple(last_fi, it, buffer[it]);
                    }
                    else    // 匹配满了
                    {
                        tuple = std::make_tuple(fi,cei,nullch);
                    }
                }
                else    // 如果是一上来就匹配失败
                {
                    tuple = std::make_tuple(0,0,buffer[it]);
                }

                window.append(buffer,0,it + 1); // window 添加字符串
                buffer.erase(0,it + 1); // buffer移除匹配成功的字符串
                for(uint64 _{}; _ <= it and is.get(c); ++_) // 更新buffer的数据
                {
                    buffer.push_back(c);
                }

                os.write(reinterpret_cast<const char*>(&tuple),sizeof(tuple)); // 写入三元组

                if(window.size() > window_length)   // 如果window超出了预设窗口长度 则弹出部分字符串
                {
                    window.erase(0,window.size() - window_length);
                }

                make_hash();    // 重新预处理 window的哈希值 为了O(1)生成任意字串哈希值
                break;
            }
            else    // 否则 即 匹配成功 或者没匹配满
            {
                last_fi = fi;   // 记录上次匹配成功时 window中的起始下标
            }
        }
    }while(is or !buffer.empty());

    return true;
}

/*   lz77的压缩在上面就已经完毕 众所周知lz77主要难在压缩  解压非常容易 故下面算法也很简单           */
/*  故不再给出过多的注释        简而言之就是 反向模拟 读了元组 无脑读出对应串即可                  */


auto lz_depress(const std::string_view file,const std::string_view output) -> bool
{
    std::ifstream is{ file.data(),std::ios::binary };
    if(!is)
    {
        std::cerr << "can not open the file witch path is " << file.data() << std::endl;
        std::cerr << "press enter for continuing...";
        std::cin.ignore();
        std::cin.get();
        return false;
    }
    std::string window;
    tuple tuple;
    //auto [index,len,ch] = tuple;
    std::ofstream os{ output.data(),std::ios::binary };
    while(is.read(reinterpret_cast<char*>(&tuple),sizeof(tuple)))
    {

        auto [index,len,ch] = tuple;

        char c;
        if(!is.get(c) and len and ch == nullch)  // 极小概率出现 最后一个读完 且是正常的应该读入的字符
        {
            os.write(window.data() + index,len);
            break;
        }
        is.unget();

        if(!len)
        {
            window.push_back(ch);
        }
        else
        {
            window += window.substr(index,len);
            os.write(window.data() + index,len);
            window.push_back(ch);
        }

        os.write(reinterpret_cast<const char*>(&ch),sizeof(ch));

        if(window.size() > window_length)
        {
            window.erase(0,window.size() - window_length);
        }
    }
    return true;
}

