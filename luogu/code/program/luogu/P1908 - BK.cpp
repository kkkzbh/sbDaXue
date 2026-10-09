


#include<iostream>
#include<algorithm>
#include<vector>
#include<array>

using int64 = long long;
using uint64 = unsigned long long;

template<typename T>
struct avl
{

    constexpr static int null{};

    struct node
    {
        T val;
        int sz{ 1 };
        int cnt{ 1 };
        int height{ 1 };
        int left{ null };
        int right{ null };
    };

    /*
     * std::array<node,500000 + 2> a;
     * int M_tp{ 1 };
     * avl(){ a[0].sz = a[0].cnt = a[0].height = 0; }
     */

    std::vector<node> a{ {T{},0,0,0} };
    int root{ null };

    void insert(const T& v)
    {
        if(a.size() == a.capacity())
            a.reserve(2 * a.size());
        M_insert(root,v);
    }

    int kth(const T& val) const
    {
        int rt{ root };
        int ret{};
        while(rt != null)
        {
            if(a[rt].val < val)
            {
                rt = a[rt].left;
            }
            else if(val < a[rt].val)
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
        return ret;
    }

private:

    void M_insert(int& it,const T& v)
    {
        if(it == null)
        {
            /*
             *  a[it = M_tp++].val = v;
             */

            it = a.size();
            a.push_back({ v });
            return;
        }
        if(a[it].val == v)
        {
            ++a[it].sz;
            ++a[it].cnt;
            return;
        }
        if(a[it].val < v)
            M_insert(a[it].left,v);
        else
            M_insert(a[it].right,v);

        int rt{ it };

        rotation(it);

        a[rt].height = height(rt);
        a[rt].sz = size(rt);
    }

    void rotation(int& it)
    {
        int bf{ a[a[it].left].height - a[a[it].right].height };
        if(bf == -2)    //右
        {
            if(a[a[a[it].right].left].height <= a[a[a[it].right].right].height) //右
            {
                leftrotation(it);
            }
            else    //左
            {
                rightrotation(a[it].right);
                a[a[a[it].right].right].height = height(a[a[it].right].right);
                leftrotation(it);
            }
        }
        else if(bf == 2)    //左
        {
            if(a[a[a[it].left].left].height < a[a[a[it].left].right].height)  //右
            {
                leftrotation(a[it].left);
                a[a[a[it].left].left].height = height(a[a[it].left].left);
                rightrotation(it);
            }
            else    //左
            {
                rightrotation(it);
            }
        }
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

    int height(int it)
    {
        return std::max(a[a[it].left].height,a[a[it].right].height) + 1;
    }

    int size(int it)
    {
        return a[a[it].left].sz + a[a[it].right].sz + a[it].cnt;
    }

};

int n;
avl<int> a;


int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n;
    uint64 ans{};
    for(int i{ 1 },val; i <= n; ++i)
    {
        std::cin >> val;
        ans += a.kth(val);
        a.insert(val);
    }
    std::cout << ans;

    return 0;
}