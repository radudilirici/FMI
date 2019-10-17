#include <iostream>

using namespace std;

class B
{
public:
    B() {cout<<"B cons\n";}
    virtual ~B() {cout<<"B des\n";}

    void fnv() {cout<<"B fnv\n";}
    virtual void fv() {cout<<"B fv\n";}

    void g() {fnv(); fv();}
};

class D:public B
{
public:
    D() {cout<<"D cons\n";}
    ~D() {cout<<"D des\n";}

    void fnv() {cout<<"D fnv\n";}
    void fv() {cout<<"D fv\n";}

    void h() {cout<<"D h\n";}
};

class forma ///clasa abstracta
{
public:
    virtual void arie() = 0; //trebuie redefinita in subclasa
    virtual void perimetru() = 0; //clasa se numeste abstracta daca are cel putin una de-asta
};

class cerc: public forma
{
    float raza;
public:
    cerc(float r = 0) {raza = r;}

    void arie() {cout<<3.14*raza*raza;}
    void perimetru() {cout<<2*3.14*raza;}
};

int main()
{
    /**
    D od;
    B &rb = od;
    B *pb = &od;

    rb.g();
    pb->g();
    //rb.h();
    //pb->h();*/

    /**
    B *pB = new D;
    delete pB;*/

    /**
    D od;
    B *pB = &od;
    delete pB;//CRASH*/

    /**
    B ob;
    D *pd = (D*)&ob;///NU FACI ASA!!!*/

    /**
    B *pB = new B;
    D *pD = static_cast<D*>(pB);///o face la compilare (daca e sa nu mearga, iti zice de la inceput)
    D *pD2 = dynamic_cast<D*>(pB);///o face la executie. trebuie sa fie cel putin o functie virtuala (sa fie polimorfice clasele)*/

    ///partea a doua

    //forma f;
    cerc r(2);
    r.arie();

    return 0;
}
