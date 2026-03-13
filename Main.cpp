#ifndef NOMINMAX
#define NOMINMAX // kertasi su min ir max funkcijomis, todėl ignoruojama iš windows.h šiuos
#endif

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

#include <windows.h>

#include "Common.h"// keliouose failuose naudojamos priklausomybės
#include "IsvestisIvestis.h" // Isvesties ir ivesties tvarkymo funkcijos
#include "Skaiciavimai.h" // visos operacijos susijusios su skaiciavimais
#include "klaiduValdymas.h" // Include for AllExceptionsHandler
#include "Laikas.h"

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::setw;
using std::sort;
using std::isdigit; //tikrina ar char yra skaitmuo
using std::stoi; //string to int
using std::left;
using std::cerr;
using std::endl;
using std::flush;


int main() {
    // Užtikrina, kad cout ir cerr būtų sinchronizuoti
    std::ios_base::sync_with_stdio(true);
    std::cerr.tie(&std::cout);
    
    // Keičiam console į UTF-8 kad galėtų teisingai rodyti lietuviškus simbolius ir juos skaityti
    try{
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    }
    catch(const std::exception& e) {
        cerr << "Klaida keičiant console į UTF-8: " << e.what() << std::endl;
        return -2;
    }

    int MaxPav = 0, MaxVard = 0;
    vector<studentas> stud;
    int pasirinkimas;
    do{
        cout << "1. Įvesti duomenis ranka\n"; 
        cout << "2. Generuoti pažymius\n";
        cout << "3. Generuoti vardus ir pavardes bei pažymius\n";
        cout << "4. Nuskaityti iš failo\n";
        cout << "5. Testavimas - failu kurimas ir ju apdorojimas (abudu atskirai)\n";
        cout << "6. Darbo pabaiga\n";
        cout << "Pasirinkite veiksmą: ";
        string pasirinkimas_str;
        cin >> pasirinkimas_str;
        auto pasirinkimas_opt = AllExceptionsHandler::TryStoI(pasirinkimas_str);
        while (!pasirinkimas_opt.has_value() || pasirinkimas_opt.value() < 1 || pasirinkimas_opt.value() > 6) {
            cerr << "Klaidinga įvestis. Bandykite dar kartą: " << flush;
            cin >> pasirinkimas_str;
            pasirinkimas_opt = AllExceptionsHandler::TryStoI(pasirinkimas_str);
        }
        pasirinkimas = pasirinkimas_opt.value();
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
                    auto nd_sk_opt = AllExceptionsHandler::TryStoI(nd_sk_str);
                    while (!nd_sk_opt.has_value() || nd_sk_opt.value() <= 0) {
                        cerr << "Klaidinga įvestis. Bandykite dar kartą: " << flush;
                        cin >> nd_sk_str;
                        nd_sk_opt = AllExceptionsHandler::TryStoI(nd_sk_str);
                    }
                    nd_sk = nd_sk_opt.value();
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
                    cout << "Įveskite kiek studentų duomenų norite generuoti: " << flush;
                    string n_str;
                    cin >> n_str;
                    auto n_opt = AllExceptionsHandler::TryStoI(n_str);
                    while (!n_opt.has_value() || n_opt.value() <= 0) {
                        cerr << "Klaidinga įvestis. Bandykite dar kartą: " << flush;
                        cin >> n_str;
                        n_opt = AllExceptionsHandler::TryStoI(n_str);
                    }
                    n = n_opt.value();
                    cout << "Įveskite kiek namų darbų pažymių norite generuoti: ";
                    string nd_sk_str;
                    cin >> nd_sk_str;
                    auto nd_sk_opt = AllExceptionsHandler::TryStoI(nd_sk_str);
                    while (!nd_sk_opt.has_value() || nd_sk_opt.value() <= 0) {
                        cerr << "Klaidinga įvestis. Bandykite dar kartą: " << flush;
                        cin >> nd_sk_str;
                        nd_sk_opt = AllExceptionsHandler::TryStoI(nd_sk_str);
                    }
                    nd_sk = nd_sk_opt.value();
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
                    cout << "Įveskite txt failo pavadinimą: " << flush;
                    cin >> filename;
                    FailoNuskaitymas(stud, filename);
                    if(stud.empty()) {
                        cerr << "Nėra duomenų išvesti.\n";
                        break;
                    }
                    skaiciavimai(stud);
                    raides(MaxPav, MaxVard, stud);
                    rikiavimas(stud);
                    TermArFailas(stud, MaxPav, MaxVard);
                    stud.clear();
                }
            break;
            case 5: {
                int pas;
                cout << "Įveskite pagal ką rikiuoti\n1 - vidurkis\n2 - mediana\n";
                string pas_str;
                cin >> pas_str;
                auto pas_opt = AllExceptionsHandler::TryStoI(pas_str);
                while (!pas_opt.has_value() || pas_opt.value() < 1 || pas_opt.value() > 2) {
                    cerr << "Neteisingas pasirinkimas, įveskite dar kartą: " << flush;
                    cin >> pas_str;
                    pas_opt = AllExceptionsHandler::TryStoI(pas_str);
                }
                pas = pas_opt.value();
                int sizes[5] = {1000, 10000, 100000, 1000000, 10000000};
                for(int i = 0; i < 5; i++) {
                    cout << i+1 << " testas\n\n";
                    //Bandymas1_FailuGeneravimas(sizes);
                    Bandymas2_DuomenuApdorojimas(sizes, pas);
                    cout << endl << endl;
                    }
                }
            break;
            case 6:
                {
                exit(0);
                }
            break;
        }
    }while(true);

    return 0;
}


