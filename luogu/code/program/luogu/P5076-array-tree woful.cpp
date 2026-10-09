

#include<iostream>

using size = std::size_t;

template<typename T>
struct node
{
    T val{};
    size left = 0;
    size right = 0;
    size count = 0;
    node() = default;
    node(const T& v) : val(v),count(1){}
};

template<typename T>
struct bstree
{
    constexpr static size M_size = 10000 + 10;
    using node = node<T>;

    size root = 0;
    node val[M_size];
    size M_top = 0;

    void insert(const T& v)
    {
        if(!root)
            val[root = ++M_top] = v;
        else
            M_insert(v,root);
    }
    size find_rank_x(const T& v)
    {
        return M_find_rank_x(v,root);
    }
    T& find_rank(size i)
    {
        return M_find_rank(root,i);
    }
    T find_pre(const T& v)
    {
        if(auto i = find_rank_x(v); i == 1)
            return -2147483647;
        else
            return find_rank(i - 1);
    }
    T find_back(const T& v)
    {
        if(auto i = find_rank_x(v + 1); i > val[root].count)
            return 2147483647;
        else
            return find_rank(i);
    }
private:
    T& M_find_rank(size it,size i) //得知所求结点有i - 1个数比该数小 // i >= 1
    {
        if(val[val[it].left].count == i - 1) //刚好有i - 1个数比根节点小 则根节点为所求节点
            return val[it].val;
        else if(val[val[it].left].count > i - 1) //有更多个数比根节点小 则所求结点在左子树
            return M_find_rank(val[it].left,i);
        else //左子树比根节点小的数小于i - 1个 则根节点也小于所求结点 所求结点必在右子树且现在右子树只有i - n(left) - 1个比数小
            return M_find_rank(val[it].right,i - val[val[it].left].count - 1);
    }
    size M_find_rank_x(const T& v,size it)
    {
        if(!it)
            return 1;
        if(v < val[it].val)
            return M_find_rank_x(v,val[it].left);
        else if(v > val[it].val)
            return val[val[it].left].count + 1 + M_find_rank_x(v,val[it].right);
        else
            return val[val[it].left].count + 1;
    }
    void M_insert(const T& v,size it)
    {
        if(v < val[it].val)
        {
            if(val[it].left)
                M_insert(v,val[it].left);
            else
                val[val[it].left = ++M_top] = v;
        }
        else if(val[it].val < v)
        {
            if(val[it].right)
                M_insert(v,val[it].right);
            else
                val[val[it].right = ++M_top] = v;
        }
        val[it].count = val[val[it].left].count + val[val[it].right].count + 1;
    }
};

bstree<int> tree;

int main()
{
    freopen("../in.in","r",stdin);
    freopen("../out.out","w",stdout);
    int q;
    std::cin >> q;
    for(int i = 0,op,x; i != q;++i)
    {
        switch(std::cin >> op >> x; op)
        {
            case 1:
                std::cout << tree.find_rank_x(x) << '\n';
                break;
            case 2:
                std::cout << tree.find_rank(x) << '\n';
                break;
            case 3:
                std::cout << tree.find_pre(x) << '\n';
                break;
            case 4:
                std::cout << tree.find_back(x) << '\n';
                break;
            case 5:
                tree.insert(x);
                break;
            default:
                break;
        }
    }

    return 0;
}
