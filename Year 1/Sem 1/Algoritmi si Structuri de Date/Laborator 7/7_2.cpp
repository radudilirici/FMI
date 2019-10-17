#include <stdio.h>

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

void insert1(nod *&t, int x)
{
    if (t == NULL)
    {
        t = new nod;
        t->val = x;
        t->st = NULL;
        t->dr = NULL;
        return;
    }
    if (x < t->val)
    {
        if (t->st == NULL)
        {
            nod *a = new nod;
            a->val = x;
            a->st = NULL;
            a->dr = NULL;
            t->st = a;
        }
        else
            insert1(t->st, x);
        return;
    }
    else
    {
        if (t->dr == NULL)
        {
            nod *a = new nod;
            a->val = x;
            a->st = NULL;
            a->dr = NULL;
            t->dr = a;
        }
        else
            insert1(t->dr, x);
        return;
    }
}

int search1(nod *t, int x)
{
    if (t == NULL)
        return 0;
    if (t->val == x)
        return 1;
    if (x < t->val)
        return search1(t->st, x);
    else
        return search1(t->dr, x);
}

nod *findMax(nod *t)
{
    if (t->dr != NULL)
        return findMax(t->dr);
    else
        return t;
}

void delete1(nod *&t, int x)
{
    if (t == NULL)
        return;
    if (x < t->val)
        delete1(t->st, x);
    else if (x > t->val)
        delete1(t->dr, x);
    else
    {
        if (t->st == NULL) //are grija si de cazul in care si stanga si dreapa sunt NULL
        {
            t = t->dr;
            return;
        }
        else if (t->dr == NULL)
        {
            t = t->st;
            return;
        }
        else
        {
            nod *aux = findMax(t->st);
            t->val = aux->val;
            delete1(t->st, aux->val);
            return;
        }
    }
}

int main()
{
    nod *p = NULL;
    insert1(p, 16);
    insert1(p, 7);
    insert1(p, 4);
    insert1(p, 10);
    insert1(p, 3);
    insert1(p, 5);
    insert1(p, 8);
    insert1(p, 11);
    insert1(p, 20);
    insert1(p, 30);
    RSD(p);
    printf("\n");
    SRD(p);
    printf("\n");
    SDR(p);
    printf("\n");

    printf("%d %d\n", search1(p, 5), search1(p, 17));

    nod *aux = findMax(p);
    printf("%d\n", aux->val);

    delete1(p, 7);
    delete1(p, 4);
    delete1(p, 5);
    RSD(p);
    return 0;
}
