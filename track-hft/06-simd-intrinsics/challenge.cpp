// Challenge 06 - SIMD: Min/Max/Moyenne sur grand array de prix
// Compilation: g++ -std=c++17 -O3 -march=native -o challenge challenge.cpp && ./challenge
//
// OBJECTIF: implémenter 4 versions d'une fonction stats sur 10M doubles.
// Mesurer et comparer les performances de chaque approche.
//
// SCHÉMA - Traitement de 4 doubles en parallèle (AVX2):
//
//  Entrée (array de N doubles):
//  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬────
//  │100.1 │ 99.8 │100.5 │ 99.9 │100.2 │100.0 │ 99.7 │100.3 │ ...
//  └──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴────
//    ├─────────────────────┤  ├─────────────────────┤
//      Chunk 0 (4 doubles)     Chunk 1 (4 doubles)
//           │                       │
//           ▼ vminpd / vmaxpd       ▼
//      min/max locaux          min/max locaux
//           └───────────────────────┘
//                     │
//                     ▼ réduction finale
//                 min/max/mean globaux
//
// PARTIE 1: version naive (branchement dans la boucle)
// PARTIE 2: version sans branchement (std::min / std::max)
// PARTIE 3: version unrolled x4 (aide le compilateur)
// PARTIE 4: version avec 4 accumulateurs parallèles (max ILP)
// BONUS: comparer std::minmax_element

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <limits>

using Clock = std::chrono::high_resolution_clock;

double elapsed_us(Clock::time_point a, Clock::time_point b) {
    return std::chrono::duration<double, std::micro>(b - a).count();
}

struct Stats {
    double min_val;
    double max_val;
    double mean;
};

// ─────────────────────────────────────────────
// PARTIE 1 : version naive avec branchement explicite
// ─────────────────────────────────────────────
//
// Problème: le compilateur ne peut pas vectoriser facilement
// une boucle avec if/else car il ne sait pas si les branches
// sont data-dépendantes ou non.
//
// TODO: implémenter avec if (data[i] < min_val) min_val = data[i]; etc.

Stats compute_naive(const double* data, int n) {
    if (n == 0) return {};
    double min_val = std::numeric_limits<double>::max();
    double max_val = std::numeric_limits<double>::lowest();
    double sum     = 0.0;

    for (int i = 0; i < n; i++) {
        // TODO: if/else pour min et max
    }

    return {min_val, max_val, sum / n};
}

// ─────────────────────────────────────────────
// PARTIE 2 : version sans branchement (std::min/max)
// ─────────────────────────────────────────────
//
// std::min et std::max sur des doubles compilent en instructions
// conditionnelles (cmovsd) ou VMINPD/VMAXPD selon le compilateur.
// Pas de branch misprediction  vectorisable.
//
// TODO: même logique mais avec std::min/std::max au lieu de if/else.

Stats compute_branchless(const double* __restrict__ data, int n) {
    if (n == 0) return {};
    double min_val = data[0];
    double max_val = data[0];
    double sum     = 0.0;

    for (int i = 0; i < n; i++) {
        // TODO: std::min / std::max
    }

    return {min_val, max_val, sum / n};
}

// ─────────────────────────────────────────────
// PARTIE 3 : version unrolled x4
// ─────────────────────────────────────────────
//
// Traiter 4 éléments par itération permet au compilateur d'émettre
// une instruction VMINPD (256 bits = 4 doubles) par chunk.
//
// TODO: boucle principale i += 4, traiter data[i+0..i+3],
//       puis tail loop pour les éléments restants.

Stats compute_unrolled(const double* __restrict__ data, int n) {
    if (n == 0) return {};

    double min0 = data[0], min1 = data[0], min2 = data[0], min3 = data[0];
    double max0 = data[0], max1 = data[0], max2 = data[0], max3 = data[0];
    double sum  = 0.0;

    int i = 0;
    // TODO: boucle principale (i + 3 < n), unroll x4
    // Chaque lane (0..3) maintient son propre min/max

    // TODO: tail loop

    // Réduction des 4 lanes
    double min_val = std::min({min0, min1, min2, min3});
    double max_val = std::max({max0, max1, max2, max3});

    return {min_val, max_val, sum / n};
}

// ─────────────────────────────────────────────
// PARTIE 4 : version ILP maximale (4 accumulateurs)
// ─────────────────────────────────────────────
//
// ILP = Instruction Level Parallelism.
// Les CPUs modernes ont plusieurs unités d'exécution flottante.
// En utilisant 4 accumulateurs indépendants pour sum, on permet
// au CPU d'exécuter 4 additions flottantes en parallèle
// (au lieu d'une chaîne de dépendance séquentielle).
//
// CPU superscalaire: 2-4 ports d'addition FP disponibles par cycle.
//
// TODO: sum0, sum1, sum2, sum3 accumulés séparément, fusionnés à la fin.
//       min/max aussi en 4 lanes.

Stats compute_ilp(const double* __restrict__ data, int n) {
    if (n == 0) return {};

    double min0 = data[0], min1 = data[0], min2 = data[0], min3 = data[0];
    double max0 = data[0], max1 = data[0], max2 = data[0], max3 = data[0];
    double sum0 = 0.0, sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;

    int i = 0;
    // TODO: boucle principale (i + 3 < n)
    // lane 0: data[i+0], lane 1: data[i+1], etc.

    // TODO: tail loop (accumuler dans sum0, min0, max0)

    // Réduction
    double min_val = std::min({min0, min1, min2, min3});
    double max_val = std::max({max0, max1, max2, max3});
    double sum     = sum0 + sum1 + sum2 + sum3;

    return {min_val, max_val, sum / n};
}

// ─────────────────────────────────────────────
// Benchmark runner
// ─────────────────────────────────────────────

void benchmark(const char* name,
               Stats (*fn)(const double*, int),
               const std::vector<double>& data,
               const Stats& ref) {
    constexpr int REPS = 20;
    int N = static_cast<int>(data.size());

    // Warm-up
    volatile Stats s = fn(data.data(), N);
    (void)s;

    auto t0 = Clock::now();
    Stats result{};
    for (int r = 0; r < REPS; r++)
        result = fn(data.data(), N);
    auto t1 = Clock::now();

    double us = elapsed_us(t0, t1) / REPS;
    double gb_s = (N * sizeof(double)) / (us * 1e-6) / 1e9;

    // Vérification
    bool ok = (std::abs(result.min_val - ref.min_val) < 1e-6) &&
              (std::abs(result.max_val - ref.max_val) < 1e-6) &&
              (std::abs(result.mean    - ref.mean)    < 1e-3);

    std::cout << "  " << std::left << std::setw(20) << name
              << " | " << std::right << std::setw(8) << std::fixed << std::setprecision(1) << us << " us"
              << " | " << std::setw(5) << std::setprecision(1) << gb_s << " GB/s"
              << " | " << (ok ? "PASS" : "FAIL")
              << "\n";
}

int main() {
    std::cout << "=== Challenge 06: Min/Max/Mean sur 10M doubles ===\n\n";

    std::cout << "Schéma - traitement vectorisé 4 doubles/instruction:\n";
    std::cout << "  [d0][d1][d2][d3]  VMINPD  [min0][min1][min2][min3]\n";
    std::cout << "  [d4][d5][d6][d7]  VMINPD  [min4][min5][min6][min7]\n";
    std::cout << "  ...réduction finale des lanes...\n\n";

    constexpr int N = 10'000'000;

    std::cout << "Génération de " << N << " prix aléatoires...\n";
    std::vector<double> data(N);
    {
        std::mt19937 rng(42);
        std::uniform_real_distribution<double> dist(50.0, 150.0);
        for (auto& v : data) v = dist(rng);
    }

    // Référence avec std (correcte mais pas forcément optimale)
    auto [it_min, it_max] = std::minmax_element(data.begin(), data.end());
    double ref_min  = *it_min;
    double ref_max  = *it_max;
    double ref_mean = std::accumulate(data.begin(), data.end(), 0.0) / N;
    Stats ref{ref_min, ref_max, ref_mean};

    std::cout << "Référence: min=" << std::fixed << std::setprecision(3) << ref_min
              << " max=" << ref_max << " mean=" << ref_mean << "\n\n";

    std::cout << "  " << std::left << std::setw(20) << "Version"
              << " | " << std::setw(9) << "Temps"
              << " | " << std::setw(8) << "Débit"
              << " | " << "Résultat\n";
    std::cout << "  " << std::string(55, '-') << "\n";

    benchmark("1-naive",      compute_naive,     data, ref);
    benchmark("2-branchless", compute_branchless, data, ref);
    benchmark("3-unrolled",   compute_unrolled,   data, ref);
    benchmark("4-ilp",        compute_ilp,        data, ref);

    // BONUS: std::minmax_element
    {
        constexpr int REPS = 20;
        auto t0 = Clock::now();
        volatile double dummy_min = 0, dummy_max = 0;
        for (int r = 0; r < REPS; r++) {
            auto [mn, mx] = std::minmax_element(data.begin(), data.end());
            dummy_min = *mn; dummy_max = *mx;
        }
        auto t1 = Clock::now();
        double us = elapsed_us(t0, t1) / REPS;
        double gb = (N * sizeof(double)) / (us * 1e-6) / 1e9;
        std::cout << "  " << std::left << std::setw(20) << "5-std::minmax"
                  << " | " << std::right << std::setw(8) << std::fixed << std::setprecision(1) << us << " us"
                  << " | " << std::setw(5) << std::setprecision(1) << gb << " GB/s"
                  << " | (sans mean)\n";
    }

    std::cout << "\n[Implémente les TODO et observe le speedup entre versions]\n";
    return 0;
}
