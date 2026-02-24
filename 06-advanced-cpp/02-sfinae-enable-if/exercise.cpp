// Chapitre 02 — SFINAE / enable_if : Exercices
// Compilation : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// ============================================================
// Exercice 1 : Deux overloads de describe()
// - Si T est intégral : afficher "integer: <val>"
// - Si T est flottant : afficher "float: <val>"
// Utiliser std::enable_if_t comme paramètre template par défaut
// ============================================================

// TODO : version pour types intégraux
// template<typename T, typename = ...>
// void describe(T val) { ... }

// TODO : version pour types flottants
// template<typename T, typename = ...>
// void describe(T val) { ... }


// ============================================================
// Exercice 2 : Fonction serialize()
// - Si T est arithmetic (int, float, etc.) : retourner to_string(val)
// - Sinon : retourner "[non-numeric]"
// Utiliser le type de retour avec enable_if
// ============================================================

// TODO : version arithmetic
// template<typename T>
// std::enable_if_t<..., std::string> serialize(T val) { ... }

// TODO : version non-arithmetic
// template<typename T>
// std::enable_if_t<..., std::string> serialize(T val) { ... }


// ============================================================
// Exercice 3 : Tag dispatch pour safe_divide()
// - Pour les types intégraux : division entière, vérifier division par zéro
// - Pour les types flottants : division normale (0.0 donne inf/nan, c'est ok)
// Créer deux tags et dispatcher depuis safe_divide()
// ============================================================

// TODO : tags
// struct int_tag {};
// struct float_tag {};

// TODO : implémentations
// template<typename T>
// T safe_divide_impl(T a, T b, int_tag) { ... }

// template<typename T>
// T safe_divide_impl(T a, T b, float_tag) { ... }

// TODO : dispatcher
// template<typename T>
// T safe_divide(T a, T b) { ... }


// ============================================================
// Exercice 4 : has_size<T>
// Type trait custom : vrai si T a un membre .size()
// Utiliser decltype + SFINAE (void_t ou enable_if)
// ============================================================

// TODO : template primaire (faux par défaut)
// template<typename T, typename = void>
// struct has_size : std::false_type {};

// TODO : spécialisation pour les types qui ont .size()
// template<typename T>
// struct has_size<T, std::void_t<decltype(std::declval<T>().size())>>
//     : std::true_type {};

// Helper
// template<typename T>
// inline constexpr bool has_size_v = has_size<T>::value;


// ============================================================
// Tests — décommenter après implémentation
// ============================================================

int main() {
    // Test 1
    // describe(42);        // "integer: 42"
    // describe(3.14);      // "float: 3.14"
    // describe(100L);      // "integer: 100"

    // Test 2
    // std::cout << serialize(42) << "\n";         // "42"
    // std::cout << serialize(3.14f) << "\n";      // "3.140000"
    // std::cout << serialize(std::string("x")) << "\n";  // "[non-numeric]"

    // Test 3
    // std::cout << safe_divide(10, 3) << "\n";    // 3
    // std::cout << safe_divide(10.0, 3.0) << "\n"; // 3.333...
    // safe_divide(5, 0);  // doit afficher une erreur et retourner 0

    // Test 4
    // std::cout << has_size_v<std::vector<int>> << "\n"; // 1
    // std::cout << has_size_v<std::string> << "\n";      // 1
    // std::cout << has_size_v<int> << "\n";              // 0

    std::cout << "Decommentez les tests apres implementation.\n";
    return 0;
}
