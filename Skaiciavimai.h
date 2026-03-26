#ifndef STUDENTU_SISTEMA_SKAICIAVIMAI_H
#define STUDENTU_SISTEMA_SKAICIAVIMAI_H

#include "Common.h"
#include <algorithm>
#include <list>
#include <deque>
using std::vector;

// Forward declarations for comparison functions
bool VardoRikiavimas(const studentas &a, const studentas &b);
bool PavardeRikiavimas(const studentas &a, const studentas &b);
bool MedianaRikiavimas(const studentas &a, const studentas &b);
bool VidurkisRikiavimas(const studentas &a, const studentas &b);


bool VardoRikiavimas(const studentas &a, const studentas &b); // rikiuoja pagal vardą abėcėlės tvarka
bool MedianaRikiavimas(const studentas &a, const studentas &b); // rikiuoja pagal mediana nuo didžiausio iki mažiausio
bool VidurkisRikiavimas(const studentas &a, const studentas &b); // rikiuoja pagal vidurkis nuo didžiausio iki mažiausio

// Generic template for containers with random access (vector, deque)
template<typename T>
void rikiavimas(T &stud) {
    std::sort(stud.begin(), stud.end(), [](const studentas &a, const studentas &b) {
        return a.vardas < b.vardas;
    });
}

// Specialization for std::list
template<>
inline void rikiavimas(std::list<studentas> &stud) {
    stud.sort([](const studentas &a, const studentas &b) {
        return a.vardas < b.vardas;
    });
}

// Generic template for containers with random access (vector, deque)
template<typename T>
void rikiavimas(T &stud, int krit) {
    switch(krit) {
        case 1:
            std::sort(stud.begin(), stud.end(), VardoRikiavimas);
            break;
        case 2:
            std::sort(stud.begin(), stud.end(), PavardeRikiavimas);
            break;
        case 3:
            std::sort(stud.begin(), stud.end(), MedianaRikiavimas);
            break;
        case 4:
            std::sort(stud.begin(), stud.end(), VidurkisRikiavimas);
            break;
        default:
            std::cerr << "Neteisingas rikiavimo kriterijus. Programos refrence klaida\n";
    }
}

// Specialization for std::list
template<>
inline void rikiavimas(std::list<studentas> &stud, int krit) {
    switch(krit) {
        case 1:
            stud.sort(VardoRikiavimas);
            break;
        case 2:
            stud.sort(PavardeRikiavimas);
            break;
        case 3:
            stud.sort(MedianaRikiavimas);
            break;
        case 4:
            stud.sort(VidurkisRikiavimas);
            break;
        default:
            std::cerr << "Neteisingas rikiavimo kriterijus. Programos refrence klaida\n";
    }
}


template<typename T>
void skaiciavimai(T &stud) {
    for (auto &s : stud) {

        if (!s.nd.empty()) {
            double sum = 0;
            for (int grade : s.nd) {
                sum += grade;
            }
            s.GalVidurkis = sum / s.nd.size();
            

            s.GalVidurkis = s.GalVidurkis * 0.4 + s.egz * 0.6;
            

            std::vector<int> sorted_grades = s.nd;
            std::sort(sorted_grades.begin(), sorted_grades.end());
            
            if (sorted_grades.size() % 2 == 0) {
                s.GalMediana = (sorted_grades[sorted_grades.size() / 2 - 1] + sorted_grades[sorted_grades.size() / 2]) / 2.0;
            } else {
                s.GalMediana = sorted_grades[sorted_grades.size() / 2];
            }
            

            s.GalMediana = s.GalMediana * 0.4 + s.egz * 0.6;
        }
    }
}

template<typename T>
void raides(int &MaxPav, int &MaxVard, const T &stud) {
    MaxPav = 0;
    MaxVard = 0;
    
    for (const auto &s : stud) {
        if (static_cast<int>(s.pavarde.length()) > MaxPav) {
            MaxPav = s.pavarde.length();
        }
        if (static_cast<int>(s.vardas.length()) > MaxVard) {
            MaxVard = s.vardas.length();
        }
    }
}

#endif //STUDENTU_SISTEMA_SKAICIAVIMAI_H