#include <string>
#include "klaiduValdymas.h"
#include "Common.h"
#include "IsvestisIvestis.h"
#include "Skaiciavimai.h"
#include "Laikas.h"
#include <iostream>
#include <iomanip>

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;
using std::flush;

bool isInteger(const string& s)
{
    if (s.empty()) return false;

    const int start = (s[0] == '-' || s[0] == '+') ? 1 : 0; //praleidžia +/- ženklus

    for (size_t i = start; i < s.size(); i++)
        if (!isdigit(s[i]))
            return false;

    return (s.size() - start) > 0;
}

void atrinkimas(const vector<studentas> &stud, vector<studentas> &atrinkti, vector<studentas> &neatrinkti) {
    cout << "Pagal ką atrinkinėti? (1 - pagal vidurkį, 2 - pagal medianą): " << std::flush;
    string pasirinkimas;
    std::cin >> pasirinkimas;
    while (pasirinkimas != "1" && pasirinkimas != "2") {
        cerr << "Klaidinga įvestis. Bandykite dar kartą: " << std::flush;
        std::cin >> pasirinkimas;
    }
    int pasirinkimas_int = std::stoi(pasirinkimas);
    if(pasirinkimas_int == 1) {
        for (const auto& s : stud) {
            if (s.GalVidurkis >= 5) {
                atrinkti.push_back(s);
            } else {
                neatrinkti.push_back(s);
            }
        }
    } else {
        for (const auto& s : stud) {
            if (s.GalMediana >= 5) {
                atrinkti.push_back(s);
            } else {
                neatrinkti.push_back(s);
            }
        }
    }
}

void atrinkimasAutomatiskas(const vector<studentas> &stud, vector<studentas> &geri, vector<studentas> &blogi) {
    for (const auto& s : stud) {
        if (s.GalMediana >= 5.0) {
            geri.push_back(s);
        } else {
            blogi.push_back(s);
        }
    }
}

void Bandymas1_FailuGeneravimas(int sizes[5]) {

    cout << "1 BANDYMAS: FAILŲ GENERAVIMAS\n";
    
    cout << std::left << std::setw(15) << "Studentai" 
         << std::setw(20) << "Laikas (ms)" 
         << std::setw(20) << "Failas" << "\n";
    cout << string(55, '-') << "\n";

    int nd_sk = 10;
    Laikas timer;

    for (int i = 0; i < 5; ++i) {
        string filename = "studentai" + std::to_string(sizes[i]) + "_gen";
        
        timer.Reset();
        timer.PradekLaikmati();
        GeneruotiStudentuFaila(filename, sizes[i], nd_sk);
        timer.BaigtiLaikmati();

        cout << std::left << std::setw(15) << sizes[i]
                << std::setw(20) << LaikoVektorius.back()
                << std::setw(20) << filename << "\n";
    }
    
    cout << "\n";
}

void Bandymas2_DuomenuApdorojimas(int sizes[5], const int pas) {
    cout << "2 BANDYMAS: DUOMENŲ APDOROJIMAS (Skaitymas, Rūšiavimas, Rašymas)\n";
    cout << std::left << std::setw(15) << "Studentai" 
         << std::setw(20) << "Skaitymas (ms)"
         << std::setw(20) << "Rūšiavimas (ms)"
         << std::setw(20) << "Rašymas (ms)"
         << std::setw(20) << "Iš viso (ms)" << "\n";
    cout << string(95, '-') << "\n";

    for (int i = 0; i < 5; ++i) {
        string filename = "studentai" + std::to_string(sizes[i]) + "_gen";
        vector<studentas> stud;
        int MaxPav = 0, MaxVard = 0;

        Laikas timer;
        timer.Reset();

        // Laiko pradžia (iš viso)
        timer.PradekLaikmati();
        
        // 1. Duomenų nuskaitymas
        timer.PradekLaikmati();
        FailoNuskaitymas(stud, filename);
        timer.BaigtiLaikmati();
        double reading_time = LaikoVektorius.back();

        // 2. Skaiciavimai
        skaiciavimai(stud);

        // 3. Rūšiavimas
        timer.PradekLaikmati();
        vector<studentas> geri, blogi;
        atrinkimasAutomatiskas(stud, geri, blogi);
        if (pas == 1) {
            // vidurkis
            rikiavimas(blogi, 4);
            rikiavimas(geri, 4);
        } else if (pas == 2) {
            // mediana
            rikiavimas(blogi, 3);
            rikiavimas(geri, 3);
        } else exit(-9);
        timer.BaigtiLaikmati();
        double sorting_time = LaikoVektorius.back();

        // 4. Rašymas
        timer.PradekLaikmati();
        raides(MaxPav, MaxVard, stud);
        IsvestiBlogusGerusFailus(geri, blogi, filename, MaxPav, MaxVard);
        timer.BaigtiLaikmati();
        double writing_time = LaikoVektorius.back();

        // Laiko pabaiga
        timer.BaigtiLaikmati();
        double total_time = LaikoVektorius.back();

        cout << std::left << std::setw(15) << sizes[i]
                << std::setw(20) << reading_time
                << std::setw(20) << sorting_time
                << std::setw(20) << writing_time
                << std::setw(20) << reading_time + sorting_time + writing_time << "\n";

        // Išvalyti
        stud.clear();
        geri.clear();
        blogi.clear();
    }

    cout << "\n";
}