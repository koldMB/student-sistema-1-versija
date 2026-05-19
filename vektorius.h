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

public:
    // Numatytasis konstruktorius
    mano_vektorius() : duomenys_(nullptr), dydis_(0), talpa_(0) {}

    // Konstruktorius su pradine talpa
    explicit mano_vektorius(size_t initial_capacity)
        : dydis_(0), talpa_(initial_capacity) {
        if (initial_capacity > 0) {
            duomenys_ = new T[initial_capacity];
        } else {
            duomenys_ = nullptr;
        }
    }

    // Konstruktorius su dydžiu ir numatytąja reikšme
    mano_vektorius(size_t size, const T& value)
        : dydis_(size), talpa_(size) {
        if (size > 0) {
            duomenys_ = new T[size];
            for (size_t i = 0; i < size; ++i) {
                duomenys_[i] = value;
            }
        } else {
            duomenys_ = nullptr;
        }
    }

    // Kopijuojantis konstruktorius
    mano_vektorius(const mano_vektorius& other)
        : dydis_(other.dydis_), talpa_(other.talpa_) {
        if (talpa_ > 0) {
            duomenys_ = new T[talpa_];
            for (size_t i = 0; i < dydis_; ++i) {
                duomenys_[i] = other.duomenys_[i];
            }
        } else {
            duomenys_ = nullptr;
        }
    }

    // Perkėlimo konstruktorius
    mano_vektorius(mano_vektorius&& other) noexcept
        : duomenys_(other.duomenys_), dydis_(other.dydis_), talpa_(other.talpa_) {
        other.duomenys_ = nullptr;
        other.dydis_ = 0;
        other.talpa_ = 0;
    }
    // Kopijavimo priskyrimo operatorius
    mano_vektorius& operator=(mano_vektorius other) noexcept {
        std::swap(duomenys_, other.duomenys_);
        std::swap(dydis_,    other.dydis_);
        std::swap(talpa_,    other.talpa_);
        return *this;
    }

};

#endif // VEKTORIUS_H