// Chapitre 03 - Lock-Free Structures
// Compilation: g++ -std=c++17 -O2 -pthread -o lockfree exercise.cpp && ./lockfree

#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <vector>
#include <cassert>

// =============================================================
// EXERCICE 1 : Compteur atomique avec CAS
// =============================================================
// Implemente un increment atomique en utilisant compare_exchange_weak
// au lieu de fetch_add (pour comprendre le mecanisme CAS)

class AtomicCounter {
    std::atomic<long> value_{0};
public:
    void increment() {
        // TODO: Utilise une boucle CAS pour incrementer value_
        // 1. Charge la valeur courante dans 'expected'
        // 2. Essaie compare_exchange_weak(expected, expected + 1)
        // 3. Si echec, recommence (expected est mis a jour automatiquement)
    }

    long get() const {
        return value_.load(std::memory_order_seq_cst);
    }
};

// =============================================================
// EXERCICE 2 : SPSC Queue Lock-Free
// =============================================================
// Single Producer Single Consumer queue basee sur un ring buffer
// C'est LA structure de communication HFT par excellence

template<typename T, size_t Size = 1024>
class SPSCQueue {
    static_assert((Size & (Size - 1)) == 0, "Size must be power of 2");

    T buffer_[Size];

    // Chaque position sur sa propre cache line pour eviter le false sharing
    alignas(64) std::atomic<size_t> write_pos_{0};
    alignas(64) std::atomic<size_t> read_pos_{0};

public:
    bool push(const T& item) {
        // TODO:
        // 1. Charge write_pos_ (relaxed - seul le producer ecrit)
        // 2. Verifie que la queue n'est pas pleine:
        //    write_pos - read_pos (acquire) != Size
        // 3. Ecris item dans buffer_[write_pos % Size]
        //    (utilise write_pos & (Size-1) car Size est puissance de 2)
        // 4. Store write_pos + 1 avec memory_order_release
        // 5. Return true si succes, false si plein
        return false;
    }

    bool pop(T& item) {
        // TODO:
        // 1. Charge read_pos_ (relaxed - seul le consumer lit)
        // 2. Verifie que la queue n'est pas vide:
        //    read_pos == write_pos (acquire)  vide
        // 3. Lis buffer_[read_pos % Size] dans item
        // 4. Store read_pos + 1 avec memory_order_release
        // 5. Return true si succes, false si vide
        return false;
    }

    size_t size() const {
        return write_pos_.load(std::memory_order_acquire) -
               read_pos_.load(std::memory_order_acquire);
    }
};

// Structure de market data pour les tests
struct MarketTick {
    double price;
    int quantity;
    long sequence;
};

int main() {
    // Test Exercice 1: Compteur atomique
    std::cout << "=== Exercice 1: Compteur Atomique CAS ===" << std::endl;
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
        std::cout << (actual == expected ? "PASS" : "FAIL - implemente le CAS!") << std::endl;
    }

    // Test Exercice 2: SPSC Queue
    std::cout << "\n=== Exercice 2: SPSC Queue ===" << std::endl;
    {
        SPSCQueue<MarketTick, 4096> queue;
        constexpr int N_MESSAGES = 1'000'000;
        std::atomic<bool> producer_done{false};
        long consumer_sum = 0;

        // Producer thread: envoie des market ticks
        std::thread producer([&]() {
            for (int i = 0; i < N_MESSAGES; i++) {
                MarketTick tick{100.0 + i * 0.01, i % 100 + 1, (long)i};
                while (!queue.push(tick)) {
                    // Queue pleine, spin (en vrai on ferait un yield)
                }
            }
            producer_done.store(true, std::memory_order_release);
        });

        // Consumer thread: consomme les market ticks
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
        if (elapsed_us > 0) {
            std::cout << "Throughput:  " << (long long)N_MESSAGES * 1'000'000 / elapsed_us << " msg/sec" << std::endl;
            std::cout << "Latency:     " << elapsed_us * 1000 / N_MESSAGES << " ns/msg" << std::endl;
        }
        std::cout << "Sum check:   " << (consumer_sum == expected_sum ? "PASS" : "FAIL") << std::endl;
    }

    return 0;
}
