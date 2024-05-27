#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>
#include <utility>
#include <vector>
#include <numeric>
#include "studentas.h"
#include "vectorClass.h"
using namespace std;

/**
 * @brief Studentu duomenu ivedimas zinant studentu skaiciu
 * @param grupeVector studentu obejektu vektorius
 * @param n studentu kiekis
 */
void ivedimas(vector<studentasV>& grupeVector, int n);

/**
 * @brief Studentu duomenu ivedimas zinant studentu skaiciu
 * @param grupeVector studentu obejektu vektorius
 * @param n studentu kiekis
 * @param pazymiuKiekis pazymiu kiekis
 */
void ivedimasV(vector<studentasV>& grupeVector, studentasV& stud, int studentoNr, int pazymiuKiekis);
/**
 * @brief Studentu duomenu ivedimas nezinant studentu skaiciaus
 * @param grupeVector studentu obejektu vektorius
 */
void ivedimasNoSize(vector<studentasV>& grupeVector);

/**
 * @brief Ivestam studentui generuojami atsitiktiniai pazymiai
 * @param grupeVector studentu obejektu vektorius
 */
void ivedimasCaseTwo(vector<studentasV>& grupeVector);

/**
 * @brief studentu duomenu nuskaitymas is failo, kiekvieno studento vidurkio ir medianos apskaiciavimas
 * @param grupeVector studentu obejektu vektorius
 * @param failas failo pavadinimas
 * @param laikasSkaitymas duomenu nuskaitymo is failo trukme
 * @param fakePazymiai - netinkamu pazymiu skaicius
 * @param laikasSkaiciavimas - skaiciavimo trukme
 */
void fileReading(vector<studentasV>& grupeVector, const string& failas, double & laikasSkaitymas, int& fakePazymiai, double& laikasSkaiciavimas);

/**
 * @brief studentui sugeneruojami atsitiktiniai pazymiai
 * @param stud studentas
 */
void generateRandomGrades(studentasV &stud);

/**
 * @brief studento objektui sugeneruojamas vardas ir pavarde
 * @param stud
 */
void generateRandomNames(studentasV &stud);

/**
 * @brief visiems grupeVector studento objektams apskaiciuojamas vidurkis
 * @param grupeVector studentu obejektu vektorius
 */
void generalVidurkisCalculate(vector<studentasV>& grupeVector);

/**
 * @brief visiems grupeVector studento objektams apskaiciuojama mediana
 * @param grupeVector
 */
void generalMedianaCalculate(vector<studentasV>& grupeVector);

/**
 *
 * @param grupeVector studentu obejektu vektorius
 * @param laikasSkaitymas duomenu nuskaitymo is failo trukme
 * @param laikasSkaiciavimas duomenu apskaiciavimo trukme
 * @param laikasRusiavimas studentu rusiavimo pagal pasirinkta kriteriju trukme
 * @param fakePazymiai netinkamu pazymiu skaicius
 * @param iteracija iteracija parodo, su kuriais failais dirba programa
 */
void isvedimas(vector<studentasV> grupeVector, double laikasSkaitymas, double laikasSkaiciavimas, double laikasRusiavimas, int fakePazymiai, int iteracija);

/**
 * @brief rankiniu budu ivedamu studentu pazymiu ivedimo ir ju patikimumo tikrinimo funkcija
 * @param stud studento objektas
 * @param maxItems nurodo, kiek pazymiu programa tikisi
 */
void readNumbersV(studentasV& stud, int maxItems);

/**
 * @brief studentu objektu vektoriaus rusiavimas pagal pasirinkta kriteriju
 * @param choice pasirinikimas, pagal koki kriteriju norima rusiuoti studentu objektu vektoriu
 * @param grupeVector studentu obejektu vektorius
 */
void sortInput(string& choice, vector<studentasV>& grupeVector);

/**
 * @brief funkcija apjungianti duomenu nuskaityma ir duomenu rusiavima
 * @param grupeVector studentu objektu vektorius
 * @param grupeBad bloguju studentu objektu vektorius
 * @param grupeGood geruju studentu objektu vektorius
 * @param i iteracija
 * @param vidMed vidurkio mediano pasirinkimo kintamasis
 * @param ivedimasKonteineris konteinerio pasirinkimo kintamasis
 * @param choice sortInput pasirinkimo kintamasis
 */
void failoNuskaitymasRusiavimas(vector<studentasV>& grupeVector, vector<studentasV>& grupeBad, vector<studentasV>& grupeGood, int i, string vidMed, string ivedimasKonteineris, string choice);

/**
 * @brief funkcija kuri isveda studentu objektu duomenis i faila
 * @param grupeVector studentu objektu vektorius
 * @param grupeBad universalus kintamasis (arva grupeBad arba grupeGood)
 * @param i iteracija
 * @param vidMed vidurkio mediano pasirinkimo kintamasis
 * @param choice sortInput pasirinkimo kintamasis
 */
void isvedimasFailai(vector<studentasV>& grupeVector, vector<studentasV>& grupeBad, int i, string& vidMed, string& choice);

/**
 * @brief funkcija skirta pasirinkti vidurki arba mediana
 * @param vidMed
 */
void pasirinkimasVidMed(string& vidMed);

/**
 * @brief main funkcija, kuri apjungia visas kitas funkcijas
 * @param vidMed vidurkio mediano pasirinkimo kintamasis
 * @param choice sortInput pasirinkimo kintamasis
 * @param grupeVector studentu objektu vektorius
 * @param grupeBad blogu studentu objektu vektorius
 * @param grupeGood geru studentu objektu vektorius
 * @param ivedimasKonteineris  ar noresite rusiuoti duomenis i du naujus konteinerius ar rusiuoti i sena ir viena nauja konteineri
 */
void vektoriaiMain(string vidMed, string choice, vector<studentasV>& grupeVector, vector<studentasV>& grupeBad, vector<studentasV>& grupeGood, string ivedimasKonteineris);

/**
 * @brief funkcija, kuri panaudodama partition isrusiuoja grupeVector i du naujus konteinerius
 * @param vidMed vidurkio mediano pasirinkimo kintamasis
 * @param grupeVector studentu objektu vektorius
 * @param grupeGood geru studentu objektu vektorius
 * @param grupeBad blogu studentu objektu vektorius
 */
void vectorPartition(string vidMed, vector<studentasV>& grupeVector, vector<studentasV>& grupeGood, vector<studentasV>& grupeBad);

/**
 * @brief funkcija, kuri panaudodama partition isrusiuoja grupeVector i viena nauja ir viena sena konteineri
 * @param vidMed vidurkio mediano pasirinkimo kintamasis
 * @param grupeVector studentu objektu vektorius
 * @param grupeBad blogu studentu objektu vektorius
 */
void vectorPartition2(string vidMed, vector<studentasV>& grupeVector, vector<studentasV>& grupeBad);