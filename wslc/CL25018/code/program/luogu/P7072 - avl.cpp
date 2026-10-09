
#include<iostream>
#include<array>
#include<algorithm>

constexpr int null{};

template<typename T>
struct M_anode
{
    T val{};
    int left{ null };
    int right{ null };
    int sz{ 1 };
    int hei{ 1 };
    int cnt{ 1 };
    M_anode() = default;
    M_anode(const T& v) : val(v){}
};

template<typename T,typename M_cmp>
struct avl
{
    constexpr static int M_size{ 10000 };
    using M_anode = M_anode<T>;
    std::array<M_anode,M_size> a;
    int root{ null };
    int M_tp{ 1 };

    avl()
    {
        a[0].sz = a[0].cnt =  a[0].hei = 0;
    }

    void insert(const T& val)
    {
        M_insert(root,val);
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
            a[it = M_tp++].val = val;
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

    void rotation(int& it)
    {
        int bf{ a[a[it].left].hei - a[a[it].right].hei };
        if(bf == -2)    //右
        {
            if(a[a[a[it].right].left].hei < a[a[a[it].right].right].hei) //右
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

avl<int,decltype([](const int a,const int b)
{
    return a > b;
})> a;
int n,w;

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin >> n >> w;
    for(int i{ 1 },val; i <= n; ++i)
    {
        std::cin >> val;
        a.insert(val);
        std::cout << a.find_kth(std::max(1,i * w / 100)) << ' ';
    }

    return 0;
}