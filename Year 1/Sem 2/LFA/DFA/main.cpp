#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

ifstream f("data.in");
ofstream g("data.txt");

int delta[15000][26];

int main()
{
    int stari, litere, q0, finale, tranzitii, cuvinte;
    int F[15000];
    int aux;
    char aux2;

    f>>stari;
    for (int i = 0; i < stari; i++)
        f>>aux;

    f>>litere;
    for (int i = 0; i < litere; i++)
        f>>aux2;

    f>>q0;

    f>>finale;
    for (int i = 0; i < finale; i++)
        f>>F[i];

    f>>tranzitii;
    int x, z;
    char y;
    for (int i = 0; i < tranzitii; i++)
    {
        f>>x>>y>>z;
        delta[x][y - 'a'] = z;
    }

    f>>cuvinte;
    char w[51];
    int lungime, ok;
    f.getline(w, 50); //enter-ul
    for (int i = 0; i < cuvinte; i++)
    {
        f.getline(w, 50);
        lungime = strlen(w);
        x = q0;
        ok = 0;
        for (int j = 0; j < lungime; j++)
            x = delta[x][w[j] - 'a'];
        for (int j = 0; j < finale; j++)
            if (x == F[j])
            {
                g<<"DA\n";
                ok = 1;
                break;
            }
        if (ok == 0)
            g<<"NU\n";
    }

    return 0;
}
