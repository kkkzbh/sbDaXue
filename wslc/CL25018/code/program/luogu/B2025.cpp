

#ifdef B2025

#include<iostream>

int main()
{
    int n = 5;
    char a[21] = "                    ";
    char s[21] = "********************";
    char b[21] = "                    ";
    int l = n/2;
    int r = n/2;
    for(;r < 5;--l,++r)
    {
        a[l] = s[l];
        a[r] = s[r];
        printf("%s\n",a);
    }
    l = 0;
    r = n-1;
    while(l != r)
    {
        s[l] = b[l];
        s[r] = '\0';
        printf("%s\n",s);
        ++l;
        --r;
    }

    return 0;
}

#endif
