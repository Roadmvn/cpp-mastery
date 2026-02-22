// ============================================================
// Chapitre 01 - Challenge HFT : Struct Order
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
// ============================================================
// Contexte : En trading haute frequence, chaque ordre doit etre
// represente de facon compacte et efficace. Les structs sont
// ideales pour ca : acces direct, pas d'overhead de vtable.
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>

enum class Side : uint8_t { BUY, SELL };

struct Order {
    std::string symbol;
    double price;
    uint32_t qty;
    Side side;
    int64_t timestamp;  // nanosecondes depuis epoch

    static int64_t now_ns() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
        ).count();
    }

    void print() const {
        std::cout << std::fixed << std::setprecision(2)
                  << "[" << timestamp << "] "
                  << (side == Side::BUY ? "BUY " : "SELL")
                  << " " << std::setw(6) << symbol
                  << " | Qty: " << std::setw(5) << qty
                  << " | Price: $" << std::setw(10) << price
                  << std::endl;
    }
};

struct OrderBook {
    std::string symbol;
    std::vector<Order> bids;  // Ordres d'achat (tries par prix decroissant)
    std::vector<Order> asks;  // Ordres de vente (tries par prix croissant)

    void add_order(const Order& order) {
        if (order.side == Side::BUY) {
            bids.push_back(order);
            std::sort(bids.begin(), bids.end(),
                [](const Order& a, const Order& b) { return a.price > b.price; });
        } else {
            asks.push_back(order);
            std::sort(asks.begin(), asks.end(),
                [](const Order& a, const Order& b) { return a.price < b.price; });
        }
    }

    double spread() const {
        if (bids.empty() || asks.empty()) return 0.0;
        return asks.front().price - bids.front().price;
    }

    double mid_price() const {
        if (bids.empty() || asks.empty()) return 0.0;
        return (asks.front().price + bids.front().price) / 2.0;
    }

    void print_book() const {
        std::cout << "\n===== Order Book : " << symbol << " =====" << std::endl;
        std::cout << "--- ASKS (vente) ---" << std::endl;
        for (auto it = asks.rbegin(); it != asks.rend(); ++it) {
            it->print();
        }
        std::cout << "--- SPREAD: $" << std::fixed << std::setprecision(2)
                  << spread() << " | MID: $" << mid_price() << " ---" << std::endl;
        std::cout << "--- BIDS (achat) ---" << std::endl;
        for (const auto& b : bids) {
            b.print();
        }
        std::cout << "============================\n" << std::endl;
    }
};

int main() {
    std::cout << "=== Challenge HFT : Order Book ===" << std::endl;

    OrderBook book;
    book.symbol = "AAPL";

    // Simulation d'ordres d'achat
    book.add_order({"AAPL", 185.50, 100, Side::BUY,  Order::now_ns()});
    book.add_order({"AAPL", 185.45, 250, Side::BUY,  Order::now_ns()});
    book.add_order({"AAPL", 185.40, 500, Side::BUY,  Order::now_ns()});
    book.add_order({"AAPL", 185.30, 150, Side::BUY,  Order::now_ns()});

    // Simulation d'ordres de vente
    book.add_order({"AAPL", 185.55, 200, Side::SELL, Order::now_ns()});
    book.add_order({"AAPL", 185.60, 300, Side::SELL, Order::now_ns()});
    book.add_order({"AAPL", 185.70, 100, Side::SELL, Order::now_ns()});
    book.add_order({"AAPL", 185.80, 400, Side::SELL, Order::now_ns()});

    book.print_book();

    // Benchmark : combien d'ordres on peut creer par seconde
    std::cout << "=== Benchmark : Creation d'ordres ===" << std::endl;
    constexpr int N = 1'000'000;
    std::vector<Order> orders;
    orders.reserve(N);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        orders.push_back({"AAPL", 185.50 + (i % 100) * 0.01,
                          static_cast<uint32_t>(100 + i % 1000),
                          (i % 2 == 0) ? Side::BUY : Side::SELL,
                          Order::now_ns()});
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << N << " ordres crees en " << duration.count() << " us" << std::endl;
    std::cout << "Debit: " << (N * 1'000'000LL / duration.count())
              << " ordres/sec" << std::endl;
    std::cout << "Latence moyenne: " << (duration.count() * 1000.0 / N)
              << " ns/ordre" << std::endl;

    return 0;
}
