// Chapitre 01 - Cache Optimization - SOLUTION
// Compilation: g++ -std=c++17 -O2 -o cache solution.cpp && ./cache

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>

// =============================================================
// SOLUTION 1 : Struct reorganisee - membres du plus grand au plus petit
// =============================================================
struct Order {
    double price;       // 8 bytes  (offset 0)
    long timestamp;     // 8 bytes  (offset 8)
    char symbol[8];     // 8 bytes  (offset 16)
    int quantity;       // 4 bytes  (offset 24)
    short exchange_id;  // 2 bytes  (offset 28)
    char side;          // 1 byte   (offset 30)
    bool is_active;     // 1 byte   (offset 31)
};  // Total: 32 bytes - zero padding!

// =============================================================
// SOLUTION 2 : Struct alignee sur cache line avec alignas(64)
// =============================================================
struct alignas(64) MarketTick {
    double bid_price;       // 8
    double ask_price;       // 8
    int bid_size;           // 4
    int ask_size;           // 4
    long sequence_number;   // 8
    // Total utile: 32 bytes, padding auto jusqu'a 64
};

// =============================================================
// SOLUTION 3 : Acces sequentiel vs random
// =============================================================
long long sum_sequential(const std::vector<int>& data) {
    long long sum = 0;
    for (size_t i = 0; i < data.size(); i++) {
        sum += data[i];
    }
    return sum;
}

long long sum_random(const std::vector<int>& data, const std::vector<int>& indices) {
    long long sum = 0;
    for (size_t i = 0; i < indices.size(); i++) {
        sum += data[indices[i]];
    }
    return sum;
}

int main() {
    // Test Solution 1
    std::cout << "=== Solution 1: Struct Padding ===" << std::endl;
    std::cout << "sizeof(Order) = " << sizeof(Order) << " bytes" << std::endl;
    static_assert(sizeof(Order) == 32, "Order devrait faire 32 bytes");

    // Test Solution 2
    std::cout << "\n=== Solution 2: Cache Line Alignment ===" << std::endl;
    std::cout << "sizeof(MarketTick) = " << sizeof(MarketTick) << " bytes" << std::endl;
    std::cout << "alignof(MarketTick) = " << alignof(MarketTick) << std::endl;
    static_assert(sizeof(MarketTick) == 64, "MarketTick devrait faire 64 bytes");
    static_assert(alignof(MarketTick) == 64, "MarketTick devrait etre aligne sur 64");

    // Test Solution 3
    std::cout << "\n=== Solution 3: Sequential vs Random ===" << std::endl;
    constexpr int N = 10'000'000;
    std::vector<int> data(N);
    for (int i = 0; i < N; i++) data[i] = i;

    std::vector<int> indices(N);
    for (int i = 0; i < N; i++) indices[i] = i;
    for (int i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        std::swap(indices[i], indices[j]);
    }

    auto start = std::chrono::high_resolution_clock::now();
    long long s1 = sum_sequential(data);
    auto end = std::chrono::high_resolution_clock::now();
    auto seq_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    long long s2 = sum_random(data, indices);
    end = std::chrono::high_resolution_clock::now();
    auto rand_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Sequential: " << seq_time << " us (sum=" << s1 << ")" << std::endl;
    std::cout << "Random:     " << rand_time << " us (sum=" << s2 << ")" << std::endl;
    if (seq_time > 0) {
        std::cout << "Ratio:      " << (double)rand_time / seq_time << "x plus lent" << std::endl;
    }

    return 0;
}
