#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "PazymiaiVectors.h"
#include <fstream>
#include <sstream>
#include "chrono"
#include "Common.h"
#include "studentas.h"

double laikasSkaitymas = 0.0;
double laikasSkaiciavimas = 0.0;
double laikasRusiavimas = 0.0;
int fakePazymiai = 0;


void ivedimasV(vector<studentasV>& grupeVector, studentasV& stud, int studentoNr, int pazymiuKiekis) {
    string s;
    cout << "Iveskite " << studentoNr + 1 << " mokinio varda: ";
    cin >> s;
    stud.setVardas(s);
    cout << "Iveskite " << studentoNr + 1 << " mokinio pavarde: ";
    cin >> s;
    stud.setPavarde(s);
    cout << "Iveskite mokinio pazymius: ";
    readNumbersV(stud, pazymiuKiekis);

    do {
        cout << "Iveskite " << studentoNr + 1 << " mokinio egzamino rezultata: ";
        cin >> s;
    } while (stoi(s) < 1 || stoi(s) > 10);
    int skaicius = stoi(s);
    stud.setEgzaminas(skaicius);

    grupeVector.push_back(stud);
    cout << grupeVector.size() << " ";
}
void ivedimas(vector<studentasV>& grupeVector, int n) {
    int x = 0;
    do {
        cout << "Kiek namu darbu pazymiu turi kiekvienas mokinys?(Bent 1 paz.)" << endl;
        cin >> x;
    }while(x < 1);
    studentasV laikinasV;
    for (int i = 0; i < n; i++) {
        ivedimasV(grupeVector, laikinasV, i, x);
    }
}
void ivedimasNoSize(vector<studentasV>& grupeVector) {
    char testi = 't';
    string laikVardas;
    string laikPavarde;
    float laikEgzaminas;
    do{
        studentasV laikinasV;
        ivedimasV(grupeVector, laikinasV, grupeVector.size(), 0);
            cout << "Jei norite testi, iveskite t, jei nenorite testi, iveskite n ";
            cin >> testi;
    } while (testi == 't' || testi == 'T');
}
void ivedimasCaseTwo(vector<studentasV>& grupeVector) {

    studentasV laikinasV;
    string laikinasVardas;
    string laikinaPavarde;
    char testi = 't';
    do {
        cout << "Iveskite " << grupeVector.size() + 1 << " mokinio varda: ";
        cin >> laikinasVardas;
        laikinasV.setVardas(laikinasVardas);
        cout << "Iveskite " << grupeVector.size() + 1 << " mokinio pavarde: ";
        cin >> laikinaPavarde;
        laikinasV.setPavarde(laikinaPavarde);
        laikinasV.setAtsitiktiniaiPazymiai();
        grupeVector.push_back(laikinasV);
        do{
            cout << "Jei norite testi, iveskite t, jei nenorite testi, iveskite n" << endl;
            cin >> testi;
        }while(tolower(testi) != 't' && tolower(testi) != 'n');
    } while (tolower(testi) == 't' );
}
void fileReading(vector<studentasV>& grupeVector, const string &failas, double& laikasSkaitymas, int& fakePazymiai, double& laikasSkaiciavimas) {
    ifstream fin(failas);
    while (!fin.is_open()) {
        cerr << "Error: nepavyko atidaryti failo!!!\n" << endl;
        cerr << "Generuojami reikalingi failai!!\n";
        pazymiuFailoGeneravimas();
        fin.open(failas);
    }
    //grupeVector.Reserve(10000000);
    auto start = chrono::high_resolution_clock::now();
    string line;
    vector<int> laikiniPazymiai;
    getline(fin, line); // Skip header
    int laikinas = 0;
    while (getline(fin, line)) {

        istringstream iss(line);
        studentasV laikinasV;
        string laikinasVardas, laikinaPavarde, grade;

        iss >> laikinasVardas >> laikinaPavarde;
        laikinasV.setVardas(laikinasVardas);
        laikinasV.setPavarde(laikinaPavarde);
        while (iss >> grade) {
            try {
                int pazymys = std::stoi(grade);
                if (pazymys >= 0 && pazymys <= 10) {
                    laikiniPazymiai.push_back(pazymys);
                }
            } catch (const std::exception& e) {

            }
        }

        laikinasV.setEgzaminas(laikiniPazymiai.back());
        laikiniPazymiai.pop_back();
        laikinasV.setPazymiaiVector(laikiniPazymiai);
        grupeVector.push_back(laikinasV);
        laikiniPazymiai.clear();
    }
    fin.close();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    laikasSkaitymas = duration.count();
    cout << "VECTOR - Studentu nuskaitymas is failo truko: " << laikasSkaitymas << " sek." << endl;

    auto skStart = chrono::high_resolution_clock::now();
    for(auto& student : grupeVector){
        student.setVidurkis();
        student.setMediana();
    }
    auto skEnd = chrono::high_resolution_clock::now();

    chrono::duration<double> skDuration = skEnd - skStart;
    laikasSkaiciavimas = skDuration.count();
    grupeVector.shrink_to_fit();
}

//Random duomenu generavimo funkcijos
void generateRandomNames(studentasV &stud) {
    const char* vardas[] = { "Bronius", "Juozas", "Rimas", "Tomas", "Matas", "Markas", "Ignas", "Kristupas", "Joris", "Arnas" };
    const char* pavarde[] = { "Broniauskas", "Juozevicius", "Rimauskas", "Tomavicius", "Matkevicius", "Markevicius", "Igniauskas", "Kristevicius", "Jorevicius", "Arniavicius" };
    int vardasIndex = rand() % 10;
    int pavardeIndex = rand() % 10;
    stud.setVardas(std::string(vardas[vardasIndex]));
    stud.setPavarde(std::string(pavarde[pavardeIndex]));
}
void generateRandomGrades(studentasV &stud) {
    stud.resizePazymiai((rand() % 10 + 1));
    for (double paz : stud.getPazymiai()) {
        paz = rand() % 10 + 1;
    }
    stud.setEgzaminas(rand() % 10 + 1);
}

//General vidurkio/medianos skaiciavimas pasirinkus
void generalVidurkisCalculate(vector<studentasV>& grupeVector) {
    for (auto& student : grupeVector) {
        student.setVidurkis();
    }
}
void generalMedianaCalculate(vector<studentasV>& grupeVector) {
    for (auto& studentas : grupeVector) {
        studentas.setMediana();
    }
}

//Isvedimo funkcija
void isvedimoPasirinkimas(string& pasirinkimasConsole){
    do {
        cout << "Jei norite isvedimo i konsole, rasykite 1, jei norite isvedimo i faila, rasykite 2" << endl;
        cin >> pasirinkimasConsole;
    } while (pasirinkimasConsole != "1" && pasirinkimasConsole != "2");
}

void isvedimas(vector<studentasV> grupeVector, double laikasSkaitymas, double laikasSkaiciavimas, double laikasRusiavimas, int fakePazymiai, int iteracija) {
    string choice = " ";
    string pasirinkimasConsole;
    string vidMed;
    string custom = " ";
    ofstream fout("KursiokaiNesugeneruotas" + to_string(iteracija+1) + ".txt");

    pasirinkimasVidMed(vidMed);
    cout << "--------------------------------------------------" << endl;
    sortChoice(choice);
    sortInput(choice, grupeVector);
    cout << "--------------------------------------------------" << endl;
    isvedimoPasirinkimas(pasirinkimasConsole);
    cout << "--------------------------------------------------" << endl;

    if(pasirinkimasConsole == "1"){
        if (vidMed == "1") {
            cout << "--------------------------------------------------" << endl;
            cout << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(20) << "Galutinis (Vid.)" << endl;
            cout << "--------------------------------------------------" << endl;

            for (auto& student : grupeVector) {
                cout << left << setw(20) << student.getVardas() << left << setw(20) << student.getPavarde() << left << setw(20) << setprecision(4) << student.getVidurkis() << endl;
            }
        }
        else if (vidMed == "2") {
            cout << "--------------------------------------------------" << endl;
            cout << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(20) << "Galutinis (Med.)" << endl;
            cout << "--------------------------------------------------" << endl;

            for (auto& student : grupeVector) {
                cout << left << setw(20) << student.getVardas() << left << setw(20) << student.getPavarde() << left << setw(20) << setprecision(4) << student.getMediana() << endl;
            }
        }
    }else{
        if (vidMed == "1") {
            fout << "--------------------------------------------------" << endl;
            fout << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(20) << "Galutinis (Vid.)" << endl;
            fout << "--------------------------------------------------" << endl;

            for (auto& student : grupeVector) {
                fout << left << setw(20) << student.getVardas()<< left << setw(20) << student.getPavarde() << left << setw(20) << setprecision(4) << student.getVidurkis() << endl;
            }

        }
        else if (vidMed == "2") {
            fout << "--------------------------------------------------" << endl;
            fout << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(20) << "Galutinis (Med.)" << endl;
            fout << "--------------------------------------------------" << endl;

            for (auto& student : grupeVector) {
                fout << left << setw(20) << student.getVardas() << left << setw(20) << student.getPavarde() << left << setw(20) << fixed << setprecision(3) << student.getMediana() << endl;
            }
        }
    }
    fout.close();
}


//Comparinimo bool funkcijos
bool compareByName(const studentasV& a, const studentasV& b) {
    std::string nameA = a.getVardas();
    std::string nameB = b.getVardas();

    if (nameA.compare(0, 6, "Vardas") == 0 && nameB.compare(0, 6, "Vardas") == 0) {
        int num1 = std::stoi(nameA.substr(6));
        int num2 = std::stoi(nameB.substr(6));
        return num1 > num2;
    } else {
        return nameA < nameB;
    }
}

bool compareBySurname(const studentasV& a, const studentasV& b) {
    std::string surnameA = a.getPavarde();
    std::string surnameB = b.getPavarde();

    if (surnameA.compare(0, 7, "Pavarde") == 0 && surnameB.compare(0, 7, "Pavarde") == 0) {
        try {
            int num1 = std::stoi(surnameA.substr(7));
            int num2 = std::stoi(surnameB.substr(7));
            return num1 > num2;
        } catch(const std::invalid_argument& e) {
            return surnameA < surnameB;
        }
    } else {
        return surnameA < surnameB;
    }
}
bool compareByAverage(const studentasV& a, const studentasV& b){
    return a.getVidurkis() < b.getVidurkis();
}
bool compareByMediana(const studentasV& a, const studentasV& b){
    return a.getMediana() < b.getMediana();
}

//Dinaminis pazymiu ivedimas
void readNumbersV(studentasV &stud, int maxItems = 0) {
    string s;
    bool testi = true;
    int notNumbers = 0;
    int badValues = 0;
    if (maxItems > 0) {
        cout << "Iveskite " << maxItems << " pazymius. Noredami baigti ivedima spauskite 0." << endl;
        cout << "---------------------------------------------------------" << endl;
    }
    else {
        cout << "Iveskite pazymius. Noredami baigti ivedima spauskite 0." << endl;
        cout << "---------------------------------------------------------" << endl;
    }
    while (testi) {
        while (s != "0") {
            cin >> s;
            try {
                int value = std::stoi(s);
                badValues += value >= 0 && value <= 10 ? 0 : 1;
                if ((stud.getPazymiai().size() < maxItems || maxItems == 0) && value > 0 && value < 11) {
                    stud.setPazymiai(stoi(s));
                }
            }
            catch (...) {
                notNumbers++;
            }
        }
        testi = maxItems > 0 && stud.getPazymiai().size() < maxItems;
        if (testi) {
            if (notNumbers > 0)
                cout << "Ivestu neteisingu pazymiu skaicius: " << notNumbers << endl;
            if (badValues)
                cout << "Ivestu pazymiu, kurie nera intervale [1,10], skaicius: " << badValues << endl;
            cout << "Trukstamu pazymiu skaicius: " << maxItems - stud.getPazymiai().size() << ". Teskite ivedima" << endl;
            s = "";
            notNumbers = badValues = 0;
        }
    }
}
//Sortinimo funkcija
void sortInput(string& choice, vector<studentasV>& grupeVector){
    auto start = std::chrono::high_resolution_clock::now();

    int choiceInt = 0;
    if(all_of(choice.begin(), choice.end(), ::isdigit)) {
        choiceInt = stoi(choice);
    } else {
        cerr << "Error: choice must be a numeric value between 1 and 4.\n";
        return;
    }

    if (choiceInt < 1 || choiceInt > 4) {
        cerr << "Error: Invalid sorting choice!\n";
        return;
    }

    switch(choiceInt){
        case 1:{
            sort(grupeVector.begin(), grupeVector.end(), [](const studentasV& a, const studentasV& b) {
                return (a.getVardas().find("Vardas") == 0 && b.getVardas().find("Vardas") == 0) ?
                       std::stoi(a.getVardas().substr(6)) > std::stoi(b.getVardas().substr(6)) :
                       a.getVardas() < b.getVardas();
            });
            break;
        }
        case 2:{
            sort(grupeVector.begin(), grupeVector.end(), [](const studentasV& a, const studentasV& b) {
                return (a.getPavarde().find("Pavarde") == 0 && b.getPavarde().find("Pavarde") == 0) ?
                       std::stoi(a.getPavarde().substr(7)) > std::stoi(b.getPavarde().substr(7)) :
                       a.getPavarde() < b.getPavarde();
            });
            break;
        }
        case 3:{
            sort(grupeVector.begin(), grupeVector.end(), [](const studentasV& a, const studentasV& b) {
                return a.getVidurkis() < b.getVidurkis();
            });
            break;
        }
        case 4:{
            sort(grupeVector.begin(), grupeVector.end(), [](const studentasV& a, const studentasV& b) {
                return a.getMediana() < b.getMediana();
            });
            break;
        }
        default:{
            cerr << "Error: Invalid sorting choice!\n";
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    laikasRusiavimas = duration.count();
}
void laikoIsvedimas(double laikasSkaitymas, double laikasSkaiciavimas, double laikasRusiavimas) {
        cout << "Is viso sugaistas laikas nuskaitant duomenis is failo: " << laikasSkaitymas << "sek. \n";
        cout << "Is viso sugaistas laikas  atliekant skaiciavimus: " << laikasSkaitymas << "sek. \n";
        cout << "Is viso sugaistas laikas rusiuojant duomenis: " << laikasSkaiciavimas << "sek. \n";
        cout << "Viso sugaista laiko: " << laikasSkaitymas + laikasSkaitymas + laikasSkaiciavimas << "sek. \n";
}
void studentuGeneravimas(vector<studentasV>& grupeVector, int kiekis) {
    for (int i = 1; i <= kiekis; i++) {
        studentasV stud;
        std::string vardas = "Vardas" + to_string(i);
        std::string pavarde = "Pavarde" + to_string(i);
        stud.setVardas(vardas);
        stud.setPavarde(pavarde);
        stud.resizePazymiai(rand() % 10 + 1);
        for (int paz : stud.getPazymiai()) {
            paz = rand() % 10 + 1;
        }
        stud.setEgzaminas(rand() % 10 + 1);
        grupeVector.push_back(stud);
    }
}

void failoNuskaitymasRusiavimas(vector<studentasV>& grupeVector, vector<studentasV>& grupeBad, vector<studentasV>& grupeGood, int i, string vidMed, string ivedimasKonteineris, string choice) {
    fileReading(grupeVector, "studentai" + to_string(i + 1) + ".txt", laikasSkaitymas, fakePazymiai, laikasSkaiciavimas);

    auto start1 = std::chrono::high_resolution_clock::now();
    sortInput(choice, grupeVector);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;


    auto start = std::chrono::high_resolution_clock::now();
    if (ivedimasKonteineris == "1") {
        vectorPartition(vidMed, grupeVector, grupeGood, grupeBad);
    }
    else {
        vectorPartition2(vidMed, grupeVector, grupeBad);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    cout << "VECTOR - studentu konteinerio rusiavimas truko: " << duration1.count() << " sek." << endl;
    cout << "VECTOR - Studentu rusiavimas i du konteinerius su " << ivedimasKonteineris << " pasirinkimu truko:  " << duration.count() << " sek." << endl;
}
void isvedimasFailai(vector<studentasV>& grupeVector, vector<studentasV>& grupeBad,int i, string& vidMed, string& choice) {

        ofstream fout("KursiokaiGood" + to_string(i + 1) + ".txt");
        ofstream foutB("KursiokaiBad" + to_string(i + 1) + ".txt");

        stringstream bufferis;
        stringstream bufferisB;

        auto start = std::chrono::high_resolution_clock::now();
        sortInput(choice, grupeVector);
        sortInput(choice, grupeBad);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;

        //cout << "Abieju studentu konteineriu rusiavimas pagal pasirinkima :  " << duration.count() << " sek." << endl;
        auto start1 = std::chrono::high_resolution_clock::now();
        if (vidMed == "1") {
            bufferis << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(20) << "Galutinis (Vid.)" << endl;
            bufferis << "--------------------------------------------------" << endl;

            for (auto& studentGeras : grupeVector) {
                cout << studentGeras.getVardas() << endl;
                bufferis << left << setw(20) << studentGeras.getVardas() << left << setw(20) << studentGeras.getPavarde() << left << setw(20) << setprecision(3) << studentGeras.getVidurkis() << endl;
            }
            fout << bufferis.str();
            bufferis.str("");
            bufferis.clear();
        }
        else if (vidMed == "2") {
            bufferis << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(20) << "Galutinis (Med.)" << endl;
            bufferis << "--------------------------------------------------" << endl;
            for (auto& student : grupeVector) {
                bufferis << left << setw(20) << student.getVardas() << left << setw(20) << student.getPavarde() << left << setw(20) << setprecision(3) << student.getMediana() << endl;
            }
            fout << bufferis.str();
            bufferis.str("");
            bufferis.clear();
        }

        if (vidMed == "1") {
            bufferisB << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(20) << "Galutinis (Vid.)" << endl;
            bufferisB << "--------------------------------------------------" << endl;

            for (auto& student : grupeBad) {
                bufferisB << left << setw(20) << student.getVardas() << left << setw(20) << student.getPavarde()<< left << setw(20) << setprecision(3) << student.getVidurkis() << endl;
            }
            foutB << bufferisB.str();
            bufferisB.str("");
            bufferisB.clear();

        }
        else if (vidMed == "2") {
            bufferisB << left << setw(20) << "Vardas" << left << setw(20) << "Pavarde" << left << setw(20) << "Galutinis (Med.)" << endl;
            bufferisB << "--------------------------------------------------" << endl;

            for (auto& student : grupeBad) {
                bufferisB << left << setw(20) << student.getVardas() << left << setw(20) << student.getPavarde() << left << setw(20) << setprecision(3) << student.getMediana() << endl;
            }
            foutB << bufferisB.str();
            bufferisB.str("");
            bufferisB.clear();
        }
        fout.close();
        foutB.close();
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration1 = end1 - start1;
        cout << "Abieju studentu konteineriu isvedimas truko:  " << duration1.count() << " sek." << endl;
}
void clearVector(vector<studentasV>& grupeVector) {
    grupeVector.clear();
}
void vectorPartition(string vidMed, vector<studentasV>& grupeVector, vector<studentasV>& grupeGood, vector<studentasV>& grupeBad) {
    grupeGood.reserve(grupeVector.size());
    grupeBad.reserve(grupeVector.size());
    if (vidMed == "1") {
        auto it = std::partition(grupeVector.begin(), grupeVector.end(), [](const studentasV& student) {
            return student.getVidurkis() >= 5;
        });

        if(it != grupeVector.begin()){
            grupeGood.insert(grupeGood.end(), grupeVector.begin(), it);
        }
        if(it != grupeVector.end()){
            grupeBad.insert(grupeBad.end(), it, grupeVector.end());
        }
    }
    else {
        auto it = std::partition(grupeVector.begin(), grupeVector.end(), [](const studentasV& student) {
            return student.getMediana() >= 5;
        });

        if(it != grupeVector.begin()){
            grupeGood.insert(grupeGood.end(), grupeVector.begin(), it);
        }
        if(it != grupeVector.end()){
            grupeBad.insert(grupeBad.end(), it, grupeVector.end());
        }
    }
    grupeBad.shrink_to_fit();
    grupeGood.shrink_to_fit();
}
void vectorPartition2(string vidMed, vector<studentasV>& grupeVector, vector<studentasV>& grupeBad) {
    grupeBad.reserve(grupeVector.size());
    if (vidMed == "1") {
        auto it = std::partition(grupeVector.begin(), grupeVector.end(), [](const studentasV& student) {
            return student.getVidurkis() >= 5;
        });
        if(it != grupeVector.end()){
            grupeBad.insert(grupeBad.end(), it, grupeVector.end());
            grupeVector.erase(it, grupeVector.end());
        }
    }
    else {
        auto it = std::partition(grupeVector.begin(), grupeVector.end(), [](const studentasV &student) {
            return student.getMediana() >= 5;
        });
        if(it != grupeVector.end()){
            grupeBad.insert(grupeBad.end(), it, grupeVector.end());
            grupeVector.erase(it, grupeVector.end());
        }
    }
    grupeBad.shrink_to_fit();
    grupeVector.shrink_to_fit();
}

void vektoriaiMain(string vidMed, string choice, vector<studentasV>& grupeVector, vector<studentasV>& grupeBad, vector<studentasV>& grupeGood, string ivedimasKonteineris) {

    pasirinkimasVidMed(vidMed);
    sortChoice(choice);
    pasirinkimasIvedimas(ivedimasKonteineris);
    //pazymiuFailoGeneravimas();
    auto start = std::chrono::high_resolution_clock::now();


    for (int i = 0; i < 5; i++) {
        cout << pow(10, i + 3) << " studentu failas" << endl;

        failoNuskaitymasRusiavimas(grupeVector, grupeBad, grupeGood, i, vidMed, ivedimasKonteineris, choice);
        isvedimasFailai(grupeVector, grupeBad, i, vidMed, choice);
        cout << "--------------------------------------------------" << endl;
        grupeVector.clear();

    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "VIsos programos veikimo trukme:  " << duration.count() << " sek." << endl;
}
