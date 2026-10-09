

#ifdef P1598

#include<iostream>
#include<string>

char G[30][410];
char ot[410][30];
int top[30];
int max;

void T()
{
    for(int i = 0;i<26;++i)
        for(int j = 0;j<410;++j)
        {
            ot[410 - j - 1][i] = G[i][j];
        }
}

int main()
{
    for(int i = 0;i<26;++i)
    {
        G[i][0] = 'A' + i;
    }
    std::string str;
    while(std::cin >> str)
    {
        for(auto it : str)
        {
            if(isalpha(it))
            {
                G[it - 'A'][++top[it - 'A']] = '*';
                if (top[it - 'A'] > max) max = top[it - 'A'];
            }
        }
    }
    T();
    for(int i = 410 - max - 1;i < 410;++i)
    {
        int flag = 1;
        int end = 25;
        if(i != 409)
            for(;ot[i][end] != '*';--end);
        for(int j = 0;j<=end;++j)
        {
            if(flag) flag = 0; else std::cout << ' ';
            if(!ot[i][j]) std::cout << ' ';
            else std::cout << ot[i][j];
        }
        if(i != 409)
            std::cout << '\n';
    }

    return 0;
}

#endif
