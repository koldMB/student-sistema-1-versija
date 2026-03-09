#include "Laikas.h"
#include <chrono>

double LaikasA[] = {0, 0, 0}; //parametrai laikams saugoti 0 - skaitymas, 1 - Rikiavimas pagal vidurkį, 2 - išvestis

void Laikas::PradekLaikmati() {
    start = std::chrono::high_resolution_clock::now();
}

void Laikas::BaigtiLaikmati(int pos) {
    auto end = std::chrono::high_resolution_clock::now();
    double duration = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    LaikasA[pos] += duration;
}