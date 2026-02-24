// Chapitre 03 — Concepts C++20 : Exercices
// Compilation : g++ -std=c++20 -Wall -Wextra -o exercise exercise.cpp

#include <iostream>
#include <concepts>
#include <string>
#include <vector>
#include <list>

// ============================================================
// Exercice 1 : Concept Numeric
// Définir un concept Numeric qui accepte les types arithmétiques
// (intégraux ET flottants). Utiliser std::integral et std::floating_point.
// ============================================================

// TODO : définir le concept Numeric
// template<typename T>
// concept Numeric = ...;

// TODO : écrire describe(T val) contrainte par Numeric
// Afficher "numeric: <val>"
// template<Numeric T>
// void describe(T val) { ... }


// ============================================================
// Exercice 2 : Concept Container
// Définir un concept Container qui requiert :
//   - T::value_type existe
//   - c.begin() et c.end() sont valides
//   - c.size() est valide et retourne convertible_to std::size_t
// ============================================================

// TODO : définir le concept Container
// template<typename T>
// concept Container = requires(T c) { ... };

// TODO : fonction print_container(const C& c) qui affiche les éléments
// template<Container C>
// void print_container(const C& c) { ... }


// ============================================================
// Exercice 3 : Concept Comparable
// Définir un concept Comparable : T supporte < et ==
// Puis écrire max_of(T a, T b) contrainte par Comparable
// ============================================================

// TODO : concept Comparable
// template<typename T>
// concept Comparable = requires(T a, T b) { ... };

// TODO : max_of
// template<Comparable T>
// T max_of(T a, T b) { ... }


// ============================================================
// Exercice 4 : requires inline
// Sans définir de concept nommé, utiliser requires directement
// dans la signature pour contraindre une fonction add(a, b)
// qui retourne a + b, requérant que a + b soit valide.
// ============================================================

// TODO : add() avec requires inline
// template<typename T>
// T add(T a, T b) requires requires(T x) { x + x; } { ... }


// ============================================================
// Tests
// ============================================================

int main() {
    // Test 1
    // describe(42);         // "numeric: 42"
    // describe(3.14);       // "numeric: 3.14"
    // describe("hello");    // erreur de compilation attendue

    // Test 2
    // std::vector<int> v{1, 2, 3};
    // print_container(v);
    // std::list<std::string> l{"a", "b", "c"};
    // print_container(l);

    // Test 3
    // std::cout << max_of(3, 7) << "\n";         // 7
    // std::cout << max_of(1.5, 2.5) << "\n";     // 2.5
    // std::cout << max_of(std::string("a"), std::string("b")) << "\n"; // "b"

    // Test 4
    // std::cout << add(3, 4) << "\n";     // 7
    // std::cout << add(1.5, 2.5) << "\n"; // 4.0

    std::cout << "Decommentez les tests apres implementation.\n";
    return 0;
}
