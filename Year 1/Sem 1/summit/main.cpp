#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("summit.in");
ofstream fout("summit.out");

int v[1000002],s[1000002];

int cbin(int st, int dr, int x)
{
    if (st==dr){
        if (s[st]==x)
            return st;
        else return 0;}
    int mij=(st+dr)/2;
    if (s[mij]==x)
        return mij;
    else if (x<s[mij])
        return cbin(st,mij,x);
    else
        return cbin(mij+1,dr,x);
    return 0;
}

int main()
{
    int n;
    fin>>n;
    for (int i=1;i<=n;i++)
    {
        fin>>v[i];
        s[i]=s[i-1]+v[i];
    }
    for (int i=1;i<=n;i++)
        fout<<cbin(1,n,v[i])<<"\n";

    return 0;
}
