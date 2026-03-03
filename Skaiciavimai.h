#ifndef STUDENTU_SISTEMA_SKAICIAVIMAI_H
#define STUDENTU_SISTEMA_SKAICIAVIMAI_H

#include "Common.h"
using std::vector;


void skaiciavimai(vector<studentas> &stud); // apskaičiuoja vidurkius ir medianas kiekvienam studentui
void raides(int &MaxPav, int &MaxVard, const vector <studentas> &stud); // tikrina vardų ir pavardžių ilgius, kad lentelė būtų tvarkinga
bool VardoRikiavimas(const studentas &a, const studentas &b); // rikiuoja pagal vardą abėcėlės tvarka
bool MedianaRikiavimas(const studentas &a, const studentas &b); // rikiuoja pagal mediana nuo didžiausio iki mažiausio
bool VidurkisRikiavimas(const studentas &a, const studentas &b); // rikiuoja pagal vidurkis nuo didžiausio iki mažiausio
void rikiavimas(vector<studentas> &stud); // leidžia vartotojui pasirinkti rikiavimo kriterijų


#endif //STUDENTU_SISTEMA_SKAICIAVIMAI_H