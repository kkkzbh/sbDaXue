

#include<iostream>
#include<cstring>
constexpr int size = 10 + 10;

constexpr int null = -1;

template<typename T>
struct node
{
    T element = T();
    int left = -1;
    int right = -1;
    node() = default;
    explicit node(const T& ele) : T(ele){}
};

inline int to_int(int c)
{
    return c - '0';
}

bool isomorphism(node<char> (&tr1)[size],int h1,node<char> (&tr2)[size],int h2)
{
    if(h1 == null && h2 == null) return true;
    if((h1 == null  ||  h2 == null)) return false;
    if(tr1[h1].element != tr2[h2].element) return false;
    return isomorphism(tr1,tr1[h1].left,tr2,tr2[h2].left)
           && isomorphism(tr1,tr1[h1].right,tr2,tr2[h2].right)
           || isomorphism(tr1,tr1[h1].left,tr2,tr2[h2].right) &&
              isomorphism(tr1,tr1[h1].right,tr2,tr2[h2].left);
}

const char ans[][5]{"No","Yes"};

int main()
{
    int n;
    std::cin >> n;
    char left;
    char right;
    node<char> tree1[size];
    node<char> tree2[size];
    int tab[size]{};
    int head1 = null;
    int head2 = null;
    for(int i = 0; i < n;++i)
    {
        std::cin >> tree1[i].element >> left >> right;
        if(std::isdigit(left))
        {
            tree1[i].left = to_int(left);
            ++tab[to_int(left)];
        }
        if(std::isdigit(right))
        {
            tree1[i].right = to_int(right);
            ++tab[to_int(right)];
        }
    }
    for(int i = 0; i < n;++i)
    {
        if(!tab[i])
        {
            head1 = i;
            break;
        }
    }
    memset(tab,0,sizeof(tab));
    std::cin >> n;
    for(int i = 0; i < n;++i)
    {
        std::cin >> tree2[i].element >> left >> right;
        if(std::isdigit(left))
        {
            tree2[i].left = to_int(left);
            ++tab[to_int(left)];
        }
        if(std::isdigit(right))
        {
            tree2[i].right = to_int(right);
            ++tab[to_int(right)];
        }
    }
    for(int i = 0; i < n;++i)
    {
        if(!tab[i])
        {
            head2 = i;
            break;
        }
    }
    std::cout << ans[isomorphism(tree1,head1,tree2,head2)];

    return 0;
}