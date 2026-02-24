# Chapitre 04 — CRTP : Curiously Recurring Template Pattern

## Principe

Le CRTP est un idiome où une classe de base est templatée sur sa classe dérivée.
Cela permet à la base d'appeler des méthodes de la dérivée **sans virtualité**.

```cpp
template<typename Derived>
class Base {
public:
    void interface() {
        // Appel de la méthode de la dérivée, résolu à la compilation
        static_cast<Derived*>(this)->implementation();
    }
};

class Concrete : public Base<Concrete> {
public:
    void implementation() {
        std::cout << "Concrete::implementation\n";
    }
};
```

---

## Polymorphisme virtuel vs CRTP

```
Polymorphisme virtuel (runtime)         CRTP (compile-time)
---------------------------------       -------------------

class Animal {                          template<typename D>
  virtual void speak() = 0;            class AnimalBase {
};                                        void speak() {
                                            static_cast<D*>(this)->speak_impl();
class Dog : public Animal {               }
  void speak() override {             };
    cout << "Woof";
  }                                    class Dog : public AnimalBase<Dog> {
};                                       void speak_impl() {
                                           cout << "Woof";
Animal* a = new Dog();                   }
a->speak();    // vtable lookup        };
               // ~5ns overhead
                                       Dog d;
                                       d.speak();  // inlined, 0ns overhead

Avantages virtual :                    Avantages CRTP :
- Runtime polymorphism                 - Zero overhead (inlining)
- Pas besoin de connaitre le type      - Meilleure optimisation compilateur
- Collections heterogenes faciles      - Pas d'allocation virtuelle
                                       - Idéal pour HFT / embedded
```

---

## Vtable overhead

```
Objet avec virtual :                   Objet CRTP :
+------------------+                   +------------------+
| vptr ----------->|---+               | data membres     |
| data membres     |   |               +------------------+
+------------------+   |
                        v              Appel : inlined directement
                   +--------+          dans le binaire, pas de
                   | vtable |          déréférencement de pointeur.
                   | [0] ---|-> speak
                   | [1] ---|-> eat
                   +--------+
```

---

## Mixin Pattern

Le CRTP est aussi utilisé pour injecter des comportements dans une classe
sans héritage multiple complexe :

```cpp
// Mixin : donne un opérateur != à partir de ==
template<typename Derived>
struct EqualityComparable {
    bool operator!=(const Derived& other) const {
        return !(static_cast<const Derived&>(*this) == other);
    }
};

// Mixin : donne >, <=, >= à partir de <
template<typename Derived>
struct Comparable : EqualityComparable<Derived> {
    bool operator>(const Derived& other) const {
        return other < static_cast<const Derived&>(*this);
    }
    bool operator<=(const Derived& other) const {
        return !(other < static_cast<const Derived&>(*this));
    }
    bool operator>=(const Derived& other) const {
        return !(static_cast<const Derived&>(*this) < other);
    }
};

class Price : public Comparable<Price> {
    double value_;
public:
    explicit Price(double v) : value_(v) {}
    bool operator<(const Price& other) const { return value_ < other.value_; }
    bool operator==(const Price& other) const { return value_ == other.value_; }
};
// Price hérite automatiquement de >, <=, >=, !=
```

---

## Fichiers

| Fichier | Description |
|---------|-------------|
| `exercise.cpp` | Implémenter un CRTP de base + mixin Comparable |
| `solution.cpp` | Solution complète |
| `challenge.cpp` | Base class pour objets avec compteur de performance (HFT) |
