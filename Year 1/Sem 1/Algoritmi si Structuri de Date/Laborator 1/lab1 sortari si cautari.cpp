#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("data.in");
ofstream fout("data.out");

///************************Lab1 Sortari si Cautari

void citire(int v[], int &n)
{
    fin>>n;
    for (int i=1; i<=n; i++)
        fin>>v[i];
}

void afisare(int v[], int n)
{
    for (int i=1; i<=n; i++)
        fout<<v[i]<<" ";
    fout<<"\n";
}

int cautare_secventiala(int v[], int n,int x)
{
    for (int i=1; i<=n; i++)
        if (v[i]==x)
            return i;
    return -1;
}

int cautare_binara(int v[], int st, int dr, int x)
{
    while (st<=dr)
    {
        int mijloc=(st+dr)/2;
        if (v[mijloc]==x)
            return mijloc;
        else if (v[mijloc]>x)
            dr=mijloc-1;
        else
            st=mijloc+1;
    }
    return -1;
}

void bubblesort(int v[], int n)
{
    bool sortat;
    do{
        sortat=true;
        for (int i=1; i<n; i++)
        if (v[i]>v[i+1])
        {
                swap(v[i],v[i+1]);
            sortat=false;
        }
    }while (!sortat);
}

void sortare_interschimbare(int v[], int n)
{
    for (int i=1; i<n; i++)
        for (int j=i+1; j<=n; j++)
            if (v[i]>v[j])
            {
                int aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }
}

void sortare_insertie(int v[], int n)
{
    for (int i=1; i<n; i++)
    {
        int j=i;
        int x=v[i+1];
        while (j>=1 && x<v[j])
        {
            v[j+1]=v[j];
            j--;
        }
        v[j+1]=x;
    }
}

void sortare_selectie(int v[], int n)
{
    for (int i=1; i<n; i++)
    {
        int minim=v[i];
        int pozmin=i;
        for (int j=i+1; j<=n; j++)
        {
            if (v[j]<minim)
            {
                minim=v[j];
                pozmin=j;
            }
        }
        swap(v[i],v[pozmin]);
    }
}

int main()
{
    int v[101], n;

    citire(v,n);
    sortare_interschimbare(v,n);
    afisare(v, n);

    citire(v,n);
    sortare_insertie(v,n);
    afisare(v, n);

    citire(v,n);
    sortare_selectie(v, n);
    afisare(v, n);

    citire(v,n);
    bubblesort(v, n);
    afisare(v, n);

    fout<<cautare_secventiala(v,n,23)<<"\n";
    fout<<cautare_binara(v,1,n,23)<<"\n";

    return 0;
}
