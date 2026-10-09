

#include"matrix.h"

//¹¹Ôìº¯Êý
matrix::matrix(int a, int b) :m(a), n(b)
{
	mat = new int* [m];
	for (int i = 0;i < m;i++)
	{
		mat[i] = new int[n];
		for (int j = 0;j < n;j++)
		{
			mat[i][j] = 0;
		}
	}
}
matrix::matrix(matrix& M)
{
	m = M.m;
	n = M.n;
	mat = new int* [m];
	for (int i = 0;i < m;i++)
	{
		mat[i] = new int[n];
		for (int j = 0;j < n;j++)
		{
			mat[i][j] = M.mat[i][j];
		}
	}
}
matrix::~matrix()
{
	for (int i = 0;i < m;i++)
	{
		delete[] mat[i];
	}
	delete[] mat;
}



//


matrix matrix::Transpose()
{
	matrix M(n, m);
	for (int i = 0;i < m;i++)
	{
		for (int j = 0;j < n;j++)
		{
			M.mat[j][i] = mat[i][j];
		}
	}
	return M;
}

void matrix::input()
{
	for (int i = 0;i < m;i++)
	{
		for (int j = 0;j < n;j++)
		{
			std::cin >> mat[i][j];
		}
	}
}

void matrix::output()
{
	for (int i = 0;i < m;i++)
	{
		for (int j = 0;j < n;j++)
		{
			std::cout << mat[i][j] << " ";
		}
		std::cout << "\n";
	}
}

int matrix::FindMax()
{
	int max = mat[0][0];
	for (int i = 0;i < m;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (mat[i][j] > max)
			{
				max = mat[i][j];
			}
		}
	}
	return max;
}
int matrix::FindMax(int& a, int& b)
{
	int max = mat[0][0];
	for (int i = 0;i < m;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (mat[i][j] > max)
			{
				max = mat[i][j];
				a = i;
				b = j;
			}
		}
	}
	return max;
}
int matrix::FindMax(int* a, int* b)
{
	int max = mat[0][0];
	for (int i = 0;i < m;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (mat[i][j] > max)
			{
				max = mat[i][j];
				*a = i;
				*b = j;
			}
		}
	}
	return max;
}