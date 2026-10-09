#include"List.hpp"


//DoubleList----------------------------------------------------

DoubleList::DoubleList(const int n){}

DoubleList::~DoubleList(){}

void DoubleList::push_back(const int n)
{
	Dnote* it = this;
	Dnote* tmp = new Dnote(n);
	while (it->next)
	{
		it = it->next;
	}
	it->next = tmp;
	tmp->last = it;
}



















//DoubleList----------------------------------------------------