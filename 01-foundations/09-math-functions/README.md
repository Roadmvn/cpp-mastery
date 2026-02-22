# Fonctions Mathematiques 

## Pourquoi c'est important

En HFT, tu calcules des volatilites (racines carrees), des prix d'options (puissances,
exponentielles), des arrondis au tick le plus proche (floor, ceil). Chaque micro-erreur
d'arrondi s'accumule sur des millions de trades. En offensive, tu generes des nombres
aleatoires pour des ports, des IPs, des cles. `rand()` c'est nul pour la crypto, mais
c'est le point de depart pour comprendre le PRNG.

---

## #include <cmath> -- La boite a outils

```
  Fonction         Description                  Exemple
 ┌───────────────┬──────────────────────────┬──────────────────┐
 │ pow(x, y)     │ x puissance y            │ pow(2, 10) = 1024│
 │ sqrt(x)       │ Racine carree            │ sqrt(144) = 12   │
 │ abs(x)        │ Valeur absolue (int)     │ abs(-42) = 42    │
 │ fabs(x)       │ Valeur absolue (double)  │ fabs(-3.14)= 3.14│
 │ round(x)      │ Arrondi au plus proche   │ round(3.5) = 4   │
 │ ceil(x)       │ Arrondi superieur        │ ceil(3.1) = 4    │
 │ floor(x)      │ Arrondi inferieur        │ floor(3.9) = 3   │
 │ fmod(x, y)    │ Modulo flottant          │ fmod(5.5,2)= 1.5 │
 │ log(x)        │ Logarithme naturel       │ log(e) = 1       │
 │ log10(x)      │ Logarithme base 10       │ log10(100) = 2   │
 └───────────────┴──────────────────────────┴──────────────────┘
```

```cpp
#include <cmath>

double x = pow(2, 10);    // 1024
double y = sqrt(144);     // 12
double z = fabs(-3.14);   // 3.14
```

---

## Arrondis -- round, ceil, floor

```
  Valeur    round()    ceil()    floor()
 ┌─────────┬──────────┬─────────┬─────────┐
 │   3.2   │    3     │    4    │    3    │
 │   3.5   │    4     │    4    │    3    │
 │   3.7   │    4     │    4    │    3    │
 │  -2.3   │   -2     │   -2    │   -3    │
 │  -2.7   │   -3     │   -2    │   -3    │
 └─────────┴──────────┴─────────┴─────────┘
```

En HFT, on utilise `floor` pour arrondir un prix au tick inferieur et `ceil` au tick
superieur. Arrondir au mauvais cote = payer plus cher ou ne pas etre execute.

---

## max et min

```cpp
#include <algorithm>  // Pour std::max et std::min

int a = std::max(10, 20);  // 20
int b = std::min(10, 20);  // 10

// Avec des doubles
double c = std::max(3.14, 2.72);  // 3.14
```

---

## Nombres aleatoires -- srand / rand

`rand()` retourne un entier pseudo-aleatoire entre 0 et `RAND_MAX`.
`srand(seed)` initialise le generateur avec une graine.

```
  srand(seed)          rand()          rand()          rand()
 ┌──────────┐      ┌──────────┐    ┌──────────┐    ┌──────────┐
 │ Graine   │ ───> │ Nombre 1 │ -> │ Nombre 2 │ -> │ Nombre 3 │
 │ (seed)   │      │ (pseudo) │    │ (pseudo) │    │ (pseudo) │
 └──────────┘      └──────────┘    └──────────┘    └──────────┘
   Meme seed = memes nombres (deterministe)
```

```cpp
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()

srand(time(0));  // Graine basee sur l'heure actuelle

int r = rand();              // Entier entre 0 et RAND_MAX
int dice = rand() % 6 + 1;  // Entier entre 1 et 6
int port = rand() % 65536;  // Port entre 0 et 65535
```

**Attention** : `rand()` n'est PAS securise. Pour de la crypto ou de la securite,
utilise `<random>` (C++11) ou les APIs systeme. Ici on l'utilise pour apprendre le
concept.

---

## Exemple complet commente

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int main() {
    // Puissance et racine
    double capital = 10000;
    double taux = 0.07;  // 7% par an
    int annees = 10;
    double futur = capital * pow(1 + taux, annees);
    std::cout << "Capital dans " << annees << " ans : " << futur << std::endl;

    // Volatilite (ecart-type simplifie)
    double variance = 0.0256;
    double volatilite = sqrt(variance);
    std::cout << "Volatilite : " << volatilite * 100 << "%" << std::endl;

    // Arrondi au tick (tick = 0.05)
    double prix_brut = 142.873;
    double tick = 0.05;
    double prix_arrondi = floor(prix_brut / tick) * tick;
    std::cout << "Prix arrondi au tick : " << prix_arrondi << std::endl;

    // Min/Max
    double bid = 100.25;
    double ask = 100.30;
    double spread = ask - bid;
    double mid = (std::max(bid, ask) + std::min(bid, ask)) / 2.0;
    std::cout << "Mid price : " << mid << ", Spread : " << spread << std::endl;

    // Aleatoire
    srand(time(0));
    std::cout << "De : " << (rand() % 6 + 1) << std::endl;

    return 0;
}
```

---

## Checkpoint 

1. **Quelle est la difference entre `round(3.5)`, `ceil(3.5)` et `floor(3.5)` ?**
   > `round(3.5) = 4` (au plus proche), `ceil(3.5) = 4` (superieur), `floor(3.5) = 3` (inferieur).

2. **Pourquoi `rand()` n'est-il pas adapte a la securite ?**
   > Parce que c'est un generateur pseudo-aleatoire deterministe. Si tu connais la graine (seed), tu peux predire toute la sequence. Pour la securite, il faut un CSPRNG.

3. **Comment arrondir un prix au tick inferieur de 0.01 ?**
   > `floor(prix / 0.01) * 0.01`. On divise par le tick, on tronque, on remultiplie.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret.
