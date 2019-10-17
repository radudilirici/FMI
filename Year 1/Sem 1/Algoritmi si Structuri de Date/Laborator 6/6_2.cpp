#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct nod
{
	int val, prioritate;
	nod *urm;
};

void afisare(nod *p)
{
	while (p)
	{
		printf("%d ", p->val);
		p = p->urm;
	}
	printf("\n");
}

void adaugare(nod *&p, int valcrt, int prioritatecrt)
{
	if (p == NULL)
	{
		p = new nod;
		p->val = valcrt;
		p->prioritate = prioritatecrt;
		p->urm = NULL;
		return;
	}

	if (prioritatecrt < p->prioritate)
	{
		nod *a = new nod;
		a->val = valcrt;
		a->prioritate = prioritatecrt;
		a->urm = p;
		p = a;
		return;
	}

	nod *c = p;
	while (c->urm)
		if (c->urm->prioritate <= prioritatecrt)
			c = c->urm;
		else
			break;

	nod *a = new nod;
	a->val = valcrt;
	a->prioritate = prioritatecrt;
	a->urm = c->urm;
	c->urm = a;
}

void eliminare(nod *&p, int prioritatecrt)
{
	if (p->prioritate > prioritatecrt)
		return;

	if (p->prioritate == prioritatecrt)
	{
		nod *a = p;
		p = p->urm;
		delete(a);
		return;
	}

	nod *c = p;
	while (c->urm)
		if (c->urm->prioritate < prioritatecrt)
			c = c->urm;
		else
			break;

	if (c->urm == NULL)
		return;

	nod *a = c->urm;
	c->urm = c->urm->urm;
	delete(a);
}

int main()
{
	nod *prim = NULL;
	adaugare(prim, 1, 2);
	adaugare(prim, 2, 2);
	adaugare(prim, 3, 1);
	adaugare(prim, 4, 1);
	adaugare(prim, 5, 3);
	adaugare(prim, 6, 6);
	adaugare(prim, 7, 4);
	eliminare(prim, 1);
	afisare(prim);
	return 0;
}