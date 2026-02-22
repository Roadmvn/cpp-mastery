// Chapitre 02 - Memory Pools & Allocators
// Compilation: g++ -std=c++17 -O2 -o pool exercise.cpp && ./pool

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <cassert>

struct Order {
    double price;
    int quantity;
    int id;
    char side;  // 'B' ou 'S'
};

// =============================================================
// EXERCICE 1 : Implementer un Pool Allocator basique
// =============================================================
// Le pool pre-alloue un tableau de slots au demarrage.
// Chaque slot libre pointe vers le prochain via une free list.
// allocate() retourne le premier slot libre.
// deallocate() remet le slot en tete de la free list.

template<typename T, size_t PoolSize = 4096>
class PoolAllocator {
    // Un slot peut contenir soit un objet T, soit un pointeur vers le prochain slot libre
    union Slot {
        T object;
        Slot* next;
        Slot() {}
        ~Slot() {}
    };

    std::vector<Slot> pool_;
    Slot* free_list_ = nullptr;

public:
    PoolAllocator() : pool_(PoolSize) {
        // TODO: Chainer tous les slots ensemble dans la free list
        // pool_[0].next -> pool_[1].next -> ... -> pool_[N-1].next -> nullptr
        // free_list_ pointe vers pool_[0]
    }

    T* allocate() {
        // TODO: Prendre le premier slot de la free list
        // Avancer free_list_ au slot suivant
        // Retourner un pointeur vers l'objet T dans ce slot
        // Retourner nullptr si plus de slots disponibles
        return nullptr;
    }

    void deallocate(T* ptr) {
        // TODO: Remettre le slot en tete de la free list
        // Caster ptr en Slot*, faire pointer slot->next vers l'ancienne tete
        // free_list_ = slot
    }

    size_t capacity() const { return PoolSize; }
};

// =============================================================
// EXERCICE 2 : Implementer un Arena Allocator
// =============================================================
// L'arena alloue lineairement dans un buffer. Pas de free individuel.
// On libere tout d'un coup avec reset().

class ArenaAllocator {
    std::vector<char> buffer_;
    size_t offset_ = 0;

public:
    explicit ArenaAllocator(size_t size) : buffer_(size) {}

    template<typename T>
    T* allocate() {
        // TODO: Aligner offset_ sur alignof(T) (arrondi superieur)
        // Verifier qu'il reste assez de place
        // Retourner un pointeur vers buffer_[offset_] caste en T*
        // Avancer offset_ de sizeof(T)
        return nullptr;
    }

    void reset() {
        // TODO: Remettre offset_ a 0
    }

    size_t used() const { return offset_; }
    size_t capacity() const { return buffer_.size(); }
};

int main() {
    // Test Exercice 1: Pool Allocator
    std::cout << "=== Exercice 1: Pool Allocator ===" << std::endl;
    PoolAllocator<Order> pool;

    Order* o1 = pool.allocate();
    Order* o2 = pool.allocate();

    if (o1 && o2) {
        o1->price = 100.50;
        o1->quantity = 10;
        o1->side = 'B';

        o2->price = 101.00;
        o2->quantity = 5;
        o2->side = 'S';

        std::cout << "Order 1: " << o1->side << " " << o1->quantity << " @ " << o1->price << std::endl;
        std::cout << "Order 2: " << o2->side << " " << o2->quantity << " @ " << o2->price << std::endl;

        pool.deallocate(o1);
        pool.deallocate(o2);

        // Apres deallocation, on peut re-allouer
        Order* o3 = pool.allocate();
        if (o3) {
            std::cout << "Re-allocation reussie apres deallocation" << std::endl;
            pool.deallocate(o3);
        }
    } else {
        std::cout << "ERREUR: allocate() retourne nullptr - implemente le TODO!" << std::endl;
    }

    // Test Exercice 2: Arena Allocator
    std::cout << "\n=== Exercice 2: Arena Allocator ===" << std::endl;
    ArenaAllocator arena(4096);

    Order* a1 = arena.allocate<Order>();
    Order* a2 = arena.allocate<Order>();

    if (a1 && a2) {
        a1->price = 99.50;
        a2->price = 100.25;

        std::cout << "Arena used: " << arena.used() << " / " << arena.capacity() << " bytes" << std::endl;

        arena.reset();
        std::cout << "After reset: " << arena.used() << " / " << arena.capacity() << " bytes" << std::endl;
    } else {
        std::cout << "ERREUR: allocate() retourne nullptr - implemente le TODO!" << std::endl;
    }

    // Benchmark
    std::cout << "\n=== Benchmark: Pool vs new/delete ===" << std::endl;
    constexpr int N = 50000;
    std::vector<Order*> ptrs(N);

    // Pool
    PoolAllocator<Order, 65536> bench_pool;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) ptrs[i] = bench_pool.allocate();
    for (int i = 0; i < N; i++) {
        if (ptrs[i]) bench_pool.deallocate(ptrs[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto pool_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // new/delete
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) ptrs[i] = new Order();
    for (int i = 0; i < N; i++) delete ptrs[i];
    end = std::chrono::high_resolution_clock::now();
    auto new_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Pool:       " << pool_ns / N << " ns/op" << std::endl;
    std::cout << "new/delete: " << new_ns / N  << " ns/op" << std::endl;
    if (pool_ns > 0) {
        std::cout << "Speedup:    " << (double)new_ns / pool_ns << "x" << std::endl;
    }

    return 0;
}
