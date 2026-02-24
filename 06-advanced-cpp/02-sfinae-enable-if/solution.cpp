// Chapitre 02 — SFINAE / enable_if : Solution
// Compilation : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <stdexcept>

// ============================================================
// Exercice 1 : describe() avec enable_if
// ============================================================

template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
void describe(T val) {
    std::cout << "integer: " << val << "\n";
}

// Note : deux templates avec meme signature de base créent une ambiguïté.
// On utilise un deuxième paramètre template dummy différent pour distinguer.
template<typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>, int = 0>
void describe(T val) {
    std::cout << "float: " << val << "\n";
}

// ============================================================
// Exercice 2 : serialize() avec enable_if sur le type de retour
// ============================================================

template<typename T>
std::enable_if_t<std::is_arithmetic_v<T>, std::string>
serialize(T val) {
    return std::to_string(val);
}

template<typename T>
std::enable_if_t<!std::is_arithmetic_v<T>, std::string>
serialize(T /*val*/) {
    return "[non-numeric]";
}

// ============================================================
// Exercice 3 : Tag dispatch pour safe_divide()
// ============================================================

struct int_tag {};
struct float_tag {};

template<typename T>
T safe_divide_impl(T a, T b, int_tag) {
    if (b == 0) {
        std::cerr << "Error: integer division by zero\n";
        return T{0};
    }
    return a / b;
}

template<typename T>
T safe_divide_impl(T a, T b, float_tag) {
    // La division flottante par 0 donne inf/nan — comportement défini
    return a / b;
}

template<typename T>
T safe_divide(T a, T b) {
    using tag = std::conditional_t<std::is_integral_v<T>, int_tag, float_tag>;
    return safe_divide_impl(a, b, tag{});
}

// ============================================================
// Exercice 4 : has_size<T> type trait
// ============================================================

// Cas général : T n'a pas de .size()
template<typename T, typename = void>
struct has_size : std::false_type {};

// Spécialisation : T a .size() (SFINAE via void_t)
template<typename T>
struct has_size<T, std::void_t<decltype(std::declval<T>().size())>>
    : std::true_type {};

template<typename T>
inline constexpr bool has_size_v = has_size<T>::value;

// Utilisation du trait : afficher la taille si disponible
template<typename T>
void print_size_if_available(const T& x) {
    if constexpr (has_size_v<T>) {
        std::cout << "size = " << x.size() << "\n";
    } else {
        std::cout << "no .size() member\n";
    }
}

// ============================================================
// Tests
// ============================================================

int main() {
    // Test 1 : describe
    describe(42);        // integer: 42
    describe(3.14);      // float: 3.14
    describe(100L);      // integer: 100

    // Test 2 : serialize
    std::cout << serialize(42) << "\n";                 // 42
    std::cout << serialize(3.14f) << "\n";              // 3.140000
    std::cout << serialize(std::string("hello")) << "\n"; // [non-numeric]

    // Test 3 : safe_divide
    std::cout << safe_divide(10, 3) << "\n";       // 3
    std::cout << safe_divide(10.0, 3.0) << "\n";   // 3.33333
    safe_divide(5, 0);                             // erreur + retour 0

    // Test 4 : has_size
    std::cout << std::boolalpha;
    std::cout << "vector has size: " << has_size_v<std::vector<int>> << "\n"; // true
    std::cout << "string has size: " << has_size_v<std::string> << "\n";      // true
    std::cout << "int has size: "    << has_size_v<int> << "\n";              // false

    print_size_if_available(std::vector<int>{1, 2, 3});  // size = 3
    print_size_if_available(42);                          // no .size() member

    return 0;
}
