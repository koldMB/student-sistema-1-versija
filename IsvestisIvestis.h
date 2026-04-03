#ifndef STUDENTU_SISTEMA_ISVESTISIVESTIS_H
#define STUDENTU_SISTEMA_ISVESTISIVESTIS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <array>
#include "Common.h"
#include "klaiduValdymas.h"

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::cin;

// Forward declarations
string pad_utf8(const string& str, size_t width);
string randomVardas(vector<Studentas> &stud);
string randomPavarde(vector<Studentas> &stud);

// Function declarations - all using vector<Studentas> only
void skaitymas(vector<Studentas> &stud);
void skaitymas(vector<Studentas> &stud, int &n, int nd_sk);
void skaitymas(vector<Studentas> &stud, int &n, int nd_sk, int VardPavSk);
void FailoNuskaitymas(vector<Studentas> &stud, const string& filename);
void FailoIsvedimas(const vector<Studentas> &stud, const string& filename, int &MaxPav, int &MaxVard);
void TermArFailas(const vector<Studentas> &stud, int &MaxPav, int &MaxVard);
void isvestis(const vector<Studentas> &stud, int &MaxPav, int &MaxVard);
void IsvestiGeriBlogiFailus(const vector<Studentas> &geri, const vector<Studentas> &blogi, int MaxPav, int MaxVard);
void IsvestiBlogusGerusFailus(const vector<Studentas> &geri, const vector<Studentas> &blogi, const string& basename, int MaxPav, int MaxVard);
void GeneruotiStudentuFaila(const string& filename, int student_count, int nd_sk);


#endif //STUDENTU_SISTEMA_ISVESTISIVESTIS_H