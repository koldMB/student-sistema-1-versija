#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>


#include "Common.h"
#include "klaiduValdymas.h"

using std::vector;
using std::cout;
using std::cin;
using std::cerr;

bool VardoRikiavimas(const Studentas &a, const Studentas &b) {
    return a.vardas() < b.vardas();
}

bool MedianaRikiavimas(const Studentas &a, const Studentas &b) {
    return a.mediana() > b.mediana();
}

bool VidurkisRikiavimas(const Studentas &a, const Studentas &b) {
    return a.vidurkis() > b.vidurkis();
}

bool PavardeRikiavimas(const Studentas &a, const Studentas &b) {
    return a.pavarde() < b.pavarde();
}

