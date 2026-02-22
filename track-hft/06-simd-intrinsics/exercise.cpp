// Chapitre 06 - SIMD et Vectorisation - EXERCICE
// Compilation: g++ -std=c++17 -O3 -march=native -o exercise exercise.cpp && ./exercise
//
// OBJECTIF: comprendre comment écrire du code que le compilateur peut vectoriser.
// On n'utilise PAS d'intrinsics directs. On écrit des boucles propres,
// avec bon alignement et sans aliasing, et on mesure le speedup avec -O3.
//
// EXERCICE 1: vectoriser une boucle de multiplication scalaire (prix * facteur)
// EXERCICE 2: calculer le dot product (VWAP: sum(price*vol) / sum(vol))
// EXERCICE 3: comparer les performances scalaire vs optimisé

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <random>
#include <cstring>
#include <cassert>
#include <cmath>
#include <iomanip>

// Alignement pour AVX2 (256 bits = 32 bytes)
constexpr size_t ALIGN = 32;

// ─────────────────────────────────────────────
// Helpers timing
// ─────────────────────────────────────────────

using Clock = std::chrono::high_resolution_clock;

double elapsed_us(Clock::time_point a, Clock::time_point b) {
    return std::chrono::duration<double, std::micro>(b - a).count();
}

// ─────────────────────────────────────────────
// EXERCICE 1 : Scale un array de prix
// ─────────────────────────────────────────────
//
// Applique factor à chaque prix: out[i] = in[i] * factor
//
// Version SCALAIRE (référence - le compilateur peut ne pas vectoriser)
void scale_prices_scalar(const double* in, double* out, int n, double factor) {
    // TODO: boucle simple, pas d'optimisation particulière
    for (int i = 0; i < n; i++) {
        // TODO
    }
}

// Version OPTIMISÉE (boucle que le compilateur PEUT vectoriser)
// Règles: pas d'alias (in != out), alignement, N multiple de 4
void scale_prices_opt(const double* __restrict__ in,
                      double* __restrict__ out,
                      int n, double factor) {
    // TODO: même logique, mais avec __restrict__ et potentiellement
    // un unrolling manuel par 4 pour aider le compilateur
    for (int i = 0; i < n; i++) {
        // TODO
    }
}

// ─────────────────────────────────────────────
// EXERCICE 2 : VWAP - Volume Weighted Average Price
// ─────────────────────────────────────────────
//
// VWAP = sum(price[i] * vol[i]) / sum(vol[i])
//
// Schema:
//
//   prices:  [100.1] [99.8] [100.3] [100.0] ...
//   volumes: [  500] [ 200] [  800] [  300] ...
//             ×        ×       ×       ×
//   contrib: [50050] [19960] [80240] [30000] ...
//             ──────────────────────────────
//   sum_pv = 180250
//   sum_v  = 1800
//   VWAP   = 100.139

double compute_vwap(const double* prices, const int* volumes, int n) {
    // TODO: calculer VWAP avec deux accumulateurs double
    // (utiliser des accumulateurs séparés pour pv et v pour aider la vectorisation)
    double sum_pv = 0.0;
    double sum_v  = 0.0;

    // TODO: boucle sur n
    for (int i = 0; i < n; i++) {
        // TODO
    }

    return (sum_v > 0.0) ? sum_pv / sum_v : 0.0;
}

// ─────────────────────────────────────────────
// EXERCICE 3 : Min/Max/Mean sur array
// ─────────────────────────────────────────────
//
// Calculer en une seule passe: min, max, mean
// Astuce: utiliser des variables min/max locales (register-friendly)

struct Stats {
    double min_val;
    double max_val;
    double mean;
};

Stats compute_stats(const double* data, int n) {
    if (n == 0) return {0.0, 0.0, 0.0};

    // TODO: initialiser min = max = data[0], sum = 0.0
    double min_val = data[0];
    double max_val = data[0];
    double sum     = 0.0;

    // TODO: boucle optimisée (pas de branchement sur min/max  utiliser std::min/max)
    for (int i = 0; i < n; i++) {
        // TODO
    }

    return {min_val, max_val, sum / n};
}

// ─────────────────────────────────────────────
// Benchmark helper
// ─────────────────────────────────────────────

void benchmark_scale(int N) {
    // Allouer avec alignement
    std::vector<double> in(N, 0.0), out_scalar(N), out_opt(N);
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(99.0, 101.0);
    for (auto& v : in) v = dist(rng);

    constexpr int REPS = 100;
    double factor = 1.0001;

    // Scalaire
    auto t0 = Clock::now();
    for (int r = 0; r < REPS; r++)
        scale_prices_scalar(in.data(), out_scalar.data(), N, factor);
    auto t1 = Clock::now();
    double scalar_us = elapsed_us(t0, t1) / REPS;

    // Optimisé
    auto t2 = Clock::now();
    for (int r = 0; r < REPS; r++)
        scale_prices_opt(in.data(), out_opt.data(), N, factor);
    auto t3 = Clock::now();
    double opt_us = elapsed_us(t2, t3) / REPS;

    // Vérification
    for (int i = 0; i < N; i++)
        assert(std::abs(out_scalar[i] - out_opt[i]) < 1e-9);

    std::cout << "  Scalaire : " << std::setw(8) << std::fixed << std::setprecision(2)
              << scalar_us << " us\n";
    std::cout << "  Optimisé : " << std::setw(8) << opt_us << " us";
    if (scalar_us > 0)
        std::cout << "  (speedup: " << std::setprecision(1) << scalar_us / opt_us << "x)";
    std::cout << "\n";
}

// ─────────────────────────────────────────────
// Main
// ─────────────────────────────────────────────

int main() {
    std::cout << "=== Chapitre 06: SIMD et Vectorisation ===\n\n";

    // Exercice 1
    std::cout << "--- Exercice 1: Scale prices (N=1,000,000) ---\n";
    benchmark_scale(1'000'000);

    // Exercice 2
    std::cout << "\n--- Exercice 2: VWAP ---\n";
    {
        constexpr int N = 500'000;
        std::vector<double> prices(N);
        std::vector<int>    volumes(N);
        std::mt19937 rng(99);
        std::uniform_real_distribution<double> pdist(99.5, 100.5);
        std::uniform_int_distribution<int>     vdist(100, 10000);
        for (int i = 0; i < N; i++) { prices[i] = pdist(rng); volumes[i] = vdist(rng); }

        auto t0 = Clock::now();
        double vwap = compute_vwap(prices.data(), volumes.data(), N);
        auto t1 = Clock::now();

        std::cout << "  VWAP sur " << N << " ticks: " << std::fixed << std::setprecision(4)
                  << vwap << "  (" << elapsed_us(t0, t1) << " us)\n";
    }

    // Exercice 3
    std::cout << "\n--- Exercice 3: Min/Max/Mean (N=1,000,000) ---\n";
    {
        constexpr int N = 1'000'000;
        std::vector<double> data(N);
        std::mt19937 rng(7);
        std::uniform_real_distribution<double> d(50.0, 150.0);
        for (auto& v : data) v = d(rng);

        auto t0 = Clock::now();
        Stats s = compute_stats(data.data(), N);
        auto t1 = Clock::now();

        std::cout << "  Min  = " << std::fixed << std::setprecision(4) << s.min_val << "\n";
        std::cout << "  Max  = " << s.max_val << "\n";
        std::cout << "  Mean = " << s.mean << "\n";
        std::cout << "  Temps: " << elapsed_us(t0, t1) << " us\n";
    }

    std::cout << "\n[Implémente les TODO et recompile avec -O3 -march=native]\n";
    return 0;
}
