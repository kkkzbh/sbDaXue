//
// Created by k on 24-6-4.
//

#include "rle.h"


auto rle_compress(const std::string_view file,const std::string_view output) -> bool
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
    std::string buffer;
    char c;
    while(is.get(c))
    {
        buffer.push_back(c);
    }
    std::ofstream os{ output.data(),std::ios::binary };
    for(uint64 l{},r{},cei{ buffer.size() }; r < cei; ++r)
    {
        if(buffer[r] != buffer[l] or (r + 1 == cei and ++r))
        {
            if(r - l == 1)  //如果是 单字符 进行块单字符压缩
            {
                std::string buf;
                buf += buffer[l];
                while(r + 1 < cei and buffer[r] != buffer[r + 1] or r == cei - 1)
                {
                    buf += buffer[r++];
                }
                uint8 len{ static_cast<uint8>((r - l) | tag) }; // 写 1字节
                os.write(reinterpret_cast<const char*>(&len),sizeof(len));
                os.write(buf.data(),static_cast<int64>(buf.size())); // 全部1字节代价写入
                l = r;
            }
            else    // 写 两个字节
            {
                uint8 len{ static_cast<uint8>(r - l)};
                os.write(reinterpret_cast<const char*>(&len),sizeof(len));
                os.write(&buffer[l],sizeof(buffer[l]));
                l = r;
            }
        }
    }
    return true;
}

auto rle_depress(const std::string_view file,const std::string_view output) -> bool
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
    std::ofstream os{ output.data(),std::ios::binary };
    char c;
    while(is.get(c))    // 按压缩解压
    {
        if(c & tag) // 是不等块
        {
            for(uint8 i{ 1 },cei{ static_cast<uint8>(c ^ tag) }; i <= cei; ++i)
            {
                is.get(c);
                os.write(&c,sizeof(c));
            }
        }
        else    // 是等长块
        {
            uint8 cei{ static_cast<uint8>(c) };
            is.get(c);
            for(uint8 i{ 1 }; i <= cei; ++i)
            {
                os.write(&c,sizeof(c));
            }
        }
    }
    return true;
}