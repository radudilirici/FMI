#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct nod
{
    int val;
    nod *urm;
};

void push(int a, nod *&p)
{
    if (p == NULL)
    {
        p=new nod;
        p->val=a;
        p->urm=NULL;
        return;
    }

    nod *c=p, *aux;
    while (c->urm)
        c=c->urm;
    aux=new nod;
    aux->val=a;
    aux->urm=NULL;
    c->urm=aux;
}

int pop(nod *&p)
{
    int val=-1;
    if (p == NULL)
        return val;
    if (p->urm == NULL)
    {
        val=p->val;
        delete (p);
        p=NULL;
        return val;
    }
    nod *c=p;
    while (c->urm->urm)
        c=c->urm;
    val=c->urm->val;
    delete (c->urm);
    c->urm=NULL;
    return val;
}

int peek(nod *p)
{
    if (p == NULL)
        return -1;
    if (p->urm == NULL)
        return p->val;
    while (p->urm)
        p=p->urm;
    return p->val;
}

bool empty1(nod *p)
{
    if (p == NULL)
        return true;
    return false;
}

int search1(int a, nod *p)
{
    while (p)
    {
        if (a == p->val)
            break;
        p=p->urm;
    }
    if (p == NULL)
        return -1;
    int distanta=0;
    while (p->urm)
    {
        p=p->urm;
        distanta++;
    }
    return distanta;
}

void afiseaza(nod *p)
{
    if (p->urm)
        afiseaza(p->urm);
    printf("%d ", p->val);
}

int main()
{
    int n, i, val, verif, valid=1;
    nod *stiva=NULL;
    scanf("%d", &n);
    for (i=1; i<=n; i++)
    {
        scanf("%d", &val);
        if (search1(val, stiva) >= 0)
        {
            verif=pop(stiva);
            if (verif != val)
                valid=-1;
        }
        else
            push(val, stiva);
    }
    if (valid==1)
        printf("Configuratie valida");
    else
        printf("Configuratie invalida");
    return 0;
}
