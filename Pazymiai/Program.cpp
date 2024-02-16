#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>
#include <ctime>
#include "PazymiaiVectors.h"
#include "PazymiaiArrays.h"
#include "Common.h"
#include "cstdlib"

using namespace std;

#include <iostream>
#include <cstdlib> // Include for rand() and srand()
#include <ctime>   // Include for time()

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int n = 0; //studentu skaicius
    int x = 0; //pazymiu skaicius
    int i = 0;
    int pasirinkimas = 0;
    int arrVect = 0;
    int laikinas = 0;
    studentasA* grupe = nullptr;
    vector<studentasV> grupeVector;

    arraysVectorsPasirinkimas(arrVect);
    if(arrVect == 1){
        while (pasirinkimas != 4) {

            meniu(pasirinkimas);
            switch (pasirinkimas) {
            case 1:
                printf("Kiek studentu yra grupeje? (iveskite 0, jei norite ivesti neribota kieki)\n");
                cin >> n;
                grupe = new studentasA[n];
                if (n == 0) {
                    ivedimas(grupe, n);
                    vidurkis(n, grupe);

                    medianaSkaiciavimas(n, grupe);
                }
                else {
                    ivedimas(n, x, grupe);
                    medianaSkaiciavimas(n, x, grupe);
                }
                isvedimas(n, grupe);
                break;
            case 2:
                grupe = new studentasA[n];
                ivedimasCaseTwo(grupe, n);
                printf("Pazymiai sugeneruoti\n");
                vidurkis(n, grupe);
                medianaSkaiciavimas(n, grupe);
                isvedimas(n, grupe);
                break;
            case 3:

                printf("Kiek studentu yra grupeje?\n");
                cin >> n;
                grupe = new studentasA[n];

                while (i < n) {
                    studentasA stud = studentasA();
                    generateRandomNames(stud);
                    generateRandomGrades(stud);
                    addToArray(grupe, i, stud);
                }
                vidurkis(n, grupe);
                medianaSkaiciavimas(n, grupe);
                isvedimas(n, grupe);
                break;
            case 4:
                printf("Sekmingai baigete darba!!!\n");
                break;
            default:
                printf("Neteisingai ivesti duomenys\n");
            }

            printf("--------------------------------------------------\n");
            if (pasirinkimas == 4) {
                break;
            }

        }
        for (int i = 0; i < n; i++) {
            delete[] grupe[i].pazymiai;
        }
        delete[] grupe;
    }
    else {
        while (pasirinkimas != 4) {

            meniu(pasirinkimas);
            switch (pasirinkimas) {
            case 1:
                printf("Kiek studentu yra grupeje? (iveskite 0, jei norite ivesti neribota kieki)\n");
                cin >> n;
                grupeVector.resize(n);
                if (n == 0) {
                    ivedimasNoSize(grupeVector);
                    vidurkis(grupeVector);
                }
                else {
                    ivedimas(grupeVector, n);
                    medianaSkaiciavimasV(grupeVector);
                }
                isvedimas(grupeVector);
                for (int i = 0; i < n; i++) {
                    grupeVector[i].pazymiai.clear();
                }
                grupeVector.clear();
                break;
            case 2:
                ivedimasCaseTwo(grupeVector);
                printf("Pazymiai sugeneruoti\n");

                isvedimas(grupeVector);
                for (int i = 0; i < n; i++) {
                    grupeVector[i].pazymiai.clear();
                }
                grupeVector.clear();
                break;
            case 3:

                printf("Kiek studentu yra grupeje?\n");
                cin >> n;
                for (int z = 0; z < n; z++) {
                    studentasV stud = studentasV();
                    generateRandomNames(stud);
                    generateRandomGrades(stud);
                    grupeVector.push_back(stud);
                }
                isvedimas(grupeVector);
                for (int i = 0; i < n; i++) {
                    grupeVector[i].pazymiai.clear();
                }
                grupeVector.clear();
                break;
            case 4:
                printf("Sekmingai baigete darba!!!\n");
                break;
            default:
                printf("Neteisingai ivesti duomenys\n");
            }

            printf("--------------------------------------------------\n");
            if (pasirinkimas == 4) {
                break;
            }
        }
    }
    return 0;
}


