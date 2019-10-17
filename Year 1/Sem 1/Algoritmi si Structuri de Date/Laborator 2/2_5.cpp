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

void produs_liste(nod *p1, nod *p2, nod *&produs)
{
    int prd, prd2=0;
    nod *q, *c2, *a, *i;
    produs=new nod;
    produs->val=0; //pt ca lucarm pe urmatoarea pozitie, cream prima pozitie, ca apoi sa o stergem (nu ne intereseaza ce valoare avem aici)
    produs->next=NULL;
    i=produs;
    while (p1) //facem inmultirea de mana. cele 2 whileuri functioneaza ca niste foruri
    {
        q=i; //"i" retine pozitia de la care inepem sa punem valori (dupa fiecare inmultire a listei p2 cu o cifra din lista p1 o sa incepem cu o pozitie mai departe (stanga in viata reala))
        c2=p2;
        while (c2)
        {
            prd=p1->val*c2->val;
            prd+=prd2;
            if (q->next)
                prd+=q->next->val;
            prd2=0;
            if (prd>=10)
            {
                prd2=prd/10;
                prd=prd%10;
            }
            if (q->next==NULL)
            {
                a=new nod;
                a->val=prd;
                a->next=NULL;
                q->next=a;
                q=a;
            }
            else
            {
                q=q->next;
                q->val=prd;
            }
            c2=c2->next;
        }
        if (prd2)
        {
            a=new nod;
            a->val=prd2;
            a->next=NULL;
            q->next=a;
            prd2=0;
        }
        i=i->next;
        p1=p1->next;
    }
    if (prd2)
    {
        a=new nod;
        a->val=prd2;
        a->next=NULL;
        q->next=a;
    }
    stergere_pozitie(produs,1);
}

int main()
{
    nod *p1=NULL, *p2=NULL, *u1=NULL, *u2=NULL, *produs=NULL;
    char s1[101], s2[101];
    scanf("%s%s",s1,s2);
    creare_lista_nr_mare(p1,u1,s1);
    creare_lista_nr_mare(p2,u2,s2);
    produs_liste(p1,p2,produs);
    afisare_inversa(produs);
    return 0;
}
