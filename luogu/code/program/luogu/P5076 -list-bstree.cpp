

#include<iostream>

using size_t = std::size_t;

template<typename T>
struct node
{
    T val;
    node* left = nullptr;
    node* right = nullptr;
    size_t sz = 0;
    node() = default;
    node(const T& v) noexcept : val(v),sz(1){}
};

template<typename T>
struct bstree
{
    using node = node<T>;
    node* root = nullptr;

    void insert(const T& v) noexcept
    {
        struct stack
        {
            node* buffer[20000];
            size_t t = 0;
            void push(node*& v) noexcept
            {
                buffer[t++] = v;
            }
            void pop() noexcept
            {
                --t;
            }
            node*& top() noexcept
            {
                return buffer[t - 1];
            }
            [[nodiscard]]
            bool empty() const noexcept
            {
                return !t;
            }
            [[nodiscard]]
            size_t size() const noexcept
            {
                return t;
            }
        };

        node** it = &root;
        stack stk;
        while(true)
        {
            if(!*it)
            {
                *it = new node(v);
                break;
            }
            else if(v < (*it)->val)
            {
                stk.push(*it);
                it = &(*it)->left;
            }
            else if((*it)->val < v)
            {
                stk.push(*it);
                it = &(*it)->right;
            }
            else
                break;
        }
        while(!stk.empty())
        {
            node* tmp = stk.top();
            tmp->sz = 1;
            if(tmp->left) tmp->sz += tmp->left->sz;
            if(tmp->right) tmp->sz += tmp->right->sz;
            stk.pop();
        }
    }
    [[nodiscard]]
    size_t rank_x(const T& v) const noexcept
    {
        node* it = root;
        size_t rank = 1;
        while(it)       //首break可以优化为while 尾break do-while 尾递归->栈
        {
            if(v < it->val)
            {
                it = it->left;
            }
            else if(it->val < v)
            {
                if(it->left) rank += it->left->sz;
                ++rank;
                it = it->right;
            }
            else
            {
                if(it->left) rank += it->left->sz;
                break;
            }
        }
        return rank;
    }
    [[nodiscard]]
    T rank(size_t rk) const
    {
        node* it = root;
        while(it)
        {
            if(!it->left && rk == 1 || it->left && it->left->sz == rk - 1)
                return it->val;
            else if(!it->left || it->left->sz < rk - 1)
            {
                if(it->left)
                    rk -= it->left->sz;
                --rk;
                it = it->right;
            }
            else
                it = it->left;
        }
        throw std::invalid_argument("cannot find a val in the tree which rank is rk");
    }
    [[nodiscard]]
    T f_pre(const T& v) const
    {
        if(auto i = rank_x(v); i == 1)
            return -2147483647;
        else
            return rank(i - 1);
    }
    [[nodiscard]]
    T f_back(const T& v) const
    {
        if(auto i = rank_x(v + 1); !root || i > root->sz)
            return 2147483647;
        else
            return rank(i);
    }
};


int main()
{
    freopen("../in.in","r",stdin);
    freopen("../out.out","w",stdout);
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr),std::cout.tie(nullptr);
    int q;
    std::cin >> q;
    bstree<int> tree;
    while(q--)
    {
        int op,x;
        switch(std::cin >> op >> x; op)
        {
            case 1:
                std::cout << tree.rank_x(x) << '\n';
                break;
            case 2:
                std::cout << tree.rank(x) << '\n';
                break;
            case 3:
                std::cout << tree.f_pre(x) << '\n';
                break;
            case 4:
                std::cout << tree.f_back(x) << '\n';
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