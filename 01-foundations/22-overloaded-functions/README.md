# Fonctions Surchargees (Overloading) 🔀

## Pourquoi c'est important

La surcharge de fonctions permet d'avoir plusieurs fonctions avec le MEME nom mais des
signatures differentes (types ou nombre de parametres differents).
En HFT, tu veux une seule fonction `format()` qui marche avec des prix, des volumes, des timestamps.
Ca rend l'API propre et intuitive.

---

## Principe

Le compilateur choisit la bonne version de la fonction en fonction des arguments :

```cpp
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

string add(string a, string b) {
    return a + b;
}

// Le compilateur sait laquelle appeler :
add(3, 5);            // Appelle la version int
add(3.14, 2.71);      // Appelle la version double
add("Hello", " World"); // Appelle la version string
```

---

## Regles de surcharge

Ce qui DIFFERENCIE les fonctions surchargees :

```
  VALIDE (signatures differentes) :
  ├── Nombre de parametres different
  │   int area(int side);
  │   int area(int width, int height);
  │
  ├── Types de parametres differents
  │   void print(int x);
  │   void print(double x);
  │   void print(string x);
  │
  └── Ordre des types different
      void log(int id, string msg);
      void log(string msg, int id);
```

Ce qui NE COMPTE PAS :

```
  INVALIDE (pas une surcharge) :
  ├── Juste le type de retour different
  │   int convert(double x);     // ERREUR !
  │   double convert(double x);  // Meme signature
  │
  └── Juste le nom des parametres different
      void f(int x);    // ERREUR !
      void f(int y);    // Meme signature
```

---

## Exemple pratique : formatage

```cpp
#include <string>
#include <sstream>
#include <iomanip>

string format(int value) {
    return to_string(value);
}

string format(double value, int decimals) {
    ostringstream oss;
    oss << fixed << setprecision(decimals) << value;
    return oss.str();
}

string format(string label, double value) {
    return label + ": " + format(value, 2);
}

// Utilisation
format(42);                  // "42"
format(3.14159, 2);          // "3.14"
format("Prix", 150.258);    // "Prix: 150.26"
```

---

## Attention aux ambiguites 

```cpp
void f(int x);
void f(double x);

f(5);      // OK -> int
f(5.0);    // OK -> double
f(5.0f);   // OK -> float converti en double
f('A');    // Ambigu ? Non, char -> int (promotion implicite)
```

Si le compilateur ne peut pas decider, il te donnera une erreur d'ambiguite.

---

## Checkpoint 

1. **Qu'est-ce que la surcharge de fonctions ?**
   > Plusieurs fonctions avec le meme nom mais des signatures differentes (types/nombre de parametres).

2. **Le type de retour seul suffit-il pour surcharger ?**
   > Non. Le type de retour ne fait pas partie de la signature pour la surcharge.

3. **Comment le compilateur choisit-il la bonne fonction ?**
   > Il regarde le nombre et le type des arguments passes a l'appel et choisit la meilleure correspondance.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret. 
