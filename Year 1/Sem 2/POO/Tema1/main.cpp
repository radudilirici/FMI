#include <iostream>
#include <fstream>

using namespace std;

ifstream f("data.in");
ofstream g("data.out");

class Nod
{
    int nod_initial;
    int val;
    int pondere;
    Nod *next;
    friend class Graf;

public:
    Nod();
    Nod(int nod_i, int x, int cost);
    Nod(const Nod &N);
    ~Nod();
    void adauga(int nod_i, int urm, int cost);
    Nod& operator=(const Nod &N);
    friend ostream &operator<<(ostream &g,Nod &N);
};

Nod::Nod()
{
    this->nod_initial = 0;
    this->val = 0;
    this->pondere = 0;
    this->next = NULL;
}

Nod::Nod(int nod_i, int x = 0, int cost = 0)
{
    this->nod_initial = nod_i;
    this->val = x;
    this->pondere = cost;
    this->next = NULL;
}

Nod::Nod(const Nod& N)
{
    if (&N == NULL)
        return;
    this->nod_initial = N.nod_initial;
    this->val = N.val;
    this->pondere = N.pondere;
    this->next = NULL;
}

Nod::~Nod()
{
    if (this != NULL)
        if (this->next != NULL)
            delete this->next;
}

void Nod::adauga(int nod_i, int urm, int cost)
{
    if (this == NULL)
        return;

    Nod *p = this;
    while (p->next != NULL)
        p = p->next;
    Nod* aux = new Nod(nod_i, urm, cost);
    p->next = aux;
}

Nod& Nod::operator=(const Nod &N)
{
    if (&N == NULL)
        return *this;
    this->val = N.val;
    this->pondere = N.pondere;
    this->next = NULL;
    return *this;
}

ostream &operator<<(ostream &g,Nod &N)
{
    Nod *p = &N;
    while (p != NULL)
    {
        if (p->nod_initial < p->val)
        {
            g<<p->nod_initial<<" "<<p->val;
            if (p->pondere > 0)
                g<<" "<<p->pondere;
            g<<"\n";
        }
        p = p->next;
    }
    return g;
}

class Graf
{
    int n;
    Nod **Lista;

public:
    Graf();
    Graf(int noduri);
    Graf(const Graf &G);
    ~Graf();
    void goleste();
    int getn();
    int nr_muchii();
    void leaga(int nod1, int nod2, int cost);
    Graf &operator=(const Graf &G);
    Graf operator*(Graf &G);
    friend istream &operator>>(istream &f, Graf &G);
    friend ostream &operator<<(ostream &g, Graf &G);
    int **floyd_warshall();
    int **drumuri();
    Nod **componente_conexe();
    bool e_conex();
    int **muchii();
    Graf arbore_p(int nod);
};

Graf::Graf()
{
    this->n = 0;
    Lista = NULL;
    return;
}

Graf::Graf(int noduri)
{
    this->n = noduri;
    this->Lista = new Nod* [noduri+1];
    for (int i = 0; i <= noduri; i++)
        Lista[i] = NULL;
}

Graf::Graf(const Graf& G)
{
    this->n = G.n;
    this->Lista = new Nod* [this->n+1];
    for (int i = 1; i <= this->n; i++)
    {
        if (G.Lista[i] != NULL)
        {
            this->Lista[i] = new Nod(*G.Lista[i]);
            Nod *p = this->Lista[i];
            Nod *q = G.Lista[i];
            while (q->next != NULL)
            {
                q = q->next;
                Nod *aux = new Nod(*q);
                p->next = aux;
                p = aux;
            }
        }
        else
            this->Lista[i] = NULL;
    }
}

Graf::~Graf()
{
    for (int i = 1; i <= this->n; i++)
        if (Lista != NULL)
            if (this->Lista[i] != NULL)
                delete this->Lista[i];
    if (Lista != NULL)
        delete[] this->Lista;
}

int Graf::getn()
{
    return this->n;
}

int Graf::nr_muchii()
{
    int m = 0;
    for (int i = 1; i <= this->n; i++)
    {
        Nod *p = this->Lista[i];
        while (p != NULL)
        {
            m++;
            p = p->next;
        }
    }
    return m/2;
}

void Graf::goleste()
{
    for (int i = 1; i <= this->n; i++)
        if (Lista != NULL)
            if (this->Lista[i] != NULL)
                delete this->Lista[i];
    if (Lista != NULL)
        delete[] this->Lista;
    this->n = 0;
}

void Graf::leaga(int nod1, int nod2, int cost = 0)
{
    if (nod1 < 1 || nod1 > this->n)
    {
        cout<<"Nu se poate adauga nodul "<<nod1<<"\n";
        return;
    }
    if (nod2 < 1 || nod2 > this->n)
    {
        cout<<"Nu se poate adauga nodul "<<nod2<<"\n";
        return;
    }

    if (this->Lista[nod1] == NULL)
        this->Lista[nod1] = new Nod(nod1, nod2, cost);
    else
    this->Lista[nod1]->adauga(nod1, nod2, cost);

    if (this->Lista[nod2] == NULL)
        this->Lista[nod2] = new Nod(nod2, nod1, cost);
    else
    this->Lista[nod2]->adauga(nod2, nod1, cost);
}

Graf& Graf::operator=(const Graf &G)
{
    if (this->Lista == G.Lista)
        return *this;
    if (this->Lista != NULL)
        this->goleste();
    this->n = G.n;
    this->Lista = new Nod* [this->n+1];
    for (int i = 1; i <= this->n; i++)
    {
        if (G.Lista[i] != NULL)
        {
            this->Lista[i] = new Nod(*G.Lista[i]);
            Nod *p = this->Lista[i];
            Nod *q = G.Lista[i];
            while (q->next != NULL)
            {
                q = q->next;
                Nod *aux = new Nod(*q);
                p->next = aux;
                p = aux;
            }
        }
        else
            this->Lista[i] = NULL;
    }
    return *this;
}

istream &operator>>(istream &f, Graf &G)
{
    int n, m;
    f>>n>>m;
    G = Graf(n);

    int nod1, nod2, cost;
    for (int i = 0; i < m; i++)
    {
        f>>nod1>>nod2>>cost;
        G.leaga(nod1, nod2, cost);
    }

    return f;
}

ostream &operator<<(ostream &g,Graf &G)
{
    g<<G.n<<" "<<G.nr_muchii()<<"\n";
    for (int i = 1; i <= G.n; i++)
        g<<*G.Lista[i];
    return g;
}

int** Graf::floyd_warshall()
{
    int **fw = new int* [this->n + 1];
    for (int i = 1; i <= this->n; i++)
        fw[i] = new int[this->n + 1];

    for (int i = 1; i <= this->n; i++)
        for(int j = 1; j <= this->n; j++)
            fw[i][j] = 999999999;

    for (int i = 1; i <= this->n; i++)
    {
        Nod *p = this->Lista[i];
        while (p != NULL)
        {
            fw[p->nod_initial][p->val] = p->pondere;
            p = p->next;
        }
    }

    for (int i = 1; i <= this->n; i++)
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

int** Graf::drumuri()
{
    int fw[this->n + 1][this->n + 1];

    int **intermediar = new int* [this->n + 1];
    for (int i = 1; i <= this->n; i++)
        intermediar[i] = new int[this->n + 1];

    for (int i = 1; i <= this->n; i++)
        for(int j = 1; j <= this->n; j++)
        {
            fw[i][j] = 999999999;
            intermediar[i][j] = 0;
        }

    for (int i = 1; i <= this->n; i++)
    {
        Nod *p = this->Lista[i];
        while (p != NULL)
        {
            fw[i][p->val] = p->pondere;
            intermediar[i][p->val] = i;
            p = p->next;
        }
    }

    for (int i = 1; i <= this->n; i++)
        fw[i][i] = 0;

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (fw[i][j] > fw[i][k] + fw[k][j])
                {
                    fw[i][j] = fw[i][k] + fw[k][j];
                    intermediar[i][j] = k;
                }

    return intermediar;
}

class Stack
{
    int n;
    int *s;
public:
    Stack(int nr);
    ~Stack();
    int getn()
    {
        return n;
    }
    void push(int x)
    {
        this->n++;
        this->s[n] = x;
    }
    int top()
    {
        return this->s[n];
    }
    void pop()
    {
        if (n > 0)
            this->n--;
    }
};

Stack::Stack(int nr = 0)
{
    this->n = 0;
    if (nr == 0)
    {
        s = NULL;
        return;
    }
    this->s = new int[nr];
}

Stack::~Stack()
{
    delete[] this->s;
}

Nod** Graf::componente_conexe()
{
    int parcurs[this->n + 1] = {0};

    Nod **conexe = new Nod* [this->n + 1];
    for (int i = 0; i <= n; i++)
        conexe[i] = NULL;
    int nr_comp = 0;

    Stack myStack(this->n);

    for (int i = 1; i <= this->n; i++)
    {
        if (parcurs[i] == 0)
        {
            parcurs[i] = 1;
            nr_comp++;
            conexe[nr_comp - 1] = new Nod(i, i, 0);
            myStack.push(i);
            while (myStack.getn() > 0)
            {
                int tp = myStack.top();
                myStack.pop();

                Nod *p = this->Lista[tp];
                while (p != NULL)
                {
                    if (parcurs[p->val] == 0)
                    {
                        parcurs[p->val] = 1;
                        myStack.push(p->val);
                        conexe[nr_comp - 1]->adauga(i, p->val, 0);
                    }
                    p = p->next;
                }
            }
        }
    }

    return conexe;
}

bool Graf::e_conex()
{
    Nod **conex = this->componente_conexe();
    int nr_comp = 0;
    for (int i = 0; i <= this->n && nr_comp < 2; i++)
        if (conex[i] != NULL)
            nr_comp++;

    for (int i = 0; i < this->n; i++)
        if (conex[i] != NULL)
            delete conex[i];
    if (conex != NULL)
        delete[] conex;

    return nr_comp < 2;
}

int** Graf::muchii()
{
    int **m = new int* [this->nr_muchii()];
    for (int i = 0; i < this->nr_muchii(); i++)
        m[i] = new int[3]; //m[0] = nod1, m[1] = nod2, m[2] = pondere
    int k = 0;

    for (int i = 1; i <= this->n; i++)
        if (this->Lista[i] != NULL)
        {
            Nod *p = Lista[i];
            while (p != NULL)
            {
                if (i < p->val)
                {
                    m[k][0] = i;
                    m[k][1] = p->val;
                    m[k][2] = p->pondere;
                    k++;
                }
                p = p->next;
            }
        }
    return m;
}

Graf Graf::arbore_p(int nod)
{
    int **m = this->muchii();
    int nr_m = this->nr_muchii();
    Nod **conex = this->componente_conexe();

    int componenta = 0;
    int gasit = 0;
    while (conex[componenta] != NULL && gasit == 0)
    {
        Nod *p = conex[componenta];
        while (p != NULL && gasit == 0)
        {
            if (p->val == nod)
                gasit = 1;
            p = p ->next;
        }
        if (gasit == 0)
            componenta++;
    }

    for (int i = 0; i < nr_m; i++) //scoatem toate muchiile care nu sunt din aceeasi componenta conexa
    {
        int ok = 0;
        Nod *p = conex[componenta];
        while (p != NULL)
        {
            if (m[i][1] == p->val)
            {
                ok = 1;
                break;
            }
            p = p->next;
        }
        if (ok == 0)
        {
            int *aux = m[i];
            m[i] = m[nr_m - 1];
            m[nr_m - 1] = aux;
            nr_m--;
            i--;
        }
    }

    for (int i = 0; i < nr_m - 1; i++)
        for (int j  = i + 1; j < nr_m; j++)
            if (m[i][2] > m[j][2])
            {
                int *aux = m[i];
                m[i] = m[j];
                m[j] = aux;
            }

    int viz[this->n] = {0};

    Graf A(this->n);

    for (int i = 0; i < nr_m; i++)
    {
        if (viz[m[i][0]] == 0 || viz[m[i][1]] == 0)
        {
            viz[m[i][0]] = viz[m[i][1]] = 1;
            A.leaga(m[i][0], m[i][1]);
        }
    }

    //eliberare memorie
    for (int i = 0; i < this->nr_muchii(); i++)
        if (m[i] != NULL)
            delete[] m[i];
    delete[] m;

    for (int i = 0; i < this->n; i++)
        if (conex[i] != NULL)
            delete conex[i];
    delete[] conex;

    return A;
}

Graf Graf::operator*(Graf &G)
{
    if (this->n != G.n)
        return *this;

    int **m1 = this->muchii();
    int **m2 = G.muchii();

    int nr_m = this->nr_muchii() + G.nr_muchii();
    int **m = new int* [nr_m];
    for (int i = 0; i < this->nr_muchii(); i++)
        m[i] = m1[i];
    for (int i = this->nr_muchii(); i < nr_m; i++)
        m[i] = m2[i - this->nr_muchii()];

    for (int i = 0; i < nr_m - 1; i++)
        for (int j  = i + 1; j < nr_m; j++)
            if (m[i][2] > m[j][2])
            {
                int *aux = m[i];
                m[i] = m[j];
                m[j] = aux;
            }

    int **intersectie_m = new int* [nr_m];
    int nr_inter = 0;

    for (int i = 0; i < nr_m - 1; i++) //retinem muchiile care se repeta
        for (int j = i + 1; j < nr_m; j++)
            if (m[i][0] == m[j][0] && m[i][1] == m[j][1])
            {
                intersectie_m[nr_inter] = m[i];
                nr_inter++;
            }



    Graf grafNou(this->n);

    for (int i = 0; i < nr_inter; i++)
        grafNou.leaga(intersectie_m[i][0], intersectie_m[i][1], intersectie_m[i][2]);

    for (int i = 0; i < this->nr_muchii() + G.nr_muchii(); i++)
        if (m[i] != NULL)
            delete[] m[i];
    delete[] m1;
    delete[] m2;
    delete[] m;
    delete[] intersectie_m;

    return grafNou;
}

void afisare_drum(int **drum, int x, int y)
{
    if (x != y)
        afisare_drum(drum, x, drum[x][y]);
    g<<y<<" ";
}

int main()
{
    if (!f)
    {
        cout<<"Eroare la deschiderea fisierului data.in\n";
        exit(1);
    }

    Graf A;
    f>>A;
    g<<"A:\n"<<A<<"\n";

    Graf B = A;
    B = A;
    f>>B;

    if (A.e_conex())
        g<<"A E CONEX\n\n";
    else
        g<<"A NU E CONEX\n\n";


    g<<"Floyd Warshall A:\n";
    int **fw = A.floyd_warshall();
    for (int i = 1; i <= A.getn(); i++)
    {
        for (int j = 1; j <= A.getn(); j++){
            g<<fw[i][j]<<" ";
            if (fw[i][j] / 10 == 0)
                g<<" ";
        }
        g<<"\n";
    }
    g<<"\n";


    g<<"Drum 1-4:\n";
    int **drum = A.drumuri();
    afisare_drum(drum, 1, 4);
    g<<"\n\n";

    int nod_apm = 1;
    Graf Arbore = A.arbore_p(nod_apm);
    g<<"APM din nodul "<<nod_apm<<" in A:\n"<<Arbore<<"\n";

    Graf C = A*B;
    g<<"A*B:\n"<<C<<"\n";

    if (C.e_conex())
        g<<"A*B E CONEX\n\n";
    else
        g<<"A*B NU E CONEX\n\n";

    return 0;
}
