#define _CRT_SECURE_NO_WARNINGS
#pragma once



#define HA 3
#define LE 3


#define HH 9
#define LL 9
#define HHS 11
#define LLS 11
#define BOM 10



#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>



void menu();
void game1();
void priQB(char arr[HA][LE], int x, int y);
void PlayerMove(char arr[HA][LE], int a, int b);
void ComputerMove(char arr[HA][LE], int m, int n);
int IsTie(char arr[HA][LE], int m, int n);
char IsWin(char arr[HA][LE], int n, int m);





void game2();
void AddBOOM(char b[HHS][LLS], int A, int B);
void InitiaBOOM(char show[HHS][LLS], int A, int B, char set);
void printBOOM(char X[HHS][LLS], int x, int y);
char FindBOOM(char show[HHS][LLS], char bm[HHS][LLS], int x, int y);
void Amazeing(char show[HHS][LLS], char bm[HHS][LLS], int x, int y);
void scanBOOM(char show[HHS][LLS], char bm[HHS][LLS], int A, int B);








