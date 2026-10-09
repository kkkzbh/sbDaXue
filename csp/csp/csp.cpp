#define _CRT_SECURE_NO_WARNINGS





//
//#include<iostream>
//#include<cstdio>
//
//using namespace std;
//
//#define ROW 100
//#define COW 4
//
//int main()
//{
//	int n = 0, a = 0, b = 0;
//	std::cin >> n >> a >> b;
//	int arr[ROW][COW] = { 0 };
//	int i = 0;
//	for (i = 0;i < n;i++)
//	{
//		cin >> arr[i][0] >> arr[i][1] >> arr[i][2] >> arr[i][3];
//		
//	}
//	int S = 0;
//	for (i = 0;i < n;i++)
//	{
//		if (arr[i][0] < a && arr[i][3] > 0 && arr[i][1] < b && arr[i][2] > 0) //是否相交 相交了在进行内部计算
//		{
//			int rmpx = arr[i][0] > 0 ? arr[i][0] : 0;
//			int rmpy = arr[i][1] > 0 ? arr[i][1] : 0;
//			int tmpx = (arr[i][2] > a ? a : arr[i][2]) - rmpx;
//			int tmpy = (arr[i][3] > b ? b : arr[i][3]) - rmpy;
//			S += tmpx * tmpy;
//		}
//	}
//	cout << S;
//
//	return 0;
//}

//
//
//#include<iostream>
//
//using namespace std;
//using Z = int;
//
//int main()
//{
//	int n = 0,k = 0;
//	Z m = 0;
//	cin >> n >> m >> k;
//	Z(*arr)[2] = (Z(*)[2])malloc(n * sizeof(Z[2]));
//
//	for (int i = 0; i < n;i++)
//	{
//		cin >> arr[i][0] >> arr[i][1];
//	}
//	int find = 0;
//	while (!find)
//	{
//		Z max = 0;
//		for (int i = 1; i < n && !find;i++)
//		{
//			if (arr[max][0] < arr[i][0])
//			{
//				max = i;
//			}
//		}
//		if (m - arr[max][1] >= 0)
//		{
//			arr[max][0]--;
//			m -= arr[max][1];
//		}
//		else
//		{
//			find = 1;
//		}
//	}
//	Z max = arr[0][0];
//	for (int i = 1; i < n;i++)
//	{
//		if(max < arr[i][0])
//		max = arr[i][0];
//	}
//	cout << max;
//
//	return 0;
//}
//
//
//
//






//
//if (arr[min][0] > k && (m - arr[min][1] > 0))
//{
//
//	while (arr[min][0] > k && (m - arr[min][1] >= 0))
//	{
//		arr[min][0]--;
//		m -= arr[min][1];
//	}
//	if (m <= 0)
//	{
//		find = 1;
//		arr[min][1] = 100001;
//	}
//	else
//	{
//		arr[min][1] = 100001;
//	}
//}