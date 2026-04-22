#include <iostream>
#include "Common.h"
#include <windows.h>
#include <assert.h>
#include <exception>
#include <sstream>

// Test 1: Numatytasis Konstruktorius
void test_numatytasis_konstruktorius() {
    std::cout << "Test 1: Numatytasis Konstruktorius... ";
    Studentas s;
    assert(s.vardas() == "");
    assert(s.egzaminas() == 0);
    assert(s.nd().empty());
    std::cout << "PASSED\n";
}

// Test 2: Kopijavimo Konstruktorius
void test_kopijavimo_konstruktorius() {
    std::cout << "Test 2: Kopijavimo Konstruktorius... ";
    Studentas original;
    original.setVardas("Jonas");
    original.setPavarde("Jonaitis");
    original.setEgzaminas(8.5);
    original.addNd(7.0);
    
    Studentas copy(original);
    assert(copy.vardas() == "Jonas");
    assert(copy.pavarde() == "Jonaitis");
    assert(copy.egzaminas() == 8.5);
    assert(copy.nd()[0] == 7.0);
    std::cout << "PASSED\n";
}

// Test 3: Kopijavimo Priskyrimo Operatorius
void test_kopijavimo_priskyrimas() {
    std::cout << "Test 3: Kopijavimo Priskyrimo Operatorius... ";
    Studentas s1;
    s1.setVardas("Petras");
    s1.setPavarde("Petraitis");
    s1.addNd(6.5);
    
    Studentas s2;
    s2 = s1;
    assert(s2.vardas() == "Petras");
    assert(s2.pavarde() == "Petraitis");
    assert(s2.nd()[0] == 6.5);
    std::cout << "PASSED\n";
}

// Test 4: Perkėlimo Konstruktorius
void test_perkėlimo_konstruktorius() {
    std::cout << "Test 4: Perkėlimo Konstruktorius... ";
    Studentas original;
    original.setVardas("Marija");
    original.setPavarde("Motina");
    original.addNd(8.0);
    
    Studentas moved(std::move(original));
    assert(moved.vardas() == "Marija");
    assert(moved.pavarde() == "Motina");
    assert(moved.nd()[0] == 8.0);
    std::cout << "PASSED\n";
}

// Test 5: Perkėlimo Priskyrimo Operatorius
void test_perkėlimo_priskyrimas() {
    std::cout << "Test 5: Perkėlimo Priskyrimo Operatorius... ";
    Studentas s1;
    s1.setVardas("Laima");
    s1.setPavarde("Laimaite");
    s1.addNd(9.0);
    
    Studentas s2;
    s2 = std::move(s1);
    assert(s2.vardas() == "Laima");
    assert(s2.pavarde() == "Laimaite");
    assert(s2.nd()[0] == 9.0);
    std::cout << "PASSED\n";
}

// Test 6: Destruktorius
void test_destruktorius() {
    std::cout << "Test 6: Destruktorius... ";
    {
        Studentas s;
        s.setVardas("Darius");
        s.addNd(7.5);
        s.addNd(8.0);
        // Destruktorius automatiškai iškviečiamas
    }
    std::cout << "PASSED\n";
}

// Test 7: Setteriai ir Getteriai
void test_setteriai_getteriai() {
    std::cout << "Test 7: Setteriai ir Getteriai... ";
    Studentas s;
    
    s.setVardas("Vytautas");
    assert(s.vardas() == "Vytautas");
    
    s.setPavarde("Vytautaitis");
    assert(s.pavarde() == "Vytautaitis");
    
    s.setEgzaminas(7.5);
    assert(s.egzaminas() == 7.5);
    
    s.setMediana(7.0);
    assert(s.mediana() == 7.0);
    
    s.setVidurkis(7.25);
    assert(s.vidurkis() == 7.25);
    
    std::cout << "PASSED\n";
}

// Test 8: ND Operacijos (addNd, clearNd, resizeNd, setNdAt)
void test_nd_operacijos() {
    std::cout << "Test 8: ND Operacijos (addNd, clearNd, resizeNd, setNdAt)... ";
    Studentas s;
    
    s.addNd(5.0);
    s.addNd(6.0);
    s.addNd(7.0);
    assert(s.nd().size() == 3);
    assert(s.nd()[0] == 5.0);
    
    s.setNdAt(1, 8.5);
    assert(s.nd()[1] == 8.5);
    
    s.resizeNd(5);
    assert(s.nd().size() == 5);
    
    s.clearNd();
    assert(s.nd().empty());
    
    std::cout << "PASSED\n";
}

// Test 9: setNd ir ndRef
void test_setnd_ndref() {
    std::cout << "Test 9: setNd ir ndRef... ";
    Studentas s;
    
    std::vector<double> paz = {6.0, 7.0, 8.0, 9.0};
    s.setNd(paz);
    assert(s.nd().size() == 4);
    assert(s.nd()[3] == 9.0);
    
    s.ndRef().push_back(10.0);
    assert(s.nd().size() == 5);
    assert(s.nd()[4] == 10.0);
    
    std::cout << "PASSED\n";
}


int main() {

    try{
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    }
    catch(const std::exception& e) {
        std::cerr << "Klaida keičiant console į UTF-8: " << e.what() << std::endl;
        return -2;
    }
    std::cout << "\nPenkių taisyklės ir metodų testai\n\n";
    
    test_numatytasis_konstruktorius();
    test_kopijavimo_konstruktorius();
    test_kopijavimo_priskyrimas();
    test_perkėlimo_konstruktorius();
    test_perkėlimo_priskyrimas();
    test_destruktorius();
    test_setteriai_getteriai();
    test_nd_operacijos();
    test_setnd_ndref();
    
    std::cout << "\nVisi testai praeiti\n\n";
    return 0;
}
