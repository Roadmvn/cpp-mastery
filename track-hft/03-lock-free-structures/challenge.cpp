// Chapitre 03 - Lock-Free Structures - CHALLENGE
// SPSC Queue complete avec benchmark mutex vs lock-free
// Compilation: g++ -std=c++17 -O2 -pthread -o challenge challenge.cpp && ./challenge

#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>
#include <vector>
#include <iomanip>

struct MarketTick {
    double price;
    int quantity;
    long sequence;
    char symbol[8];
};

// Lock-Free SPSC Queue
template<typename T, size_t Size = 8192>
class SPSCQueue {
    static_assert((Size & (Size - 1)) == 0, "Size must be power of 2");
    T buffer_[Size];
    alignas(64) std::atomic<size_t> write_pos_{0};
    alignas(64) std::atomic<size_t> read_pos_{0};

public:
    bool push(const T& item) {
        size_t w = write_pos_.load(std::memory_order_relaxed);
        if (w - read_pos_.load(std::memory_order_acquire) == Size) return false;
        buffer_[w & (Size - 1)] = item;
        write_pos_.store(w + 1, std::memory_order_release);
        return true;
    }

    bool pop(T& item) {
        size_t r = read_pos_.load(std::memory_order_relaxed);
        if (r == write_pos_.load(std::memory_order_acquire)) return false;
        item = buffer_[r & (Size - 1)];
        read_pos_.store(r + 1, std::memory_order_release);
        return true;
    }
};

// Mutex-based Queue (pour comparaison)
template<typename T>
class MutexQueue {
    std::queue<T> queue_;
    std::mutex mutex_;

public:
    bool push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
        return true;
    }

    bool pop(T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) return false;
        item = queue_.front();
        queue_.pop();
        return true;
    }
};

template<typename QueueType>
double benchmark_queue(QueueType& queue, int n_messages) {
    long consumer_sum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    std::thread producer([&]() {
        for (int i = 0; i < n_messages; i++) {
            MarketTick tick{100.0 + i * 0.01, i % 100 + 1, (long)i, "AAPL"};
            while (!queue.push(tick)) {}
        }
    });

    std::thread consumer([&]() {
        long count = 0;
        MarketTick tick;
        while (count < n_messages) {
            if (queue.pop(tick)) {
                consumer_sum += tick.sequence;
                count++;
            }
        }
    });

    producer.join();
    consumer.join();

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::micro>(end - start).count();
}

void print_bar(double value, double max_val, int width = 35) {
    int bars = static_cast<int>(value / max_val * width);
    bars = std::min(bars, width);
    for (int i = 0; i < bars; i++) std::cout << "█";
    for (int i = bars; i < width; i++) std::cout << "░";
}

int main() {
    std::cout << "╔══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  LOCK-FREE vs MUTEX BENCHMARK 🔓                    ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;

    std::vector<int> sizes = {100'000, 500'000, 1'000'000, 5'000'000};

    std::cout << "\n" << std::setw(12) << "Messages"
              << std::setw(15) << "Lock-Free"
              << std::setw(15) << "Mutex"
              << std::setw(10) << "Speedup" << std::endl;
    std::cout << std::string(52, '-') << std::endl;

    for (int n : sizes) {
        // Lock-free
        SPSCQueue<MarketTick> lf_queue;
        double lf_us = benchmark_queue(lf_queue, n);

        // Mutex
        MutexQueue<MarketTick> mx_queue;
        double mx_us = benchmark_queue(mx_queue, n);

        std::cout << std::fixed << std::setprecision(0);
        std::cout << std::setw(12) << n
                  << std::setw(12) << lf_us << " us"
                  << std::setw(12) << mx_us << " us"
                  << std::setw(8) << std::setprecision(1) << mx_us / lf_us << "x"
                  << std::endl;
    }

    // Latence par message
    std::cout << "\n--- Latence par message (ns/msg) ---\n" << std::endl;

    constexpr int N = 1'000'000;

    SPSCQueue<MarketTick> lf_queue;
    double lf_us = benchmark_queue(lf_queue, N);
    double lf_ns = lf_us * 1000 / N;

    MutexQueue<MarketTick> mx_queue;
    double mx_us = benchmark_queue(mx_queue, N);
    double mx_ns = mx_us * 1000 / N;

    double max_ns = std::max(lf_ns, mx_ns);

    std::cout << "  Lock-Free: ";
    print_bar(lf_ns, max_ns);
    std::cout << std::fixed << std::setprecision(1) << " " << lf_ns << " ns/msg" << std::endl;

    std::cout << "  Mutex:     ";
    print_bar(mx_ns, max_ns);
    std::cout << " " << mx_ns << " ns/msg" << std::endl;

    // Throughput
    std::cout << "\n--- Throughput ---\n" << std::endl;
    double lf_throughput = (double)N / lf_us * 1'000'000;
    double mx_throughput = (double)N / mx_us * 1'000'000;

    std::cout << std::fixed << std::setprecision(0);
    std::cout << "  Lock-Free: " << lf_throughput / 1'000'000 << "M msg/sec" << std::endl;
    std::cout << "  Mutex:     " << mx_throughput / 1'000'000 << "M msg/sec" << std::endl;

    // Correctness test
    std::cout << "\n--- Correctness Test ---\n" << std::endl;
    {
        SPSCQueue<MarketTick, 256> small_queue;
        constexpr int TEST_N = 1'000'000;
        long sum = 0;

        std::thread prod([&]() {
            for (int i = 0; i < TEST_N; i++) {
                MarketTick tick{0, 0, (long)i, ""};
                while (!small_queue.push(tick)) {}
            }
        });

        std::thread cons([&]() {
            long count = 0;
            MarketTick tick;
            while (count < TEST_N) {
                if (small_queue.pop(tick)) {
                    sum += tick.sequence;
                    count++;
                }
            }
        });

        prod.join();
        cons.join();

        long expected = (long)(TEST_N - 1) * TEST_N / 2;
        std::cout << "  Small buffer (256 slots), " << TEST_N << " messages: "
                  << (sum == expected ? "PASS" : "FAIL") << std::endl;
    }

    std::cout << "\n╔══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  En HFT, la SPSC queue lock-free est la norme 🚀     ║" << std::endl;
    std::cout << "║  Mutex = contention = latence imprevisible           ║" << std::endl;
    std::cout << "║  Lock-free = deterministe = victoire                 ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;

    return 0;
}
