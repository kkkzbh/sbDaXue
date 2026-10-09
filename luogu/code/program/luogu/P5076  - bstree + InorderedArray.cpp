

#if 0

字数的结点struct node 不一定非要标准三权值 剩余的全靠打 不一定   |||都是 space -> time
由于标准的bstree不是muti的 但其实也可以实现muti 定义相等放左放右即可 非muti的一个操作为 额外引入一个计数的变量 space -> information

以下的logn复杂度 为一个理论上的logn 由于这不是自旋上的二叉树 最坏下仍然是n
1.bstree中 找第i个小的数  --由于每次都会走一层 复杂度 logn
    结点中引入 size = 子树的结点数量 每次插入时维护 有这个变量 又牺牲了空间 但bstree也因此变的更为强大
    进入根节点 if 左子树的个数+1 大于 i 则所求结点 -> 左子树 此时根和右子树都比所求结点大 不管
    进入根节点 if 左子树的个数+1 小于i 则所求结点 -> 右子树  此时根和左子树都小于所求结点 转化问题为求右子树 第 i - 左子树 - 1个小的数
    进入根节点 if 左子树的个数+1 == i 则 根节点为所求结点
    显然上述为一个递归过程 核心为size变量 如果没有这个变量几乎无法完成此功能 size更好的发挥了其的有序性
2.bstree 找有几个数比x小  --复杂度 logn
    进入根节点正常搜索x的位置 如果进入左子树 进入左子树 右子树和根的显然都比x大 不用管
    如果进入右子树 则左子树包括根都比x小 加上左子树的所有个数 + 1
    如果找到值x 加上其左子树(如果有)的个数 然后就可以return了;
    如果找到空结点(没搜到x) 此时也可以直接return;了
3.找前驱后驱     --logn
    由于树的特殊性 前驱后驱不一定是相邻的结点 可能压根就没有任何关系
    那么如果要在树上去寻找前驱后驱 一个办法是
    利用2.找有几个树比x小 假设有i个数据比x小 --logn
    利用1.找第i个小的数 为前驱 --logn
    利用1.找第i + 2小的数 为后驱 --理论logn
4.插入
    这个就没什么好说的了 正常建立一个bstree即可 链表亦或者是数组 建树
    链表建树更为直观
    数组建树 维护两个指针即可 root指针 容量指针 只是结点都存储到一块了 与静态链表并无区别 可能操作较链表方便 节省寻址时间
#endif

#include<iostream>

template<typename T>
struct node
{
    T val;
    node* left = nullptr;
    node* right = nullptr;
    node() = default;
    explicit node(const T& v) : val(v){}
};

template<typename T>
struct bstree
{
    using node = node<T>;
    struct buffer       //菜鸡才选择的 中序序列数组化
    {
        constexpr static std::size_t default_size = 8;
        constexpr static std::size_t default_add_time = 2;
        T* buf = new T[default_size];
        T* ed = buf;
        T* cap = buf + default_size;

        T& operator[](std::size_t pos) noexcept { return buf[pos]; }
        void push_back(const T& v) noexcept
        {
            if(ed == cap) rc();
            *ed++ = v;
        }
        [[nodiscard]]
        std::size_t size() const noexcept
        { return ed - buf; }
        [[nodiscard]]
        std::size_t lower_bound(const T& v) const noexcept
        {
            auto l = buf;
            auto r = ed;
            while(l != r)
            {
                T* mid = l + (r - l) / 2;
                if(*mid < v) l = mid + 1;
                else r = mid;
            }
            return l - buf;
        }
        [[nodiscard]]
        std::size_t upper_bound(const T& v) const noexcept
        {
            auto l = buf;
            auto r = ed;
            while(l != r)
            {
                T* mid = l + (r - l) / 2;
                if(*mid <= v) l = mid + 1;
                else r = mid;
            }
            return l - buf;
        }
        void clear() noexcept
        { ed = buf; }
    private:
        void rc()
        {
            std::size_t new_size = default_add_time * (cap - buf);
            T* tmp = new T[new_size];
            for(std::size_t i = 0; i != size();++i) tmp[i] = std::move(buf[i]);
            ed = tmp + (ed - buf);
            cap = tmp + new_size;
            delete[] buf;
            buf = tmp;
        }
    };


    buffer buf;
    node* head = nullptr;
    bool swi = false;

    void insert(const T& v) noexcept { M_Insert(v,head); swi = false; buf.clear(); }
    std::size_t find_rank(const T& v) noexcept
    {
        if(!swi) M_Inordered(head,buf),swi = true;
        return buf.lower_bound(v) + 1;
    }
    T find_pre(const T& v) noexcept
    {
        if(!swi)  M_Inordered(head,buf),swi = true;
        auto i = buf.lower_bound(v);
        if(i <= 0) return -2147483647;
        return buf[i - 1];
    }
    T find_back(const T& v) noexcept
    {
        if(!swi) M_Inordered(head,buf),swi = true;
        auto i = buf.upper_bound(v);
        if(i == buf.size()) return 2147483647;
        return buf[i];
    }
    T find_rank_x(std::size_t x) noexcept
    {
        if(!swi)  M_Inordered(head,buf),swi = true;
        return buf[x - 1];
    }
private:
    static void M_Insert(const T& v,node*& n) noexcept
    {
        if(!n) n = new node(v);
        else if(v < n->val) M_Insert(v,n->left);
        else if(n->val < v) M_Insert(v,n->right);
    }
    static void M_Inordered(node* it,buffer& buf) noexcept
    {
        if(it->left) M_Inordered(it->left,buf);
        buf.push_back(it->val);
        if(it->right) M_Inordered(it->right,buf);
    }
};

int main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr),std::cout.tie(nullptr);
    freopen("../in.in","r",stdin);
    freopen("../out.out","w",stdout);
    int q;
    std::cin >> q;
    bstree<int> tree;
    for(int i = 0,op,x; i != q;++i)
    {
        if(std::cin >> op >> x; op == 1) std::cout <<  tree.find_rank(x) << '\n';
        else if(op == 2) std::cout << tree.find_rank_x(x) << '\n';
        else if(op == 3) std::cout << tree.find_pre(x) << '\n';
        else if(op == 4) std::cout << tree.find_back(x) << '\n';
        else if(op == 5) tree.insert(x);
    }

    return 0;
}