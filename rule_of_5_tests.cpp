#include <iostream>
#include "Common.h"
#include "vektorius.h"
#include <windows.h>
#include <gtest/gtest.h>
#include <exception>
#include <sstream>

// Test 1: Numatytasis Konstruktorius
TEST(StudentasTest, NumatytasisKonstruktorius) {
    Studentas s;
    EXPECT_EQ(s.vardas(), "");
    EXPECT_EQ(s.egzaminas(), 0);
    EXPECT_TRUE(s.nd().empty());
}

// Test 2: Kopijavimo Konstruktorius
TEST(StudentasTest, KopijantimoKonstruktorius) {
    Studentas original;
    original.setVardas("test1");
    original.setPavarde("test2");
    original.setEgzaminas(8.5);
    original.addNd(7.0);
    
    Studentas copy(original);
    EXPECT_EQ(copy.vardas(), "test1");
    EXPECT_EQ(copy.pavarde(), "test2");
    EXPECT_EQ(copy.egzaminas(), 8.5);
    EXPECT_EQ(copy.nd()[0], 7.0);
}

// Test 3: Kopijavimo Priskyrimo Operatorius
TEST(StudentasTest, KopijantimoPeriskyrimo) {
    Studentas s1;
    s1.setVardas("test3");
    s1.setPavarde("test4");
    s1.addNd(6.5);
    
    Studentas s2;
    s2 = s1;
    EXPECT_EQ(s2.vardas(), "test3");
    EXPECT_EQ(s2.pavarde(), "test4");
    EXPECT_EQ(s2.nd()[0], 6.5);
}

// Test 4: Perkėlimo Konstruktorius
TEST(StudentasTest, PerkėlimoKonstruktorius) {
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
    EXPECT_EQ(moved.vardas(), orig_vardas);
    EXPECT_EQ(moved.pavarde(), orig_pavarde);
    EXPECT_EQ(moved.egzaminas(), orig_egz);
    EXPECT_EQ(moved.nd().size(), orig_nd_size);
    EXPECT_EQ(moved.mediana(), orig_mediana);
    EXPECT_EQ(moved.vidurkis(), orig_vidurkis);
    EXPECT_EQ(moved.nd()[0], 8.0);
    
    // Check original object is empty/cleared
    EXPECT_EQ(original.vardas(), "");
    EXPECT_EQ(original.pavarde(), "");
    EXPECT_TRUE(original.nd().empty());
    
    // Add new data to moved object and verify recalculation
    moved.addNd(9.0);
    EXPECT_EQ(moved.nd().size(), orig_nd_size + 1);
    EXPECT_EQ(moved.nd().back(), 9.0);
}


// Test 5: Perkėlimo Priskyrimo Operatorius
TEST(StudentasTest, PerkelimoPerskyrimas) {
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
    EXPECT_EQ(s2.vardas(), s1_vardas);
    EXPECT_EQ(s2.pavarde(), s1_pavarde);
    EXPECT_EQ(s2.egzaminas(), s1_egz);
    EXPECT_EQ(s2.nd().size(), s1_nd_size);
    EXPECT_EQ(s2.mediana(), s1_mediana);
    EXPECT_EQ(s2.vidurkis(), s1_vidurkis);
    EXPECT_EQ(s2.nd()[0], 9.0);
    
    // Check s1 is empty/cleared
    EXPECT_EQ(s1.vardas(), "");
    EXPECT_EQ(s1.pavarde(), "");
    EXPECT_TRUE(s1.nd().empty());
    
    // Add new data to s2 and verify
    s2.addNd(7.5);
    EXPECT_EQ(s2.nd().size(), s1_nd_size + 1);
    EXPECT_EQ(s2.nd().back(), 7.5);
}

// Test 6: Destruktorius
TEST(StudentasTest, Destruktorius) {
    {
        Studentas s;
        s.setVardas("test9");
        s.addNd(7.5);
        s.addNd(8.0);
        // Destruktorius automatiškai iškviečiamas
    }
}

// Test 7: Setteriai ir Getteriai
TEST(StudentasTest, SetteriaIGetteriai) {
    Studentas s;
    
    s.setVardas("test10");
    EXPECT_EQ(s.vardas(), "test10");
    
    s.setPavarde("test11");
    EXPECT_EQ(s.pavarde(), "test11");
    
    s.setEgzaminas(7.5);
    EXPECT_EQ(s.egzaminas(), 7.5);
    
    s.setMediana(7.0);
    EXPECT_EQ(s.mediana(), 7.0);
    
    s.setVidurkis(7.25);
    EXPECT_EQ(s.vidurkis(), 7.25);
}

// Test 8: ND Operacijos (addNd, clearNd, resizeNd, setNdAt)
TEST(StudentasTest, NDOperacijos) {
    Studentas s;
    
    s.addNd(5.0);
    s.addNd(6.0);
    s.addNd(7.0);
    EXPECT_EQ(s.nd().size(), 3);
    EXPECT_EQ(s.nd()[0], 5.0);
    
    s.setNdAt(1, 8.5);
    EXPECT_EQ(s.nd()[1], 8.5);
    
    s.resizeNd(5);
    EXPECT_EQ(s.nd().size(), 5);
    
    s.clearNd();
    EXPECT_TRUE(s.nd().empty());
}

// Test 9: setNd ir ndRef
TEST(StudentasTest, SetndNdref) {
    Studentas s;
    
    std::vector<double> paz = {6.0, 7.0, 8.0, 9.0};
    s.setNd(paz);
    EXPECT_EQ(s.nd().size(), 4);
    EXPECT_EQ(s.nd()[3], 9.0);
    
    s.ndRef().push_back(10.0);
    EXPECT_EQ(s.nd().size(), 5);
    EXPECT_EQ(s.nd()[4], 10.0);
}
// ============================================
// MANO_VEKTORIUS TESTAI
// ============================================

// Test 1: Default Constructor
TEST(ManoVektoriusTest, DefaultKonstruktorius) {
    mano_vektorius<int> v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

// Test 2: Constructor with initial capacity
TEST(ManoVektoriusTest, KonstruktoriusSuTalpa) {
    mano_vektorius<int> v(10);
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 10);
}

// Test 3: Constructor with size and value
TEST(ManoVektoriusTest, KonstruktoriusSuDydžiuIrReikšme) {
    mano_vektorius<int> v(5, 42);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 5);
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(v[i], 42);
    }
}

// Test 4: operator[] access
TEST(ManoVektoriusTest, OperatorSquareBrackets) {
    mano_vektorius<int> v(3, 10);
    v[0] = 100;
    v[1] = 200;
    v[2] = 300;
    EXPECT_EQ(v[0], 100);
    EXPECT_EQ(v[1], 200);
    EXPECT_EQ(v[2], 300);
}

// Test 5: at() method - valid access
TEST(ManoVektoriusTest, AtMethodValidAccess) {
    mano_vektorius<double> v(3, 1.5);
    EXPECT_EQ(v.at(0), 1.5);
    EXPECT_EQ(v.at(1), 1.5);
    EXPECT_EQ(v.at(2), 1.5);
}

// Test 6: at() method - out of bounds
TEST(ManoVektoriusTest, AtMethodOutOfBounds) {
    mano_vektorius<int> v(3, 5);
    EXPECT_THROW(v.at(3), std::out_of_range);
    EXPECT_THROW(v.at(100), std::out_of_range);
}

// Test 7: front() and back() - valid
TEST(ManoVektoriusTest, FrontBackValid) {
    mano_vektorius<int> v(5, 0);
    v[0] = 10;
    v[4] = 50;
    EXPECT_EQ(v.front(), 10);
    EXPECT_EQ(v.back(), 50);
}

// Test 8: front() and back() - empty vector
TEST(ManoVektoriusTest, FrontBackEmpty) {
    mano_vektorius<int> v;
    EXPECT_THROW(v.front(), std::out_of_range);
    EXPECT_THROW(v.back(), std::out_of_range);
}

// Test 9: reserve() expands capacity
TEST(ManoVektoriusTest, ReserveExpandCapacity) {
    mano_vektorius<int> v(5, 1);
    EXPECT_EQ(v.capacity(), 5);
    v.reserve(20);
    EXPECT_EQ(v.capacity(), 20);
    EXPECT_EQ(v.size(), 5);  // Size should not change
}

// Test 10: reserve() does not shrink
TEST(ManoVektoriusTest, ReserveDoesNotShrink) {
    mano_vektorius<int> v(20, 1);
    v.reserve(10);
    EXPECT_EQ(v.capacity(), 20);  // Should remain at 20
}

// Test 11: resize() increases size with default value
TEST(ManoVektoriusTest, ResizeIncreaseWithDefault) {
    mano_vektorius<int> v(3, 5);
    v.resize(7);
    EXPECT_EQ(v.size(), 7);
    EXPECT_EQ(v[0], 5);
    EXPECT_EQ(v[3], 0);  // New elements should be default-initialized
}

// Test 12: resize() increases size with custom value
TEST(ManoVektoriusTest, ResizeIncreaseWithCustomValue) {
    mano_vektorius<int> v(2, 10);
    v.resize(5, 99);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[2], 99);
    EXPECT_EQ(v[4], 99);
}

// Test 13: resize() decreases size
TEST(ManoVektoriusTest, ResizeDecrease) {
    mano_vektorius<int> v(5, 20);
    v.resize(2);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 20);
    EXPECT_EQ(v[1], 20);
}

// Test 14: Copy Constructor
TEST(ManoVektoriusTest, KopijuojantisKonstruktorius) {
    mano_vektorius<int> original(4, 42);
    original[0] = 100;
    original[3] = 400;
    
    mano_vektorius<int> copy(original);
    EXPECT_EQ(copy.size(), 4);
    EXPECT_EQ(copy.capacity(), 4);
    EXPECT_EQ(copy[0], 100);
    EXPECT_EQ(copy[3], 400);
    
    // Modifying copy should not affect original
    copy[0] = 999;
    EXPECT_EQ(original[0], 100);
}

// Test 15: Move Constructor
TEST(ManoVektoriusTest, PerkėlimoKonstruktorius) {
    mano_vektorius<int> original(5, 10);
    original[0] = 50;
    original[4] = 90;
    
    mano_vektorius<int> moved(std::move(original));
    EXPECT_EQ(moved.size(), 5);
    EXPECT_EQ(moved[0], 50);
    EXPECT_EQ(moved[4], 90);
    
    // Original should be empty
    EXPECT_TRUE(original.empty());
    EXPECT_EQ(original.capacity(), 0);
}

// Test 16: Copy Assignment Operator
TEST(ManoVektoriusTest, KopijuojantisPriskyrimas) {
    mano_vektorius<int> v1(3, 5);
    v1[0] = 100;
    
    mano_vektorius<int> v2(2, 10);
    v2 = v1;
    
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2[0], 100);
    
    // Modifying v2 should not affect v1
    v2[0] = 999;
    EXPECT_EQ(v1[0], 100);
}

// Test 17: Move Assignment Operator (uses unified assignment operator)
TEST(ManoVektoriusTest, PerkelimosPriskyrimas) {
    mano_vektorius<int> v1(4, 20);
    v1[0] = 77;
    v1[3] = 88;
    
    mano_vektorius<int> v2(2, 5);
    v2 = std::move(v1);
    
    EXPECT_EQ(v2.size(), 4);
    EXPECT_EQ(v2[0], 77);
    EXPECT_EQ(v2[3], 88);
    
    // v1 should be empty after move assignment (via the move constructor in parameter)
    EXPECT_TRUE(v1.empty());
    EXPECT_EQ(v1.capacity(), 0);
}

// Test 18: self assignment handling
TEST(ManoVektoriusTest, SelfAssignment) {
    mano_vektorius<int> v(3, 42);
    v = v;  // Self assignment
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 42);
}

// Test 19: Multiple operations in sequence
TEST(ManoVektoriusTest, MultipleOperations) {
    mano_vektorius<int> v;
    v.reserve(10);
    v.resize(5, 3);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 10);
    
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(v[i], 3);
    }
}

// Test 20: Vector of doubles
TEST(ManoVektoriusTest, VectorOfDoubles) {
    mano_vektorius<double> v(3, 3.14);
    EXPECT_DOUBLE_EQ(v[0], 3.14);
    EXPECT_DOUBLE_EQ(v.front(), 3.14);
    EXPECT_DOUBLE_EQ(v.back(), 3.14);
}

// Test 21: Vector of strings
TEST(ManoVektoriusTest, VectorOfStrings) {
    mano_vektorius<std::string> v(2, "hello");
    EXPECT_EQ(v[0], "hello");
    EXPECT_EQ(v[1], "hello");
    
    v[0] = "world";
    EXPECT_EQ(v.front(), "world");
}

// Test 22: Move semantics with complex types
TEST(ManoVektoriusTest, MoveSemanticsComplexTypes) {
    mano_vektorius<std::string> v1(2, "test");
    v1[0] = "hello";
    v1[1] = "world";
    
    mano_vektorius<std::string> v2(std::move(v1));
    EXPECT_EQ(v2[0], "hello");
    EXPECT_EQ(v2[1], "world");
    EXPECT_TRUE(v1.empty());
}

// Test 23: Resize with capacity doubling
TEST(ManoVektoriusTest, ResizeWithCapacityDoubling) {
    mano_vektorius<int> v(2, 5);
    EXPECT_EQ(v.capacity(), 2);
    
    v.resize(5, 10);
    EXPECT_EQ(v.size(), 5);
    EXPECT_GE(v.capacity(), 5);  // Capacity should be at least 5, likely doubled
}

// Test 24: Empty vector access to at()
TEST(ManoVektoriusTest, EmptyVectorAtAccess) {
    mano_vektorius<int> v;
    EXPECT_THROW(v.at(0), std::out_of_range);
}

// Test 25: Destructor test (no memory leaks in scope)
TEST(ManoVektoriusTest, DestructorTest) {
    {
        mano_vektorius<int> v(100, 42);
        v.resize(200, 99);
        // Destructor should be called automatically
    }
    // If we reach here without crash, destructor worked
    EXPECT_TRUE(true);
}
int main(int argc, char** argv) {
    try{
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    }
    catch(const std::exception& e) {
        std::cerr << "Klaida keičiant console į UTF-8: " << e.what() << std::endl;
        return -2;
    }
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
