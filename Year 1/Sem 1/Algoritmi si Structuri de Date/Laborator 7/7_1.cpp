#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct nod
{
    int val;
    nod *st, *dr;
};

void RSD(nod *p)
{
    if (p == NULL)
        return;
    printf("%d ", p->val);
    RSD(p->st);
    RSD(p->dr);
}

void SRD(nod *p)
{
    if (p == NULL)
        return;
    SRD(p->st);
    printf("%d ", p->val);
    SRD(p->dr);
}

void SDR(nod *p)
{
    if (p == NULL)
        return;
    SDR(p->st);
    SDR(p->dr);
    printf("%d ", p->val);
}

void adaugare(nod *&p, int valcrt)
{
    if (p == NULL)
    {
        p = new nod;
        p->val = valcrt;
        p->st = NULL;
        p->dr = NULL;
        return;
    }
    int r = rand() % 2;
    if (r == 0) // stanga
    {
        if (p->st == NULL)
        {
            nod *a = new nod;
            a->val = valcrt;
            a->st = NULL;
            a->dr = NULL;
            p->st = a;
        }
        else
            adaugare(p->st, valcrt);
        return;
    }
    else
    {
        if (p->dr == NULL)
        {
            nod *a = new nod;
            a->val = valcrt;
            a->st = NULL;
            a->dr = NULL;
            p->dr = a;
        }
        else
            adaugare(p->dr, valcrt);
        return;
    }
}

int main()
{
    //srand (time(NULL));
    nod *p = NULL;
    adaugare(p, 1);
    adaugare(p, 2);
    adaugare(p, 3);
    adaugare(p, 4);
    adaugare(p, 5);
    adaugare(p, 6);
    adaugare(p, 7);
    adaugare(p, 9);
    RSD(p);
    printf("\n");
    SRD(p);
    printf("\n");
    SDR(p);

    return 0;
}
