#pragma once



/* ***************************** /*

    这里主要是 向文件 写入map 写入哈夫曼树 时需要用到的 是类友元的函数
    不过具体实现细节不在过多注释 基本就是搬砖工作 不难从函数中读出实现方法
    堆区内存向文件写入 就是如此麻烦

/* ***************************** */
#include"utility.h"
#include"map.h"
#include"huftree.h"
#include"deflate.h"

template<typename stkmem>
auto write(const map<std::string,stkmem>& map,std::ofstream& ofs) -> void
{
    auto sz{ map.vec.size() };
    ofs.write(reinterpret_cast<const char*>(&sz),sizeof(sz));
    ofs.write(reinterpret_cast<const char*>(&map.cnt),sizeof(map.cnt));
    ofs.write(reinterpret_cast<const char*>(&map.sz),sizeof(map.sz));
    //ofs << sz << map.cnt << map.sz;
    for(const auto& v : map.vec)
    {
        sz = v.size();
        ofs.write(reinterpret_cast<const char*>(&sz),sizeof(sz));
        //ofs << sz;
        for(const auto& [str,m] : v)
        {
            sz = str.size();
            ofs.write(reinterpret_cast<const char*>(&sz),sizeof(sz));
            ofs.write(str.data(),static_cast<int64>(str.size()));
            ofs.write(reinterpret_cast<const char*>(&m),sizeof(m));
        }
    }
}

template<typename stkmem>
auto read(map<std::string,stkmem>& map,std::ifstream& ifs) -> void
{
    std::size_t sz;
    ifs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
    ifs.read(reinterpret_cast<char*>(&map.cnt),sizeof(map.cnt));
    ifs.read(reinterpret_cast<char*>(&map.sz),sizeof(map.sz));
    map.vec.resize(sz);
    for(auto& v : map.vec)
    {
        ifs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        v.resize(sz);
        for(auto& [str,m] : v)
        {
            ifs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
            str.resize(sz);
            ifs.read(str.data(),static_cast<int64>(sz));
            ifs.read(reinterpret_cast<char*>(&m),sizeof(m));
        }
    }
}

#ifdef O2

template<typename Tree>
requires contain_a<Tree>
auto write(const Tree& tree,std::ofstream& ofs) -> void
{
    uint sz{ static_cast<uint>(tree.a.size() )};
    ofs.write(reinterpret_cast<const char*>(&sz),sizeof(sz));
    for(const auto& it : tree.a)
    {
        ofs.write(reinterpret_cast<const char*>(&it),sizeof(it));
    }
}

template<typename Tree>
requires contain_a<Tree>
auto read(Tree& tree,std::ifstream& ifs) -> void
{
    uint sz;
    ifs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
    tree.a.resize(sz);
    for(auto& it : tree.a)
    {
        ifs.read(reinterpret_cast<char*>(&it),sizeof(it));
    }
}

//auto write(const huftree& tree,std::ofstream& ofs) -> void = delete;
//
//auto read(huftree& tree,std::ifstream& ifs) -> void = delete;
//
//auto write(const deflate_tree& tree,std::ofstream& ofs) -> void = delete;
//
//auto read(deflate_tree& tree,std::ifstream& ifs) -> void = delete;

#endif