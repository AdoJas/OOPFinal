//
// Created by Adomas on 15/04/2024.
//

#ifndef OOPUZD_STUDENTAS_H
#define OOPUZD_STUDENTAS_H

#include <iostream>
#include <string>
#include <vector>
#include "numeric"
#include <algorithm>
#include "vectorClass.h"
/**
 * @brief Base klasė Zmogus kuria zmogaus objektus - vardas, pavarde
 *
 * Ši klasė yra abstrakti, t.y. apibrezia abstrakcius metodus, kurie turi buti perkrauti paveldetose klasese
 */
class Zmogus {
public:

    /**
     * @brief Objektui priskiria varda.
     *
     * @param vardas Nustatomas vardas.
     */
    virtual void setVardas(std::string vardas) = 0;

    /**
     * @brief Grazina objekto varda.
     *
     * @return vardas Grazinamas objekto vardas.
     */
    virtual std::string getVardas() const = 0;

    /**
     * @brief Objektui priskiria pavarde.
     *
     * @param pavarde Nustatoma pavarde.
     */
    virtual void setPavarde(std::string pavarde) = 0;

    /**
     * @brief Grazina objekto pavarde.
     *
     * @return pavarde Grazinama pavarde.
     */
    virtual std::string getPavarde() const = 0;

    /**
     * @brief Virtualus objekto destruktorius.
     */
    virtual ~Zmogus() = default;
};

class studentasV : public Zmogus {
private:
    std::string vardas = " "; /**>Studento vardas.*/
    std::string pavarde = " ";/**>Studento pavarde.*/
    float vidurkis = 0.0;/**>Studento pazymiu vidurkis.*/
    float mediana = 0.0;/**>Studento pazymiu mediana.*/
    std::vector<int> pazymiai;/**>Studento pazymiai.*/
    double egzaminas{};/**>Studento egzamino ivertinimas.*/
public:

    /**
    * @brief Default studento objekto konstruktorius.
    */
    studentasV() : egzaminas(0.0) {}

    /**
     * @brief Ovveride'inta Zmogus klases funkcija setVardas - nustato studento varda.
     *
     * @param vardas
     */
    void setVardas(std::string vardas) override;

    /**
     * @brief Ovveride'inta Zmogus klases funkcija getVardas - grazina studento varda.
     *
     * @return  vardas
     */
    std::string getVardas() const override;

    /**
     * @brief Ovveride'inta Zmogus klases funkcija setPavarde - nustato studento pavarde.
     *
     * @param pavarde
     */
    void setPavarde(std::string pavarde) override;

    /**
     * @brief Ovveride'inta Zmogus klases funkcija getPavarde - grazina studento pavarde.
     *
     * @return  pavarde
     */
    std::string getPavarde() const override;

    /**
     * @brief funkcija setPazymiaiVector - priskiriami pazymiai (vector<int> tipo).
     *
     * @param pazVector
     */
    void setPazymiaiVector(const std::vector<int>& pazVector);

    /**
     * @brief funkcija setPazymiai - priskiriami pazymiai (int tipo).
     *
     * @param paz
     */
    void setPazymiai(int paz);

    /**
     * @brief funkcija getPazymiai - grazina pazymius.
     * @return std::vector<int> pazymiai
     */
    std::vector<int> getPazymiai() const;

    /**
     * @brief funkcija resizePazymiai - pakeicia std::vector<int> pazymiai dydi.
     * @param n
     */
    void resizePazymiai(int n);
    /**
     * @brief funkcija setEgzaminas - iraso studento egzamino rezultata.
     * @param egzaminas
     */
    void setEgzaminas(int egzaminas);

    /**
     * @brief funkcija getEgzaminas - grazina mokinio egzamino rezultata.
     * @return egzaminas
     */
    int getEgzaminas() const;

    /**
     * @brief funkcija setVidurkis - apskaiciuoja studento vidurki.
     */
    void setVidurkis();

    /**
     * @brief funkcija setMediana - apskaiciuoja studento mediana.
     */
    void setMediana();

    /**
     * @brief funkcija getVidurkis - grazina studento vidurki.
     * @return vidurkis
     */
    float getVidurkis() const;

    /**
     * @brief funkcija getMediana - grazina studento mediana.
     * @return mediana
     */
    float getMediana() const;

    /**
     * @brief funkcija setAtsitiktiniaiPazymiai - ivestiems studentu vardams ranka, sugeneruoja pazymius ir egzamina.
     */
    void setAtsitiktiniaiPazymiai();

    /**
     * funkcija setAtsitiktiniaiDuomenys - sugeneruoja studentus ir ju pazymius ir egzamina.
     */
    void setAtsitiktiniaiDuomenys();

//    //Rule of Five headers
    /**
     * @brief rule of five kopijavimo konstruktorius - kopijuoja visa objekta su jo duomenimis i kita objekta.
     * @param kita
     */
    studentasV(const studentasV &kita);

    /**
     * @brief rule of five priskyrimo konstruktorius - priskiria vieno objekto duomenis kitam objektui
     * @param kita
     */
    studentasV &operator=(const studentasV &kita);

    /**
     * @brief rule of five perkelimo konstruktorius - perkelia objekta is vieno i kita pasalindamas duomenis is pirmojo
     * @param kita
     */
    studentasV(studentasV &&kita) noexcept;

    /**
     * @brief rule of five perkelimo priskyrimo operatorius - perkelia objekta is vieno i kita pasalindamas duomenis is pirmojo
     * @param kita
     */
    studentasV &operator=(studentasV &&kita) noexcept; //Perkelimo priskyrimo konstruktorius
    ~studentasV(); //Destruktorius

    /**
     * @brief Overloadinamas ostream operatorius << skirtas darbui su objektu studentas
     * @param os outputstream kintamasis
     * @param studentas
     */
    friend std::ostream &operator<<(std::ostream &os, const studentasV &studentas);

    /**
     * @brief Overloadinamas istream operatorius >> skirtas darbui su objektu studentas
     * @param is
     * @param studentas
     */
    friend std::istream &operator>>(std::istream &is, studentasV &studentas);
};

#endif //OOPUZD_STUDENTAS_H