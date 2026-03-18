#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <list>
#include <deque>

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

// Templatai studentui
template<typename T1, typename T2, typename T3>
void atrinkimas(const T1 &stud, T2 &atrinkti, T3 &neatrinkti) {
    vector<studentas> temp_stud(stud.begin(), stud.end());
    vector<studentas> temp_atrinkti, temp_neatrinkti;
    atrinkimas(temp_stud, temp_atrinkti, temp_neatrinkti);
    atrinkti.assign(temp_atrinkti.begin(), temp_atrinkti.end());
    neatrinkti.assign(temp_neatrinkti.begin(), temp_neatrinkti.end());
}

template<typename T1, typename T2, typename T3>
void atrinkimasAutomatiskas(const T1 &stud, T2 &geri, T3 &blogi) {
    vector<studentas> temp_stud(stud.begin(), stud.end());
    vector<studentas> temp_geri, temp_blogi;
    atrinkimasAutomatiskas(temp_stud, temp_geri, temp_blogi);
    geri.assign(temp_geri.begin(), temp_geri.end());
    blogi.assign(temp_blogi.begin(), temp_blogi.end());
}

#endif // COMMON_H