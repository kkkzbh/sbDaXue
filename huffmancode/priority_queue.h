#pragma once

#include"utility.h"
#include"concept.h"

/* ********************* /*

    非本次的核心 这里就是一个通用堆模板
    算法也都是数据结构上讲过的 已经不需要给出注释了

/* ********************* */

template<typename T,typename cmp = decltype([](const T& a,const T& b){ return a < b; })>
        requires comparable<T>
struct priority_queue
{

    priority_queue() = default;

    priority_queue(std::initializer_list<T> il)
    {
        a.reserve(il.end() - il.begin());
        for(const T& it : il)
            a.push_back(it);
        make();
    }

    template<typename M_iterator>
    priority_queue(M_iterator st,M_iterator ed)
    {
        a.reserve(ed - st);
        for(; st != ed; ++st)
            a.push_back(*st);
        make();
    }

    template<typename M_iterator>
    priority_queue(M_iterator st,int n)
    {
        a.reserve(n);
        for(int i{}; i != n; ++i)
            a.push_back(*st++);
        make();
    }

    explicit priority_queue(const std::vector<T>& vec)
    {
        a = vec;
        make();
    }

    explicit priority_queue(std::vector<T>&& vec)
    {
        a = std::move(vec);
        make();
    }

    auto push(const T& val) -> void
    {
        std::size_t it{ a.size() };
        a.resize(it + 1);
        for(; it and cmp{}(a[up(it)],val); it = up(it))
            a[it] = std::move(a[up(it)]);
        a[it] = val;
    }

    auto push(T&& val) -> void
    {
        std::size_t it{ a.size() };
        a.resize(it + 1);
        for(; it and cmp{}(a[up(it)],val); it = up(it))
            a[it] = std::move(a[up(it)]);
        a[it] = std::move(val);
    }

    template<typename... Args>
    auto emplace(Args&&... args) -> void
    {
        std::size_t it{ a.size() };
        a.resize(it + 1);
        T val{ args... };
        for(; it and cmp{}(a[up(it)],val); it = up(it))
            a[it] = std::move(a[up(it)]);
        a[it] = val;
    }

    auto top() -> T&
    {
        return a[0];
    }

    auto pop() -> void
    {
        auto val{ std::move(a.back()) };
        a.pop_back();
        adj_down(0,std::move(val));
    }

    [[nodiscard]]
    auto size() const noexcept -> std::size_t
    {
        return a.size();
    }

    [[nodiscard]]
    auto empty() const noexcept -> bool
    {
        return a.empty();
    }

private:

    std::vector<T> a;

    auto adj_down(std::size_t it,T&& val) -> void
    {
        std::size_t rt{ left(it) };
        std::size_t tp{ a.size() };
        while(rt < tp)
        {
            if(rt != tp - 1 and cmp{}(a[rt],a[rt + 1]))
                ++rt;
            if(cmp{}(a[rt],val))
                break;
            else
            {
                a[it] = std::move(a[rt]);
                it = rt;
                rt = left(it);
            }
        }
        a[it] = std::forward<T>(val);
    }

    auto make() -> void
    {
        std::size_t tp{ a.size() - 1 };
        for(std::size_t it{ up(tp) }; it != -1; --it)
        {
            auto val{ std::move(a[it]) };
            adj_down(it,std::move(val));
        }
    }

};