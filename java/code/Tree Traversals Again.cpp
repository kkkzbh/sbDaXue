


//题目
//有序二叉树遍历可以通过堆栈以非递归方式实现。
//例如，假设遍历6节点二叉树（键的编号从1到6）时
//堆栈操作为：push（1）；push（2）；push（3）；pop（）；pop（）；push（4）；pop（）；pop（）；push（5）；push（6）；pop（）；pop（）
//然后，可以从这个操作序列生成一个唯一的二叉树（如图1所示）。你的任务是给出这个树的后序遍历序列


//Input Specification
//Each input file contains one test case. For each case, the first line contains a positive integer N (≤30)
//which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to N).
//Then 2N lines follow, each describes a stack operation in the format: "Push X"
//where X is the index of the node being pushed onto the stack; or "Pop" meaning to pop one node from the stack.

//Output Specification
//For each test case, print the postorder traversal sequence of the corresponding tree in one line.
//A solution is guaranteed to exist.
//All the numbers must be separated by exactly one space, and there must be no extra space at the end of the line.

//Sample Input:
//6
//  Push 1
//  Push 2
//  Push 3
//  Pop
//  Pop
//  Push 4
//  Pop
//  Pop
//  Push 5
//  Push 6
//  Pop
//  Pop

//Sample Output:
// 3 4 2 6 5 1

#ifdef __DEBUG__010
//*****************************text     one *****************************//
//思路
// 题目通过栈的操作 给出了一个中序序列 来让求出一个后序序列
// 实际上通过入栈 和 出栈的操作 已经对应了两条序列 先序和后序 我们可以利用这两条序列 不构树得到一个问题的解

#include<iostream>
#include<string>
#define MAX 30     //定义一个宏

int preorder[MAX] = {0};    //存储先序序列的数组
int inorder[MAX] = {0};
int find;

void postorder(int root,int start,int end)  //老操作了 三针两序定一树
{
    int i = 0;
    while(inorder[i] != preorder[root]) ++i;
    if(start <= i-1)
        postorder(root+1,start,i-1);
    if(i+1 <= end)
        postorder(root-start+i+1,i+1,end);
    if(!find) find = 1;
    else std::cout << ' ';
    std::cout << preorder[root];
}

auto main() -> int
{
    int n = 0;
    std::cin >> n;
    int* stack = new int[n];
    int top = -1;
    int t1 = -1;
    int t2 = -1;
    int value = 0;
    std::string str;
    for(int i = 0;i<n || top != -1;)
    {
        std::cin >> str;
        if("Push" == str)
        {
            std::cin >> value;
            stack[++top] = value;
            preorder[++t1] = value;
            ++i;
        }
        else
        {
            inorder[++t2] = stack[top--];
        }
    }
    postorder(0,0,t1);
    return 0;
}

#endif













