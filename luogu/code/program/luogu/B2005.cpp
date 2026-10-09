

#ifdef B2005

#include<iostream>
#include<cstring>

int main()
{
    int n = 5;
    char c = 0;
    std::cin >> c;
    char a[21] = "                    ";
    char s[21]{};
    memset(s,c,20);
    int l = n/2;
    int r = n/2;
    for(;r < 5;--l,++r)
    {
        a[l] = s[l];
        a[r] = s[r];
        a[r + 1] = '\0';
        printf("%s\n",a);
    }

    return 0;
}

#endif
