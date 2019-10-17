#include <iostream>

using namespace std;

class complex
{
    float re, im;

public:
    complex();
    complex(float);
    complex(float, float);
    complex(const complex&);
    ~complex();
    void operator=(const complex&);
    complex suma(complex);
    void citire();
    void afisare();
};

complex::complex()
{
    cout<<"creare 1\n";
    this->re = this->im = 0;
}

complex::complex(float re)
{
    cout<<"creare 2\n";
    this->re = re;
}

complex::complex(float re, float im)
{
    cout<<"creare 3\n";
    this->re = re;
    this->im = im;
}

complex::complex(const complex& ob)
{
    cout<<"copiere\n";
    this->re = ob.re;
    this->im = ob.im;
}

complex::~complex()
{
    cout<<"obiect distrus\n";
}

void complex::operator=(const complex& ob)
{
    cout<<"=\n";
    this->re = ob.re;
    this->im = ob.im;
}

void complex::citire()
{
    cin>>this->re>>this->im;
}

void complex::afisare()
{
    cout<<"<< "<<this->re<<" "<<this->im<<"\n";
}

complex complex::suma(complex ob)
{
    complex aux;// = new complex;
    aux.re = this->re + ob.re;
    aux.im = this->im + ob.im;
    return aux;
}

int main()
{
    complex A;//= new complex;
    A.citire();
    complex B(1, 2);// = new complex(3, 5);

    complex C = A.suma(B);
    //C.afisare();

    //complex *D = new complex(*C);
    complex D;
    D = C;
    complex E(C);
    C.citire();
    C.afisare();
    D.afisare();
    E.afisare();

    return 0;
}
