// Chapitre 05 — Métaprogrammation : Solution
// Compilation : g++ -std=c++20 -Wall -Wextra -o solution solution.cpp

#include <iostream>
#include <type_traits>
#include <array>
#include <string>
#include <cstdint>

// ============================================================
// Exercice 1 : fibonacci
// ============================================================

constexpr int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    // Itératif en constexpr pour éviter la récursion exponentielle
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}

static_assert(fibonacci(0)  == 0);
static_assert(fibonacci(1)  == 1);
static_assert(fibonacci(10) == 55);
static_assert(fibonacci(15) == 610);

// ============================================================
// Exercice 2 : factorial
// ============================================================

constexpr long long factorial(int n) {
    if (n <= 0) return 1;
    long long result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

static_assert(factorial(0)  == 1);
static_assert(factorial(5)  == 120);
static_assert(factorial(10) == 3628800);

// ============================================================
// Exercice 3 : serialize avec if constexpr
// ============================================================

template<typename T>
std::string serialize(T val) {
    if constexpr (std::is_integral_v<T>) {
        return std::to_string(val);
    } else if constexpr (std::is_floating_point_v<T>) {
        return std::to_string(val) + "f";
    } else {
        return "[unknown]";
    }
}

// ============================================================
// Exercice 4 : std::conditional pour l'index
// ============================================================

template<bool Wide>
using Index = std::conditional_t<Wide, std::int64_t, std::int32_t>;

static_assert(sizeof(Index<true>)  == 8, "Index<true> doit etre int64_t");
static_assert(sizeof(Index<false>) == 4, "Index<false> doit etre int32_t");

// ============================================================
// Exercice 5 : table de puissances à la compilation
// ============================================================

template<std::size_t N>
constexpr std::array<int, N> powers_of_two() {
    std::array<int, N> arr{};
    int val = 1;
    for (std::size_t i = 0; i < N; ++i) {
        arr[i] = val;
        val *= 2;
    }
    return arr;
}

static_assert(powers_of_two<4>()[0] == 1);
static_assert(powers_of_two<4>()[3] == 8);

// ============================================================
// Bonus : type_traits custom avec if constexpr
// ============================================================

// Retourne une description textuelle du type à la compilation
template<typename T>
constexpr std::string_view type_category() {
    if constexpr (std::is_integral_v<T> && std::is_signed_v<T>)
        return "signed integer";
    else if constexpr (std::is_integral_v<T> && std::is_unsigned_v<T>)
        return "unsigned integer";
    else if constexpr (std::is_floating_point_v<T>)
        return "floating point";
    else if constexpr (std::is_pointer_v<T>)
        return "pointer";
    else
        return "other";
}

// ============================================================
// Tests
// ============================================================

int main() {
    // Test 1 : fibonacci
    std::cout << "=== fibonacci ===\n";
    for (int i = 0; i <= 10; ++i) {
        std::cout << "fib(" << i << ") = " << fibonacci(i) << "\n";
    }

    // Test 2 : factorial
    std::cout << "\n=== factorial ===\n";
    for (int i = 0; i <= 10; ++i) {
        std::cout << i << "! = " << factorial(i) << "\n";
    }

    // Test 3 : serialize
    std::cout << "\n=== serialize ===\n";
    std::cout << serialize(42) << "\n";
    std::cout << serialize(-7L) << "\n";
    std::cout << serialize(3.14) << "\n";
    std::cout << serialize(2.71828f) << "\n";
    std::cout << serialize(std::string("hello")) << "\n";

    // Test 4 : Index
    std::cout << "\n=== Index ===\n";
    Index<true>  big_idx = 5000000000LL;
    Index<false> small_idx = 1000;
    std::cout << "big_idx   = " << big_idx   << " (sizeof=" << sizeof(big_idx) << ")\n";
    std::cout << "small_idx = " << small_idx << " (sizeof=" << sizeof(small_idx) << ")\n";

    // Test 5 : powers of two
    std::cout << "\n=== powers_of_two<10> ===\n";
    constexpr auto table = powers_of_two<10>();
    for (auto v : table) std::cout << v << " ";
    std::cout << "\n";

    // Bonus : type_category
    std::cout << "\n=== type_category ===\n";
    std::cout << "int     : " << type_category<int>() << "\n";
    std::cout << "uint64  : " << type_category<std::uint64_t>() << "\n";
    std::cout << "double  : " << type_category<double>() << "\n";
    std::cout << "int*    : " << type_category<int*>() << "\n";
    std::cout << "string  : " << type_category<std::string>() << "\n";

    return 0;
}
