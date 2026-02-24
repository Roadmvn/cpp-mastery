// Chapitre 02 — Challenge : Overload resolution pour types numériques
// Compilation : g++ -std=c++17 -Wall -Wextra -O2 -o challenge challenge.cpp
//
// Contexte : En HFT, on manipule des types numériques variés (int, long, double,
// fixed-point maison). On veut un système qui :
//   1. Traite les entiers avec une arithmétique exacte (pas de FP)
//   2. Traite les flottants avec std::fma() pour la précision
//   3. Refuse à la compilation les types non-numériques
//   4. Expose un type_traits custom "is_hft_numeric"

#include <iostream>
#include <type_traits>
#include <cmath>
#include <string>
#include <vector>

// ============================================================
// Type trait custom : is_hft_numeric
// On considère "HFT numeric" : intégraux + flottants
// Extensible : on peut spécialiser pour un type fixed-point maison
// ============================================================

template<typename T>
struct is_hft_numeric : std::is_arithmetic<T> {};

// Exemple d'extension : un type fixed-point fictif
struct Fixed64 {
    long long value;  // mantissa * 10^8
    explicit Fixed64(long long v) : value(v) {}
};

// On déclare Fixed64 comme numérique HFT
template<>
struct is_hft_numeric<Fixed64> : std::true_type {};

template<typename T>
inline constexpr bool is_hft_numeric_v = is_hft_numeric<T>::value;

// ============================================================
// Trait pour distinguer entier vs flottant dans le contexte HFT
// ============================================================

template<typename T>
inline constexpr bool is_hft_integer_v =
    is_hft_numeric_v<T> && std::is_integral_v<T>;

template<typename T>
inline constexpr bool is_hft_float_v =
    is_hft_numeric_v<T> && std::is_floating_point_v<T>;

// ============================================================
// multiply_add : a * b + c
// - Entiers : calcul exact avec long long
// - Flottants : std::fma() pour precision maximale
// - Fixed64 : calcul fixe
// ============================================================

// Version entière
template<typename T>
std::enable_if_t<is_hft_integer_v<T>, T>
multiply_add(T a, T b, T c) {
    // Promotion en long long pour eviter l'overflow sur les petits types
    return static_cast<T>(static_cast<long long>(a) * b + c);
}

// Version flottante
template<typename T>
std::enable_if_t<is_hft_float_v<T>, T>
multiply_add(T a, T b, T c) {
    return std::fma(a, b, c);  // calcul en une instruction, arrondi unique
}

// Version Fixed64 (dispatch explicite)
Fixed64 multiply_add(Fixed64 a, Fixed64 b, Fixed64 c) {
    // Fixed * Fixed : divise par 10^8 pour rester en echelle
    long long result = (a.value * b.value) / 100000000LL + c.value;
    return Fixed64{result};
}

// ============================================================
// clamp générique : contraint val dans [lo, hi]
// Requis : T doit être HFT numeric (sinon erreur de compilation)
// ============================================================

template<typename T>
std::enable_if_t<is_hft_numeric_v<T>, T>
hft_clamp(T val, T lo, T hi) {
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

// ============================================================
// Affichage générique avec tag dispatch
// ============================================================

struct int_tag {};
struct float_tag {};
struct fixed_tag {};
struct other_tag {};

template<typename T>
auto select_tag() {
    if constexpr (std::is_integral_v<T>)        return int_tag{};
    else if constexpr (std::is_floating_point_v<T>) return float_tag{};
    else if constexpr (std::is_same_v<T, Fixed64>)  return fixed_tag{};
    else                                            return other_tag{};
}

template<typename T>
void print_value(T val, int_tag)   { std::cout << "[int]   " << val << "\n"; }
template<typename T>
void print_value(T val, float_tag) { std::cout << "[float] " << val << "\n"; }
void print_value(Fixed64 val, fixed_tag) {
    std::cout << "[fixed] " << val.value << " (raw)\n";
}
template<typename T>
void print_value(T /*val*/, other_tag) {
    std::cout << "[other] (not numeric)\n";
}

template<typename T>
void describe(T val) {
    print_value(val, select_tag<T>());
}

// ============================================================
// Vérification statique : assert que T est HFT numeric
// ============================================================

template<typename T>
void require_numeric(T val) {
    static_assert(is_hft_numeric_v<T>,
        "require_numeric: T must be an HFT numeric type (integral, floating, or Fixed64)");
    describe(val);
}

// ============================================================
// main
// ============================================================

int main() {
    // multiply_add sur différents types
    std::cout << "=== multiply_add ===\n";
    std::cout << multiply_add(3, 4, 5) << "\n";           // int: 17
    std::cout << multiply_add(3.0, 4.0, 5.0) << "\n";     // double fma: 17.0
    std::cout << multiply_add(3.0f, 4.0f, 5.0f) << "\n";  // float fma: 17.0

    Fixed64 fa{300000000LL};  // 3.0 en fixed point (10^8)
    Fixed64 fb{400000000LL};  // 4.0
    Fixed64 fc{500000000LL};  // 5.0
    Fixed64 result = multiply_add(fa, fb, fc);
    std::cout << "Fixed64 result.value = " << result.value << "\n"; // 1700000000 (17.0)

    // clamp
    std::cout << "\n=== hft_clamp ===\n";
    std::cout << hft_clamp(150, 0, 100) << "\n";       // 100
    std::cout << hft_clamp(-5.0, 0.0, 1.0) << "\n";   // 0.0
    std::cout << hft_clamp(Fixed64{50}.value, 0LL, 100LL) << "\n"; // 50

    // describe avec tag dispatch
    std::cout << "\n=== describe ===\n";
    describe(42);
    describe(3.14);
    describe(Fixed64{12345});

    // require_numeric
    std::cout << "\n=== require_numeric ===\n";
    require_numeric(100);
    require_numeric(2.71828);
    require_numeric(Fixed64{99999});

    // Décommenter pour vérifier l'erreur de compilation statique :
    // require_numeric(std::string("not numeric"));

    std::cout << "\nDone.\n";
    return 0;
}
