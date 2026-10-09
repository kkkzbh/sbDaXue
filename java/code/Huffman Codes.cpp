


//第一行一个N
//然后第二一整行
//格式    c[1] f[1] c[2] f[2] ... c[N] f[N]
//c表示字符 f表示频率
//然后第三行一个M  表示个数
//对于每个M 都对应一个N行 每行格式c[i] code[i]  c是字符 code是编码
//判断是不是哈夫曼编码


#ifdef __DEBUG__012
//*****************************text     one *****************************//

#include<cstdio>
#include<cctype>
#include<cstring>

int frequent[70];

inline int find(char c)
{
    if(isdigit(c))
    {
        return c - '0';
    }
    if(islower(c))
    {
        return 10 + c - 'a';
    }
    if(isupper(c))
    {
        return 36 + c - 'A';
    }
    return 62;
}

#define LEFT(X) (2*(X) + 1)
#define RIGHT(X) (LEFT(X) + 1)
#define UP(X) ((X - 1)/2)

struct hufnode
{
    int weigh = 0;
    hufnode* left = nullptr;
    hufnode* right = nullptr;
    hufnode() = default;
    hufnode(int w) : weigh(w){}
    bool operator<(const hufnode& huf) const
    {
        return weigh < huf.weigh;
    }
    bool operator>(const hufnode& huf) const
    {
        return weigh > huf.weigh;
    }
};

hufnode heap[70];
int top = -1;

template<class T>
void swap(T &x,T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

void down(int n)
{
    int son = LEFT(n);
    if(son <= top)
    {
        if(son + 1 <= top && heap[son] > heap[son + 1])
            ++son;
        if(heap[son] < heap[n])
        {
            swap(heap[son], heap[n]);
            down(son);
        }
    }
}

void up(int n)
{
    hufnode tmp = heap[n];
    while(n && heap[UP(n)].weigh > heap[n].weigh)
    {
        heap[n] = heap[UP(n)];
        n = UP(n);
    }
    heap[n] = tmp;
}

void push(const hufnode& huf)
{
    heap[++top] = huf;
    up(top);
}

hufnode& pop()
{
    swap(heap[0],heap[top--]);
    down(0);
    return heap[top + 1];
}

int MakeLength(hufnode* huf,int depth)
{
    if(!huf->left)
    {
        return huf->weigh * depth;
    }
    return MakeLength(huf->left,depth + 1)
           + MakeLength(huf->right,depth + 1);
}

hufnode* CreateHuf()
{
    hufnode tmp;
    while(top)
    {
        hufnode& a = pop();
        hufnode& b = pop();
        tmp.weigh = a.weigh + b.weigh;
        tmp.left = new hufnode(a);
        tmp.right = new hufnode(b);
        push(tmp);
    }
    hufnode* huf = new hufnode(pop());
    return huf;
}



bool code(char *seq,hufnode* huf)
{
    char* select = seq;
    hufnode* it = huf;
    while(*seq)
    {
        if(huf->weigh) return false;
        if('1' == *seq)
        {
            if(huf->right)
                huf = huf->right;
            else
            {
                huf->right = new hufnode();
                huf = huf->right;
            }
        }
        else
        {
            if(huf->left)
                huf = huf->left;
            else
            {
                huf->left = new hufnode();
                huf = huf->left;
            }
        }
        ++seq;
    }
    if(huf->weigh || huf->left || huf->right)
        return false;
    huf->weigh = 1;
    return true;
}

int main()
{
    int n;
    scanf("%d",&n);
    char tmp;
    int v;
    char s[70]{};
    for(int i = 0;i<n;++i)
    {
        scanf(" %c",s + i);
        scanf("%d",&v);
        frequent[find(s[i])] += v;
        //heap[++top].weigh = frequent[find(tmp)];
    }
    for(int i = 0;i<n;++i)
    {
        heap[++top].weigh = frequent[find(s[i])];
    }
    for(int i = UP(top);i;--i)
    {
        down(i);
    }
    int m;
    scanf("%d",&m);
    hufnode* huf = CreateHuf();
    int length = MakeLength(huf,0);
    int max;
    char seq[1001][65]{};
    int flag;
    int enter = 1;
    for(int i = 0;i<m;++i)
    {
        flag = 1;
        max = 0;
        for(int j = 0;j<n;++j)
        {
            scanf(" %c",&tmp);
            scanf("%s",seq[j]);
            max += static_cast<int>(strlen(seq[j])) * frequent[find(tmp)];
        }
        if(max != length)
        {
            flag = 0;
        }
        if(flag)
        {
            hufnode *huf = new hufnode();
            for (int j = 0; j < n; ++j)
            {
                if (!code(seq[j], huf))
                {
                    flag = 0;
                    break;
                }
            }
        }
        if(enter) enter = 0; else printf("\n");
        if(flag)
        {
            printf("Yes");
        }
        else
        {
            printf("No");
        }
    }
    return 0;
}
#endif

#ifdef OTHERS

//第一行一个N
//然后第二一整行
//格式    c[1] f[1] c[2] f[2] ... c[N] f[N]
//c表示字符 f表示频率
//然后第三行一个M  表示个数
//对于每个M 都对应一个N行 每行格式c[i] code[i]  c是字符 code是编码
//判断是不是哈夫曼编码



//*****************************text     one *****************************//

#include<cstdio>
#include<cctype>
#include<cstring>

int frequent[70];

inline int find(char c)
{
    if(isdigit(c))
    {
        return c - '0';
    }
    if(islower(c))
    {
        return 10 + c - 'a';
    }
    if(isupper(c))
    {
        return 36 + c - 'A';
    }
    return 62;
}

#define LEFT(X) (2*(X) + 1)
#define RIGHT(X) (LEFT(X) + 1)
#define UP(X) ((X - 1)/2)

struct hufnode
{
    int weigh = 0;
    hufnode* left = nullptr;
    hufnode* right = nullptr;
    hufnode() = default;
    hufnode(int w) : weigh(w){}
    bool operator<(const hufnode& huf) const
    {
        return weigh < huf.weigh;
    }
    bool operator>(const hufnode& huf) const
    {
        return weigh > huf.weigh;
    }
};

hufnode heap[70];
int top = -1;

template<class T>
void swap(T &x,T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

void down(int n)
{
    int son = LEFT(n);
    if(son <= top)
    {
        if(son + 1 <= top && heap[son] > heap[son + 1])
            ++son;
        if(heap[son] < heap[n])
        {
            swap(heap[son], heap[n]);
            down(son);
        }
    }
}

void up(int n)
{
    hufnode tmp = heap[n];
    while(n && heap[UP(n)].weigh > heap[n].weigh)
    {
        heap[n] = heap[UP(n)];
        n = UP(n);
    }
    heap[n] = tmp;
}

void push(const hufnode& huf)
{
    heap[++top] = huf;
    up(top);
}

hufnode& pop()
{
    swap(heap[0],heap[top--]);
    down(0);
    return heap[top + 1];
}

int MakeLength(hufnode* huf,int depth)
{
    if(!huf->left)
    {
        return huf->weigh * depth;
    }
    return MakeLength(huf->left,depth + 1)
           + MakeLength(huf->right,depth + 1);
}

hufnode* CreateHuf()
{
    hufnode tmp;
    while(top)
    {
        hufnode& a = pop();
        hufnode& b = pop();
        tmp.weigh = a.weigh + b.weigh;
        tmp.left = new hufnode(a);
        tmp.right = new hufnode(b);
        push(tmp);
    }
    hufnode* huf = new hufnode(pop());
    return huf;
}



bool code(char *seq,hufnode* huf)
{
    char* select = seq;
    hufnode* it = huf;
    while(*seq)
    {
        if('1' == *seq)
        {
            if(huf->right)
                huf = huf->right;
            else
            {
                huf->right = new hufnode();
                huf = huf->right;
            }
        }
        else
        {
            if(huf->left)
                huf = huf->left;
            else
            {
                huf->left = new hufnode();
                huf = huf->left;
            }
        }
        ++seq;
    }
    if(huf->weigh != 0 || huf->left || huf->right)
        return false;
    huf->weigh = 1;
    return true;
}

int main()
{
    int n;
    scanf("%d",&n);
    char tmp;
    for(int i = 0;i<n;++i)
    {
        scanf(" %c",&tmp);
        scanf("%d",&frequent[find(tmp)]);
        heap[++top].weigh = frequent[find(tmp)];
    }
    for(int i = UP(top);i;--i)
    {
        down(i);
    }
    int m;
    scanf("%d",&m);
    hufnode* huf = CreateHuf();
    int length = MakeLength(huf,0);
    int max;
    char seq[1001][65]{};
    int flag;
    int enter = 1;
    for(int i = 0;i<m;++i)
    {
        flag = 1;
        max = 0;
        for(int j = 0;j<n;++j)
        {
            scanf(" %c",&tmp);
            scanf("%s",seq[j]);
            max += static_cast<int>(strlen(seq[j])) * frequent[find(tmp)];
        }
        if(max != length)
        {
            flag = 0;
        }
        if(flag)
        {
            hufnode *huf = new hufnode();
            for (int j = 0; j < n; ++j)
            {
                if (!code(seq[j], huf))
                {
                    flag = 0;
                    break;
                }
            }
        }
        if(enter) enter = 0; else printf("\n");
        if(flag)
        {
            printf("Yes");
        }
        else
        {
            printf("No");
        }
    }
    return 0;
}

#endif