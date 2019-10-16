#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("data.in");
ofstream fout("data.out");

class Nod
{
    int val;
    vector<Nod*> vecini;
    vector<int> ponderi;
    friend class Graf;

public:
    friend ostream &operator<<(ostream &g, Nod &nod_crt);
    Nod(int val_crt);
    //void adaugare_vecin(Nod *vecin, int pondere);
    int get_val();
};

Nod::Nod(int val_crt)
{
    val = val_crt;
}
/*
void Nod::adaugare_vecin(Nod *vecin, int pondere)
{
    vecini.push_back(vecin);
    ponderi.push_back(pondere);
}*/

int Nod::get_val()
{
    return val;
}

ostream &operator<<(ostream &g, Nod &nod_crt)
{
    for (unsigned int i = 0; i < nod_crt.vecini.size(); i++)
        g<<nod_crt.val<<" "<<(*nod_crt.vecini[i]).get_val()<<" "<<nod_crt.ponderi[i]<<"\n";

    return g;
}

class Graf
{
    vector<Nod*> noduri;
    void adaugare_nod(int val_crt);
    Nod *get_nod(int val_crt);
    void leaga(int nod1, int nod2, int pondere);

public:
    void afisareVecini(int val_crt);
    friend istream &operator>>(istream &f, Graf &grafulMeu);
    friend ostream &operator<<(ostream &g, Graf &grafulMeu);
};


void Graf::adaugare_nod(int val_crt)
{
    Nod *nodNou = new Nod(val_crt);
    noduri.push_back(nodNou);
}

Nod *Graf::get_nod(int val_crt)
{
    for (unsigned int i = 0; i < noduri.size(); i++)
        if (noduri[i]->get_val() == val_crt)
            return noduri[i];
    return NULL;
}

void Graf::leaga(int val1, int val2, int pondere)
{
    Nod *nod1 = get_nod(val1);
    Nod *nod2 = get_nod(val2);

    if (nod1 == 0 || nod2 == 0)
        return;

    nod1->vecini.push_back(nod2);
    nod1->ponderi.push_back(pondere);
    nod2->vecini.push_back(nod1);
    nod2->ponderi.push_back(pondere);
}

void Graf::afisareVecini(int val_crt)
{
    Nod *nod_crt = get_nod(val_crt);

    for (unsigned int i = 0; i < nod_crt->vecini.size(); i++)
        cout<<(*nod_crt->vecini[i]).get_val()<<" "<<nod_crt->ponderi[i]<<"\n";
    cout<<"\n";
}

istream &operator>>(istream &f, Graf &grafulMeu)
{
    int n, m;
    f>>n>>m;
    for (int i = 0; i <= n; i++)
        grafulMeu.adaugare_nod(i);
    int x, y, cost;
    for (int i = 1; i <= m; i++)
    {
        f>>x>>y>>cost;
        grafulMeu.leaga(x, y, cost);
    }
    return f;
}

ostream &operator<<(ostream &g, Graf &grafulMeu)
{
    g<<grafulMeu.noduri.size() - 1<<"\n";//<<" "<<grafulMeu.m<<"\n";

    for (unsigned int i = 1; i < grafulMeu.noduri.size(); i++)
        g<<*grafulMeu.noduri[i];

    return g;
}

int **floyd_warshall(Graf graf_crt)
{
    int n = graf_crt.noduri.size();
    int **fw = new(int*)[n+1];
    for (int i = 1; i <= n; i++)
        fw[i] = new(int)[n+1];

    for (int i = 1; i <= n; i++)
        for(int j = 1; j <=n; j++)
            fw[i][j] = 999999999;

    for (int i = 1; i <= graf_crt.n; i++)
    {
        for (int j = 1; j <= graf_crt.noduri[i])
    }
}

int main()
{
    Graf grafulMeu;
    fin>>grafulMeu;
    fout<<grafulMeu;

    return 0;
}
