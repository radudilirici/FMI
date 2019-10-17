#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct nod
{
	int val;
	nod *prev, *next;
};

void afisare_in_ordine(nod *p)
{
	while (p)
	{
		printf("%d ", p->val);
		p = p->next;
	}
	printf("\n");
}

void afisare_inversa(nod *p)
{
	while (p->next)
		p = p->next;
	while (p)
	{
		printf("%d ", p->val);
		p = p->prev;
	}
	printf("\n");
}

void adaugare_inceput(nod *&p, int valcrt)
{
	if (p == NULL)
	{
		p = new nod;
		p->val = valcrt;
		p->prev = NULL;
		p->next = NULL;
		return;
	}
	nod *a = new nod;
	a->val = valcrt;
	a->next = p;
	a->prev = NULL;
	p->prev = a;
	p = a;
}

void adaugare_final(nod *&p, int valcrt)
{
	if (p == NULL)
	{
		p = new nod;
		p->val = valcrt;
		p->prev = NULL;
		p->next = NULL;
		return;
	}
	nod *c = p;
	while (c->next)
		c = c->next;
	nod *a = new nod;
	a->val = valcrt;
	a->next = NULL;
	a->prev = c;
	c->next = a;
}

void adaugare_pe_pozitie(nod *&p, int valcrt, int pozitie)
{
	if (pozitie <= 1)
	{
		nod *a = new nod;
		a->val = valcrt;
		a->next = p;
		a->prev = NULL;
		p->prev = a;
		p = a;
		return;
	}

	nod *c = p;
	int i;
	for (i=2; i<pozitie && c->next; i++)
		c = c->next;
	nod *urm = c->next;

	if (urm == NULL)
	{
		nod *a = new nod;
		a->val = valcrt;
		a->next = NULL;
		a->prev = c;
		c->next = a;
		return;
	}

	nod *a = new nod;
	a->val = valcrt;
	c->next = a;
	a->prev = c;
	a->next = urm;
	urm->prev = a;
}

void eliminare_dupa_pozitie(nod *&p, int pozitie)
{
	if (pozitie <= 1)
	{
		nod *a = p;
		p = p->next;
		p->prev = NULL;
		delete(a);
		return;
	}
	nod *c = p;
	int i;
	for (i=1; i<pozitie && c->next; i++)
		c = c->next;
	nod *ult = c->prev;
	nod *urm = c->next;
	ult->next = urm;
	if (urm)
		urm->prev = ult;
	delete(c);
}

void eliminare_dupa_valoare(nod *&p, int valcrt)
{
	if (p->val == valcrt)
	{
		nod *a = p;
		p = p->next;
		p->prev = NULL;
		delete(a);
		return;
	}
	nod *c = p;
	while (c->val != valcrt && c->next)
		c = c->next;
	if (c->next == NULL)
		return;
	nod *ult = c->prev;
	nod *urm = c->next;
	ult->next = urm;
	if (urm)
		urm->prev = ult;
	delete(c);
}

int main()
{
	nod *prim = NULL;
	int optiune, valcrt, pozitie;
	do
	{
		printf("\nAlegeti Optiunea:\n1. Adaugarea unui element la inceput\n2. Adaugarea unui element la final\n3. Adaugarea unui element pe o anumita pozitie\n4. Afisarea elementelor\n5. Afisarea inversa a elementelor\n6. Stergerea unui element dupa pozititie\n7. Stergerea unui element dupa valoare\n0. Iesire\n\n");
		scanf("%d", &optiune);
		switch (optiune)
		{
			case 1: printf("Valoare: "); scanf("%d", &valcrt); adaugare_inceput(prim, valcrt); break;
			case 2: printf("Valoare: "); scanf("%d", &valcrt); adaugare_final(prim, valcrt); break;
			case 3: printf("Valoare, Pozitie: "); scanf("%d %d", &valcrt, &pozitie); adaugare_pe_pozitie(prim, valcrt, pozitie); break;
			case 4: afisare_in_ordine(prim); break;
			case 5: afisare_inversa(prim); break;
			case 6: printf("Pozitie: "); scanf("%d", &pozitie); eliminare_dupa_pozitie(prim, pozitie); break;
			case 7: printf("Valoare: "); scanf("%d", &valcrt); eliminare_dupa_valoare(prim, valcrt); break;
			case 0: break;
			default: optiune = 0; break;
		}
	}while(optiune > 0);
	return 0;
}