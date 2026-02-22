# Methodes de Strings 🔤

## Pourquoi c'est important

En HFT, tu parses des messages reseau, des ordres de trading, des flux de donnees. Tout arrive sous forme de texte brut.
En Red Team, tu manipules des payloads, des chemins, des commandes. Les strings sont partout.
Maitriser les methodes de `string` c'est obligatoire.

---

## La classe string en C++

En C, les chaines de caracteres c'est des tableaux de `char` termines par `\0`. Galere a manipuler.
En C++, la classe `std::string` encapsule tout ca et te donne des methodes puissantes.

```cpp
#include <string>
using namespace std;

string msg = "Hello";  // Pas besoin de gerer la memoire toi-meme
```

---

## Les methodes essentielles

### length() / size() -- Taille de la chaine

```cpp
string s = "AAPL";
cout << s.length() << endl;  // 4
cout << s.size() << endl;    // 4 (identique)
```

### substr(pos, len) -- Extraire une sous-chaine

```cpp
string s = "8=FIX.4.2";
string version = s.substr(2);     // "FIX.4.2" (depuis position 2)
string fix = s.substr(2, 3);      // "FIX" (3 caracteres depuis pos 2)
```

### find(str) -- Chercher une sous-chaine

```cpp
string s = "Prix:150.25";
size_t pos = s.find(":");       // 4
size_t nope = s.find("XYZ");    // string::npos (pas trouve)

if (pos != string::npos) {
    cout << "Trouve a la position " << pos << endl;
}
```

### replace(pos, len, str) -- Remplacer

```cpp
string s = "Buy AAPL";
s.replace(4, 4, "TSLA");  // "Buy TSLA"
```

### append(str) -- Ajouter a la fin

```cpp
string s = "Order";
s.append(" Sent");     // "Order Sent"
s += " OK";            // "Order Sent OK" (raccourci)
```

### compare(str) -- Comparer

```cpp
string a = "AAPL";
string b = "GOOG";
int result = a.compare(b);  // < 0 car "AAPL" < "GOOG" (ordre alphabetique)
// 0 = egal, < 0 = a avant b, > 0 = a apres b

// Plus simple :
if (a == b) { /* egal */ }
if (a < b)  { /* a avant b */ }
```

### c_str() -- Conversion vers char*

```cpp
string s = "hello.txt";
const char* c = s.c_str();  // Necessaire pour certaines fonctions C
// Utile pour les appels systeme (open, fopen, etc.)
```

### at(index) -- Acces securise

```cpp
string s = "AAPL";
char c = s.at(0);    // 'A' -- verifie les bornes (exception si hors limites)
char d = s[0];       // 'A' -- PAS de verification (plus rapide, mais dangereux)
```

### erase(pos, len) -- Supprimer

```cpp
string s = "Hello World";
s.erase(5, 6);    // "Hello" (supprime 6 chars depuis pos 5)
s.erase(3);        // "Hel" (supprime tout depuis pos 3)
```

### insert(pos, str) -- Inserer

```cpp
string s = "Hello!";
s.insert(5, " World");  // "Hello World!"
```

---

## Schema recapitulatif 📋

```
  string s = "Hello World";

  s.length()      --> 11
  s.substr(6)     --> "World"
  s.find("World") --> 6
  s.at(0)         --> 'H'
  s.erase(5,1)    --> "HelloWorld"
  s.insert(5," ") --> "Hello World"
  s.replace(6,5,"C++") --> "Hello C++"
  s.append("!")   --> "Hello C++!"
  s.c_str()       --> const char*
```

---

## Checkpoint ✅

Avant de passer aux exercices :

1. **Quelle difference entre `at()` et `[]` ?**
   > `at()` verifie les bornes et lance une exception si l'index est invalide. `[]` ne verifie rien, plus rapide mais risque d'acces memoire invalide.

2. **Que retourne `find()` si la sous-chaine n'existe pas ?**
   > `string::npos` (une constante speciale, generalement -1 converti en size_t).

3. **Pourquoi `c_str()` est utile ?**
   > Pour interfacer du code C++ avec des fonctions C qui attendent un `const char*`.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret. 👊
