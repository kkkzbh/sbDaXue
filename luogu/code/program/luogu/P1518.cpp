

#ifdef P1518

#include<iostream>
#include<array>

constexpr int size = 10 + 2;
constexpr int max = 10000000 + 10;

std::array<std::array<char,size>,size> map;


class Obj
{
public:
    int x = 0;
    int y = 0;
    int point = 0;
public:
    Obj() = default;
    void set(int a,int b)
    {
        x = a;
        y = b;
    }
    void move()
    {
        if(point == 0)
        {
            if(map[x - 1][y] == '.')
                --x;
            else if(map[x - 1][y] == '*')
                point = ++point % 4;
        }
        else if(point == 1)
        {
            if(map[x][y + 1] == '.')
                ++y;
            else if(map[x][y + 1] == '*')
                point = ++point % 4;
        }
        else if(point == 2)
        {
            if(map[x + 1][y] == '.')
                ++x;
            else if(map[x + 1][y] == '*')
                point = ++point % 4;
        }
        else if(point == 3)
        {
            if(map[x][y - 1] == '.')
                --y;
            else if(map[x][y - 1] == '*')
                point = ++point % 4;
        }
    }
};

bool isWin(Obj& a,Obj& b)
{
    return a.x == b.x && a.y == b.y;
}

void print(Obj& a,Obj& b)
{
    for(int i = 1; i <= 10;++i)
    {
        for(int j = 1; j <= 10; ++j)
        {
            if(i == a.x && j == a.y)
                std::cout << 'F';
            else if(i == b.x && j == b.y)
                std::cout << 'C';
            else std::cout << map[i][j];
            std::cout << ' ';
        }
        std::cout << '\n';
    }
}

int main()
{
    Obj J;
    Obj C;
    for(int i = 0;i<=11;++i)
    {
        for(int j = 0;j<=11;++j)
        {
            if(i == 0 || i == 11 || j == 0 || j == 11)
                map[i][j] = '*';
            else
            {
                std::cin >> map[i][j];
                if (map[i][j] == 'F')
                {
                    J.set(i, j);
                    map[i][j] = '.';
                }
                if (map[i][j] == 'C')
                {
                    C.set(i, j);
                    map[i][j] = '.';
                }
            }
        }
    }

    int count = 0;
    while(!isWin(J,C))
    {
        J.move();
        C.move();
        ++count;
        if(count > max)
        {
            std::cout << 0;
            return 0;
        }
    }
    std::cout << count;

    return 0;
}

#endif
