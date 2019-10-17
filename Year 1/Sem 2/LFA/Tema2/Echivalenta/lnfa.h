#ifndef LNFA_H_INCLUDED
#define LNFA_H_INCLUDED

#include <set>
#include <map>

//using namespace std;

std::set <int> inchidere(std::set <int> stari, std::map <std::pair <int, char>, std::set <int> > delta);
void citire_QEFD(std::set <int> &Q, std::set <char> &Epsilon, int &q0, std::set <int> &F, std::map <std::pair <int, char>, std::set <int> > &delta, std::istream &f);

#endif // LNFA_H_INCLUDED
