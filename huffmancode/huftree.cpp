

#include"huftree.h"

huftree::huftree(const std::array<uint64,ch_size>& feq) //接受一个词频表构造huftree
{

#ifdef OPTIMISE  // 这里其实是想获取总字符个数 sum_index 应该是某个用不到的下标的空间的利用

    sum = feq[sum_index];   // 但其实这是个失败的设计,毕竟谁也不能一帆风顺是吗 为了不改其他代码 让代码能跑起来 故未删

#endif

    std::vector<std::pair<uint64,std::size_t>> vec; // 先存储二元组 uint64 = weigh权重  std::size_t = 在哈夫曼树中的下标
#ifndef OPTIMISE
    for(int i{}; i != ch_size; ++i)
    {
        if(feq[i])
        {
            vec.emplace_back(feq[i],a.size());
            a.emplace_back(feq[i], static_cast<unsigned char>(i));
        }
    }
#else
    for(int i{}; i != ch_size - 1; ++i)
    {
        if(feq[i])
        {
            vec.emplace_back(feq[i],a.size());
            a.emplace_back(feq[i], static_cast<unsigned char>(i));
        }
    }
#endif
    // 使用刚才的vec O(n)建堆 即数据结构上的筛选法 这里把上面的std::vector 利用 std::move 移动到堆中
    priority_queue<decltype(vec)::value_type,decltype([](auto p1,auto p2)
    {
        return p1.first > p2.first;
    })> que{ std::move(vec) };   //建立堆
    while(que.size() != 1) //常规构造算法
    {
        auto p1 = que.top();
        que.pop();
        auto p2 = que.top();
        que.pop();
        que.emplace(p1.first + p2.first,a.size());
        a[p1.second].up = a[p2.second].up = a.size();
        a.emplace_back(p1.first + p2.first,0,null,p1.second,p2.second);
    }
    /*     至此 一棵哈夫曼树 就构造好啦        */

}

huftree& huftree::operator=(huftree&& huf) noexcept
{
    a = std::move(huf.a);
    return *this;
}

#ifdef O2

auto huftree::get_iterator() -> iterator
{
    return iterator{ a.size() - 1,a };
}

#endif


hufcode::hufcode(const huftree& tree) // 接受一个哈夫曼树 构造信息
{
    if(!tree.a.empty()) // 由于内部是 不空则调用 则这里需要一次判空 至于空了做什么 待定... 也可以什么也不做
    {
        std::string s;
        create(tree.a.size() - 1,s,tree.a);
    }
}

hufcode::hufcode(std::ifstream& ifs)
{
    read(map,ifs);
}

auto hufcode::create(uint64 it,std::string& s,const std::vector<huftree::hufnode>& vec) -> void
{
    if(vec[it].left == null and vec[it].right == null)
    {                                       // 如果是叶节点 开始存储信息
        map.insert(std::make_pair(a[vec[it].ch] = s,vec[it].ch));
    }
    else    // 否则
    {
        if(auto l{ vec[it].left }; l != null) // 如果有左 进入左
        {
            s.push_back('0');   // 追加路径
            create(l,s,vec);
            s.pop_back();   // 回溯----
        }
        if(auto r{ vec[it].right }; r != null)
        {
            s.push_back('1');
            create(r,s,vec);
            s.pop_back();
        }
    }
}

auto hufcode::operator[](unsigned char c) -> std::string&
{
    return a[c];
}

auto hufcode::operator[](const std::string& s) -> char
{
    return map[s];
}

auto hufcode::operator[](std::string&& s) -> char
{
    return map[std::move(s)];
}




