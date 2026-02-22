// Chapitre 08 - Mesure de Latence - SOLUTION
// Compilation: g++ -std=c++17 -O2 -o solution solution.cpp && ./solution

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

using Clock     = std::chrono::high_resolution_clock;
using Nanos     = std::chrono::nanoseconds;
using TimePoint = Clock::time_point;

int64_t ns_between(TimePoint a, TimePoint b) {
    return std::chrono::duration_cast<Nanos>(b - a).count();
}

// ─────────────────────────────────────────────
// Percentiles
// ─────────────────────────────────────────────

struct Percentiles {
    double mean;
    double p50;
    double p90;
    double p99;
    double p999;
    double min_val;
    double max_val;
};

Percentiles compute_percentiles(std::vector<int64_t>& samples) {
    if (samples.empty()) return {};
    std::sort(samples.begin(), samples.end());
    int N = static_cast<int>(samples.size());

    double mean = std::accumulate(samples.begin(), samples.end(), 0.0) / N;
    auto pct = [&](double p) -> double {
        int idx = static_cast<int>(p * N);
        idx = std::max(0, std::min(N - 1, idx));
        return static_cast<double>(samples[idx]);
    };

    return {
        mean,
        pct(0.50),
        pct(0.90),
        pct(0.99),
        pct(0.999),
        static_cast<double>(samples.front()),
        static_cast<double>(samples.back())
    };
}

void print_percentiles(const std::string& label, Percentiles& p) {
    std::cout << "  " << std::left << std::setw(22) << label
              << " mean=" << std::setw(8) << std::fixed << std::setprecision(1) << p.mean
              << " p50=" << std::setw(8) << p.p50
              << " p90=" << std::setw(8) << p.p90
              << " p99=" << std::setw(8) << p.p99
              << " p99.9=" << std::setw(8) << p.p999
              << " ns\n";
}

// ─────────────────────────────────────────────
// SOLUTION 1 : overhead Clock::now()
// ─────────────────────────────────────────────

void exercise_clock_overhead() {
    constexpr int N = 1'000'000;

    // Warm-up
    for (int i = 0; i < 1000; i++) (void)Clock::now();

    volatile int64_t dummy = 0;
    auto t0 = Clock::now();
    for (int i = 0; i < N; i++) {
        auto tp = Clock::now();
        dummy = tp.time_since_epoch().count();
    }
    auto t1 = Clock::now();

    double total_ns = static_cast<double>(ns_between(t0, t1));
    double avg      = total_ns / N;

    std::cout << "  N=" << N << " appels Clock::now()\n";
    std::cout << "  Total: " << static_cast<int64_t>(total_ns / 1000) << " us\n";
    std::cout << "  Overhead par appel: " << std::fixed << std::setprecision(1) << avg << " ns\n";
    (void)dummy;
}

// ─────────────────────────────────────────────
// SOLUTION 2 : bench_map et bench_unordered_map
// ─────────────────────────────────────────────

template<typename Map>
std::vector<int64_t> bench_lookup(Map& m, double target, int reps) {
    // Warm-up
    for (int i = 0; i < 100; i++) {
        volatile auto it = m.find(target);
        (void)it;
    }

    std::vector<int64_t> samples(reps);
    for (int r = 0; r < reps; r++) {
        auto t0 = Clock::now();
        volatile auto it = m.find(target);
        auto t1 = Clock::now();
        samples[r] = ns_between(t0, t1);
        (void)it;
    }
    return samples;
}

void benchmark_lookups() {
    constexpr int REPS = 50'000;
    double target = 100.00001;

    for (int n : {100, 1000, 10000}) {
        std::mt19937 rng(42);
        std::uniform_real_distribution<double> dist(99.0, 101.0);

        std::map<double, int>             m_map;
        std::unordered_map<double, int>   m_uhm;
        m_uhm.reserve(n * 2);

        for (int i = 0; i < n; i++) {
            double k = dist(rng);
            m_map[k] = i;
            m_uhm[k] = i;
        }
        m_map[target] = -1;
        m_uhm[target] = -1;

        auto s_map = bench_lookup(m_map, target, REPS);
        auto s_uhm = bench_lookup(m_uhm, target, REPS);

        auto p_map = compute_percentiles(s_map);
        auto p_uhm = compute_percentiles(s_uhm);

        std::cout << "  N=" << std::setw(6) << n << "\n";
        print_percentiles("    std::map", p_map);
        print_percentiles("    unordered_map", p_uhm);
    }
}

// ─────────────────────────────────────────────
// SOLUTION 4 : outliers
// ─────────────────────────────────────────────

void exercise_outliers() {
    std::mt19937 rng(123);
    std::uniform_int_distribution<int> die(1, 100);
    std::normal_distribution<double> fast_dist(20.0, 3.0);
    std::normal_distribution<double> slow_dist(5000.0, 500.0);

    constexpr int N = 100'000;
    std::vector<int64_t> samples(N);
    int outlier_count = 0;

    for (int i = 0; i < N; i++) {
        bool is_outlier = (die(rng) == 1);
        double val = is_outlier ? slow_dist(rng) : fast_dist(rng);
        samples[i] = std::max(1LL, static_cast<int64_t>(val));
        if (is_outlier) outlier_count++;
    }

    auto p = compute_percentiles(samples);

    std::cout << "  Distribution bimodale (N=" << N << ", outliers=" << outlier_count << "):\n";
    print_percentiles("  Résultats", p);
    std::cout << "\n  Conclusion:\n";
    std::cout << "    → mean=" << std::fixed << std::setprecision(1) << p.mean
              << " ns (gonflée par les outliers " << std::setprecision(0)
              << p.p999 << " ns)\n";
    std::cout << "    → p50=" << p.p50 << " ns  = vrai coût normal\n";
    std::cout << "    → p99.9=" << p.p999 << " ns = outlier (1 op/1000)\n";
    std::cout << "    → Optimiser sur p50: OK. Ignorer p99.9: DANGER en HFT!\n";
}

// ─────────────────────────────────────────────
// Demo: mesure d'opérations concrètes
// ─────────────────────────────────────────────

void demo_concrete_ops() {
    constexpr int REPS = 100'000;
    std::vector<int64_t> samples(REPS);

    // Mesure: vector push_back
    {
        for (int r = 0; r < REPS; r++) {
            std::vector<int> v;
            v.reserve(1);
            auto t0 = Clock::now();
            v.push_back(r);
            auto t1 = Clock::now();
            samples[r] = ns_between(t0, t1);
        }
        auto p = compute_percentiles(samples);
        print_percentiles("vector::push_back", p);
    }

    // Mesure: new/delete
    {
        for (int r = 0; r < REPS; r++) {
            auto t0 = Clock::now();
            int* p = new int(r);
            delete p;
            auto t1 = Clock::now();
            samples[r] = ns_between(t0, t1);
        }
        auto p = compute_percentiles(samples);
        print_percentiles("new + delete", p);
    }

    // Mesure: mutex lock/unlock
    {
        std::mutex mtx;
        for (int r = 0; r < REPS; r++) {
            auto t0 = Clock::now();
            mtx.lock();
            mtx.unlock();
            auto t1 = Clock::now();
            samples[r] = ns_between(t0, t1);
        }
        auto p = compute_percentiles(samples);
        print_percentiles("mutex lock+unlock", p);
    }
}

// ─────────────────────────────────────────────
// Main
// ─────────────────────────────────────────────

int main() {
    std::cout << "=== Solution 08: Mesure de Latence ===\n\n";

    std::cout << "--- Overhead Clock::now() ---\n";
    exercise_clock_overhead();

    std::cout << "\n--- Map vs UnorderedMap (50K reps par N) ---\n";
    benchmark_lookups();

    std::cout << "\n--- Opérations concrètes (100K reps) ---\n";
    demo_concrete_ops();

    std::cout << "\n--- Impact des outliers ---\n";
    exercise_outliers();

    return 0;
}
