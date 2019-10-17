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

void adaugare_inceput(nod *&p, nod *&u, int valoare)
{
    if (p==NULL)
    {
        p=new nod;
        p->val=valoare;
        p->next=NULL;
        u=p;
        return;
    }
    nod *q=new nod;
    q->val=valoare;
    q->next=p;
    p=q;
}

void adaugare_dupa_pozitie(nod *&p, int valoare, int pozitie)
{
    nod *q=new nod;
    q=p;
    for (int i=1; i<pozitie-1 && q->next!=NULL; i++)
        q=q->next;
    nod *a=new nod;
    a->val=valoare;
    a->next=q->next;
    q->next=a;;
}

void afisare_lista(nod *p)
{
    if (p==NULL)
        printf("-");
    while (p!=NULL)
    {
        printf("%d ", p->val);
        p=p->next;
    }
    printf("\n");
}

nod *cautare_valoare(nod *p, int valoare)
{
    while (p!=NULL)
    {
        if (p->val==valoare)
            return p;
        p=p->next;
    }
    return NULL;
}

nod *cautare_pozitie(nod *p, int pozitie)
{
    for (int i=1; i<pozitie && p!=NULL; i++)
        p=p->next;
    return p;
}

void stergere_valoare(nod *&p, int valoare)
{
    nod *c=p;
    if (p==NULL)
        return;
    if (p->val==valoare)
    {
        nod *q=p;
        p=p->next;
        delete q;
        return;
    }
    while(c->next!=NULL)
        if (c->next->val!=valoare)
            c=c->next;

    if (c->next==NULL)
        return;
    nod *q=c->next;
    c->next=c->next->next;
    delete q;
}

void stergere_pozitie(nod *&p, int pozitie)
{
    if (pozitie==1)
    {
        nod *q=p;
        p=p->next;
        delete q;
        return;
    }
    nod *c=p;
    for (int i=1; i<pozitie-1 && c->next!=NULL; i++)
        c=c->next;
    nod *q=c->next;
    c->next=c->next->next;
    delete q;
}

void stergere_lista(nod *&p)
{
    while (p)
        stergere_pozitie(p,1);
}

int main()
{
    nod *p=NULL, *u=NULL, *a;
    int v,w,x,y,z;
    scanf("%d%d%d%d%d",&v,&w,&x,&y,&z);

    adaugare_final(p,u,v);
    adaugare_final(p,u,w);
    adaugare_inceput(p,u,x);
    adaugare_dupa_pozitie(p,y,2);
    adaugare_dupa_pozitie(p,z,4);
    afisare_lista(p);

    a=cautare_valoare(p,10);
    if (a)
        printf("exista 10\n");
    else
        printf("nu exista 10\n");

    a=cautare_pozitie(p, 3);
    printf("pe pozitia 3 este %d\n", a->val);

    stergere_valoare(p,10);
    afisare_lista(p);

    stergere_pozitie(p,2);
    afisare_lista(p);

    stergere_lista(p);
    afisare_lista(p);

    return 0;
}
