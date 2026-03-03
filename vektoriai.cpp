//implimentacija su vektoriais

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <sstream>
#include <array>

#define NOMINMAX // kertasi su min ir max funkcijomis, todėl ignoruojama iš windows.h šiuos
#include <windows.h>


using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::setw;
using std::sort;
using std::isdigit; //tikrina ar char yra skaitmuo
using std::stoi; //string to int
using std::left;
using std::endl;

struct studentas {
    string vardas = "Vardenis";
    string pavarde = "Pavardenis";
    vector<int> nd = {};
    int egz = 0;
    double GalVidurkis = 0;
    double GalMediana = 0;
};

double LaikasA[] = {0, 0, 0}; // masyvas laikams saugoti 0 - skaitymas, 1 - Rikiavimas pagal vidurkį, 2 - išvestis

#include "Laikas.h"

void skaiciavimai(vector<studentas> &stud); // apskaičiuoja vidurkius ir medianas kiekvienam studentui
void isvestis(const vector<studentas> &stud, int &MaxPav, int &MaxVard); // išveda lentelę su studentų duomenimis į terminalą
void raides(int &MaxPav, int &MaxVard, vector <studentas> &stud); // tikrina vardų ir pavardžių ilgius, kad lentelė būtų tvarkinga
bool isInteger(const string& s);
void skaitymas(vector<studentas> &stud); // paprastas vedimas ranka
void skaitymas(vector<studentas> &stud, int &n, int nd_sk); // generuoja n studentų duomenis su nd_sk namų darbų pažymiais
void skaitymas(vector<studentas> &stud, int &n, int nd_sk, int vardPavSk); // generuoja n studentų duomenis su nd_sk namų darbų pažymiais ir vardais/pavardėmis iš vardPavSk dydžio sąrašo
void FailoNuskaitymas(vector<studentas> &stud, const string& filename); // skaito duomenis iš failo
bool VardoRikiavimas(const studentas &a, const studentas &b); // rikiuoja pagal vardą abėcėlės tvarka
bool MedianaRikiavimas(const studentas &a, const studentas &b); // rikiuoja pagal mediana nuo didžiausio iki mažiausio
bool VidurkisRikiavimas(const studentas &a, const studentas &b); // rikiuoja pagal vidurkis nuo didžiausio iki mažiausio
void rikiavimas(vector<studentas> &stud); // leidžia vartotojui pasirinkti rikiavimo kriterijų
void FailoIsvedimas(const vector<studentas> &stud, const string& filename, int &MaxPav, int &MaxVard); // išveda lentelę su studentų duomenimis į failą
void TermArFailas(const vector<studentas> &stud, int &MaxPav, int &MaxVard); // leidžia vartotojui pasirinkti ar išvesti duomenis į terminalą ar į failą

int main() {
    // Keičiam console į UTF-8 kad galėtų teisingai rodyti lietuviškus simbolius ir juos skaityti
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Laikas laikmatis;
    int MaxPav = 0, MaxVard = 0;
    vector<studentas> stud;
    int pasirinkimas;
    do{
        cout << "1. Įvesti duomenis ranka\n"; 
        cout << "2. Generuoti pažymius\n";
        cout << "3. Generuoti vardus ir pavardes bei pažymius\n";
        cout << "4. Nuskaityti iš failo\n";
        cout << "5. Darbo pabaiga\n";
        cout << "Pasirinkite veiksmą: ";
        string pasirinkimas_str;
        cin >> pasirinkimas_str;
        while(!isInteger(pasirinkimas_str) || stoi(pasirinkimas_str) < 1 || stoi(pasirinkimas_str) > 5) {
            cout << "Klaidinga įvestis. Bandykite dar kartą: ";
            cin >> pasirinkimas_str;
        }
        pasirinkimas = stoi(pasirinkimas_str);
        switch (pasirinkimas) 
        {
            case 1: // veikia
                {
                    skaitymas(stud);
                    skaiciavimai(stud);
                    raides(MaxPav, MaxVard, stud);
                    rikiavimas(stud);
                    TermArFailas(stud, MaxPav, MaxVard);
                    stud.clear();
                }
            break;
            case 2: //veikia
                {
                    int n, nd_sk;
                    cout << "Įveskite kiek namų darbų pažymių norite generuoti: ";
                    string nd_sk_str;
                    cin >> nd_sk_str;
                    while(!isInteger(nd_sk_str) || stoi(nd_sk_str) <= 0) {
                        cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                        cin >> nd_sk_str;
                    }
                    nd_sk = stoi(nd_sk_str);
                    skaitymas(stud, n, nd_sk);
                    skaiciavimai(stud);
                    raides(MaxPav, MaxVard, stud);
                    rikiavimas(stud);
                    TermArFailas(stud, MaxPav, MaxVard);
                    stud.clear();
                }
            break;
            case 3:
                {
                    int n, nd_sk;
                    cout << "Įveskite kiek studentų duomenų norite generuoti: ";
                    string n_str;
                    cin >> n_str;
                    while(!isInteger(n_str) || stoi(n_str) <= 0) {
                        cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                        cin >> n_str;
                    }
                    n = stoi(n_str);
                    cout << "Įveskite kiek namų darbų pažymių norite generuoti: ";
                    string nd_sk_str;
                    cin >> nd_sk_str;
                    while(!isInteger(nd_sk_str) || stoi(nd_sk_str) <= 0) {
                        cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                        cin >> nd_sk_str;
                    }
                    nd_sk = stoi(nd_sk_str);
                    skaitymas(stud, n, nd_sk, n); // antras n perduodamas jei bus vardu sarašas
                    skaiciavimai(stud);
                    raides(MaxPav, MaxVard, stud);
                    rikiavimas(stud);
                    TermArFailas(stud, MaxPav, MaxVard);
                    stud.clear();
                }
            break;
            case 4:
                {
                    string filename;
                    cout << "Įveskite txt failo pavadinimą: ";
                    cin >> filename;
                    FailoNuskaitymas(stud, filename);
                    if(stud.empty()) {
                        cout << "Nėra duomenų išvesti.\n";
                        break;
                    }
                    skaiciavimai(stud);
                    raides(MaxPav, MaxVard, stud);
                    rikiavimas(stud);
                    TermArFailas(stud, MaxPav, MaxVard);
                    stud.clear();
                    cout << "Skaitymas iš failo: " << LaikasA[0]/1000 << " sekundžių\n";
                    cout << "Rikiavimas: " << LaikasA[1]/1000 << " sekundžių\n";
                    cout << "Išvedimas: " << LaikasA[2]/1000 << " sekundžių\n";
                }
            break;
            case 5:
                {
                exit(0);
                }
            break;
        }
    }while(true);

    return 0;
} 

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
        int nd_count;
        cout << "Įveskite namų darbų skaičių: ";
        string nd_sk_str;
        cin >> nd_sk_str;
        if(nd_sk_str == "\\0") return;
        while(!isInteger(nd_sk_str) || stoi(nd_sk_str) <= 0) {
            cout << "Klaidinga įvestis. Bandykite dar kartą: ";
            cin >> nd_sk_str;
            if(nd_sk_str == "\\0") return;
        }
        nd_count = stoi(nd_sk_str);
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

void skaitymas(vector<studentas> &stud, int &n, int nd_sk, int VardPavSk)
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

void raides(int &MaxPav, int &MaxVard, vector <studentas> &stud)
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

bool isInteger(const string& s)
{
    if (s.empty()) return false;

    int start = (s[0] == '-' || s[0] == '+') ? 1 : 0; //praleidžia +/- ženklus

    for (size_t i = start; i < s.size(); i++)
        if (!isdigit(s[i]))
            return false;

    return (s.size() - start) > 0;
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
    int kriterijus;
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
    kriterijus = stoi(kriterijusStr);
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