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
    std::cout << "veikia\n";
}

// Test 2: Kopijavimo Konstruktorius
void test_kopijavimo_konstruktorius() {
    std::cout << "Test 2: Kopijavimo Konstruktorius... ";
    Studentas original;
    original.setVardas("test1");
    original.setPavarde("test2");
    original.setEgzaminas(8.5);
    original.addNd(7.0);
    
    Studentas copy(original);
    assert(copy.vardas() == "test1");
    assert(copy.pavarde() == "test2");
    assert(copy.egzaminas() == 8.5);
    assert(copy.nd()[0] == 7.0);
    std::cout << "veikia\n";
}

// Test 3: Kopijavimo Priskyrimo Operatorius
void test_kopijavimo_priskyrimas() {
    std::cout << "Test 3: Kopijavimo Priskyrimo Operatorius... ";
    Studentas s1;
    s1.setVardas("test3");
    s1.setPavarde("test4");
    s1.addNd(6.5);
    
    Studentas s2;
    s2 = s1;
    assert(s2.vardas() == "test3");
    assert(s2.pavarde() == "test4");
    assert(s2.nd()[0] == 6.5);
    std::cout << "veikia\n";
}

// Test 4: Perkėlimo Konstruktorius
void test_perkėlimo_konstruktorius() {
    std::cout << "Test 4: Perkėlimo Konstruktorius... ";
    Studentas original;
    original.setVardas("test5");
    original.setPavarde("test6");
    original.setEgzaminas(7.5);
    original.addNd(8.0);
    original.addNd(7.5);
    original.addNd(8.5);
    original.setMediana(8.0);
    original.setVidurkis(8.0);

    // Store original values
    std::string orig_vardas = original.vardas();
    std::string orig_pavarde = original.pavarde();
    double orig_egz = original.egzaminas();
    size_t orig_nd_size = original.nd().size();
    double orig_mediana = original.mediana();
    double orig_vidurkis = original.vidurkis();

    Studentas moved(std::move(original));
    
    // Check moved object has all original data
    assert(moved.vardas() == orig_vardas);
    assert(moved.pavarde() == orig_pavarde);
    assert(moved.egzaminas() == orig_egz);
    assert(moved.nd().size() == orig_nd_size);
    assert(moved.mediana() == orig_mediana);
    assert(moved.vidurkis() == orig_vidurkis);
    assert(moved.nd()[0] == 8.0);
    
    // Check original object is empty/cleared
    assert(original.vardas() == "");
    assert(original.pavarde() == "");
    assert(original.nd().empty());
    
    // Add new data to moved object and verify recalculation
    moved.addNd(9.0);
    assert(moved.nd().size() == orig_nd_size + 1);
    assert(moved.nd().back() == 9.0);
    
    std::cout << "veikia\n";
}


// Test 5: Perkėlimo Priskyrimo Operatorius
void test_perkėlimo_priskyrimas() {
    std::cout << "Test 5: Perkėlimo Priskyrimo Operatorius... ";
    Studentas s1;
    s1.setVardas("test7");
    s1.setPavarde("test8");
    s1.setEgzaminas(8.5);
    s1.addNd(9.0);
    s1.addNd(8.5);
    s1.setMediana(8.75);
    s1.setVidurkis(8.75);
    
    // Store original values
    std::string s1_vardas = s1.vardas();
    std::string s1_pavarde = s1.pavarde();
    double s1_egz = s1.egzaminas();
    size_t s1_nd_size = s1.nd().size();
    double s1_mediana = s1.mediana();
    double s1_vidurkis = s1.vidurkis();
    
    Studentas s2;
    s2.setVardas("old7");
    s2.setPavarde("old8");
    s2.addNd(5.0);
    
    s2 = std::move(s1);
    
    // Check s2 has all original s1 data
    assert(s2.vardas() == s1_vardas);
    assert(s2.pavarde() == s1_pavarde);
    assert(s2.egzaminas() == s1_egz);
    assert(s2.nd().size() == s1_nd_size);
    assert(s2.mediana() == s1_mediana);
    assert(s2.vidurkis() == s1_vidurkis);
    assert(s2.nd()[0] == 9.0);
    
    // Check s1 is empty/cleared
    assert(s1.vardas() == "");
    assert(s1.pavarde() == "");
    assert(s1.nd().empty());
    
    // Add new data to s2 and verify
    s2.addNd(7.5);
    assert(s2.nd().size() == s1_nd_size + 1);
    assert(s2.nd().back() == 7.5);
    
    std::cout << "veikia\n";
}

// Test 6: Destruktorius
void test_destruktorius() {
    std::cout << "Test 6: Destruktorius... ";
    {
        Studentas s;
        s.setVardas("test9");
        s.addNd(7.5);
        s.addNd(8.0);
        // Destruktorius automatiškai iškviečiamas
    }
    std::cout << "veikia\n";
}

// Test 7: Setteriai ir Getteriai
void test_setteriai_getteriai() {
    std::cout << "Test 7: Setteriai ir Getteriai... ";
    Studentas s;
    
    s.setVardas("test10");
    assert(s.vardas() == "test10");
    
    s.setPavarde("test11");
    assert(s.pavarde() == "test11");
    
    s.setEgzaminas(7.5);
    assert(s.egzaminas() == 7.5);
    
    s.setMediana(7.0);
    assert(s.mediana() == 7.0);
    
    s.setVidurkis(7.25);
    assert(s.vidurkis() == 7.25);
    
    std::cout << "veikia\n";
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
    
    std::cout << "veikia\n";
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
    
    std::cout << "veikia\n";
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
