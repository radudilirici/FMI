#include <iostream>
#include <fstream>
#include <string.h>
#include <queue>

using namespace std;

ifstream f("data.in");
ofstream g("data.out");

int delta[15000][27][1000];

vector<int> inchidere(int nod, int j)
{
    vector<int> v;
    int vizitat[15000] = {0};

    v.push_back(nod);
    vizitat[nod] = 1;

    queue<int> Q;
    Q.push(nod);
    while (!Q.empty())
    {
        int frnt = Q.front();
        for (int i = 1; i <= delta[frnt][26][0]; i++)
        {
            if (!vizitat[delta[frnt][26][i]])
            {
                Q.push(delta[frnt][26][i]);
                v.push_back(delta[frnt][26][i]);
                vizitat[delta[frnt][26][i]] = 1;
            }
        }
        Q.pop();
    }
    return v;
}

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
        if (y == '.')
            y = 'a' + 26;
        delta[x][y - 'a'][0]++;
        delta[x][y - 'a'][delta[x][y - 'a'][0]] = z;
    }

    f>>cuvinte;
    char w[51];
    int lungime, ok;
    f.getline(w, 5); //enter-ul

    queue <int> q;
    int frnt;

    vector<int> lambda_inchidere;

    for (int i = 0; i < cuvinte; i++)
    {
        f.getline(w, 50);
        lungime = strlen(w);

        lambda_inchidere = inchidere(q0, i);
        for (unsigned int l = 0; l < lambda_inchidere.size(); l++)
            q.push(lambda_inchidere[l]);
        lambda_inchidere.clear();

        q.push(-1);
        ok = 0;

        for (int j = 0; j < lungime; j++)
        {
            while (1)
            {
                frnt = q.front();
                if (frnt == -1)
                {
                    q.pop();
                    break;
                }
                for (int k = 1; k <= delta[frnt][w[j] - 'a'][0]; k++)
                {
                    aux = delta[frnt][w[j] - 'a'][k];
                    lambda_inchidere = inchidere(aux, i);
                    for (unsigned int l = 0; l < lambda_inchidere.size(); l++) //punem in coada toate inchiderile lambda
                        q.push(lambda_inchidere[l]);
                    lambda_inchidere.clear();
                }

                q.pop();
                if (q.empty())
                    break;
            }
            q.push(-1); //marcam dupa fiecare litera ca sa stim unde ne oprim data viitoare
        }
        while (!q.empty())
        {
            for (int j = 0; j < finale; j++)
            {
                frnt = q.front();
                if (frnt == F[j])
                {
                    g<<"DA\n";
                    ok = 1;
                    break;
                }
            }
            q.pop();
            if (ok == 1)
                break;
        }
        if (ok == 0)
            g<<"NU\n";
        while(!q.empty())
            q.pop();
    }

    return 0;
}
