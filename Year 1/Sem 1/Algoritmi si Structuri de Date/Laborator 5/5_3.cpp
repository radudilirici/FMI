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
    int val=0;
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
        return 0;
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
    nod *stiva=NULL;
    char wi;
    int n, i, verificare=0, val, par_deschisa=0, par_inchisa=0;
    scanf("%d", &n);
    for (i=1; i<=n;)
    {
        scanf("%c", &wi);
        if (wi=='(')
        {
            push(1, stiva);
            i++;
        }
        else if (wi==')')
        {
            push(-1, stiva);
            i++;
        }
    }

    i=n;
    while (empty1(stiva) == false)
    {
        val=pop(stiva);
        verificare+=val;
        if (verificare > 0 && val == 1) //pentru ca parcurgem stiva de la varf
            par_deschisa=i;
        else if (verificare < 0 && val == -1)
            par_inchisa=i;
        i--;
    }

    printf("%d %d %d\n", verificare, par_deschisa, par_inchisa);

    if (verificare != 0)
    {
        if (par_deschisa == 0)
            printf("%d", par_inchisa);
        else
            printf("%d", par_deschisa);
    }

    return 0;
}
