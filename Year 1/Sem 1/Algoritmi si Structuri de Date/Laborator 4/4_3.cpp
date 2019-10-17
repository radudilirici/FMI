#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct nod
{
    int val;
    nod *urm;
};

void afisare(nod *p)
{
    while (p)
    {
        printf("%d ", p->val);
        p=p->urm;
    }
    printf("\n");
}

void adaugare_final(nod *&p, nod *&u, int valcrt)
{
    if (p==NULL)
    {
        p=new nod;
        p->val=valcrt;
        p->urm=NULL;
        u=p;
        return;
    }
    nod *a=new nod;
    a->val=valcrt;
    a->urm=NULL;
    u->urm=a;
    u=a;
}

void citire(nod *&p, nod *&u)
{
    int n, val;
    scanf("%d", &n);
    for (int i=1; i<=n; i++)
    {
        scanf("%d", &val);
        adaugare_final(p, u, val);
    }
}

void despartire(nod *C, nod *&A, nod *&B)
{
    if (C == NULL)
        return;
    if (C->urm == NULL)
    {
        A=C;
        return;
    }

    nod *parcurgere_A, *parcurgere_B;
    int ab=1;

    A=C;
    B=C->urm;

    parcurgere_A=A;
    parcurgere_B=B;

    C=C->urm->urm;

    while (C)
    {
        if (ab)
        {
            ab=0;
            parcurgere_A->urm=C;
            parcurgere_A=C;
        }
        else
        {
            ab=1;
            parcurgere_B->urm=C;
            parcurgere_B=C;
        }
        C=C->urm;
    }
    parcurgere_A->urm=NULL;
    parcurgere_B->urm=NULL;
}

int main()
{
    nod *C=NULL, *uC, *A=NULL, *B=NULL;
    citire(C, uC);

    despartire(C, A, B);
    afisare(A);
    afisare(B);

    return 0;
}
