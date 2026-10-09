#include"List.hpp"

//List----------------------------------------------------------

List::List(const int n) {}
List::~List()
{
	note* it = this->next;
	while (it)
	{
		note* tmp = it;
		it = it->next;
		delete tmp;
	}
}

void List::push_back(const int n)
{
	note* it = this;
	note* tmp = new note(n);
	if (nullptr == tmp)
	{
		std::cerr << "Can't new a memory!\n";
		return;
	}
	while (it->next)
	{
		it = it->next;
	}
	it->next = tmp;
	x++;
}

void List::push_in(const int n)
{
	note* tmp = new note(n);
	tmp->next = this->next;
	this->next = tmp;
	x++;
}

std::ostream& List::print() const
{
	note* it = this->next;
	while (it)
	{
		std::cout << it->x << ' ';
		it = it->next;
	}
	return std::cout;
}


//std::ostream& List::print(List* P) const
//{
//	note* ita = this->next;
//	note* itb = P->next;
//	int count = 1;
//	while (ita && itb)
//	{
//		if (count++ == itb->x)
//		{
//			std::cout << ita->x << ' ';
//			itb = itb->next;
//		}
//		ita = ita->next;
//	}
//	return std::cout;
//}


note* List::Find(const int n) const
{
	note* it = this->next;
	while (it && n != it->x)
		it = it->next;
	return it;
}

void List::Del(const int location)
{
	if (location <= 0 || location > x)
		return;
	note* it = this->next;
	for (int i = 1;i != location - 1;i++, it = it->next);
	note* tmp = it->next;
	it->next = tmp->next;
	delete tmp;
	x--;
}

void List::Swap(const int loa, const int lob)
{
	if (loa == lob || loa <= 0 || lob <= 0 || loa > x || lob > x)
		return;
	note* ita = this;
	note* itb = this;
	for (int i = 1;i < loa;ita = ita->next, i++);
	for (int i = 1;i < lob;itb = itb->next, i++);
	note* itmax = loa > lob ? ita : itb;
	note* itmin = loa > lob ? itb : ita;
	note* tmpmin = itmin->next;
	note* tmpmax = itmax->next;
	note* maxback = tmpmax->next;
	itmin->next = tmpmax;
	tmpmax->next = tmpmin->next == tmpmax ? tmpmin : tmpmin->next; /**************/
	itmax->next = tmpmin;
	tmpmin->next = maxback;
}

void List::Swap(const int lo)
{
	if (lo <= 0 || lo >= x)
		return;
	note* it = this;
	for (int i = 1;i < lo;it = it->next, i++);
	note* left = it->next;
	note* right = left->next;
	it->next = right;
	left->next = right->next;
	right->next = left;
}




//List----------------------------------------------------------