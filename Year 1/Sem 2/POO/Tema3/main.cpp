#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <typeinfo>
#include <string>

using namespace std;

///----------------------------------Clase

class Masina
{
protected:
    string nume;
    float lungime, litraj;
    int pret;
public:
    Masina(string s, int pr, float lung, float lit): nume(s), lungime(lung), litraj(lit), pret(pr) {}
    virtual ~Masina() {}
    friend istream& operator>>(istream &f, Masina &M);
    friend ostream& operator<<(ostream &g, Masina &M);
    virtual void citire(istream &f) = 0;
    virtual void afisare(ostream &g) = 0;
    virtual bool verif(float l_min, float l_max);
};
class MMini: public Masina
{
    static float l_min, l_max;
public:
    MMini(string s = "", int pr = 0, float lung = 3.8, float lit = 4):Masina(s, pr, lung, lit) {verif(l_min, l_max);};
    void citire(istream &f);
    void afisare(ostream &g);
};
class MMica: public Masina
{
    static float l_min, l_max;
public:
    MMica(string s = "", int pr = 0, float lung = 4, float lit = 4.5):Masina(s, pr, lung, lit) {verif(l_min, l_max);};
    void citire(istream &f);
    void afisare(ostream &g);
};
class Compacta: public Masina
{
protected:
    static float l_min, l_max;
public:
    Compacta(string s = "", int pr = 0, float lung = 4.3, float lit = 5):Masina(s, pr, lung, lit) {verif(l_min, l_max);};
};
class CompactaHB: public Compacta
{
public:
    void citire(istream &f);
    void afisare(ostream &g);
};
class CompactaC: public Compacta
{
public:
    void citire(istream &f);
    void afisare(ostream &g);
};
class CompactaS: public Compacta
{
public:
    void citire(istream &f);
    void afisare(ostream &g);
};
class Monovolum: public Masina
{
protected:
    static float l_min, l_max;
    int nr_persoane;
public:
    Monovolum(string s = "", int pr = 0, float lung = 5.6, float lit = 5.8, int pers = 5): Masina(s, pr, lung, lit), nr_persoane(pers) {verif(l_min, l_max);};
    void citire(istream &f);
    void afisare(ostream &g);
    virtual bool verif(float l_min, float l_max);
};
class Monovolum_sh: public Monovolum
{
    static bool e_vara;
    int ani_vechime;
public:
    Monovolum_sh(string s = "", int pr = 0, float lung = 6, float lit = 5.8, int pers = 5, int ani = 1);
    void citire(istream &f);
    void afisare(ostream &g);
    bool verif(float l_min, float l_max);
    int reducere();
};

///----------------------------------Variabile statice

float MMini::l_min = 3.5;
float MMini::l_max = 4;

float MMica::l_min = 3.85;
float MMica::l_max = 4.1;

float Compacta::l_min = 4.2;
float Compacta::l_max = 4.5;

float Monovolum::l_min = 4.5;
float Monovolum::l_max = 7;

bool Monovolum_sh::e_vara = true;

Monovolum_sh::Monovolum_sh(string s, int pr, float lung, float lit, int pers, int ani):Monovolum(s, pr, lung, lit, pers), ani_vechime(ani)
{
    try
    {
        if (ani < 0)
            throw(-1);
    }
    catch (int x)
    {
        cout<<"Valoare negativa\n";
    }
}
///----------------------------------Verificari

bool Masina::verif(float l_min, float l_max)
{
    try
    {
        if (lungime < l_min || lungime > l_max)
            throw(lungime);
        if (lungime < 0 || litraj < 0)
            throw(-1);
    }
    catch(int x)
    {
        cout<<"Valoare negativa\n";
        return false;
    }
    catch(float l)
    {
        cout<<"Lungimea "<<l<<" nu e potrivita pentru masina\n";
        if (l < l_min)
            lungime = l_min;
        else
            lungime = l_max;
        return false;
    }
    return true;
}

bool Monovolum::verif(float l_min, float l_max)
{

    if (Masina::verif(l_min, l_max) == 0)
        return false;

    try
    {
        if (nr_persoane < 0)
            throw(-1);
    }
    catch(int x)
    {
        cout<<"Valoare negativa\n";
        return false;
    }
    return true;
}

bool Monovolum_sh::verif(float l_min, float l_max)
{
    if (Monovolum::verif(l_min, l_max) == 0)
        return false;

    try
    {
        if (ani_vechime < 0)
            throw(-1);
    }
    catch(int x)
    {
        cout<<"Valoare negativa\n";
        return false;
    }
    return true;
}

///----------------------------------Citiri / Afisari

istream& operator>>(istream &f, Masina &M)
{
    M.citire(f);
    return f;
}
ostream& operator<<(ostream &g, Masina &M)
{
    M.afisare(g);
    return g;
}

void MMini::citire(istream &f)
{
    f>>nume>>pret>>lungime>>litraj;
    verif(l_min, l_max);
}
void MMica::citire(istream &f)
{
    f>>nume>>pret>>lungime>>litraj;
    verif(l_min, l_max);
}
void CompactaHB::citire(istream &f)
{
    f>>nume>>pret>>lungime>>litraj;
    verif(l_min, l_max);
}
void CompactaC::citire(istream &f)
{
    f>>nume>>pret>>lungime>>litraj;
    verif(l_min, l_max);
}
void CompactaS::citire(istream &f)
{
    f>>nume>>pret>>lungime>>litraj;
    verif(l_min, l_max);
}
void Monovolum::citire(istream &f)
{
    f>>nume>>pret>>lungime>>litraj>>nr_persoane;
    verif(l_min, l_max);
}
void Monovolum_sh::citire(istream &f)
{
    f>>nume>>pret>>lungime>>litraj>>nr_persoane>>ani_vechime;
    verif(l_min, l_max);
}
void MMini::afisare(ostream &g)
{
    g<<"Mini: nume "<<nume<<", pret "<<pret<<" euro, lungime "<<lungime<<" m, litraj "<<litraj<<" l\n";
}
void MMica::afisare(ostream &g)
{
    g<<"Masina mica: nume "<<nume<<", pret "<<pret<<" euro, lungime "<<lungime<<" m, litraj "<<litraj<<" l\n";
}
void CompactaHB::afisare(ostream &g)
{
    g<<"Hatchback: nume "<<nume<<", pret "<<pret<<" euro, lungime "<<lungime<<" m, litraj "<<litraj<<" l\n";
}
void CompactaC::afisare(ostream &g)
{
    g<<"Combi: nume "<<nume<<", pret "<<pret<<" euro, lungime "<<lungime<<" m, litraj "<<litraj<<" l\n";
}
void CompactaS::afisare(ostream &g)
{
    g<<"Sedan: nume "<<nume<<", pret "<<pret<<" euro, lungime "<<lungime<<" m, litraj "<<litraj<<" l\n";
}
void Monovolum::afisare(ostream &g)
{
    g<<"Monovolum: nume "<<nume<<", pret "<<pret<<" euro, lungime "<<lungime<<" m, litraj "<<litraj<<" l, numar persoane "<<nr_persoane<<"\n";
}
void Monovolum_sh::afisare(ostream &g)
{
    g<<"Monovolum_sh: nume "<<nume<<", pret "<<pret<<" euro, lungime "<<lungime<<" m, litraj "<<litraj<<" l, numar persoane "<<nr_persoane<<", ani vechime "<<ani_vechime<<"\n";
}

int Monovolum_sh::reducere()
{
    int r = 0;
    if (e_vara)
        r = 10;
    return r + ani_vechime;
}

///----------------------------------Vanzare

template <class T>
class Vanzare
{
    T nr_masini;
    T masini_vandute;
    vector <Masina*> stoc;
    vector <Masina*> vandute;
public:
    Vanzare<T>(): nr_masini(0), masini_vandute(0) {};
    friend istream& operator>>(istream& f, Vanzare<T>& V) {V.citire(f); return f;};
    friend ostream& operator<<(ostream& g, Vanzare<T>& V) {V.afisare(g); return g;};
    void citire(istream& f);
    void afisare(ostream& g);
    Vanzare<T>& operator=(const Vanzare<T>& V);
    void operator+=(Masina* M);
    void operator-=(Masina* M);
    void operator-=(int poz);
};

template<class T>
void Vanzare<T>::citire(istream& f)
{
    int n, optiune;
    f>>n;

    Masina* M;
    for (int i = 0; i < n; i++)
    {
        f>>optiune;
        switch(optiune)
        {
        case 1: //MMini
            M = new MMini;
            break;
        case 2: //MMica
            M = new MMica;
            break;
        case 3: //CompactaHB
            M = new CompactaHB;
            break;
        case 4: //CompactaC
            M = new CompactaC;
            break;
        case 5: //CompactaS
            M = new CompactaS;
            break;
        case 6: //Monovolum
            M = new Monovolum;
            break;
        case 7: //Monovolum_sh
            M = new Monovolum_sh;
            break;
        default:
            continue;
        }
        f>>*M;
        nr_masini++;
        stoc.push_back(M);
    }
}

template<class T>
void Vanzare<T>::afisare(ostream& g)
{
    g<<"Masini in stoc:\n";
    for(int i = 0; i < nr_masini; i++)
        g<<*stoc[i];
    g<<"Masini vandute:\n";
    for (int i = 0; i < masini_vandute; i++)
        g<<*vandute[i];
}

template<class T>
Vanzare<T>& Vanzare<T>::operator=(const Vanzare<T>& V)
{
    stoc.empty();
    vandute.empty();
    nr_masini = V.nr_masini;
    masini_vandute = V.masini_vandute;/*
    for (int i = 0; i < nr_masini; i++)
    {
        const type_info& ti = typeid(*V.stoc[i]);
        //switch
        if (ti == typeid(MMini))
        {
            MMini *M = new MMini(*V.stoc[i]);
            stoc.push_back(M);
        }
        else if (ti == typeid(MMica))
        {
            MMica *M = new MMica(*V.stoc[i]);
            stoc.push_back(M);
        }
        else if (ti == typeid(CompactaHB))
        {
            CompactaHB *M = new CompactaHB(*V.stoc[i]);
            stoc.push_back(M);
        }
        else if (ti == typeid(CompactaS))
        {
            CompactaS *M = new CompactaS(*V.stoc[i]);
            stoc.push_back(M);
        }
        else if (ti == typeid(CompactaC))
        {
            CompactaC *M = new CompactaC(*V.stoc[i]);
            stoc.push_back(M);
        }
        else if (ti == typeid(Monovolum))
        {
            Monovolum *M = new Monovolum(*V.stoc[i]);
            stoc.push_back(M);
        }
        else if (ti == typeid(Monovolum_sh))
        {
            Monovolum_sh *M = new Monovolum_sh(*V.stoc[i]);
            stoc.push_back(M);
        }
    }
    for (int i = 0; i < masini_vandute; i++)
    {
        const type_info& ti = typeid(*V.vandute[i]);
        //switch
        if (ti == typeid(MMini))
        {
            MMini *M = new MMini(*V.vandute[i]);
            vandute.push_back(M);
        }
        else if (ti == typeid(MMica))
        {
            MMica *M = new MMica(*V.vandute[i]);
            vandute.push_back(M);
        }
        else if (ti == typeid(CompactaHB))
        {
            CompactaHB *M = new CompactaHB(*V.vandute[i]);
            vandute.push_back(M);
        }
        else if (ti == typeid(CompactaS))
        {
            CompactaS *M = new CompactaS(*V.vandute[i]);
            vandute.push_back(M);
        }
        else if (ti == typeid(CompactaC))
        {
            CompactaC *M = new CompactaC(*V.vandute[i]);
            vandute.push_back(M);
        }
        else if (ti == typeid(Monovolum))
        {
            Monovolum *M = new Monovolum(*V.vandute[i]);
            vandute.push_back(M);
        }
        else if (ti == typeid(Monovolum_sh))
        {
            Monovolum_sh *M = new Monovolum_sh(*V.vandute[i]);
            vandute.push_back(M);
        }
    }*/
    return *this;
}

template<class T>
void Vanzare<T>::operator+=(Masina* M)
{
    vector <Masina*>::iterator it = find(stoc.begin(), stoc.end(), M);
    if (it == stoc.end())
    {
        stoc.push_back(M);
        nr_masini++;
    }
}

template<class T>
void Vanzare<T>::operator-=(Masina* M)
{
    vector <Masina*>::iterator it = find(stoc.begin(), stoc.end(), M);
    if (it != stoc.end())
    {
        stoc.erase(it);
        vandute.push_back(M);
        nr_masini--;
        masini_vandute++;
    }
}

template<class T>
void Vanzare<T>::operator-=(int poz)
{
    try
    {
        if (poz < 0 || poz > nr_masini)
            throw(-1);
    }
    catch(...)
    {
        cout<<"Pozitie inexistenta\n";
        return;
    }
    Masina* M = stoc[poz];
    vector <Masina*>::iterator it = find(stoc.begin(), stoc.end(), M);
    stoc.erase(it);
    vandute.push_back(M);
    nr_masini--;
    masini_vandute++;
}

///----------------------------------Specializare Vanzare

template <>
class Vanzare<unsigned int>
{
    unsigned int nr_masini;
    unsigned int masini_vandute;
    vector <Masina*> stoc;
    vector <Masina*> vandute;
public:
    Vanzare(): nr_masini(0), masini_vandute(0) {};
    friend istream& operator>>(istream& f, Vanzare<unsigned int>& V) {V.citire(f); return f;};
    friend ostream& operator<<(ostream& g, Vanzare<unsigned int>& V) {V.afisare(g); return g;};
    void citire(istream& f);
    void afisare(ostream& g);
    bool verif_mv(Masina* M);
    void operator+=(Masina* M);
    void operator-=(Masina* M);
    void operator-=(int poz);
};

void Vanzare<unsigned int>::citire(istream& f)
{
    int n, optiune;
    f>>n;

    Masina* M;
    for (int i = 0; i < n; i++)
    {
        f>>optiune;
        switch(optiune)
        {
        case 1: //Monovolum
            M = new Monovolum;
            break;
        case 2: //Monovolum_sh
            M = new Monovolum_sh;
            break;
        default:
            continue;
        }
        f>>*M;
        nr_masini++;
        stoc.push_back(M);
    }
}

void Vanzare<unsigned int>::afisare(ostream& g)
{
    g<<"Monovolume in stoc:\n";
    for(int i = 0; i < nr_masini; i++)
        g<<*stoc[i];
    g<<"Monovolume vandute:\n";
    for (int i = 0; i < masini_vandute; i++)
        g<<*vandute[i];
}

bool Vanzare<unsigned int>::verif_mv(Masina* M)
{
    try
    {
        if (typeid(*M) != typeid(Monovolum) && typeid(*M) != typeid(Monovolum_sh))
            throw (-1);
    }
    catch(int x)
    {
        cout<<"Masina nu este monovolum\n";
        return false;
    }
    return true;
}

void Vanzare<unsigned int>::operator+=(Masina* M)
{
    if (verif_mv(M) == false)
        return;
    vector <Masina*>::iterator it = find(stoc.begin(), stoc.end(), M);
    if (it == stoc.end())
    {
        stoc.push_back(M);
        nr_masini++;
    }
}

void Vanzare<unsigned int>::operator-=(Masina* M)
{
    vector <Masina*>::iterator it = find(stoc.begin(), stoc.end(), M);
    if (it != stoc.end())
    {
        stoc.erase(it);
        vandute.push_back(M);
        nr_masini--;
        masini_vandute++;
    }
}

void Vanzare<unsigned int>::operator-=(int poz)
{
    try
    {
        if (poz < 0 || poz > nr_masini)
            throw(-1);
    }
    catch(...)
    {
        cout<<"Pozitie inexistenta\n";
        return;
    }
    Masina* M = stoc[poz];
    vector <Masina*>::iterator it = find(stoc.begin(), stoc.end(), M);
    stoc.erase(it);
    vandute.push_back(M);
    nr_masini--;
    masini_vandute++;
}

int main()
{
    ifstream fin("data.in");
    ofstream fout("data.out");

    try
    {
        string s("Nu exista fisierul de intrare\n");
        if (!fin)
            throw s;
    }
    catch (string s)
    {
        cout<<"Eroare: "<<s;
        return -1;
    }

    Monovolum* ob = new Monovolum("Dubita", 3000);
    Monovolum* ob2 = new Monovolum(*ob);
    Vanzare<int> v;
    fin>>v;
    v+=ob2;
    v-=1;
    fout<<v;
    return 0;
}
