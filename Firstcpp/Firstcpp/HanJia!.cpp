#define _CRT_SECURE_NO_WARNINGS

#include"Head.h"
#include"link.h"

int main()
{
    polyptr p1 = Create();
    polyptr p2 = Create();
    PushPoly(8, 0, p1);
    PushPoly(9, 1, p1);
    PushPoly(4, 2, p1);
    PushPoly(5, 3, p1);
    PrintPoly(p1);
    cout << "\n";
    PushPoly(2, 1, p2);
    PushPoly(3, 3, p2);
    PushPoly(7, 4, p2);
    PushPoly(4, 6, p2);
    PrintPoly(p2);
    cout << "\n";
    polyptr p3 = ADD(p1, p2);
    cout << "求和的结果为 ：";
    PrintPoly(p3);
    cout << "\n";
    cout << "求积的结果为 ：";
    p3 = MUL(p1, p2);
    PrintPoly(p3);
    cout << "\n";

    return 0;
}