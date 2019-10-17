#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

ifstream f("data.in");

int delta[1000][1000];

int main()
{

    int n, m, x, y, z, q0, lungime;
    char w[50];

    f>>q0;
    f>>n;
    for (int i = 1; i <= n; i++)
    {
        f>>x>>y>>z;
        delta[x][y] = z;
    }
    f>>m;
    for (int i = 1; i <= m; i++)
    {
        x = q0;
        f.get(w, 50);
        lungime = strlen(w);
        for (int j = 0; j < lungime; j++)
            x = delta[x][(int)w[j]];
        ///if x apartine lui F cout<<DA
    }

    return 0;
}
