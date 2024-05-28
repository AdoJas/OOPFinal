# ***Klasės ir struktūros***

## Kompiuterio komponentai naudoti testavimo metu 

| Komponentas |                    Pavadinimas                    |                      
|:-----------:|:-------------------------------------------------:|
|   **CPU**   |             `AMD Ryzen 5 3600 6-core`             |
|   **GPU**   | `G.Skill Trident Z RGB DDR4 16GB (2x8GB) 3200MHz` |
|   **SSD**   |         `Samsung SSD 970 EVO Plus, 500GB`         |


# Turinys
- [x] [Projekto dokumentacija - Doxygen](#projekto-dokumentacija)
- [x] [Kelios Vector klases funkcijos](#kelios-vector-klases-funkcijos)
- [x] [Vector ir std::vector spartos analize](#vector-ir-stdvector-spartos-analize)
- [x] [Paskirstymu kiekis std::vector ir Vector konteineriuose](#paskirstymu-kiekis-stdvector-ir-vector-konteineriuose)
- [x] [Programos greitis](#programos-greitis)
- [x] [Testavimas - GoogleTest Vector klase](#testavimas)
- [x] [Instaliacija](#instaliacija)
- [x] [Ka daro programa?](#ka-daro-programa)
- [x] [Kaip pasinaudoti kodu? (Windows ir macOS)](#kaip-pasinaudoti-kodu-windows-ir-macos)

# Projekto dokumentacija
 **Projekto dokumentacija galite perzvelgti naudodami savo IDE arba overleaf.com online Latex compiliatoriu, tereikia ikelti latex failo .zip rinkini.
 Taip pat galite perziureti dokumentacijos PDF faila, kuris yra pridetas prie projekto failu.**

## Kelios Vector klases funkcijos
> 1. `void PushBack(reference object)` - prideda nauja elementa i Vector konteineri.
> 2. `void PopBack()` - istrina paskutini elementa is Vector konteinerio.
> 3. `void Insert(size_type index, reference object)` - iterpia nauja elementa i Vector konteineri pagal nurodyta index'a.
> 4. `void Erase(size_type index)` - istrina elementa is Vector konteinerio pagal nurodyta index'a.
> 5. `void Resize(size_type n)` - pakeicia Vector konteinerio dydi i n.
### Funkciju kodas issamiau
#### 1. `void PushBack(reference object)`
```
    void PushBack(reference object) {
    if (size == capacity) {
    Reserve(capacity == 0 ? 1 : capacity * 2);
    }
    elements[size] = object;
    size++;
    }
```
1. `if (size == capacity)` - tikrina ar Vector konteineris pilnas.
2. `Reserve(capacity == 0 ? 1 : capacity * 2);` - jei konteineris pilnas, tai padvigubinamas jo dydis.
3. `elements[size] = object;` - prideda nauja elementa i Vector konteineri.
4. `size++;` - padidina Vector konteinerio dydi vienetu.
5. `}` - uzbaigia funkcija.

#### 2. `void PopBack()`
```
    void PopBack() {
    if (size == 0) {
    throw std::out_of_range("Vector is empty");
    }
    size--;
    }
```
1. `if (size == 0)` - tikrina ar Vector konteineris tuscias.
2. `throw std::out_of_range("Vector is empty");` - jei konteineris tuscias, tai ismeta klaida.
3. `size--;` - istrina paskutini elementa is Vector konteinerio.
4. `}` - uzbaigia funkcija.

#### 3. `void Insert(size_type index, reference object)`
```
    void Insert(size_type index, reference object) {
    if (index < 0 || index > size) {
    throw std::out_of_range("Index out of range");
    }
    if (size == capacity) {
    Reserve(capacity == 0 ? 1 : capacity * 2);
    }
    for (size_type i = size; i > index; i--) {
    elements[i] = elements[i - 1];
    }
    elements[index] = object;
    size++;
    }
```
1. `if (index < 0 || index > size)` - tikrina ar nurodytas index'as yra tinkamas.
2. `throw std::out_of_range("Index out of range");` - jei index'as netinkamas, tai ismeta klaida.
3. `if (size == capacity)` - tikrina ar Vector konteineris pilnas.
4. `Reserve(capacity == 0 ? 1 : capacity * 2);` - jei konteineris pilnas, tai padvigubinamas jo dydis.
5. `for (size_type i = size; i > index; i--)` - ciklas, kuris perstumia elementus i desine.
6. `elements[i] = elements[i - 1];` - perstumia elementus i desine.
7. `elements[index] = object;` - iterpia nauja elementa i Vector konteineri pagal nurodyta index'a.
8. `size++;` - padidina Vector konteinerio dydi vienetu.
9. `}` - uzbaigia funkcija.

#### 4. `void Erase(size_type index)`
```
    void Erase(size_type index) {
    if (index < 0 || index >= size) {
    throw std::out_of_range("Index out of range");
    }
    for (size_type i = index; i < size - 1; i++) {
    elements[i] = elements[i + 1];
    }
    size--;
    }
```
1. `if (index < 0 || index >= size)` - tikrina ar nurodytas index'as yra tinkamas.
2. `throw std::out_of_range("Index out of range");` - jei index'as netinkamas, tai ismeta klaida.
3. `for (size_type i = index; i < size - 1; i++)` - ciklas, kuris perstumia elementus i kaire.
4. `elements[i] = elements[i + 1];` - perstumia elementus i kaire.
5. `size--;` - istrina elementa is Vector konteinerio pagal nurodyta index'a.
6. `}` - uzbaigia funkcija.

#### 5.  `void Resize(size_type n)` 
```
    void Resize(size_type n) {
    if (n < 0) {
    throw std::out_of_range("Size out of range");
    }
    if (n > size) {
    if (n > capacity) {
    Reserve(n);
    }
    for (size_type i = size; i < n; i++) {
    elements[i] = T();
    }
    }
    size = n;
    }
```
1. `if (n < 0)` - tikrina ar n yra teigiamas skaicius.
2. `throw std::out_of_range("Size out of range");` - jei n yra neigiamas skaicius, tai ismeta klaida.
3. `if (n > size)` - tikrina ar n yra didesnis uz size.
4. `if (n > capacity)` - tikrina ar n didesnis uz capacity.
5. `Reserve(n);` - jei n didesnis uz capacity, tai padvigubinamas jo dydis.
6. `for (size_type i = size; i < n; i++)` - ciklas, kuris prideda naujus elementus i Vector konteineri.
7. `elements[i] = T();` - prideda naujus elementus i Vector konteineri.
8. `size = n;` - pakeicia Vector konteinerio dydi i n.
9. `}` - uzbaigia funkcija.

## Vector ir std::vector spartos analize
### std::vector 
```
int alokacijaSTD = 0, alokacijaVector = 0;
        for(int x = 0; x < 5; x++){
            auto start = std::chrono::high_resolution_clock::now();
                unsigned int sz = pow(10, 3+x);
                std::vector<int> v1;
                for (int i = 1; i <= sz; ++i){
                    v1.push_back(i);
                }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end-start;
            cout << "std::vector<int> " << sz << " elementu: " << diff.count() << " s\n";
            alokacijaSTD = 0;
        }
```
### Vector
```
        for(int x = 0; x < 5; x++){
            auto start = std::chrono::high_resolution_clock::now();
            unsigned int sz = pow(10, 3+x);
            Vector<int> v1;
            for (int i = 1; i <= sz; ++i){
                v1.PushBack(i);
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end-start;
            cout << "Vector<int> " << sz << " elementu: " << diff.count() << " s\n";
            alokacijaVector = 0;
        }
```
### Rezultatai
| Konteinerio tipas | Elementu kiekis | Laikas      |
|-------------------|-----------------|-------------|
| std::vector<int>  | 1000            | 3.79e-05 s  |
| std::vector<int>  | 10000           | 0.0001457 s |
| std::vector<int>  | 100000          | 0.0011799 s |
| std::vector<int>  | 1000000         | 0.0128761 s |
| std::vector<int>  | 10000000        | 0.10869 s   |
| Vector<int>       | 1000            | 2.02e-05 s  |
| Vector<int>       | 10000           | 8.4e-05 s   |
| Vector<int>       | 100000          | 0.0007809 s |
| Vector<int>       | 1000000         | 0.0067444 s |
| Vector<int>       | 10000000        | 0.05882 s   |

### Išvados
> 1. Vector konteineris yra greitesnis nei std::vector konteineris.
> 2. Taip gali buti del to, kad Vector konteineris rezervuoja daugiau atminties nei std::vector konteineris su kiekvienu pridedamu elementu.

# Paskirstymu kiekis std::vector ir Vector konteineriuose
## Papildomos eilutes, naudotos kode
```
if(v1.Size() == v1.Capacity()){
                    alokacijaVector++;
                }
```

```
if(v1.size() == v1.capacity()){
                    alokacijaSTD++;
                }
```    

### Rezultatai
| Konteinerio tipas | Elementu kiekis | Perskirstymu kiekis |
|-------------------|-----------------|---------------------|
| std::vector<int>  | 1000            | 10                  |
| std::vector<int>  | 10000           | 14                  |
| std::vector<int>  | 100000          | 17                  |
| std::vector<int>  | 1000000         | 20                  |
| std::vector<int>  | 10000000        | 24                  |
| Vector<int>       | 1000            | 7                   |
| Vector<int>       | 10000           | 10                  |
| Vector<int>       | 100000          | 14                  |
| Vector<int>       | 1000000         | 17                  |
| Vector<int>       | 10000000        | 20                  |

### Išvados
> 1. Vector konteineris perskirsto atminti reciau nei std::vector konteineris, nes jau yra inicializuojamas su `capacity = 10`, o std::vector su `capacity = 0`.

# Programos greitis
## std::vector
| Studentų skaičius | Konteinerio tipas | Failo skaitymo laikas (s) | Rūšiavimo laikas (s) | Skirstymo laikas (s) | Išvedimo laikas (s) |
|-------------------|-------------------|---------------------------|----------------------|----------------------|---------------------|
| 100000            | std::vector       | 0.290567                  | 0.696348             | 0.0644754            | 0.138012            |
| 1e+06             | std::vector       | 3.11317                   | 9.24343              | 0.700809             | 1.40712             |
| 1e+07             | std::vector       | 29.7807                   | 109.566              | 6.54661              | 14.0588             |
## Vector
| Studentų skaičius | Konteinerio tipas | Failo skaitymo laikas (s) | Rūšiavimo laikas (s) | Skirstymo laikas (s) | Išvedimo laikas (s) |
|-------------------|-------------------|---------------------------|----------------------|----------------------|---------------------|
| 100000            | VEKTORIUS         | 0.341567                  | 0.668255             | 0.129638             | 0.12699             |
| 1e+06             | VEKTORIUS         | 3.40367                   | 7.6812               | 1.23574              | 1.30948             |
| 1e+07             | VEKTORIUS         | 34.9877                   | 95.6473              | 12.5077              | 12.8941             |

### Išvados
> 1. Vector konteineris leciau nuskaito duomenis is failu nei std::vector konteineris
> 2. Vector konteineris greiciau sortina duomenis nei std::vector konteineris
> 3. Vector konteineris leciau skirsto duomenis i skirtingus konteinerius nei std::vector konteineris
> 4. Vector konteineris greiciau isveda duomenis i failus nei std::vector konteineris

## Testavimas
> 1. Testavimas buvo darytas su Googel Test Unit testu testavimo frameworku.
> 2. Nuoroda i Google Test -> https://github.com/google/googletest/releases
> 3. Buvo testuojama Vector class'e, a.k.a. Vector klases metodai

### Testai Vector klasei
#### 1. `TEST(VectorClassTest, PushBackTest)`
```
TEST(VectorClassTest, PushBackTest) {
    Vector<int> v;
    v.PushBack(1);
    EXPECT_EQ(v.Size(), 1);
    EXPECT_EQ(v[0], 1);
}
```
#### 2. `TEST(VectorClassTest, PopBackTest)`
```
TEST(VectorClassTest, PopBackTest) {
    Vector<int> v;
    v.PushBack(1);
    v.PopBack();
    EXPECT_EQ(v.Size(), 0);
}
```
#### 3. `TEST(VectorClassTest, ClearTest)`
```
TEST(VectorClassTest, ClearTest) {
Vector<int> v(5,10);
v.Clear();
EXPECT_EQ(v.Size(), 0);
}
```
#### 4.  TEST(VectorClassTest, ResizeTest)
```
TEST(VectorClassTest, ResizeTest) {
Vector<int> v(5,10);
v.Resize(10);
EXPECT_EQ(v.Size(), 10);
}
```
#### 5. `TEST(VectorClassTest, ReserveTest)`
```
TEST(VectorClassTest, ReserveTest) {
Vector<int> v;
v.Reserve(10);
EXPECT_GE(v.Capacity(), 10);
}
```
#### 6. `TEST(VectorClassTest, ShrinkToFitTest)`
```
TEST(VectorClassTest, ShrinkToFitTest) {
Vector<int> v(5, 10);
v.Reserve(10);
v.ShrinkToFit();
EXPECT_EQ(v.Capacity(), 5);
}
```
#### 7. `TEST(VectorClassTest, AtTest)`
```
TEST(VectorClassTest, AtTest) {
Vector<int> v(5,10);
EXPECT_NO_THROW(v.At(4));
EXPECT_THROW(v.At(5), std::out_of_range);
}
```
#### 8. `TEST(VectorClassTest, FrontBackTest)`
```
TEST(VectorClassTest, FrontBackTest) {
Vector<int> v;
v.PushBack(1);
v.PushBack(2);
EXPECT_EQ(v.Front(), 1);
EXPECT_EQ(v.Back(), 2);
}
```

#### 9. `TEST(VectorClassTest, IteratorTest)`
```
TEST(VectorClassTest, IteratorTest) {
Vector<int> v;
v.PushBack(1);
v.PushBack(2);
v.PushBack(3);
int sum = 0;
for(auto it = v.begin(); it != v.end(); ++it) {
sum += *it;
}
EXPECT_EQ(sum, 6);
}
```

#### 10. `TEST(VectorClassTest, EmplaceBackTest)`
```
TEST(VectorClassTest, EmplaceBackTest) {
Vector<int> v;
v.EmplaceBack(1);
EXPECT_EQ(v.Size(), 1);
EXPECT_EQ(v[0], 1);
}
```

### Testu rezultatai
```
[==========] Running 13 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 13 tests from VectorClassTest
[ RUN      ] VectorClassTest.MoveConstructorTest
[       OK ] VectorClassTest.MoveConstructorTest (0 ms)
[ RUN      ] VectorClassTest.CopyAssignmentOperatorTest
[       OK ] VectorClassTest.CopyAssignmentOperatorTest (0 ms)
[ RUN      ] VectorClassTest.MoveAssignmentOperatorTest
[       OK ] VectorClassTest.MoveAssignmentOperatorTest (0 ms)
[ RUN      ] VectorClassTest.PushBackTest
[       OK ] VectorClassTest.PushBackTest (0 ms)
[ RUN      ] VectorClassTest.PopBackTest
[       OK ] VectorClassTest.PopBackTest (0 ms)
[ RUN      ] VectorClassTest.ClearTest
[       OK ] VectorClassTest.ClearTest (0 ms)
[ RUN      ] VectorClassTest.ResizeTest
[       OK ] VectorClassTest.ResizeTest (0 ms)
[ RUN      ] VectorClassTest.ReserveTest
[       OK ] VectorClassTest.ReserveTest (0 ms)
[ RUN      ] VectorClassTest.ShrinkToFitTest
[       OK ] VectorClassTest.ShrinkToFitTest (0 ms)
[ RUN      ] VectorClassTest.AtTest
[       OK ] VectorClassTest.AtTest (0 ms)
[ RUN      ] VectorClassTest.FrontBackTest
[       OK ] VectorClassTest.FrontBackTest (0 ms)
[ RUN      ] VectorClassTest.IteratorTest
[       OK ] VectorClassTest.IteratorTest (0 ms)
[ RUN      ] VectorClassTest.EmplaceBackTest
[       OK ] VectorClassTest.EmplaceBackTest (0 ms)
[----------] 13 tests from VectorClassTest (0 ms total)

[----------] Global test environment tear-down
[==========] 13 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 13 tests.
```
# Instaliacija
> 1. Atsisiusti projekto failus is GitHub.
> 2. Paspausti ant outputas.exe failo.
> 3. Failai bus suinstaliuoti i jusu kompiuteri.
> 4. Smagaus naudojimo!!!

# ***Ka daro programa?***
>1. Leidzia dinamiskai arba statiskai ivesti studentu duomenis ir dirbti su jais.
>2. Leidzia ivedus studentu vardus ir pavardes generuoti ju pazymius ir dirbti su jais.
>3. Leidzia automatiskai atsitiktinai generuoti studentu vardus, pavardes ir ju pazymius, dirbti su jais.
>4. Leidzia nuskaityti duomenis is failo ir dirbti su tais duomenimis.
>5. Leidzia generuoti studentu duomenu faila su pazymiais, juos nuskaityti ir dirbti su jais.
>6. 5 funkcija, su pridetu pasirinkimu rusiuoti duomenis i skirtingus konteinerius(Vector, list, deque).


# ***Kaip pasinaudoti kodu? (Windows ir macOS)***
>1. Atsisiuntę ir išsisaugoję projekto failus savo kompiuteryje, atsisiųskite CLion IDE. [https://www.jetbrains.com/clion/download/#section=mac]
>2. Aktyvuokite CLion IDE su savo gautu kodu, kuris jums bus atsiūstas i el. pašto adresą, su kuriuo registravotės į JETBRAINS.
>3. Atlikę šiuos žingsnius, atsidarykite failus per CLion.
>4. Atidarius į failus, paspauskite ant Program.cpp du kartus.
>5. Viršuje iššokęs langelis praneš, kad reikia sukonfiguruoti CMake projektą.
>6. Paspauskite šį mygtuką ir nurodykite CMakeLists.txt failo vietą savo kompiuteryje.
>7. Atlikus šiuos žingsnius, lango viršuje paspauskite "RUN" mygtuką.
>8. Smagaus naudojimo!!!
