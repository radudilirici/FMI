#include <stdio.h>

using namespace std;

struct nod
{
    int val;
    nod *st, *dr;
};

void completare(nod *p, int v[], int &k)
{
    if (p == NULL)
        return;
    completare(p->st, v, k);
    v[k] = p->val;
    k++;
    completare(p->dr, v, k);
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
    int n, i, v[100];
    scanf("%d", &n);
    for (i=0; i<n; i++)
        scanf("%d", &v[i]);
    for (i=0; i<n; i++)
        adaugare(p, v[i]);
    i = 0;
    completare(p, v, i);
    for (i=0; i<n; i++)
        printf("%d ", v[i]);
    return 0;
}
