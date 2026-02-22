# Chapitre 09 - Classes Abstraites et Interfaces 🎨

## Concept fondamental 

Une **classe abstraite** est une classe qui ne peut pas etre instanciee. Elle contient au moins une **fonction virtuelle pure** (= 0). Elle sert de contrat : les classes derivees DOIVENT implementer les methodes pures.

## Fonction virtuelle pure 

```cpp
class Forme {
public:
    virtual double aire() const = 0;       // = 0 : pure virtual
    virtual double perimetre() const = 0;  // Les derivees DOIVENT implementer
    virtual ~Forme() = default;
};

// Forme f;  // ERREUR : ne peut pas instancier une classe abstraite
```

## Interface pattern 

En C++, une **interface** est une classe abstraite avec uniquement des methodes pure virtual (pas de donnees) :

```cpp
class ISerializable {     // Convention : prefixe I
public:
    virtual ~ISerializable() = default;
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string& data) = 0;
};

class IComparable {
public:
    virtual ~IComparable() = default;
    virtual int compare_to(const IComparable& other) const = 0;
};
```

## Classe abstraite vs Interface 

```
Classe abstraite                Interface (convention C++)
+------------------------+      +------------------------+
| Peut avoir des membres |      | Pas de membres         |
| Peut avoir des methodes|      | Que des methodes       |
|   implementees         |      |   pure virtual (= 0)   |
| Au moins 1 pure virtual|      | Toutes pure virtual    |
+------------------------+      +------------------------+
  "Base commune avec code"        "Contrat pur"
```

## Implementation concrete 

```cpp
class Cercle : public Forme {
    double rayon;
public:
    explicit Cercle(double r) : rayon(r) {}

    // DOIT implementer TOUTES les methodes pure virtual
    double aire() const override {
        return 3.14159 * rayon * rayon;
    }

    double perimetre() const override {
        return 2 * 3.14159 * rayon;
    }
};
```

Si une derivee n'implemente pas TOUTES les methodes pure virtual, elle est aussi abstraite.

## Pourquoi c'est utile ? 

```
1. CONTRAT : Force les derivees a implementer les methodes critiques
2. POLYMORPHISME : On peut stocker differents types dans un vector<Base*>
3. DECOUPLAGE : Le code client travaille avec l'interface, pas l'implementation
4. TESTABILITE : On peut creer des mocks pour les tests

// Code client ne depend QUE de l'interface
void traiter(const ISerializable& obj) {
    std::string data = obj.serialize();  // Fonctionne avec TOUTE implementation
}
```

## Classe abstraite avec methodes implementees 

```cpp
class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(const std::string& msg) = 0;  // Pure virtual

    // Methode concrete partagee par toutes les derivees
    void info(const std::string& msg)  { log("[INFO] " + msg); }
    void error(const std::string& msg) { log("[ERROR] " + msg); }
};
```

## Bonnes pratiques 

1. Utiliser des interfaces pour definir des **contrats**
2. Prefixer les interfaces par `I` (ISerializable, IComparable)
3. **Toujours** un destructeur virtuel dans les classes abstraites
4. Preferer les classes abstraites aux hierarchies profondes
5. Une classe peut implementer plusieurs interfaces (heritage multiple)

## Compilation 🔨

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
```
