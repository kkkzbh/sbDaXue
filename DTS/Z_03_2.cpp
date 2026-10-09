

#include<iostream>
#include<cctype>
#include<queue>
constexpr int size = 10 + 10;
constexpr int null = -1;

template<typename T>
struct node
{
    T element = T();
    int left = null;
    int right = null;
    node() = default;
    explicit node(const T& ele) : element(ele){}
};

inline int to_int(int c)
{
    return c - '0';
}

void bfs(const node<int>(&a)[size],int head)
{
    std::queue<int> que;
    que.push(head);
    int it = null;
    int flag = 1;
    while(!que.empty())
    {
        it = que.front();
        que.pop();
        if(a[it].left == null && a[it].right == null)
        {
            if(flag) flag = 0; else std::cout << ' ';
            std::cout << a[it].element;
        }
        if(a[it].left != null)
        {
            que.push(a[it].left);
        }
        if(a[it].right != null)
        {
            que.push(a[it].right);
        }
    }
}

int main()
{
    node<int> tree[size];
    int n;
    std::cin >> n;
    char left,right;
    int top[size]{};
    for(int i = 0; i < n;++i)
    {
        std::cin >> left >> right;
        tree[i].element = i;
        if(isdigit(left))
        {
            tree[i].left = to_int(left);
            ++top[to_int(left)];
        }
        if(isdigit(right))
        {
            tree[i].right = to_int(right);
            ++top[to_int(right)];
        }
    }
    int head = null;
    for(int i = 0; i < n;++i)
    {
        if(!top[i])
        {
            head = i;
            break;
        }
    }
    bfs(tree,head);

    return 0;
}