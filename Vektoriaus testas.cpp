#include <vector>
#include <iostream>
#include "vektorius.h"
#include "Laikas.h"

using namespace std;

Laikas laikas;

int main()
{
    int sz = 1000000;
    
    // Test mano_vektorius performance
    laikas.PradekLaikmati();
    mano_vektorius<int> v1(sz);
    for (int i = 0; i < sz; ++i)
    {
        v1[i] = i;
    }
    laikas.BaigtiLaikmati();
    
    // 
    laikas.PradekLaikmati();
    vector<int> v2(sz);
    for (int i = 0; i < sz; ++i)
    {
        v2[i] = i;
    }
    laikas.BaigtiLaikmati();
    
    laikas.Isvesk();
    return 0;
}