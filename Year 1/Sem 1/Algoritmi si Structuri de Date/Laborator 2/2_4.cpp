#include <stdio.h>
#include <string.h>
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

void afisare_inversa(nod *p)
{
    if (p->next)
        afisare_inversa(p->next);
    printf("%d",p->val);
}

void afisare_lista(nod *p)
{
    if (p==NULL)
        printf("-");
    while (p!=NULL)
    {
        printf("%d", p->val);
        p=p->next;
    }
    printf("\n");
}

void creare_lista_nr_mare(nod *&p, nod *&u, char s[])
{
    int l=strlen(s);
    int x;
    for (int i=l-1; i>=0; i--)
    {
        x=s[i]-'0';
        adaugare_final(p,u,x);
    }
}

void suma_liste(nod *p1, nod*p2, nod *&suma)
{
    if (p1==NULL && p2==NULL) //verificare
        return;
    if (p1==NULL)
    {
        suma=p2;
        return;
    }
    if (p2==NULL)
    {
        suma=p1;
        return;
    }

    int sum1, sum2=0, sp1, sp2;

    suma=new nod; //adaugam prima oara separat
    sum1=p1->val+p2->val;
    if (sum1>=10)
    {
        sum2=sum1/10;
        sum1=sum1%10;
    }
    suma->val=sum1;
    suma->next=NULL;
    p1=p1->next;
    p2=p2->next;

    nod *a, *c=suma;

    while(p1 || p2) //facem suma pana la capatul celei mai lungi liste
    {
        a=new nod;
        if (p1) //daca am iesit dintr-o lista, adaugam 0 din partea ei
            sp1=p1->val;
        else
            sp1=0;
        if (p2)
            sp2=p2->val;
        else
            sp2=0;
        sum1=sum2+sp1+sp2;
        sum2=0;
        if (sum1>=10)
        {
            sum2=sum1/10;
            sum1=sum1%10;
        }
        a->val=sum1;
        a->next=NULL;
        c->next=a;
        c=a;
        if (p1)
            p1=p1->next;
        if (p2)
            p2=p2->next;
    }
    if (sum2) //daca a mai ramas o cifra de pus
    {
        a=new nod;
        a->val=sum2;
        a->next=NULL;
        c->next=a;
    }
}

int main()
{
    nod *p1=NULL, *p2=NULL, *u1=NULL, *u2=NULL, *suma=NULL;
    char s1[101], s2[101];
    scanf("%s%s",s1,s2);
    creare_lista_nr_mare(p1,u1,s1);
    creare_lista_nr_mare(p2,u2,s2);
    suma_liste(p1,p2,suma);
    afisare_inversa(suma);
    return 0;
}
