#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <list>


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
  
  // Konstruktorius su vardais
  Studentas(std::string v, std::string p) 
    : vardas_(std::move(v)), pavarde_(std::move(p)), egzaminas_(0), mediana_(0.0), vidurkis_(0.0) { }
  
  // Konstruktorius su visais duomenimis
  Studentas(std::string v, std::string p, double egz, double med, double vid, std::vector<double> n)
    : vardas_(std::move(v)), pavarde_(std::move(p)), egzaminas_(egz), mediana_(med), vidurkis_(vid), nd_(std::move(n)) { }
  
  // Kopijavimo konstruktorius
  Studentas(const Studentas& kitasSTD) 
  {
    vardas_ = kitasSTD.vardas_;
    pavarde_ = kitasSTD.pavarde_;
    egzaminas_ = kitasSTD.egzaminas_;
    mediana_ = kitasSTD.mediana_;
    vidurkis_ = kitasSTD.vidurkis_;
    nd_ = kitasSTD.nd_;
  }
  
  // Kopijavimo priskyrimo operatorius
  Studentas& operator=(const Studentas& kitasSTD) {
    if (this != &kitasSTD) {
      vardas_ = kitasSTD.vardas_;
      pavarde_ = kitasSTD.pavarde_;
      egzaminas_ = kitasSTD.egzaminas_;
      mediana_ = kitasSTD.mediana_;
      vidurkis_ = kitasSTD.vidurkis_;
      nd_ = kitasSTD.nd_;
    }
    return *this;
  }
  
  // Perkelimo konstruktorius
  Studentas(Studentas&& kitasSTD) noexcept
    : vardas_(std::move(kitasSTD.vardas_)), pavarde_(std::move(kitasSTD.pavarde_)), 
      egzaminas_(kitasSTD.egzaminas_), mediana_(kitasSTD.mediana_), 
      vidurkis_(kitasSTD.vidurkis_), nd_(std::move(kitasSTD.nd_)) { }
  
  // Perkelimo priskyrimo operatorius
  Studentas& operator=(Studentas&& kitasSTD) noexcept {
    if (this != &kitasSTD) {
      vardas_ = std::move(kitasSTD.vardas_);
      pavarde_ = std::move(kitasSTD.pavarde_);
      egzaminas_ = kitasSTD.egzaminas_;
      mediana_ = kitasSTD.mediana_;
      vidurkis_ = kitasSTD.vidurkis_;
      nd_ = std::move(kitasSTD.nd_);
    }
    return *this;
  }
  
  // Getters
  inline std::string vardas() const { return vardas_; }
  inline std::string pavarde() const { return pavarde_; }
  inline double egzaminas() const { return egzaminas_; }
  inline double mediana() const { return mediana_; }
  inline double vidurkis() const { return vidurkis_; }
  inline const std::vector<double>& nd() const { return nd_; }
  double galBalas(double (*) (const vector<double>&) = nullptr) const;
  
  // Setters
  inline void setVardas(std::string v) { vardas_ = std::move(v); }
  inline void setPavarde(std::string p) { pavarde_ = std::move(p); }
  inline void setEgzaminas(double e) { egzaminas_ = e; }
  inline void setMediana(double m) { mediana_ = m; }
  inline void setVidurkis(double v) { vidurkis_ = v; }
  inline void setNd(std::vector<double> n) { nd_ = std::move(n); }
  inline std::vector<double>& ndRef() { return nd_; }
  
  // addNd vienam pažymiui
  inline void addNd(double pazymys) { nd_.push_back(pazymys); }
  
  // addNd keliems pažymiams
  inline void addNd(const std::vector<double>& pazymiai) { 
    for(double g : pazymiai) nd_.push_back(g); 
  }
  
  inline void clearNd() { nd_.clear(); }
  inline void resizeNd(size_t size) { nd_.resize(size); }
  inline void setNdAt(size_t idx, double pazymys) { if(idx < nd_.size()) nd_[idx] = pazymys; }
  
  // Overloaded setters - set name (vardas and pavarde kartu)
  inline void setVardaPavarde(std::string v, std::string p) { 
    vardas_ = std::move(v); 
    pavarde_ = std::move(p); 
  }
  
  // Overloaded setters pazymiams
  inline void setRez(double egz, double med, double vid) {
    egzaminas_ = egz;
    mediana_ = med;
    vidurkis_ = vid;
  }
  
  std::istream& readStudent(std::istream&);
  //TODO: operator >> ir <<
  friend std::istream& operator>>(std::istream& in, Studentas& s);
  friend std::ostream& operator<<(std::ostream& out, const Studentas& s);

  ~Studentas() {
    vardas_.clear();
    pavarde_.clear();
    egzaminas_ = 0;
    mediana_ = 0;
    vidurkis_ = 0;
    nd_.clear();
  }
};
//TODO: Žmogaus base klasė su vardu ir pavarde (v1.5)
void atrinkimas(const vector<Studentas> &stud, vector<Studentas> &atrinkti, vector<Studentas> &neatrinkti);
void atrinkimasAutomatiskas(const vector<Studentas> &stud, vector<Studentas> &geri, vector<Studentas> &blogi);
void Bandymas1_FailuGeneravimas(int sizes[5]);
void Bandymas2_DuomenuApdorojimas(int sizes[5], int pas);

#endif // COMMON_H