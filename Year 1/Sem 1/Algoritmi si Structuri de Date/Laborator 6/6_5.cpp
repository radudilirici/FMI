#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct nod
{
	int val;
	nod *ant, *urm;
};

//este echivalentul unei cozi

void afisare(nod *Start)
{
	if (Start->urm == NULL)
	{
		printf("\n");
		return;
	}
	Start = Start->urm;
	nod *c = Start;
	do
	{
		printf("%d ", c->val);
		c = c->urm;
	}while (c != Start);
	printf("\n");
}

void adaugare(nod *&Start, int valcrt)
{
	if (Start->urm == NULL)
	{
		nod *a = new nod;
		a->val = valcrt;
		a->ant = a;
		a->urm = a;
		Start->urm = a;
		return;
	}

	nod *p = Start->urm;
	nod *u = p->ant;
	nod *a = new nod;
	a->val = valcrt;
	a->urm = p;
	p->ant = a;
	a->ant = u;
	u->urm = a;
	Start->urm = a;
}

void eliminare(nod *&Start)
{
	if (Start->urm == NULL)
		return;
	if (Start->urm->urm == Start->urm)
	{
		Start->urm = NULL;
		return;
	}
	nod *p = Start->urm;
	nod *a = p->ant;
	nod *u = a->ant;
	p->ant = u;
	u->urm = p;
	delete(a);
}

int main()
{
	nod *Start = new nod;
	Start->val = 0;
	Start->urm = NULL;
	Start->ant = NULL;
	adaugare(Start, 1);
	adaugare(Start, 7);
	adaugare(Start, 3);
	adaugare(Start, 10);
	afisare(Start);
	eliminare(Start);
	afisare(Start);
	eliminare(Start);
	afisare(Start);
	eliminare(Start);
	afisare(Start);
	return 0;
}
