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

bool VardoRikiavimas(const studentas &a, const studentas &b) {
    return a.vardas < b.vardas;
}

bool MedianaRikiavimas(const studentas &a, const studentas &b) {
    return a.GalMediana > b.GalMediana;
}

bool VidurkisRikiavimas(const studentas &a, const studentas &b) {
    return a.GalVidurkis > b.GalVidurkis;
}

bool PavardeRikiavimas(const studentas &a, const studentas &b) {
    return a.pavarde < b.pavarde;
}

