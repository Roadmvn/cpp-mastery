# Conversion de Types 🔄

## Pourquoi c'est important

En HFT, melanger des `int` et des `double` dans un calcul de prix peut silencieusement
tronquer tes resultats. Une perte de precision sur un prix a 6 decimales et ton algo
prend la mauvaise decision. En offensive, convertir entre types c'est le quotidien :
caster un `void*` en `char*` pour lire de la memoire brute, convertir des octets en
adresses, manipuler des buffers. Si tu maitrises pas les conversions, tu maitrises rien.

---

## Conversion implicite (automatique)

Le compilateur convertit automatiquement quand les types sont differents dans une expression.
La regle : le type le plus "petit" est promu vers le plus "grand".

```
  Hierarchie de promotion (bas -> haut)
 ┌─────────────────────────────────────┐
 │  long double                        │  <- Plus precis
 │  double                             │
 │  float                              │
 │  unsigned long long                 │
 │  long long                          │
 │  unsigned long                      │
 │  long                               │
 │  unsigned int                       │
 │  int                                │  <- Plus petit
 └─────────────────────────────────────┘
   Le petit monte vers le grand
```

```cpp
int a = 5;
double b = 2.5;
double c = a + b;  // 'a' est promu en double automatiquement -> 7.5

int x = 10;
double y = x;     // Promotion implicite : 10 -> 10.0 (aucune perte)
```

---

## Narrowing -- La perte silencieuse

Le probleme arrive quand tu vas du grand vers le petit. C'est du **narrowing** :
le compilateur coupe ce qui depasse, sans avertir (ou juste un warning).

```
  double 3.99
     │
     ▼  narrowing (troncation)
  int 3          <- Les decimales sont perdues !

  int 300
     │
     ▼  narrowing (overflow)
  char 44        <- 300 ne tient pas dans un char (max 127)
```

```cpp
double price = 3.99;
int rounded = price;          // 3 (PAS 4 -- c'est tronque, pas arrondi)

int big = 100000;
short small = big;            // Valeur imprevisible si big > 32767

long long huge = 9999999999;
int lost = huge;              // Overflow : valeur corrompue
```

---

## Conversion explicite -- static_cast

`static_cast<type>(valeur)` est la facon propre de convertir en C++.
Ca rend l'intention explicite et le compilateur verifie que la conversion a du sens.

```cpp
// Division reelle : on force la conversion
int a = 7, b = 2;
double result = static_cast<double>(a) / b;  // 3.5

// Conversion deliberee avec perte acceptee
double price = 42.87;
int price_int = static_cast<int>(price);      // 42 (perte voulue)

// Conversion de char en int (code ASCII)
char lettre = 'A';
int ascii = static_cast<int>(lettre);          // 65
```

### Pourquoi pas le cast C ?

```cpp
// Cast style C -- a eviter en C++ moderne
int x = (int)3.14;          // Marche mais pas de verification
int y = (int)some_pointer;  // Dangereux : compile sans broncher

// static_cast -- prefere
int x = static_cast<int>(3.14);  // Explicite, verifie a la compilation
```

Le cast C `(type)value` est une massue : il force la conversion sans rien verifier.
`static_cast` est un scalpel : il verifie que la conversion est logique.

---

## Exemple complet commente

```cpp
#include <iostream>

int main() {
    // Promotion implicite : int -> double (safe)
    int quantity = 150;
    double price = 42.75;
    double total = quantity * price;  // quantity promu en double
    std::cout << "Total : " << total << std::endl;

    // Narrowing dangereux : double -> int (perte)
    double avg = 14.7;
    int avg_int = avg;  // 14, pas 15 -- troncation !
    std::cout << "Moyenne tronquee : " << avg_int << std::endl;

    // static_cast pour division correcte
    int notes_total = 267;
    int nb_notes = 5;
    double moyenne = static_cast<double>(notes_total) / nb_notes;
    std::cout << "Moyenne reelle : " << moyenne << std::endl;  // 53.4

    // Conversion char <-> int
    char c = 'Z';
    int code = static_cast<int>(c);
    std::cout << c << " = ASCII " << code << std::endl;  // Z = ASCII 90

    char back = static_cast<char>(65);
    std::cout << "ASCII 65 = " << back << std::endl;  // A

    return 0;
}
```

---

## Checkpoint ✅

1. **Que vaut `int x = 9.7;` ?**
   > `x = 9`. Conversion implicite double -> int, la partie decimale est tronquee (pas arrondie).

2. **Pourquoi utiliser `static_cast` au lieu du cast C `(int)val` ?**
   > `static_cast` est verifie a la compilation : si la conversion n'a pas de sens, le compilateur refuse. Le cast C force tout sans verification, meme les conversions dangereuses.

3. **Comment forcer une division reelle entre deux int `a` et `b` ?**
   > `static_cast<double>(a) / b` -- on convertit explicitement un des operandes en `double` avant la division.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret.
