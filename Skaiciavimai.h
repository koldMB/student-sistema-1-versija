#ifndef STUDENTU_SISTEMA_SKAICIAVIMAI_H
#define STUDENTU_SISTEMA_SKAICIAVIMAI_H

#include "Common.h"
#include <algorithm>
using std::vector;

// Forward declarations for comparison functions
bool VardoRikiavimas(const Studentas &a, const Studentas &b);
bool PavardeRikiavimas(const Studentas &a, const Studentas &b);
bool MedianaRikiavimas(const Studentas &a, const Studentas &b);
bool VidurkisRikiavimas(const Studentas &a, const Studentas &b);

// Function declarations - vector only
void rikiavimas(vector<Studentas> &stud);
void rikiavimas(vector<Studentas> &stud, int krit);
void skaiciavimai(vector<Studentas> &stud);
void raides(int &MaxPav, int &MaxVard, const vector<Studentas> &stud);

// Implementations for vector

inline void rikiavimas(vector<Studentas> &stud) {
    std::sort(stud.begin(), stud.end(), [](const Studentas &a, const Studentas &b) {
        return a.vardas() < b.vardas();
    });
}

inline void rikiavimas(vector<Studentas> &stud, int krit) {
    switch(krit) {
        case 1:
            std::sort(stud.begin(), stud.end(), VidurkisRikiavimas);
            break;
        case 2:
            std::sort(stud.begin(), stud.end(), MedianaRikiavimas);
            break;
        case 3:
            // nerikiuoti
            break;
        default:
            std::cerr << "Neteisingas rikiavimo kriterijus. Programos refrence klaida\n";
    }
}

inline void skaiciavimai(vector<Studentas> &stud) {
    for (auto &s : stud) {

        if (!s.nd().empty()) {
            double sum = 0;
            for (double grade : s.nd()) {
                sum += grade;
            }
            double vid = sum / s.nd().size();
            

            vid = vid * 0.4 + s.egzaminas() * 0.6;
            s.setVidurkis(vid);
            

            std::vector<double> sorted_grades(s.nd().begin(), s.nd().end());
            std::sort(sorted_grades.begin(), sorted_grades.end());
            
            double med;
            if (sorted_grades.size() % 2 == 0) {
                med = (sorted_grades[sorted_grades.size() / 2 - 1] + sorted_grades[sorted_grades.size() / 2]) / 2.0;
            } else {
                med = sorted_grades[sorted_grades.size() / 2];
            }
            

            med = med * 0.4 + s.egzaminas() * 0.6;
            s.setMediana(med);
        }
    }
}

inline void raides(int &MaxPav, int &MaxVard, const vector<Studentas> &stud) {
    MaxPav = 0;
    MaxVard = 0;
    
    for (const auto &s : stud) {
        if (static_cast<int>(s.pavarde().length()) > MaxPav) {
            MaxPav = s.pavarde().length();
        }
        if (static_cast<int>(s.vardas().length()) > MaxVard) {
            MaxVard = s.vardas().length();
        }
    }
}

#endif //STUDENTU_SISTEMA_SKAICIAVIMAI_H