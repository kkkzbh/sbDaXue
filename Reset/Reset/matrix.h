#pragma once

#include<iostream>

class matrix
{
public:
	matrix Transpose(); //转置
	void input();	//输入
	void output();	//输出

	//寻找最大值
	int FindMax();
	int FindMax(int& a, int& b);
	int FindMax(int* a, int* b);

private:
	int m;
	int n;
	int** mat;

public:
	matrix(int a, int b);
	matrix(matrix& M);
	~matrix();
};