#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::setw;
using std::left;

struct studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
    double vidurkis;
    double mediana;
};

void skaitymas(vector<studentas> &stud);
void skaičiavimai(vector<studentas> &stud);
void išvestis(const vector<studentas> &stud, int &MaxPav, int &MaxVard);


int main() {
    studentas temp;
    vector<studentas> stud;
    skaitymas(stud);
    skaičiavimai(stud);
    int MaxPav = 0, MaxVard = 0;
    išvestis(stud, MaxPav, MaxVard);
    return 0;
}

void skaitymas(vector<studentas> &stud)
{
    studentas temp;
    cout << "Įveskite kiek studentų duomenų norite įvesti: ";
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cout << "Įveskite " << i + 1 << " studento vardą: ";
        cin >> temp.vardas;
        cout << "Įveskite " << i + 1 << " studento pavardę: ";
        cin >> temp.pavarde;
        int nd_sk;
        cout << "Įveskite namų darbų skaičių: ";
        cin >> nd_sk;
        temp.nd.resize(nd_sk);
        for(int j = 0; j < nd_sk; j++) {
            cout << "Įveskite " << j + 1 << " namų darbų įvertinimą: ";
            cin >> temp.nd[j];
        }
        cout << "Įveskite egzamino įvertinimą: ";
        cin >> temp.egz;
        stud.push_back(temp);
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