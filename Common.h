#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>

using std::string;

bool isInteger(const string& s);

struct studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    double GalMediana;
    double GalVidurkis;
    int egz;
    bool Teig = false; // Galutinis balas. Jeigu >= 5 tai true, kitaip false
};

#endif // COMMON_H