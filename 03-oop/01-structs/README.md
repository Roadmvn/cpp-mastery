# Chapitre 01 - Les Structures (struct) en C++

## Concept fondamental

Une **struct** est un type de donnees compose qui regroupe plusieurs variables (membres) sous un meme nom. C'est la brique de base de la programmation orientee objet en C++.

## Declaration et utilisation

```cpp
struct Point {
    double x;
    double y;
};

Point p1;          // Declaration (membres non initialises)
p1.x = 3.14;      // Acces avec l'operateur point
p1.y = 2.71;

Point p2 = {1.0, 2.0};   // Initialisation agregate
Point p3{5.0, 10.0};     // Initialisation uniforme (C++11)
```

## Representation en memoire

```
┌──────────────────┐
│ struct Point     │
├──────────────────┤
│ double x  [8B]   │  offset 0
│ double y  [8B]   │  offset 8
└──────────────────┘
  Total: 16 bytes
```

## Struct avec methodes

En C++, contrairement au C, les structs peuvent avoir des methodes :

```cpp
struct Rectangle {
    double largeur;
    double hauteur;

    double aire() const {
        return largeur * hauteur;
    }

    double perimetre() const {
        return 2 * (largeur + hauteur);
    }
};
```

## Struct vs Class - La vraie difference

| Aspect | struct | class |
|--------|--------|-------|
| Acces par defaut | **public** | **private** |
| Heritage par defaut | **public** | **private** |
| Convention | Donnees simples, POD | Logique complexe, encapsulation |

```
struct = class avec tout public par defaut
class  = struct avec tout private par defaut
```

C'est la **seule** difference technique. Le reste est convention.

## Initialisation des membres (C++11)

```cpp
struct Config {
    int port = 8080;           // Valeur par defaut
    std::string host = "localhost";
    bool debug = false;
};

Config c1;           // port=8080, host="localhost", debug=false
Config c2{9090};     // port=9090, host="localhost", debug=false
```

## Struct imbriquees

```cpp
struct Adresse {
    std::string rue;
    std::string ville;
    int code_postal;
};

struct Personne {
    std::string nom;
    int age;
    Adresse adresse;    // Struct dans une struct
};
```

## Passage par reference vs copie

```cpp
void modifier(Point& p) {    // Par reference - modifie l'original
    p.x = 100;
}

void afficher(const Point& p) {  // Par const ref - lecture seule, pas de copie
    std::cout << p.x << ", " << p.y;
}
```

## Bonnes pratiques

1. Utiliser `struct` pour les types simples (donnees groupees)
2. Toujours passer les structs par **const reference** si pas de modification
3. Preferer l'initialisation uniforme `{}` a l'affectation membre par membre
4. Utiliser les valeurs par defaut des membres (C++11+)

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
```
