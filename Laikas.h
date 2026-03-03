#ifndef LAIKAS_H
#define LAIKAS_H

#include <chrono>

extern double LaikasA[]; 

class Laikas // laikmačio klasė, naudojama matuoti funkcijų vykdymo laiką
{
public:
    void PradekLaikmati();
    void BaiktiLaikmati(int pos);

private:
    std::chrono::high_resolution_clock::time_point start;
};

#endif