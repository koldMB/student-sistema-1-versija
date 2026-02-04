//implimentacija su vektoriais

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <iomanip>
#include <cctype>
#include <cstdlib>


using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::setw;
using std::sort;
using std::isdigit; //tikrina ar char yra skaitmuo
using std::stoi; //string to int
using std::left;

struct studentas {
    string vardas = "Vardenis";
    string pavarde = "Pavardenis";
    vector<int> nd = {0};
    int egz = 0;
    double vidurkis = 0;
    double mediana = 0;
};

void skaičiavimai(vector<studentas> &stud);
void išvestis(const vector<studentas> &stud, int &MaxPav, int &MaxVard);
void raidės(int &MaxPav, int &MaxVard, vector <studentas> &stud);
bool isInteger(const string& s);
void skaitymas(vector<studentas> &stud, bool genPaz = false, int n = 0, int nd_sk = 0, bool genVardPav = false, int vardPavSk = 0);


int main() {
    studentas temp;
    int MaxPav = 0, MaxVard = 0;
    vector<studentas> stud;
    int pasirinkimas;
    do{
        cout << "1. Įvesti duomenis ranka\n";
        cout << "2. Generuoti pažymius\n";
        cout << "3. Generuoti vardus ir pavardes bei pažymius\n";
        cout << "4. Darbo pabaiga\n";
        cout << "Pasirinkite veiksmą: ";
        string pasirinkimas_str;
        cin >> pasirinkimas_str;
        while(!isInteger(pasirinkimas_str) || stoi(pasirinkimas_str) < 1 || stoi(pasirinkimas_str) > 4) {
            cout << "Klaidinga įvestis. Bandykite dar kartą: ";
            cin >> pasirinkimas_str;
        }
        pasirinkimas = stoi(pasirinkimas_str);
        switch (pasirinkimas) 
        {
            case 1:
                skaitymas(stud, false, 0, 0, false, 0);
            break;
            case 2:
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
                    skaitymas(stud, true, n, nd_sk, false, 0);
                }
            break;
            case 3:
                {
                    int n, nd_sk, VardPavSk;
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
                    cout << "Įveskite vardų ir pavardžių sąrašo dydį: ";
                    string VardPavSk_str;
                    cin >> VardPavSk_str;
                    while(!isInteger(VardPavSk_str) || stoi(VardPavSk_str) <= 0) {
                        cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                        cin >> VardPavSk_str;
                    }
                    VardPavSk = stoi(VardPavSk_str);
                    skaitymas(stud, true, n, nd_sk, true, VardPavSk);
                }
            break;
            case 4:
                {
                exit(0);
                }
            break;
        }
    }while(true);
    skaitymas(stud, false, 0, 0, false, 0);
    skaičiavimai(stud);
    raidės(MaxPav, MaxVard, stud);
    išvestis(stud, MaxPav, MaxVard);
    return 0;
}

void skaitymas(vector<studentas> &stud, bool genPaz, int n, int nd_sk, bool genVardPav, int VardPavSk)
{
    // Jei generavimas neįjungtas, naudojame rankinį įvedimą
    if(!genPaz) {
        studentas temp;
        cout << "Įveskite kiek studentų duomenų norite įvesti: ";
        string n_str;
        cin >> n_str;
        while(!isInteger(n_str) || stoi(n_str) <= 0) {
            cout << "Klaidinga įvestis. Bandykite dar kartą: ";
            cin >> n_str;
        }
        n = stoi(n_str);
        for(int i = 0; i < n; i++) {
            cout << "Įveskite " << i + 1 << " studento vardą: ";
            cin >> temp.vardas;
            cout << "Įveskite " << i + 1 << " studento pavardę: ";
            cin >> temp.pavarde;
            int nd_count;
            cout << "Įveskite namų darbų skaičių: ";
            string nd_sk_str;
            cin >> nd_sk_str;
            while(!isInteger(nd_sk_str) || stoi(nd_sk_str) <= 0) {
                cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                cin >> nd_sk_str;
            }
            nd_count = stoi(nd_sk_str);
            temp.nd.resize(nd_count);

            for(int j = 0; j < nd_count; j++) {
                cout << "Įveskite " << j + 1 << " namų darbų įvertinimą: ";
                string nd_str;
                cin >> nd_str;
                while(!isInteger(nd_str) || stoi(nd_str) < 0) {
                    cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                    cin >> nd_str;
                }
                temp.nd[j] = stoi(nd_str);
            }
            cout << "Įveskite egzamino įvertinimą: ";
            string egz_str;
            cin >> egz_str;
            while(!isInteger(egz_str) || stoi(egz_str) < 0) {
                cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                cin >> egz_str;
            }
            temp.egz = stoi(egz_str);
            stud.push_back(temp);
        }
        return;
    }

    // Generavimo atvejis
    if (n <= 0 || nd_sk <= 0) return; // saugumas

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> gradeDist(1, 10);
    std::uniform_int_distribution<> letterDist(0, 25);
    int maxNameLen = std::max(3, VardPavSk);
    std::uniform_int_distribution<> nameLenDist(3, maxNameLen);

    vector<string> vardai;
    vector<string> pavardes;
    if (genVardPav) {
        vardai.reserve(VardPavSk);
        pavardes.reserve(VardPavSk);
        for (int i = 0; i < VardPavSk; ++i) {
            int lenV = nameLenDist(gen);
            string v; v.reserve(lenV);
            v.push_back(char('A' + letterDist(gen)));
            for (int k = 1; k < lenV; ++k) v.push_back(char('a' + letterDist(gen)));
            vardai.push_back(v);

            int lenP = nameLenDist(gen);
            string p; p.reserve(lenP);
            p.push_back(char('A' + letterDist(gen)));
            for (int k = 1; k < lenP; ++k) p.push_back(char('a' + letterDist(gen)));
            pavardes.push_back(p);
        }
    }

    stud.clear();
    stud.reserve(n);
    std::uniform_int_distribution<> poolIdx(0, std::max(0, VardPavSk - 1));

    for (int i = 0; i < n; ++i) {
        studentas temp;

        // Vardas / pavardė
        if (genVardPav) {
            int idx = poolIdx(gen);
            temp.vardas = vardai[idx];
            temp.pavarde = pavardes[idx];
        } else {
            cout << "Įveskite " << i + 1 << " studento vardą: ";
            cin >> temp.vardas;
            cout << "Įveskite " << i + 1 << " studento pavardę: ";
            cin >> temp.pavarde;
        }

        // Namų darbai
        temp.nd.resize(nd_sk);
        for (int j = 0; j < nd_sk; ++j) temp.nd[j] = gradeDist(gen);

        // Egzaminas
        temp.egz = gradeDist(gen);

        stud.push_back(std::move(temp));
    }
}

void skaičiavimai(vector<studentas> &stud)
{
    for(auto &s : stud) {
        double suma = 0;
        for(const auto &nd_ivar : s.nd) {
            suma += nd_ivar;
        }
        s.vidurkis = suma / s.nd.size();

        vector<int> nd_kopija = s.nd;
        sort(nd_kopija.begin(), nd_kopija.end());
        if(nd_kopija.size() % 2 == 0) {
            s.mediana = (nd_kopija[nd_kopija.size()/2 - 1] + nd_kopija[nd_kopija.size()/2]) / 2.0;
        } else {
            s.mediana = nd_kopija[nd_kopija.size()/2];
        }
    }
}

void išvestis(const vector<studentas> &stud, int &MaxPav, int &MaxVard)
{
    MaxVard = std::max(MaxVard, 12);
    MaxPav  = std::max(MaxPav, 12);

    cout << left << setw(MaxVard + 2) << "Vardas" << setw(MaxPav + 2) << "Pavardė"
            << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    cout << string(MaxVard + MaxPav + 44, '-') << "\n";
    for(const auto &s : stud) {
        cout << left << setw(MaxVard + 2) << s.vardas << setw(MaxPav + 2) << s.pavarde
                << setw(20) << std::fixed << std::setprecision(2) << (0.4 * s.vidurkis + 0.6 * s.egz)
                << setw(20) << std::fixed << std::setprecision(2) << (0.4 * s.mediana + 0.6 * s.egz) << "\n";
    }
}

void raidės(int &MaxPav, int &MaxVard, vector <studentas> &stud)
{
    MaxPav = 0;
    MaxVard = 0;
    for(const auto &s : stud) {
        if(s.pavarde.length() > MaxPav) {
            MaxPav = s.pavarde.length();
        }
        if(s.vardas.length() > MaxVard) {
            MaxVard = s.vardas.length();
        }
    }
    
}

bool isInteger(const string& s)
{
    if (s.empty()) return false;

    int start = (s[0] == '-' || s[0] == '+') ? 1 : 0; //praleidzia +/- ženklus

    for (int i = start; i < s.size(); i++)
        if (!isdigit(s[i]))
            return false;

    return (s.size() - start) > 0;
}
