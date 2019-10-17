#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct nod
{
	int val;
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

void adaugare_inceput(nod *&p, int valcrt)
{
	if (p == NULL)
	{
		p = new nod;
		p->val = valcrt;
		p->urm = NULL;
		return;
	}
	nod *a = new nod;
	a->val = valcrt;
	a->urm = p;
	p = a;
}

void adaugare_final(nod *&p, int valcrt)
{
	if (p == NULL)
	{
		p = new nod;
		p->val = valcrt;
		p->urm = NULL;
		return;
	}
	nod *c = p;
	while (c->urm)
		c = c->urm;
	nod *a = new nod;
	a->val = valcrt;
	a->urm = NULL;
	c->urm = a;
}

void eliminare_inceput(nod *&p)
{
	if (p == NULL)
		return;

	nod *a = p;
	p = p->urm;
	delete(a);
}

void eliminare_final(nod *&p)
{
	if (p == NULL)
		return;
	if (p->urm == NULL)
	{
		p = NULL;
		return;
	}
	nod *c = p;
	while (c->urm->urm)
		c = c->urm;
	c->urm = NULL;
}

int main()
{
	nod *Start = NULL;
	adaugare_inceput(Start, 1);
	adaugare_inceput(Start, 2);
	adaugare_final(Start, 3);
	adaugare_final(Start, 4);
	afisare(Start);
	eliminare_inceput(Start);
	afisare(Start);
	eliminare_final(Start);
	afisare(Start);
	eliminare_final(Start);
	afisare(Start);
	eliminare_final(Start);
	afisare(Start);
	eliminare_final(Start);
	afisare(Start);
	eliminare_final(Start);
	afisare(Start);
	eliminare_final(Start);
	afisare(Start);
	return 0;
}