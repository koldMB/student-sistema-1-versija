#ifndef VEKTORIUS_H
#define VEKTORIUS_H

#include <stdexcept>
#include <algorithm>
#include <utility>


template <typename T>
class mano_vektorius {
private:
    T* duomenys_;
    size_t dydis_; // Faktinis elementų skaičius vektoriuje
    size_t talpa_; // Iš viso paskirstyta atmintis (kiek elementų gali tilpti)

    // Pagalbinė funkcija atminčiai iš naujo paskirstyti pakitus vektoriaus dydžiui
    void reallocate(size_t nauja_talpa) {
        if (nauja_talpa < dydis_) return;

        T* new_data = new T[nauja_talpa];

        for (size_t i = 0; i < dydis_; ++i) {
            new_data[i] = std::move(duomenys_[i]);
        }

        delete[] duomenys_;
        duomenys_ = new_data;
        talpa_ = nauja_talpa;
    }
};

#endif // VEKTORIUS_H