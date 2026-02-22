// Chapitre 01 - Cache Optimization - CHALLENGE
// Compare acces sequentiel vs random sur un grand array
// avec differentes tailles de stride pour visualiser l'effet du cache
// Compilation: g++ -std=c++17 -O2 -o challenge challenge.cpp && ./challenge

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <iomanip>
#include <cstring>

// Structure compacte, cache-friendly
struct alignas(64) CompactOrder {
    double price;
    int quantity;
    int order_id;
    long timestamp;
    char side;
    char symbol[7];
    // Tout tient dans 1 cache line (64 bytes)
};

// Structure eclatee, cache-hostile
struct SpreadOrder {
    double price;
    char padding1[56];  // force a deborder sur une autre cache line
    int quantity;
    char padding2[60];
    int order_id;
    char padding3[60];
    long timestamp;
    char padding4[56];
    char side;
    char padding5[63];
    char symbol[7];
    char padding6[57];
};

double measure_sequential(const std::vector<int>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    volatile long long sum = 0;
    for (size_t i = 0; i < data.size(); i++) {
        sum += data[i];
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::micro>(end - start).count();
}

double measure_stride(const std::vector<int>& data, int stride) {
    auto start = std::chrono::high_resolution_clock::now();
    volatile long long sum = 0;
    for (size_t i = 0; i < data.size(); i += stride) {
        sum += data[i];
    }
    auto end = std::chrono::high_resolution_clock::now();
    int elements_accessed = data.size() / stride;
    double total_us = std::chrono::duration<double, std::micro>(end - start).count();
    return total_us / elements_accessed * 1e9; // ns par element
}

double measure_random(const std::vector<int>& data, const std::vector<int>& indices) {
    auto start = std::chrono::high_resolution_clock::now();
    volatile long long sum = 0;
    for (size_t i = 0; i < indices.size(); i++) {
        sum += data[indices[i]];
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::micro>(end - start).count();
}

int main() {
    std::cout << "╔══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║     CACHE OPTIMIZATION BENCHMARK 🔥              ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════╝" << std::endl;

    constexpr int N = 16'000'000; // ~64 MB d'ints
    std::vector<int> data(N);
    for (int i = 0; i < N; i++) data[i] = i;

    // === Test 1: Sequentiel vs Random ===
    std::cout << "\n--- Test 1: Sequentiel vs Random Access ---" << std::endl;

    std::mt19937 rng(42);
    std::vector<int> indices(N);
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), rng);

    double seq_us = measure_sequential(data);
    double rand_us = measure_random(data, indices);

    std::cout << std::fixed << std::setprecision(0);
    std::cout << "Sequentiel:  " << seq_us << " us" << std::endl;
    std::cout << "Random:      " << rand_us << " us" << std::endl;
    std::cout << "Ratio:       " << rand_us / seq_us << "x" << std::endl;

    // === Test 2: Stride Access (effet de la cache line) ===
    std::cout << "\n--- Test 2: Cout par element selon le stride ---" << std::endl;
    std::cout << "  Si stride < 16 ints (64 bytes): benefice spatial locality" << std::endl;
    std::cout << "  Si stride >= 16 ints: chaque acces = nouveau cache line load" << std::endl;
    std::cout << std::endl;

    std::cout << std::setw(10) << "Stride" << std::setw(15) << "ns/element" << std::endl;
    std::cout << "  ─────────────────────────" << std::endl;

    for (int stride : {1, 2, 4, 8, 16, 32, 64, 128, 256, 512}) {
        double ns_per = measure_stride(data, stride);
        std::cout << std::setw(10) << stride
                  << std::setw(15) << std::setprecision(1) << ns_per
                  << "  ";
        int bars = std::min(50, (int)(ns_per / 2));
        for (int i = 0; i < bars; i++) std::cout << "█";
        std::cout << std::endl;
    }

    // === Test 3: Compact vs Spread Struct ===
    std::cout << "\n--- Test 3: Compact vs Spread Struct ---" << std::endl;
    constexpr int M = 500'000;

    std::vector<CompactOrder> compact(M);
    for (int i = 0; i < M; i++) {
        compact[i].price = 100.0 + i * 0.01;
        compact[i].quantity = i;
        compact[i].order_id = i;
    }

    std::vector<SpreadOrder> spread(M);
    for (int i = 0; i < M; i++) {
        spread[i].price = 100.0 + i * 0.01;
        spread[i].quantity = i;
        spread[i].order_id = i;
    }

    // Parcours compact
    auto start = std::chrono::high_resolution_clock::now();
    volatile double total = 0;
    for (int i = 0; i < M; i++) {
        total += compact[i].price * compact[i].quantity;
    }
    auto end = std::chrono::high_resolution_clock::now();
    double compact_us = std::chrono::duration<double, std::micro>(end - start).count();

    // Parcours spread
    start = std::chrono::high_resolution_clock::now();
    total = 0;
    for (int i = 0; i < M; i++) {
        total += spread[i].price * spread[i].quantity;
    }
    end = std::chrono::high_resolution_clock::now();
    double spread_us = std::chrono::duration<double, std::micro>(end - start).count();

    std::cout << "sizeof(CompactOrder) = " << sizeof(CompactOrder) << " bytes" << std::endl;
    std::cout << "sizeof(SpreadOrder)  = " << sizeof(SpreadOrder)  << " bytes" << std::endl;
    std::cout << "Compact:  " << std::setprecision(0) << compact_us << " us" << std::endl;
    std::cout << "Spread:   " << spread_us << " us" << std::endl;
    std::cout << "Ratio:    " << std::setprecision(1) << spread_us / compact_us << "x" << std::endl;

    // === Conclusion ===
    std::cout << "\n╔══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  CONCLUSION 📊                                   ║" << std::endl;
    std::cout << "║  - L'acces sequentiel domine grace au prefetch    ║" << std::endl;
    std::cout << "║  - Le stride >= cache line tue la performance     ║" << std::endl;
    std::cout << "║  - Les structs compactes sont critiques en HFT   ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════╝" << std::endl;

    return 0;
}
