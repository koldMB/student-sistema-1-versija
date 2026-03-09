#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>

using std::string;
using std::vector;
bool isInteger(const string& s);

struct studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    double GalMediana;
    double GalVidurkis;
    int egz;
};

void atrinkimas(const vector<studentas> &stud, vector<studentas> &atrinkti, vector<studentas> &neatrinkti, int MaxPav, int MaxVard);


#endif // COMMON_H