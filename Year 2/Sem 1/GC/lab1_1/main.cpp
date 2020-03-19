#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("date.in");

struct punct{
    float x, y, z;
};

int main()
{
    punct A[4];
    for(int i = 1; i <= 3; i++)
        fin>>A[i].x>>A[i].y>>A[i].z;

    if (A[1].x == A[2].x && A[1].y == A[2].y && A[1].z == A[2].z){
        cout<<"Punctele sunt coliniare\n";
        cout<<"A2 = 1 * A1 + 0 * A3\n";
        return 0;
    }

    if (A[1].x != A[2].x){
        float a = (A[3].x - A[1].x)/(A[2].x - A[1].x);

        if (A[3].y - A[1].y != a*(A[2].y - A[1].y)){
            cout<<"Punctele nu sunt coliniare\n";
            return 0;
        }
        if (A[3].z - A[1].z != a*(A[2].z - A[1].z)){
            cout<<"Punctele nu sunt coliniare\n";
            return 0;
        }

        cout<<"Punctele sunt coliniare\n";
        cout<<"A3 = "<<1-a<<" * A1 + "<<a<<" * A2";
        return 0;
    }

    if (A[1].y != A[2].y){
        float a = (A[3].y - A[1].y)/(A[2].y - A[1].y);

        if (A[3].x - A[1].x != a*(A[2].x - A[1].x)){
            cout<<"Punctele nu sunt coliniare\n";
            return 0;
        }
        if (A[3].z - A[1].z != a*(A[2].z - A[1].z)){
            cout<<"Punctele nu sunt coliniare\n";
            return 0;
        }

        cout<<"Punctele sunt coliniare\n";
        cout<<"A3 = "<<1-a<<" * A1 + "<<a<<" * A2";
        return 0;
    }

    if (A[1].z != A[2].z){
        float a = (A[3].z - A[1].z)/(A[2].z - A[1].z);

        if (A[3].y - A[1].y != a*(A[2].y - A[1].y)){
            cout<<"Punctele nu sunt coliniare\n";
            return 0;
        }
        if (A[3].x - A[1].x!= a*(A[2].x - A[1].x)){
            cout<<"Punctele nu sunt coliniare\n";
            return 0;
        }

        cout<<"Punctele sunt coliniare\n";
        cout<<"A3 = "<<1-a<<" * A1 + "<<a<<" * A2";
        return 0;
    }

    return 0;
}
