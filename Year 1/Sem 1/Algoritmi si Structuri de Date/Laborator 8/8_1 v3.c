#include <iostream>

using namespace std;

struct nod
{
    int info, bal;
    nod *st, *dr;
};

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void inordine(nod *p)
{
    if(p)
    {
        inordine(p->st);
        cout << p->info << ' ';
        inordine(p->dr);
    }
}

void inordine_bal(nod *p)
{
    if(p)
    {
        inordine_bal(p->st);
        cout << p->bal << ' ';
        inordine_bal(p->dr);
    }
}

void rotatie_dreapta(nod *&p)
{
    nod *t = p->st;
    p->st = t->dr;
    t->dr = p;
    p->bal = p->bal + (1 - min(t->bal, 0));
    t->bal = t->bal + (1 + max(p->bal, 0));
    p = t;
}

void rotatie_stanga(nod *&p)
{
    nod *t = p->dr;
    p->dr = t->st;
    t->st = p;
    p->bal = p->bal - (1 + max(t->bal, 0));
    t->bal = t->bal - (1 - min(p->bal, 0));
    p = t;
}

void rotatie_stanga_dreapta(nod *&p)
{
    rotatie_stanga(p->st);
    rotatie_dreapta(p);
}

void rotatie_dreapta_stanga(nod *&p)
{
    rotatie_dreapta(p->dr);
    rotatie_stanga(p);
}

void echilibreaza(nod *&p)
{
    cout << "acum: ";
    inordine(p);
    cout << "\n";
    if(p->bal == -2)
    {
        if(p->st->bal == 1)
            rotatie_stanga_dreapta(p);
        else
            rotatie_dreapta(p);
    }
    else
    {
        if(p->dr->bal == -1)
            rotatie_dreapta_stanga(p);
        else
            rotatie_stanga(p);
    }
}

bool inserare_rec(nod *&p, int x)
{
    if(p == NULL)
    {
        nod *t = new nod;
        t->info = x;
        t->bal = 0;
        t-> st = t->dr = NULL;
        p = t;
        return true;
    }
    else
    {

        if(p->info == x)
            return false;

        if(x < p->info)
        {
            if(inserare_rec(p->st, x) == true)
                --p->bal; //cout << "nodul: " << p->info << "are bal: " << p->bal << '\n';}
            else
                return false;
        }
        else
        {
            if(inserare_rec(p->dr, x) == true)
                ++p->bal; //cout << "nodul: " << p->info << "are bal: " << p->bal << '\n';}
            else
                return false;
        }
        if(p->bal == 2 || p->bal == -2){
            echilibreaza(p);
            return false;
        }
        return true;
    }
}

bool cauta(nod *t, int x)
{
    if(t)
    {
        if(x == t->info)
            return true;
        if(x > t->info)
            return cauta(t->dr, x);
        if(x < t->info)
            return cauta(t->st, x);
    }
    return false;
}

int maxim(nod *r)
{
    while(r->dr)
        r = r->dr;
    return r->info;
}

nod* sterge(nod *t, int x)
{
    if(t == NULL)
        return t;
    if(x > t->info)
    {
        t->dr = sterge(t->dr, x);
        t->bal--;
    }
    else
    {
        if(x < t->info)
        {
            t->st = sterge(t->st, x);
            t->bal++;
        }
        else
        {
            if(t->dr == NULL)
            {
                nod *temp = t->st;
                delete t;
                return temp;
            }
            if(t->st == NULL)
            {
                nod *temp = t->dr;
                delete t;
                return temp;
            }
            int m = maxim(t->st);
            t->info = m;
            t->st = sterge(t->st, m);
        }
    }
    if(t->bal != -1 && t->bal != 0 && t->bal != 1)
        echilibreaza(t);
    return t;
}

int main()
{
    nod *p = NULL;
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        if(inserare_rec(p, x))
            cout << x << " a fost adaugat in avl\n";
        inordine(p);
        cout << "\n";
        inordine_bal(p);
        cout << "\n";
    }

    inordine(p);
    cout << "\n";
    inordine_bal(p);
    cout << "\n";
/*
    int c;
    cout << "ce welem cauti?";
    cin >> c;

    if(cauta(p, c))
        cout << "da, este";
    else
        cout << "nu este";
    cout << "\n maximul este:" << maxim(p);
*/
    cout << "\n elem pe care vrei sa il stergi: ";

    int s ;
    cin >> s;
    p = sterge(p, s);
    cout << "\n";
    inordine(p);
    cout << "\n";
    inordine_bal(p);
    return 0;
}
