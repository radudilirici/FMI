#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct nod
{
	int val;
	nod *urm;
};

void afisare(nod *Start)
{
	Start = Start->urm;
	while (Start)
	{
		printf("%d ", Start->val);
		Start = Start->urm;
	}
	printf("\n");
}

void adaugare_inceput(nod *&Start, int valcrt)
{
	if (Start->urm == NULL)
	{
		nod *a = new nod;
		a->val = valcrt;
		a->urm = NULL;
		Start->urm = a;
		return;
	}
	nod *a = new nod;
	a->val = valcrt;
	a->urm = Start->urm;
	Start->urm = a;
}

void adaugare_final(nod *&Start, int valcrt)
{
	if (Start->urm == NULL)
	{
		nod *a = new nod;
		a->val = valcrt;
		a->urm = NULL;
		Start->urm = a;
		return;
	}
	nod *c = Start->urm;
	while (c->urm)
		c = c->urm;
	nod *a = new nod;
	a->val = valcrt;
	a->urm = NULL;
	c->urm = a;
}

void eliminare_inceput(nod *&Start)
{
	if (Start->urm == NULL)
		return;

	nod *a = Start->urm;
	Start->urm = Start->urm->urm;
	delete(a);
}

void eliminare_final(nod *&Start)
{
	if (Start->urm == NULL)
		return;
	if (Start->urm->urm == NULL)
	{
		Start->urm = NULL;
		return;
	}
	nod *c = Start->urm;
	while (c->urm->urm)
		c = c->urm;
	c->urm = NULL;
}

int main()
{
	nod *Start = new nod;
	Start->val =  0;
	Start->urm = NULL;

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