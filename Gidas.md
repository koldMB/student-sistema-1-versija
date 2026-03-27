# Studentų Sistema

## Reikalavimai

Jums reikės šių įrankių, įdiegtų jūsų sistemoje:

1. **CMake** (versija 3.20 arba naujesnė)
   - Atsisiųskite iš: https://cmake.org/download/

2. **C++ Kompiliatorius** (GCC/G++)
   - Rekomenduojame naudoti **MSYS2** su MinGW64
   - Atsisiųskite iš: https://www.msys2.org/
   - Sekite jų diegimo instrukcijas

## Patikrinkite Diegimą

Atidarykite **PowerShell** ir patikrinkite, ar įrankiai yra įdiegti:

```powershell
cmake --version
g++ --version
```

Jei gausite klaidų, įsitikinkite, kad įrankiai yra pridėti prie jūsų sistemos PATH aplinkos kintamojo.

## Projekto Kompiliavimas

### 1 Žingsnis: Navigiuokite į Projekto Aplankalą, pvz.

```powershell
cd "C:\Users\...\studentu-sistema"
```

### 2 Žingsnis: Sukurkite Kompiliavimo Aplankalą

```powershell
mkdir build -Force
cd build
```

### 3 Žingsnis: Konfigūruokite Projektą su CMake

```powershell
cmake .. -G "MinGW Makefiles"
```

### 4 Žingsnis: Kompiliuokite Projektą

```powershell
cmake --build .
```

**Tikėtina Išvestis:** Išplečiamasis failas `studentuSistema.exe` bus sukurtas `build` kataloge.

## Programos Paleidimas

### Parinktis 1: Paleiskite iš Kompiliavimo Katalogo

```powershell
.\studentuSistema.exe
```

### Parinktis 2: Paleiskite iš Projekto Šaknies

```powershell
cd ..
.\build\studentuSistema.exe
```


## Projekto Struktūra

### Pagrindiniai Failai
- **Main.cpp**: Pagrindinis programos failas, kuriame vykdomas vartotojo sąveikos valdymas. Čia yra meniu, leidžiantis vartotojui pasirinkti veiksmus, tokius kaip duomenų įvedimas, generavimas, skaitymas iš failo ir rezultatų išvedimas.
- **CMakeLists.txt**: Konfigūracijos failas, naudojamas projektui sukurti naudojant CMake.
- **README.md**: Šis failas, kuriame aprašoma projekto struktūra ir funkcionalumas.

### Header Failai
- **Common.h**: Apibrėžia bendras struktūras ir priklausomybes, tokias kaip `studentas` struktūra, naudojama keliuose failuose.
- **IsvestisIvestis.h**: Apibrėžia funkcijas, susijusias su duomenų įvedimu ir išvedimu.
- **Skaiciavimai.h**: Apibrėžia funkcijas, susijusias su skaičiavimais, tokiais kaip vidurkio ir medianos apskaičiavimas.
- **Laikas.h**: Apibrėžia laikmačio klasę, naudojamą funkcijų vykdymo laikui matuoti.

### Implementacijos Failai
- **IsvestisIvestis.cpp**: Įgyvendina funkcijas, susijusias su duomenų įvedimu ir išvedimu.
- **Skaiciavimai.cpp**: Įgyvendina funkcijas, susijusias su skaičiavimais ir rikiavimu.
- **Laikas.cpp**: Įgyvendina laikmačio funkcionalumą.

### Duomenų Failai
- **kursiokai.txt**: Pavyzdinis failas su studentų duomenimis.

### Kiti Failai
- **Laiko efektyvumo testai.md**: Dokumentas, kuriame pateikiami efektyvumo testų rezultatai.
- **LICENSE**: Projekto licencijos failas.

## Funkcijos

### Duomenų Įvedimas ir Išvedimas
- `skaitymas(vector<studentas> &stud)`: Leidžia vartotojui rankiniu būdu įvesti studentų duomenis.
- `FailoNuskaitymas(vector<studentas> &stud, const string& filename)`: Skaito studentų duomenis iš failo.
- `FailoIsvedimas(const vector<studentas> &stud, const string& filename, int &MaxPav, int &MaxVard)`: Išveda studentų duomenis į failą.
- `isvestis(const vector<studentas> &stud, int &MaxPav, int &MaxVard)`: Išveda studentų duomenis į terminalą.

### Skaičiavimai
- `skaiciavimai(vector<studentas> &stud)`: Apskaičiuoja kiekvieno studento vidurkį ir medianą.
- `rikiavimas(vector<studentas> &stud)`: Leidžia vartotojui pasirinkti rikiavimo kriterijų (pagal vardą, pavardę, vidurkį ar medianą).

### Laiko Matavimas
- `PradekLaikmati()`: Pradeda laikmačio matavimą.
- `BaigtiLaikmati(int pos)`: Baigia laikmačio matavimą ir išsaugo rezultatą.

### Klaidų Valdymas
- `AllExceptionsHandler::CatchAll(const std::function<void()>& func)`: Apgaubia funkciją ir apdoroja visas standartines išimtis su numatytomis žinutėmis.
- `AllExceptionsHandler::ThrowRuntimeError()`: Išmeta `runtime_error` išimtį su numatytąja žinute.

## Naudojimas
1. Paleiskite programą.
2. Pasirinkite veiksmą iš meniu:
    - Įvesti duomenis ranka.
    - Generuoti duomenis.
    - Skaityti duomenis iš failo.
    - Išvesti rezultatus į terminalą arba failą.
3. Sekite instrukcijas terminale.

## Licencija
Šis projektas yra licencijuotas pagal [LICENSE](LICENSE) failą.
