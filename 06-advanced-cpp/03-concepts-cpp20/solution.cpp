// Chapitre 03 — Concepts C++20 : Solution
// Compilation : g++ -std=c++20 -Wall -Wextra -o solution solution.cpp

#include <iostream>
#include <concepts>
#include <string>
#include <vector>
#include <list>
#include <cstddef>

// ============================================================
// Exercice 1 : Concept Numeric
// ============================================================

template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<Numeric T>
void describe(T val) {
    std::cout << "numeric: " << val << "\n";
}

// ============================================================
// Exercice 2 : Concept Container
// ============================================================

template<typename T>
concept Container = requires(T c) {
    typename T::value_type;
    { c.begin() } -> std::input_or_output_iterator;
    { c.end() }   -> std::input_or_output_iterator;
    { c.size() }  -> std::convertible_to<std::size_t>;
};

template<Container C>
void print_container(const C& c) {
    std::cout << "[ ";
    for (const auto& elem : c) {
        std::cout << elem << " ";
    }
    std::cout << "] (size=" << c.size() << ")\n";
}

// ============================================================
// Exercice 3 : Concept Comparable
// ============================================================

template<typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
};

template<Comparable T>
T max_of(T a, T b) {
    return (b < a) ? a : b;
}

// ============================================================
// Exercice 4 : requires inline
// ============================================================

template<typename T>
T add(T a, T b) requires requires(T x) { x + x; } {
    return a + b;
}

// ============================================================
// Bonus : concept avec contrainte sur le type de retour
// ============================================================

template<typename T>
concept Stringifiable = requires(T x) {
    { x.to_string() } -> std::convertible_to<std::string>;
};

// Exemple de type qui satisfait Stringifiable
struct Price {
    double value;
    std::string to_string() const {
        return std::to_string(value);
    }
};

template<Stringifiable T>
void print_as_string(const T& x) {
    std::cout << x.to_string() << "\n";
}

// ============================================================
// Tests
// ============================================================

int main() {
    // Test 1 : Numeric
    std::cout << "=== Numeric ===\n";
    describe(42);
    describe(3.14);
    describe('A');    // char est integral
    // describe("hello");  // erreur de compilation

    // Test 2 : Container
    std::cout << "\n=== Container ===\n";
    std::vector<int> v{1, 2, 3, 4, 5};
    print_container(v);

    std::list<std::string> l{"alpha", "beta", "gamma"};
    print_container(l);

    // Test 3 : Comparable
    std::cout << "\n=== Comparable ===\n";
    std::cout << max_of(3, 7) << "\n";
    std::cout << max_of(1.5, 2.5) << "\n";
    std::cout << max_of(std::string("apple"), std::string("banana")) << "\n";

    // Test 4 : add avec requires inline
    std::cout << "\n=== add ===\n";
    std::cout << add(3, 4) << "\n";
    std::cout << add(1.5, 2.5) << "\n";
    std::cout << add(std::string("hello "), std::string("world")) << "\n";

    // Bonus : Stringifiable
    std::cout << "\n=== Stringifiable ===\n";
    print_as_string(Price{142.50});

    return 0;
}
