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

    /*
    size_t nes CPU gali būti 32 ar 64 bitų
    
    size_t can store the maximum size of a theoretically possible object of any type (including array).

    size_t is commonly used for array indexing and loop counting. Programs that use other types, such as unsigned int, for array indexing may fail on, e.g. 64-bit systems when the index exceeds UINT_MAX or if it relies on 32-bit modular arithmetic. 
    https://en.cppreference.com/c/types/size_t
    */ 

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
    // Unified assignment operator (handles both copy and move through parameter passing)
    mano_vektorius& operator=(mano_vektorius other) noexcept {
        std::swap(duomenys_, other.duomenys_);
        std::swap(dydis_,    other.dydis_);
        std::swap(talpa_,    other.talpa_);
        return *this;
    }

    // Destruktorius
    ~mano_vektorius() {
        delete[] duomenys_;
    }

    // Elemento prieiga
    T& operator[](size_t index) {
        return duomenys_[index];
    }

    const T& operator[](size_t index) const {
        return duomenys_[index];
    }

    T& at(size_t index) {
        if (index >= dydis_) {
            throw std::out_of_range("mano_vektorius::at() indeksas yra ne šiose ribose");
        }
        return duomenys_[index];
    }

    const T& at(size_t index) const {
        if (index >= dydis_) {
            throw std::out_of_range("mano_vektorius::at() indeksas yra ne šiose ribose");
        }
        return duomenys_[index];
    }

    T& front() {
        if (dydis_ == 0) throw std::out_of_range("mano_vektorius::front() vektorius yra tuščias");
        return duomenys_[0];
    }

    const T& front() const {
        if (dydis_ == 0) throw std::out_of_range("mano_vektorius::front() vektorius yra tuščias");
        return duomenys_[0];
    }

    T& back() {
        if (dydis_ == 0) throw std::out_of_range("mano_vektorius::back() vektorius yra tuščias");
        return duomenys_[dydis_ - 1];
    }

    const T& back() const {
        if (dydis_ == 0) throw std::out_of_range("mano_vektorius::back() vektorius yra tuščias");
        return duomenys_[dydis_ - 1];
    }

    // Talpa
    size_t size() const {
        return dydis_;
    }

    size_t capacity() const {
        return talpa_;
    }

    bool empty() const {
        return dydis_ == 0;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > talpa_) {
            reallocate(new_capacity);
        }
    }

    void resize(size_t new_size) {
        if (new_size > talpa_) {
            size_t new_capacity = (talpa_ == 0) ? new_size : std::max(new_size, talpa_ * 2);
            reallocate(new_capacity);
        }

        // Initialize new elements if expanding
        if (new_size > dydis_) {
            for (size_t i = dydis_; i < new_size; ++i) {
                duomenys_[i] = T{};
            }
        }
        // Clear removed elements if shrinking
        else if (new_size < dydis_) {
            for (size_t i = new_size; i < dydis_; ++i) {
                duomenys_[i] = T{};
            }
        }

        dydis_ = new_size;
    }

    void resize(size_t new_size, const T& value) {
        if (new_size > talpa_) {
            size_t new_capacity = (talpa_ == 0) ? new_size : std::max(new_size, talpa_ * 2);
            reallocate(new_capacity);
        }

        // naikink kas neieina į naują dydį
        for (size_t i = new_size; i < dydis_; ++i) {
            duomenys_[i] = T{};
        }

        // Inicializuoti naujus elementus
        for (size_t i = dydis_; i < new_size; ++i) {
            duomenys_[i] = value;
        }

        dydis_ = new_size;
    }

    void clear() {
        // naikink visus elementus prieš nustatant nulinį dydį
        for (size_t i = 0; i < dydis_; ++i) {
            duomenys_[i] = T{};
        }
        dydis_ = 0;
    }

    // Modifikatoriai
    void push_back(const T& value) {
        if (dydis_ >= talpa_) {
            size_t new_capacity = (talpa_ == 0) ? 1 : talpa_ * 2;
            reallocate(new_capacity);
        }
        duomenys_[dydis_] = value;
        ++dydis_;
    }

    void push_back(T&& value) {
        if (dydis_ >= talpa_) {
            size_t new_capacity = (talpa_ == 0) ? 1 : talpa_ * 2;
            reallocate(new_capacity);
        }
        duomenys_[dydis_] = std::move(value);
        ++dydis_;
    }

    void pop_back() {
        if (dydis_ > 0) {
            --dydis_;
        }
    }

    // Sumažinti iki dydžio
    void shrink_to_fit() {
        if (dydis_ < talpa_) {
            if (dydis_ == 0) {
                delete[] duomenys_;
                duomenys_ = nullptr;
                talpa_ = 0;
            } else {
                T* new_data = new T[dydis_];
                for (size_t i = 0; i < dydis_; ++i) {
                    new_data[i] = std::move(duomenys_[i]);
                }
                delete[] duomenys_;
                duomenys_ = new_data;
                talpa_ = dydis_;
            }
        }
    }

    // Iteratoriaus palaikymas
    T* begin() {
        return duomenys_;
    }

    const T* begin() const {
        return duomenys_;
    }

    T* end() {
        return duomenys_ + dydis_;
    }

    const T* end() const {
        return duomenys_ + dydis_;
    }

    // Duomenų prieiga
    // https://en.cppreference.com/cpp/container/vector/data
    T* data() {
        return duomenys_;
    }

    const T* data() const {
        return duomenys_;
    }
};

#endif // VEKTORIUS_H