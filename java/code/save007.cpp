

//题目
//在老电影“007之生死关头”（Live and Let Die）中有一个情节
//007被毒贩抓到一个鳄鱼池中心的小岛上，他用了一种极为大胆的方法逃脱 
//直接踩着池子里一系列鳄鱼的大脑袋跳上岸去！
//(据说当年替身演员被最后一条鳄鱼咬住了脚，幸好穿的是特别加厚的靴子才逃过一劫。)
//设鳄鱼池是长宽为100米的方形，中心坐标为 (0, 0)，且东北角坐标为 (50, 50)。池心岛是以 (0, 0) 为圆心、直径15米的圆。
//给定池中分布的鳄鱼的坐标、以及007一次能跳跃的最大距离，你需要告诉他是否有可能逃出生天。

//输入格式
//首先第一行给出两个正整数：鳄鱼数量 N（≤100）和007一次能跳跃的最大距离 D
//随后 N 行，每行给出一条鳄鱼的 (x,y) 坐标。注意：不会有两条鳄鱼待在同一个点上。

//输出格式
//如果007有可能逃脱，就在一行中输出"Yes"，否则输出"No"。

//输入样例 1
// 14 20
// 25 -15
// -25 28
// 8 49
// 29 15
// -35 -2
// 5 28
// 27 -29
// -8 -28
// -20 -35
// -25 -20
// -13 29
// -30 15
// -35 40
// 12 12

//输出样例 1
// Yes

//输入样例 2
// 4 13
// -12 12
// 12 12
// -12 -12
// 12 -12

//输出样例
// No


#ifdef __DEBUG__007
//*****************************text     one *****************************//

#include<iostream>
#define MAX 100
#define DIS(dx,dy) (((dx)*(dx)) + ((dy)*(dy))) //定义宏 用于计算距离的平方

struct obj  //对象 每个节点存储的信息
{
    int x; //x坐标
    int y; //y坐标

    obj():x(0),y(0){}
    obj(int px,int py) : x(px),y(py){}
};

class graph //先搓一个图,并注意到是无向的, 这里我用邻接矩阵表示法
{
public:
    bool G[MAX][MAX];    //矩阵 存储图的关系    //**不过我仔细回想 本题的邻接矩阵没有一丁点用！！！！**//
                                            //本题通过什么判断邻接点？ 非本矩阵 或者表 而是 DIS宏的值
    obj ob[MAX];    //存储每个节点的数据
    int top;
    bool visitor[MAX];     //访问数组 用于表示是否已经访问
    int N;  //表示数量
    int jump;   //表示跳跃距离
    bool win;   //判定是否可以逃脱
    graph() : top(-1),win(0)
    {       //******    由于邻接矩阵根本用不到 但我这里就不做取消了     ********//
        for(int i = 0;i<MAX;++i)
        {
            for(int j = 0;j<MAX;++j)
            {
                G[i][j] = false;       //这里我用false表示没有结点未连接
            }
            visitor[i] = false;  //初始化visit 表示没访问
        }
        //*********                             ********//
    }
    void insert(int x,int y)
    {
        ob[++top] = obj(x,y);   //插入节点
                             //插入节点值的属性后 邻接矩阵插入边
    }
    inline bool isWin(int v) //判断是否可以逃出
    {
        return 50 - ob[v].x < ob[v].x + 50 ? 50 - ob[v].x <= jump : ob[v].x + 50 <= jump || 
                50 - ob[v].y < ob[v].y + 50 ? 50 - ob[v].y <= jump : ob[v].y + 50 <= jump; 
    }
    bool BFS(int v)  //使用深度优先搜索 判断是否可以跳到对岸
    {                       //这里递归的设计要合理  //怎么才能保留返回值 ？
        visitor[v] = true;
        int iswin = 0;
        if(isWin(v))    //如果可以跳出对岸 则返回true
        {
            win = 1;       //这里以两种方式 一种以对象内部定义变量 然后全部搜索一下
            return true;    //或者局部压栈iswin 以次变量保留下次栈帧的BFS值 用以返回 且判定可以逃脱后不会再进行遍历
        }
        for(int i = 0;i<N;++i)  //不能就继续跳跳跳
        {
            //v == 0表示在岛上 距离可以缩短15            //距离缩短15 等效为可以多跳15 sqrt(DIS)-15 <= jump 移项平方
            if(!iswin && v == 0 && !visitor[i] && (DIS(ob[v].x - ob[i].x,ob[v].y - ob[i].y) <= (jump+15)*(jump+15) ))  //判断能不能跳 即是否跳过 或够不到
                iswin = BFS(i);     //保留这次的遍历值 如果为1 则直接停止跳跃 因为已经赢了
            else if(!iswin && !visitor[i] && (DIS(ob[v].x - ob[i].x,ob[v].y - ob[i].y) <= (jump)*(jump)))
                iswin = BFS(i);
        }
        if(iswin)
            return true;   //如果各种跳都不行 就只能 寄了！
        return false;
    }
};


auto main() -> int
{
    graph G;  //生产一个对象
    std::cin >> G.N >> G.jump;
    int vx,vy;
    G.insert(0,0);  //这个是007的节点 等会就从这搜索
    for(int i = 0;i<G.N;++i)
    {
        std::cin >> vx >> vy;
        G.insert(vx,vy);        //这里其实可以优化insert 利用G.N 直接用insert读取N个数据 且避免了top这一个变量的空间和计算
                                //不过我懒的写了
    }
    if(G.BFS(0))
    {
        std::cout << "Yes";
    }
    else
    {
        std::cout << "No";
    }
    return 0;
}

#endif









