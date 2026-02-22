# Chapitre 05 - Surcharge de Constructeurs (Constructor Overloading) 🔀

## Concept fondamental 🎯

La **surcharge de constructeurs** permet de creer un objet de differentes manieres. Chaque constructeur a une signature differente (nombre ou type de parametres).

## Multiples constructeurs 📝

```cpp
class Couleur {
    int r, g, b;
public:
    Couleur() : r(0), g(0), b(0) {}                      // Noir
    Couleur(int gris) : r(gris), g(gris), b(gris) {}     // Niveaux de gris
    Couleur(int r, int g, int b) : r(r), g(g), b(b) {}   // RGB complet
};

Couleur noir;            // Couleur()
Couleur gris(128);       // Couleur(int)
Couleur rouge(255,0,0);  // Couleur(int,int,int)
```

## Delegation de constructeurs (C++11) 🔗

Un constructeur peut appeler un autre constructeur de la meme classe :

```cpp
class Connexion {
    std::string host;
    int port;
    int timeout;

public:
    // Constructeur principal
    Connexion(std::string h, int p, int t)
        : host(std::move(h)), port(p), timeout(t) {}

    // Delegation vers le principal
    Connexion(std::string h, int p)
        : Connexion(std::move(h), p, 30) {}      // timeout defaut 30s

    Connexion(std::string h)
        : Connexion(std::move(h), 80, 30) {}      // port 80, timeout 30s

    Connexion()
        : Connexion("localhost", 80, 30) {}        // Tout par defaut
};
```

```
Chaine de delegation :
Connexion() --> Connexion("localhost", 80, 30)
                          |
Connexion("srv") -------> Connexion("srv", 80, 30)
                          |
Connexion("srv", 443) --> Connexion("srv", 443, 30)
                          |
                          v
              Constructeur principal (h, p, t)
```

## Constructeur de copie 📋

```cpp
class Buffer {
    int* data;
    size_t size;
public:
    Buffer(size_t n) : data(new int[n]), size(n) {}

    // Constructeur de copie (deep copy)
    Buffer(const Buffer& other) : data(new int[other.size]), size(other.size) {
        std::copy(other.data, other.data + size, data);
    }

    ~Buffer() { delete[] data; }
};

Buffer a(100);
Buffer b(a);    // Appelle le constructeur de copie
Buffer c = a;   // Aussi un appel au constructeur de copie
```

## explicit - Empecher les conversions implicites 🚫

```cpp
class Poids {
    double kg;
public:
    explicit Poids(double k) : kg(k) {}   // explicit = pas de conversion implicite
};

Poids p1(75.0);     // OK
Poids p2 = 75.0;    // ERREUR avec explicit (OK sans)
// void peser(Poids p);
// peser(75.0);      // ERREUR avec explicit (empeche les bugs)
```

## = default et = delete 🛠️

```cpp
class Singleton {
public:
    Singleton() = default;                          // Genere par le compilateur
    Singleton(const Singleton&) = delete;           // Interdit la copie
    Singleton& operator=(const Singleton&) = delete; // Interdit l'affectation
};
```

## Bonnes pratiques 💡

1. Utiliser la **delegation** plutot que dupliquer du code
2. Mettre `explicit` sur les constructeurs a un seul parametre
3. Penser au constructeur de copie si la classe gere des ressources
4. Utiliser `= delete` pour interdire explicitement des operations
5. Le constructeur principal doit etre celui avec le plus de parametres

## Compilation 🔨

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
```
