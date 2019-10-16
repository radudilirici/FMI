#include <iostream>
#include <fstream>
#include <string.h>
#include <queue>
#include <set>
#include <map>

using namespace std;

set <int> inchidere(set <int> stari, map <pair <int, char>, set <int> > delta)
{
    queue <int> q;
    set <int> ::iterator iStari;
    for (iStari = stari.begin(); iStari != stari.end(); iStari++)
        q.push(*iStari);

    map <pair <int, char>, set <int> > ::iterator iDelta;
    while (!q.empty())
    {
        iDelta = delta.find(make_pair(q.front(), '.')); //lambda
        q.pop();
        if (iDelta != delta.end())
            for (iStari = iDelta->second.begin(); iStari != iDelta->second.end(); iStari++)
                if (stari.find(*iStari) == stari.end())
                {
                    stari.insert(*iStari);
                    q.push(*iStari);
                }
    }
    return stari;
}

set <int> urmStari(set <int> stari1, map <pair <int, char>, set <int> > delta, char c)
{
    set <int> stari2;
    set <int> ::iterator iStari, jStari;
    map <pair <int, char>, set <int> > ::iterator iDelta;

    for (iStari = stari1.begin(); iStari != stari1.end(); iStari++)
    {
        iDelta = delta.find(make_pair(*iStari, c));
        if (iDelta != delta.end())
            for (jStari = iDelta->second.begin(); jStari != iDelta->second.end(); jStari++)
                stari2.insert(*jStari);
    }
    return stari2;
}

void lnfa(set <int> stari, map <pair <int, char>, set <int> > delta, set <int> F, char w[], ostream &g)
{
    int lungime = strlen(w);
    for (int j = 0; j < lungime && !stari.empty(); j++)
    {
        set <int> aux = urmStari(stari, delta, w[j]);
        stari.clear();
        stari = aux;
        stari = inchidere(stari, delta);
    }
    set <int> ::iterator iStari;
    for (iStari = stari.begin(); iStari != stari.end(); iStari++)
        if (F.find(*iStari) != F.end())
        {
            g<<"DA\n";
            return;
        }
    g<<"NU\n";
}

void citire_QEFD(set <int> &Q, set <char> &Epsilon, int &q0, set <int> &F, map <pair <int, char>, set <int> > &delta, istream &f)
{
    if (!f)
    {
        cout<<"Nu exista fisierul de intrare\n";
        exit(1);
    }

    int nrStari, nrLitere, nrStariFinale, nrTranzitii;

    int auxInt;
    char auxChar;

    f>>nrStari;
    for (int i = 0; i < nrStari; i++)
    {
        f>>auxInt;
        Q.insert(auxInt);
    }

    f>>nrLitere;
    for (int i = 0; i < nrLitere; i++)
    {
        f>>auxChar;
        Epsilon.insert(auxChar);
    }

    f>>q0;

    f>>nrStariFinale;
    for (int i = 0; i < nrStariFinale; i++)
    {
        f>>auxInt;
        F.insert(auxInt);
    }

    f>>nrTranzitii;
    map <pair <int, char>, set <int> > ::iterator iDelta;
    int x, z;
    char y;
    for (int i = 0; i < nrTranzitii; i++)
    {
        f>>x>>y>>z;
        iDelta = delta.find(make_pair(x, y));
        if (iDelta != delta.end())
            iDelta->second.insert(z);
        else
        {
            set <int> auxSet;
            auxSet.insert(z);
            delta.insert(make_pair(make_pair(x, y), auxSet));
        }
    }
}
