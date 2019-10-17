#include <stdio.h>

using namespace std;

struct nod
{
    float val;
    nod *next;
};

void afisare_lista(nod *p)
{
    if (p==NULL)
        printf("-");
    while (p!=NULL)
    {
        printf("%g ", p->val);
        p=p->next;
    }
    printf("\n");
}

void adaugare_final(nod *&p, nod *&u, float valoare)
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

void adaugare_medie(nod *p)
{
    nod *urm=p->next;
    nod *medie;
    while (urm!=NULL)
    {
        medie=new nod;
        medie->val=(p->val+urm->val)/2;
        medie->next=urm;
        p->next=medie;
        p=urm;
        urm=urm->next;
    }
}

int main()
{
    nod *p=NULL, *u=NULL;
    float v,w,x,y,z;
    scanf("%g%g%g%g%g",&v,&w,&x,&y,&z);
    adaugare_final(p,u,v);
    adaugare_final(p,u,w);
    adaugare_final(p,u,x);
    adaugare_final(p,u,y);
    adaugare_final(p,u,z);

    adaugare_medie(p);
    afisare_lista(p);
    return 0;
}
