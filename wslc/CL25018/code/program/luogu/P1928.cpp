

#ifdef P1928

#include<iostream>
#include<string>

std::string solve()
{
    char c;
    std::string s;
    int multiple;
    while(std::cin >> c)
    {
        if(c == '[')
        {
            std::cin >> multiple;
            std::string tmp = solve();
            while(multiple--)
            {
                s += tmp;
            }
        }
        else
        {
            if(c == ']') return s;
            s += c;
        }
    }
    return s;
}

int main()  //模拟实现的话 一种可以避免频繁的移动原字符序列的方法是 避免重复的
                        //在原串进行循环倍数插入操作 而是另起一字符串倍增
                        //然后replace掉原先压缩的整体部分 则一次解压只移动一次原串
                        //移动原串的操作与解压次数成比 则移动的次数会非常少 提高效率
                        //即大量的拼接增长操作 先另起一串完成 在replace而不直接在原串频繁insert
{
    std::cout << solve();

    return 0;
}

#endif