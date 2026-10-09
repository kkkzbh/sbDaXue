#pragma once


#include<iostream>
#include<array>
#include<algorithm>
#include<vector>

template<typename T,typename M_cmp = decltype([](const T& a,const T& b){ return a < b; })>
struct avl
{
    constexpr static int null{};
    constexpr static int M_size{ 100000 + 2 };

    struct node
    {
        T val{};
        int left{ null };
        int right{ null };
        int sz{ 1 };
        int hei{ 1 };
        int cnt{ 1 };
        node() = default;
        node(const T& v) : val(v){}
    };

    std::array<node,M_size> a;
    int root{ null };
    int M_tp{ 1 };
    std::vector<int> del;

    T& operator[](int index)
    {
        return a[index].val;
    }

    avl()
    {
        a[0].sz = a[0].cnt =  a[0].hei = 0;
    }

    void insert(const T& val)
    {
        M_insert(root,val);
    }

    void erase(const T& val)
    {
        M_erase(root,val);
    }

    void inorder()
    {
        M_inorder(root);
    }

    T find_kth(int k)
    {
        int it{ root };
        while(it != null)
        {
            if(a[a[it].left].sz + a[it].cnt < k)
            {
                k -= a[a[it].left].sz + a[it].cnt;
                it = a[it].right;
            }
            else if(a[a[it].left].sz >= k )
                it = a[it].left;
            else
                return a[it].val;
        }
    }

    int val_kth(const T& val) const
    {
        int rt{ root };
        int ret{};
        while(rt != null)
        {
            if(M_cmp{}(val,a[rt].val))
            {
                rt = a[rt].left;
            }
            else if(M_cmp{}(a[rt].val,val))
            {
                ret += a[a[rt].left].sz + a[rt].cnt;
                rt = a[rt].right;
            }
            else
            {
                ret += a[a[rt].left].sz;
                rt = null;
            }
        }
        return ret + 1;
    }

private:

    void M_inorder(const int it)
    {
        if(it == null)
            return;
        M_inorder(a[it].left);
        std::cout << a[it].val << ' ';
        M_inorder(a[it].right);
    }

    void M_insert(int& it,const T& val)
    {
        if(it == null)
        {
            if(del.empty())
                a[it = M_tp++].val = val;
            else
            {
                a[it = del.back()].val = val;
                del.pop_back();
            }
            return;
        }

        if(a[it].val == val)
        {
            ++a[it].cnt;
            ++a[it].sz;
            return;
        }

        if(M_cmp{}(val,a[it].val))
            M_insert(a[it].left,val);
        else
            M_insert(a[it].right,val);

        int rt{ it };

        rotation(it);

        a[rt].hei = heigh(rt);
        a[rt].sz = size(rt);
    }

    void M_erase(int& it,const T& val)
    {
        if(it == null)
            return;
        if(M_cmp{}(val,a[it].val))
        {
            M_erase(a[it].left,val);
        }
        else if(M_cmp{}(a[it].val,val))
        {
            M_erase(a[it].right,val);
        }
        else
        {
            if(a[it].left != null && a[it].right != null)
            {
                if(a[it].cnt == 1)
                {
                    int rt{a[it].right};
                    while (a[rt].left != null)
                        rt = a[rt].left;
                    std::swap(a[it].val, a[rt].val);
                    std::swap(a[it].cnt, a[rt].cnt);
                    M_erase(a[it].right, val);
                }
                else
                {
                    --a[it].cnt;
                    --a[it].sz;
                    return;
                }
            }
            else if(a[it].left != null)
            {
                if(a[it].cnt == 1)
                {
                    int rt{ a[it].left };
                    del.push_back(it);
                    a[it].left = a[it].right = null;
                    a[it].hei = a[it].sz = 1;
                    it = rt;
                }
                else
                {
                    --a[it].cnt;
                    --a[it].sz;
                }
                return;
            }
            else
            {
                if(a[it].cnt == 1)
                {
                    int rt{ a[it].right };
                    del.push_back(it);
                    a[it].left = a[it].right = null;
                    a[it].hei = a[it].sz = 1;
                    it = rt;
                }
                else
                {
                    --a[it].cnt;
                    --a[it].sz;
                }
                return;
            }
        }

        int rt{ it };

        rotation(it);

        a[rt].hei = heigh(rt);
        a[rt].sz = size(rt);
    }

    void rotation(int& it)
    {
        int bf{ a[a[it].left].hei - a[a[it].right].hei };
        if(bf == -2)    //右
        {
            if(a[a[a[it].right].left].hei <= a[a[a[it].right].right].hei) //右
            {
                leftrotation(it);
            }
            else    //左
            {
                rightrotation(a[it].right);
                a[a[a[it].right].right].hei = heigh(a[a[it].right].right);
                leftrotation(it);
            }
        }
        else if(bf == 2)    //左
        {
            if(a[a[a[it].left].left].hei < a[a[a[it].left].right].hei)  //右
            {
                leftrotation(a[it].left);
                a[a[a[it].left].left].hei = heigh(a[a[it].left].left);
                rightrotation(it);
            }
            else    //左
            {
                rightrotation(it);
            }
        }
    }

    int heigh(int it)
    {
        return std::max(a[a[it].left].hei,a[a[it].right].hei) + 1;
    }

    int size(int it)
    {
        return a[a[it].left].sz + a[a[it].right].sz + a[it].cnt;
    }

    void leftrotation(int& it)  //左旋
    {
        int r{ a[it].right };
        a[it].right = a[r].left;
        a[r].left = it;
        a[it].sz = size(it);
        a[r].sz = size(r);
        it = r;
    }

    void rightrotation(int& it)
    {
        int l{ a[it].left };
        a[it].left = a[l].right;
        a[l].right = it;
        a[it].sz = size(it);
        a[l].sz = size(l);
        it = l;
    }
};