#include "spsc_queue.h"

#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <atomic>

// Nombre de messages echanges pendant le benchmark
static constexpr int NUM_MESSAGES = 1'000'000;
static constexpr int QUEUE_SIZE   = 1024; // puissance de 2

using Clock = std::chrono::steady_clock;
using Ns    = std::chrono::nanoseconds;

// Retourne le timestamp courant en nanosecondes (steady_clock)
static inline int64_t now_ns() {
    return std::chrono::duration_cast<Ns>(Clock::now().time_since_epoch()).count();
}

// Calcule le percentile d'un vecteur deja trie
static int64_t percentile(const std::vector<int64_t>& sorted, double p) {
    if (sorted.empty()) return 0;
    const std::size_t idx = static_cast<std::size_t>(p / 100.0 * (sorted.size() - 1));
    return sorted[idx];
}

int main() {
    SPSCQueue<int64_t, QUEUE_SIZE> queue;

    // timestamps[i] = instant ou le consommateur a recu le message i
    // Le producteur envoie now_ns() comme valeur, le consommateur mesure la difference.
    std::vector<int64_t> latencies;
    latencies.resize(NUM_MESSAGES);

    std::atomic<bool> consumer_ready{false};
    std::atomic<bool> producer_done{false};

    // Thread consommateur
    std::thread consumer([&]() {
        consumer_ready.store(true, std::memory_order_release);

        for (int received = 0; received < NUM_MESSAGES; ) {
            auto val = queue.pop();
            if (val) {
                const int64_t recv_ts = now_ns();
                latencies[received] = recv_ts - *val;
                ++received;
            }
            // Busy-wait intentionnel : on simule un vrai consommateur HFT
        }
    });

    // Attendre que le consommateur soit pret
    while (!consumer_ready.load(std::memory_order_acquire)) {
        std::this_thread::yield();
    }

    // Thread producteur (main thread)
    const int64_t bench_start = now_ns();

    for (int sent = 0; sent < NUM_MESSAGES; ) {
        const int64_t ts = now_ns();
        if (queue.push(ts)) {
            ++sent;
        }
        // Busy-wait intentionnel
    }

    consumer.join();
    const int64_t bench_end = now_ns();

    // --- Statistiques de latence ---
    std::sort(latencies.begin(), latencies.end());

    const int64_t total_ns   = bench_end - bench_start;
    const double  throughput = static_cast<double>(NUM_MESSAGES) /
                               (static_cast<double>(total_ns) * 1e-9);

    std::printf("=== SPSC Queue Benchmark ===\n");
    std::printf("Messages   : %d\n", NUM_MESSAGES);
    std::printf("Queue cap  : %zu\n", queue.capacity());
    std::printf("\n--- Latence producteur -> consommateur ---\n");
    std::printf("  min      : %6lld ns\n", latencies.front());
    std::printf("  p50      : %6lld ns\n", percentile(latencies, 50.0));
    std::printf("  p90      : %6lld ns\n", percentile(latencies, 90.0));
    std::printf("  p99      : %6lld ns\n", percentile(latencies, 99.0));
    std::printf("  p99.9    : %6lld ns\n", percentile(latencies, 99.9));
    std::printf("  max      : %6lld ns\n", latencies.back());
    std::printf("\n--- Throughput ---\n");
    std::printf("  total    : %.3f ms\n", total_ns / 1e6);
    std::printf("  debit    : %.2f M msg/s\n", throughput / 1e6);

    return 0;
}
