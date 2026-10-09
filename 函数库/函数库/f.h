#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>


#define NN 100
#define NNN 1000


int Z(int n);


int GCD(int a, int b);


int LCM(int a, int b);


int JS(int n);


int SumPrime(int x);


int WS(int x);


int C(int m, int n);


double myPOW(int x, int n);


void BubbleSort(int* arr, int sz);


int GCD2(int x, int y);


void Swap(char* e1, char* e2, int width);


void bubble_sort(void* base, int sz, int width, int (*cmp)(void* e1, void* e2));


int Int(int* e1, int* e2);


int Str(char* e1, char* e2);


void GenerateMagicSquare(int(*arr)[NN], int n);


void ini_yang(int(*arr)[NN], int n);


void print_yang(int(*arr)[NN], int n);


void print_yang_b(int(*arr)[NN], int n);


void yang_fib(int(*arr)[NN], int* Fib, int n);


void printYfib(int* Fib, int n);


void getZ(int* arr, int n);


void IniSnakeSquare(int(*arr)[NN], int n);


void printNxN(int(*arr)[NN], int n);


double Qinxn1(int n, double* arr, double x);


double Qinxn2(int n, double* arr, double x);


double Qinxn3(int n, double* arr, double x);


unsigned long long Hanoi(int n);


void IniArr1(int* arr, int n);


void PriArr1(int* arr, int n);


void ExchangeSort(int* arr, int n);


void SelectionSort(int* arr, int n);


void RemarkArr(const int* arr, const int n, int* brr);


void Zerofront(int* arr, int n);


int MaxFind(int* arr, int n);


int ModeFind(int* arr, int n, int max);


int MedianFind(const int* arr, int n);


void FindMNmax(int m, int n, int(*arr)[NN], int ret[3]);


void IniMN(int m, int n, int(*arr)[NN]);


int FindSaPoint(int m, int n, int(*arr)[NN], int* ret);


void Cablake(int n);


void CombineArr(int* a, int* b, int m, int n, int* c);


int MinFind(int* arr, int n);


int ZeroBack(int* arr, int n);


void EqalZero(int* arr, int n);


int BigPointSort(int* arr, int n);


void ShowBpS(int* arr, int n);


int Strcmp(const char* dst, const char* src);


int Strncmp(const char* dst, const char* src, size_t n);


char* Strcpy(char* dst, const char* src);


char* Strncpy(char* dst, const char* src, size_t n);


char* Strcat(char* dst, const char* src);


char* Strncat(char* dst, const char* src, size_t n);


size_t Strlen(char* str);


char* Strstr(const char* dst, const char* src);


char* Strtok(char* str, const char* sep);


void* Memcpy(void* dst, const void* src, size_t n);


void* Memmove(void* dst, const void* src, size_t n);


void* Memcmp(const void* s1, const void* s2, size_t num);


int Gcd(int a, int b);