// Chapitre 01 — Variadic Templates : Solution
// Compilation : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp

#include <iostream>
#include <string>
#include <sstream>

// ============================================================
// Exercice 1 : sum() avec fold expression
// ============================================================

template<typename... Ts>
auto sum(Ts... args) {
    return (... + args);  // unary left fold sur '+'
}

// ============================================================
// Exercice 2 : print_all()
// ============================================================

template<typename... Ts>
void print_all(Ts... args) {
    // Binary fold : on insere un espace avant chaque arg sauf le premier
    // Technique : fold sur << avec initializer d'espace conditionnel
    std::size_t i = 0;
    ((std::cout << (i++ ? " " : "") << args), ...);
    std::cout << "\n";
}

// ============================================================
// Exercice 3 : count_args()
// ============================================================

template<typename... Ts>
constexpr std::size_t count_args(Ts...) {
    return sizeof...(Ts);
}

// ============================================================
// Exercice 4 : to_string_all()
// ============================================================

template<typename... Ts>
std::string to_string_all(Ts... args) {
    std::ostringstream oss;
    (oss << ... << args);  // binary left fold sur <<
    return oss.str();
}

// ============================================================
// Exercice 5 : récursion explicite (compatible C++11)
// ============================================================

// Cas de base : pack vide
void print_recursive() {
    std::cout << "\n";
}

// Cas récursif : traite le premier, récurse sur le reste
template<typename First, typename... Rest>
void print_recursive(First first, Rest... rest) {
    std::cout << first << "\n";
    print_recursive(rest...);
}

// ============================================================
// Tests
// ============================================================

int main() {
    // Test 1 : sum
    auto s = sum(1, 2, 3, 4, 5);
    std::cout << "sum(1,2,3,4,5) = " << s << "\n";  // 15

    auto sf = sum(1.5, 2.5, 3.0);
    std::cout << "sum(1.5,2.5,3.0) = " << sf << "\n";  // 7.0

    // Test 2 : print_all
    print_all(42, 3.14, "world");       // "42 3.14 world"
    print_all("only one");              // "only one"

    // Test 3 : count_args
    std::cout << "count_args(1,2,3) = " << count_args(1, 2, 3) << "\n";  // 3
    std::cout << "count_args() = " << count_args() << "\n";              // 0

    // Test 4 : to_string_all
    std::string s2 = to_string_all("Order", 42, " qty=", 100);
    std::cout << s2 << "\n";  // "Order42 qty=100"

    // Test 5 : récursion
    print_recursive(1, "two", 3.0);

    return 0;
}
