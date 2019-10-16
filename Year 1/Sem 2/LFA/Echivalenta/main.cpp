#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include "lnfa.cpp"

using namespace std;

ifstream f("data.in");
ofstream g("data.out");

struct Graf
{
    int q0;

    set <int> Q;
    set <char> Epsilon;
    set <int> F;
    set <int> lambda_q0;
    map <pair <int, char>, set <int> > delta;
};

void afisare(Graf A)
{
    set <int> ::iterator iStari;
    map <pair <int, char>, set <int> > ::iterator iDelta;

    for (iDelta = A.delta.begin(); iDelta != A.delta.end(); iDelta++)
    {
        for (iStari = iDelta->second.begin(); iStari != iDelta->second.end(); iStari++)
        {
            int x = iDelta->first.first;
            char y = iDelta->first.second;
            int z = *iStari;

            cout<<x<<" "<<y<<" "<<z<<"\n";
        }
    }
    cout<<"\n";

    set <int> ::iterator iF;
    for (iF = A.F.begin(); iF != A.F.end(); iF++)
        cout<<*iF<<" ";
    cout<<"\n";
}

Graf completare(Graf A)
{
    set <int> ::iterator iQ;
    set <char> ::iterator iEpsilon;

    int k = 0;
    while (A.Q.find(k) != A.Q.end())
        k--;

    A.Q.insert(k);
    map <pair <int, char>, set <int> > ::iterator iDelta;

    for (iQ = A.Q.begin(); iQ != A.Q.end(); iQ++)
        for (iEpsilon = A.Epsilon.begin(); iEpsilon != A.Epsilon.end(); iEpsilon++)
        {
            iDelta = A.delta.find(make_pair(*iQ, *iEpsilon));
            if (iDelta == A.delta.end())
            {
                set <int> auxSet;
                auxSet.insert(k);
                A.delta.insert(make_pair(make_pair(*iQ, *iEpsilon), auxSet));
            }
        }

    return A;
}

Graf complement(Graf A)
{
    A = completare(A);

    set <int> F2;
    set <int> ::iterator iQ;

    for (iQ = A.Q.begin(); iQ != A.Q.end(); iQ++)
        if (A.F.find(*iQ) ==  A.F.end())
            F2.insert(*iQ);
    A.F.clear();
    A.F = F2;

    return A;
}

bool e_vid(Graf A)
{
    set <char> ::iterator iEpsilon;
    set <int> ::iterator iStari;
    map <pair <int, char>, set <int> > ::iterator iDelta;

    queue <int> q;
    set <int> viz;
    q.push(A.q0);
    viz.insert(A.q0);

    while (!q.empty())
    {
        int nod = q.front();
        q.pop();

        if (A.F.find(nod) != A.F.end())
            return false;

        for (iEpsilon = A.Epsilon.begin(); iEpsilon != A.Epsilon.end(); iEpsilon++)
        {
            iDelta = A.delta.find(make_pair(nod, *iEpsilon));
            if (iDelta != A.delta.end())
                for (iStari = iDelta->second.begin(); iStari != iDelta->second.end(); iStari++)
                    if (viz.find(*iStari) == viz.end())
                    {
                        viz.insert(*iStari);
                        q.push(*iStari);
                    }
        }
    }
    return true;
}

Graf redenumireGrafB(Graf A, Graf B)
{
    Graf C;
    int k = 1;
    set <int> ::iterator iQ;
    map <int, int> redenumire;
    for (iQ = B.Q.begin(); iQ != B.Q.end(); iQ++)
    {
        while (A.Q.find(k) != A.Q.end())
            k++;
        redenumire.insert(make_pair(*iQ, k));
        C.Q.insert(k);

        if (*iQ == B.q0)
            C.q0 = k;

        if (B.F.find(*iQ) != B.F.end())
            C.F.insert(k);
        k++;
    }
    set <char> ::iterator iEpsilon;
    for (iEpsilon = B.Epsilon.begin(); iEpsilon != B.Epsilon.end(); iEpsilon++)
            C.Epsilon.insert(*iEpsilon);

    set <int> ::iterator iStari;
    map <pair <int, char>, set <int> > ::iterator iDelta;

    for (iDelta = B.delta.begin(); iDelta != B.delta.end(); iDelta++)
    {
        for (iStari = iDelta->second.begin(); iStari != iDelta->second.end(); iStari++)
        {
            int x = redenumire.find(iDelta->first.first)->second;
            char y = iDelta->first.second;
            int z = redenumire.find(*iStari)->second;

            map <pair <int, char>, set <int> > ::iterator iDelta2;
            iDelta2 = C.delta.find(make_pair(x, y));
            if (iDelta2 != C.delta.end())
                iDelta2->second.insert(z);
            else
            {
                set <int> auxSet;
                auxSet.insert(z);
                C.delta.insert(make_pair(make_pair(x, y), auxSet));
            }
        }
    }
    return C;
}

Graf reuniune(Graf A, Graf B)
{
    B = redenumireGrafB(A, B);
    set <int> ::iterator iQ;
    for (iQ = B.Q.begin(); iQ != B.Q.end(); iQ++)
    {
        A.Q.insert(*iQ);
        if (B.F.find(*iQ) != B.F.end())
            A.F.insert(*iQ);
    }
    set <char> ::iterator iEpsilon;
    for (iEpsilon = B.Epsilon.begin(); iEpsilon != B.Epsilon.end(); iEpsilon++)
            A.Epsilon.insert(*iEpsilon);

    set <int> ::iterator iStari;
    map <pair <int, char>, set <int> > ::iterator iDelta;

    for (iDelta = B.delta.begin(); iDelta != B.delta.end(); iDelta++)
    {
        for (iStari = iDelta->second.begin(); iStari != iDelta->second.end(); iStari++)
        {
            int x = iDelta->first.first;
            char y = iDelta->first.second;
            int z = *iStari;

            map <pair <int, char>, set <int> > ::iterator iDelta2;
            iDelta2 = A.delta.find(make_pair(x, y));
            if (iDelta2 != A.delta.end())
                iDelta2->second.insert(z);
            else
            {
                set <int> auxSet;
                auxSet.insert(z);
                A.delta.insert(make_pair(make_pair(x, y), auxSet));
            }
        }
    }

    set <int> auxSet;
    auxSet.insert(A.q0);
    auxSet.insert(B.q0);

    int k = -1;
    while (A.Q.find(k) != A.Q.end())
        k--;
    A.Q.insert(k);
    A.q0 = k;

    A.delta.insert(make_pair(make_pair(k, '.'), auxSet));

    return A;
}

set <int> veciniNod(set <int> nod, char litera, map <pair <int, char>, set <int> > delta)
{
    set <int> vecini;
    set <int> ::iterator it;
    set <int> ::iterator iStari;
    map <pair <int, char>, set <int> > ::iterator iDelta;
    for (it = nod.begin(); it != nod.end(); it++)
    {
        iDelta = delta.find(make_pair(*it, litera));
        if (iDelta != delta.end())
            for (iStari = iDelta->second.begin(); iStari != iDelta->second.end(); iStari++)
                vecini.insert(*iStari);
    }
    return vecini;
}

bool intersectieF(set <int> nod, set <int> F1, set <int> F2)
{
    set <int> ::iterator iNoduri;
    set <int> ::iterator iF;
    int ok1, ok2, megaOk1, megaOk2;
    megaOk1 = megaOk2 = 0;

    for (iNoduri = nod.begin(); iNoduri != nod.end(); iNoduri++)
    {
        ok1 = ok2 = 0;
        if (F1.find(*iNoduri) != F1.end())
        {
            ok1 = 1;
            megaOk1 = 1;
        }
        if (F2.find(*iNoduri) != F2.end())
        {
            ok2 = 1;
            megaOk2 = 1;
        }
        if (ok1 == 0 && ok2 == 0)
            return false;
    }
    if (megaOk1 && megaOk2)
        return true;
    return false;
}

Graf LNFAtoDFA(Graf A, set <int> F1, set <int> F2)
{
    Graf B;
    B.Epsilon = A.Epsilon;
    B.q0 = 1;
    B.Q.insert(1);

    set <int> nod;
    queue <set <int> > q;
    map <set <int>, int> redenumire;

    nod.insert(A.q0);
    nod = inchidere(nod, A.delta);
    q.push(nod);
    redenumire.insert(make_pair(nod, 1));
    int k = 2;

    set <char> ::iterator iEpsilon;
    map <pair <int, char>, set <int> > ::iterator iDelta;

    while (!q.empty())
    {
        nod = q.front();
        q.pop();

        set <int> nodNou;
        for (iEpsilon = A.Epsilon.begin(); iEpsilon != A.Epsilon.end(); iEpsilon++)
        {
            nodNou = veciniNod(inchidere(nod, A.delta), *iEpsilon, A.delta);
            if (nodNou.empty())
                continue;
            if (redenumire.find(nodNou) == redenumire.end())
            {
                redenumire.insert(make_pair(nodNou, k));
                B.Q.insert(k);
                k++;
                q.push(nodNou);
            }
            int x = redenumire.find(nod)->second;
            char y = *iEpsilon;
            int z = redenumire.find(nodNou)->second;

            iDelta = B.delta.find(make_pair(x, y));
            if (iDelta != B.delta.end())
                iDelta->second.insert(z);
            else
            {
                set <int> auxSet;
                auxSet.insert(z);
                B.delta.insert(make_pair(make_pair(x, y), auxSet));
            }
        }
    }

    map <set <int>, int> ::iterator it;
    for (it = redenumire.begin(); it != redenumire.end(); it++)
        if (intersectieF(it->first, F1, F2))
            B.F.insert(it->second);

    B = completare(B);
    return B;
}

Graf intersectie(Graf A, Graf B)
{
    B = redenumireGrafB(A, B);
    Graf C = LNFAtoDFA(reuniune(complement(A), complement(B)), A.F, B.F);
    return C;
}

bool sunt_echivalente(Graf A, Graf B)
{
    B = redenumireGrafB(A, B);
    Graf cA = complement(A);
    Graf cB = complement(B);
    return (e_vid(intersectie(cA, B)) && e_vid(intersectie(A, cB)) && e_vid(A) == e_vid(B));
}

int main()
{
    Graf A, B;

    citire_QEFD(A.Q, A.Epsilon, A.q0, A.F, A.delta, f);
    citire_QEFD(B.Q, B.Epsilon, B.q0, B.F, B.delta, f);

    if (sunt_echivalente(A, B))
        g<<"Sunt echivalente\n";
    else
        g<<"Nu sunt echivalente\n";

    return 0;
}
