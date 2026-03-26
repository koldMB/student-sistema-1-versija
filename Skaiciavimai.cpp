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

void rikiavimas(vector<studentas> &stud) {

    std::string kriterijusStr;
    cout << "Pasirinkite rikiavimo kriterijų:\n";
    cout << "1. Rikiuoti pagal varda \n";
    cout << "2. Rikiuoti pagal pavardę \n";
    cout << "3. Rikiuoti pagal medianą (nuo didžiausio iki mažiausio)\n";
    cout << "4. Rikiuoti pagal vidurkį (nuo didžiausio iki mažiausio)\n";
    cout << "5. Nerikiuoti\n";
    cout << "Įveskite pasirinkimą: ";
    cin >> kriterijusStr;
    auto kriterijus_opt = AllExceptionsHandler::TryStoI(kriterijusStr);
    while (!kriterijus_opt.has_value()) {
        cerr << "Neteisinga įvestis. Prašome įvesti sveiką skaičių (1-5): ";
        cin >> kriterijusStr;
        kriterijus_opt = AllExceptionsHandler::TryStoI(kriterijusStr);
    }
    const int kriterijus = kriterijus_opt.value();

    switch(kriterijus) {
        case 1:
            sort(stud.begin(), stud.end(), VardoRikiavimas);
            break;
        case 2:
            sort(stud.begin(), stud.end(), PavardeRikiavimas);
            break;
        case 3:
            sort(stud.begin(), stud.end(), MedianaRikiavimas);
            break;
        case 4:
            sort(stud.begin(), stud.end(), VidurkisRikiavimas);
            break;
        case 5:
            return;
        default:
            cerr << "Neteisingas rikiavimo kriterijus.\n";
    }
}

void rikiavimas(vector<studentas> &stud, int krit) {
    switch(krit) {
        case 1:
            sort(stud.begin(), stud.end(), VardoRikiavimas);
            break;
        case 2:
            sort(stud.begin(), stud.end(), PavardeRikiavimas);
            break;
        case 3:
            sort(stud.begin(), stud.end(), MedianaRikiavimas);
            break;
        case 4:
            sort(stud.begin(), stud.end(), VidurkisRikiavimas);
            break;
        default:
            cerr << "Neteisingas rikiavimo kriterijus. Programos refrence klaida\n";
    }
}

