#define _CRT_SECURE_NO_WARNINGS

#define MENUR 13
#define MENUL 51

#define BOARDUP 2
#define BOARDDOWN 9
#define BOARDLEFT 4
#define BOARDRIGHT 45


#define NAME 16
#define SEX 8

#define PERSON 100

#define DEFAULT_COUNT 5
#define ADD_COUNT 5



#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>



typedef struct Person
{
	long long id;
	char name[NAME];
	char sex[SEX];
	long long phone;

}Person;

typedef struct Contact
{
	Person* a;
	int sz;
	int count;
}Contact;


enum select
{
	EXIT,
	print,
	search,
	add,
	del,
	sort,
	modify,
};

void menu(char(*a)[MENUL]);

void pmenu(char(*a)[MENUL]);

void Print(Contact* x);

void Add(Contact* x);

void Search(Contact* x);

void Delete(Contact* x);

void Sort(Contact* x);

void IniContact(Contact* x);

void ModifyContent(Contact* x);

void Modify(Contact* x);

void Exit(Contact* x);