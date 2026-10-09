#define _CRT_SECURE_NO_WARNINGS


//bool isLeapYear(int& year)
//{
//	//if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
//		//return true;
//	//return false;
//	return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
//}
//
//void DayofYear(int year, int month, int* pDay)
//{
//	bool x = isLeapYear(year);
//	int a[2][12]{ 31,28,31,30,31,30,31,31,30,31,30,31 };
//	memcpy(a[1], a[0], 12 * sizeof(int));
//	a[1][1] = 29;
//	for (int i = 0;i < month-1;i++)
//	{
//		*pDay += a[x][i];
//	}
//}
//
//int main()
//{
//	int year, month, day;
//
//	cin >> year >> month >> day;
//	//记得检验输入合法性 day的范围需要考虑当前输入的是几月 去判断是否合法
//	DayofYear(year, month, &day);
//	
//	cout << day;
//
//	return 0;
//}

//
//
//bool isLeapYear(int& year)
//{
//	//if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
//		//return true;
//	//return false;
//	return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
//}
//
//
//void MonthDay(int year, int yearDay, int* pMonth, int* pDay)
//{
//	int arr[2][12]{{31,28,31,30,31,30,31,31,30,31,30,31},{ 31,29,31,30,31,30,31,31,30,31,30,31}};
//	int leap = isLeapYear(year);
//	while (yearDay > arr[leap][*pMonth])
//	{
//		yearDay -= arr[leap][(*pMonth)++];
//	}
//	*pDay = yearDay;
//	(*pMonth)++;
//}
//
//
//
//int main()
//{
//	int year,yearDay, pMonth = 0, pDay = 0;
//	cin >> year >> yearDay;
//	MonthDay(year, yearDay, &pMonth, &pDay);
//	cout << year << "年" << pMonth << "月" << pDay << "日";
//	
//	return 0;
//}

//
//void Transpose(int** a, int n)
//{
//	for (int i = 0;i < n;i++)
//	{
//		for (int j = i+1;j < n;j++)
//		{
//			a[i][j] = a[i][j] ^ a[j][i];
//			a[j][i] = a[i][j] ^ a[j][i];
//			a[i][j] = a[i][j] ^ a[j][i];	//小心按位异或自己！！！
//		}
//	}
//
//
//
//}
//
//int main()
//{
//	int n = 0;
//	cout << "n :>";
//	cin >> n;
//	int**a = new int*[n];
//	for (int i = 0;i<n;i++)
//	{
//		a[i] = new int[n];
//	}
//	for (int i = 0;i < n;i++)
//	{
//		for (int j = 0;j < n;j++)
//		{
//			cin >> a[i][j];
//		}
//	}
//
//	Transpose(a, n);
//
//	for (int i = 0;i < n;i++)
//	{
//		for (int j = 0;j < n;j++)
//		{
//			cout << a[i][j] << ' ';
//		}
//		cout << "\n";
//	}
//
//	return 0;
//}
//
//void Swap(int& x, int& y)
//{
//	x = x ^ y;
//	y = x ^ y;
//	x = x ^ y;
//}
//
//
//void Transpose(int** a,int **b, int m, int n)
//{
//	for (int i = 0;i < n;i++)
//	{
//		for (int j = 0;j < m;j++)
//		{
//			b[i][j] = a[j][i];
//		}
//	}
//}
//
//
//int main()
//{
//	freopen("./data.dat", "r+", stdin);
//
//	int m, n;
//	cin >> m >> n;
//	int max = m > n ? m : n;
//	int** a = new int* [m];
//
//	for (int i = 0;i < m;i++)
//	{
//		a[i] = new int[n];
//	}
//
//	int** b = new int* [n];
//
//	for (int i = 0;i < n;i++)
//	{
//		b[i] = new int[m];
//	}
//
//	for (int i = 0;i < m;i++)
//	{
//		for (int j = 0;j < n;j++)
//		{
//			cin >> a[i][j];
//		}
//	}
//
//	Transpose(a,b, m, n);
//
//	for (int i = 0; i < n;i++)
//	{
//		for (int j = 0;j < m;j++)
//		{
//			cout << b[i][j] << ' ';
//		}
//		cout << '\n';
//	}
//
//
//
//	return 0;
//}


//#include"main.h"
//
//int main()
//{
//	int a = 2;
//	int b = 3;
//	scanf("%d%d", &a,&b);
//
//
//
//	return 0;
//}
//
//#include "main.h"
//


//#include<iostream>
//
//using namespace std;
//
//int Fib(int n)
//{
//	if (1 == n || 2 == n)
//		return 1;
//	else if (n <= 0)
//		return -1;
//	int x1 = 1;
//	int x2 = 1;
//	int x3 = 0;
//	for (int i = 3;i <= n;i++)
//	{
//		x3 = x1 + x2;
//		x1 = x2;
//		x2 = x3;
//	}
//	return x3;
//}
//
//
//int main()
//{
//	int n;
//	cin >> n;
//	int ret = Fib(n);
//	cout << ret;
//
//	return 0;
//}

//
//#include<iostream>
//
//using namespace std;
//
//int f(int* a, int n)
//{
//	int i = 0;
//	int j = 0;
//	int find = 0;
//	for (i = n - 2;a[i] > a[i + 1] && i != -1;i--);
//	if (i != -1)
//	{
//		for (j = n - 1;a[j] < a[i] && j;j--);
//		a[i] = a[i] ^ a[j];
//		a[j] = a[i] ^ a[j];
//		a[i] = a[i] ^ a[j];
//		for (i++;i < n - i;i++)
//		{
//			a[i] = a[i] ^ a[n - i];
//			a[n - i] = a[i] ^ a[n - i];
//			a[i] = a[i] ^ a[n - i];
//		}
//		find = 1;
//	}
//	return find;
//}
//
//
//int main()
//{
//	int a[10]{ 2,8,9,6,5,7,3,1,0,4 };
//	int n = sizeof(a) / sizeof(a[0]);
//
//	for (int i = 0;i < n;i++)
//	{
//		cout << a[i] << ' ';
//	}
//	cout << "\n";
//
//	for (cout << "-------------------\n";f(a, n);cout << "--------------------\n")
//	{
//		for (int i = 0;i < n;i++)
//		{
//			cout << a[i] << ' ';
//		}
//		cout << "\n";
//	}
//
//	return 0;
//}




//#include<iostream>
//#include<windows.h>
//
//
//
//using namespace std;
//
//struct Clock
//{
//	int hour;
//	int minute;
//	int second;
//
//	void print()
//	{
//		std::cout << hour << ":" << minute << ":" << second << std::endl;
//	}
//	void add()
//	{
//		second += 1;
//		if (60 == second)
//		{
//			second = 0;
//			minute++;
//		}
//		if (60 == minute)
//		{
//			minute = 0;
//			hour++;
//		}
//		hour == 24 ? 0 : hour;
//	}
//	Clock() :hour(12), minute(0), second(0){}
//};
//
//
//int main()
//{
//	Clock c;
//	while (1)
//	{
//		c.print();
//		Sleep(1000);
//		c.add();
//	}
//	
//	return 0;
//}
//
//
//#include <iostream>
//
//using namespace std;
//
//struct i
//{
//	int a;
//	int b;
//
//
//	i operator* (const i& x)
//	{
//		i ret;
//		ret.a = a * x.a - b * x.b;
//		ret.b = a * x.b + b * x.a;
//		return ret;
//	}
//
//	void scan()
//	{
//		cin >> a >> b;
//	}
//
//	ostream& print()
//	{
//		std::cout << a << '+' << b << 'i';
//		return std::cout;
//	}
//
//	i():a(0),b(0){}
//};
//
//int main()
//{
//	i x1;
//	x1.scan();
//	i x2;
//	x2.scan();
//	i x3 = x1 * x2;
//	x1.print() << endl;
//	x2.print() << endl;
//	cout << "乘积 :";
//
//	x3.print() << endl;
//	return 0;
//}
//#include<iostream>
//#include<cstdlib>
//#include<cstring>
//#include<ctime>
//
//using namespace std;
//
//
//int main()
//{
//	int a = 5;
//
//	(a = a) = 10;
//	printf("%x", a);
//
//	return 0;
//}

//
//#include<iostream>
//using namespace std;
//
//class Int
//{
//	friend Int operator+(Int& a, Int& b);
//public:
//	Int(int n = 0) :x(n)
//	{
//		std::cout << "调用构造函数" << std::endl;
//	}
//	Int(const Int& n):x(n.x)
//	{
//		std::cout << x << "  调用拷贝函数" << std::endl;
//		x = 100;
//	}
//
//	~Int()
//	{
//		std::cout <<"数值为:" << x << "  调用析构函数" << std::endl;
//	}
//
//	int get()
//	{
//		return x;
//	}
//
//	Int& operator=(Int &n)
//	{
//		std::cout << "调用等号" << std::endl;
//	}
//
//	virtual void bark()
//	{
//		std::cout << "Int狗叫" << std::endl;
//	}
//
//
//
//	static int A;
//
//private:
//	int x;
//};
//int Int::A;
//
//class Dog : public Int
//{
//public:
//	Dog(int a = 0):m_A(a){}
//	void bark() override
//	{
//		std::cout << "Dog 狗叫" << std::endl;
//	}
//	int m_A;
//};
//
//
//class BadDog : public Dog
//{
//	void bark() override
//	{
//		std::cout << "Bad Dog狗叫\n";
//	}
//};
//
//
//Int operator+(Int & a,Int & b)
//{
//	Int c(0);
//	c.x = a.x + b.x;
//	return c;
//}
//
//ostream& operator << (ostream & cout, Int& x)
//{
//	cout << x.get();
//	return cout;
//}
//
//Int Add(Int x, Int y)
//{
//	Int d = x + y;
//	return d;
//}
//
//class P : public Int
//{
//	static int A;
//};
//int P::A;
//
//
//int Add(int, int);
//
//int main()
//{
//	
//
//
//	return 0;
//}
//




//
//#include<iostream>
//
//using namespace std;
//
//class animal
//{
//public:
//    int m_A;
//    int m_B;
//    int m_C;
//
//    void bark()
//    {
//        std::cout << "动物叫\n";
//    }
//};
//
//class Dog : public animal
//{
//public:
//    int m_Age;
//    void bark()
//    {
//        std::cout << "狗叫\n";
//    }
//};
//
////class Cat : virtual public animal
////{
////public:
////    int m_Age;
////    void bark() override
////    {
////        std::cout << "猫叫\n";
////    }
////};
//
//class DC : public Dog  /*virtual public Cat*/
//{
//public:
//    int m_Age;
//};
//
//void AnimalBark(animal& animal)
//{
//    animal.bark();
//}
//
//int main()
//{
//    animal ani;
//    Dog dog;
//    DC dc;
//
//    Dog* pdog = &dc;
//
//    return 0;
//}

#include<iostream>

class A
{
public:
	int m_A;


public:
	A(int n = 0) : m_A(n)
	{
		std::cout << "Create A! \n";
	}
	~A(){}

	virtual void bark()
	{
		std::cout << "A\n";
	}
};

class AA :virtual public A
{
public:
	int m_AA;

public:
	virtual void bark()
	{
		std::cout << "AA !\n";
	}
};

class B : virtual public A
{
public:
	int m_B;


public:
	B(int n = 0):m_B(666)
	{
		std::cout << "Create B! \n";
	}
	~B(){}

	virtual void bark()
	{
		std::cout << "B\n";
	}
	//virtual void bb()
	//{
	//	std::cout << "B bb \n";
	//}
};

class RET : public AA,public B
{
public:
	int m_RET;


public:
	virtual void bark()
	{
		std::cout << "RET \n";
	}
	virtual void Hello()
	{
		std::cout << "Hello world\n";
	}
};


int main()
{
	RET ret;
	std::cin.get();
	system("pause");
	return 0;
}