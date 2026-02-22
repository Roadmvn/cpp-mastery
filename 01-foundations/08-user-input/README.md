# Saisie Utilisateur 

## Pourquoi c'est important

En HFT, meme si les ordres sont automatises, il faut des interfaces pour configurer
les parametres : symbole, prix limite, quantite, seuils de risque. Un champ mal valide
et tu passes un ordre a un prix absurde. En offensive, la saisie c'est la surface
d'attaque numero 1 : buffer overflow, injection de commandes, tout commence par un input
mal gere. Savoir le faire proprement, c'est la base des deux cotes.

---

## cin -- Lecture basique

`std::cin` lit depuis l'entree standard (le clavier). Il s'arrete au premier espace
ou retour a la ligne.

```cpp
int age;
std::cout << "Age : ";
std::cin >> age;  // Lit un entier, s'arrete au premier non-chiffre

double prix;
std::cout << "Prix : ";
std::cin >> prix;  // Lit un double

std::string mot;
std::cout << "Mot : ";
std::cin >> mot;   // Lit UN mot (s'arrete a l'espace)
```

**Piege** : `cin >> mot` lit "Bonjour" si tu tapes "Bonjour le monde". Les mots
suivants restent dans le buffer.

---

## getline -- Lire une ligne entiere

`std::getline(std::cin, variable)` lit tout jusqu'au retour a la ligne.

```cpp
std::string phrase;
std::cout << "Phrase : ";
std::getline(std::cin, phrase);  // Lit toute la ligne, espaces inclus
```

---

## Le piege cin + getline 

```
  Buffer apres cin >> age (tu tapes "25\n")
 ┌─────────────────────────────────┐
 │  cin >> age  lit "25"           │
 │  Il reste '\n' dans le buffer!  │
 │                                 │
 │  getline() lit '\n' -> ""       │  <- Saut de ligne fantome !
 └─────────────────────────────────┘

  Solution : cin.ignore() vide le '\n' restant
 ┌─────────────────────────────────┐
 │  cin >> age;                    │
 │  cin.ignore();   <- mange '\n'  │
 │  getline(cin, nom);  <- OK     │
 └─────────────────────────────────┘
```

```cpp
int age;
std::string nom;

std::cout << "Age : ";
std::cin >> age;

std::cin.ignore();  // Vide le '\n' laisse par cin

std::cout << "Nom complet : ";
std::getline(std::cin, nom);  // Maintenant ca marche
```

---

## Validation basique

Quand `cin` recoit un type inattendu (lettres au lieu de chiffres), il passe en
etat d'erreur. Il faut le detecter et le reinitialiser.

```cpp
int nombre;
std::cout << "Nombre : ";
std::cin >> nombre;

if (std::cin.fail()) {
    std::cout << "Erreur : ce n'est pas un nombre !" << std::endl;
    std::cin.clear();              // Reinitialise l'etat d'erreur
    std::cin.ignore(1000, '\n');   // Vide le buffer jusqu'au '\n'
}
```

---

## Exemple complet commente

```cpp
#include <iostream>
#include <string>

int main() {
    std::string symbole;
    double prix;
    int quantite;

    // Saisie d'un symbole (un mot, pas d'espace)
    std::cout << "Symbole : ";
    std::cin >> symbole;

    // Saisie du prix avec validation
    std::cout << "Prix    : ";
    std::cin >> prix;
    if (std::cin.fail() || prix <= 0) {
        std::cout << "Prix invalide !" << std::endl;
        return 1;
    }

    // Saisie de la quantite
    std::cout << "Quantite: ";
    std::cin >> quantite;
    if (std::cin.fail() || quantite <= 0) {
        std::cout << "Quantite invalide !" << std::endl;
        return 1;
    }

    // Resume
    double total = prix * quantite;
    std::cout << "\n--- Ordre ---" << std::endl;
    std::cout << symbole << " x " << quantite
              << " @ " << prix << " = " << total << " USD" << std::endl;

    return 0;
}
```

Exemple d'execution :
```
Symbole : AAPL
Prix    : 178.50
Quantite: 100
--- Ordre ---
AAPL x 100 @ 178.5 = 17850 USD
```

---

## Checkpoint 

1. **Quelle est la difference entre `cin >>` et `getline()` ?**
   > `cin >>` lit jusqu'au premier espace ou retour a la ligne. `getline()` lit toute la ligne, espaces inclus.

2. **Pourquoi faut-il `cin.ignore()` entre `cin >>` et `getline()` ?**
   > `cin >>` laisse le caractere `\n` dans le buffer. `getline()` le lit immediatement et retourne une chaine vide. `cin.ignore()` supprime ce `\n` residuel.

3. **Comment detecter une saisie invalide (lettre au lieu de nombre) ?**
   > Avec `std::cin.fail()` qui retourne `true` si la derniere lecture a echoue. Ensuite `cin.clear()` reinitialise l'etat et `cin.ignore()` vide le buffer.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret.
