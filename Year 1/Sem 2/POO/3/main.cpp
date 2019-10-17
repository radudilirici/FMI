#include <iostream>

using namespace std;

class B
{
    int priv = 10;
protected:
    int protec = 10;
public:
    int pub = 10;

    void setpub(int pub_nou = 0) {pub = pub_nou;}

    void h(){cout<<"hB\n";}

    B(int j = 0) {priv = protec = pub = j; cout<<"constructor B\n";}
    B(const B&ob) {priv = ob.priv; protec = ob.protec; pub = ob.pub; cout<<"constructor de copiere B\n";}
    ~B() {cout<<"destructor B\n";}

    B& operator=(const B& ob)
    {
        priv = ob.priv;
        protec = ob.protec;
        pub = ob.pub;
        return *this;
    }
};

class D:public B
{
    int y;
public:
    void out()
    {
        cout<<y<<"\n";
        cout<<protec<<"\n";
        cout<<pub<<"\n";
    }

    void sety(int y_nou = 0) {y = y_nou;}

    void h(){cout<<"hD\n";}

    D(int j = 0):B(j) { cout<<"constructor D\n";}
    D(const D&od):B(od) {y = od.y; cout<<"constructor de copiere D\n";}
    ~D() {cout<<"destructor D\n";}

    D& operator=(const D&od)
    {
        this->B::operator=(od);
        y = od.y;
        return *this;
    }
};

int main()
{
    D ob(1);
    ob.sety(3);
    ob.setpub(-1);

    D ob2 = ob;
    ob2.out();

    D ob3;
    ob3 = ob2;
    ob3.out();

    ob3.h();
    ob3.B::h();

    return 0;
}
