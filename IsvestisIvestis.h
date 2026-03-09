#ifndef STUDENTU_SISTEMA_ISVESTISIVESTIS_H
#define STUDENTU_SISTEMA_ISVESTISIVESTIS_H

#include <vector>
#include <string>
#include "Common.h"

using std::string;
using std::vector;

void skaitymas(vector<studentas> &stud); // paprastas vedimas ranka
void skaitymas(vector<studentas> &stud, int &n, int nd_sk); // generuoja n studentų duomenis su nd_sk namų darbų pažymiais
void skaitymas(vector<studentas> &stud, int &n, int nd_sk, int VardPavSk); // generuoja n studentų duomenis su nd_sk namų darbų pažymiais ir vardais/pavardėmis iš vardPavSk dydžio sąrašo
void FailoNuskaitymas(vector<studentas> &stud, const string& filename); // skaito duomenis iš failo
void FailoIsvedimas(const vector<studentas> &stud, const string& filename, int &MaxPav, int &MaxVard); // išveda lentelę su studentų duomenimis į failą
void TermArFailas(const vector<studentas> &stud, int &MaxPav, int &MaxVard); // leidžia vartotojui pasirinkti ar išvesti duomenis į terminalą ar į failą
void isvestis(const vector<studentas> &stud, int &MaxPav, int &MaxVard); // išveda lentelę su studentų duomenimis į terminalą
string randomVardas(vector<studentas> &stud);
string randomPavarde(vector<studentas> &stud);

#endif //STUDENTU_SISTEMA_ISVESTISIVESTIS_H