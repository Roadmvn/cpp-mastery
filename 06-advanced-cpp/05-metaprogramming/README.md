# Chapitre 05 — Métaprogrammation et calcul à la compilation

## constexpr

`constexpr` indique qu'une valeur ou fonction peut être évaluée à la compilation.

```cpp
constexpr int square(int x) { return x * x; }

constexpr int result = square(5);  // calculé à la compilation
int runtime_val = square(n);       // peut aussi s'utiliser au runtime
```

Depuis C++14, les fonctions `constexpr` peuvent contenir des boucles,
des conditions, des variables locales.

---

## if constexpr (C++17)

`if constexpr` permet de brancher le code à la compilation. La branche non prise
n'est pas instanciée, ce qui évite des erreurs de compilation sur du code inapplicable.

```cpp
template<typename T>
void process(T val) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "int: " << val << "\n";
        // Ce bloc n'est PAS instancié si T est double
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "float: " << val << "\n";
    } else {
        std::cout << "other\n";
    }
}
```

Différence avec `if` ordinaire : avec `if constexpr`, les branches
non-sélectionnées ne sont pas compilées pour le type T courant.

---

## std::conditional

Sélection de type à la compilation :

```cpp
// std::conditional<Condition, TypeIfTrue, TypeIfFalse>::type
using storage_t = std::conditional_t<sizeof(T) <= 8, T, T*>;
//                 si T tient en 8 octets   ^---- stocke T   sinon T*

// Exemple concret : choisir entre int32_t et int64_t selon la taille
template<bool Wide>
using Index = std::conditional_t<Wide, std::int64_t, std::int32_t>;

Index<true>  big_idx   = 5000000000LL;  // int64_t
Index<false> small_idx = 1000;          // int32_t
```

---

## Type traits et transformations de types

```cpp
#include <type_traits>

// Transformations
std::remove_const_t<const int>           // => int
std::remove_reference_t<int&>            // => int
std::remove_pointer_t<int*>              // => int
std::add_const_t<int>                    // => const int
std::add_pointer_t<int>                  // => int*
std::decay_t<int(&)[]>                   // => int*
std::make_signed_t<unsigned int>         // => int
std::make_unsigned_t<int>                // => unsigned int

// Compositions courantes
template<typename T>
using bare_t = std::remove_cvref_t<T>;  // C++20 : remove const, volatile, &, &&
```

---

## Calcul compile-time : exemples

```
Fibonacci à la compilation :

  fib(0) = 0
  fib(1) = 1
  fib(n) = fib(n-1) + fib(n-2)

  constexpr int fib(int n) {
      if (n <= 1) return n;
      return fib(n-1) + fib(n-2);
  }

  constexpr auto f10 = fib(10);  // calculé à la compilation : 55
  // static_assert vérifie à la compilation :
  static_assert(f10 == 55);
```

---

## static_assert

Vérifie une condition à la compilation, avec un message clair :

```cpp
static_assert(sizeof(long) == 8, "Need 64-bit long");
static_assert(std::is_trivially_copyable_v<MyStruct>,
              "MyStruct must be trivially copyable for memcpy");

template<typename T>
void store(T val) {
    static_assert(sizeof(T) <= 8, "T too large for fast path");
    // ...
}
```

---

## Fichiers

| Fichier | Description |
|---------|-------------|
| `exercise.cpp` | Implémenter constexpr fibonacci, factorielle, et if constexpr |
| `solution.cpp` | Solution complète |
| `challenge.cpp` | Tables de lookup et sélection de types à la compilation (HFT) |
