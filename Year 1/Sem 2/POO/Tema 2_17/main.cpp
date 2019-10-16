#include <iostream>
#include <fstream>
#include <typeinfo>

using namespace std;

class Object
{
public:
    Object() {}
    virtual ~Object() {}
    virtual void display() = 0;
    friend istream& operator>>(istream &f, Object &o);
    friend ostream &operator<<(ostream &g, Object &o);
    virtual void citire(istream &f) = 0;
    virtual void afisare(ostream &g) = 0;
};

class ObArray
{
    Object **p;
    int size;
    int grows;
    int dimens;
    int resize();
public:
    ObArray(int dimens = 10, int grows = 5);
    ~ObArray();
    friend istream &operator>>(istream &f, ObArray &arr);
    friend ostream &operator<<(ostream &g, ObArray &arr);
    void RemoveAll();
    int getSize();
    int getDim();
    int add(Object *x);
    int insertAt(int i, Object *x);
    int removeAt(int i);
    Object* getAt(int i);
    void display();
};

class Punct:public Object
{
    int x, y;
public:
    Punct(int x = 0, int y = 0);
    Punct(const Punct &p);
    ~Punct() {}
    void citire(istream &f);
    void afisare(ostream &g);
    Punct& operator=(const Punct &p);
    void display();
    void adr();
};

class Complex:public Object
{
    int re, im;
public:
    Complex(int re = 0, int im = 0);
    Complex(const Complex &c);
    ~Complex() {}
    void citire(istream &f);
    void afisare(ostream &g);
    Complex& operator=(const Complex &c);
    void display();
};

///--------------------------------------------------Object

istream& operator>>(istream &f, Object &o)
{
    o.citire(f);
    return f;
}

ostream &operator<<(ostream &g, Object &o)
{
    o.afisare(g);
    return g;
}

///--------------------------------------------------ObArray

ObArray::ObArray(int dimens, int grows)
{
    this->dimens = dimens;
    this->grows = grows;
    this->size = 0;

    this->p = new Object* [dimens];
}

ObArray::~ObArray()
{
    this->RemoveAll();
}

istream &operator>>(istream &f, ObArray &arr)
{
    arr.RemoveAll();
    int n, optiune;
    Punct *P;
    Complex *C;
    f>>n;
    arr = ObArray(n);
    for (int i = 0; i < n; i++)
    {
        f>>optiune;
        switch (optiune)
        {
            case 1:
                //arr.p[i] = new Punct();
                P = new Punct;
                f>>*P;
                arr.add(P);
                //f>>*static_cast<Punct*>(arr.p[i]);
                break;
            case 2:
                //arr.p[i] = new Complex();
                //f>>*static_cast<Complex*>(arr.p[i]);
                C = new Complex;
                f>>*C;
                arr.add(C);
                break;
            default: return f;
        }
    }
    return f;
}

ostream &operator<<(ostream &g, ObArray &arr)
{
    Punct P;
    Complex C;

    for (int i = 0; i < arr.size; i++)
    {
        if (typeid(*arr.p[i]) == typeid(P))
            g<<*static_cast<Punct*>(arr.p[i]);
        else if (typeid(*arr.p[i]) == typeid(C))
            g<<*static_cast<Complex*>(arr.p[i]);
        else
            g<<"\n";
    }
    return g;
}

void ObArray::RemoveAll()
{
    if (this->p == NULL || this->size == 0)
        return;
    for (int i = 0; i < this->size; i++)
        if (this->p[i] != NULL)
            delete this->p[i];
}

int ObArray::getSize()
{
    return this->size;
}

int ObArray::getDim()
{
    return this->dimens;
}

int ObArray::resize()
{
    Object **aux;
    aux = new Object* [this->dimens + this->grows];
    if (aux == NULL)
        return 0;

    for (int i = 0; i < this->size; i++)
        aux[i] = this->p[i];
    this->dimens += grows;
    this->p = aux;

    return 1;
}

int ObArray::add(Object *x)
{
    if (this->size == this->dimens)
        if (this->resize() == 0)
            return 0;
    //Object *aux = x->clone();
    //this->p[this->size] = aux;
    this->p[this->size] = x;
    this->size++;
    return 1;
}

int ObArray::insertAt(int i, Object* x)
{
    if (i >= this->size)
        return 0;
    this->p[i] = x;
    return 1;
}

int ObArray::removeAt(int i)
{
    if (i >= this->size)
        return 0;
    this->p[i] = NULL;
    return 1;
}

Object* ObArray::getAt(int i)
{
    if (i >= this->size)
        return NULL;
    return this->p[i];
}

///--------------------------------------------------Punct

Punct::Punct(int x, int y)
{
    this->x = x;
    this->y = y;
}

Punct::Punct(const Punct &p)
{
    this->x = p.x;
    this->y = p.y;
}

void Punct::citire(istream &f)
{
    f>>this->x>>this->y;
}

void Punct::afisare(ostream &g)
{
    g<<"x: "<<this->x<<" y: "<<this->y<<"\n";
}

Punct& Punct::operator=(const Punct &p)
{
    this->x = p.x;
    this->y = p.y;
    return *this;
}

void Punct::display()
{
    cout<<this->x<<" "<<this->y<<"\n";
}

///--------------------------------------------------Complex

Complex::Complex(int re, int im)
{
    this->re = re;
    this->im = im;
}

Complex::Complex(const Complex &c)
{
    this->re = c.re;
    this->im = c.im;
}

void Complex::citire(istream &f)
{
    f>>this->re>>this->im;
}

void Complex::afisare(ostream &g)
{
    g<<this->re<<" + "<<this->im<<"*i\n";
}

Complex& Complex::operator=(const Complex &c)
{
    this->re = c.re;
    this->im = c.im;
    return *this;
}

void Complex::display()
{
    cout<<re<<" "<<im<<"\n";
}

///--------------------------------------------------main

int main()
{
    ifstream f("data.in");
    ofstream g("data.out");

    if (!f)
    {
        cout<<"Nu exista \"data.in\"";
        exit(1);
    }

    ObArray Ob1, Ob2;

    f>>Ob1>>Ob2;

    g<<Ob1<<Ob2;

    return 0;
}
