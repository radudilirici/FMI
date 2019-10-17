#include <stdio.h>

using namespace std;

struct nod
{
    int val;
    nod *next;
};

void adaugare_final(nod *&p, nod *&u, int valoare)
{
    if (u==NULL)
    {
        u=new nod;
        u->val=valoare;
        u->next=NULL;
        p=u;
        return;
    }
    nod *q=new nod;
    q->val=valoare;
    q->next=NULL;
    u->next=q;
    u=q;
}

int nr_pare(nod *p)
{
    int numere=0;
    while (p!=NULL)
    {
        if (p->val%2==0)
            numere++;
        p=p->next;
    }
    return numere;
}

float medie_impare(nod *p)
{
    float numere=0, suma=0;
    while (p!=NULL)
    {
        if (p->val%2==1)
        {
            numere++;
            suma+=p->val;
        }
        p=p->next;
    }
    return suma/numere;
}

int main()
{
    nod *p=NULL, *u=NULL;
    int v,w,x,y,z;
    scanf("%d%d%d%d%d",&v,&w,&x,&y,&z);
    adaugare_final(p,u,v);
    adaugare_final(p,u,w);
    adaugare_final(p,u,x);
    adaugare_final(p,u,y);
    adaugare_final(p,u,z);

    printf("%d\n", nr_pare(p));
    printf("%f\n", medie_impare(p));

    return 0;
}
