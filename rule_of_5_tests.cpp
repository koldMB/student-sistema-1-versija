#include <iostream>
#include "Common.h"
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
