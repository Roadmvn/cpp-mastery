// Chapitre 08 - Mesure de Latence - EXERCICE
// Compilation: g++ -std=c++17 -O2 -o exercise exercise.cpp && ./exercise
//
// OBJECTIF: apprendre à mesurer la latence correctement avec std::chrono.
//
// EXERCICE 1: mesurer le coût d'un appel Clock::now()
// EXERCICE 2: mesurer le coût d'un std::map lookup vs std::unordered_map
// EXERCICE 3: calculer p50 / p99 / mean sur un vecteur de mesures
// EXERCICE 4: identifier pourquoi la moyenne trompe (outliers)

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>
#include <cassert>
#include <iomanip>
#include <cmath>
#include <string>

using Clock    = std::chrono::high_resolution_clock;
using Nanos    = std::chrono::nanoseconds;
using TimePoint = Clock::time_point;

// ─────────────────────────────────────────────
// Helpers timing
// ─────────────────────────────────────────────

// Retourne le temps écoulé en nanosecondes entre deux time_points
int64_t ns_between(TimePoint a, TimePoint b) {
    return std::chrono::duration_cast<Nanos>(b - a).count();
}

// ─────────────────────────────────────────────
// EXERCICE 1 : coût d'un appel Clock::now()
// ─────────────────────────────────────────────
//
// Clock::now() n'est pas gratuit: il fait un syscall ou lit le TSC.
// Sur macOS: ~40-80 ns. Sur Linux: ~20-40 ns.
//
// Méthode: mesurer N appels consécutifs, diviser.

void exercise_clock_overhead() {
    constexpr int N = 1'000'000;

    // TODO: mesurer le temps pour N appels à Clock::now()
    // Stocker dans une variable volatile pour éviter l'élimination
    volatile int64_t dummy = 0;

    auto t0 = Clock::now();
    // TODO: boucle N fois, appeler Clock::now() et lire son résultat dans dummy
    auto t1 = Clock::now();

    int64_t total_ns = ns_between(t0, t1);
    double avg_ns = (double)total_ns / N;

    std::cout << "  N=" << N << " appels Clock::now()\n";
    std::cout << "  Total: " << total_ns / 1000 << " us\n";
    std::cout << "  Overhead par appel: " << avg_ns << " ns\n";
    (void)dummy;
}

// ─────────────────────────────────────────────
// EXERCICE 2 : lookup dans différentes structures
// ─────────────────────────────────────────────
//
// Pattern: chercher un prix (double) dans une structure remplie de N éléments.
// Mesurer le temps médian pour une seule recherche.

struct LookupResult {
    double median_ns;
    double mean_ns;
    double p99_ns;
    bool   found;
};

// TODO: mesurer le lookup dans un std::map<double, int>
LookupResult bench_map(int n_elements, double target) {
    std::map<double, int> m;
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(99.0, 101.0);

    // Remplir avec n_elements entrées
    for (int i = 0; i < n_elements; i++)
        m[dist(rng)] = i;
    // S'assurer que target est dans la map
    m[target] = -1;

    constexpr int REPS = 10'000;
    std::vector<int64_t> samples(REPS);

    for (int r = 0; r < REPS; r++) {
        auto t0 = Clock::now();
        // TODO: appeler m.find(target), stocker dans volatile
        volatile auto it = m.end(); (void)it;
        auto t1 = Clock::now();
        samples[r] = ns_between(t0, t1);
    }

    std::sort(samples.begin(), samples.end());
    double median = samples[REPS / 2];
    double mean   = std::accumulate(samples.begin(), samples.end(), 0.0) / REPS;
    double p99    = samples[static_cast<int>(REPS * 0.99)];

    return {median, mean, p99, true};
}

// TODO: mesurer le lookup dans un std::unordered_map<double, int>
LookupResult bench_unordered_map(int n_elements, double target) {
    std::unordered_map<double, int> m;
    m.reserve(n_elements * 2);   // éviter les rehash pendant le benchmark

    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(99.0, 101.0);
    for (int i = 0; i < n_elements; i++)
        m[dist(rng)] = i;
    m[target] = -1;

    constexpr int REPS = 10'000;
    std::vector<int64_t> samples(REPS);

    for (int r = 0; r < REPS; r++) {
        auto t0 = Clock::now();
        // TODO: appeler m.find(target), stocker dans volatile
        volatile auto it = m.end(); (void)it;
        auto t1 = Clock::now();
        samples[r] = ns_between(t0, t1);
    }

    std::sort(samples.begin(), samples.end());
    double median = samples[REPS / 2];
    double mean   = std::accumulate(samples.begin(), samples.end(), 0.0) / REPS;
    double p99    = samples[static_cast<int>(REPS * 0.99)];

    return {median, mean, p99, true};
}

// ─────────────────────────────────────────────
// EXERCICE 3 : calcul de percentiles
// ─────────────────────────────────────────────
//
// Étant donné un vecteur de durées (ns), calculer:
// - mean  = somme / N
// - p50   = valeur à l'index N*0.50 (après tri)
// - p90   = valeur à l'index N*0.90
// - p99   = valeur à l'index N*0.99
// - p99.9 = valeur à l'index N*0.999

struct Percentiles {
    double mean;
    double p50;
    double p90;
    double p99;
    double p999;
    double min_val;
    double max_val;
};

// TODO: implémenter compute_percentiles
// ATTENTION: cette fonction doit trier le vecteur (sort in place)
Percentiles compute_percentiles(std::vector<int64_t>& samples) {
    // TODO: trier
    // TODO: calculer chaque percentile par index
    // TODO: calculer mean avec std::accumulate

    Percentiles p{};
    // TODO: remplir p
    return p;
}

// ─────────────────────────────────────────────
// EXERCICE 4 : outliers et pourquoi la moyenne trompe
// ─────────────────────────────────────────────
//
// Générer une distribution "bimodale" simulant une opération
// qui est rapide 99% du temps, mais lente 1% du temps (ex: page fault, OS jitter).

void exercise_outliers() {
    std::mt19937 rng(123);
    std::uniform_int_distribution<int> die(1, 100);   // 1% de chance de lenteur
    std::normal_distribution<double>   fast_dist(20.0, 3.0);   // ~20 ns
    std::normal_distribution<double>   slow_dist(5000.0, 500.0); // ~5000 ns (syscall)

    constexpr int N = 100'000;
    std::vector<int64_t> samples(N);

    for (int i = 0; i < N; i++) {
        double val = (die(rng) == 1) ? slow_dist(rng) : fast_dist(rng);
        samples[i] = std::max(1LL, static_cast<int64_t>(val));
    }

    // TODO: appeler compute_percentiles et afficher les résultats
    // Expected:
    //   mean  ≈ 70 ns  (tiré par les outliers!)
    //   p50   ≈ 20 ns
    //   p99   ≈ 30 ns
    //   p99.9 ≈ 5000 ns
    //
    // Conclusion: la moyenne (~70 ns) ment. Le vrai coût est 20 ns.
    // Les outliers sont vrais problèmes à gérer, pas à moyenner.

    std::cout << "[TODO: appeler compute_percentiles et afficher]\n";
}

// ─────────────────────────────────────────────
// Main
// ─────────────────────────────────────────────

int main() {
    std::cout << "=== Chapitre 08: Mesure de Latence ===\n\n";

    std::cout << "--- Exercice 1: overhead de Clock::now() ---\n";
    exercise_clock_overhead();

    std::cout << "\n--- Exercice 2: Map vs UnorderedMap lookup ---\n";
    {
        double target = 100.0;
        for (int n : {100, 1000, 10000}) {
            auto r_map = bench_map(n, target);
            auto r_uhm = bench_unordered_map(n, target);

            std::cout << "  N=" << std::setw(6) << n << " | "
                      << "map p50=" << std::setw(6) << std::fixed << std::setprecision(0)
                      << r_map.median_ns << " ns  p99=" << std::setw(6) << r_map.p99_ns << " ns | "
                      << "umap p50=" << std::setw(6) << r_uhm.median_ns << " ns  p99=" << std::setw(6)
                      << r_uhm.p99_ns << " ns\n";
        }
    }

    std::cout << "\n--- Exercice 3: Calcul de percentiles ---\n";
    {
        // Distribution simulée
        std::vector<int64_t> data = {10, 12, 11, 15, 13, 14, 200, 9, 16, 11,
                                     12, 13, 10, 18, 14, 500, 12, 11, 13, 15};
        Percentiles p = compute_percentiles(data);
        std::cout << "  mean=" << p.mean << " ns  p50=" << p.p50 << " ns  p99=" << p.p99 << " ns\n";
    }

    std::cout << "\n--- Exercice 4: Impact des outliers ---\n";
    exercise_outliers();

    std::cout << "\n[Implémente les TODO pour voir les résultats réels]\n";
    return 0;
}
