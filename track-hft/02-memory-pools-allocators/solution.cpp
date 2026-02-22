// Chapitre 02 - Memory Pools & Allocators - SOLUTION
// Compilation: g++ -std=c++17 -O2 -o pool solution.cpp && ./pool

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <cassert>

struct Order {
    double price;
    int quantity;
    int id;
    char side;
};

// =============================================================
// SOLUTION 1 : Pool Allocator
// =============================================================
template<typename T, size_t PoolSize = 4096>
class PoolAllocator {
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
        return reinterpret_cast<T*>(slot);
    }

    void deallocate(T* ptr) {
        Slot* slot = reinterpret_cast<Slot*>(ptr);
        slot->next = free_list_;
        free_list_ = slot;
    }

    size_t capacity() const { return PoolSize; }
};

// =============================================================
// SOLUTION 2 : Arena Allocator
// =============================================================
class ArenaAllocator {
    std::vector<char> buffer_;
    size_t offset_ = 0;

public:
    explicit ArenaAllocator(size_t size) : buffer_(size) {}

    template<typename T>
    T* allocate() {
        // Aligner sur alignof(T)
        size_t alignment = alignof(T);
        size_t aligned_offset = (offset_ + alignment - 1) & ~(alignment - 1);

        if (aligned_offset + sizeof(T) > buffer_.size()) return nullptr;

        T* ptr = reinterpret_cast<T*>(&buffer_[aligned_offset]);
        offset_ = aligned_offset + sizeof(T);
        return ptr;
    }

    void reset() {
        offset_ = 0;
    }

    size_t used() const { return offset_; }
    size_t capacity() const { return buffer_.size(); }
};

int main() {
    // Test Pool Allocator
    std::cout << "=== Solution 1: Pool Allocator ===" << std::endl;
    PoolAllocator<Order> pool;

    Order* o1 = pool.allocate();
    Order* o2 = pool.allocate();

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

    Order* o3 = pool.allocate();
    std::cout << "Re-allocation reussie: ptr = " << o3 << std::endl;
    pool.deallocate(o3);

    // Test Arena Allocator
    std::cout << "\n=== Solution 2: Arena Allocator ===" << std::endl;
    ArenaAllocator arena(4096);

    Order* a1 = arena.allocate<Order>();
    Order* a2 = arena.allocate<Order>();
    a1->price = 99.50;
    a2->price = 100.25;

    std::cout << "Arena used: " << arena.used() << " / " << arena.capacity() << " bytes" << std::endl;
    arena.reset();
    std::cout << "After reset: " << arena.used() << " / " << arena.capacity() << " bytes" << std::endl;

    // Benchmark
    std::cout << "\n=== Benchmark: Pool vs new/delete ===" << std::endl;
    constexpr int N = 50000;
    std::vector<Order*> ptrs(N);

    PoolAllocator<Order, 65536> bench_pool;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) ptrs[i] = bench_pool.allocate();
    for (int i = 0; i < N; i++) bench_pool.deallocate(ptrs[i]);
    auto end = std::chrono::high_resolution_clock::now();
    auto pool_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) ptrs[i] = new Order();
    for (int i = 0; i < N; i++) delete ptrs[i];
    end = std::chrono::high_resolution_clock::now();
    auto new_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Pool:       " << pool_ns / N << " ns/op" << std::endl;
    std::cout << "new/delete: " << new_ns / N  << " ns/op" << std::endl;
    std::cout << "Speedup:    " << (double)new_ns / pool_ns << "x" << std::endl;

    return 0;
}
