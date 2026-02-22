# Chapitre 08 - Polymorphisme et Fonctions Virtual 🎭

## Concept fondamental 

Le **polymorphisme** permet d'appeler la bonne methode selon le type reel de l'objet, meme a travers un pointeur ou une reference vers la classe de base. C'est rendu possible par le mot-cle `virtual`.

## Le probleme sans virtual 

```cpp
class Animal {
public:
    void parler() { std::cout << "..." << std::endl; }
};

class Chien : public Animal {
public:
    void parler() { std::cout << "Woof!" << std::endl; }
};

Animal* a = new Chien();
a->parler();   // Affiche "..." et PAS "Woof!" -> MAUVAIS
```

## La solution : virtual 

```cpp
class Animal {
public:
    virtual void parler() { std::cout << "..." << std::endl; }
    virtual ~Animal() = default;   // Destructeur virtuel OBLIGATOIRE
};

class Chien : public Animal {
public:
    void parler() override { std::cout << "Woof!" << std::endl; }
};

Animal* a = new Chien();
a->parler();   // Affiche "Woof!" -> CORRECT (late binding)
```

## Comment ca marche : vtable et vptr 

```
Chaque classe avec virtual a une vtable (table de fonctions virtuelles).
Chaque objet a un vptr (pointeur cache vers la vtable de sa classe).

Objet Chien en memoire :
+---------------------------+
| vptr -----> vtable Chien  |     vtable Chien :
| (8 bytes)   +----------+  |     +-------------------+
+-------------|          |--+     | parler() -> Chien::parler  |
| nom         | ....     |       | ~Animal() -> Chien::~Chien |
| (membres)   |          |       +-------------------+
+---------------------------+

Objet Animal en memoire :
+---------------------------+
| vptr -----> vtable Animal |     vtable Animal :
| (8 bytes)                 |     +-------------------+
+---------------------------+     | parler() -> Animal::parler |
| nom                       |     | ~Animal() -> Animal::~Animal|
+---------------------------+     +-------------------+

Quand on fait a->parler() :
1. Lire le vptr de l'objet
2. Chercher parler() dans la vtable
3. Appeler la bonne version -> LATE BINDING
```

## override (C++11) - Securite 

```cpp
class Base {
public:
    virtual void calculer(int x) {}
};

class Derivee : public Base {
public:
    void calculer(int x) override {}    // OK
    // void calculer(double x) override {}  // ERREUR de compilation !
    // Le compilateur detecte que ca ne surcharge rien
};
```

**Toujours** utiliser `override` : le compilateur verifie qu'on surcharge bien une methode virtual de la base.

## final - Interdire la surcharge 🚫

```cpp
class Base {
public:
    virtual void methode() {}
};

class Derivee : public Base {
public:
    void methode() final {}   // Plus personne ne peut surcharger
};

class SousDerivee : public Derivee {
    // void methode() override {}  // ERREUR : methode est final
};
```

## Destructeur virtuel : OBLIGATOIRE 

```cpp
class Base {
public:
    virtual ~Base() = default;   // TOUJOURS si la classe a des methodes virtuelles
};
```

Sans destructeur virtuel, `delete base_ptr` ne detruit pas la partie derivee -> fuite memoire.

## Cout du polymorphisme 

```
Appel normal (compile-time) :     Appel virtual (runtime) :
+----------------------+          +----------------------+
| call Chien::parler   |          | load vptr            |
| (adresse connue)     |          | load vtable[index]   |
+----------------------+          | call indirect         |
                                  +----------------------+
  ~1 ns                             ~3-5 ns (cache miss possible)
```

En HFT, on evite le virtual dans le hot path. En code normal, le cout est negligeable.

## Bonnes pratiques 

1. Si une methode est surchargee dans une derivee : la marquer `virtual` dans la base
2. **Toujours** utiliser `override` dans les classes derivees
3. **Toujours** un destructeur virtuel dans les classes de base polymorphes
4. Utiliser `final` pour optimiser (le compilateur peut devirtualiser)

## Compilation 🔨

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
```
