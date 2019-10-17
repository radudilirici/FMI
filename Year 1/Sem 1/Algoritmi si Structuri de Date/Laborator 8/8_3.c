#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAX(a, b) (((a)>(b))?(a):(b))

typedef struct node
{
	char *val;
	int bal;
	struct node *st, *dr;
}nod;

void afiseaza(nod *p)
{
    if (p)
    {
        afiseaza(p->st);
        printf("%s ", p->val);
        afiseaza(p->dr);
    }
}

nod *new_node(char *x)
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

nod *adauga(nod *p, char *x)
{
    if (p == NULL)
        return new_node(x);

    if (strcmp(x, p->val) < 0)
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
    else
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

char *maxim(nod *p)
{
    while (p->dr != NULL)
    	p = p->dr;
    return p->val;
}

char *minim(nod *p)
{
    while (p->st != NULL)
    	p = p->st;
    return p->val;
}

nod *stergere(nod *p, char *x)
{
	if (p == NULL)
		return NULL;
    if (strcmp(x, p->val) == 0)
    {
        if (p->st == NULL)
        	return p->dr;
        if (p->dr == NULL)
        	return p->st;
        p->val = maxim(p->st);
        p->st = stergere(p->st, p->val);
    }
    else if (strcmp(x, p->val) < 0)
        p->st = stergere(p->st, x);
    else
        p->dr = stergere(p->dr, x);

    p = echilibrare(p);
    return p;
}

int main()
{
	char *s = (char*) malloc(100*sizeof(char));
	fgets(s, 100, stdin);

	char *c;
	nod *p = NULL;
	while (*s != '\0' && *s != '\n')
	{
		c = s;
		while (*s != ' ' && *s != '\n' && *s != '\0')
			s++;
		*s = '\0';
		if (s + 1 != NULL)
			s++;
		p = adauga(p, c);
	}

	char **sortat = (char**) malloc(100*sizeof(char*));
	int i, n;
	for (i=0; i<100; i++)
		sortat[i] = (char*) malloc(100*sizeof(char));

	i = 0;
	while (p != NULL)
	{
		sortat[i] = minim(p);
		p = stergere(p, sortat[i]);
		i++;
	}
	n = i;
	for (i=0; i<n; i++)
		printf("%s\n", sortat[i]);

	free(s);
	free(sortat);
	return 0;
}