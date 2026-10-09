#pragma once

#include"utility.h"
#include"priority_queue.h"
#include"map.h"
#include"hufio.h"

/* ************************************ /*

    该文件主要含两大类 huftree 和 hufcode
    huftree
    哈夫曼树 需要一个词频表得以构造 词频表值的是 给定一个字符'a'  table['a'] 能够返回其频率
    内部使用的堆算法构造哈夫曼树  关于堆 详见 priority_queue.h 没有.cpp 因为是模板
    hufcode
    哈夫曼编码 存储两个映射 一个是 'a' -> 001100  一个是 001100 -> 'a'
    这两个映射共同基于 dfs + 回溯算法 对哈夫曼树遍历的实现 具体可详见.cpp中的create函数

    还需要提出的是 这个.h中存在一个O2宏的选择性编译
    算是一个优化版本 不过这个优化版本最终没有在哈夫曼解压 压缩中 体现 而是后来写到了 defalte.h和.cpp中体现
    这里可以选择性的看一下

/* ************************************ */

struct huftree
{

private:

#ifndef O2  // 未定义O2前的 内部结点定义 定义O2后 就是存哈夫曼树而不是map了 所以 这个未优化的hufnode 占的空间很奢侈

    struct hufnode  //聚合类
    {
        auto friend operator<(const huftree::hufnode& n1,const huftree::hufnode& n2) -> bool  //重载 <
        {
            return n1.weigh < n2.weigh;
        }

        uint64 weigh;  //权值     基本8个字节
        unsigned char ch{};    // 字符
        std::size_t up{ null };  //指向父节点    基本8个字节 奢侈
        std::size_t left{ null };   //指向左右孩子结点
        std::size_t right{ null };
    };

#else   // 考虑开O2 存哈夫曼树 故对变量进行了一些压缩

    struct hufnode  //聚合类
    {
        auto friend operator<(const huftree::hufnode& n1,const huftree::hufnode& n2) -> bool  //重载 <
        {
            return n1.weigh < n2.weigh;
        }

        uint weigh;  //权值
        unsigned char ch{};    // 字符
        uint up{ null };  //指向父节点
        uint left{ null };   //指向左右孩子结点
        uint right{ null };
    };

#endif

#ifdef O2       // 哈夫曼树迭代器 只有把哈夫曼树当成解码器时才会用到  故这里定义O2才会编译这个迭代器的定义

    struct huf_iterator
    {

        auto friend operator==(const huf_iterator& i1,const huf_iterator& i2) -> bool
        {
            return i1.it == i2.it;
        }

        huf_iterator() = default;

        huf_iterator(uint64 it,const std::vector<hufnode>& vec) : it(it),vec(&vec){}

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

        auto get() -> uint8      // if the iteraotr is not a leaf, the behavior is undefined.
        {
            return (*vec)[it].ch;
        }

    private:

        uint64 it{ null };
        const std::vector<hufnode>* vec;

    };

#endif

public:

    friend struct hufcode;

#ifndef O2
    constexpr static std::size_t null{ static_cast<std::size_t>(-1) };    //定义 空
#else   // 由于O2版 多出了对哈夫曼树的存储 所以多出了下方的一些定义

    constexpr static uint null{ static_cast<uint>(-1) };
    using iterator = huf_iterator;

    template<typename Tree>
    requires contain_a<Tree>
    auto friend write(const Tree& tree,std::ofstream& ofs) -> void;

    template<typename Tree>
    requires contain_a<Tree>
    auto friend read(Tree& tree,std::ifstream& ifs) -> void;

#endif


    huftree() = default;

    huftree(huftree&& huf) = default;

    /*   这是该树最关键的构造函数 .cpp中可见实现          */
    explicit huftree(const std::array<uint64,ch_size>& feq); //接受一个词频表构造huftree

    auto operator=(huftree&& huf) noexcept -> huftree&;

#ifdef O2

    auto get_iterator() -> iterator;

#endif

#ifdef OPTIMISE

    [[nodiscard]]
    auto get_sum() const -> uint64 { return sum; }

#endif

private:

    std::vector<hufnode> a; //哈夫曼树底层存储数据的容器

#ifdef OPTIMISE

    uint64 sum; // 存有数据总数

#endif

};


// 该类很直观 值得注意的就是其接受哈夫曼树的构造函数 和 create函数

struct hufcode
{

    friend auto compress(const std::string_view file,const std::string_view output) -> bool;

    friend auto depress(const std::string_view file,const std::string_view output) -> bool;

    constexpr static auto null{ huftree::null };

    hufcode() = default;

    hufcode(const hufcode& hufcode) = default;

    hufcode(hufcode&& hufcode) = default;

    explicit hufcode(const huftree& tree); // 接受一个哈夫曼树 构造信息

    explicit hufcode(std::ifstream& ifs);   //接受一个输入流 构造信息 但此时只能用于解压！ 这个是解压时使用的构造函数

    auto operator[](unsigned char c) -> std::string&;

    auto operator[](const std::string& s) -> char;

    auto operator[](std::string&& s) -> char;


private:

    // 此函数是构造两个映射的核心 .cpp中可见具体实现
    auto create(uint64 it,std::string& s,const std::vector<huftree::hufnode>& vec) -> void;

    std::array<std::string,ch_size> a;    //存储每个字符的01序列 压缩使用
    map<std::string,char> map;  //存储01序列 对应的字符 解压使用

};
