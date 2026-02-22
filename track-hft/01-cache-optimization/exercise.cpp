// Chapitre 01 - Cache Optimization
// Compilation: g++ -std=c++17 -O2 -o cache exercise.cpp && ./cache

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>

// =============================================================
// EXERCICE 1 : Reorganiser cette struct pour minimiser le padding
// =============================================================
// TODO: Reorganise les membres pour que sizeof(Order) soit minimal
// Regle: les types plus grands d'abord, les plus petits a la fin
struct Order {
    char side;          // 'B' ou 'S'
    double price;
    short exchange_id;
    int quantity;
    bool is_active;
    long timestamp;
    char symbol[8];
};
// Apres reorganisation, sizeof devrait etre 40 au lieu de 48+

// =============================================================
// EXERCICE 2 : Creer une struct alignee sur une cache line
// =============================================================
// TODO: Utilise alignas pour que cette struct occupe exactement 64 bytes
// Cela evite le false sharing quand plusieurs threads y accedent
struct MarketTick {
    double bid_price;
    double ask_price;
    int bid_size;
    int ask_size;
    long sequence_number;
};

// =============================================================
// EXERCICE 3 : Acces sequentiel vs random
// =============================================================
// TODO: Complete les deux fonctions ci-dessous
// sum_sequential: parcourt le tableau dans l'ordre (index 0, 1, 2, ...)
// sum_random: parcourt le tableau via un tableau d'indices melanges

long long sum_sequential(const std::vector<int>& data) {
    long long sum = 0;
    // TODO: Parcours sequentiel du tableau data
    // Additionne chaque element dans sum
    return sum;
}

long long sum_random(const std::vector<int>& data, const std::vector<int>& indices) {
    long long sum = 0;
    // TODO: Parcours le tableau data en utilisant les indices melanges
    // sum += data[indices[i]] pour chaque i
    return sum;
}

int main() {
    // Test Exercice 1
    std::cout << "=== Exercice 1: Struct Padding ===" << std::endl;
    std::cout << "sizeof(Order) = " << sizeof(Order) << " bytes" << std::endl;
    // Objectif: sizeof <= 40

    // Test Exercice 2
    std::cout << "\n=== Exercice 2: Cache Line Alignment ===" << std::endl;
    std::cout << "sizeof(MarketTick) = " << sizeof(MarketTick) << " bytes" << std::endl;
    std::cout << "alignof(MarketTick) = " << alignof(MarketTick) << std::endl;
    // Objectif: sizeof == 64, alignof == 64

    // Test Exercice 3
    std::cout << "\n=== Exercice 3: Sequential vs Random ===" << std::endl;
    constexpr int N = 10'000'000;
    std::vector<int> data(N);
    for (int i = 0; i < N; i++) data[i] = i;

    // Creer des indices melanges (Fisher-Yates shuffle)
    std::vector<int> indices(N);
    for (int i = 0; i < N; i++) indices[i] = i;
    for (int i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        std::swap(indices[i], indices[j]);
    }

    // Mesurer l'acces sequentiel
    auto start = std::chrono::high_resolution_clock::now();
    long long s1 = sum_sequential(data);
    auto end = std::chrono::high_resolution_clock::now();
    auto seq_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Mesurer l'acces random
    start = std::chrono::high_resolution_clock::now();
    long long s2 = sum_random(data, indices);
    end = std::chrono::high_resolution_clock::now();
    auto rand_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Sequential: " << seq_time << " us (sum=" << s1 << ")" << std::endl;
    std::cout << "Random:     " << rand_time << " us (sum=" << s2 << ")" << std::endl;
    if (seq_time > 0) {
        std::cout << "Ratio:      " << (double)rand_time / seq_time << "x plus lent" << std::endl;
    }

    return 0;
}
