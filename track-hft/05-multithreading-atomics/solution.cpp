// Chapitre 05 - Multithreading & Atomics - SOLUTION
// Compilation: g++ -std=c++17 -O2 -pthread -o mt solution.cpp && ./mt

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <chrono>
#include <cassert>

struct MarketTick {
    double price;
    int volume;
    long sequence;
};

// =============================================================
// SOLUTION 1 : Data race corrigee avec atomic
// =============================================================
void exercise_data_race() {
    constexpr int N_THREADS = 4;
    constexpr int N_OPS = 100000;

    // Version buggee
    int unsafe_counter = 0;
    {
        std::vector<std::thread> threads;
        for (int t = 0; t < N_THREADS; t++) {
            threads.emplace_back([&unsafe_counter]() {
                for (int i = 0; i < N_OPS; i++) unsafe_counter++;
            });
        }
        for (auto& t : threads) t.join();
    }
    std::cout << "Unsafe counter: " << unsafe_counter
              << " (expected " << N_THREADS * N_OPS << ")" << std::endl;

    // Version corrigee avec atomic
    std::atomic<int> safe_counter{0};
    {
        std::vector<std::thread> threads;
        for (int t = 0; t < N_THREADS; t++) {
            threads.emplace_back([&safe_counter]() {
                for (int i = 0; i < N_OPS; i++) {
                    safe_counter.fetch_add(1, std::memory_order_relaxed);
                }
            });
        }
        for (auto& t : threads) t.join();
    }
    int result = safe_counter.load();
    assert(result == N_THREADS * N_OPS);
    std::cout << "Safe counter:   " << result
              << " (expected " << N_THREADS * N_OPS << ") PASS" << std::endl;
}

// =============================================================
// SOLUTION 2 : Producer-Consumer avec atomic flag
// =============================================================
struct SharedBuffer {
    MarketTick tick;
    std::atomic<bool> has_data{false};
};

void exercise_producer_consumer() {
    constexpr int N_TICKS = 100000;
    SharedBuffer buffer;
    std::atomic<bool> done{false};

    std::thread producer([&]() {
        for (int i = 0; i < N_TICKS; i++) {
            // Attend que le consumer ait lu le precedent
            while (buffer.has_data.load(std::memory_order_acquire)) {}
            buffer.tick = MarketTick{100.0 + i * 0.01, (i % 500) + 1, (long)i};
            buffer.has_data.store(true, std::memory_order_release);
        }
        // Attend que le dernier tick soit consomme
        while (buffer.has_data.load(std::memory_order_acquire)) {}
        done.store(true, std::memory_order_release);
    });

    long total_volume = 0;
    long tick_count = 0;

    std::thread consumer([&]() {
        while (true) {
            if (buffer.has_data.load(std::memory_order_acquire)) {
                total_volume += buffer.tick.volume;
                tick_count++;
                buffer.has_data.store(false, std::memory_order_release);
            } else if (done.load(std::memory_order_acquire)) {
                break;
            }
        }
    });

    producer.join();
    consumer.join();

    assert(tick_count == N_TICKS);
    std::cout << "Ticks processed: " << tick_count << " PASS" << std::endl;
    std::cout << "Total volume:    " << total_volume << std::endl;
}

// =============================================================
// SOLUTION 3 : Benchmark mutex vs atomic
// =============================================================
void exercise_benchmark() {
    constexpr int N_THREADS = 4;
    constexpr int N = 1'000'000;

    // Mutex
    int mutex_counter = 0;
    std::mutex mtx;

    auto start = std::chrono::high_resolution_clock::now();
    {
        std::vector<std::thread> threads;
        for (int t = 0; t < N_THREADS; t++) {
            threads.emplace_back([&]() {
                for (int i = 0; i < N; i++) {
                    std::lock_guard<std::mutex> lock(mtx);
                    mutex_counter++;
                }
            });
        }
        for (auto& t : threads) t.join();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto mutex_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // Atomic
    std::atomic<int> atomic_counter{0};

    start = std::chrono::high_resolution_clock::now();
    {
        std::vector<std::thread> threads;
        for (int t = 0; t < N_THREADS; t++) {
            threads.emplace_back([&]() {
                for (int i = 0; i < N; i++) {
                    atomic_counter.fetch_add(1, std::memory_order_relaxed);
                }
            });
        }
        for (auto& t : threads) t.join();
    }
    end = std::chrono::high_resolution_clock::now();
    auto atomic_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    assert(mutex_counter == N_THREADS * N);
    assert(atomic_counter.load() == N_THREADS * N);

    std::cout << "Mutex:  " << mutex_ns / 1000 << " us (counter=" << mutex_counter << ")" << std::endl;
    std::cout << "Atomic: " << atomic_ns / 1000 << " us (counter=" << atomic_counter.load() << ")" << std::endl;
    std::cout << "Ratio:  " << (double)mutex_ns / atomic_ns << "x" << std::endl;
}

int main() {
    std::cout << "=== Solution 1: Data Race ===" << std::endl;
    exercise_data_race();

    std::cout << "\n=== Solution 2: Producer-Consumer ===" << std::endl;
    exercise_producer_consumer();

    std::cout << "\n=== Solution 3: Mutex vs Atomic ===" << std::endl;
    exercise_benchmark();

    return 0;
}
