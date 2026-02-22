# Variables & Types de donnees 📦

## Pourquoi c'est important

En HFT, choisir le bon type = nanosecondes gagnees. Un `float` au lieu d'un `double` peut faire
la difference sur un million d'operations par seconde.

En maldev, comprendre les types = comprendre la memoire. Et comprendre la memoire, c'est la base
de tout : buffer overflows, injection, reverse engineering.

---

## C'est quoi une variable ?

Une variable, c'est une **boite en memoire** avec :
- Un **nom** (pour la retrouver)
- Un **type** (pour savoir combien d'espace elle prend)
- Une **valeur** (ce qu'elle contient)

```
  Memoire RAM (representation simplifiee)
 ┌──────────────────────────────────────────────────────────────┐
 │                                                              │
 │  Adresse    Nom          Type      Taille    Valeur          │
 │  ────────   ──────────   ──────    ──────    ──────          │
 │  0x1000     age          int       4 bytes   [ 00 00 00 19 ] │
 │  0x1004     prix         double    8 bytes   [ 40 59 00 00 ] │
 │  0x100C     lettre       char      1 byte    [ 41 ]          │
 │  0x100D     actif        bool      1 byte    [ 01 ]          │
 │  0x100E     nom          string    variable  [ "Alex" ]      │
 │                                                              │
 └──────────────────────────────────────────────────────────────┘
```

---

## Les types fondamentaux

### Types entiers

| Type | Taille | Plage (approximative) | Usage |
|---|---|---|---|
| `int` | 4 bytes | -2 milliards a +2 milliards | Usage general |
| `short` | 2 bytes | -32 768 a +32 767 | Economiser la memoire |
| `long` | 8 bytes | Tres grand | Grands nombres |
| `unsigned int` | 4 bytes | 0 a ~4 milliards | Jamais negatif |

### Types decimaux

| Type | Taille | Precision | Usage |
|---|---|---|---|
| `float` | 4 bytes | ~7 chiffres | Quand la precision importe peu |
| `double` | 8 bytes | ~15 chiffres | Calculs financiers, HFT |

### Autres types

| Type | Taille | Valeurs | Usage |
|---|---|---|---|
| `char` | 1 byte | Un caractere ASCII | Caracteres, manipulation binaire |
| `bool` | 1 byte | `true` / `false` | Conditions, flags |
| `string` | variable | Texte | Chaines de caracteres (necessite `<string>`) |

---

## Declaration vs Initialisation

```cpp
int age;           // Declaration : la boite existe, mais contient n'importe quoi (dangereux !)
int age = 25;      // Declaration + Initialisation : la boite existe ET contient 25
int age{25};       // Initialisation uniforme (C++11) : plus stricte, recommandee
```

**Regle d'or** : Toujours initialiser tes variables. Une variable non initialisee contient
des donnees aleatoires (residus en memoire). C'est un bug classique et une faille de securite.

---

## sizeof() : connaitre la taille en memoire

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "int    : " << sizeof(int)    << " bytes" << endl;  // 4
    cout << "double : " << sizeof(double) << " bytes" << endl;  // 8
    cout << "char   : " << sizeof(char)   << " bytes" << endl;  // 1
    cout << "bool   : " << sizeof(bool)   << " bytes" << endl;  // 1
    cout << "float  : " << sizeof(float)  << " bytes" << endl;  // 4
    cout << "long   : " << sizeof(long)   << " bytes" << endl;  // 8

    // Fonctionne aussi sur des variables
    int x = 42;
    cout << "x      : " << sizeof(x) << " bytes" << endl;      // 4

    return 0;
}
```

---

## Exemple complet

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Types entiers
    int age = 25;
    unsigned int nb_connexions = 1042;

    // Types decimaux
    double prix_btc = 67234.56;
    float ratio = 3.14f;          // Le 'f' indique un float (pas double)

    // Caractere et booleen
    char grade = 'A';             // Guillemets SIMPLES pour char
    bool est_admin = true;

    // Chaine de caracteres
    string pseudo = "h4ck3r_01";  // Guillemets DOUBLES pour string

    // Affichage
    cout << "Age          : " << age << endl;
    cout << "Connexions   : " << nb_connexions << endl;
    cout << "Prix BTC     : " << prix_btc << endl;
    cout << "Ratio        : " << ratio << endl;
    cout << "Grade        : " << grade << endl;
    cout << "Admin        : " << est_admin << endl;  // Affiche 1 (true) ou 0 (false)
    cout << "Pseudo       : " << pseudo << endl;

    return 0;
}
```

---

## Checkpoint ✅

1. **Quelle est la difference entre `float` et `double` ?**
   > `float` = 4 bytes, ~7 chiffres de precision. `double` = 8 bytes, ~15 chiffres. En finance/HFT, on utilise `double` pour la precision.

2. **Pourquoi faut-il TOUJOURS initialiser ses variables ?**
   > Une variable non initialisee contient des donnees aleatoires (residus memoire). Ca cause des bugs imprevisibles et des failles de securite.

3. **Que retourne `sizeof(int)` et pourquoi c'est utile ?**
   > Retourne 4 (bytes sur la plupart des systemes). C'est utile pour comprendre l'empreinte memoire, calculer des offsets, et en programmation bas niveau.

---

Passe aux exercices dans `exercise.cpp`. 👊
