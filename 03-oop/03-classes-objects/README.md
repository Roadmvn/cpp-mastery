# Chapitre 03 - Classes et Objets

## Concept fondamental

Une **classe** est un plan (blueprint) qui definit les donnees (attributs) et les comportements (methodes) d'un type. Un **objet** est une instance concrete d'une classe.

## Declaration d'une classe

```cpp
class Compteur {
private:                    // Accessible uniquement depuis la classe
    int valeur;

public:                     // Accessible de partout
    void incrementer() {
        valeur++;
    }

    int get_valeur() const {
        return valeur;
    }
};
```

## Objet en memoire

```
Stack (ou Heap si new)
┌───────────────────────────┐
│  Objet Compteur           │
├───────────────────────────┤
│  [private] int valeur  4B │  <- donnee membre
└───────────────────────────┘

Segment code (partage entre tous les objets Compteur)
┌───────────────────────────┐
│ incrementer()             │
│ get_valeur()              │
└───────────────────────────┘

Les methodes ne sont PAS stockees dans l'objet.
Elles sont dans le segment code.
```

## public / private / protected

```
┌──────────────────┬──────────────────┬──────────────────┐
│     public       │    private       │   protected      │
├──────────────────┼──────────────────┼──────────────────┤
│ Accessible       │ Accessible       │ Accessible       │
│ de PARTOUT       │ UNIQUEMENT       │ depuis la classe │
│                  │ depuis la classe │ ET ses derivees  │
├──────────────────┼──────────────────┼──────────────────┤
│ Interface        │ Implementation   │ Heritage         │
│ utilisateur      │ interne          │ seulement        │
└──────────────────┴──────────────────┴──────────────────┘
```

## Methodes definies hors de la classe

```cpp
class Calculatrice {
private:
    double resultat;

public:
    void additionner(double val);
    void reset();
    double get_resultat() const;
};

// Definition avec l'operateur de resolution de portee ::
void Calculatrice::additionner(double val) {
    resultat += val;
}

void Calculatrice::reset() {
    resultat = 0;
}

double Calculatrice::get_resultat() const {
    return resultat;
}
```

## Le pointeur this

```cpp
class Point {
    double x, y;
public:
    Point& deplacer(double dx, double dy) {
        this->x += dx;   // this pointe vers l'objet courant
        this->y += dy;
        return *this;     // Retourner *this pour le chainage
    }
};

Point p;
p.deplacer(1, 2).deplacer(3, 4);  // Method chaining
```

## const correctness

```cpp
class Cercle {
    double rayon;
public:
    // Methode const : promet de ne pas modifier l'objet
    double aire() const {
        return 3.14159 * rayon * rayon;
    }

    // Methode non-const : peut modifier l'objet
    void agrandir(double facteur) {
        rayon *= facteur;
    }
};
```

## Bonnes pratiques

1. **Tout en private** par defaut, n'exposer que ce qui est necessaire
2. Marquer **const** toutes les methodes qui ne modifient pas l'objet
3. Separer l'interface (public) de l'implementation (private)
4. Un fichier `.h` pour la declaration, un `.cpp` pour la definition

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
```
