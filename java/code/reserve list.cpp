

//题目
//反转一个链表
//输入第一行 给定第一个节点的地址 节点总数N 和 正整数K(K≤N) K表示反转链表的长度
//如1->2->3->4->5->6    K = 3 结果 : 3->2->1->4->5->6
// K = 4 结果 : 4->3->2->1->5->6
//接下来的N行输入 为以下格式
//Address Data Next
//Address是节点位置,Data是一个整数,Next是下一个节点的位置   -1表示空指针
//输出
//输出结果排序的链表，每个节点属性独占一行 格式与输入相同

//案例
//输入
// 00100 6 4
// 00000 4 99999
// 00100 1 12309
// 68237 6 -1
// 33218 3 00000
// 99999 5 68237
// 12309 2 33218

//输出 

// 00000 4 33218
// 33218 3 12309
// 12309 2 00100
// 00100 1 99999
// 99999 5 68237
// 68237 6 -1


//*****************************text     one *****************************//
//          思路则是反转链表 按个数反转即可
//          但这个链表为一个抽象链表 不是很好操作

#ifdef __DEBUG__004

#include<iostream>
#include<iomanip>

struct List     //创建一个抽象链表
{
    int Address;    //地址
    int Data;   //数值
    int Next;   //指向地址

    List(int address = 0,int data = 0,int next = 0):Address(address),Data(data),Next(next){}
};

int find(int address,List* tpL)   //寻找函数  寻找address地址的下标
{
    int top = -1;
    while(tpL[++top].Address != address);
    return top;
}

int main()
{
    int head;
    std::cin >> head;
    int N,K;
    std::cin >> N >> K;
    List* tpL = new List[N]();    //创建数组管理链表
    int top = -1;   //数组头
    List tmp;   //临时模板 用于接受输入数据 以放入数组
    for(int i = 0;i<N;++i)
    {
        std::cin >> tmp.Address >> tmp.Data >> tmp.Next;
        tpL[++top] = tmp;   //存入数据
    }
    List* L = new List[N]();
    int t = -1;
    L[++t] = tpL[find(head,tpL)];    //寻找第一个节点 即链表头
    while(L[t].Next != -1)
    {
        L[++t] = tpL[find(L[t].Next,tpL)];   //继续寻找它的下家
    }
    //往下我们获得了顺序存储的链表后 想要实现部分逆序输出 可以分两步直接输出    //或排序数组输出
    //以上就是基础中的对数组元素的操作和打印了 这里还是打算正常做
    for(int i = 0;i<K-1;i++)    //循环k-1次逆序K个数 但当K = 1时 实际效果与不旋转链表相同   每一次循环多一个<-
    {
        head = i+1;  //头指针偏移
        L[head].Next = L[head-1].Address;    //头指针下一元素指向首元素 即完成反转
    }
    if(head + 1 != N)
        L[0].Next = L[head+1].Address;  //对接链表 即让倒置后的部分链表的尾元素对接上原破碎的链表,如果不是全部倒置
    t = -1;
    std::cout << std::setfill('0');     //流操作算子 控制格式5个宽度 右对齐 不足处补0
    while(L[head].Next != -1)   //如果下一个节点是空指针 则为最后一个节点停止循环
    {
        std::cout << std::setw(5) << L[head].Address << ' ' << L[head].Data << ' '<< std::setw(5) << L[head].Next << '\n';
        head = find(L[head].Next,L);
    }
    std::cout << std::setw(5) << L[head].Address << ' ' << L[head].Data << ' ' << L[head].Next << '\n';  //打印最后一个节点
    //时间复杂度 已经无需吐槽
    //让我看看 O(n²)平平无奇 主要这个链表还是抽象链表 并不算一个指针链表
    delete[] tpL;
    delete[] L;
    return 0;
}


#endif