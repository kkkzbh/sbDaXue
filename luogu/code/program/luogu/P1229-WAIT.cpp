

#if 0

走到一个根节点时 他只有一个子树 产生的多解
如何确定只有一个子结点的结点

假设该根结点A仅有一个子树(根节点为B) 则先序序列中必然为AB
后续序列中 必然存在BA 

那么如何判定命题 当先序AB 后序BA 一定是根节点A只有一个子树而不存在A是叶节点这种情况 留作WAIT
由AB + A为叶节点
对于BA 遍历完B后 第一步也必然是回退到结点Y 且是从左回退 否则 Y = A 与A叶节点矛盾
若Y无右节点 则矛盾 此时是BY 而Y不可能为A 则Y有右节点 进入右节点
那么推理出命题 A 在 Y的右节点 然而根据先序遍历的结果 如果 B 在Y的左侧 A 在Y的右侧 必然不可能有AB 故矛盾 命题为真

推理就只得根据已知条件和运行结果一步步的推理证明

#endif


#include<iostream>
#include<string>
#include<format>

template<typename... Args>
void print(const std::string_view fmt_str,Args&&... args)
{
    fputs(std::vformat(fmt_str,std::make_format_args(args...)).c_str(),stdout);
}


std::string front,back;

size_t inorder(size_t root,size_t left,size_t right)  //fleft = root
{
    if(left != right)
    {
        if(front[root + 1] == back[right - 1])
        {
            return 2 * inorder(root + 1,left,right - 1);
        }
        else
        {
            size_t i;
            for(i = left; i != right && back[i] != front[root + 1];++i);    //N
            return inorder(root + 1,left,i) * inorder(root + 1 + (i - left + 1),i + 1,right - 1);   //logN
        }
    }
    return 1;
}

int main()
{
    freopen("../in.in","r",stdin);
    freopen("../out.out","w",stdout);
    std::cin >> front >> back;
    print("{}",inorder(0,0,back.size() - 1));


    return 0;
}