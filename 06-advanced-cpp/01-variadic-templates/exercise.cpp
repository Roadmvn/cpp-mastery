// Chapitre 01 — Variadic Templates : Exercices
// Compilation : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp

#include <iostream>
#include <string>
#include <sstream>

// ============================================================
// Exercice 1 : Fonction sum()
// Retourne la somme de tous les arguments (fold expression C++17)
// Doit fonctionner avec int, double, ou un mélange.
// ============================================================

// TODO : implémenter sum() avec un fold expression
// template<typename... Ts>
// auto sum(Ts... args) { ... }


// ============================================================
// Exercice 2 : Fonction print_all()
// Affiche tous les arguments séparés par des espaces, suivi d'un '\n'
// Exemple : print_all(1, 2.5, "hello") => "1 2.5 hello\n"
// ============================================================

// TODO : implémenter print_all() avec un fold expression
// template<typename... Ts>
// void print_all(Ts... args) { ... }


// ============================================================
// Exercice 3 : Fonction count_args()
// Retourne le nombre d'arguments (sans les afficher)
// ============================================================

// TODO : implémenter count_args() avec sizeof...
// template<typename... Ts>
// constexpr std::size_t count_args(Ts...) { ... }


// ============================================================
// Exercice 4 : Fonction to_string_all()
// Concatène tous les arguments en une std::string
// Utiliser std::ostringstream
// ============================================================

// TODO : implémenter to_string_all()
// template<typename... Ts>
// std::string to_string_all(Ts... args) { ... }


// ============================================================
// Exercice 5 : Récursion explicite (sans fold)
// Implémenter print_recursive() qui affiche chaque arg sur une ligne
// Version C++11 compatible (pas de fold expressions)
// ============================================================

// TODO : cas de base
// void print_recursive() { std::cout << "\n"; }

// TODO : cas récursif
// template<typename First, typename... Rest>
// void print_recursive(First first, Rest... rest) { ... }


// ============================================================
// Tests — ne pas modifier
// ============================================================

int main() {
    // Test 1
    // auto s = sum(1, 2, 3, 4, 5);
    // std::cout << "sum(1,2,3,4,5) = " << s << "\n";  // attendu : 15

    // Test 2
    // print_all(42, 3.14, "world");  // attendu : "42 3.14 world\n"

    // Test 3
    // std::cout << count_args(1, 2, 3) << "\n";  // attendu : 3
    // std::cout << count_args() << "\n";          // attendu : 0

    // Test 4
    // std::string s2 = to_string_all("Order", 42, " qty=", 100);
    // std::cout << s2 << "\n";  // attendu : "Order42 qty=100"

    // Test 5
    // print_recursive(1, "two", 3.0);

    std::cout << "Decommentez les tests apres avoir implemente les fonctions.\n";
    return 0;
}
