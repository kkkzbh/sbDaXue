

//题目
//给一个最小堆,下标从1开始存储,往最小堆里插入一系列数字，然后给定下标i 打印从下标i到根节点的路径
//第一行输入 N,M   N表示要插入几个数字  M表示要给多少个下标i

//案例
//输入
//5 3
//46 23 26 24 10
//5 4 3

//输出
//24 23 10
//46 23 10
//26 10


#ifdef __DEBUG__005
//*****************************text     one *****************************//

#include<iostream>


class heap  //制造一个对象 ： 最小堆
{
private:
    int* tr;
    int top;
public:
    heap(int n):tr(new int[n+1]()),top(0) //初始化heap 容量为n+1
    {
        tr[top] = -9999999;    //哨兵
    }
    void insert(int x)  //插入功能
    {
        int t = ++top;  //拷贝一份top 防止修改对象的top
        while(tr[t/2] > x)  //如果父亲比儿子大 说明需要交换 同时更新栈帧指针
        {
            tr[t] = tr[t/2];  //此时将父亲值 赋给儿子 同时栈帧指针向上移动
            t /= 2;     //移动指针
        }
        tr[t] = x;  //最后给当前栈帧指针赋值x
    }
    void print(int x)   //打印路径功能
    {
        std::cout << tr[x]; //先打印出叶节点 这样是为了不多打印一个空格
        while(x/2)  //只要父亲不是哨兵
        {
            x /= 2;
            std::cout << ' ' << tr[x];
        }
    }
};

int main()
{
    int N,M;
    std::cin >> N >> M;
    heap h(N);   //产生一个大小为容量为N+1的堆
    int value;
    for(int i = 0;i<N;++i)
    {
        std::cin >> value;
        h.insert(value);
    }
    for(int i = 0;i<M;++i)
    {
        std::cin >> value;
        h.print(value);
        std::cout << '\n';
    }
    return 0;
}

#endif