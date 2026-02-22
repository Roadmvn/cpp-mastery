// Chapitre 03 - Lock-Free Structures - SOLUTION
// Compilation: g++ -std=c++17 -O2 -pthread -o lockfree solution.cpp && ./lockfree

#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <vector>
#include <cassert>

// =============================================================
// SOLUTION 1 : Compteur atomique avec CAS
// =============================================================
class AtomicCounter {
    std::atomic<long> value_{0};
public:
    void increment() {
        long expected = value_.load(std::memory_order_relaxed);
        while (!value_.compare_exchange_weak(expected, expected + 1,
                std::memory_order_seq_cst, std::memory_order_relaxed)) {
            // expected est automatiquement mis a jour par compare_exchange_weak
            // on re-essaie avec la nouvelle valeur
        }
    }

    long get() const {
        return value_.load(std::memory_order_seq_cst);
    }
};

// =============================================================
// SOLUTION 2 : SPSC Queue Lock-Free
// =============================================================
template<typename T, size_t Size = 1024>
class SPSCQueue {
    static_assert((Size & (Size - 1)) == 0, "Size must be power of 2");

    T buffer_[Size];
    alignas(64) std::atomic<size_t> write_pos_{0};
    alignas(64) std::atomic<size_t> read_pos_{0};

public:
    bool push(const T& item) {
        size_t w = write_pos_.load(std::memory_order_relaxed);
        if (w - read_pos_.load(std::memory_order_acquire) == Size) {
            return false; // queue pleine
        }
        buffer_[w & (Size - 1)] = item;
        write_pos_.store(w + 1, std::memory_order_release);
        return true;
    }

    bool pop(T& item) {
        size_t r = read_pos_.load(std::memory_order_relaxed);
        if (r == write_pos_.load(std::memory_order_acquire)) {
            return false; // queue vide
        }
        item = buffer_[r & (Size - 1)];
        read_pos_.store(r + 1, std::memory_order_release);
        return true;
    }

    size_t size() const {
        return write_pos_.load(std::memory_order_acquire) -
               read_pos_.load(std::memory_order_acquire);
    }
};

struct MarketTick {
    double price;
    int quantity;
    long sequence;
};

int main() {
    // Test Exercice 1
    std::cout << "=== Solution 1: Compteur Atomique CAS ===" << std::endl;
    {
        AtomicCounter counter;
        constexpr int N_THREADS = 4;
        constexpr int N_INCREMENTS = 100000;

        std::vector<std::thread> threads;
        for (int t = 0; t < N_THREADS; t++) {
            threads.emplace_back([&counter]() {
                for (int i = 0; i < N_INCREMENTS; i++) {
                    counter.increment();
                }
            });
        }
        for (auto& t : threads) t.join();

        long expected = N_THREADS * N_INCREMENTS;
        long actual = counter.get();
        std::cout << "Expected: " << expected << std::endl;
        std::cout << "Actual:   " << actual << std::endl;
        assert(actual == expected);
        std::cout << "PASS" << std::endl;
    }

    // Test Exercice 2
    std::cout << "\n=== Solution 2: SPSC Queue ===" << std::endl;
    {
        SPSCQueue<MarketTick, 4096> queue;
        constexpr int N_MESSAGES = 1'000'000;
        std::atomic<bool> producer_done{false};
        long consumer_sum = 0;

        std::thread producer([&]() {
            for (int i = 0; i < N_MESSAGES; i++) {
                MarketTick tick{100.0 + i * 0.01, i % 100 + 1, (long)i};
                while (!queue.push(tick)) {}
            }
            producer_done.store(true, std::memory_order_release);
        });

        std::thread consumer([&]() {
            long count = 0;
            MarketTick tick;
            while (count < N_MESSAGES) {
                if (queue.pop(tick)) {
                    consumer_sum += tick.sequence;
                    count++;
                }
            }
        });

        auto start = std::chrono::high_resolution_clock::now();
        producer.join();
        consumer.join();
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        long expected_sum = (long)(N_MESSAGES - 1) * N_MESSAGES / 2;
        std::cout << "Messages:    " << N_MESSAGES << std::endl;
        std::cout << "Time:        " << elapsed_us << " us" << std::endl;
        std::cout << "Throughput:  " << (long long)N_MESSAGES * 1'000'000 / elapsed_us << " msg/sec" << std::endl;
        std::cout << "Latency:     " << elapsed_us * 1000 / N_MESSAGES << " ns/msg" << std::endl;
        assert(consumer_sum == expected_sum);
        std::cout << "Sum check:   PASS" << std::endl;
    }

    return 0;
}
