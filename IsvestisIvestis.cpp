#include "IsvestisIvestis.h"
#include "Common.h"

#include <chrono>
#include <iostream>
#include <random>
#include <array>
#include <iomanip>
#include <fstream>

#include "Laikas.h"

using std::cout;
using std::endl;
using std::vector;
using std::cin;
using std::stoi;
using std::left;
using std::setw;

void skaitymas(vector<studentas> &stud)
{
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
        while(!isInteger(nd_sk_str) || stoi(nd_sk_str) <= 0) {
            cout << "Klaidinga įvestis. Bandykite dar kartą: ";
            cin >> nd_sk_str;
            if(nd_sk_str == "\\0") return;
        }
        const int nd_count = stoi(nd_sk_str);
        temp.nd.resize(nd_count);

        for(int j = 0; j < nd_count; j++) {
            cout << "Įveskite " << j + 1 << " namų darbų įvertinimą: ";
            string nd_str;
            cin >> nd_str;
            if(nd_str == "\\0") {
                temp.nd.resize(j); // sumažina vektoriaus dydį iki įvestų pažymių skaičiaus
                return;
            }
            while(!isInteger(nd_str) || stoi(nd_str) < 0 || stoi(nd_str) > 10) {
                cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                cin >> nd_str;
                if(nd_str == "\\0") return;
            }
            temp.nd[j] = stoi(nd_str);
        }
        cout << "Įveskite egzamino įvertinimą: ";
        string egz_str;
        cin >> egz_str;
        if(egz_str == "\\0") {
            temp.nd.clear();
            return;
        }
        temp.egz = stoi(egz_str);
        stud.push_back(temp);
        n++;
    }
}

void skaitymas(vector<studentas> &stud, int &n, int nd_sk)
{
    n = 0;
    if (nd_sk <= 0)
    {
        cout << "Neteisingi parametrai generavimui. Patikrinkite įvestį.\n";
        return;
    }
    // std::random_device is a uniformly-distributed integer random number generator that produces non-deterministic random numbers.
    std::random_device rd;
    /*
    static std::chrono::time_point<std::chrono::high_resolution_clock> now() noexcept;
	Returns a time point representing the current point in time.
    */
    std::array<unsigned int, 2> seed_data = {rd(), static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::seed_seq seed(seed_data.begin(), seed_data.end());
    // A Mersenne Twister pseudo-random generator of 64-bit numbers with a state size of 19937 bits.
    std::mt19937_64 gen(seed);
    /*
    Produces random integer values i, uniformly distributed on the closed interval [a, b], that is, distributed according to the discrete probability function
    */
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
            temp.nd[j] = dist(gen);
        }
        temp.egz = dist(gen);
        stud.push_back(temp);
        i++;
    }
    n = static_cast<int>(stud.size());
}

void skaitymas(vector<studentas> &stud, const int n, const int nd_sk, const int VardPavSk)
{
    if (n <= 0 || nd_sk <= 0 || VardPavSk <= 0)
    {
        cout << "Neteisingi parametrai generavimui. Patikrinkite įvestį.\n";
        return;
    }

    std::random_device rd;
    std::array<unsigned int, 2> seed_data = {rd(), static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::seed_seq seed(seed_data.begin(), seed_data.end());
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution<> score_dist(1, 10);

    for (int i = 0; i < n; ++i) {
        studentas temp;
        temp.vardas = "Vardas" + std::to_string(i + 1);
        temp.pavarde = "Pavarde" + std::to_string(i + 1);
        temp.nd.resize(nd_sk);
        for (int j = 0; j < nd_sk; ++j) temp.nd[j] = score_dist(gen);
        temp.egz = score_dist(gen);
        stud.push_back(temp);
    }
}

void isvestis(const vector<studentas> &stud, int &MaxPav, int &MaxVard)
{
    MaxVard = std::max(MaxVard, 12);
    MaxPav  = std::max(MaxPav, 12);

    cout << left << setw(MaxVard + 2) << "Vardas" << setw(MaxPav + 2) << "Pavardė"
            << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    cout << string(MaxVard + MaxPav + 44, '-') << "\n";
    for(auto &s : stud) {
        cout << left << setw(MaxVard + 2) << s.vardas << setw(MaxPav + 2) << s.pavarde << setw(20) << std::fixed << std::setprecision(2) << s.GalVidurkis << setw(20) << std::fixed << std::setprecision(2) << s.GalMediana << "\n";
    }
}


void FailoIsvedimas(const vector<studentas> &stud, const string& filename, int &MaxPav, int &MaxVard) {
    Laikas FailIsvesk;
    FailIsvesk.PradekLaikmati();
    std::ofstream f(filename);
    if (!f.is_open()) {
        std::cerr << "Nepavyko atidaryti failo rašymui." << filename << "\n";
        return;
    }
    f << left << setw(MaxVard + 2) << "Vardas" << setw(MaxPav + 2) << "Pavardė"
      << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    f << string(MaxVard + MaxPav + 44, '-') << "\n";
    for(const auto &s : stud) {
        f << left << setw(MaxVard + 2) << s.vardas << setw(MaxPav + 2) << s.pavarde
          << setw(20) << std::fixed << std::setprecision(2) << s.GalVidurkis
          << setw(20) << std::fixed << std::setprecision(2) << s.GalMediana << "\n";
    }
    f.close();
    FailIsvesk.BaiktiLaikmati(2);
}

void TermArFailas(const vector<studentas> &stud, int &MaxPav, int &MaxVard) {
    int pasirinkimas;
    cout << "Ar norite išvesti duomenis į failą? (1 - Taip, 2 - Ne): ";
    cin >> pasirinkimas;
    while(pasirinkimas != 1 && pasirinkimas != 2) {
        cout << "Klaidinga įvestis. Įveskite 1 arba 2: ";
        cin >> pasirinkimas;
    }
    if (pasirinkimas == 1) {
        string filename;
        cout << "Įveskite txt failo pavadinimą (su .txt): ";
        cin >> filename;
        FailoIsvedimas(stud, filename, MaxPav, MaxVard);
    } else {
        cout << "Duomenys bus išvesti į terminalą.\n";
        isvestis(stud, MaxPav, MaxVard);
    }
}