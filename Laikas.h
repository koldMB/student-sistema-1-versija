#ifndef LAIKAS_H
#define LAIKAS_H

#include <chrono>
#include <vector>

extern std::vector<double> LaikoVektorius;

class Laikas
{
public:
    void PradekLaikmati();
    void BaigtiLaikmati();
    void Reset();
    void Isvesk();

private:
    std::chrono::high_resolution_clock::time_point start;
};

#endif