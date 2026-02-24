#include "thread_safe_queue.h"

#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <numeric>
#include <queue>
#include <mutex>

using Clock = std::chrono::steady_clock;
using Ns    = std::chrono::nanoseconds;

static inline int64_t now_ns() {
    return std::chrono::duration_cast<Ns>(Clock::now().time_since_epoch()).count();
}

static int64_t percentile(std::vector<int64_t> v, double p) {
    if (v.empty()) return 0;
    std::sort(v.begin(), v.end());
    return v[static_cast<std::size_t>(p / 100.0 * (v.size() - 1))];
}

// ============================================================
// Benchmark 1 : multi-producteur / multi-consommateur
// ============================================================
static void bench_mpmc(int num_producers, int num_consumers, int messages_per_producer) {
    const int total_messages = num_producers * messages_per_producer;

    ThreadSafeQueue<int64_t> queue;
    std::atomic<int> produced{0};
    std::atomic<int> consumed{0};
    std::vector<int64_t> latencies(total_messages);

    // Consommateurs
    std::vector<std::thread> consumers;
    consumers.reserve(num_consumers);
    for (int c = 0; c < num_consumers; ++c) {
        consumers.emplace_back([&]() {
            while (true) {
                auto val = queue.pop();
                if (!val) break; // queue fermee et vide

                const int64_t recv = now_ns();
                const int idx = consumed.fetch_add(1, std::memory_order_relaxed);
                if (idx < total_messages) {
                    latencies[idx] = recv - *val;
                }
            }
        });
    }

    const int64_t start = now_ns();

    // Producteurs
    std::vector<std::thread> producers;
    producers.reserve(num_producers);
    for (int p = 0; p < num_producers; ++p) {
        producers.emplace_back([&, p]() {
            for (int i = 0; i < messages_per_producer; ++i) {
                queue.push(now_ns());
                produced.fetch_add(1, std::memory_order_relaxed);
            }
        });
    }

    for (auto& t : producers) t.join();

    // Attendre que tout soit consomme, puis fermer
    while (consumed.load(std::memory_order_acquire) < total_messages) {
        std::this_thread::yield();
    }
    queue.close();

    for (auto& t : consumers) t.join();

    const int64_t end = now_ns();
    const double  throughput = static_cast<double>(total_messages) /
                               ((end - start) * 1e-9);

    std::printf("--- MPMC %dp / %dc / %d msg ---\n",
                num_producers, num_consumers, total_messages);
    std::printf("  p50   : %6lld ns\n", percentile(latencies, 50.0));
    std::printf("  p99   : %6lld ns\n", percentile(latencies, 99.0));
    std::printf("  debit : %.2f M msg/s\n\n", throughput / 1e6);
}

// ============================================================
// Benchmark 2 : std::queue non thread-safe (acces serie, reference)
// ============================================================
static void bench_std_queue_serial(int num_messages) {
    std::queue<int64_t> q;
    std::vector<int64_t> latencies(num_messages);

    const int64_t start = now_ns();

    for (int i = 0; i < num_messages; ++i) {
        q.push(now_ns());
    }
    for (int i = 0; i < num_messages; ++i) {
        const int64_t recv = now_ns();
        latencies[i] = recv - q.front();
        q.pop();
    }

    const int64_t end = now_ns();
    const double throughput = static_cast<double>(num_messages) /
                              ((end - start) * 1e-9);

    std::printf("--- std::queue serie (reference, 1 thread) ---\n");
    std::printf("  p50   : %6lld ns\n", percentile(latencies, 50.0));
    std::printf("  p99   : %6lld ns\n", percentile(latencies, 99.0));
    std::printf("  debit : %.2f M msg/s\n\n", throughput / 1e6);
}

int main() {
    std::printf("=== ThreadSafeQueue Benchmark ===\n\n");

    // Reference : std::queue monothreade
    bench_std_queue_serial(500'000);

    // Multi-producteur, multi-consommateur
    bench_mpmc(1, 1,  500'000);  // 1 prod / 1 cons
    bench_mpmc(2, 2,  250'000);  // 2 prod / 2 cons
    bench_mpmc(4, 4,  125'000);  // 4 prod / 4 cons

    std::printf("Note: la latence ThreadSafeQueue inclut le cout du mutex et\n");
    std::printf("      de la condition_variable. La reference serie est optimiste\n");
    std::printf("      (pas de synchronisation inter-thread).\n");

    return 0;
}
