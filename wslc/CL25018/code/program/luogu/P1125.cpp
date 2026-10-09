

#ifdef P1125

#include<iostream>
#include<string>

int alpha[26];

bool isprime(int n)
{
    if(n <= 1) return false;
    int flag = 1;
    for(int i = 2;i*i<=n;++i)
    {
        if(n % i == 0)
        {
            flag = 0;
            break;
        }
    }
    return flag;
}

int main()
{
    std::string s;
    std::cin >> s;
    for(auto& it : s)
    {
        ++alpha[it - 'a'];
    }
    int maxi = 0;
    int mini = 101;
    for(int i = 0;i<26;++i)
    {
        if(alpha[i] > maxi)
        {
            maxi = alpha[i];
        }
        if(alpha[i] && alpha[i] < mini)
        {
            mini = alpha[i];
        }
    }
    if(isprime(maxi - mini))
    {
        std::cout << "Lucky Word\n";
        std::cout << maxi - mini;
    }
    else
    {
        std::cout << "No Answer\n";
        std::cout << 0;
    }

    return 0;
}

#endif
