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

void skaiciavimai(vector<studentas> &stud) // apskaičiuoja vidurkius ir medianas kiekvienam studentui
{

    for(auto &s : stud) {
        if(s.nd.empty()) {
            s.GalVidurkis = 0;
            s.GalMediana = 0;
            continue;
        }

        double suma = 0;
        for(const auto &nd_ivar : s.nd) {
            suma += nd_ivar;
        }
        s.GalVidurkis = suma / s.nd.size();

        s.GalVidurkis = s.GalVidurkis * 0.4 + s.egz * 0.6;
        vector<int> nd_kopija = s.nd;
        std::sort(nd_kopija.begin(), nd_kopija.end());
        if(nd_kopija.size() % 2 == 0) {
            auto mid1 = AllExceptionsHandler::TryAt(nd_kopija, nd_kopija.size()/2 - 1);
            auto mid2 = AllExceptionsHandler::TryAt(nd_kopija, nd_kopija.size()/2);
            if (mid1.has_value() && mid2.has_value()) {
                s.GalMediana = (mid1.value() + mid2.value()) / 2.0;
            }
        } else {
            auto mid = AllExceptionsHandler::TryAt(nd_kopija, nd_kopija.size()/2);
            if (mid.has_value()) {
                s.GalMediana = mid.value();
            }
        }
        s.GalMediana = s.GalMediana * 0.4 + s.egz * 0.6;
    }
}



void raides(int &MaxPav, int &MaxVard, const vector <studentas> &stud)
{
    MaxPav = 0;
    MaxVard = 0;
    for(const auto &s : stud) {
        if(static_cast<int>(s.pavarde.length()) > MaxPav) {
            MaxPav = static_cast<int>(s.pavarde.length());
        }
        if(static_cast<int>(s.vardas.length()) > MaxVard) {
            MaxVard = static_cast<int>(s.vardas.length());
        }
    }
}

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

