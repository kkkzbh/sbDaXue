

//#define S1_1_6
#ifdef S1_1_6

#include<iostream>
#include<queue>

int main()
{
    std::queue<int> A;
    std::queue<int> B;
    int n;
    int v;
    std::cin >> n;
    while(n--)
    {
        std::cin >> v;
        if(v & 1) A.push(v);
        else B.push(v);
    }
    int flag = 1;
    while(!A.empty() || !B.empty())
    {
        if(!A.empty())
        {
            if(flag) flag = 0; else std::cout << ' ';
            std::cout << A.front();
            A.pop();
            if(!A.empty())
            {
                std::cout << ' ' << A.front();
                A.pop();
            }
        }
        if(!B.empty())
        {
            if(flag) flag = 0; else std::cout << ' ';
            std::cout << B.front();
            B.pop();
        }
    }

    return 0;
}

#endif
