# Chapitre 07 - Heritage (Inheritance)

## Concept fondamental

L'**heritage** permet a une classe (derivee) d'heriter des attributs et methodes d'une autre classe (base). C'est le mecanisme cle du "is-a" : un Stock **est un** Instrument.

## Syntaxe de base

```cpp
class Animal {              // Classe de base
protected:
    std::string nom;
public:
    Animal(std::string n) : nom(std::move(n)) {}
    void manger() { std::cout << nom << " mange" << std::endl; }
};

class Chien : public Animal {   // Chien herite de Animal
public:
    Chien(std::string n) : Animal(std::move(n)) {}  // Appel constructeur base
    void aboyer() { std::cout << nom << " aboie!" << std::endl; }
};
```

## Hierarchie de classes

```
             ┌──────────────────┐
             │    Instrument    │  <- Classe de base
             │  - symbol        │
             │  - price         │
             │  + get_symbol()  │
             └──────────────────┘
                /      |      \
               /       |       \
    ┌──────────┐  ┌──────────┐  ┌──────────┐
    │  Stock   │  │   Bond   │  │  Future  │  <- Classes derivees
    │ - shares │  │ - coupon │  │ - expiry │
    │ - div    │  │ - yield  │  │ - margin │
    └──────────┘  └──────────┘  └──────────┘
```

## Types d'heritage

```
class Derived : public Base     -> public reste public, protected reste protected
class Derived : protected Base  -> public et protected deviennent protected
class Derived : private Base    -> tout devient private (defaut)
```

```
                 Heritage    Heritage      Heritage
Membre Base      public      protected     private
-----------      -------     ---------     -------
public    ->     public      protected     private
protected ->     protected   protected     private
private   ->     INACCESSIBLE (toujours)
```

En pratique : **presque toujours public**.

## Constructeurs herites

```cpp
class Base {
protected:
    int x;
public:
    Base(int v) : x(v) {}
};

class Derivee : public Base {
    int y;
public:
    // DOIT appeler le constructeur de Base dans la liste d'initialisation
    Derivee(int vx, int vy) : Base(vx), y(vy) {}
};
```

Ordre de construction : **Base d'abord**, puis Derivee.
Ordre de destruction : **Derivee d'abord**, puis Base (inverse).

## Redefinition de methodes (hiding)

```cpp
class Base {
public:
    void saluer() { std::cout << "Bonjour (Base)" << std::endl; }
};

class Derivee : public Base {
public:
    void saluer() {    // Cache la methode de Base (hiding, PAS polymorphisme)
        std::cout << "Bonjour (Derivee)" << std::endl;
    }
};

Derivee d;
d.saluer();          // "Bonjour (Derivee)"
d.Base::saluer();    // "Bonjour (Base)" - acces explicite
```

## protected vs private

- `private` : accessible uniquement dans la classe elle-meme
- `protected` : accessible dans la classe ET ses derivees
- `public` : accessible de partout

## Bonnes pratiques

1. Utiliser l'heritage **public** (sauf raison specifique)
2. Preferer `protected` a `private` pour les membres que les derivees doivent utiliser
3. Toujours appeler le constructeur de Base dans la liste d'initialisation
4. Heritage = relation "is-a" (pas "has-a", pour ca utiliser la composition)
5. Ne pas heriter plus de 2-3 niveaux de profondeur

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
```
