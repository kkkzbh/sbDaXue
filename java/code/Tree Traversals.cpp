

//题目
//Suppose that all the keys in a binary tree are distinct positive integers.
//Given the postorder and inorder traversal sequences, 
//you are supposed to output the level order traversal sequence of the corresponding binary tree.

//Input Specification
//Each input file contains one test case. For each case, the first line gives a positive integer N (≤30)，
//the total number of nodes in the binary tree.
//The second line gives the postorder sequence and the third line gives the inorder sequence.
//All the numbers in a line are separated by a space.

//Output Specification
//For each test case, print in one line the level order traversal sequence of the corresponding binary tree.
// All the numbers in a line must be separated by exactly one space, 
//and there must be no extra space at the end of the line.

//Sample Input:
//7
//2 3 1 5 7 6 4
//1 2 3 4 5 6 7

//Sample Output:
//4 1 6 3 5 7 2


//*****************************text     one *****************************//
//思路
//我仔细思考 或许可以应用分治算法解决问题,当然直接用序列构造一棵树是最容易最暴力的解决方法,最后我将(尝试)给出这种方法
//分治则为
//给定一个子树（树本身是自己的子树）的后序序列和中序序列可以看作为 左子树后序序列+右子树后序序列+根 | 左子树中序+根+右子树中序
//然后尝试去用递归解决问题
//如何确定容器 如何获得子树的子树序列是个问题

#ifdef ABANDON  // ****************狗都写不出这样的垃圾！ 直接废弃！*******************
#include<iostream>

void levelorder(int* post_,int* in_,int pi,int ii)   //功能 利用两个序列 得到层序序列   //pi ii表示数组大小
{
    int next_pi = 0;
    int next_ii = 0;
    int *lnext_post = new int[pi];   //下一个的序列一定会小一点 所以不担心越界
    int *lnext_in = new int[ii];
    int *rnext_post = new int[pi];
    int *rnext_in = new int[ii];
    std::cout << ' ';
    std::cout << post_[pi-1];
    for(next_ii = 0;post_[pi-1] != in_[next_ii];++next_ii)   //名字确实抽象了点 这名字 //遍历中序序列
    {
        lnext_post[next_ii] = post_[next_ii];     //保存左子树的后序序列
        lnext_in[next_ii] = in_[next_ii];   //保存左子树的中序序列
    }
    for(int i = next_ii+1;post_[i] != post_[pi-1];++i)
    {
        rnext_post[i] = post_[i];   //保存右子树的后序序列
    }
    for(int i = next_ii+1;i<ii;++i)
    {
        rnext_in[i] = in_[i];  //保存右子树的中序序列
    }
    levelorder(lnext_post,lnext_in,next_ii+1,next_ii+1);    //递归左子树
    levelorder(rnext_post,rnext_in,pi-next_ii-2,ii-next_ii-2);  //递归右子树
}

int main()
{
    int n;
    std::cin >> n;  //读入数据n
    int* post = new int[n];
    for(int i = 0;i<n;++i)
    {
        std::cin >> post[i];
    }
    int* in = new int[n];
    for(int i = 0;i<n;++i)
    {
        std::cin >> in[i];
    }
    //为了使末尾不会残留空格 第一次不递归
    int next_pi = 0;
    int next_ii = 0;
    int *lnext_post = new int[n];   //下一个的序列一定会小一点 所以不担心越界
    int *lnext_in = new int[n];
    int *rnext_post = new int[n];
    int *rnext_in = new int[n];
    std::cout << post[n-1];
    for(next_ii = 0;post[n-1] != in[next_ii];++next_ii)   //名字确实抽象了点 这名字 //遍历中序序列
    {
        lnext_post[next_ii] = post[next_ii];     //保存左子树的后序序列
        lnext_in[next_ii] = in[next_ii];   //保存左子树的中序序列
    }
    for(int i = next_ii+1;post[i-1] != post[n-1];++i)
    {
        rnext_post[i-next_ii-1] = post[i];   //保存右子树的后序序列
    }
    for(int i = next_ii+1;i<n;++i)
    {
        rnext_in[i-next_ii-1] = in[i];  //保存右子树的中序序列
    }
    levelorder(lnext_post,lnext_in,next_ii,next_ii);    //递归左子树
    levelorder(rnext_post,rnext_in,n-next_ii-1,n-next_ii-1);  //递归右子树

    return 0;
}

#endif

#ifdef __DEBUG__009
//*****************************text     two *****************************//
//      从上方的废弃代码可以看出 盲目的去用遍历的方式 以数组为容器 构造左右子树的序列数列实在是太tm傻逼了
//      这里用干脆改用数学的方法去研究   首先可以得出 n(中序) = n(后序) 这是显然的 对于一棵树而言 遍历的序列个数一定相同
//      然后下设start end root 三个指针 分别指代某次栈帧序列的 起点 终点 和根节点
//      其中start end的作用是 确定中序列中一个子树的范围 root的作用是 这个序列的根的序号（用于后序序列)
//      对于某个栈帧  后序遍历 最后一个结点一定是当前栈帧的根结点  此时root为后序列中的最后一个元素 
//      假设中序遍历序列中该根节点为序号为i
//      则可以根据理论得出 左子树的start = start , end = i - 1
//                       右子树的start = i + 1 , end = end;     //非常对称
//       因为start end 只表示了此树作用与中序序列中的序列 因此需要额外用一个root 作用于后序序列 表示该树的根
//       即对于一段某段子树中序序列 1,2,3,4,5,6 start = 1 , end = 6 但 后序序列不一定完美对应这个范围 我们需要知道根

//      对于非中序序列 我们利用该序列的任务就是确定根节点
//      对于中序序列 我们利用该序列的任务就是 用左右子树序列的 start 与 end 找到i 进而可以递归下去

//      那么只要序列合法 就可以递归下去 直到序列不合法 停止递归（一般则为递归到根节点的子树的情况)
//      最后还是依然需要一个容器来存储 我个人而言对STL底层代码不熟 故倾向于一般情况下 不使用STL 所以还是使用数组

#include<iostream>

#define MAX 30      //方便调试 我就不在堆上开数组了

int postorder[MAX] = {0};   //为了方便 数组直接开在全局
int inorder[MAX] = {0};
                   

    //对于这个preorder 他是依赖于两个数组运行的 而我想要说的就是 对于root start end的确定 到底该如何确定
    //首先对于一段序列 我们拥有它的root start end 然后 postorder inorder 两个数组是完全独立的
    //他们有序列对齐(即某个子树序列的start 和 end 在两个数组里相同)的情况 也亦有 不对齐的情况
    //现在抽象的认为 start end 只应用于inorder    root 只用于postorder
    //则首先一定可以用 start end 找到这个序列的根
    //则 这个序列的根被确定后 可以得知的是 左子树的个数为 i - start  右子树个数为 end - i
    //虽然两个序列可能存在不对齐的情况 但是左子树与右子树的个数却是绝对的
    //然后通过这个 回到 postorder的序列 作如下偏移 root - 1 一定是右子树的根 root - (end - i) - 1 一定是左子树的根
                                                                        //root - end + i - 1
void preorder(int root,int start,int end)    //对于给定一个序列 这里我用start 与 end 指针 去顺序的访问这个序列(通过容器数组)     
{
    if(start > end) return;     //如果start > end 说明这是一个空序列 也就是空树 停止递归
    std::cout << postorder[root] << ' '; //打印该栈帧的根节点
    int i = start;  //确定起点指针
    while(inorder[i] != postorder[root]) ++i;    //在中序序列中找到根 序号i
            // 这里没有添加 i < end 等 控制合法性的判断 原因在于 如果一个树合法 也就是说有序列 则必然能从start到end找到根的
    preorder(root - end + i - 1,start,i-1);    //打印左子树序列
    preorder(root - 1,i+1,end);      //打印右子树序列                     
}
//可以看到上面的结构 很类似于 自己 左子树 右子树 的先序结构


struct que_node
{
    int root;
    int start;
    int end;      //三个指针决定了一棵树 且 找左右子树的方法
    que_node* next;

    inline que_node(int x,int y,int z) : root(x),start(y),end(z),next(nullptr){}
};

class queue     //搓一个队列 这个没什么好说的
{
private:
    que_node* _front;
    que_node* _back;
public:
    inline queue() : _front(nullptr),_back(nullptr){}
    void push(int x,int y,int z)
    {
        if(!_front)
        {
            _front = new que_node(x,y,z);
            _back = _front;
            return;
        }
        _back->next = new que_node(x,y,z);
        _back = _back->next;
    }
    void pop()
    {
        if(!_front)
            return;
        else if(_front == _back)
        {
            delete _front;
            _front = _back = nullptr;
        }
        else
        {
            que_node* tmp = _front;
            _front = _front->next;
            delete tmp;
        }
    }
    inline auto top() -> que_node&
    {
        return *_front;
    }
    inline auto back() -> que_node&
    {
        return *_back;
    }
    inline auto empty() -> bool
    {
        return _front == nullptr;
    }
};


//上面的并不是本题要解决的 本题 要解决的是转化为 levelorder
//那么结合经验 可以得知 结构大概是要与队列相关 不过这只是我猜
void levelorder(int root,int start,int end)     //依然选择上面那三个指针 去确定一棵树
{
    queue que;
    que.push(root,start,end); //root - start - end 定 结点+左右子树
    que_node tmp(root,start,end);
    int i = 0;
    while(!que.empty())
    {
        tmp = que.top();
        que.pop();
        std::cout << postorder[tmp.root] << ' ';
        i = tmp.start;                              //切记操作习惯 所有的start end root 均记得是tmp下的值
        while(inorder[i] != postorder[tmp.root]) ++i;
        if(tmp.start <= i-1)
            que.push(tmp.root - tmp.end + i - 1,tmp.start,i-1);
        if(i+1 <= tmp.end)
            que.push(tmp.root - 1,i+1,tmp.end);
    }
}

int main()
{
    int n;  //读入节点数
    std::cin >> n;
    for(int i = 0;i<n;++i)
    {
        std::cin >> postorder[i];
    }
    for(int i = 0;i<n;++i)
    {
        std::cin >> inorder[i];
    }
    levelorder(n-1,0,n-1);
    return 0;
}

//实在是累了 用序列构造树 我就不构造了先 真的累了

#endif