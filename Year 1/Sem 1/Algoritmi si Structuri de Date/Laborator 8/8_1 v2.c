#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAX(a, b) (((a)>(b))?(a):(b))


typedef struct node
{
    int val, bal;
    struct node *st, *dr;
}nod;

void afiseaza(nod *p)
{
    if (p)
    {
        afiseaza(p->st);
        printf("%d ", p->val);
        afiseaza(p->dr);
    }
}

void RSD(nod *p)
{
    if (p)
    {
        printf("%d ", p->val);
        RSD(p->st);
        RSD(p->dr);
    }
}

void RSD_bal(nod *p)
{
    if (p)
    {
        printf("%d ", p->bal);
        RSD_bal(p->st);
        RSD_bal(p->dr);
    }
}

nod *new_node(int x)
{
    nod *a = (nod*) malloc(sizeof(nod));
    a->val = x;
    a->bal = 0;
    a->st = NULL;
    a->dr = NULL;
    return a;
}

void rotire_stanga(nod **p)
{
    nod *r = (*p)->dr;
    (*p)->dr = r->st;
    r->st = *p;
    (*p)->bal -= 1 + MAX(r->bal, 0);
    r->bal -= 1 - MIN((*p)->bal, 0);
    *p = r;
}

void rotire_dreapta(nod **p)
{
    nod *l = (*p)->st;
    (*p)->st = l->dr;
    l->dr = (*p);
    (*p)->bal += 1 - MIN(l->bal, 0);
    l->bal += 1 + MAX((*p)->bal, 0);
    *p = l;
}

void rotire_dreapta_stanga(nod **p)
{
    rotire_dreapta(&(*p)->dr);
    rotire_stanga(p);
}

void rotire_stanga_dreapta(nod **p)
{
    rotire_stanga(&(*p)->st);
    rotire_dreapta(p);
}

void echilibrare(nod **p)
{
    if ((*p)->bal == -2)
    {
        if ((*p)->st->bal == 1)
            rotire_dreapta_stanga(p);
        else
            rotire_stanga(p);
    }
    else if ((*p)->bal == 2)
    {
        if ((*p)->dr->bal == -1)
           rotire_stanga_dreapta(p);
        else
            rotire_dreapta(p);
    }
}

int adauga(nod **p, int x)
{
    if (*p == NULL)
    {
        *p = (nod*) malloc(sizeof(nod));
        p->val = x;
        p->bal = 0;
        p->st = NULL;
        p->dr = NULL;
        return 1;
    }
    if ((*p)->val == x)
        return 0;

    if (x < (*p)->val)
    {
        if (adauga(&(*p)->st, x) == 1)
            (*p)->bal--;
        else
            return 0;
    }
    else if (adauga(&(*p)->dr, x) == 1)
        (*p)->bal++;
    else
        return 0;

    if ((*p)->bal >= -1 && (*p)->bal <= 1)
        return 1;
    else
    {
        echilibrare(p);
        return 0;
    }
}

int cauta(nod *p, int x)
{
    if (p == NULL)
        return 0;
    if (p->val == x)
        return 1;
    if (x < p->val)
        return cauta(p->st, x);
    if (x > p->val)
        return cauta(p->dr, x);
    return 0;
}

int maxim(nod *p)
{
    while (p->dr != NULL)
    	p = p->dr;
    return p->val;
}

/*void stergere(nod **p, int x)
{
	if (*p == NULL)
		return NULL;
    if (p->val == x)
    {
        if (p->st == NULL)
        	return p->dr;
        if (p->dr == NULL)
        	return p->st;
        p->val = maxim(p->st);
        p->st = stergere(p->st, p->val);
    }
    else if (x < p->val)
        p->st = stergere(p->st, x);
    else if (x > p->val)
        p->dr = stergere(p->dr, x);

    echilibrare(p);
    return p;
}*/

int main()
{
    nod *t = NULL;
    int n, i, x;
    scanf("%d", &n);
    for (i=0; i<n; i++)
    {
        scanf("%d", &x);
        adauga(&t, x);
    }

	printf("\n\n");
    RSD(t);
    printf("\n");
    RSD_bal(t);
    printf("\n\n");

    //t = stergere(t, 23);
    //t = stergere(t, 9);
    //t = stergere(t, 10);

    RSD(t);
    printf("\n");
    RSD_bal(t);
    printf("\n");

    return 0;
}
/*
10
30 25 57 80 45 12 23 3 9 10
*/
