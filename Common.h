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

void atrinkimas(const vector<studentas> &stud, vector<studentas> &atrinkti, vector<studentas> &neatrinkti);
void atrinkimasAutomatiskas(const vector<studentas> &stud, vector<studentas> &geri, vector<studentas> &blogi);
void Bandymas1_FailuGeneravimas(int sizes[5]);
void Bandymas2_DuomenuApdorojimas(int sizes[5], int pas);


#endif // COMMON_H