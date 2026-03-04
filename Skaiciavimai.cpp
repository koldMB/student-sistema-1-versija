#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>


#include "Common.h"
#include "Laikas.h"

using std::vector;
using std::cout;
using std::cin;

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
            s.GalMediana = (nd_kopija[nd_kopija.size()/2 - 1] + nd_kopija[nd_kopija.size()/2]) / 2.0;
        } else {
            s.GalMediana = nd_kopija[nd_kopija.size()/2];
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
    Laikas RikLaik;
    std::string kriterijusStr;
    cout << "Pasirinkite rikiavimo kriterijų:\n";
    cout << "1. Rikiuoti pagal varda \n";
    cout << "2. Rikiuoti pagal pavardę \n";
    cout << "3. Rikiuoti pagal medianą (nuo didžiausio iki mažiausio)\n";
    cout << "4. Rikiuoti pagal vidurkį (nuo didžiausio iki mažiausio)\n";
    cout << "Įveskite pasirinkimą: ";
    cin >> kriterijusStr;
    while (!isInteger(kriterijusStr)) {
        cout << "Neteisinga įvestis. Prašome įvesti sveiką skaičių (1-4): ";
        cin >> kriterijusStr;
    }
    const int kriterijus = stoi(kriterijusStr);
    RikLaik.PradekLaikmati();
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
        default:
            cout << "Neteisingas rikiavimo kriterijus.\n";
    }
    RikLaik.BaiktiLaikmati(1);
}

