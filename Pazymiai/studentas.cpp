//
// Created by Adomas on 15/04/2024.
//
#include "studentas.h"
#include <fstream>

void studentasV::setVardas(std::string vardas) {
    this -> vardas = vardas;
}
std::string studentasV::getVardas() const{
    return vardas;
}
void studentasV::setPavarde(std::string pavarde) {
    this -> pavarde = pavarde;
}
std::string studentasV::getPavarde() const{
    return pavarde;
}
void studentasV::setPazymiaiVector(const std::vector<int>& pazVector) {
    for (auto& elem : pazVector) {
        pazymiai.push_back(elem);
    }
}
void studentasV::setPazymiai(int paz){
    pazymiai.push_back(paz);
}
void studentasV::resizePazymiai(int n) {
    pazymiai.resize(n);
}
std::vector<int> studentasV::getPazymiai() const {
    return pazymiai;
}

void studentasV::setEgzaminas(int egzaminas) {
    this -> egzaminas = egzaminas;
}
int studentasV::getEgzaminas() const{
    return egzaminas;
}
void studentasV::setVidurkis(){
    if (pazymiai.empty()) {
        vidurkis = egzaminas * 0.6;
    } else {
        double suma = std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0);
        vidurkis = (suma / pazymiai.size()) * 0.4 + egzaminas * 0.6;
    }
}
void studentasV::setMediana() {
    std::sort(pazymiai.begin(), pazymiai.end());

    size_t size = pazymiai.size();
    if (size == 0) {
        mediana = -1;
    } else if (size % 2 == 0) {
        mediana = (pazymiai[size / 2 - 1] + pazymiai[size / 2]) / 2.0 * 0.4 + egzaminas * 0.6;
    } else {
        mediana = (pazymiai[size / 2]) * 0.4 + egzaminas * 0.6;
    }
}
float studentasV::getVidurkis() const{
    return vidurkis;
}
float studentasV::getMediana() const{
    return mediana;
}

void studentasV::setAtsitiktiniaiPazymiai() {
    pazymiai.resize(rand() % 10 + 1);
    for (int & paz : pazymiai) {
        paz = rand() % 10 + 1;
    }
    egzaminas = rand() % 10 + 1;
}
void studentasV::setAtsitiktiniaiDuomenys() {
    setAtsitiktiniaiPazymiai(); // Assuming this function sets pazymiai

    const std::vector<std::string> vardai = { "Bronius", "Juozas", "Rimas", "Tomas", "Matas", "Markas", "Ignas", "Kristupas", "Joris", "Arnas" };
    const std::vector<std::string> pavardes = { "Broniauskas", "Juozevicius", "Rimauskas", "Tomavicius", "Matkevicius", "Markevicius", "Igniauskas", "Kristevicius", "Jorevicius", "Arniavicius" };

    int vardasIndex = rand() % vardai.size();
    int pavardeIndex = rand() % pavardes.size();

    this->vardas = vardai[vardasIndex];
    this->pavarde = pavardes[pavardeIndex];
}
//Kopijavimo konstruktorius
studentasV::studentasV(const studentasV& kita)
        : Zmogus(kita), pazymiai(kita.pazymiai), egzaminas(kita.egzaminas) {
    vardas = kita.vardas;
    pavarde = kita.pavarde;
    vidurkis = kita.vidurkis;
    mediana = kita.mediana;
}
////Priskyrimo konstruktorius
studentasV& studentasV::operator=(const studentasV &kita) {
    if (this != &kita) {
        vardas = kita.vardas;
        pavarde = kita.pavarde;
        vidurkis = kita.vidurkis;
        mediana = kita.mediana;
        pazymiai = kita.pazymiai;
        egzaminas = kita.egzaminas;
    }
    return *this;
}
////Perkelimo konstruktorius
studentasV::studentasV(studentasV&& kita) noexcept :
        Zmogus(),
        pazymiai(std::move(kita.pazymiai)),
        egzaminas(kita.egzaminas) {
        vardas = std::move(kita.vardas);
        pavarde = std::move(kita.pavarde);
        vidurkis = kita.vidurkis;
        mediana = kita.mediana;

        kita.vidurkis = 0.0;
        kita.mediana = 0.0;
        kita.egzaminas = 0.0;
}
//// Perkelimo priskyrimo operatorius
studentasV& studentasV::operator=(studentasV&& kita) noexcept {
    if (this != &kita) {
        pazymiai = kita.pazymiai;
        egzaminas = kita.egzaminas;
        setVardas(kita.vardas);
        setPavarde(kita.pavarde);
        vidurkis = kita.vidurkis;
        mediana = kita.mediana;

        kita.vardas.clear();
        kita.pavarde.clear();
        kita.pazymiai.clear();
        kita.vidurkis = 0.0;
        kita.mediana = 0.0;
        kita.egzaminas = 0.0;
    }
    return *this;
}
//Destruktorius
studentasV::~studentasV(){
    pazymiai.clear();
}
//output streamo operatorius <<
std::ostream& operator<<(std::ostream& outputas, const studentasV &studentas) {
    outputas << studentas.vardas << " " << studentas.pavarde << " " << studentas.egzaminas << " ";
    for (int pazymys : studentas.pazymiai) {
        outputas << pazymys << " ";
    }
    return outputas;
}
//input streamo operatorius >>
std::istream &operator>>(std::istream &inputas, studentasV &studentas){
    inputas >> studentas.vardas >> studentas.pavarde >> studentas.egzaminas;
    studentas.pazymiai.clear();
    int pazymys;
    while (inputas >> pazymys) {
        studentas.pazymiai.push_back(pazymys);
    }
    return inputas;
}
