#ifndef STUDENTU_SISTEMA_SKAICIAVIMAI_H
#define STUDENTU_SISTEMA_SKAICIAVIMAI_H

#include "Common.h"
#include "klaiduValdymas.h"
#include <algorithm>
#include <string>
using std::vector;

// Forward declarations for comparison functions
bool VardoRikiavimas(const studentas &a, const studentas &b);
bool PavardeRikiavimas(const studentas &a, const studentas &b);
bool MedianaRikiavimas(const studentas &a, const studentas &b);
bool VidurkisRikiavimas(const studentas &a, const studentas &b);


template<template<typename> class T>
void skaiciavimai(T<studentas> &stud); // apskaičiuoja vidurkius ir medianas kiekvienam studentui
template<template<typename> class T>
void raides(int &MaxPav, int &MaxVard, const T<studentas> &stud); // tikrina vardų ir pavardžių ilgius, kad lentelė būtų tvarkinga
bool VardoRikiavimas(const studentas &a, const studentas &b); // rikiuoja pagal vardą abėcėlės tvarka
bool MedianaRikiavimas(const studentas &a, const studentas &b); // rikiuoja pagal mediana nuo didžiausio iki mažiausio
bool VidurkisRikiavimas(const studentas &a, const studentas &b); // rikiuoja pagal vidurkis nuo didžiausio iki mažiausio
template<template<typename> class T>
void rikiavimas(T<studentas> &stud); // leidžia vartotojui pasirinkti rikiavimo kriterijų
template<template<typename> class T>
void rikiavimas(T<studentas> &stud, int krit); // rikiavimas pagal programos perduota kriteriju

// Template implementations

template<template<typename> class T>
void skaiciavimai(T<studentas> &stud) {
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
        std::vector<int> nd_kopija = s.nd;
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

template<template<typename> class T>
void raides(int &MaxPav, int &MaxVard, const T<studentas> &stud) {
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

template<template<typename> class T>
void rikiavimas(T<studentas> &stud) {
    vector<studentas> temp(stud.begin(), stud.end());
    
    std::string kriterijusStr;
    std::cout << "Pasirinkite rikiavimo kriterijų:\n";
    std::cout << "1. Rikiuoti pagal varda \n";
    std::cout << "2. Rikiuoti pagal pavardę \n";
    std::cout << "3. Rikiuoti pagal medianą (nuo didžiausio iki mažiausio)\n";
    std::cout << "4. Rikiuoti pagal vidurkį (nuo didžiausio iki mažiausio)\n";
    std::cout << "5. Nerikiuoti\n";
    std::cout << "Įveskite pasirinkimą: ";
    std::cin >> kriterijusStr;
    auto kriterijus_opt = AllExceptionsHandler::TryStoI(kriterijusStr);
    while (!kriterijus_opt.has_value()) {
        std::cerr << "Neteisinga įvestis. Prašome įvesti sveiką skaičių (1-5): ";
        std::cin >> kriterijusStr;
        kriterijus_opt = AllExceptionsHandler::TryStoI(kriterijusStr);
    }
    const int kriterijus = kriterijus_opt.value();

    switch(kriterijus) {
        case 1:
            std::sort(temp.begin(), temp.end(), VardoRikiavimas);
            break;
        case 2:
            std::sort(temp.begin(), temp.end(), PavardeRikiavimas);
            break;
        case 3:
            std::sort(temp.begin(), temp.end(), MedianaRikiavimas);
            break;
        case 4:
            std::sort(temp.begin(), temp.end(), VidurkisRikiavimas);
            break;
        case 5:
            return;
        default:
            std::cerr << "Neteisingas rikiavimo kriterijus.\n";
    }
    
    stud.assign(temp.begin(), temp.end());
}

template<template<typename> class T>
void rikiavimas(T<studentas> &stud, int krit) {
    vector<studentas> temp(stud.begin(), stud.end());
    
    switch(krit) {
        case 1:
            std::sort(temp.begin(), temp.end(), VardoRikiavimas);
            break;
        case 2:
            std::sort(temp.begin(), temp.end(), PavardeRikiavimas);
            break;
        case 3:
            std::sort(temp.begin(), temp.end(), MedianaRikiavimas);
            break;
        case 4:
            std::sort(temp.begin(), temp.end(), VidurkisRikiavimas);
            break;
        default:
            std::cerr << "Neteisingas rikiavimo kriterijus. Programos refrence klaida\n";
    }
    
    stud.assign(temp.begin(), temp.end());
}

#endif //STUDENTU_SISTEMA_SKAICIAVIMAI_H