#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
    double vidurkis;
    double mediana;
};

void skaitymas(vector<studentas> &stud);


int main() {
    studentas temp;
    vector<studentas> stud;
    skaitymas(stud);
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
