#include <iostream>

using namespace std;

int main()
{
    int i = 2, j;
    const int c = 0; //trebuie initializat
    //c = 1;
    //int &r = c; pentru ca am putea face r = 1, dar nu avem voie
    ///I
    const int *cp; //pointer la valoare constanta
    int const *cp1;//echivalente
    cp = &i;
    i = 1;
    //*cp = 1;
    int *p;
    //p = cp; pentru ca am putea face *p = 1, dar nu avem voie

    ///II
    int * const pc = &i; //pointer constant. trebuie initializat
    i = 1;
    *pc = 2;
    //pc = &j;

    ///III
    int const * const cpc = &i; //pointer constant la valoare constanta. trebuie initializat
    //cpc = &j;
    //*cpc = 2;

    ///IV
    const int &cr = i;
    int const &cr1 = j;
    //cr = 1;

    return 0;
}
