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

int main()
{
    nod *stiva=NULL;

    push(1, stiva);
    push(4, stiva);
    push(8, stiva);
    push(2, stiva);
    push(20, stiva);
    push(6, stiva);
    push(15, stiva);

    printf("%d\n", pop(stiva));
    printf("%d\n", peek(stiva));
    printf("%s\n", empty1(stiva)? "E vida":"Nu e vida");
    printf("%d\n", search1(20, stiva));

    afiseaza(stiva);
    return 0;
}
