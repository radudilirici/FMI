#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

#define pb push_back
#define mp make_pair

using namespace std;

struct CFG
{
    vector <char> N; //Nonterminale
    vector <char> T; //Terminale
    map <char, vector <string> > P; //Productii
    char S; //Start
    vector <char> NUL; //Nonterminale care duc in Lambda
};

void adauga(map <char, vector <string> >& P, char from, string to)
{
    map <char, vector <string> >::iterator it = P.find(from);
    if (it != P.end())
    {
        it->second.pb(to);
    }
    else
    {
        vector <string> v;
        v.pb(to);
        P.insert(mp(from, v));
    }
}

void citire(CFG& G, istream& fin)
{
    int n, m, nr;
    char aux;
    string auxs;

    fin>>n;
    for (int i = 0; i < n; i++)
    {
        fin>>aux;
        G.N.pb(aux);
    }

    fin>>m;
    for (int i = 0; i < m; i++)
    {
        fin>>aux;
        G.T.pb(aux);
    }

    fin>>G.S;

    fin>>nr;
    for (int i = 0; i < nr; i++)
    {
        fin>>aux;
        fin>>auxs;
        if (auxs == ".")
            auxs.erase();
        adauga(G.P, aux, auxs);
    }
}

void afisare(const CFG& G, ostream& fout)
{
    fout<<G.N.size()<<"\n";
    for (int i = 0; i < (int)G.N.size(); i++)
        fout<<G.N[i]<<" ";

    fout<<"\n"<<G.T.size()<<"\n";
    for (int i = 0; i < (int)G.T.size(); i++)
        fout<<G.T[i]<<" ";

    fout<<"\n"<<G.S<<"\n";

    fout<<G.P.size()<<"\n";
    map <char, vector <string> >::const_iterator it;
    for (it = G.P.begin(); it != G.P.end(); it++)
    {
        fout<<it->first<<" -> ";
        for (int j = 0; j < (int)it->second.size(); j++)
            if (it->second[j] == "")
                fout<<". ";
            else
                fout<<it->second[j]<<" ";
        fout<<"\n";
    }
}

char min(CFG G)
{
    vector <char>::iterator it;
    for (char A = '@'; A <= 'Z'; A++)
    {
        it = find(G.N.begin(), G.N.end(), A);
        if (it == G.N.end())
            return A;
    }
    return '0';
}

void START(CFG& G)
{
    char newS = min(G);
    G.N.pb(newS);

    vector <string> v;
    string S;
    S += G.S;
    v.pb(S);
    G.P.insert(mp(newS, v));
    G.S = newS;
}

void TERM(CFG& G)
{
    map <char,  char> rename;
    for (int i = 0; i < (int)G.T.size(); i++)
    {
        char newN = min(G);
        rename.insert(mp(G.T[i], newN));
        G.N.pb(newN);
    }

    map <char, vector <string> >::iterator it;
    for (it = G.P.begin(); it != G.P.end(); it++)
        for (int i = 0; i < (int)it->second.size(); i++)
            for (int j = 0; j < (int)it->second[i].size(); j++)
            {
                vector <char>::iterator t = find(G.T.begin(), G.T.end(), it->second[i][j]); //verificam daca e terminal
                if (t != G.T.end())
                    it->second[i][j] = rename.find(it->second[i][j])->second;
            }

    for (int i = 0; i < (int)G.T.size(); i++)
    {
        string T;
        T += G.T[i];
        adauga(G.P, rename.find(G.T[i])->second, T);
    }
}

void micsoreaza(CFG& G, string& mare)
{
    if (mare.size() >= 2)
    {
        char newN = min(G);
        G.N.pb(newN);

        string newNs;
        newNs += newN;
        string s (mare, 1);
        adauga(G.P, newN, s);

        mare.replace(1, mare.size(), newNs);

        map <char, vector <string> >::iterator it = G.P.find(newN);
        micsoreaza(G, it->second[0]);
    }
}

void BIN(CFG& G)
{
    map <char, vector <string> >::iterator it;
    for (it = G.P.begin(); it != G.P.end(); it++)
        for (int i = 0; i < (int)it->second.size(); i++)
        {
            string& mare = it->second[i];
            micsoreaza(G, mare);
        }
}

bool adauga_NUL(CFG& G)
{
    int ok = 0;
    map <char, vector <string> >::iterator it;
    for (it = G.P.begin(); it != G.P.end(); it++)
    {
        vector <char>::iterator e_deja = find(G.NUL.begin(), G.NUL.end(), it->first);
        if (e_deja != G.NUL.end())
            continue;
        for (int i = 0; i < (int)it->second.size(); i++)
            if (it->second[i] == "")
            {
                G.NUL.push_back(it->first);
                ok = 1;
                break;
            }
    }
    if (ok)
        return true;
    return false;
}

vector <string> lambda_inlocuiri_de_2(const CFG& G, const vector <string> productii, const string& s)
{
    vector <string> to_return;
    int unu = 0, doi = 0;
    string a, b, c;
    a += s[0];
    b += s[1];

    if (s.size() == 1)
    {
        if (find(G.NUL.begin(), G.NUL.end(), s[0]) != G.NUL.end())
            to_return.push_back(c);
        return to_return;
    }

    if (find(G.NUL.begin(), G.NUL.end(), s[0]) != G.NUL.end())
        doi = 1;
    if (find(G.NUL.begin(), G.NUL.end(), s[1]) != G.NUL.end())
        unu = 1;

    if (unu)
        if (find(productii.begin(), productii.end(), a) == productii.end())
            to_return.push_back(a);

    if (doi)
        if (find(productii.begin(), productii.end(), b) == productii.end())
            to_return.push_back(b);

    if (unu && doi)
        if (find(productii.begin(), productii.end(), c) == productii.end())
            to_return.push_back(c);

    return to_return;
}

void DEL_lambda(CFG& G)
{
    map <char, vector <string> >::iterator it;
    for (it = G.P.begin(); it != G.P.end(); it++)
    {
        if (find(G.NUL.begin(), G.NUL.end(), it->first) == G.NUL.end() || it->first == G.S)
            continue;
        for (int i = 0; i < (int)it->second.size();)
            if (it->second[i] == "")
                it->second.erase(it->second.begin() + i);
            else
                i++;
    }
}

void DEL(CFG& G)
{
    while (adauga_NUL(G))
    {
        map <char, vector <string> >::iterator it;
        for (it = G.P.begin(); it != G.P.end(); it++)
            for (int i = 0; i < (int)it->second.size(); i++)
            {
                vector <string> aux = lambda_inlocuiri_de_2(G, it->second, it->second[i]);
                for (int j = 0; j < (int)aux.size(); j++)
                    if (find(it->second.begin(), it->second.end(), aux[j]) == it->second.end())
                        it->second.push_back(aux[j]);
            }
    }
    DEL_lambda(G);
}

void eliminare(CFG& G, char vechi, char nou)
{
    map <char, vector <string> >::iterator it;
    string sN;
    sN += nou;
    for (it = G.P.begin(); it != G.P.end(); it++)
    {
        for (int i = 0; i < (int)it->second.size(); i++)
            for (int j = 0; j < (int)it->second[i].size(); j++)
            {
                if (it->second[i][j] == vechi)
                    it->second[i].replace(j, 1, sN);
            }
    }
}

vector <string> productii_din(CFG& G, char N)
{
    map <char, vector <string> >::iterator it;
    for (it = G.P.begin(); it != G.P.end(); it++)
        if (it->first == N)
            return it->second;
    vector <string> aux;
    return aux;
}

void UNIT(CFG& G)
{
    map <char, vector <string> >::iterator it;
    vector <string> aux;

    for (it = G.P.begin(); it != G.P.end();)
    {
        if (it->second.size() == 1 && it->second[0].size() == 1 && find(G.N.begin(), G.N.end(), it->second[0][0]) != G.N.end())
        {
            eliminare(G, it->first, it->second[0][0]);
            if (it->first == G.S)
                G.S = it->second[0][0];

            vector <char>::iterator remove_from_N = find(G.N.begin(), G.N.end(), it->first);
            G.N.erase(remove_from_N);

            map <char, vector <string> >::iterator it2 = it;
            it++;
            G.P.erase(it2);
        }
        else
            it++;
    }

    int ok = 1;
    while (ok)
    {
    ok = 0;
        for (it = G.P.begin(); it != G.P.end();it ++)
        {
            for (int i = 0; i < (int)it->second.size(); i++)
            {
                if (it->second[i].size() == 1 && find(G.N.begin(), G.N.end(), it->second[i][0]) != G.N.end())
                {
                    aux = productii_din(G, it->second[i][0]);

                    for (int j = 0; j < (int)aux.size(); j++)
                    {
                        if (find(it->second.begin(), it->second.end(), aux[j]) == it->second.end())
                            it->second.push_back(aux[j]);
                    }
                    it->second.erase(it->second.begin() + i);
                    ok = 1;
                }
            }
        }
    }
}

int position(const vector <char>& N, char c)
{
    for (int i = 0; i < (int)N.size(); i++)
        if (N[i] == c)
            return i+1;
    return 0;
}

bool CYK(CFG G, string s)
{
    int n = s.size();
    int r = G.N.size();
    bool M[n+1][n+1][r+20];
    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < n + 1; j++)
            for (int k = 0; k < r + 1; k++)
                M[i][j][k] = false;

    map <char, vector <string> >::iterator it;
    for (int i = 1; i < n + 1; i++)
    {
        for (it = G.P.begin(); it != G.P.end(); it++)
        {
            for (int j = 0; j < (int)it->second.size(); j++)
            {
                if (it->second[j][0] == s[i-1] && it->second[j].size() == 1)
                {
                    //cout<<i<<" "<<it->first<<"\n";
                    int a = position(G.N, it->first);
                    M[1][i][a] = true;
                }
            }
        }
    }
    //cout<<"\n\n";

    for (int i = 2; i < n + 1; i++)
    {
        for (int j = 1; j < n - i + 2; j++)
        {
            for (int k = 1; k < i ; k++)
            {
                for (it = G.P.begin(); it != G.P.end(); it++)
                {
                    for (int l = 0; l < (int)it->second.size(); l++)
                    {
                        if (it->second[l].size() < 2)
                            continue;
                        //if (i == 2 && j == 1)
                        //cout<<it->first<<"  "<<it->second[l]<<"\n";
                        int a = position(G.N, it->first);
                        int b = position(G.N, it->second[l][0]);
                        int c = position(G.N, it->second[l][1]);
                        /*if (i == 2 && j == 1)
                        {
                            if (M[k][j][b])
                                cout<<"1 ";
                            else
                                cout<<"0 ";
                            if (M[i-k][j+k][c])
                                cout<<"1 ";
                            else
                                cout<<"0 ";
                            cout<<"\n";
                        }*/
                        //cout<<a<<" "<<b<<" "<<c<<"\n";
                        if (M[k][j][b] && M[i-k][j+k][c])
                            M[i][j][a] = true;
                    }
                }
            }
        }
    }

    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n - i + 1; j++)
        {
            int ok = 0;
            for (int k = 1; k < r + 1; k++)
                if (M[i][j][k])
                {
                    ok = 1;
                    break;
                }
            cout<<ok<<" ";
        }
        cout<<"\n";
    }

    return M[n][1][1];
}

void CFG_to_CNF(CFG& G)
{
    START(G);
    TERM(G);
    BIN(G);
    DEL(G);
    UNIT(G);
}

int main()
{
    ifstream fin("data.in");
    ofstream fout("data.out");
    if (!fin)
    {
        cout<<"Nu exista data.in\n";
        return 1;
    }

    CFG G;
    citire(G, fin);
    CFG_to_CNF(G);

    afisare(G, cout);
    cout<<"\n";

    if (CYK(G, "([aaa])[]aa(()[]a)aaaaaaaa"))
        cout<<"\nDA";
    else
        cout<<"\nnu...";

    return 0;
}
