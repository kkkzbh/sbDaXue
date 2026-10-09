


#ifndef DEFLATE_H
#define DEFLATE_H

/* ********************* /*

    deflate
    基于lz77 + 哈夫曼树实现 在这里用到了lz解压压缩的接口 详见 lz77.h和.cpp
    deflate_tree的定义 基本是抄写了一遍huftree的流程 故不在给出过多注释
    deflate_compress 和 deflate_compress 也是基本基于lz77 和 哈夫曼结合 不在给出过多注释
    不过需要提出的一点是
    如果在utility.h中定义O2  会启用O2版本
    ---->  用更少的结点压缩信息 利用树 解码 而不是map解码
    但 亲测打不过非O2 应该？ 忘了

/* ********************* */


#include"utility.h"
#include"lz77.h"
#include"fun.h"
#include"map.h"
#include<tuple>
#include"statistics.h"

constexpr static char default_buf_path[]{ R"(buff)" };
constexpr static char default_buf2_path[]{ R"(buff2)" };

struct deflate_tree
{

private:

#ifndef O2

    struct deflate_node
    {

        auto friend operator<=>(const deflate_node& n1,const deflate_node& n2) -> std::partial_ordering
        {
            return n1.weigh <=> n2.weigh;
        }

        auto friend operator==(const deflate_node& n1,const deflate_node& n2) -> bool
        {
            return n1.weigh == n2.weigh;
        }

        uint64 weigh;
        std::tuple<uint16,uint16,char> tuple;
        std::size_t up{ null };
        std::size_t left{ null };
        std::size_t right{ null };
    };

#else

    struct deflate_node
    {

        auto friend operator<=>(const deflate_node& n1,const deflate_node& n2) -> std::partial_ordering
        {
            return n1.weigh <=> n2.weigh;
        }

        auto friend operator==(const deflate_node& n1,const deflate_node& n2) -> bool
        {
            return n1.weigh == n2.weigh;
        }

        uint weigh;
        std::tuple<uint16,uint16,char> tuple;
        uint up{ null };
        uint left{ null };
        uint right{ null };
    };


#endif

#ifdef O2

    struct deflate_iterator
    {

        auto friend operator==(const deflate_iterator& i1,const deflate_iterator& i2) -> bool
        {
            return i1.it == i2.it;
        }

        deflate_iterator() = default;

        deflate_iterator(uint64 it,const std::vector<deflate_node>& vec) : it(it),vec(&vec){}

        [[nodiscard]]
        auto leaf() const noexcept -> bool
        {
            return (*vec)[it].left == null;
        }

        auto operator++() -> void  // if it is a leaf, the behavior is undefined.
        {
            it = (*vec)[it].left;
        }

        auto operator++(int) -> void
        {
            it = (*vec)[it].right;
        }

        auto reset() -> void // if the iterator is construct by defalut constructor, the behavior is undefined.
        {
            it = (*vec).size() - 1;
        }

        auto get() -> tuple      // if the iteraotr is not a leaf, the behavior is undefined.
        {
            return (*vec)[it].tuple;
        }

    private:

        uint64 it{ null };
        const std::vector<deflate_node>* vec;

    };


#endif

public:

    friend struct deflate_code;

#ifndef O2
    constexpr static std::size_t null{ static_cast<std::size_t>(-1) };
#else
    constexpr static uint null{ static_cast<uint>(-1) };
    using iterator = deflate_iterator;

    template<typename Tree>
    requires contain_a<Tree>
    auto friend write(const Tree& tree,std::ofstream& ofs) -> void;

    template<typename Tree>
    requires contain_a<Tree>
    auto friend read(Tree& tree,std::ifstream& ifs) -> void;

    auto get_iterator() -> iterator;

#endif

    deflate_tree() = default;

    explicit deflate_tree(map<tuple,uint>&& map);

private:

    std::vector<deflate_node> a;

};

struct deflate_code
{

    auto friend deflate_compress(const std::string_view file,const std::string_view output) -> bool;

    auto friend deflate_depress(const std::string_view file,const std::string_view output) -> bool;

    constexpr static auto null{ deflate_tree::null };

    deflate_code() = default; // default constructor which not be defined.

    explicit deflate_code(const deflate_tree& tree);

    explicit deflate_code(std::ifstream& ifs);

    auto operator[](const tuple tuple) -> std::string&;

    auto operator[](const std::string& s) -> tuple;

    auto operator[](std::string&& s) -> tuple;

private:

    auto create(uint64 it,std::string& s,const std::vector<deflate_tree::deflate_node>& vec) -> void;

    map<tuple,std::string> a;   // give the tuple,get the code which be used to compress file
    map<std::string,tuple> map; // give the code,get the tuple which be used to decompress file

};


auto deflate_compress(const std::string_view file,const std::string_view output = "../out.nt") -> bool;

auto deflate_depress(const std::string_view file,const std::string_view output = "../de.znt") -> bool;


#endif
