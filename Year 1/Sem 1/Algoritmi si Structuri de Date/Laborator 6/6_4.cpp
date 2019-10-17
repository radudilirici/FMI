#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct nod
{
	int val;
	nod *ant, *urm;
};

void afisare(nod *Start)
{
	if (Start->urm == NULL)
	{
		printf("\n");
		return;
	}
	nod *c = Start->urm;
	while (c != Start)
	{
		printf("%d ", c->val);
		c = c->urm;
	}
	printf("\n");
}

void adaugare_dupa_pozitie(nod *&Start, int valcrt, int pozitie)
{
	if (Start->urm == NULL)
	{
		nod *a = new nod;
		a->val = valcrt;
		a->ant = Start;
		a->urm = Start;
		Start->urm = a;
		Start->ant = a;
		return;
	}

	int i;
	nod *c = Start;
	for (i=1; i<pozitie; i++)
        c = c->urm;

	nod *p = c->urm;
	nod *a = new nod;
	a->val = valcrt;
	a->urm = p;
	p->ant = a;
	a->ant = c;
	c->urm = a;
}

void eliminare_dupa_pozitie(nod *&Start, int pozitie)
{
	if (Start->urm == NULL)
		return;
	if (Start->urm->urm == Start)
	{
		Start->urm = NULL;
		return;
	}

	int i;
	nod *c = Start;
	for (i=1; i<pozitie; i++)
        c = c->urm;

	nod *a = c->urm;
	nod *p = a->urm;
	c->urm = p;
	p->ant = c;
	delete(a);
}

int main()
{
	nod *Start = new nod;
	Start->val = 0;
	Start->urm = NULL;
	Start->ant = NULL;
	adaugare_dupa_pozitie(Start, 1, 1);
	adaugare_dupa_pozitie(Start, 7, 1);
	adaugare_dupa_pozitie(Start, 3, 2);
	adaugare_dupa_pozitie(Start, 10, 4);
	afisare(Start);
	eliminare_dupa_pozitie(Start, 2);
	afisare(Start);
	eliminare_dupa_pozitie(Start, 3);
	afisare(Start);
	eliminare_dupa_pozitie(Start, 1);
	afisare(Start);
	eliminare_dupa_pozitie(Start, 10);
	afisare(Start);
	return 0;
}
