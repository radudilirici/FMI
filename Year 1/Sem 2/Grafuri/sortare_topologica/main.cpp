#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

ifstream f("sortaret.in");
ofstream g("sortaret.out");

vector<int> adiacenta[50001];
vector<int> vizitat;
stack<int> stiva;

void dfs(int nod)
{
    vizitat[nod] = 1;
    int vecini = adiacenta[nod].size();
    for (int i = 0; i < vecini; i++)
        if(vizitat[adiacenta[nod][i]] == 0)
            dfs(adiacenta[nod][i]);
    stiva.push(nod);
}

int main()
{
    int n, m;
    f>>n>>m;

    int x, y;
    for (int i = 0; i < m; i++)
    {
        f>>x>>y;
        adiacenta[x].push_back(y);
    }

    vizitat.resize(n+1, 0);

    for (int i = 1; i <=n; i++)
        if (vizitat[i] == 0)
            dfs(i);

    for (int i = 0; i < n; i++)
    {
        g<<stiva.top()<<" ";
        stiva.pop();
    }

    return 0;
}
