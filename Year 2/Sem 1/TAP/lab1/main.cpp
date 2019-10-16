/**
2SUM:
    ordonez si folosesc doi pointeri, unul la stanga si unul la dreapta

3SUM:
    parcurg fiecare element si fac 2SUM pe ce ramane
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

ifstream fin("data.in");
int n, a, b, c;
vector<int> v;

void print (vector<int>& w){
    for (vector<int>::iterator it = w.begin(); it < w.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
}

int main()
{
    fin>>n;

    for(int i = 0; i < n; i++){
            fin>>a;
            v.push_back(a);
    }

    v.resize(n);
    sort(v.begin(),v.end());

    print(v);

    for (int k = 0; k < v.size(); k++){
        int i = k+1;
        int j = n-1;
        while (i < j){
            int sum = v[i] + v[j] + v[k];

            if (sum < 0){
                while (v[i] == v[i+1] && i+1 < n)
                    i++;
                i++;
            }
            else if (sum > 0){
                while (v[j] == v[j-1] && j-1 > 0)
                    j--;
                j--;
            }
            else{
                cout<<v[k]<<" "<<v[i]<<" "<<v[j]<<"\n";
                while (v[i] == v[i+1] && i+1 < n)
                    i++;
                i++;
                while (v[j] == v[j-1] && j-1 > 0)
                    j--;
                j--;
            }
        }
        while (v[k] == v[k+1])
            k++;
    }


    return 0;
}
