

//题目
//编写程序在二叉树中查找给定结点及父结点。二叉树结点的数据域值不等于0的整数。

//输入格式
//输入第1行为一组用空格间隔的整数，表示带空指针信息的二叉树先根序列，其中空指针用0表示。
//例如1 5 8 0 0 0 6 0 0表示如下图的二叉树。第2行为整数m，表示查询个数。
//接下来m行，每行为一个不等于0的整数K，表示要查找的结点的数据值。
//m不超过100，二叉树结点个数不超过150000，高度不超过6000。输入数据保证二叉树各结点数据值互不相等。


//输出格式
//输出为m行，每行1个整数，表示被查找结点K的父结点数据值，若二叉树中无结点K或结点K无父结点，则输出0。


//输入样例
//1 5 8 0 0 0 6 0 0
//3
//8

#ifdef __DEBUG__006
//*****************************text     one *****************************//

#include<iostream>

class tree     //生成一个树 不创建实例对象而是使用指针管理
{
public:
    int element;
    tree* left;
    tree* right;
public:
    tree(int x = 0):element(x),left(nullptr),right(nullptr){}
};

tree* create(tree* tr)      //根据先序序列使一棵空树生成一棵树 必须严格按照规则输入先序序列(比如最后一定有两个0)
{
    static int value;   //在线序递归的过程中 保持value始终是一致的 使用static
    std::cin >> value;
    if(value)   //如果value != 0 对该节点的栈帧做如下处理
    {
        tr = new tree(value);   //创造该节点
        tr->left = create(tr->left);    //创造该节点的左节点
        tr->right = create(tr->right);  //创造该节点的右节点
    }
    return tr;  //如果value为0 说明目前该节点就应该为空指针域 故不做任何处理 直接返回
}
tree* find(int x,tree* tr,tree* lastv)  //查找函数 这里使用了一级lastv 仅用于保存上一栈帧的节点地址 没有修改意图
{
    if(!tr) //如果该栈帧节点为空 则返回空指针表示没有找到
        return nullptr;
    if(x == tr->element)    //如果该节点就是要找的节点 则直接返回lastv,如果是根节点 lastv刚好为nullptr(确保传参是nullptr)
        return lastv;
    lastv = tr;     //如果该节点不是要找的节点 且也不是空节点 则保存lastv
    tree* tmp = find(x,tr->left,lastv);     //去左子树找
    if(tmp)     //如果非空 说明找到了 返回即可
        return tmp;
    lastv = tr;     //左子树没找到就去右子树找
    tmp = find(x,tr->right,lastv);
    return tmp;     //不管右子树找没找到 都返回即可 没找到返回nullptr 找到则返回父节点
}       //对于递归写法的必要lastv引入 一般需要作为函数参数传值 整个栈帧过程中有且仅有一个lastv值 估也可以改为static 或者全局
        //虽然多传了一个参数 但对于指针来说 递归内存的消耗还是在可接受范围内的

int main()
{
    tree* tr = nullptr; //产生一棵空树
    tr = create(tr);    //对于create函数 如果参数为nullptr 则会更新当前栈帧的根节点 故函数外内递归 都做赋值处理
    int m;
    std:: cin >> m;
    tree* tmp = nullptr;
    tree* lastv = nullptr;
    int value;
    int flag = 1;
    for(int i = 0;i<m;++i)
    {
        std::cin >> value;
        tmp = find(value,tr,lastv);     //寻找tr内部value的父指针
        if(flag) flag = 0;
        else std::cout << '\n';
        if(tmp)     //不是空指针 说明找到了
        {
            std::cout << tmp->element;
        }
        else   //没找到
        {
            std::cout << 0;
        }
    }
    return 0;
}

#endif

