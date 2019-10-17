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
        SRD(p->st);
        printf("%d ", p->val);
        SRD(p->dr);
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

nod *rotire_stanga(nod *p)
{
    nod *r = p->dr;
    p->dr = r->st;
    r->st = p;
    p->bal -= 1 + MAX(r->bal, 0);
    r->bal -= 1 - MIN(p->bal, 0);
    return r;
}

nod *rotire_dreapta(nod *p)
{
    nod *l = p->st;
    p->st = l->dr;
    l->dr = p;
    p->bal += 1 - MIN(l->bal, 0);
    l->bal += 1 + MAX(p->bal, 0);
    return l;
}

nod *rotire_dreapta_stanga(nod *p)
{
    p->dr = rotire_dreapta(p->dr);
    p = rotire_stanga(p);
    return p;
}

nod *rotire_stanga_dreapta(nod *p)
{
    p->st = rotire_stanga(p->st);
    p = rotire_dreapta(p);
    return p;
}

nod *echilibrare(nod *p)
{
    if (p->bal >= 2)
    {
        if (p->dr->bal >= 0)
            p = rotire_stanga(p);
        else
            p = rotire_dreapta_stanga(p);
    }
    else if (p->bal <= -2)
    {
        if (p->st->bal <= 0)
            p = rotire_dreapta(p);
        else
            p = rotire_stanga_dreapta(p);
    }
    return p;
}

nod *adauga(nod *p, int x)
{
    if (p == NULL)
        return new_node(x);

    if (x < p->val)
    {
        p->bal--;
        if (p->st == NULL)
        {
            nod *a = new_node(x);
            p->st = a;
        }
        else
            p->st = adauga(p->st, x);
    }
    else if (x >= p->val)
    {
        p->bal++;
        if (p->dr == NULL)
        {
            nod *a = new_node(x);
            p->dr = a;
        }
        else
            p->dr = adauga(p->dr, x);
    }

    if (p->bal >= 2 || p->bal <= -2)
        p = echilibrare(p);

    return p;
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

nod *stergere(nod *p, int x)
{
	if (p == NULL)
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

    p = echilibrare(p);
    return p;
}