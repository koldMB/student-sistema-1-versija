#include "IsvestisIvestis.h"
#include "Common.h"
#include "klaiduValdymas.h"
#include "Laikas.h"


#include <chrono>
#include <iostream>
#include <random>
#include <array>
#include <iomanip>
#include <fstream>


using std::cout;
using std::cerr;
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
                temp.nd.resize(j); // sumažina vektoriaus dydį iki įvestų pažymių skaičiaus
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

void skaitymas(vector<studentas> &stud, int &n, int nd_sk)
{
    n = 0;
    if (nd_sk <= 0)
    {
        cerr << "Neteisingi parametrai generavimui. Patikrinkite įvestį.\n";
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
            AllExceptionsHandler::TrySetAt(temp.nd, j, dist(gen));
        }
        temp.egz = dist(gen);
        stud.push_back(temp);
        i++;
    }
    n = static_cast<int>(stud.size());
}

void skaitymas(vector<studentas> &stud, int &n, int nd_sk, int VardPavSk)
{
    if (n <= 0 || nd_sk <= 0 || VardPavSk <= 0)
    {
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
        temp.vardas = "Vardas" + std::to_string(i + 1);
        temp.pavarde = "Pavarde" + std::to_string(i + 1);
        temp.nd.resize(nd_sk);
        for (int j = 0; j < nd_sk; ++j) AllExceptionsHandler::TrySetAt(temp.nd, j, score_dist(gen));
        temp.egz = score_dist(gen);
        stud.push_back(temp);
    }
}

void isvestis(const vector<studentas> &stud, int &MaxPav, int &MaxVard)
{
    MaxVard = std::max(MaxVard, 12);
    MaxPav  = std::max(MaxPav, 12);

    std::ostringstream oss; // https://cplusplus.com/reference/sstream/ostringstream/

    oss << left << setw(MaxVard + 2) << "Vardas" << setw(MaxPav + 2) << "Pavardė"
            << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    oss << string(MaxVard + MaxPav + 44, '-') << "\n";
    for(auto &s : stud) {
        oss << left << setw(MaxVard + 2) << s.vardas << setw(MaxPav + 2) << s.pavarde << setw(20) << std::fixed << std::setprecision(2) << s.GalVidurkis << setw(20) << std::fixed << std::setprecision(2) << s.GalMediana << "\n";
    }
    cout << oss.str();
}


void FailoIsvedimas(const vector<studentas> &stud, const string& filename, int &MaxPav, int &MaxVard) {
    std::ofstream f(filename + ".txt");
    if (!f.is_open()) {
        std::cerr << "Nepavyko atidaryti failo rašymui." << filename << "\n";
        return;
    }
    
    std::ostringstream oss; 
    oss << left << setw(MaxVard + 2) << "Vardas" << setw(MaxPav + 2) << "Pavardė"
        << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    oss << string(MaxVard + MaxPav + 44, '-') << "\n";
    for(const auto &s : stud) {
        oss << left << setw(MaxVard + 2) << s.vardas << setw(MaxPav + 2) << s.pavarde
            << setw(20) << std::fixed << std::setprecision(2) << s.GalVidurkis
            << setw(20) << std::fixed << std::setprecision(2) << s.GalMediana << "\n";
    }
    
    f << oss.str();
    f.close();
}

void TermArFailas(const vector<studentas> &stud, int &MaxPav, int &MaxVard) {
    int pasirinkimas;
    cout << "Ar norite išvesti duomenis į failą? (1 - Taip, 2 - Ne): ";
    cin >> pasirinkimas;
    while(pasirinkimas != 1 && pasirinkimas != 2) {
        cerr << "Klaidinga įvestis. Įveskite 1 arba 2: ";
        cin >> pasirinkimas;
    }
    if (pasirinkimas == 1) {
        string filename;
        cout << "Įveskite txt failo pavadinimą: ";
        cin >> filename;
        FailoIsvedimas(stud, filename, MaxPav, MaxVard);
    } else {
        cout << "Duomenys bus išvesti į terminalą.\n";
        isvestis(stud, MaxPav, MaxVard);
    }
}

void FailoNuskaitymas(vector<studentas> &stud, const string& filename) {
    Laikas FailSkait;
    
    std::ifstream f(filename+".txt");
    if (!f.is_open()) {
        cerr << "Klaida: Nepavyko atidaryti failo \"" << filename << ".txt\". Patikrinkite, ar failas egzistuoja.\n";
        return;
    }
    
    AllExceptionsHandler::CatchAll([&]() {

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
            auto vardas_opt = AllExceptionsHandler::TryAt(tokens, 0);
            auto pavarde_opt = AllExceptionsHandler::TryAt(tokens, 1);
            if (!vardas_opt.has_value() || !pavarde_opt.has_value()) continue;
            temp.vardas = vardas_opt.value();
            temp.pavarde = pavarde_opt.value();
            temp.nd.resize(nd_sk);

            // nuskaito namų darbų pažymius
            for (int i = 0; i < nd_sk; i++) {
                auto token_opt = AllExceptionsHandler::TryAt(tokens, 2 + i);
                if (!token_opt.has_value()) continue;
                auto nd_opt = AllExceptionsHandler::TryStoI(token_opt.value());
                if (nd_opt.has_value()) {
                    AllExceptionsHandler::TrySetAt(temp.nd, i, nd_opt.value());
                }
            }

            // nuskaito egzamino pažymį
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