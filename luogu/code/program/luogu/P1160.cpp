

#include<iostream>
#include<unordered_map>

#if 0

走了大的弯路 我也是服了

思路1 本思路: 使用链表
应用单链表模拟本题
首先一个问题是 当需要插入第i位同学的左边或者右边时 如何快速找到第i位同学
one. 从头遍历 -> TLE
two. 题目使用了一个unordered_map 来存储 二元组 { index, pos };
    存储第i位的前指针 由于我所采用的为单链表故这样存储
    但其实仍然有可优化的情况
    可以利用题目的编号已经是1 ~ N 所以如果有了这个1 ~ N 的条件的话
    那么可以极低成本的利用数组 a[index] = pos 来存该二元组{ index,pos };
    且用数组消耗内存更少,速度也更快
    注意点 :
    注意每次的左右插入都会更改其他一些结点的前指针 所以需要同步更新 删除也是同理
    如果用双链表 则二元组的存储不需要存前指针 存index处的指针即可 且不需要考虑插入删除对其他结点的影响
    用双链表也属于空间 换 时间 多一个指针域的消耗 换每次插入删除的 少两次计算 几乎区别不大
思路2
直接采用一个二元组数组 a[index] = { left , right }; 来存储index处同学的左右同学
    本质就是一个 静态双向链表 与考虑链表的操作相同 不在过多赘述
    当然思路1的采用单链表 也可以改成静态链表存储 其实本质都是链表
    但应用静态链表 一定上也是 1 ~ N 的原因 可以低成本的使用静态链表

    以上两个思路使用 虚结点 (头节点) 可以更方便的处理 以及低成本找到开头 建议
#endif

template<typename T>
struct node
{
    T val;
    node* next = nullptr;
    node() = default;
    node(const T& v) : val(v){}
};

std::unordered_map<int,node<int>*> map;
template<typename T>
struct queue
{
    using node = node<T>;
    node* head = new node();
    node* Back = head;

    node* front(){ return head->next; }
    void push(const T& v){ Back = Back->next = new node(v); }
    node* back(){ return Back;}
    bool empty(){ return head == Back; }
    void insert(const T& v,int i,const T& kv)
    {
        node* it = head;
        while(it->next && it->next->val != v) it = it->next;
        if(i) it = it->next;
        node* tmp = new node(kv);
        tmp->next = it->next;
        it->next = tmp;
    }
    void insert(node* it,int i,const T& kv)
    {
        if(i) it = it->next;
        map.insert({kv,it});
        node* tmp = new node(kv);
        tmp->next = it->next;
        it->next = tmp;
        if(tmp->next) map[tmp->next->val] = tmp;
    }
    void erase(const T& v)
    {
        node* it = head;
        while(it->next && it->next->val != v) it = it->next;
        if(!it->next) return;
        node* tmp = it->next;
        it->next = tmp->next;
        delete tmp;
    }
    void erase(node* it)
    {
        node* tmp = it->next;
        map.erase(tmp->val);
        it->next = tmp->next;
        if(tmp->next) map[tmp->next->val] = it;
        delete tmp;
    }
    void print()
    {
        node* it = head;
        while(it->next)
        {
            std::cout << it->next->val << ' ';
            it = it->next;
        }
    }
};

int main()
{
    std::ios::sync_with_stdio(false),std::cout.tie(nullptr),std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    queue<int> que;
    que.push(1);
    map.emplace(1,que.head);
    for(int i = 2,k,p; i <= n; ++i)
    {
        std::cin >> k >> p;
        que.insert(map[k],p,i);
    }
    int m;
    std::cin >> m;
    for(int i = 1,sec; i <= m;++i)
    {
        decltype(map.begin()) it;
        std::cin >> sec;
        if((it = map.find(sec)) != map.end())
            que.erase(it->second);
    }
    que.print();

    return 0;
}