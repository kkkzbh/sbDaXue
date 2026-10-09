

#include<iostream>

struct note
{
public:
	int x;
	note* next;

public:
	note(const int n = 0) : x(n), next(nullptr) {}
	~note(){}
};

struct Dnote
{
public:
	int x;
	Dnote* last;
	Dnote* next;
public:
	Dnote(const int n = 0) :x(n), last(nullptr), next(nullptr) {}
	~Dnote(){}
};


class List :public note
{
protected:


public:
	void push_back(const int n);
	void push_in(const int n);
	std::ostream& print() const;
	std::ostream& print(List* P) const = delete;
	note* Find(const int n) const;
	void Del(const int location);
	void Swap(const int loa, const int lob);
	void Swap(const int lo);

public:
	List(const int n = 0);
	~List();

};

class DoubleList : public Dnote
{
protected:


public:
	void push_back(const int n);

public:
	DoubleList(const int n = 0);
	~DoubleList();
};
using DList = DoubleList;

