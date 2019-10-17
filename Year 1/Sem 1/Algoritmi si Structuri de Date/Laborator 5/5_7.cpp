#include <stdio.h>

using namespace std;

struct nod
{
    int val;
    nod *urm;
};

void push(int a, nod *&coada)
{
    if (coada == NULL)
    {
        coada=new nod;
        coada->val=a;
        coada->urm=NULL;
        return;
    }

    nod *c=coada, *aux;
    while (c->urm)
        c=c->urm;
    aux=new nod;
    aux->val=a;
    aux->urm=NULL;
    c->urm=aux;
}

int pop(nod *&coada)
{
    if (coada == NULL)
        return -1;
    nod *aux=coada;
    coada=coada->urm;
    int val=aux->val;
    delete (aux);
    return val;
}

int peek(nod *coada)
{
    if (coada == NULL)
        return -1;
    return coada->val;
}

bool empty1(nod *coada)
{
    if (coada == NULL)
        return true;
    return false;
}

int search1(int a, nod *coada)
{
    if (coada == NULL)
        return -1;
    int distanta=0;
    while (coada)
    {
        if (a == coada->val)
            return distanta;
        coada=coada->urm;
        distanta++;
    }
    return -1;
}

void afiseaza(nod *coada)
{
    while (coada)
    {
        printf("%d ", coada->val);
        coada=coada->urm;
    }
}

int ultim(nod *p)
{
    if (p==NULL)
        return -1;
    while (p->urm)
        p=p->urm;
    return p->val;
}

int main()
{
    int n, k, i, j, maxim, poz, v;
    scanf("%d %d", &n, &k);

    nod *linie[k], *cda=NULL;

    for (i=0; i<k; i++)
        linie[i]=NULL;
    for (i=0; i<k; i++)
        push(0, linie[i]);

    for (i=1; i<=n; i++)
    {
        scanf("%d", &v);
        push(v, cda);
    }

    for (i=n; i>=1; i--)
    {
        maxim=-1;
        poz=-1;
        for (j=0; j<k; j++)
        {
            if (ultim(linie[j]) > maxim && ultim(linie[j]) < cda->val)
            {
                maxim=ultim(linie[j]);
                poz=j;
            }
        }
        if (poz==-1)
        {
            printf("Nu se poate");
            return 0;
        }
        push(cda->val, linie[poz]);
        pop(cda);
    }
    printf("Se poate");
    return 0;
}
