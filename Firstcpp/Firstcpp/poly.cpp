


#include "link.h"


polyptr Create()
{
	return make_shared<poly>();
}

polyptr PushPoly(double cof, double idx, polyptr position)
{
	polyptr note = make_shared<poly>();
	polyptr tmp = position->Next;
	note->coeff = cof;
	note->index = idx;
	position->Next = note;
	note->Next = tmp;
	return note;
}

void PrintPoly(polyptr Poly)
{
	Poly = Poly->Next;
	while (nullptr != Poly->Next)
	{
		cout << Poly->coeff << "x" << Poly->index << " + ";
		Poly = Poly->Next;
	}
	if(Poly->index)
		cout << Poly->coeff << "x" << Poly->index << endl;
	else
		cout << Poly->coeff << endl;
}


polyptr ADD(polyptr Poly1, polyptr Poly2)
{
	Poly1 = Poly1->Next;
	Poly2 = Poly2->Next;
	polyptr add = Create();
	polyptr late = add;
	while (Poly1 && Poly2)
	{
		if (Poly1->index > Poly2->index)
		{
			late = PushPoly(Poly1->coeff, Poly1->index, late);
			Poly1 = Poly1->Next;
		}
		else if (Poly1->index < Poly2->index)
		{
			late = PushPoly(Poly2->coeff, Poly2->index, late);
			Poly2 = Poly2->Next;
		}
		else
		{
			late = PushPoly(Poly1->coeff + Poly2->coeff, Poly1->index + Poly2->index, late);
			Poly1 = Poly1->Next;
			Poly2 = Poly2->Next;
		}
	}
	for (;Poly1;Poly1 = Poly1->Next) late = PushPoly(Poly1->coeff, Poly1->index, late);
	for (;Poly2;Poly2 = Poly2->Next) late = PushPoly(Poly2->coeff, Poly2->index, late);
	return add;
}


polyptr MUL(polyptr Poly1, polyptr Poly2)
{
	Poly1 = Poly1->Next;
	Poly2 = Poly2->Next;
	polyptr mul = Create();
	polyptr late = mul;
	while (Poly1)
	{
		polyptr tmp = Poly2;
		while (tmp)
		{
			poly note;
			note.coeff = Poly1->coeff * tmp->coeff;
			note.index = Poly1->index + tmp->index;
			int flag = 0;
			while (late->Next && !flag)
			{
				if (note.index > late->Next->index)
				{
					late = PushPoly(note.coeff, note.index, late);
					late = late->Next;
					flag = 1;
				}
				else if (note.index < late->Next->index)
				{
					late = late->Next;
				}
				else
				{
					late->Next->coeff += note.coeff;
					late = late->Next;
					flag = 1;
				}
			}
			if (!flag)
			{
				PushPoly(note.coeff, note.index, late);
			}
			tmp = tmp->Next;
		}
		Poly1 = Poly1->Next;
		late = mul;
	}

	return mul;
}


