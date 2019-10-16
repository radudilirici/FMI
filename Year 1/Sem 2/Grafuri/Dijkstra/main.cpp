#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#define nmax 50001
#define INF 9999999

using namespace std;

ifstream f("dijkstra.in");
ofstream g("dijkstra.out");

priority_queue <pair<int, int> > myheap;
vector <pair<int, int> > v[nmax];
vector <int> dist(nmax, INF);
vector <int> viz(nmax);

int main()
{
    int N, M, x, y, cost;
    f>>N>>M;



    for (int i = 1; i <= M; i++)
    {
        f>>x>>y>>cost;
        v[x].push_back(make_pair(y, cost));
    }

    /*for (int i = 0; i <= N; i++)
        dist[i] = INF;*/
    dist[1] = 0;

    myheap.push(make_pair(0, 1));

    while (!myheap.empty())
    {
        int index = myheap.top().second;
        myheap.pop();
        if (viz[index])
            continue;

        for (int i = 0; i < (int)v[index].size(); i++)
        {
            pair <int, int> it = v[index][i];
            if (dist[it.first] > dist[index] + it.second && viz[it.first] == 0)
            {
                dist[it.first] = dist[index] + it.second;
                myheap.push(make_pair(-dist[it.first], it.first));
            }
        }
        viz[index] = 1;
    }

    for (int i = 2; i <= N; i++)
        if (dist[i] < INF)
            g<<dist[i]<<" ";
        else
            g<<"0 ";

    return 0;
}
