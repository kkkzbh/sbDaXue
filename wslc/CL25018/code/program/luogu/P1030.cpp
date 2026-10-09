

#include<iostream>
#include<string>

std::string in,back;

void dfs(size_t root,size_t left,size_t right)
{
    if(left == right) return;
    size_t i;
    for(i = left; in[i] != back[root]; ++i);
    std::cout << in[i];
    dfs(root - right + i,left,i);
    dfs(root - 1,i + 1,right);
}

int main()
{
    freopen("../in","r",stdin);
    freopen("../out","w",stdout);
    std::cin >> in >> back;
    dfs(back.size() - 1,0,in.size());


    return 0;
}