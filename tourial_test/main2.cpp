

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int add(int x, int y);

auto main() -> int
{
	int a   = 2;
	int b   = 3;
	int ans = add(a, b);
	printf("the sum of a and b is %d", ans);
}