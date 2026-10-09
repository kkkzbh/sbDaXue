

#include<iostream>
#include<array>

constexpr size_t M_size = 30;

inline void print(char c)
{
    fputc(c,stdout);
}

struct node
{
    char left = '*';
    char right = '*';
};

struct tree
{
    std::array<node,M_size> a;
    char root = '*';

    void insert(char x,char y,char z) noexcept
    {
        a[hash(x)].left = y;
        a[hash(x)].right = z;
    }
    void preorder() const noexcept
    {
        if(root == '*') return;
        M_preorder(root,a);
    }
private:
    static void M_preorder(char root,const std::array<node,M_size>& a) noexcept
    {
        print(root);
        if(a[hash(root)].left != '*') M_preorder(a[hash(root)].left,a);
        if(a[hash(root)].right != '*') M_preorder(a[hash(root)].right,a);
    }
    static size_t hash(char c) noexcept
    {
        return c ^ 96;
    }
};

int main()
{
    freopen("../in","r",stdin);
    freopen("../out","w",stdout);
    int n;
    std::cin >> n;
    tree v;
    for(int i = 0; i != n;++i)
    {
        char a,b,c;
        std::cin >> a >> b >> c;
        if(!i) v.root = a;
        v.insert(a,b,c);
    }
    v.preorder();


    return 0;
}