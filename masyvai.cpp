//implimentacija su masyvais

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>

using std::cout;
using std::cin;
using std::string;
using std::setw;
using std::sort;
using std::isdigit;
using std::stoi;
using std::left;

struct studentas {
    string vardas;
    string pavarde;
    int *nd = nullptr;
    int nd_sk = 0;
    int egz;
    double vidurkis;
    double mediana;
};

void skaitymas(studentas* &stud, int &n);
void skaičiavimai(studentas* stud, int n);
void išvestis(const studentas* stud, int n, int MaxPav, int MaxVard);
void raidės(int &MaxPav, int &MaxVard, studentas* stud, int n);
bool isInteger(const string& s);

int main() {
    studentas* stud = nullptr;
    int n = 0;
    int MaxPav = 0, MaxVard = 0;

    skaitymas(stud, n);
    skaičiavimai(stud, n);
    raidės(MaxPav, MaxVard, stud, n);
    išvestis(stud, n, MaxPav, MaxVard);

    for (int i = 0; i < n; ++i) {
        delete[] stud[i].nd;
    }
    delete[] stud;

    return 0;
}

void skaitymas(studentas* &stud, int &n)
{
    cout << "Įveskite kiek studentų duomenų norite įvesti: ";
    string n_str;
    cin >> n_str;
    while(!isInteger(n_str) || stoi(n_str) <= 0) {
        cout << "Klaidinga įvestis. Bandykite dar kartą: ";
        cin >> n_str;
    }
    n = stoi(n_str);

    stud = new studentas[n];

    for(int i = 0; i < n; i++) {
        cout << "Įveskite " << i + 1 << " studento vardą: ";
        cin >> stud[i].vardas;
        cout << "Įveskite " << i + 1 << " studento pavardę: ";
        cin >> stud[i].pavarde;

        cout << "Įveskite namų darbų skaičių: ";
        string nd_sk_str;
        cin >> nd_sk_str;
        while(!isInteger(nd_sk_str) || stoi(nd_sk_str) <= 0) {
            cout << "Klaidinga įvestis. Bandykite dar kartą: ";
            cin >> nd_sk_str;
        }
        stud[i].nd_sk = stoi(nd_sk_str);
        stud[i].nd = new int[stud[i].nd_sk];

        for(int j = 0; j < stud[i].nd_sk; j++) {
            cout << "Įveskite " << j + 1 << " namų darbų įvertinimą: ";
            string nd_str;
            cin >> nd_str;
            while(!isInteger(nd_str) || stoi(nd_str) < 0) {
                cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                cin >> nd_str;
            }
            stud[i].nd[j] = stoi(nd_str);
        }

        cout << "Įveskite egzamino įvertinimą: ";
        string egz_str;
        cin >> egz_str;
        while(!isInteger(egz_str) || stoi(egz_str) < 0) {
            cout << "Klaidinga įvestis. Bandykite dar kartą: ";
            cin >> egz_str;
        }
        stud[i].egz = stoi(egz_str);
    }
}

void skaičiavimai(studentas* stud, int n)
{
    for(int i = 0; i < n; ++i) {
        studentas &s = stud[i];
        double suma = 0;
        for(int j = 0; j < s.nd_sk; ++j) {
            suma += s.nd[j];
        }
        s.vidurkis = (s.nd_sk > 0) ? suma / s.nd_sk : 0;


        int *nd_kopija = new int[s.nd_sk];
        for(int j = 0; j < s.nd_sk; ++j) nd_kopija[j] = s.nd[j];
        sort(nd_kopija, nd_kopija + s.nd_sk);
        if (s.nd_sk > 0) {
            if (s.nd_sk % 2 == 0) {
                s.mediana = (nd_kopija[s.nd_sk/2 - 1] + nd_kopija[s.nd_sk/2]) / 2.0;
            } else {
                s.mediana = nd_kopija[s.nd_sk/2];
            }
        } else {
            s.mediana = 0;
        }
        delete[] nd_kopija;
    }
}

void išvestis(const studentas* stud, int n, int MaxPav, int MaxVard)
{
    MaxVard = std::max(MaxVard, 12);
    MaxPav  = std::max(MaxPav, 12);

    cout << left << setw(MaxVard + 2) << "Vardas" << setw(MaxPav + 2) << "Pavardė"
            << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    cout << string(MaxVard + MaxPav + 44, '-') << "\n";
    for(int i = 0; i < n; ++i) {
        const studentas &s = stud[i];
        cout << left << setw(MaxVard + 2) << s.vardas << setw(MaxPav + 2) << s.pavarde
                << setw(20) << std::fixed << std::setprecision(2) << (0.4 * s.vidurkis + 0.6 * s.egz)
                << setw(20) << std::fixed << std::setprecision(2) << (0.4 * s.mediana + 0.6 * s.egz) << "\n";
    }
}

void raidės(int &MaxPav, int &MaxVard, studentas* stud, int n)
{
    MaxPav = 0;
    MaxVard = 0;
    for(int i = 0; i < n; ++i) {
        const studentas &s = stud[i];
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

    int start = (s[0] == '-' || s[0] == '+') ? 1 : 0;

    for (int i = start; i < s.size(); i++)
        if (!isdigit(s[i]))
            return false;

    return start < s.size();
}

