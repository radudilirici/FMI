#include <iostream>

using namespace std;

class B
{
    static int s; //acelasi pt toate obiectele
    static const int i = 2;
public:
    B(int i)//:s(i)
    {s = i;}
    static void g(){} //pt a folosi datele statice
    //void g(){}
};

int B::s; //eroare de compilare daca nu facem asta (alocare de memorie)

int main()
{
    /**
    B::s = 1;
    B ob;
    ob.s = 1; //acelasi lucru*/
    B::g();
    return 0;
}
