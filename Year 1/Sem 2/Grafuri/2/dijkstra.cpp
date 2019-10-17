#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

ifstream fin("data.in");
ofstream fout("data.out");

int v[10001][10001];

void dijkstra(int start, int n)
{
    int dist[n+1];
    int viz[n+1] = {0};

    for (int i = 0; i <=n; i++)
        dist[i] = 99999999;
    dist[start] = 0;

    queue<int> myq;
    myq.push(start);

    while (!myq.empty())
    {
        int minim, urm = 0, crt;
        crt = myq.front();
        myq.pop();
        viz[crt] = 1;
        minim = 99999999;
        for (int i = 1; i <= n; i++)
        {
            if (dist[crt] + v[crt][i] < dist[i])
                dist[i] = dist[crt] + v[crt][i];
            if (dist[i] < minim && viz[i] == 0)
            {
                minim = dist[i];//v[crt][i];
                urm = i;
            }
        }
        if (urm > 0)
            myq.push(urm);
    }

    for (int i = 0; i <=n; i++)
        if (dist[i] == 99999999)
            dist[i] = 0;

    for (int i = 1; i <= n; i++)
        if (i != start)
            fout<<dist[i]<<" ";
}

int main()
{
    int n, m;
    fin>>n>>m;

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            v[i][j] = 99999999;

    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        fin>>x>>y>>z;
        v[x][y] = z;
    }

    dijkstra(1, n);

    return 0;
}
