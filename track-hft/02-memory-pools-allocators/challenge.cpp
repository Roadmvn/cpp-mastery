// Chapitre 02 - Memory Pools & Allocators - CHALLENGE
// Implementer un pool allocator complet pour des Order objects
// avec benchmark contre new/delete et arena allocator
// Compilation: g++ -std=c++17 -O2 -o challenge challenge.cpp && ./challenge

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cassert>
#include <cstring>

struct Order {
    double price;
    int quantity;
    int order_id;
    char side;       // 'B' or 'S'
    char symbol[7];  // ex: "AAPL"
};

// Pool Allocator avec statistiques
template<typename T, size_t PoolSize = 65536>
class PoolAllocator {
    union Slot {
        T object;
        Slot* next;
        Slot() {}
        ~Slot() {}
    };

    std::vector<Slot> pool_;
    Slot* free_list_ = nullptr;
    size_t allocated_ = 0;
    size_t peak_ = 0;

public:
    PoolAllocator() : pool_(PoolSize) {
        for (size_t i = 0; i < PoolSize - 1; i++) {
            pool_[i].next = &pool_[i + 1];
        }
        pool_[PoolSize - 1].next = nullptr;
        free_list_ = &pool_[0];
    }

    T* allocate() {
        if (!free_list_) return nullptr;
        Slot* slot = free_list_;
        free_list_ = free_list_->next;
        allocated_++;
        if (allocated_ > peak_) peak_ = allocated_;
        return reinterpret_cast<T*>(slot);
    }

    void deallocate(T* ptr) {
        Slot* slot = reinterpret_cast<Slot*>(ptr);
        slot->next = free_list_;
        free_list_ = slot;
        allocated_--;
    }

    size_t allocated() const { return allocated_; }
    size_t peak() const { return peak_; }
    size_t capacity() const { return PoolSize; }
};

// Arena Allocator
class ArenaAllocator {
    std::vector<char> buffer_;
    size_t offset_ = 0;
    size_t alloc_count_ = 0;

public:
    explicit ArenaAllocator(size_t size) : buffer_(size) {}

    template<typename T>
    T* allocate() {
        size_t alignment = alignof(T);
        size_t aligned = (offset_ + alignment - 1) & ~(alignment - 1);
        if (aligned + sizeof(T) > buffer_.size()) return nullptr;
        T* ptr = reinterpret_cast<T*>(&buffer_[aligned]);
        offset_ = aligned + sizeof(T);
        alloc_count_++;
        return ptr;
    }

    void reset() { offset_ = 0; alloc_count_ = 0; }
    size_t used() const { return offset_; }
    size_t count() const { return alloc_count_; }
};

struct BenchResult {
    double alloc_ns;
    double dealloc_ns;
    double total_ns;
};

BenchResult bench_new_delete(int N) {
    std::vector<Order*> ptrs(N);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        ptrs[i] = new Order{100.0 + i * 0.01, i % 1000, i, 'B', "AAPL"};
    }
    auto mid = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        delete ptrs[i];
    }
    auto end = std::chrono::high_resolution_clock::now();

    double alloc = std::chrono::duration<double, std::nano>(mid - start).count() / N;
    double dealloc = std::chrono::duration<double, std::nano>(end - mid).count() / N;
    return {alloc, dealloc, alloc + dealloc};
}

BenchResult bench_pool(int N) {
    PoolAllocator<Order> pool;
    std::vector<Order*> ptrs(N);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        ptrs[i] = pool.allocate();
        *ptrs[i] = Order{100.0 + i * 0.01, i % 1000, i, 'B', "AAPL"};
    }
    auto mid = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        pool.deallocate(ptrs[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();

    double alloc = std::chrono::duration<double, std::nano>(mid - start).count() / N;
    double dealloc = std::chrono::duration<double, std::nano>(end - mid).count() / N;
    return {alloc, dealloc, alloc + dealloc};
}

BenchResult bench_arena(int N) {
    ArenaAllocator arena(N * sizeof(Order) * 2);
    std::vector<Order*> ptrs(N);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        ptrs[i] = arena.allocate<Order>();
        *ptrs[i] = Order{100.0 + i * 0.01, i % 1000, i, 'B', "AAPL"};
    }
    auto mid = std::chrono::high_resolution_clock::now();
    arena.reset();
    auto end = std::chrono::high_resolution_clock::now();

    double alloc = std::chrono::duration<double, std::nano>(mid - start).count() / N;
    double dealloc = std::chrono::duration<double, std::nano>(end - mid).count();
    return {alloc, dealloc, alloc + dealloc / N};
}

void print_bar(double value, double max_val, int width = 30) {
    int bars = static_cast<int>(value / max_val * width);
    bars = std::min(bars, width);
    for (int i = 0; i < bars; i++) std::cout << "█";
    for (int i = bars; i < width; i++) std::cout << "░";
}

int main() {
    std::cout << "╔══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  MEMORY ALLOCATOR BENCHMARK 🏊                      ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;

    constexpr int N = 50000;
    std::cout << "\nAllocating/deallocating " << N << " Order objects..." << std::endl;
    std::cout << "sizeof(Order) = " << sizeof(Order) << " bytes\n" << std::endl;

    auto r_new = bench_new_delete(N);
    auto r_pool = bench_pool(N);
    auto r_arena = bench_arena(N);

    double max_alloc = std::max({r_new.alloc_ns, r_pool.alloc_ns, r_arena.alloc_ns});
    double max_dealloc = std::max({r_new.dealloc_ns, r_pool.dealloc_ns, r_arena.dealloc_ns});

    std::cout << std::fixed << std::setprecision(1);

    std::cout << "--- Allocation (ns/op) ---\n";
    std::cout << "  new/delete: ";
    print_bar(r_new.alloc_ns, max_alloc);
    std::cout << " " << r_new.alloc_ns << " ns\n";

    std::cout << "  Pool:       ";
    print_bar(r_pool.alloc_ns, max_alloc);
    std::cout << " " << r_pool.alloc_ns << " ns\n";

    std::cout << "  Arena:      ";
    print_bar(r_arena.alloc_ns, max_alloc);
    std::cout << " " << r_arena.alloc_ns << " ns\n";

    std::cout << "\n--- Deallocation (ns/op) ---\n";
    std::cout << "  new/delete: ";
    print_bar(r_new.dealloc_ns, max_dealloc);
    std::cout << " " << r_new.dealloc_ns << " ns\n";

    std::cout << "  Pool:       ";
    print_bar(r_pool.dealloc_ns, max_dealloc);
    std::cout << " " << r_pool.dealloc_ns << " ns\n";

    std::cout << "  Arena:      ";
    print_bar(r_arena.dealloc_ns, max_dealloc);
    std::cout << " " << r_arena.dealloc_ns << " ns (reset total)\n";

    std::cout << "\n--- Speedup vs new/delete ---\n";
    std::cout << "  Pool alloc:   " << r_new.alloc_ns / r_pool.alloc_ns << "x plus rapide\n";
    std::cout << "  Arena alloc:  " << r_new.alloc_ns / r_arena.alloc_ns << "x plus rapide\n";
    std::cout << "  Pool dealloc: " << r_new.dealloc_ns / r_pool.dealloc_ns << "x plus rapide\n";

    // Test de stress: alloc/dealloc intercales (simule un trading engine)
    std::cout << "\n--- Stress Test: Alloc/Dealloc intercales ---\n";
    PoolAllocator<Order> stress_pool;
    std::vector<Order*> active;
    active.reserve(1000);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        if (active.size() < 500 || (rand() % 2 == 0 && active.size() < 60000)) {
            Order* o = stress_pool.allocate();
            if (o) {
                *o = Order{100.0, 100, i, 'B', "TSLA"};
                active.push_back(o);
            }
        } else if (!active.empty()) {
            int idx = rand() % active.size();
            stress_pool.deallocate(active[idx]);
            active[idx] = active.back();
            active.pop_back();
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto stress_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    for (auto* o : active) stress_pool.deallocate(o);

    std::cout << "  100K operations mixtes: " << stress_us << " us\n";
    std::cout << "  Peak allocations: " << stress_pool.peak() << "\n";
    std::cout << "  ~" << stress_us * 1000 / 100000 << " ns/operation\n";

    std::cout << "\n╔══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  En HFT, JAMAIS de new/delete sur le hot path 🔥     ║" << std::endl;
    std::cout << "║  Pool pour alloc/dealloc individuels                  ║" << std::endl;
    std::cout << "║  Arena pour batch processing (reset par frame)        ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;

    return 0;
}
