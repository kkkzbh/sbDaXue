



//其实两个序列就可以确定一棵树了 对于确定的一棵树 可以有许多操作

#include<iostream>
#include<string>

using size = std::size_t;

std::string s1,s2;  //s1 为中序    s2为先序 可以直接定根

//对于双序列树 至少三个值去操作 四个值更舒服一点

void dfs(size st,size ed,size root)
{
    for(size i = st;i != ed;++i)
        if(s1[i] == s2[root])
        {
            dfs(st,i,root + 1);
            dfs(i + 1,ed,root + 1 + i - st);
            std::cout << s1[i];
            return;
        }
}

int main()
{
    std::cin >> s1 >> s2;
    dfs(0,s1.size(),0);

    return 0;
}