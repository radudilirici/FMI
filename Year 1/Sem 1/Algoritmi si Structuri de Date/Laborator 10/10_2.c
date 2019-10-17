#include <stdio.h>
#include <stdlib.h>

typedef struct l
{
    int v1, v2;
    struct l *urm;
}adi;

void citire(adi **p, int *n)
{
    FILE *f = fopen("data.in", "r");
    fscanf(f, "%d", n);

    int x=1, y=-1, x2, y2;
    adi *aux, *q;
    while (fscanf(f, " %d %d", &x2, &y2))
    {
        if (x == x2 && y == y2)
            break;
        x = x2;
        y = y2;
        if (*p == NULL)
        {
            *p = (adi *) malloc(sizeof(adi));
            (*p)->v1 = x;
            (*p)->v2 = y;
            (*p)->urm = NULL;
            continue;
        }
        q = *p;
        while (q->urm != NULL)
            q = q->urm;
        aux = (adi*) malloc(sizeof(adi));
        aux->v1 = x;
        aux->v2 = y;
        aux->urm = NULL;
        q->urm = aux;
    }
    fclose(f);
}

typedef struct qe
{
    int val;
    struct qe *urm;
}coada;

void add(coada **que, int valcrt)
{
    if (*que == NULL)
    {
        *que = (coada *) malloc(sizeof(coada));
        (*que)->val = valcrt;
        (*que)->urm = NULL;
        return;
    }
    coada *q = *que;
    while (q->urm != NULL)
        q = q->urm;
    coada *aux = (coada *) malloc(sizeof(coada));
    aux->val = valcrt;
    aux->urm = NULL;
    q->urm = aux;
}

void pop(coada **que)
{
    (*que) = (*que)->urm;
}

int conex(adi *p, int v[], int varf, int culoare)
{
    if (v[varf] != 0)
        return 0;

    coada *que = NULL;
    add(&que, varf);
    adi *aux;

    while (que != NULL)
    {
        v[que->val] = culoare;
        aux = p;
        while (aux != NULL)
        {
            if (aux->v1 == que->val && v[aux->v2] == 0)
                add(&que, aux->v2);
            if (aux->v2 == que->val && v[aux->v1] == 0)
                add(&que, aux->v1);
            aux = aux->urm;
        }
        pop(&que);
    }

    return 1;
}

int main()
{
    int n;
    adi *p = NULL;
    citire(&p, &n);

    int v[100] = {0};
    int i, culoare = 1, ok;
    for (i = 1; i <= n; i++)
    {
        ok = conex(p, v, i, culoare);
        if (ok)
            culoare++;
    }

    for (i = 1; i <= n; i++)
        printf("%d ", v[i]);
    return 0;
}
