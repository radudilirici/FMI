#include <stdio.h>

using namespace std;

struct nod
{
	char c;
    int fr;
    nod *st, *dr;
};

struct cd
{
	nod *actual;
	cd *urm;
};

void push(cd *&coada, char ccrt, int frcrt)
{
    if (coada == NULL)
    {
        coada = new cd;
        nod *a = new nod;

        a->c = ccrt;
        a->fr = frcrt;
        a->st = a->dr = NULL;

        coada->actual = a;
        coada->urm = NULL;
        return;
    }

    cd *c=coada, *aux;
    while (c->urm)
        c=c->urm;
    aux=new cd;
    nod *a = new nod;

    a->c = ccrt;
    a->fr = frcrt;
    a->st = a->dr = NULL;

    aux->actual = a;
    aux->urm = NULL;
    c->urm = aux;
}

void pushnod(cd *&coada, nod *nodcrt)
{
	if (coada == NULL)
    {
        coada = new cd;
        coada->actual = nodcrt;
        coada->urm = NULL;
        return;
    }

    cd *c=coada, *aux;
    while (c->urm)
        c=c->urm;
    aux=new cd;

    aux->actual = nodcrt;
    aux->urm = NULL;
    c->urm = aux;
}

nod *pop(cd *&coada)
{
    if (coada == NULL)
        return NULL;
    nod *a = coada->actual;
    coada = coada->urm;
    return a;
}

nod *peek(cd *coada)
{
    if (coada == NULL)
        return NULL;
    return coada->actual;
}

bool empty1(cd *coada)
{
    if (coada == NULL)
        return true;
    return false;
}

void print(cd *coada)
{
    while (coada)
    {
        printf("%c %d\n", coada->actual->c, coada->actual->fr);
        coada = coada->urm;
    }
}

void sort(cd *&coada)
{
	cd *i, *j;
	for (i = coada; i->urm != NULL; i = i->urm)
		for (j = i->urm; j != NULL; j = j->urm)
			if (i->actual->fr > j->actual->fr)
			{
				nod *aux = i->actual;
				i->actual = j->actual;
				j->actual = aux;
			}
}

void coduri(nod *huff, int v[], int k)
{
	if (huff->st == NULL && huff->dr == NULL)
	{
		printf("%c ", huff->c);
		int i;
		for (i = 0; i < k; i++)
			printf("%d", v[i]);
		printf("\n");
		return;
	}
	if (huff->st != NULL)
	{
		v[k] = 0;
		coduri(huff->st, v, k+1);
	}
	if (huff->dr != NULL)
	{
		v[k] = 1;
		coduri(huff->dr, v, k+1);
	}
}

int main()
{
	cd *coada = NULL;

	int n, i;
	char ccrt;
	int frcrt;

	scanf("%d", &n);
	for (i = 0; i <  n; i++)
	{
		scanf(" %c %d", &ccrt, &frcrt);
		push(coada, ccrt, frcrt);
	}
	sort(coada);

	nod *s, *d, *nou;

	while (empty1(coada->urm) == false)
	{
		s = pop(coada);
		d = pop(coada);
		nou = new nod;
		nou->c = '-';
		nou->fr = s->fr + d->fr;
		nou->st = s;
		nou->dr = d;

		pushnod(coada, nou);
		sort(coada);
	}

	nod *huff = coada->actual;
	int v[100];

	printf("\n");
	coduri(huff, v, 0);

	return 0;
}