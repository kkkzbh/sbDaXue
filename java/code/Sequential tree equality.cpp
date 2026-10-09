



//题目
//每一个数字序列 2 3 4 7等 都对应了唯一的一棵二叉搜索树 反之不一定
//第一行输入 N M   N序列长度 和 M要输入的序列个数
//随后M行 输入序列 其中从第二个序列开始 依次与第一个序列比较 如果 是相同的二叉搜索树 输出Yes 否则输出No

//案例
//输入
//5 4
//2 5 1 4 3
//2 1 5 4 3
//2 5 4 3 1
//3 1 5 4 3
//2 1 4 5 3

//输出
//Yes
//Yes
//No
//No

//*****************************text     one *****************************//
//                      直接根据序列制造出两棵树 然后判断两棵树是否相等

#ifdef __DEBUG__001
#include<iostream>

template<class T>
class tree              //制造一棵树
{
public:
    T element;      //元素值
    tree<T>* left;  //左指针
    tree<T>* right; //右指针

public:
    tree(const T& ele = T()):element(ele),left(nullptr),right(nullptr){}
};

template<class T>
class BST   //制造一个 二叉搜索树类
{
private:
    tree<T>* tr;
public:
    BST():tr(nullptr){}   //空树切忌空指针,不要忘记初始化
    tree<T>* push(const T& ele,tree<T>*& it) //插入操作  返回当前栈帧的节点地址
    {
        if(!it)     //如果栈帧节点为空指针 则生成一棵树的根节点
        {
            it = new tree<T>(ele);
        }
        else if(ele > it->element)  //如果是一个比当前值大的ele
        {
            it->right = push(ele,it->right);    //插入当前栈帧的右子树节点 由于右子树的根节点(nullptr)可能变化
        }                                                            // 故要做赋值处理
        else if(ele < it->element)
        {
            it->left = push(ele,it->left);
        }
        return it;
    }
    inline void push(const T& ele)  //语法糖
    {
        push(ele,tr);
    }
    inline tree<T>*& get()  //提供树头指针的接口   语法糖
    {
        return tr;
    }
};

template<class T>
bool isEqual(tree<T>* tr1,tree<T>* tr2) //功能 判定两棵树是否相等
{
    if(!tr1 && !tr2)    //如果两棵树根节点都是空指针 则判定相等
        return true;
    else if(!tr1 || !tr2)   //如果一棵树根节点空 一棵不空 则判定不相等
        return false;
    else if(tr1->element == tr2->element)   //如果都不空 且根节点值相同 则比较左右子树是否相等
        return (isEqual(tr1->left,tr2->left) && isEqual(tr1->right,tr2->right));
    else    //如果都不空 根节点值不同 则判定不相等
        return false;
}

int main()
{
    BST<int> tr;   //制造主树
    int N,M;
    std::cin >> N >> M; //输入 N与M
    int value = 0;
    for(int i = 0;i<N;i++)
    {
        std::cin >> value;
        tr.push(value);    //主树插值
    }
    for(int i = 0;i<M;i++)
    {
        BST<int> tmp;      //制造一个副树
        for(int j = 0;j<N;j++)
        {
            std::cin >> value;
            tmp.push(value);   //插值
        }
        if(isEqual(tr.get(),tmp.get()))   //判定是否相等
        {
            std::cout << "Yes\n";
        }
        else
        {
            std::cout << "No\n";
        }
    }
    return 0;
}

#endif

#ifdef __DEBUG__002
//*****************************text     two *****************************//
//      只制造出一棵树，对于第二个数字序列，按顺序对每个数字做一个处理
//      在主树上查找这个数字,从根节点开始 每一个遍历的节点做一个标记 证明已经遍历过
//                          如果找不到 直接判不相等
//                          如果找到了,则找到的这个节点未被标记遍历
//                          且向上级遍历的所有节点 都是已经标记遍历,然后给这个节点标记遍历 继续下一个数字
//                          若有一个序列中数字不符合该判定，则判定不相等

#include<iostream>

template<class T>
class tree              //制造一棵树
{
public:
    T element;      //元素值
    tree<T>* left;  //左指针
    tree<T>* right; //右指针
    int tag;    //***这是本方法与上面的一个区别 利用tag 标记该节点是否已经遍历***//
public:
    tree(const T& ele = T()):element(ele),left(nullptr),right(nullptr),tag(0){}
};

template<class T>
class BST   //制造一个 二叉搜索树类
{
private:
    tree<T>* tr;
public:
    BST():tr(nullptr){}   //空树切忌空指针,不要忘记初始化
    tree<T>* push(const T& ele,tree<T>*& it) //插入操作  返回当前栈帧的节点地址
    {
        if(!it)     //如果栈帧节点为空指针 则生成一棵树的根节点
        {
            it = new tree<T>(ele);
        }
        else if(ele > it->element)  //如果是一个比当前值大的ele
        {
            it->right = push(ele,it->right);    //插入当前栈帧的右子树节点 由于右子树的根节点(nullptr)可能变化
        }                                                            // 故要做赋值处理
        else if(ele < it->element)
        {
            it->left = push(ele,it->left);
        }
        return it;
    }
    inline void push(const T& ele)  //语法糖
    {
        push(ele,tr);
    }
    inline tree<T>*& get()  //提供树头指针的接口   语法糖
    {
        return tr;
    }     
    void clear(tree<T>* tr)
    {
        if(!tr)     //空树就请回吧
            return;
        tr->tag = 0;    //清除自己
        clear(tr->left);    //清除左子树
        clear(tr->right);    //清除右子树
    }
    inline void clear()  //语法糖   //***与上方法第二个不同点 这里添加了一个clear用于clear所有Tag值***//
    {
        clear(tr);
    }
};

template<class T>
bool find(int value,tree<T>* tr)
{
    if(tr->tag) //如果已经遍历
    {
        if(value == tr->element)    //淘汰！
            return false;
        else if(value > tr->element)
            return find(value,tr->right);    //去右子树找
        else
            return find(value,tr->left); //去左子树找
    }
    else   //新鲜的节点
    {
        if(value == tr->element)    //符合要求
        {
            tr->tag = 1;    //标记
            return true;
        }
        else    //不符合要求
        {
            return false;
        }
    }
}


int main()
{
    int N,M;    //定义N与M
    std::cin >> N >> M; //输入
    BST<int> tr;    //创建主树
    int value = 0;  //记录输入的数字
    for(int i = 0;i<N;++i)
    {
        std::cin >> value;  //开始输入数字序列
        tr.push(value); //插入主树中
    }
    for(int i = 0;i<M;++i)  //循环M次处理M个序列
    {
        int flag = 1;   //假设它是合格的
        for(int i = 0;i<N;i++)
        {
            std::cin >> value;  //读入数字
            if(flag && !find(value,tr.get()))   //只要存在不符合要求 就直接falg=0
                flag = 0;          //但不结束循环 因为要把这一行的数字读了 但利用&&特性 以多计算一次为代价 不重复find
        }
        if(flag)
        {
            std::cout << "Yes\n";
        }
        else
        {
            std::cout << "No\n";
        }
        tr.clear(); //每一次每一行的序列判断完成后 还原tag标记
    }
    
    return 0;
}

#endif

//*****************************text     three *****************************//  
//              是的，不建树难道就不能判断了吗？
//              注意到 对于 2 5 1 4 3这样的序列构成的一棵树 根节点是 2
//              但是 在2之后 按顺序取比2小的序列为{1} 很容易理解 这课树的左子树是序列{1}
//                                  同理 右子树是序列{5,4,3}
//              即 {2,5,1,4,3}这棵树的左子树是{1},右子树为{5,4,3} 根节点为第一个数字序列2
//              利用此特性去判定两棵树是否相同 类似递归的思想
#ifdef __DEBUG__003
#include<iostream>

int main()
{
    // 你说的对 我不会写

    return 0;
}

#endif

