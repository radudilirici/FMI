#include <iostream>

using namespace std;

class B
{
    int nc;
    const int c;
public:
    B(int i = 0):c(i)
    {
        nc = i;
        //c = i;
    }
    int &fc()
    {
        return nc;
        //return c
    }
    void f()
    {
        cout<<nc<<" "<<c<<"\n";
    }
    void fc() const //nu putem sa modificam obiectul actual
    {
        //nc = 1;
        //c = 1;
        B ob;
        ob.nc = 1;
        //ob.c = 1;
        //f(); //metodele constante apeleaza doar metode constante
    }
    int &frc() const
    {
        //return nc;
        //return c;
    }
    int &fr()
    {
        return nc;
        //return c;
    }
};

void g(B &ob)
{
    cout<<"mesaj\n";
}

int main()
{
    B ob(3);
    ob.f();
    const B oc(2);
    //oc.fr();
    //g(oc);
    g(ob);
    return 0;
}
