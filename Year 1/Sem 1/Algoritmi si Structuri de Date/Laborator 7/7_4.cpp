#include <stdio.h>

using namespace std;

struct nod
{
    int val;
    nod *st, *dr;
};

void afisare(nod *p, int k1, int k2)
{
    if (p == NULL)
        return;
    afisare(p->st, k1, k2);
    if (k1 <= p->val && p->val <= k2)
        printf("%d ", p->val);
    afisare(p->dr, k1, k2);
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
    if (valcrt < p->val)
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
    nod *p = NULL;
    adaugare(p, 10);
    adaugare(p, 5);
    adaugare(p, 3);
    adaugare(p, 6);
    adaugare(p, 20);
    adaugare(p, 15);
    adaugare(p, 12);
    adaugare(p, 24);
    adaugare(p, 34);
    adaugare(p, 21);

    afisare(p, 10, 23);
    return 0;
}
