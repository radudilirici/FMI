#include <iostream>
#include <stdio.h>

using namespace std;

FILE *f=fopen("data.in", "r");
FILE *g=fopen("data.out", "w");

struct pol
{
    int gr, coef;
    pol *urm;
};

void afisare_inversa(pol *p)
{
    if (p->urm)
        afisare_inversa(p->urm);
    fprintf(g, "%d ", p->coef);
}

void adauga(pol *&p, int gr1, int coef1)
{
    if (p==NULL)
    {
        p=new pol;
        p->gr=gr1;
        p->coef=coef1;
        p->urm=NULL;
        return;
    }
    if (p->gr>gr1)
    {
        pol *q=new pol;
        q->gr=gr1;
        q->coef=coef1;
        q->urm=p;
        p=q;
        return;
    }
    pol *c=p;
    while (c->urm)
    {
        if (c->urm->gr>gr1)
            break;
        c=c->urm;
    }
    pol *q=new pol;
    q->gr=gr1;
    q->coef=coef1;
    q->urm=c->urm;
    c->urm=q;
}

void inmultire_polinoame(pol *p, pol *q, pol *&rez, int n, int m)
{
    pol *c1, *c2;
    int coef_i;
    for (int grad=0; grad<=n+m; grad++)
    {
        c1=p;
        coef_i=0;
        for (int j=0, k=grad-j; j<=min(grad,n); j++, k--)
        {
            c2=q;
            for (int nr=0; nr<k && c2; nr++)
                c2=c2->urm;
            if (c1 && c2)
                coef_i+=c1->coef*c2->coef;
            c1=c1->urm;
        }
        adauga(rez, grad, coef_i);
    }
}

int main()
{
    int n, m, val;
    pol *p=NULL, *q=NULL, *rez=NULL;
    fscanf(f, "%d %d", &n, &m);
    for (int i=n; i>=0; i--)
    {
        fscanf(f, "%d", &val);
        adauga(p, i, val);
    }
    for (int i=m; i>=0; i--)
    {
        fscanf(f, "%d", &val);
        adauga(q, i, val);
    }

    inmultire_polinoame(p, q, rez, n, m);

    afisare_inversa(rez);
    return 0;
}
