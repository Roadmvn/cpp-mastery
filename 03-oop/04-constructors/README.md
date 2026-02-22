# Chapitre 04 - Constructeurs et Destructeurs

## Concept fondamental

Un **constructeur** est une methode speciale appelee automatiquement a la creation d'un objet. Un **destructeur** est appele automatiquement a sa destruction. Ils garantissent qu'un objet est toujours dans un etat valide.

## Types de constructeurs

### Constructeur par defaut

```cpp
class Timer {
    int secondes;
public:
    Timer() : secondes(0) {}   // Constructeur par defaut
};

Timer t;   // Appelle Timer()
```

### Constructeur parametre

```cpp
class Timer {
    int secondes;
public:
    Timer(int s) : secondes(s) {}
};

Timer t(60);      // 60 secondes
Timer t2{120};    // Initialisation uniforme (prefere)
```

### Liste d'initialisation vs corps

```cpp
class Personne {
    std::string nom;
    int age;
public:
    // MAL : affectation dans le corps (double travail)
    Personne(std::string n, int a) {
        nom = n;    // Construit d'abord par defaut, puis affecte
        age = a;
    }

    // BIEN : liste d'initialisation (construction directe)
    Personne(std::string n, int a) : nom(std::move(n)), age(a) {}
};
```

```
Liste d'initialisation       Corps du constructeur
┌──────────────────────┐     ┌──────────────────────┐
│ 1. Construit nom     │     │ 1. Construit nom ""  │
│    directement       │     │ 2. Affecte nom = n   │
│ 2. Construit age     │     │ 3. Construit age 0   │
│    directement       │     │ 4. Affecte age = a   │
└──────────────────────┘     └──────────────────────┘
  1 etape par membre           2 etapes par membre
  = PLUS RAPIDE                = PLUS LENT
```

## La liste d'initialisation est OBLIGATOIRE pour

1. Les membres **const**
2. Les membres **reference** (`&`)
3. Les membres sans constructeur par defaut
4. Les classes de base

```cpp
class Config {
    const int MAX_SIZE;          // const -> obligatoire
    std::string& ref_name;      // reference -> obligatoire

public:
    Config(int max, std::string& name)
        : MAX_SIZE(max), ref_name(name) {}   // Obligatoire ici
};
```

## Destructeur

```cpp
class Fichier {
    FILE* handle;
public:
    Fichier(const char* path) {
        handle = fopen(path, "r");
    }

    ~Fichier() {                // Destructeur : prefixe ~
        if (handle) {
            fclose(handle);     // Liberation automatique
        }
    }
};
// Le fichier est ferme automatiquement quand l'objet sort du scope
```

## Quand les destructeurs sont appeles

```
{
    Fichier f("data.txt");    // Constructeur appele
    // ... utilisation ...
}   // <-- Destructeur appele ICI (sortie du scope)

Fichier* p = new Fichier("x.txt");  // Constructeur
delete p;                             // Destructeur appele par delete
// SANS delete -> FUITE MEMOIRE (utiliser smart pointers)
```

## Valeurs par defaut des membres (C++11)

```cpp
class Serveur {
    std::string host = "localhost";  // Valeur par defaut
    int port = 8080;
    bool debug = false;

public:
    Serveur() = default;                          // Utilise les defauts
    Serveur(std::string h, int p) : host(std::move(h)), port(p) {}
};
```

## Bonnes pratiques

1. **Toujours** utiliser la liste d'initialisation
2. Initialiser les membres dans l'ordre de declaration
3. Utiliser `= default` pour les constructeurs triviaux
4. Les destructeurs doivent etre `noexcept` (par defaut)
5. Preferer les smart pointers pour eviter d'ecrire des destructeurs

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
```
