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


void FailoNuskaitymas(vector<studentas> &stud, const string& filename) {
    Laikas FailSkait;
    FailSkait.PradekLaikmati();
    std::ifstream f(filename);
    if (!f.is_open()) {
        std::cerr << "Nepavyko atidaryti failo. " << filename << "\n";
        return;
    }

    // Skip header line
    f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int nd_sk = -1; // pagal pirma eilute
    string line;

    while (std::getline(f, line)) {
        if (line.empty()) continue;

        // išskaido eilutę į žodžius
        std::istringstream iss(line);
        string token;
        vector<string> tokens;
        while (iss >> token) {
            tokens.push_back(token);
        }

        // bent vienas namų darbas + egzaminas + vardas + pavardė
        if (tokens.size() < 4) continue;

        // nustato namų darbų skaičių pagal pirmą eilutę
        if (nd_sk == -1) {
            nd_sk = static_cast<int>(tokens.size()) - 3; // pirmi du žodžiai - vardas ir pavardė, paskutinis - egzaminas
        }

        studentas temp;
        temp.vardas = tokens[0];
        temp.pavarde = tokens[1];
        temp.nd.resize(nd_sk);

        // nuskaito namų darbų pažymius
        for (int i = 0; i < nd_sk; i++) {
            if (isInteger(tokens[2 + i])) {
                temp.nd[i] = stoi(tokens[2 + i]);
            }
        }

        // nuskaito egzamino pažymį
        if (isInteger(tokens[2 + nd_sk])) {
            temp.egz = stoi(tokens[2 + nd_sk]);
        }

        stud.push_back(temp);
    }
    f.close();
    FailSkait.BaiktiLaikmati(0);
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

