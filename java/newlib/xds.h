#pragma once

#include<array>

template<typename Val>
struct xds
{
    constexpr static int M_size{ 100 };
    constexpr static int N{ 4 * M_size + 1 };
    std::array<Val,N> M_sum;
    std::array<Val,N> M_lazy;
    int M_n;

    template<typename M_tp,std::size_t M_sz>
    void build(int n,const std::array<M_tp,M_sz>& val) noexcept
    {
        M_n = n;
        M_build(1,n,1,val.data());
    }

    template<typename M_tp>
    void build(int n,const M_tp* val) noexcept
    {
        M_n = n;
        M_build(1,n,1,val);
    }

    [[nodiscard]]
    long long query(int l,int r) noexcept
    {
        return M_query(1,M_n,1,l,r);
    }

    template<typename M_tp>
    void add(int l,int r,M_tp val) noexcept
    {
        M_add(1,M_n,1,l,r,val);
    }

private:

    void up(int i) noexcept
    {
        M_sum[i] = M_sum[i << 1] + M_sum[i << 1 | 1];
    }

    void down(int i,int ln,int rn) noexcept
    {
        if(M_lazy[i])
        {
            lazy(i << 1,ln,M_lazy[i]);
            lazy(i << 1 | 1,rn,M_lazy[i]);
            M_lazy[i] = 0;
        }
    }

    template<typename Int>
    constexpr static Int M_mid(Int min,Int max) noexcept
    {
        return min + ((max - min) >> 1);
    }

    void lazy(int i,int n,int v) noexcept
    {
        M_lazy[i] += v;
        M_sum[i] += n * v;
    }

    template<typename M_tp>
    void M_build(int l,int r,int i,const M_tp* val) noexcept
    {
        if(l == r)
            M_sum[i] = val[l];
        else
        {
            int mid{ M_mid(l,r) };
            M_build(l,mid,i << 1,val);
            M_build(mid + 1,r,i << 1 | 1,val);
            up(i);
        }
        M_lazy[i] = 0;
    }

    [[nodiscard]]
    long long M_query(int l,int r,int i,int jl,int jr) noexcept
    {
        if(jl <= l and r <= jr)
            return M_sum[i];
        int mid{ M_mid(l,r) };
        down(i,mid - l + 1,r - mid);
        long long ret{};
        if(jl <= mid)
            ret += M_query(l,mid,i << 1,jl,jr);
        if(mid < jr)
            ret += M_query(mid + 1,r,i << 1 | 1,jl,jr);
        return ret;
    }

    template<typename M_tp>
    void M_add(int l,int r,int i,int jl,int jr,M_tp val)
    {
        if(jl <= l and r <= jr)
            lazy(i,r - l + 1,val);
        else
        {
            int mid{ M_mid(l,r) };
            down(i,mid - l + 1,r - mid);
            if(jl <= mid)
                M_add(l,mid,i << 1,jl,jr,val);
            if(mid < jr)
                M_add(mid + 1,r,i << 1 | 1,jl,jr,val);
            up(i);
        }
    }
};