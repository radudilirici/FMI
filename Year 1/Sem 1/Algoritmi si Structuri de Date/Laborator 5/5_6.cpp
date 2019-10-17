#include <stdio.h>

using namespace std;

struct nod
{
    int i, j;
    nod *urm;
};

void push(int i, int j, nod *&coada)
{
    if (coada == NULL)
    {
        coada=new nod;
        coada->i=i;
        coada->j=j;
        coada->urm=NULL;
        return;
    }

    nod *c=coada, *aux;
    while (c->urm)
        c=c->urm;
    aux=new nod;
    aux->i=i;
    aux->j=j;
    aux->urm=NULL;
    c->urm=aux;
}

void pop(nod *&coada)
{
    if (coada == NULL)
        return;
    nod *aux=coada;
    coada=coada->urm;
    delete (aux);
}

bool empty1(nod *coada)
{
    if (coada == NULL)
        return true;
    return false;
}

int main()
{
    int m, i, j, k, culoare=2, v[101][101]={0};
    int x[]={0, 0, 1, -1}, y[]={1, -1, 0, 0}, coord_x, coord_y;
    nod *coada=NULL;
    scanf("%d", &m);
    for (i=0; i<m; i++)
        for (j=0; j<m; j++)
            scanf("%d", &v[i][j]);

    for (i=0; i<m; i++)
        for (j=0; j<m; j++)
            if (v[i][j]==1)
            {
                push(i, j, coada);
                while (empty1(coada)==0)
                {
                    v[coada->i][coada->j]=culoare;
                    for (k=0; k<4; k++)
                    {
                        coord_x=coada->j+x[k];
                        coord_y=coada->i+y[k];
                        if (v[coord_y][coord_x]==1 && coord_x>=0 && coord_x<m && coord_y>=0 && coord_y<m){
                            push(coord_y, coord_x, coada);
                            v[coord_y][coord_x]=culoare;
                        }
                    }
                    pop(coada);
                }
                culoare++;
            }

    printf("\n");
    for (i=0; i<m; i++)
    {
        for (j=0; j<m; j++)
            if (v[i][j]>0)
                printf("%d ", v[i][j]);
            else
                printf("  ");
        printf("\n");
    }
    return 0;
}