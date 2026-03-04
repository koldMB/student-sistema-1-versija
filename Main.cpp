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

#include "Laikas.h" // Laiko klasė skirta naudoti efektyvumo testams
#include "Common.h"// keliouose failuose naudojamos priklausomybės
#include "IsvestisIvestis.h" // Isvesties ir ivesties tvarkymo funkcijos
#include "Skaiciavimai.h" // visos operacijos susijusios su skaiciavimais
#include "klaiduValdymas.h" // Include for AllExceptionsHandler

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


int main() {
    // Keičiam console į UTF-8 kad galėtų teisingai rodyti lietuviškus simbolius ir juos skaityti
    try{
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    }
    catch(const std::exception& e) {
        std::cerr << "Klaida keičiant console į UTF-8: " << e.what() << std::endl;
        return -2;
    }

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
        try {
            if (!isInteger(pasirinkimas_str) || stoi(pasirinkimas_str) < 1 || stoi(pasirinkimas_str) > 5) {
                AllExceptionsHandler::ThrowRuntimeError();
            }
        } catch (const std::runtime_error& e) {
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
                    try {
                        if (!isInteger(nd_sk_str) || stoi(nd_sk_str) <= 0) {
                            AllExceptionsHandler::ThrowRuntimeError();
                        }
                    } catch (const std::runtime_error& e) {
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
                    try {
                        if (!isInteger(n_str) || stoi(n_str) <= 0) {
                            AllExceptionsHandler::ThrowRuntimeError();
                        }
                    } catch (const std::runtime_error& e) {
                        cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                        cin >> n_str;
                    }
                    n = stoi(n_str);
                    cout << "Įveskite kiek namų darbų pažymių norite generuoti: ";
                    string nd_sk_str;
                    cin >> nd_sk_str;
                    try {
                        if (!isInteger(nd_sk_str) || stoi(nd_sk_str) <= 0) {
                            AllExceptionsHandler::ThrowRuntimeError();
                        }
                    } catch (const std::runtime_error& e) {
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


