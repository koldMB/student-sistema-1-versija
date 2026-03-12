#include "Laikas.h"
#include <chrono>
#include <vector>
#include <iostream>

std::vector<double> LaikoVektorius;

void Laikas::PradekLaikmati() {
    start = std::chrono::high_resolution_clock::now();
}

void Laikas::BaigtiLaikmati() {
    auto end = std::chrono::high_resolution_clock::now();
    double duration = static_cast<double>(
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    );

    LaikoVektorius.push_back(duration);
}

void Laikas::Reset() {
    LaikoVektorius.clear();
}

void Laikas::Isvesk() {
    for (int i = 0; i < LaikoVektorius.size(); i++) {
        std::cout << LaikoVektorius.at(i) << "\t";
    }
    std::cout << std::endl;
    Laikas::Reset();
}