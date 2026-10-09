

#ifdef S1_1_5

#include<iostream>
#include<array>
//#include<algorithm>
constexpr int size = 1e5 + 10;

int main()
{
    std::array<int,size> a{};
    std::array<int,size> b{};
    int n;
    std::cin >> n;
    for(int i = 1; i <= n;++i)
    {
        std::cin >> a[i];
    }
    for(int i = 1; i <= n;++i)
    {
        std::cin >> b[i];
    }
    std::array<int,2*size> ans{};
    auto s1 = a.begin() + 1;
    auto e1 = a.begin() + 1 + n;
    auto s2 = b.begin() + 1;
    auto e2 = b.begin() + 1 + n;
    decltype(a.size()) top = 0;
    //ans[top] = std::min(*s1,*s2) - 1;
    while(s1 != e1 && s2 != e2)
    {
        if(*s1 < *s2)
        {
            //if(ans[top] == *s1) ++s1;
            //else
                ans[++top] = *s1++;
        }
        //else if(*s1 == *s2)
        //{
//            if(ans[top] == *s1)
//            {
//                ++s1;
//                ++s2;
//            }
//            else
//            {
//                ans[++top] = *s1++;
//                ++s2;
//            }
//        }
        else
        {
            //if(ans[top] == *s2) ++s2;
            //else
                ans[++top] = *s2++;
        }
    }
    while(s1 != e1)
    {
        //if(ans[top] == *s1) ++s1;
        //else
            ans[++top] = *s1++;
    }
    while(s2 != e2)
    {
        //if(ans[top] == *s2) ++s2;
        //else
            ans[++top] = *s2++;
    }
    std::cout << ans[(top + 1)/2];

    return 0;
}

#endif