// Chapitre 05 — Métaprogrammation : Exercices
// Compilation : g++ -std=c++20 -Wall -Wextra -o exercise exercise.cpp

#include <iostream>
#include <type_traits>
#include <array>
#include <cstdint>

// ============================================================
// Exercice 1 : fibonacci constexpr
// Retourne le N-ième nombre de Fibonacci (0-indexé).
// fib(0)=0, fib(1)=1, fib(2)=1, fib(3)=2, ...
// Vérifier avec static_assert que fib(10) == 55.
// ============================================================

// TODO : constexpr int fibonacci(int n) { ... }

// TODO : static_assert(fibonacci(10) == 55, "fib(10) doit etre 55");


// ============================================================
// Exercice 2 : factorial constexpr
// Retourne n! pour n >= 0.
// factorial(0) = 1, factorial(5) = 120.
// Vérifier avec static_assert.
// ============================================================

// TODO : constexpr long long factorial(int n) { ... }

// TODO : static_assert(factorial(5) == 120, "5! = 120");


// ============================================================
// Exercice 3 : if constexpr — serialize()
// Selon le type T :
//   - intégral     : retourner std::to_string(val)
//   - floating_point : retourner std::to_string(val) + "f"
//   - autre         : retourner "[unknown]"
// Utiliser if constexpr, pas SFINAE ni enable_if.
// ============================================================

// TODO :
// template<typename T>
// std::string serialize(T val) {
//     if constexpr (...) { ... }
//     else if constexpr (...) { ... }
//     else { ... }
// }


// ============================================================
// Exercice 4 : std::conditional — choisir le bon type d'index
// Selon un booléen template Wide :
//   - Wide = true  : utiliser int64_t
//   - Wide = false : utiliser int32_t
// Définir un alias Index<Wide> et vérifier les tailles avec static_assert.
// ============================================================

// TODO :
// template<bool Wide>
// using Index = std::conditional_t<..., std::int64_t, std::int32_t>;

// TODO : static_asserts sur les tailles


// ============================================================
// Exercice 5 : table de puissances à la compilation
// Générer à la compilation un std::array<int, N> contenant
// les puissances de 2 : {1, 2, 4, 8, 16, ...}
// Utiliser une constexpr function et std::array.
// ============================================================

// TODO :
// template<std::size_t N>
// constexpr std::array<int, N> powers_of_two() {
//     std::array<int, N> arr{};
//     ...
//     return arr;
// }


// ============================================================
// Tests
// ============================================================

int main() {
    // Test 1
    // std::cout << fibonacci(10) << "\n";   // 55
    // std::cout << fibonacci(15) << "\n";   // 610

    // Test 2
    // std::cout << factorial(5)  << "\n";   // 120
    // std::cout << factorial(10) << "\n";   // 3628800

    // Test 3
    // std::cout << serialize(42)     << "\n";  // "42"
    // std::cout << serialize(3.14)   << "\n";  // "3.140000f"
    // std::cout << serialize("text") << "\n";  // "[unknown]"

    // Test 4
    // Index<true>  big   = 5000000000LL;
    // Index<false> small = 1000;
    // std::cout << big << " " << small << "\n";

    // Test 5
    // constexpr auto table = powers_of_two<8>();
    // for (auto v : table) std::cout << v << " ";
    // std::cout << "\n";  // "1 2 4 8 16 32 64 128"

    std::cout << "Decommentez les tests apres implementation.\n";
    return 0;
}
