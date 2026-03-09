#include <string>
#include "klaiduValdymas.h"
#include "Common.h"

using std::string;
using std::vector;
using std::cout;

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