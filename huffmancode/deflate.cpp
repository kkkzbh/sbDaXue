


#include"deflate.h"

#include"string_buffer.h"
#include"hufio.h"

deflate_tree::deflate_tree(map<tuple,uint>&& map)
{

    std::vector<std::pair<uint64,uint64>> vec;  // 1.uint64 is weight   2.uint64 is the index of a
    for(const auto& it : map)
    {
        vec.emplace_back(it.second,a.size());
        a.emplace_back(it.second,it.first);
    }
    priority_queue<decltype(vec)::value_type,decltype([](const auto p1,const auto p2)
    {
        return p1.first > p2.first;       // the min heap of weight
    })> que{ std::move(vec) };

    while(que.size() != 1)  // create the deflate_tree
    {
        auto p1{ que.top() };
        que.pop();
        auto p2{ que.top() };
        que.pop();
        que.emplace(p1.first + p2.first,a.size());
        a[p1.second].up = a[p2.second].up = a.size();
        a.emplace_back(p1.first + p2.first,tuple{},null,p1.second,p2.second);
    }

}

#ifdef O2

auto deflate_tree::get_iterator() -> iterator
{
    return iterator{ a.size() - 1,a };
}

#endif

deflate_code::deflate_code(const deflate_tree& tree)
{
    if(!tree.a.empty())
    {
        std::string s;
        create(tree.a.size() - 1,s,tree.a);
    }
}

deflate_code::deflate_code(std::ifstream& ifs)
{
    read(map,ifs);
}

auto deflate_code::create(uint64 it,std::string& s,const std::vector<deflate_tree::deflate_node>& vec) -> void
{

    if(vec[it].left == null and vec[it].right == null)
    {                                       // 如果是叶节点 开始存储信息
        a.insert(std::make_pair(vec[it].tuple,s));
        map.insert(std::make_pair(s,vec[it].tuple));
    }
    else
    {
        if(auto l{ vec[it].left }; l != null)
        {
            s.push_back('0');
            create(l,s,vec);
            s.pop_back();
        }
        if(auto r{ vec[it].right }; r != null)
        {
            s.push_back('1');
            create(r,s,vec);
            s.pop_back();
        }
    }

}

auto deflate_code::operator[](const tuple tuple) -> std::string&
{
    return a[tuple];
}

auto deflate_code::operator[](const std::string &s) -> tuple
{
    return map[s];
}

auto deflate_code::operator[](std::string &&s) -> tuple
{
    return map[std::move(s)];
}


constexpr static uint64 byte{ 8 };
constexpr static uint64 buf_sz{ byte * sizeof(int) };

auto deflate_compress(const std::string_view file,const std::string_view output) -> bool
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
    is.close();

    lz_compress(file,default_buf_path);

    deflate_tree tree{tuple_frequency(default_buf_path) };

    deflate_code code{ tree };

    is.open(default_buf_path,std::ios::binary);

    std::ofstream os{ default_buf2_path,std::ios::binary };

    string_buffer buf;

    tuple tuple;
    uint cnt{};
    while(is.read(reinterpret_cast<char*>(&tuple),sizeof(tuple)))
    {
        buf += code[tuple].data();
        if(buf.size() >= buf_sz)
        {
            int put{ buf.to_int() };
            os.write(reinterpret_cast<const char*>(&put),sizeof(put));
            ++cnt;
        }
    }

    is.close();
    os.close();

    is.open(default_buf2_path,std::ios::binary);
    os.open(output.data(),std::ios::binary);

#ifndef O2

    write(code.map,os); // this is a huge consume. must change it !!!!

#else

    write(tree,os);

#endif

    os.write(reinterpret_cast<const char*>(&cnt),sizeof(cnt));

    uint get;
    while(is.read(reinterpret_cast<char*>(&get),sizeof(get)))
    {
        os.write(reinterpret_cast<const char*>(&get),sizeof(get));
    }

    if(!buf.empty())
    {
        std::string ed{ buf.make() };
        os.write(ed.data(),static_cast<int64>(ed.size()));
        //char c = buf.get();
        //os.write(&c,sizeof(c));
    }
    return true;
}

auto deflate_depress(const std::string_view file,const std::string_view output) -> bool
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

#ifndef O2

    deflate_code code{ is };

    uint cnt{};
    is.read(reinterpret_cast<char*>(&cnt),sizeof(cnt));

    std::ofstream os{ default_buf2_path,std::ios::binary };

    string_buffer buf;

    while(cnt--)
    {
        uint get;
        is.read(reinterpret_cast<char*>(&get),sizeof(get));
        buf += std::bitset<buf_sz>{ get }.to_string().data();
        std::string b;
        uint64 key{};
        for(const auto it : buf)
        {
            key *= prime;
            key += it;
            b += it;
            auto i{ code.map.find(key,b) };
            if(i != code.map.end())
            {
                os.write(reinterpret_cast<const char*>(&i->second),sizeof(i->second));  // 写 tuple
                buf.move(b.size());
                b.clear();
                key = 0;
            }
        }
    }

    char c;
    while(is.read(&c,sizeof(c)))
    {
        buf.push(c);
    }

    std::string b;
    uint64 key{};
    for(const auto it : buf)
    {
        key *= prime;
        key += it;
        b += it;
        auto i{ code.map.find(key,b) };
        if(i != code.map.end())
        {
            os.write(reinterpret_cast<const char*>(&i->second),sizeof(i->second)); // 写 tuple
            buf.move(b.size());
            b.clear();
            key = 0;
        }
    }

    os.close();

#else

    deflate_tree tree;
    read(tree,is);
    auto it{ tree.get_iterator() };

    uint cnt{};
    is.read(reinterpret_cast<char*>(&cnt),sizeof(cnt));

    std::ofstream os{ default_buf2_path,std::ios::binary };

    string_buffer buf;

    while(cnt--)
    {
        uint get;
        is.read(reinterpret_cast<char*>(&get),sizeof(get));
        buf += std::bitset<buf_sz>{ get }.to_string().data();
        uint offset{};
        for(const auto ch : buf)
        {
            if(ch == '0')
            {
                ++it;
            }
            else
            {
                it++;
            }
            ++offset;
            if(it.leaf())
            {
                tuple tuple{ it.get() } ;
                os.write(reinterpret_cast<const char*>(&tuple),sizeof(tuple));
                buf.move(offset);
                offset = 0;
                it.reset();
            }
        }
    }

    char c;
    while(is.read(reinterpret_cast<char*>(&c),sizeof(c)))
    {
        buf += c;
    }
    it.reset();
    uint offset{};
    for(const auto ch : buf)
    {
        if(ch == '0')
        {
            ++it;
        }
        else
        {
            it++;
        }
        ++offset;
        if(it.leaf())
        {
            tuple tuple{ it.get() } ;
            os.write(reinterpret_cast<const char*>(&tuple),sizeof(tuple));
            buf.move(offset);
            offset = 0;
            it.reset();
        }
    }

    os.close();

#endif

    lz_depress(default_buf2_path,output);

    return true;
}