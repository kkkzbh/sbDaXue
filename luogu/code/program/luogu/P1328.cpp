

#ifdef P1328

#include<iostream>
#include<array>

constexpr int size = 200 + 2;
std::array<int,size> A;
std::array<int,size> B;
int scoA;
int scoB;

void cmp(int x,int y)       //多重嵌套的if表示的true或false 可以优化成 bool二维数组
{
    if(x == y) return;      //这是一个用数组时需要优化的地方 x == y 平局的考虑
    else if(x == 0)
    {
        if(y == 1 || y == 4) ++scoB;        //输了不加分 赢了加分  可以每次对scoA scoB 都进行一次矩阵判定
        else if(y == 2 || y == 3) ++scoA;
    }
    else if(x == 1)
    {
        if(y == 2 || y == 4)
            ++scoB;
        else if(y == 0 || y == 3)
            ++scoA;
    }
    else if(x == 2)
    {
        if(y == 0 || y == 3) ++scoB;
        else if(y == 1 || y == 4) ++scoA;
    }
    else if(x == 3)
    {
        if(y == 0 || y == 1) ++scoB;
        else if(y == 2 || y == 4) ++scoA;
    }
    else if(x == 4)
    {
        if(y == 2 || y == 3) ++scoB;
        else if(y == 0 || y == 1) ++scoA;
    }
}

int main()
{
    int n,a,b;
    std::cin >> n >> a >> b;
    for(int i = 1; i <= a;++i)
    {
        std::cin >> A[i];
    }
    for(int i = 1; i <= b;++i)
    {
        std::cin >> B[i];
    }
    int ita = 1;
    int itb = 1;
    for(int i = 1; i <= n;++i)
    {
        cmp(A[ita++],B[itb++]);
        if(ita > a) ita -= a;
        if(itb > b) itb -= b;
    }
    std::cout << scoA << ' ' << scoB;

    return 0;
}

#endif
