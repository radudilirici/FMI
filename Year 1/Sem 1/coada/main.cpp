#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

ifstream fin("data.in");
ofstream fout("data.out");

void push(int v[], int &n, int x)
{
    v[n] = x;
    n++;
}

void pop(int v[], int &n)
{
    n--;
    for (int i = 0; i < n; i++)
        v[i] = v[i+1];
}

int front(int v[])
{
    return v[0];
}

int main()
{
    int v[1000];
    int n = 0;
    int aux, nr_i;
    char s[10];

    //fin>>nr_i;
    while (fin>>s)
    {
        if (strcmp(s, "push") == 0)
        {
            fin>>aux;
            push(v, n, aux);
        }
        else if (strcmp(s, "pop") == 0)
            pop(v, n);
        else if (strcmp(s, "front") == 0)
            fout<<front(v)<<"\n";
    }

    return 0;
}
