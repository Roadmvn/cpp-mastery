# Chapitre 03 — Concepts C++20

## Motivation

Avant C++20, contraindre les templates passait par SFINAE, illisible pour le compilateur
et l'utilisateur :

```
SFINAE — message d'erreur typique :
------------------------------------
error: no matching function for call to 'sort(std::string)'
note: candidate: template<class T> void sort(T)
note:   template argument deduction/substitution failed:
note:   in requirements with 'T val' [with T = std::string]:
note:   'enable_if_t<is_arithmetic_v<string>, void>' has no member named 'type'

Concepts — message d'erreur C++20 :
------------------------------------
error: no matching function for call to 'sort(std::string)'
note: constraints not satisfied
note: 'std::string' does not satisfy 'Numeric'
note: 'std::is_arithmetic_v<std::string>' evaluated to false
```

---

## Syntaxe des Concepts

### Définir un concept

```cpp
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<typename T>
concept Container = requires(T c) {
    c.begin();        // T doit avoir begin()
    c.end();          // T doit avoir end()
    c.size();         // T doit avoir size()
    typename T::value_type;  // T doit avoir value_type
};
```

### Utiliser un concept (4 syntaxes équivalentes)

```cpp
// Syntaxe 1 : requires clause après template
template<typename T>
    requires Numeric<T>
void process(T val);

// Syntaxe 2 : requires clause après la signature
template<typename T>
void process(T val) requires Numeric<T>;

// Syntaxe 3 : concept comme paramètre de type (le plus concis)
template<Numeric T>
void process(T val);

// Syntaxe 4 : abbreviated function template (C++20)
void process(Numeric auto val);
```

---

## requires expression

Un `requires expression` évalue une contrainte à la compilation. Il peut contenir
des expressions simples, des type requirements, et des nested requires.

```cpp
template<typename T>
concept Printable = requires(T x) {
    // Expression requirement : doit être valide
    { std::cout << x };

    // Expression requirement avec type de retour
    { x.to_string() } -> std::convertible_to<std::string>;

    // Type requirement
    typename T::value_type;

    // Nested requires
    requires std::is_copy_constructible_v<T>;
};
```

---

## Concepts standard (C++20)

```cpp
#include <concepts>

std::integral<T>            // entier (remplace is_integral_v)
std::floating_point<T>      // flottant
std::arithmetic<T>          // pas standard, mais std::is_arithmetic_v marche
std::signed_integral<T>
std::unsigned_integral<T>
std::same_as<T, U>          // T == U
std::derived_from<D, B>     // D derive de B
std::convertible_to<T, U>   // T -> U
std::common_with<T, U>      // type commun existe
std::totally_ordered<T>     // supporte <, >, ==, etc.
std::copyable<T>
std::movable<T>
std::default_initializable<T>

#include <iterator>
std::input_iterator<It>
std::forward_iterator<It>
std::bidirectional_iterator<It>
std::random_access_iterator<It>

#include <ranges>
std::ranges::range<R>
std::ranges::sized_range<R>
std::ranges::input_range<R>
```

---

## Schéma : SFINAE vs Concepts

```
SFINAE (C++11/14/17)                 Concepts (C++20)
---------------------                ----------------

template<typename T,                 template<Numeric T>
  typename = enable_if_t<            void process(T val);
    is_arithmetic_v<T>>>             // OU
void process(T val);                 void process(Numeric auto val);

Lisibilite : faible                  Lisibilite : excellente
Erreurs : cryptiques                 Erreurs : claires et directes
Surcharge : difficile                Surcharge : naturelle
Introspection : non                  Introspection : requires expression
```

---

## Fichiers

| Fichier | Description |
|---------|-------------|
| `exercise.cpp` | Definir et utiliser des concepts simples |
| `solution.cpp` | Solution complète |
| `challenge.cpp` | Concepts Numeric et Container dans un contexte HFT |
