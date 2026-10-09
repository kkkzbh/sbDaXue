


//题目
//六度空间”理论又称作“六度分隔（Six Degrees of Separation）”理论。
//这个理论可以通俗地阐述为：“你和任何一个陌生人之间所间隔的人不会超过六个
//也就是说，最多通过五个人你就能够认识任何一个陌生人。”
//“六度空间”理论虽然得到广泛的认同，并且正在得到越来越多的应用。但是数十年来，试图验证这个理论始终是许多社会学家努力追求的目标。
//然而由于历史的原因，这样的研究具有太大的局限性和困难。随着当代人的联络主要依赖于电话、短信、微信以及因特网上即时通信等工具，
//能够体现社交网络关系的一手数据已经逐渐使得“六度空间”理论的验证成为可能。
// 假如给你一个社交网络图，请你对每个结点计算符合“六度空间”理论的结点占结点总数的百分比。

//输入格式
//输入第1行给出两个正整数 N(节点数 1 < N ≤ 10⁴) 边数  M(M ≤ 33N)
//随后的M行对应M条边，每行给出一对正整数，分别是该条边直接连通的两个结点的编号（节点从1到N编号）。

//输出格式
// 对每个结点输出与该结点距离不超过6的结点数占结点总数的百分比，精确到小数点后2位。
//每个结节点输出一行，格式为“结点编号:（空格）百分比%”。

//输入样例

// 10 9
// 1 2
// 2 3
// 3 4
// 4 5
// 5 6
// 6 7
// 7 8
// 8 9
// 9 10


//输出样例

// 1: 70.00%
// 2: 80.00%
// 3: 90.00%
// 4: 100.00%
// 5: 100.00%
// 6: 100.00%
// 7: 100.00%
// 8: 90.00%
// 9: 80.00%
// 10: 70.00%


#ifdef __DEBUG__008
//*****************************text     one *****************************//

#include<iostream>
#include<iomanip>

struct node //存储边的信息  //充当表
{
    int v;
};

struct point    //结点 存储每个结点的信息
{
    node* table;
    int top;    //告知有几个顶点

    point():table(nullptr),top(-1){}
};

struct que_node
{
    int v;
    que_node* next;

    que_node():v(0) , next(nullptr){}
    que_node(int V):v(V),next(nullptr){}
};

class queue     //由于需要广度优先搜索 遂搓一个队列 考虑到队列是存每个结点的信息
{
public:
    que_node* front;
    que_node* back;
public:
    inline queue():front(nullptr),back(nullptr){}
    void push(int v)
    {
        if(!front)
        {
            front = new que_node(v);
            back = front;
            return;
        }
        back->next = new que_node(v);
        back = back->next;
    }
    void pop()
    {
        if(!front)
            return;
        else if(front == back)
        {
            delete front;
            front = back = nullptr;
            return;
        }
        else
        {
            que_node* tmp = front;
            front = front->next;
            delete tmp;
        }
    }
    inline int& top()   //返回队头
    {
        return front->v;
    }
    inline int& dop()       //一时命名冲突 先随便起了
    {
        return back->v;     //返回队尾 对于队列这两个操作也是很重要的
    }
    bool empty()
    {
        return front == nullptr;
    }
};

class graph     //制造一个图    N <= 10⁴ 而 M <= 33N    非常稀疏 采用邻接表
{
public:
    point* G;    //构造一张多表
    int N;  //结点数
    int M;  //边数
    bool* visitor;   //访问数组 表示是否访问过
public:
    graph(int n,int m) : G(new point[N+1]),N(n),M(m),visitor(new bool[N+1]) //题目要求结点从1开始 则开N+1 不做平移 懒
    {
        for(int i = 0;i<=N;++i)
        {
            G[i].table = new node[M];     //扩充至最大可能的边数 相对链表确实浪费了空间   但动态数组比链表更麻烦
        }
    }
    void insert()
    {
        int v1,v2;
        for(int i = 0;i<M;++i)
        {
            std::cin >> v1 >> v2;
            G[v1].table[++G[v1].top].v = v2;    //无向存储处理
            G[v2].table[++G[v2].top].v = v1;
        }
    }
    void clearv()
    {
        for(int i = 0;i<=N;++i)
        {
            visitor[i] = false;
        }
    }
    int BFS(int v)  //从V开始进行广度优先搜索
    {
        queue que;
        que.push(v);
        visitor[v] = true;
        int count = 1;
        int V;
        int lastv = v;
        int level = 0;
        while(!que.empty())
        {
            V = que.top();
            que.pop();
            for(int i = 0;i<=G[V].top;++i)
            {
                if(!visitor[G[V].table[i].v])   //需要遍历表数组 我一直用->我也是醉了
                {
                    que.push(G[V].table[i].v);
                    count++;
                    visitor[G[V].table[i].v] = true;
                }
            }
            if(lastv == V)  //以这种算法进行层数的计算
            {
                ++level;
                if(!que.empty())
                    lastv = que.dop();
            }
            if(level == 6)      //写成lastv == 6 我也是醉了 已更改
                break;
        }
        return count;
    }
    void start()    //成员的入口函数，负责对每个结点来一次六层BFS 然后输出结果
    {
        int count = 0;
        std::cout << std::setprecision(2) << std::fixed;    //设置输出格式
        int find = 1;
        for(int i = 1;i<=N;++i)     //所以从1开始遍历 因为结点从1开始 我也懒的平移
        {
            if(find) find = 0;
            else std::cout << '\n';
            count = BFS(i);
            std::cout << i << ": " << (double)count/N*100 << '%';
            clearv();
        }
    }
};


int main()
{
    int N,M;
    std::cin >> N >> M;
    graph G(N,M);   //生一个对象    
    G.insert();  //插入边
    G.start();  //结束
    return 0;
}

#endif













