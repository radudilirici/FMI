#include <iostream>

using namespace std;

struct nod
{
    int info;
    nod *urm;
};

void ins_cresc(nod *&p, int x)
{
    if (x<p->info)
    {
        nod *aux2=new nod;
        aux2->info=x;
        aux2->urm=p;
        p=aux2;
    }
    nod *aux=p;
    while(x>aux->urm->info)
        aux=aux->urm;
    nod *aux2=new nod;
    aux2->info=x;
    aux2->urm=aux->urm;
    aux->urm=aux2;


}
