#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <list>
#include <deque>
#include <iostream>


using std::string;
using std::vector;
bool isInteger(const string& s);

class Studentas {
// realizacija
private:
  std::string vardas_;
  std::string pavarde_;
  double egzaminas_;
  double mediana_;
  double vidurkis_;
  std::vector<double> nd_;
// interfeisas
public:
  Studentas() : egzaminas_(0), mediana_(0.0), vidurkis_(0.0) { }  // default konstruktorius
  Studentas(std::istream& is);
  
  // Getters
  inline std::string vardas() const { return vardas_; }
  inline std::string pavarde() const { return pavarde_; }
  inline double egzaminas() const { return egzaminas_; }
  inline double mediana() const { return mediana_; }
  inline double vidurkis() const { return vidurkis_; }
  inline const std::vector<double>& nd() const { return nd_; }
  double galBalas(double (*) (const vector<double>&) = nullptr) const;
  
  // Setters
  inline void setVardas(const std::string& v) { vardas_ = v; }
  inline void setPavarde(const std::string& p) { pavarde_ = p; }
  inline void setEgzaminas(double e) { egzaminas_ = e; }
  inline void setMediana(double m) { mediana_ = m; }
  inline void setVidurkis(double v) { vidurkis_ = v; }
  inline void setNd(const std::vector<double>& n) { nd_ = n; }
  inline std::vector<double>& ndRef() { return nd_; }
  inline void addNd(double grade) { nd_.push_back(grade); }
  inline void clearNd() { nd_.clear(); }
  inline void resizeNd(size_t size) { nd_.resize(size); }
  inline void setNdAt(size_t idx, double grade) { if(idx < nd_.size()) nd_[idx] = grade;
  }
  
  std::istream& readStudent(std::istream&);

  ~Studentas() {
    vardas_.clear();
    pavarde_.clear();
    egzaminas_ = 0;
    mediana_ = 0;
    vidurkis_ = 0;
    nd_.clear();
  }
};

void atrinkimas(const vector<Studentas> &stud, vector<Studentas> &atrinkti, vector<Studentas> &neatrinkti);
void atrinkimasAutomatiskas(const vector<Studentas> &stud, vector<Studentas> &geri, vector<Studentas> &blogi);
void Bandymas1_FailuGeneravimas(int sizes[5]);
void Bandymas2_DuomenuApdorojimas(int sizes[5], int pas);

void atrinkimas(const vector<Studentas> &stud, vector<Studentas> &atrinkti, vector<Studentas> &neatrinkti);

void atrinkimasAutomatiskas(const vector<Studentas> &stud, vector<Studentas> &geri, vector<Studentas> &blogi);

#endif // COMMON_H