#include <stdio.h>

using namespace std;

struct nod
{
    int val, LeftSize;
    nod *st, *dr;
};

int gasire(nod *p, int index)
{
    if (p == NULL)
        return -1;
    if (p->LeftSize == index)
        return p->val;
    else if (index < p->LeftSize)
        return gasire(p->st, index);
    else
        return gasire(p->dr, index-(p->LeftSize)-1);
}

void SRD(nod *p)
{
    if (p == NULL)
        return;
    SRD(p->st);
    printf("%d %d\n", p->val, p->LeftSize);
    SRD(p->dr);
}

void adaugare(nod *&p, int valcrt)
{
    if (p == NULL)
    {
        p = new nod;
        p->val = valcrt;
        p->LeftSize = 0;
        p->st = NULL;
        p->dr = NULL;
        return;
    }
    if (valcrt < p->val)
    {
        p->LeftSize ++;
        if (p->st == NULL)
        {
            nod *a = new nod;
            a->val = valcrt;
            a->LeftSize = 0;
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
            a->LeftSize = 0;
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
    nod *p = NULL;

    adaugare(p, 20);
    adaugare(p, 10);
    adaugare(p, 6);
    adaugare(p, 15);
    adaugare(p, 2);
    adaugare(p, 8);
    adaugare(p, 7);
    adaugare(p, 18);
    adaugare(p, 40);
    adaugare(p, 30);
    adaugare(p, 25);
    adaugare(p, 35);

    printf("%d", gasire(p, 4));
    return 0;
}
