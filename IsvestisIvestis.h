#ifndef STUDENTU_SISTEMA_ISVESTISIVESTIS_H
#define STUDENTU_SISTEMA_ISVESTISIVESTIS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <deque>
#include <random>
#include <chrono>
#include <array>
#include "Common.h"
#include "klaiduValdymas.h"

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::cin;

// Forward declaration of pad_utf8 function
string pad_utf8(const string& str, size_t width);

template<template<typename> class T>
void skaitymas(T<studentas> &stud); // paprastas vedimas ranka

template<template<typename> class T>
void skaitymas(T<studentas> &stud, int &n, int nd_sk); // generuoja n studentų duomenis su nd_sk namų darbų pažymiais

template<template<typename> class T>
void skaitymas(T<studentas> &stud, int &n, int nd_sk, int VardPavSk); // generuoja n studentų duomenis su nd_sk namų darbų pažymiais ir vardais/pavardėmis iš vardPavSk dydžio sąrašo

template<template<typename> class T>
void FailoNuskaitymas(T<studentas> &stud, const string& filename); // skaito duomenis iš failo

template<template<typename> class T>
void FailoIsvedimas(const T<studentas> &stud, const string& filename, int &MaxPav, int &MaxVard); // išveda lentelę su studentų duomenimis į failą

template<template<typename> class T>
void TermArFailas(const T<studentas> &stud, int &MaxPav, int &MaxVard); // leidžia vartotojui pasirinkti ar išvesti duomenis į terminalą ar į failą

template<template<typename> class T>
void isvestis(const T<studentas> &stud, int &MaxPav, int &MaxVard); // išveda lentelę su studentų duomenimis į terminalą

template<template<typename> class T1, template<typename> class T2>
void IsvestiGeriBlogiFailus(const T1<studentas> &geri, const T2<studentas> &blogi, int MaxPav, int MaxVard); // išveda gerus ir blogus studentus į atskirus failus

template<template<typename> class T1, template<typename> class T2>
void IsvestiBlogusGerusFailus(const T1<studentas> &geri, const T2<studentas> &blogi, const string& basename, int MaxPav, int MaxVard); // išveda gerus ir blogus studentus į atskirus failus su nurodyta bazė

void GeneruotiStudentuFaila(const string& filename, int student_count, int nd_sk); // generuoja studentų failą su nurodytais parametrais


template<typename Container>
string randomVardas(Container &stud) {
    static const std::array<string, 67> vardai = {
        "Jonas", "Petras", "Andrius", "Tomas", "Matas",
        "Lukas", "Mantas", "Domas", "Karolis", "Rokas",
        "Paulius", "Justas", "Dovydas", "Martynas", "Edvinas",
        "Simonas", "Aurimas", "Deividas", "Rytis", "Giedrius",
        "Abdonas", "Abrahimas", "Abraomas", "Achilas", "Adalbertas", 
        "Adas", "Adauktas", "Adeodatas", "Adolfas", "Adolis", "Adomas",
        "Adonis", "Adrianas", "Adrijanas", "Adrijonas", "Adrijus", 
        "Agapitas", "Agatas", "Agatonas", "Agedas", "Agėjus", "Agilas",
        "Agnijus", "Agnius", "Aidanas", "Aidas", "Aidis", "Aidonas", 
        "Ainis", "Airidas", "Airingas", "Airis", "Airūnas", "Aistis", 
        "Aitvaras", "Aivaras", "Akselis", "Akvilas", "Akvilijus", "Akvilinas",
        "Alanas", "Alantas", "Albas", "Albertas", "Albertinas", "Albinas", 
        "Albrechtas"
    };
    std::random_device rd;
    std::array<unsigned int, 2> seed_data = {rd(), static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::seed_seq seed(seed_data.begin(), seed_data.end());
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution<> dist(0, vardai.size() - 1);
    return vardai[dist(gen)];
}

template<typename Container>
string randomPavarde(Container &stud) {
    static const std::array<string, 100> pavardes = {
        "Kazlauskas", "Stankevičius", "Petrauskas", "Jankauskas", "Žukauskas",
        "Butkus", "Balčiūnas", "Paulauskas", "Vasiliauskas", "Baranauskas", "Urbonas",
        "Navickas", "Ramanauskas", "Savickas", "Rimkus", "Žilinskas", "Šimkus",
        "Kavaliauskas", "Sakalauskas", "Ivanauskas", "Adomaitis", "Žemaitis", "Kairys",
        "Janauskas", "Kuzmickas", "Matkevičius", "Domeika", "Mačys", "Zubovskis",
        "Paulavičius", "Radauskas", "Šturm", "Zikaras", "Vaičaitis", "Valauskas",
        "Varnagiris", "Žebertavičius", "Zubavičius", "Astravas", "Braziulis", "Brazauskas",
        "Budraitis", "Cesiulis", "Čepulis", "Dabulskis", "Dimša", "Dovidaitis", "Einikis",
        "Embikas", "Fiedorovas", "Gaigalis", "Gudauskas", "Gedvilas", "Gedmintas", "Genaitis",
        "Girulis", "Glemža", "Godenis", "Gončarovas", "Graužinis", "Grinius", "Grishaiuš",
        "Gudauskas", "Gudelinas", "Gudliauskis", "Gudžius", "Gulbinas", "Gumblauskas", "Gumbus",
        "Guobis", "Gvozdinskas", "Jablonski", "Jablonskis", "Jakas", "Jakelis", "Jakilauskas",
        "Jokimas", "Jonaitis", "Jonakaitis", "Jonalauskas", "Jonavicius", "Jonelinas", "Joneliunas",
        "Jonevičius", "Joniškaitis", "Jonuškevičius", "Jonutis", "Jonusas", "Jucaitis", "Jucevičius"
    };
    std::random_device rd;
    std::array<unsigned int, 2> seed_data = {rd(), static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::seed_seq seed(seed_data.begin(), seed_data.end());
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution<> dist(0, pavardes.size() - 1);
    return pavardes[dist(gen)];
}


template<template<typename> class T>
void FailoIsvedimas(const T<studentas> &stud, const string& filename, int &MaxPav, int &MaxVard) {
    int MaxPav_local = 0, MaxVard_local = 0;
    for(const auto &s : stud) {
        if(static_cast<int>(s.pavarde.length()) > MaxPav_local) {
            MaxPav_local = static_cast<int>(s.pavarde.length());
        }
        if(static_cast<int>(s.vardas.length()) > MaxVard_local) {
            MaxVard_local = static_cast<int>(s.vardas.length());
        }
    }
    MaxPav_local = std::max(MaxPav_local, 12);
    MaxVard_local = std::max(MaxVard_local, 12);
    
    std::ofstream f(filename + ".txt");
    if (!f.is_open()) {
        std::cerr << "Nepavyko atidaryti failo rašymui." << filename << "\n";
        return;
    }
    
    std::ostringstream oss;
    oss << pad_utf8("Vardas", MaxVard_local + 2) << pad_utf8("Pavardė", MaxPav_local + 2)
        << std::setw(20) << "Galutinis (vid.)" << std::setw(20) << "Galutinis (med.)" << "\n";
    oss << std::string(MaxVard_local + MaxPav_local + 44, '-') << "\n";
    for(const auto &s : stud) {
        oss << pad_utf8(s.vardas, MaxVard_local + 2) << pad_utf8(s.pavarde, MaxPav_local + 2)
            << std::setw(20) << std::fixed << std::setprecision(2) << s.GalVidurkis
            << std::setw(20) << std::fixed << std::setprecision(2) << s.GalMediana << "\n";
    }
    
    f << oss.str();
    f.close();
}

template<template<typename> class T>
void TermArFailas(const T<studentas> &stud, int &MaxPav, int &MaxVard) {
    int pasirinkimas;
    std::cout << "Ar norite išvesti duomenis į failą? (1 - Taip, 2 - Ne): ";
    std::cin >> pasirinkimas;
    while(pasirinkimas != 1 && pasirinkimas != 2) {
        std::cerr << "Klaidinga įvestis. Įveskite 1 arba 2: ";
        std::cin >> pasirinkimas;
    }
    if (pasirinkimas == 1) {
        string filename;
        std::cout << "Įveskite txt failo pavadinimą: ";
        std::cin >> filename;
        FailoIsvedimas(stud, filename, MaxPav, MaxVard);
    } else {
        std::cout << "Duomenys bus išvesti į terminalą.\n";
        isvestis(stud, MaxPav, MaxVard);
    }
}

template<template<typename> class T>
void isvestis(const T<studentas> &stud, int &MaxPav, int &MaxVard) {
    MaxVard = std::max(MaxVard, 12);
    MaxPav  = std::max(MaxPav, 12);

    std::ostringstream oss;
    oss << pad_utf8("Vardas", MaxVard + 2) << pad_utf8("Pavardė", MaxPav + 2)
            << std::setw(20) << "Galutinis (vid.)" << std::setw(20) << "Galutinis (med.)" << "\n";
    oss << std::string(MaxVard + MaxPav + 44, '-') << "\n";
    for(const auto &s : stud) {
        oss << pad_utf8(s.vardas, MaxVard + 2) << pad_utf8(s.pavarde, MaxPav + 2)
            << std::setw(20) << std::fixed << std::setprecision(2) << s.GalVidurkis
            << std::setw(20) << std::fixed << std::setprecision(2) << s.GalMediana << "\n";
    }
    std::cout << oss.str();
}

template<template<typename> class T1, template<typename> class T2>
void IsvestiGeriBlogiFailus(const T1<studentas> &geri, const T2<studentas> &blogi, int MaxPav, int MaxVard) {
    MaxVard = std::max(MaxVard, 12);
    MaxPav = std::max(MaxPav, 12);

    std::ofstream geri_failas("geru_studentu_sarasas.txt");
    std::ofstream blogi_failas("blogu_studentu_sarasas.txt");
    if (!geri_failas.is_open() || !blogi_failas.is_open()) {
        std::cerr << "Klaida atidarant failus rašymui." << std::endl;
        return;
    }
    // Geri studentai
    geri_failas << pad_utf8("Vardas", MaxVard + 2) << pad_utf8("Pavardė", MaxPav + 2)
        << std::setw(20) << "Galutinis (vid.)" << std::setw(20) << "Galutinis (med.)" << "\n";
    geri_failas << std::string(MaxVard + MaxPav + 44, '-') << "\n";
    for (const auto& s : geri) {
        geri_failas << pad_utf8(s.vardas, MaxVard + 2) << pad_utf8(s.pavarde, MaxPav + 2)
            << std::setw(20) << std::fixed << std::setprecision(2) << s.GalVidurkis
            << std::setw(20) << std::fixed << std::setprecision(2) << s.GalMediana << "\n";
    }
    // Blogi studentai
    blogi_failas << pad_utf8("Vardas", MaxVard + 2) << pad_utf8("Pavardė", MaxPav + 2)
        << std::setw(20) << "Galutinis (vid.)" << std::setw(20) << "Galutinis (med.)" << "\n";
    blogi_failas << std::string(MaxVard + MaxPav + 44, '-') << "\n";
    for (const auto& s : blogi) {
        blogi_failas << pad_utf8(s.vardas, MaxVard + 2) << pad_utf8(s.pavarde, MaxPav + 2)
            << std::setw(20) << std::fixed << std::setprecision(2) << s.GalVidurkis
            << std::setw(20) << std::fixed << std::setprecision(2) << s.GalMediana << "\n";
    }
    geri_failas.close();
    blogi_failas.close();
}

template<template<typename> class T1, template<typename> class T2>
void IsvestiBlogusGerusFailus(const T1<studentas> &geri, const T2<studentas> &blogi, const string& basename, int MaxPav, int MaxVard) {
    MaxVard = std::max(MaxVard, 12);
    MaxPav = std::max(MaxPav, 12);

    std::ofstream geri_failas(basename + "_geri.txt");
    std::ofstream blogi_failas(basename + "_blogi.txt");
    if (!geri_failas.is_open() || !blogi_failas.is_open()) {
        std::cerr << "Klaida atidarant failus rašymui." << std::endl;
        return;
    }
    // Geri studentai
    geri_failas << pad_utf8("Vardas", MaxVard + 2) << pad_utf8("Pavardė", MaxPav + 2)
        << std::setw(20) << "Galutinis (vid.)" << std::setw(20) << "Galutinis (med.)" << "\n";
    geri_failas << std::string(MaxVard + MaxPav + 44, '-') << "\n";
    for (const auto& s : geri) {
        geri_failas << pad_utf8(s.vardas, MaxVard + 2) << pad_utf8(s.pavarde, MaxPav + 2)
            << std::setw(20) << std::fixed << std::setprecision(2) << s.GalVidurkis
            << std::setw(20) << std::fixed << std::setprecision(2) << s.GalMediana << "\n";
    }
    // Blogi studentai
    blogi_failas << pad_utf8("Vardas", MaxVard + 2) << pad_utf8("Pavardė", MaxPav + 2)
        << std::setw(20) << "Galutinis (vid.)" << std::setw(20) << "Galutinis (med.)" << "\n";
    blogi_failas << std::string(MaxVard + MaxPav + 44, '-') << "\n";
    for (const auto& s : blogi) {
        blogi_failas << pad_utf8(s.vardas, MaxVard + 2) << pad_utf8(s.pavarde, MaxPav + 2)
            << std::setw(20) << std::fixed << std::setprecision(2) << s.GalVidurkis
            << std::setw(20) << std::fixed << std::setprecision(2) << s.GalMediana << "\n";
    }
    geri_failas.close();
    blogi_failas.close();
}

// Template implementations for input functions
template<template<typename> class T>
void skaitymas(T<studentas> &stud) {
    studentas temp;
    string laikinas;
    int n = 0;
    cout << "Jeigu norite baigti darba įveskite \\0" << "\n";
    while(true) {
        cout << "Įveskite " << n + 1 << " studento vardą: ";
        cin >> laikinas;
        if(laikinas == "\\0") return;
        temp.vardas = laikinas;
        cout << "Įveskite " << n + 1 << " studento pavardę: ";
        cin >> laikinas;
        if(laikinas == "\\0") return;
        temp.pavarde = laikinas;
        cout << "Įveskite namų darbų skaičių: ";
        string nd_sk_str;
        cin >> nd_sk_str;
        if(nd_sk_str == "\\0") return;
        auto nd_sk_opt = AllExceptionsHandler::TryStoI(nd_sk_str);
        while(!nd_sk_opt.has_value() || nd_sk_opt.value() <= 0) {
            cerr << "Klaidinga įvestis. Bandykite dar kartą: ";
            cin >> nd_sk_str;
            if(nd_sk_str == "\\0") return;
            nd_sk_opt = AllExceptionsHandler::TryStoI(nd_sk_str);
        }
        const int nd_count = nd_sk_opt.value();
        temp.nd.resize(nd_count);

        for(int j = 0; j < nd_count; j++) {
            cout << "Įveskite " << j + 1 << " namų darbų įvertinimą: ";
            string nd_str;
            cin >> nd_str;
            if(nd_str == "\\0") {
                temp.nd.resize(j);
                return;
            }
            auto nd_opt = AllExceptionsHandler::TryStoI(nd_str);
            while(!nd_opt.has_value() || nd_opt.value() < 0 || nd_opt.value() > 10) {
                cerr << "Klaidinga įvestis. Bandykite dar kartą: ";
                cin >> nd_str;
                if(nd_str == "\\0") return;
                nd_opt = AllExceptionsHandler::TryStoI(nd_str);
            }
            temp.nd[j] = nd_opt.value();
        }
        cout << "Įveskite egzamino įvertinimą: ";
        string egz_str;
        cin >> egz_str;
        if(egz_str == "\\0") {
            temp.nd.clear();
            return;
        }
        auto egz_opt = AllExceptionsHandler::TryStoI(egz_str);
        if (egz_opt.has_value()) {
            temp.egz = egz_opt.value();
        }
        stud.push_back(temp);
        n++;
    }
}

template<template<typename> class T>
void skaitymas(T<studentas> &stud, int &n, int nd_sk) {
    n = 0;
    if (nd_sk <= 0) {
        cerr << "Neteisingi parametrai generavimui. Patikrinkite įvestį.\n";
        return;
    }
    std::random_device rd;
    std::array<unsigned int, 2> seed_data = {rd(), static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::seed_seq seed(seed_data.begin(), seed_data.end());
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution<> dist(1, 10);
    string laikinas;
    cout << "Įveskite \\0 norėdami baigti duomenų įvedimą\n";
    int i = 0;
    while(true) {
        studentas temp;
        cout << "Įveskite " << i + 1 << " studento vardą: ";
        cin >> laikinas;
        if(laikinas == "\\0") break;
        temp.vardas = laikinas;
        cout << "Įveskite " << i + 1 << " studento pavardę: ";
        cin >> laikinas;
        if(laikinas == "\\0") break;
        temp.pavarde = laikinas;
        temp.nd.resize(nd_sk);
        for (int j = 0; j < nd_sk; ++j) {
            AllExceptionsHandler::TrySetAt(temp.nd, j, dist(gen));
        }
        temp.egz = dist(gen);
        stud.push_back(temp);
        i++;
    }
    n = static_cast<int>(stud.size());
}

template<template<typename> class T>
void skaitymas(T<studentas> &stud, int &n, int nd_sk, int VardPavSk) {
    if (n <= 0 || nd_sk <= 0 || VardPavSk <= 0) {
        cerr << "Neteisingi parametrai generavimui. Patikrinkite įvestį.\n";
        return;
    }
    std::random_device rd;
    std::array<unsigned int, 2> seed_data = {rd(), static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::seed_seq seed(seed_data.begin(), seed_data.end());
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution<> score_dist(1, 10);

    for (int i = 0; i < n; ++i) {
        studentas temp;
        temp.vardas = randomVardas(stud);
        temp.pavarde = randomPavarde(stud);
        temp.nd.resize(nd_sk);
        for (int j = 0; j < nd_sk; ++j) AllExceptionsHandler::TrySetAt(temp.nd, j, score_dist(gen));
        temp.egz = score_dist(gen);
        stud.push_back(temp);
    }
}

template<template<typename> class T>
void FailoNuskaitymas(T<studentas> &stud, const string& filename) {
    std::ifstream f(filename+".txt");
    if (!f.is_open()) {
        std::cerr << "Klaida: Nepavyko atidaryti failo \"" << filename << ".txt\". Patikrinkite, ar failas egzistuoja.\n";
        return;
    }
    
    AllExceptionsHandler::CatchAll([&]() {
        f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int nd_sk = -1;
        string line;

        while (std::getline(f, line)) {
            if (line.empty()) continue;
            
            std::istringstream iss(line);
            string token;
            std::vector<string> tokens;
            while (iss >> token) {
                tokens.push_back(token);
            }

            if (tokens.size() < 4) continue;

            if (nd_sk == -1) {
                nd_sk = static_cast<int>(tokens.size()) - 3;
            }

            studentas temp;
            auto vardas_opt = AllExceptionsHandler::TryAt(tokens, 0);
            auto pavarde_opt = AllExceptionsHandler::TryAt(tokens, 1);
            if (!vardas_opt.has_value() || !pavarde_opt.has_value()) continue;
            temp.vardas = vardas_opt.value();
            temp.pavarde = pavarde_opt.value();
            temp.nd.resize(nd_sk);

            for (int i = 0; i < nd_sk; i++) {
                auto token_opt = AllExceptionsHandler::TryAt(tokens, 2 + i);
                if (!token_opt.has_value()) continue;
                auto nd_opt = AllExceptionsHandler::TryStoI(token_opt.value());
                if (nd_opt.has_value()) {
                    AllExceptionsHandler::TrySetAt(temp.nd, i, nd_opt.value());
                }
            }

            auto egz_token_opt = AllExceptionsHandler::TryAt(tokens, 2 + nd_sk);
            if (egz_token_opt.has_value()) {
                auto egz_opt = AllExceptionsHandler::TryStoI(egz_token_opt.value());
                if (egz_opt.has_value()) {
                    temp.egz = egz_opt.value();
                }
            }

            stud.push_back(temp);
        }
        f.close();
    });
}

// Template overloads for list and deque
template<typename T>
void skaitymas(T &stud) {
    vector<studentas> temp;
    skaitymas(temp);
    stud.assign(temp.begin(), temp.end());
}

template<typename T>
void skaitymas(T &stud, int &n, int nd_sk) {
    vector<studentas> temp;
    skaitymas(temp, n, nd_sk);
    stud.assign(temp.begin(), temp.end());
}

template<typename T>
void skaitymas(T &stud, int &n, int nd_sk, int VardPavSk) {
    vector<studentas> temp;
    skaitymas(temp, n, nd_sk, VardPavSk);
    stud.assign(temp.begin(), temp.end());
}

template<typename T>
void FailoNuskaitymas(T &stud, const string& filename) {
    vector<studentas> temp;
    FailoNuskaitymas(temp, filename);
    stud.assign(temp.begin(), temp.end());
}

template<typename T>
void TermArFailas(const T &stud, int &MaxPav, int &MaxVard) {
    vector<studentas> temp(stud.begin(), stud.end());
    TermArFailas(temp, MaxPav, MaxVard);
}

#endif //STUDENTU_SISTEMA_ISVESTISIVESTIS_H