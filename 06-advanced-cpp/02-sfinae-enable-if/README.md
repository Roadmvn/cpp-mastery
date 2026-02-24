# Chapitre 02 — SFINAE et std::enable_if

## Principe SFINAE

**SFINAE** = Substitution Failure Is Not An Error.

Quand le compilateur tente de substituer les types dans un template et que la substitution
produit du code invalide, il ne génère pas d'erreur : il retire silencieusement ce candidat
de l'overload set.

```cpp
template<typename T>
void process(T x, typename T::value_type* = nullptr) {
    // Uniquement instancié si T a un membre 'value_type'
    // => sélectionné pour std::vector, std::string, etc.
    // => écarté pour int, double, etc. (pas de ::value_type)
}
```

Si aucun candidat ne survit, alors le compilateur génère une erreur.

---

## std::enable_if

`std::enable_if<Condition, Type>::type` :
- Si `Condition` est vraie : définit `::type = Type` (par défaut `void`)
- Si `Condition` est fausse : `::type` n'existe pas => SFINAE s'applique

Trois formes d'utilisation :

```cpp
// Forme 1 : paramètre template par défaut (la plus commune)
template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
void process_int(T val) {
    std::cout << "integer: " << val << "\n";
}

// Forme 2 : type de retour
template<typename T>
std::enable_if_t<std::is_floating_point_v<T>> process_float(T val) {
    std::cout << "float: " << val << "\n";
}

// Forme 3 : paramètre non-type template
template<typename T>
void process(T val, std::enable_if_t<std::is_integral_v<T>>* = nullptr) {
    std::cout << "integer: " << val << "\n";
}
```

---

## Type traits courants

```cpp
#include <type_traits>

std::is_integral_v<T>           // int, long, char, bool...
std::is_floating_point_v<T>     // float, double, long double
std::is_arithmetic_v<T>         // integral || floating_point
std::is_pointer_v<T>            // T*
std::is_reference_v<T>          // T& ou T&&
std::is_same_v<T, U>            // T == U exactement
std::is_base_of_v<Base, Derived>
std::is_convertible_v<From, To>
std::is_trivially_copyable_v<T>
std::remove_const_t<T>          // enlève const
std::remove_reference_t<T>      // enlève & ou &&
std::decay_t<T>                 // remove_ref + remove_cv + array/func decay
```

---

## Tag dispatch

Alternative à `enable_if` : on passe un tag (type vide) pour sélectionner l'overload.

```cpp
struct integral_tag {};
struct float_tag {};

template<typename T>
void process_impl(T val, integral_tag) {
    std::cout << "integer: " << val << "\n";
}

template<typename T>
void process_impl(T val, float_tag) {
    std::cout << "float: " << val << "\n";
}

template<typename T>
void process(T val) {
    using tag = std::conditional_t<
        std::is_integral_v<T>, integral_tag, float_tag
    >;
    process_impl(val, tag{});
}
```

Le tag dispatch est souvent plus lisible que `enable_if` imbriqués.

---

## Limites de SFINAE

SFINAE est puissant mais produit des messages d'erreur difficiles à lire :

```
error: no matching function for call to 'process(std::string)'
note: candidate: 'void process(T, std::enable_if_t<is_integral_v<T>>*)'
note: template argument deduction/substitution failed:
note: 'std::enable_if<false, void>::type' has no member named 'type'
      [avec T = std::string]
```

C++20 résout ce problème avec les **Concepts** (chapitre 03).

---

## Fichiers

| Fichier | Description |
|---------|-------------|
| `exercise.cpp` | Implémenter des fonctions avec enable_if et tag dispatch |
| `solution.cpp` | Solution complète |
| `challenge.cpp` | Overload resolution pour types numériques vs autres |
