#include <string>
#include "klaiduValdymas.h"
#include "Common.h"
#include "IsvestisIvestis.h"
#include "Skaiciavimai.h"
#include "Laikas.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;
using std::flush;

bool isInteger(const string &s) {
    if (s.empty()) return false;

    const int start = (s[0] == '-' || s[0] == '+') ? 1 : 0; //praleidžia +/- ženklus

    for (size_t i = start; i < s.size(); i++)
        if (!isdigit(s[i]))
            return false;

    return (s.size() - start) > 0;
}

void atrinkimas(const vector<Studentas> &stud, vector<Studentas> &atrinkti, vector<Studentas> &neatrinkti) {
    cout << "Pagal ką atrinkinėti? (1 - pagal vidurkį, 2 - pagal medianą): " << std::flush;
    string pasirinkimas;
    std::cin >> pasirinkimas;
    while (pasirinkimas != "1" && pasirinkimas != "2") {
        cerr << "Klaidinga įvestis. Bandykite dar kartą: " << std::flush;
        std::cin >> pasirinkimas;
    }
    int pasirinkimas_int = std::stoi(pasirinkimas);
    if (pasirinkimas_int == 1) {
        for (const auto &s: stud) {
            if (s.vidurkis() >= 5) {
                atrinkti.push_back(s);
            } else {
                neatrinkti.push_back(s);
            }
        }
    } else {
        for (const auto &s: stud) {
            if (s.mediana() >= 5) {
                atrinkti.push_back(s);
            } else {
                neatrinkti.push_back(s);
            }
        }
    }
}

void atrinkimasAutomatiskas(vector<Studentas> &stud, vector<Studentas> &geri, vector<Studentas> &blogi) {
    auto partition_point = std::partition(stud.begin(), stud.end(),
        [](const Studentas &s) { return s.mediana() >= 5.0; });
    
    std::copy(stud.begin(), partition_point, std::back_inserter(geri));
    std::copy(partition_point, stud.end(), std::back_inserter(blogi));
    
    stud.clear();
    stud.shrink_to_fit();
}

void Bandymas1_FailuGeneravimas(int sizes[5]) {
    cout << "FAILŲ GENERAVIMAS\n";

    cout << std::left << std::setw(15) << "Studentai"
            << std::setw(20) << "Laikas (ms)"
            << std::setw(20) << "Failas" << "\n";
    cout << string(55, '-') << "\n";

    int nd_sk = 10;
    Laikas timer;
    timer.Reset();  // isvalo praeitus matavimus

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
    cout << "DUOMENŲ APDOROJIMAS (Skaitymas, Rūšiavimas, Rašymas)\n";
    cout << std::left << std::setw(15) << "Studentai"
            << std::setw(20) << "Skaitymas (ms)"
            << std::setw(20) << "Rūšiavimas (ms)"
            << std::setw(20) << "Rašymas (ms)"
            << std::setw(20) << "Iš viso (ms)" << "\n";
    cout << string(95, '-') << "\n";

    Laikas timer;
    timer.Reset();  // isvalo praeitus matavimus

    for (int i = 0; i < 5; ++i) {
        string filename = "studentai" + std::to_string(sizes[i]) + "_gen";
        vector<Studentas> stud;
        int MaxPav = 0, MaxVard = 0;

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
        vector<Studentas> geri, blogi;
        atrinkimasAutomatiskas(stud, geri, blogi);
        if (pas == 1) {
            // vidurkis
            rikiavimas(blogi, 1);
            rikiavimas(geri, 1);
        } else if (pas == 2) {
            // mediana
            rikiavimas(blogi, 2);
            rikiavimas(geri, 2);
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

// Stream input operator
std::istream& operator>>(std::istream& in, Studentas& s) {
    return s.readStudent(in);
}

// Stream output operator
std::ostream& operator<<(std::ostream& out, const Studentas& s) {
    out << std::left 
        << std::setw(15) << s.vardas()
        << std::setw(15) << s.pavarde()
        << std::setw(12) << std::fixed << std::setprecision(2) << s.vidurkis()
        << std::setw(12) << std::fixed << std::setprecision(2) << s.mediana()
        << std::setw(12) << std::fixed << std::setprecision(2) << s.egzaminas();
    return out;
}

// Read student data from input stream
std::istream& Studentas::readStudent(std::istream& in) {
    in >> vardas_ >> pavarde_ >> egzaminas_;
    
    int nd_count;
    in >> nd_count;
    nd_.clear();
    nd_.resize(nd_count);
    
    for (int i = 0; i < nd_count; ++i) {
        in >> nd_[i];
    }
    
    // Calculate median and average
    if (!nd_.empty()) {
        std::vector<double> sorted_nd = nd_;
        std::sort(sorted_nd.begin(), sorted_nd.end());
        
        if (sorted_nd.size() % 2 == 0) {
            mediana_ = (sorted_nd[sorted_nd.size() / 2 - 1] + sorted_nd[sorted_nd.size() / 2]) / 2.0;
        } else {
            mediana_ = sorted_nd[sorted_nd.size() / 2];
        }
        
        double sum = 0.0;
        for (double grade : nd_) {
            sum += grade;
        }
        vidurkis_ = sum / nd_.size();
    } else {
        mediana_ = 0.0;
        vidurkis_ = 0.0;
    }
    
    return in;
}