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

// Skaičiuoja UTF-8 simbolių skaičių (display width), ne baitų
size_t utf8_display_width(const string& str) {
    size_t width = 0;
    for (size_t i = 0; i < str.size(); ) {
        unsigned char c = str[i];
        if ((c & 0x80) == 0) {
            // ASCII simbolis (1 baitas)
            i += 1;
        } else if ((c & 0xE0) == 0xC0) {
            // 2 baitų UTF-8 simbolis
            i += 2;
        } else if ((c & 0xF0) == 0xE0) {
            // 3 baitų UTF-8 simbolis
            i += 3;
        } else if ((c & 0xF8) == 0xF0) {
            // 4 baitų UTF-8 simbolis
            i += 4;
        } else {
            i += 1; // Netikėtas baitas
        }
        width++;
    }
    return width;
}

// Papildo eilutę tarpais iki nurodyto pločio (pagal display width)
string pad_utf8(const string& str, size_t width) {
    size_t display_width = utf8_display_width(str);
    if (display_width >= width) {
        return str;
    }
    return str + string(width - display_width, ' ');
}

void skaitymas(vector<Studentas> &stud)
{
    Studentas temp;
    string laikinas;
    int n = 0;
    cout << "Jeigu norite baigti darba įveskite \\0" << "\n";
    while(true) {
        cout << "Įveskite " << n + 1 << " studento vardą: ";
        cin >> laikinas;
        if(laikinas == "\\0") return;
        temp.setVardas(laikinas);
        cout << "Įveskite " << n + 1 << " studento pavardę: ";
        cin >> laikinas;
        if(laikinas == "\\0") return;
        temp.setPavarde(laikinas);
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
        temp.resizeNd(nd_count);

        for(int j = 0; j < nd_count; j++) {
            cout << "Įveskite " << j + 1 << " namų darbų įvertinimą: ";
            string nd_str;
            cin >> nd_str;
            if(nd_str == "\\0") {
                temp.resizeNd(j); // sumažina vektoriaus dydį iki įvestų pažymių skaičiaus
                return;
            }
            auto nd_opt = AllExceptionsHandler::TryStoI(nd_str);
            while(!nd_opt.has_value() || nd_opt.value() < 0 || nd_opt.value() > 10) {
                cerr << "Klaidinga įvestis. Bandykite dar kartą: ";
                cin >> nd_str;
                if(nd_str == "\\0") return;
                nd_opt = AllExceptionsHandler::TryStoI(nd_str);
            }
            temp.ndRef()[j] = nd_opt.value();
        }
        cout << "Įveskite egzamino įvertinimą: ";
        string egz_str;
        cin >> egz_str;
        if(egz_str == "\\0") {
            temp.clearNd();
            return;
        }
        auto egz_opt = AllExceptionsHandler::TryStoI(egz_str);
        if (egz_opt.has_value()) {
            temp.setEgzaminas(egz_opt.value());
        }
        stud.push_back(temp);
        n++;
    }
}

void skaitymas(vector<Studentas> &stud, int &n, int nd_sk)
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
        Studentas temp;
        cout << "Įveskite " << i + 1 << " studento vardą: ";
        cin >> laikinas;
        if(laikinas == "\\0") break;
        temp.setVardas(laikinas);
        cout << "Įveskite " << i + 1 << " studento pavardę: ";
        cin >> laikinas;
        if(laikinas == "\\0") break;
        temp.setPavarde(laikinas);
        temp.resizeNd(nd_sk);
        for (int j = 0; j < nd_sk; ++j) {
            AllExceptionsHandler::TrySetAt(temp.ndRef(), j, static_cast<double>(dist(gen)));
        }
        temp.setEgzaminas(static_cast<double>(dist(gen)));
        stud.push_back(temp);
        i++;
    }
    n = static_cast<int>(stud.size());
}

void skaitymas(vector<Studentas> &stud, int &n, int nd_sk, int VardPavSk)
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
        Studentas temp;
        temp.setVardas(randomVardas(stud));
        temp.setPavarde(randomPavarde(stud));
        temp.resizeNd(nd_sk);
        for (int j = 0; j < nd_sk; ++j) AllExceptionsHandler::TrySetAt(temp.ndRef(), j, static_cast<double>(score_dist(gen)));
        temp.setEgzaminas(static_cast<double>(score_dist(gen)));
        stud.push_back(temp);
    }
}

void isvestis(const vector<Studentas> &stud, int &MaxPav, int &MaxVard)
{
    MaxVard = std::max(MaxVard, 12);
    MaxPav  = std::max(MaxPav, 12);

    std::ostringstream oss; // https://cplusplus.com/reference/sstream/ostringstream/

    oss << pad_utf8("Vardas", MaxVard + 2) << pad_utf8("Pavardė", MaxPav + 2)
            << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    oss << string(MaxVard + MaxPav + 44, '-') << "\n";
    for(auto &s : stud) {
        oss << pad_utf8(s.vardas(), MaxVard + 2) << pad_utf8(s.pavarde(), MaxPav + 2)
            << setw(20) << std::fixed << std::setprecision(2) << s.vidurkis()
            << setw(20) << std::fixed << std::setprecision(2) << s.mediana() << "\n";
    }
    cout << oss.str();
}


void FailoIsvedimas(const vector<Studentas> &stud, const string& filename, int &MaxPav, int &MaxVard) {
    std::ofstream f(filename + ".txt");
    if (!f.is_open()) {
        std::cerr << "Nepavyko atidaryti failo rašymui." << filename << "\n";
        return;
    }
    
    std::ostringstream oss; 
    oss << pad_utf8("Vardas", MaxVard + 2) << pad_utf8("Pavardė", MaxPav + 2)
        << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    oss << string(MaxVard + MaxPav + 44, '-') << "\n";
    for(const auto &s : stud) {
        oss << pad_utf8(s.vardas(), MaxVard + 2) << pad_utf8(s.pavarde(), MaxPav + 2)
            << setw(20) << std::fixed << std::setprecision(2) << s.vidurkis()
            << setw(20) << std::fixed << std::setprecision(2) << s.mediana() << "\n";
    }
    
    f << oss.str();
    f.close();
}

void TermArFailas(const vector<Studentas> &stud, int &MaxPav, int &MaxVard) {
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

void FailoNuskaitymas(vector<Studentas> &stud, const string& filename) {
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

            Studentas temp;
            auto vardas_opt = AllExceptionsHandler::TryAt(tokens, 0);
            auto pavarde_opt = AllExceptionsHandler::TryAt(tokens, 1);
            if (!vardas_opt.has_value() || !pavarde_opt.has_value()) continue;
            temp.setVardas(vardas_opt.value());
            temp.setPavarde(pavarde_opt.value());
            temp.resizeNd(nd_sk);

            // nuskaito namų darbų pažymius
            for (int i = 0; i < nd_sk; i++) {
                auto token_opt = AllExceptionsHandler::TryAt(tokens, 2 + i);
                if (!token_opt.has_value()) continue;
                auto nd_opt = AllExceptionsHandler::TryStoI(token_opt.value());
                if (nd_opt.has_value()) {
                    AllExceptionsHandler::TrySetAt(temp.ndRef(), i, static_cast<double>(nd_opt.value()));
                }
            }

            // nuskaito egzamino pažymį
            auto egz_token_opt = AllExceptionsHandler::TryAt(tokens, 2 + nd_sk);
            if (egz_token_opt.has_value()) {
                auto egz_opt = AllExceptionsHandler::TryStoI(egz_token_opt.value());
                if (egz_opt.has_value()) {
                    temp.setEgzaminas(static_cast<double>(egz_opt.value()));
                }
            }

            stud.push_back(temp);
        }
        f.close();
    });
}

void IsvestiGeriBlogiFailus(const vector<Studentas> &geri, const vector<Studentas> &blogi, int MaxPav, int MaxVard) {
    MaxVard = std::max(MaxVard, 12);
    MaxPav = std::max(MaxPav, 12);

    std::ofstream geri_failas("geru_studentu_sarasas.txt");
    std::ofstream blogi_failas("blogu_studentu_sarasas.txt");
    if (!geri_failas.is_open() || !blogi_failas.is_open()) {
        cerr << "Klaida atidarant failus rašymui." << endl;
        return;
    }
    // Geri studentai
    geri_failas << pad_utf8("Vardas", MaxVard + 2) << pad_utf8("Pavardė", MaxPav + 2)
        << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    geri_failas << string(MaxVard + MaxPav + 44, '-') << "\n";
    for (const auto& s : geri) {
        geri_failas << pad_utf8(s.vardas(), MaxVard + 2) << pad_utf8(s.pavarde(), MaxPav + 2)
            << setw(20) << std::fixed << std::setprecision(2) << s.vidurkis()
            << setw(20) << std::fixed << std::setprecision(2) << s.mediana() << "\n";
    }
    // Blogi studentai
    blogi_failas << pad_utf8("Vardas", MaxVard + 2) << pad_utf8("Pavardė", MaxPav + 2)
        << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    blogi_failas << string(MaxVard + MaxPav + 44, '-') << "\n";
    for (const auto& s : blogi) {
        blogi_failas << pad_utf8(s.vardas(), MaxVard + 2) << pad_utf8(s.pavarde(), MaxPav + 2)
            << setw(20) << std::fixed << std::setprecision(2) << s.vidurkis()
            << setw(20) << std::fixed << std::setprecision(2) << s.mediana() << "\n";
    }
    geri_failas.close();
    blogi_failas.close();
}

string randomVardas(vector<Studentas> &stud) {
    static const std::array<string, 67> vardai = {
        "Jonas", "Petras", "Andrius", "Tomas", "Matas",
        "Lukas", "Mantas", "Domas", "Karolis", "Rokas",
        "Paulius", "Justas", "Dovydas", "Martynas", "Edvinas",
        "Simonas", "Aurimas", "Deividas", "Rytis", "Giedrius",
        "Abdonas", "Abrahimas", "Abraomas", "Achilas", "Adalbertas", 
        "Adas", "Adauktas", "Adeodatas", "Adolfas", "Adolis", "Adomas",
        "Adonis", "Adrianas", "Adrijanas", "Adrijonas", "Adrijus", 
        "Agapitas", "Agatas", "Agatonas", "Agedas", "Agėjus", "Agilas",
        "Agnijus", "Agnius", "Aidanas", "Aidas", "Aidis", "Aidonas", 
        "Ainis", "Airidas", "Airingas", "Airis", "Airūnas", "Aistis", 
        "Aitvaras", "Aivaras", "Akselis", "Akvilas", "Akvilijus", "Akvilinas",
        "Alanas", "Alantas", "Albas", "Albertas", "Albertinas", "Albinas", 
        "Albrechtas"
    };
    std::random_device rd;
    std::array<unsigned int, 2> seed_data = {rd(), static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::seed_seq seed(seed_data.begin(), seed_data.end());
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution<> dist(0, vardai.size() - 1);
    return vardai[dist(gen)];
}

string randomPavarde(vector<Studentas> &stud) {
    static const std::array<string, 100> pavardes = {
    "Kazlauskas", "Stankevičius", "Petrauskas", "Jankauskas", "Žukauskas",
    "Butkus", "Balčiūnas", "Paulauskas", "Vasiliauskas", "Baranauskas", "Urbonas",
    "Navickas", "Ramanauskas", "Savickas", "Rimkus", "Žilinskas", "Šimkus",
    "Kavaliauskas", "Sakalauskas", "Ivanauskas", "Adomaitis", "Žemaitis", "Kairys",
    "Kaminskas", "Mikalauskas", "Petkevičius", "Bagdonas", "Petraitis",
    "Černauskas", "Vaitkevičius", "Mickevičius", "Urbanavičius", "Jurevičius",
    "Marcinkevičius", "Pocius", "Paškevičius", "Rutkauskas", "Mackevičius",
    "Juška", "Malinauskas", "Sinkevičius", "Radzevičius", "Sadauskas", "Kučinskas",
    "Mažeika", "Vitkauskas", "Vaitkus", "Dambrauskas", "Naujokas", "Sabaliauskas",
    "Mockus", "Bernotas", "Rakauskas", "Lukoševičius", "Norkus", "Butkevičius",
    "Barkauskas", "Lukošius", "Kubilius", "Barauskas", "Rinkevičius", "Jonaitis",
    "Krasauskas", "Vilkas", "Šukys", "Lukaševičius", "Markevičius", "Valaitis",
    "Mačiulis", "Aleksandravičius", "Venckus", "Grigaliūnas", "Juškevičius",
    "Baltrušaitis", "Morkūnas", "Tamošiūnas", "Adomavičius", "Stonkus", "Januškevičius",
    "Lapinskas", "Šidlauskas", "Stankus", "Banys", "Bartkus", "Povilaitis", "Misiūnas",
    "Rimkevičius", "Mickus", "Karpavičius", "Budrys", "Matulevičius", "Kazakevičius",
    "Gudaitis", "Račkauskas", "Steponavičius", "Noreika", "Brazauskas", "Grigas",
    "Vanagas", "Petravičius"
    };
    std::random_device rd;
    std::array<unsigned int, 2> seed_data = {rd(), static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::seed_seq seed(seed_data.begin(), seed_data.end());
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution<> dist(0, pavardes.size() - 1);
    return pavardes[dist(gen)];
}
void IsvestiBlogusGerusFailus(const vector<Studentas> &geri, const vector<Studentas> &blogi, const string& basename, int MaxPav, int MaxVard) {
    MaxVard = std::max(MaxVard, 12);
    MaxPav = std::max(MaxPav, 12);

    std::ofstream geri_failas(basename + "_geri.txt");
    std::ofstream blogi_failas(basename + "_blogi.txt");
    if (!geri_failas.is_open() || !blogi_failas.is_open()) {
        cerr << "Klaida atidarant failus rašymui." << endl;
        return;
    }
    // Geri studentai
    geri_failas << pad_utf8("Vardas", MaxVard + 2) << pad_utf8("Pavardė", MaxPav + 2)
        << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    geri_failas << string(MaxVard + MaxPav + 44, '-') << "\n";
    for (const auto& s : geri) {
        geri_failas << pad_utf8(s.vardas(), MaxVard + 2) << pad_utf8(s.pavarde(), MaxPav + 2)
            << setw(20) << std::fixed << std::setprecision(2) << s.vidurkis()
            << setw(20) << std::fixed << std::setprecision(2) << s.mediana() << "\n";
    }
    // Blogi studentai
    blogi_failas << pad_utf8("Vardas", MaxVard + 2) << pad_utf8("Pavardė", MaxPav + 2)
        << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    blogi_failas << string(MaxVard + MaxPav + 44, '-') << "\n";
    for (const auto& s : blogi) {
        blogi_failas << pad_utf8(s.vardas(), MaxVard + 2) << pad_utf8(s.pavarde(), MaxPav + 2)
            << setw(20) << std::fixed << std::setprecision(2) << s.vidurkis()
            << setw(20) << std::fixed << std::setprecision(2) << s.mediana() << "\n";
    }
    geri_failas.close();
    blogi_failas.close();
}

void GeneruotiStudentuFaila(const string& filename, int student_count, int nd_sk) {
    if (student_count <= 0 || nd_sk <= 0) {
        cerr << "Neteisingi parametrai failui generuoti.\n";
        return;
    }

    std::random_device rd;
    std::array<unsigned int, 2> seed_data = {rd(), static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::seed_seq seed(seed_data.begin(), seed_data.end());
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution<> score_dist(1, 10);

    std::ofstream failas(filename + ".txt");
    if (!failas.is_open()) {
        cerr << "Nepavyko atidaryti failo rašymui: " << filename << ".txt\n";
        return;
    }

    // Write header line
    failas << "Vardas Pavarde";
    for (int j = 0; j < nd_sk; ++j) {
        failas << " ND" << (j + 1);
    }
    failas << " Egzaminas\n";

    vector<Studentas> dummy; // Viena kart naudojamas konteineris randomVardas ir randomPavarde funkcijoms
    for (int i = 0; i < student_count; ++i) {
        string vardas = randomVardas(dummy);
        string pavarde = randomPavarde(dummy);
        
        failas << vardas << " " << pavarde << " ";
        
        // Generuoti namų darbų pažymius
        for (int j = 0; j < nd_sk; ++j) {
            failas << score_dist(gen) << " ";
        }
        
        // Generuoti egzamino pažymį
        failas << score_dist(gen) << "\n";
    }

    failas.close();
}