# Chapitre 06 - Getters, Setters et Encapsulation 

## Concept fondamental 

L'**encapsulation** est le principe de cacher les details internes d'une classe et de controler l'acces aux donnees via des methodes publiques. Les **getters** lisent, les **setters** modifient avec validation.

## Pourquoi encapsuler ? 

```
SANS encapsulation :             AVEC encapsulation :
+-------------------+            +-------------------+
| class Compte      |            | class Compte      |
| public:           |            | private:          |
|   double solde;   |            |   double solde;   |
+-------------------+            | public:           |
                                 |   double get()    |
compte.solde = -999; // OK       |   void set(val)   |
// Aucune protection !           +-------------------+
                                 // set() verifie val >= 0
```

## Getters (accesseurs) 

```cpp
class Personne {
    std::string nom;
    int age;
public:
    // Getter par valeur (types primitifs)
    int get_age() const { return age; }

    // Getter par const reference (types lourds - evite la copie)
    const std::string& get_nom() const { return nom; }
};
```

Le mot-cle **const** apres la methode garantit qu'elle ne modifie pas l'objet.

## Setters (mutateurs) avec validation 

```cpp
class Personne {
    std::string nom;
    int age;
public:
    void set_age(int a) {
        if (a < 0 || a > 150) {
            std::cerr << "Age invalide: " << a << std::endl;
            return;
        }
        age = a;
    }

    void set_nom(std::string n) {
        if (n.empty()) {
            std::cerr << "Nom vide interdit" << std::endl;
            return;
        }
        nom = std::move(n);
    }
};
```

## Pattern : setter retournant *this (fluent interface) 

```cpp
class Config {
    std::string host;
    int port;
    int timeout;
public:
    Config& set_host(std::string h)  { host = std::move(h); return *this; }
    Config& set_port(int p)          { port = p; return *this; }
    Config& set_timeout(int t)       { timeout = t; return *this; }
};

Config cfg;
cfg.set_host("srv.com").set_port(443).set_timeout(30);  // Chainage
```

## Quand NE PAS utiliser de getters/setters 

Si une classe expose tous ses membres via get/set sans aucune logique, autant utiliser une **struct** :

```cpp
// MAUVAIS : getter/setter inutiles
class Point {
    double x, y;
public:
    double get_x() const { return x; }
    void set_x(double v) { x = v; }
    // Aucune validation, aucune logique -> inutile
};

// MIEUX : utiliser une struct
struct Point {
    double x;
    double y;
};
```

## Bonnes pratiques 

1. Getter = **toujours const**
2. Retourner les types lourds par **const reference**
3. Les setters doivent **valider** les donnees
4. Si aucune validation : utiliser une **struct** directement
5. Nommage : `get_xxx()` / `set_xxx()` ou `xxx()` / `set_xxx()`

## Compilation 🔨

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
```
