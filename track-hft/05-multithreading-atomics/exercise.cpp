// Chapitre 05 - Multithreading & Atomics
// Compilation: g++ -std=c++17 -O2 -pthread -o mt exercise.cpp && ./mt

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <cassert>

struct MarketTick {
    double price;
    int volume;
    long sequence;
};

// =============================================================
// EXERCICE 1 : Data race - observer le probleme
// =============================================================
// Incremente un compteur non-atomique depuis plusieurs threads
// Puis corrige avec std::atomic

void exercise_data_race() {
    constexpr int N_THREADS = 4;
    constexpr int N_OPS = 100000;

    // Version BUGGEE (data race)
    int unsafe_counter = 0;
    {
        std::vector<std::thread> threads;
        for (int t = 0; t < N_THREADS; t++) {
            threads.emplace_back([&unsafe_counter]() {
                for (int i = 0; i < N_OPS; i++) {
                    unsafe_counter++;  // DATA RACE!
                }
            });
        }
        for (auto& t : threads) t.join();
    }
    std::cout << "Unsafe counter: " << unsafe_counter
              << " (expected " << N_THREADS * N_OPS << ")" << std::endl;

    // TODO: Version CORRIGEE avec std::atomic
    // Declare un std::atomic<int> et fais la meme chose
    // Le resultat doit etre exactement N_THREADS * N_OPS
    int safe_result = 0; // TODO: remplace par le vrai resultat

    std::cout << "Safe counter:   " << safe_result
              << " (expected " << N_THREADS * N_OPS << ")" << std::endl;
}

// =============================================================
// EXERCICE 2 : Producer-Consumer avec market data
// =============================================================
// Un producer genere des MarketTicks
// Un consumer les lit et calcule des statistiques
// Communication via un shared buffer + flag atomique

struct SharedBuffer {
    MarketTick tick;
    // TODO: Ajoute un std::atomic<bool> pour signaler qu'un nouveau tick est disponible
    // std::atomic<bool> has_data{false};
};

void exercise_producer_consumer() {
    constexpr int N_TICKS = 100000;
    SharedBuffer buffer;
    std::atomic<bool> done{false};

    // TODO: Implemente le producer
    // Pour chaque tick:
    //   1. Ecrit le tick dans buffer.tick
    //   2. Met buffer.has_data a true (release)
    //   3. Attend que le consumer lise (has_data redevient false)
    std::thread producer([&]() {
        for (int i = 0; i < N_TICKS; i++) {
            // TODO: produire le tick
        }
        done.store(true, std::memory_order_release);
    });

    // TODO: Implemente le consumer
    // Boucle tant que !done ou has_data:
    //   1. Attend que has_data soit true (busy-wait)
    //   2. Lit buffer.tick
    //   3. Met has_data a false (release)
    //   4. Accumule les stats
    long total_volume = 0;
    long tick_count = 0;

    std::thread consumer([&]() {
        // TODO: consommer les ticks
    });

    producer.join();
    consumer.join();

    std::cout << "Ticks processed: " << tick_count << std::endl;
    std::cout << "Total volume:    " << total_volume << std::endl;
}

// =============================================================
// EXERCICE 3 : Benchmark mutex vs atomic
// =============================================================
// Compare la latence d'increment avec mutex vs atomic

void exercise_benchmark() {
    constexpr int N = 1'000'000;

    // Benchmark mutex
    int mutex_counter = 0;
    std::mutex mtx;

    auto start = std::chrono::high_resolution_clock::now();
    // TODO: 4 threads incrementent mutex_counter avec lock_guard
    // Mesure le temps total
    auto end = std::chrono::high_resolution_clock::now();
    auto mutex_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // Benchmark atomic
    std::atomic<int> atomic_counter{0};

    start = std::chrono::high_resolution_clock::now();
    // TODO: 4 threads incrementent atomic_counter avec fetch_add
    // Mesure le temps total
    end = std::chrono::high_resolution_clock::now();
    auto atomic_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Mutex:  " << mutex_ns / 1000 << " us (counter=" << mutex_counter << ")" << std::endl;
    std::cout << "Atomic: " << atomic_ns / 1000 << " us (counter=" << atomic_counter.load() << ")" << std::endl;
    if (atomic_ns > 0) {
        std::cout << "Ratio:  " << (double)mutex_ns / atomic_ns << "x" << std::endl;
    }
}

int main() {
    std::cout << "=== Exercice 1: Data Race ===" << std::endl;
    exercise_data_race();

    std::cout << "\n=== Exercice 2: Producer-Consumer ===" << std::endl;
    exercise_producer_consumer();

    std::cout << "\n=== Exercice 3: Mutex vs Atomic ===" << std::endl;
    exercise_benchmark();

    return 0;
}
