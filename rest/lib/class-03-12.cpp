


#include<iostream>
#include<format>

template<typename T>
void swap(T& a,T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    int a[]{10,8,12,4,76,5,32,78,2,9,1,2,3,7,20};
    int left = 1 - 1;       //左指针
    int right = 14 + 1;     //右指针
    int num = a[0];     //划分值

    std::cout << "划分前 划分值为" << num << "\n";
    for(auto it : a)
    {
        std::cout << it << ' ';
    }
    std::cout << '\n';
    while(left < right)
    {
        while(a[++left] < num);
        while(a[--right] > num);
        if(left < right) swap(a[left],a[right]);
    }
    swap(a[0],a[right]);
    std::cout << "划分后\n";
    for(auto it : a)
    {
        std::cout << it << ' ';
    }
    //由于只遍历了一边数组 算法时间复杂度为O(n)

    return 0;
}