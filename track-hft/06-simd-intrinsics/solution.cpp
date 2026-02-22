// Chapitre 06 - SIMD et Vectorisation - SOLUTION
// Compilation: g++ -std=c++17 -O3 -march=native -o solution solution.cpp && ./solution

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iomanip>

using Clock = std::chrono::high_resolution_clock;

double elapsed_us(Clock::time_point a, Clock::time_point b) {
    return std::chrono::duration<double, std::micro>(b - a).count();
}

// ─────────────────────────────────────────────
// SOLUTION 1 : Scale prices
// ─────────────────────────────────────────────

void scale_prices_scalar(const double* in, double* out, int n, double factor) {
    for (int i = 0; i < n; i++)
        out[i] = in[i] * factor;
}

// __restrict__ indique au compilateur: in et out ne se chevauchent pas.
// Le compilateur peut alors émettre des instructions SIMD (VMULPD, etc.)
// sans craindre les alias. Avec -O3 -march=native, gcc émet du AVX2.
void scale_prices_opt(const double* __restrict__ in,
                      double* __restrict__ out,
                      int n, double factor) {
    // Unroll x4 aide le compilateur à remplir le pipeline d'exécution OOO.
    // Chaque itération traite 4 doubles → 1 instruction VMULPD (AVX2, 256 bits).
    int i = 0;
    for (; i + 3 < n; i += 4) {
        out[i+0] = in[i+0] * factor;
        out[i+1] = in[i+1] * factor;
        out[i+2] = in[i+2] * factor;
        out[i+3] = in[i+3] * factor;
    }
    // Tail: éléments restants (si N pas multiple de 4)
    for (; i < n; i++)
        out[i] = in[i] * factor;
}

// ─────────────────────────────────────────────
// SOLUTION 2 : VWAP
// ─────────────────────────────────────────────
//
// Pattern "two-accumulator": sum_pv et sum_v indépendants.
// Le compilateur peut les calculer en parallèle (2 ports d'addition flottante).

double compute_vwap(const double* __restrict__ prices,
                    const int*    __restrict__ volumes,
                    int n) {
    double sum_pv = 0.0;
    double sum_v  = 0.0;

    for (int i = 0; i < n; i++) {
        double v  = static_cast<double>(volumes[i]);
        sum_pv   += prices[i] * v;
        sum_v    += v;
    }

    return (sum_v > 0.0) ? sum_pv / sum_v : 0.0;
}

// ─────────────────────────────────────────────
// SOLUTION 3 : Min/Max/Mean
// ─────────────────────────────────────────────
//
// Clé: éviter les branches imprévisibles.
// std::min/std::max sur des doubles compile en instructions conditionnelles
// ou en VMINPD (SSE/AVX) selon le compilateur et les flags.

struct Stats {
    double min_val;
    double max_val;
    double mean;
};

Stats compute_stats(const double* __restrict__ data, int n) {
    if (n == 0) return {0.0, 0.0, 0.0};

    double min_val = data[0];
    double max_val = data[0];
    double sum     = 0.0;

    // Une seule passe: O(N), cache-friendly.
    // Avec -O3 -march=native: le compilateur utilise VMINPD / VMAXPD / VADDPD
    for (int i = 0; i < n; i++) {
        double d = data[i];
        if (d < min_val) min_val = d;
        if (d > max_val) max_val = d;
        sum += d;
    }

    return {min_val, max_val, sum / n};
}

// ─────────────────────────────────────────────
// Benchmark complet
// ─────────────────────────────────────────────

void benchmark_scale(int N) {
    std::vector<double> in(N), out_scalar(N), out_opt(N);
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(99.0, 101.0);
    for (auto& v : in) v = dist(rng);

    constexpr int REPS = 200;
    double factor = 1.0001;

    // Warm-up
    scale_prices_scalar(in.data(), out_scalar.data(), N, factor);
    scale_prices_opt(in.data(), out_opt.data(), N, factor);

    auto t0 = Clock::now();
    for (int r = 0; r < REPS; r++)
        scale_prices_scalar(in.data(), out_scalar.data(), N, factor);
    auto t1 = Clock::now();
    double scalar_us = elapsed_us(t0, t1) / REPS;

    auto t2 = Clock::now();
    for (int r = 0; r < REPS; r++)
        scale_prices_opt(in.data(), out_opt.data(), N, factor);
    auto t3 = Clock::now();
    double opt_us = elapsed_us(t2, t3) / REPS;

    for (int i = 0; i < N; i++)
        assert(std::abs(out_scalar[i] - out_opt[i]) < 1e-9);

    std::cout << "  Scalaire  : " << std::setw(8) << std::fixed << std::setprecision(2)
              << scalar_us << " us\n";
    std::cout << "  Optimisé  : " << std::setw(8) << opt_us << " us";
    if (opt_us > 0)
        std::cout << "  (speedup: " << std::setprecision(1) << scalar_us / opt_us << "x)";
    std::cout << "\n";
}

void benchmark_stats(int N) {
    std::vector<double> data(N);
    std::mt19937 rng(7);
    std::uniform_real_distribution<double> d(50.0, 150.0);
    for (auto& v : data) v = d(rng);

    constexpr int REPS = 100;
    Stats s{};

    auto t0 = Clock::now();
    for (int r = 0; r < REPS; r++)
        s = compute_stats(data.data(), N);
    auto t1 = Clock::now();

    double us = elapsed_us(t0, t1) / REPS;
    std::cout << "  Min=" << std::fixed << std::setprecision(3) << s.min_val
              << "  Max=" << s.max_val
              << "  Mean=" << s.mean
              << "  Temps=" << std::setprecision(2) << us << " us\n";
    double throughput = N / (us * 1e-6) / 1e9;
    std::cout << "  Throughput: " << std::setprecision(2) << throughput << " Gelements/s\n";
}

// ─────────────────────────────────────────────
// Démonstration SIMD conceptuelle
// ─────────────────────────────────────────────

void demo_simd_concept() {
    std::cout << "\n--- Illustration: 4 doubles traités en parallèle ---\n\n";
    std::cout << "  Code C++:  out[i] = in[i] * factor  (boucle x4)\n";
    std::cout << "  Assembleur (avec -O3 -march=native, schématique):\n\n";
    std::cout << "  vmovupd  ymm0, [in + i*8]   ; charge 4 doubles dans YMM0\n";
    std::cout << "  vbroadcastsd ymm1, factor   ; factor dans les 4 lanes de YMM1\n";
    std::cout << "  vmulpd   ymm0, ymm0, ymm1   ; 4 multiplications en 1 cycle\n";
    std::cout << "  vmovupd  [out + i*8], ymm0  ; écrit 4 doubles en mémoire\n\n";
    std::cout << "  1 itération = 4 doubles = 32 bytes lus + 32 bytes écrits\n";
    std::cout << "  Bande passante L1: ~3 ns pour 64 bytes → ~750 GB/s\n";
}

int main() {
    std::cout << "=== Solution 06: SIMD et Vectorisation ===\n";

    demo_simd_concept();

    std::cout << "\n--- Benchmark 1: Scale prices (N=1,000,000) ---\n";
    benchmark_scale(1'000'000);

    std::cout << "\n--- Benchmark 2: VWAP (N=500,000) ---\n";
    {
        constexpr int N = 500'000;
        std::vector<double> prices(N);
        std::vector<int>    vols(N);
        std::mt19937 rng(99);
        std::uniform_real_distribution<double> pd(99.5, 100.5);
        std::uniform_int_distribution<int>     vd(100, 10000);
        for (int i = 0; i < N; i++) { prices[i] = pd(rng); vols[i] = vd(rng); }

        constexpr int REPS = 100;
        double vwap = 0.0;
        auto t0 = Clock::now();
        for (int r = 0; r < REPS; r++)
            vwap = compute_vwap(prices.data(), vols.data(), N);
        auto t1 = Clock::now();

        std::cout << "  VWAP=" << std::fixed << std::setprecision(4) << vwap
                  << "  Temps=" << std::setprecision(2) << elapsed_us(t0, t1) / REPS << " us\n";
    }

    std::cout << "\n--- Benchmark 3: Min/Max/Mean (N=1,000,000) ---\n";
    benchmark_stats(1'000'000);

    return 0;
}
