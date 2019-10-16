#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("data.in");
ofstream fout("data.out");

class Nod
{
    int val;
    vector<Nod*> vecini;
    vector<int> ponderi;
    friend class Graf;
    friend void free_list(Nod* N);

public:
    friend ostream &operator<<(ostream &g, Nod &nod_crt);
    Nod();
    Nod(int val_crt);
    Nod& operator=(Nod N);
};

Nod::Nod()
{
    this->val = 0;
}

Nod::Nod(int val_crt)
{
    this->val = val_crt;
}

Nod& Nod::operator=(Nod nod_crt)
{
    Nod *nodNou = new Nod(nod_crt.val);
    return *nodNou;
}

ostream &operator<<(ostream &g, Nod &nod_crt)
{
    for (unsigned int i = 0; i < nod_crt.vecini.size(); i++)
        if (nod_crt.val < nod_crt.vecini[i]->val)
            g<<nod_crt.val<<" "<<nod_crt.vecini[i]->val<<" "<<nod_crt.ponderi[i]<<"\n";

    return g;
}

class Graf
{
    vector<Nod*> noduri;
    void adaugare_nod(int val_crt);
    Nod *get_nod(int val_crt);

public:
    friend istream &operator>>(istream &f, Graf &grafulMeu);
    friend ostream &operator<<(ostream &g, Graf &grafulMeu);
    Graf& operator=(Graf &G);
    bool operator==(Graf G);
    Graf& operator*(Graf &G);
    Graf();
    Graf(Graf& G);
    ~Graf();
    void leaga(int nod1, int nod2, int pondere);
    int nr_noduri();
    int nr_muchii();
    int **floyd_warshall();
    int **drumuri();
    vector<Nod*> componente_conexe();
    bool e_conex();
    Graf& arborep(int nod);
};

Graf::Graf()
{
    return;
}

Graf::Graf(Graf& G)
{
    int n = G.nr_noduri();
    for (int i = 0; i <= n; i++)
        this->adaugare_nod(i);
    for (int i = 0; i <= n; i++)
        for (unsigned int j = 0; j < G.noduri[i]->vecini.size(); j++)
            if (i < G.noduri[i]->vecini[j]->val)
                this->leaga(i, G.noduri[i]->vecini[j]->val, G.noduri[i]->ponderi[j]);
}

Graf& Graf::operator=(Graf& G)
{
    int n = G.nr_noduri();
    for (int i = 0; i <= n; i++)
        this->adaugare_nod(i);

    for (int i = 0; i <= n; i++)
        for (unsigned int j = 0; j < G.noduri[i]->vecini.size(); j++)
            if (i < G.noduri[i]->vecini[j]->val)
                this->leaga(i, G.noduri[i]->vecini[j]->val, G.noduri[i]->ponderi[j]);

    return *this;
}

bool Graf::operator==(Graf G)
{
    if (this->nr_noduri() != G.nr_noduri())
        return false;

    int n = this->nr_noduri();
    for (int i = 0; i <= n; i++)
    {
        if (this->noduri[i]->vecini.size() != G.noduri[i]->vecini.size())
            return false;
        for (unsigned int j = 0; j < this->noduri[i]->vecini.size(); j++)
            if (this->noduri[i]->vecini[j]->val != G.noduri[i]->vecini[j]->val || this->noduri[i]->ponderi[j] != G.noduri[i]->ponderi[j])
                return false;
    }

    return true;
}

Graf& Graf::operator*(Graf &G)
{
    int n = this->nr_noduri();
    int m1 = this->nr_muchii();
    int m2 = G.nr_muchii();
    int k = 0;

    int **v = new int* [m1 + m2];
    for (int i = 0; i < m1 + m2; i++)
        v[i] = new int[3];

    for (int i = 1; i <= n; i++){
        for (unsigned int j = 0; j < this->noduri[i]->vecini.size(); j++)
            if (this->noduri[i]->val < this->noduri[i]->vecini[j]->val)
            {
                v[k][0] = this->noduri[i]->val;
                v[k][1] = this->noduri[i]->vecini[j]->val;
                v[k][2] = this->noduri[i]->ponderi[j];
                k++;
            }
    }

    for (int i = 1; i <= n; i++){
        for (unsigned int j = 0; j < G.noduri[i]->vecini.size(); j++)
            if (G.noduri[i]->val < G.noduri[i]->vecini[j]->val)
            {
                v[k][0] = G.noduri[i]->val;
                v[k][1] = G.noduri[i]->vecini[j]->val;
                v[k][2] = G.noduri[i]->ponderi[j];
                k++;
            }
    }

    for (int i = 0; i < m1 + m2 - 1; i++)
        for (int j = i + 1; j < m1 + m2; j++)
            if (v[i][2] > v[j][2])
            {
                int aux[3];
                aux[0] = v[i][0];
                aux[1] = v[i][1];
                aux[2] = v[i][2];
                v[i][0] = v[j][0];
                v[i][1] = v[j][1];
                v[i][2] = v[j][2];
                v[j][0] = aux[0];
                v[j][1] = aux[1];
                v[j][2] = aux[2];
            }

    Graf *grafNou = new Graf;
    for (int i = 0; i <= n; i++)
        grafNou->adaugare_nod(i);

    int nod1, nod2, cost;
    int ok;

    for (int i = 0; i < m1 + m2; i++)
    {
        nod1 = v[i][0];
        nod2 = v[i][1];
        cost = v[i][2];
        ok = 1;
        for (unsigned int j = 0; j < grafNou->noduri[nod1]->vecini.size() && ok; j++) //daca am pus deja muchia asta, nu o mai punem inca o data
            if (grafNou->noduri[nod1]->vecini[j]->val == nod2)                  //pentru ca sunt sortate crescator
                ok = 0;
        if (ok)
            grafNou->leaga(nod1, nod2, cost);
    }

    return *grafNou;
}

Graf::~Graf()
{
    int n = nr_noduri();
    for (int i = 0; i <= n; i++)
    {
        this->noduri[i]->vecini.clear();
        this->noduri[i]->ponderi.clear();
        delete(this->noduri[i]);
    }
}

int Graf::nr_noduri()
{
    return this->noduri.size() - 1;
}

int Graf::nr_muchii()
{
    int n = this->nr_noduri();
    int m = 0;

    for (int i = 1; i <= n; i++)
        for (unsigned int j = 0; j < this->noduri[i]->vecini.size(); j++)
            m++;
    m/=2;
    return m;
}

void Graf::adaugare_nod(int val_crt)
{
    Nod *nodNou = new Nod(val_crt);
    this->noduri.push_back(nodNou);
}

Nod *Graf::get_nod(int val_crt)
{
    for (unsigned int i = 0; i < this->noduri.size(); i++)
        if (this->noduri[i]->val == val_crt)
            return this->noduri[i];
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
    g<<grafulMeu.nr_noduri()<<" "<<grafulMeu.nr_muchii()<<"\n";

    for (int i = 1; i <= grafulMeu.nr_noduri(); i++)
        g<<*grafulMeu.noduri[i];

    return g;
}

int **Graf::floyd_warshall()
{
    int n = this->nr_noduri();
    int **fw = new int* [n+1];
    for (int i = 1; i <= n; i++)
        fw[i] = new int[n+1];

    for (int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            fw[i][j] = 999999999;

    for (int i = 1; i <= n; i++)
        for (unsigned int j = 0; j < this->noduri[i]->vecini.size(); j++)
            fw[i][this->noduri[i]->vecini[j]->val] = this->noduri[i]->ponderi[j];

    for (int i = 1; i <= n; i++)
        fw[i][i] = 0;

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (fw[i][j] > fw[i][k] + fw[k][j])
                    fw[i][j] = fw[i][k] + fw[k][j];

    for (int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if (fw[i][j] == 999999999)
                fw[i][j] = 0;

    return fw;
}

int **Graf::drumuri()
{
    int n = this->nr_noduri();
    int fw[n+1][n+1];

    int **next = new int* [n+1];
    for (int i = 1; i <= n; i++)
        next[i] = new int[n+1];

    for (int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            fw[i][j] = 999999999;
            next[i][j] = 0;
        }

    for (int i = 1; i <= n; i++)
        for (unsigned int j = 0; j < this->noduri[i]->vecini.size(); j++)
        {
            fw[i][this->noduri[i]->vecini[j]->val] = this->noduri[i]->ponderi[j];
            next[i][this->noduri[i]->vecini[j]->val] = i;
        }

    for (int i = 1; i <= n; i++)
        fw[i][i] = 0;

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (fw[i][j] > fw[i][k] + fw[k][j])
                {
                    fw[i][j] = fw[i][k] + fw[k][j];
                    next[i][j] = k;
                }

    return next;
}

vector<Nod*> Graf::componente_conexe()
{
    int n = this->nr_noduri();
    int parcurs[n+1] = {0};
    //parcurs[1] = 1;

    vector<Nod*> conexe;
    Nod *pus, *caut, *gasit;
    queue<Nod*> q;

    for (int i = 1; i <= n; i++)
    {
        if (this->noduri[i]->vecini.size() > 0 && parcurs[i] == 0)
        {
            pus = new Nod(i);
            conexe.push_back(pus);
            parcurs[i] = 1;
            q.push(this->noduri[i]);
            while (!q.empty())
            {
                caut = q.front(); // in coada punem nodurile originale pentru legaturi, dar in vectorul de liste de noduri punem alte noduri
                for (unsigned int j = 0; j < caut->vecini.size(); j++)
                {
                    if (parcurs[caut->vecini[j]->val] == 0)
                    {
                        parcurs[caut->vecini[j]->val] = 1;
                        q.push(caut->vecini[j]);

                        gasit = new Nod(caut->vecini[j]->val);
                        pus->vecini.push_back(gasit);
                        pus = gasit;
                    }
                }
                q.pop();
            }
        }
    }

    return conexe;
}

void free_list(Nod* N)
{
    if (N->vecini.size() > 0)
        free_list(N->vecini[0]);
    N->vecini.clear();
    N->ponderi.clear();
    delete N;
}

bool Graf::e_conex()
{
    vector<Nod*> lista = this->componente_conexe();
    int r = lista.size();

    for (unsigned int i = 0; i < lista.size(); i++)
        free_list(lista[i]);

    return r == 1;
}

Graf& Graf::arborep(int nod)
{
    int n = this->nr_noduri();
    int m = this->nr_muchii();
    int k = 0;

    int **v = new int* [m];
    for (int i = 0; i < m; i++)
        v[i] = new int[3];

    for (int i = 1; i <= n; i++){
        for (unsigned int j = 0; j < this->noduri[i]->vecini.size(); j++)
            if (this->noduri[i]->val < this->noduri[i]->vecini[j]->val)
            {
                v[k][0] = this->noduri[i]->val;
                v[k][1] = this->noduri[i]->vecini[j]->val;
                v[k][2] = this->noduri[i]->ponderi[j];
                k++;
            }
    }

    for (int i = 0; i < m - 1; i++)
        for (int j = i + 1; j < m; j++)
            if (v[i][2] > v[j][2])
            {
                int aux[3];
                aux[0] = v[i][0];
                aux[1] = v[i][1];
                aux[2] = v[i][2];
                v[i][0] = v[j][0];
                v[i][1] = v[j][1];
                v[i][2] = v[j][2];
                v[j][0] = aux[0];
                v[j][1] = aux[1];
                v[j][2] = aux[2];
            }

    Graf *A = new Graf;
    for (int i = 0; i <= n; i++)
        A->adaugare_nod(i);

    int compon[n+1];
    for (int i = 1; i <= n; i++)
        compon[i] = i;

    int schimbare = 1;
    while (schimbare)
    {
        schimbare = 0;
        for (int i = 0; i < m && !schimbare; i++) //luam la rand toate muchiile, in ordinea costurilor si vedem daca sunt in aceeasi componenta conexa
        {
            if (compon[v[i][0]] != compon[v[i][1]] && (compon[v[i][0]] == nod || compon[v[i][1]] == nod))
            {
                schimbare = 1;
                for (int j = 1; j <= n; j++)
                    if (compon[j] == compon[v[i][0]] || compon[j] == compon[v[i][1]])
                        compon[j] = nod;
                A->leaga(v[i][0], v[i][1], v[i][2]);
            }
        }
    }

    for (int i = 0; i < m; i++)
        delete[] v[i];
    delete[] v;

    return *A;
}

int main()
{
    Graf A, B;
    fin>>A>>B;

    Graf copie(A);

    fout<<A<<"\n\n"<<copie<<"\n\n";

    //vector<Nod*> conexe = A.componente_conexe();

    if (A.e_conex())
        cout<<"A E CONEX\n";
    else
        cout<<"A NU E CONEX\n";

    Graf Arbore;
    Arbore = A.arborep(1);

    Graf C = B;
    Graf D;
    D = A * B;

    fout<<D<<"\n\n";

    return 0;
}
