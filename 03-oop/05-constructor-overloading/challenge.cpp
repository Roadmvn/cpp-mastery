// ============================================================
// Chapitre 05 - Challenge HFT : Classe Order multi-constructeurs
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
// ============================================================
// Contexte : Un ordre de trading peut etre cree de plusieurs
// manieres selon le contexte : ordre de marche (juste symbol + qty),
// ordre limite (symbol + price + qty), ordre complet avec toutes
// les options. La delegation evite la duplication de la logique.
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cstdint>

enum class Side : uint8_t { BUY, SELL };
enum class OrderType : uint8_t { MARKET, LIMIT, STOP, STOP_LIMIT };
enum class TimeInForce : uint8_t { DAY, GTC, IOC, FOK };

std::string to_string(Side s) { return s == Side::BUY ? "BUY" : "SELL"; }

std::string to_string(OrderType t) {
    switch (t) {
        case OrderType::MARKET:     return "MARKET";
        case OrderType::LIMIT:      return "LIMIT";
        case OrderType::STOP:       return "STOP";
        case OrderType::STOP_LIMIT: return "STOP_LIMIT";
    }
    return "?";
}

std::string to_string(TimeInForce tif) {
    switch (tif) {
        case TimeInForce::DAY: return "DAY";
        case TimeInForce::GTC: return "GTC";
        case TimeInForce::IOC: return "IOC";
        case TimeInForce::FOK: return "FOK";
    }
    return "?";
}

class Order {
private:
    static uint64_t next_id;

    uint64_t order_id;
    std::string symbol;
    Side side;
    OrderType type;
    double price;
    double stop_price;
    uint32_t quantity;
    TimeInForce tif;
    int64_t timestamp_ns;

    static int64_t now_ns() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
        ).count();
    }

public:
    // Constructeur principal (complet)
    Order(std::string sym, Side s, OrderType t, double px, double stop_px,
          uint32_t qty, TimeInForce tf)
        : order_id(next_id++), symbol(std::move(sym)), side(s), type(t),
          price(px), stop_price(stop_px), quantity(qty), tif(tf),
          timestamp_ns(now_ns()) {}

    // Ordre LIMIT : delegation (pas de stop price)
    Order(std::string sym, Side s, double px, uint32_t qty, TimeInForce tf)
        : Order(std::move(sym), s, OrderType::LIMIT, px, 0.0, qty, tf) {}

    // Ordre LIMIT DAY : delegation (TIF par defaut)
    Order(std::string sym, Side s, double px, uint32_t qty)
        : Order(std::move(sym), s, px, qty, TimeInForce::DAY) {}

    // Ordre MARKET : delegation (pas de prix)
    Order(std::string sym, Side s, uint32_t qty)
        : Order(std::move(sym), s, OrderType::MARKET, 0.0, 0.0, qty, TimeInForce::IOC) {}

    // Copie interdite (chaque ordre est unique)
    Order(const Order&) = delete;
    Order& operator=(const Order&) = delete;

    // Move autorise
    Order(Order&&) = default;
    Order& operator=(Order&&) = default;

    void print() const {
        std::cout << std::fixed << std::setprecision(2)
                  << "Order #" << order_id
                  << " | " << to_string(side)
                  << " " << to_string(type)
                  << " | " << symbol
                  << " | Qty: " << quantity;
        if (type == OrderType::LIMIT || type == OrderType::STOP_LIMIT) {
            std::cout << " | Px: $" << price;
        }
        if (type == OrderType::STOP || type == OrderType::STOP_LIMIT) {
            std::cout << " | Stop: $" << stop_price;
        }
        std::cout << " | TIF: " << to_string(tif)
                  << " | TS: " << timestamp_ns << "ns"
                  << std::endl;
    }

    uint64_t get_id() const { return order_id; }
    const std::string& get_symbol() const { return symbol; }
};

uint64_t Order::next_id = 1000;

int main() {
    std::cout << "=== Challenge HFT : Order Multi-Constructors ===" << std::endl;

    // Differentes facons de creer un ordre
    std::cout << "\n--- Ordre MARKET (symbol + side + qty) ---" << std::endl;
    Order market("AAPL", Side::BUY, 500);
    market.print();

    std::cout << "\n--- Ordre LIMIT DAY (symbol + side + price + qty) ---" << std::endl;
    Order limit_day("MSFT", Side::SELL, 285.50, 200);
    limit_day.print();

    std::cout << "\n--- Ordre LIMIT GTC (+ TimeInForce) ---" << std::endl;
    Order limit_gtc("GOOGL", Side::BUY, 140.25, 100, TimeInForce::GTC);
    limit_gtc.print();

    std::cout << "\n--- Ordre STOP_LIMIT complet ---" << std::endl;
    Order stop_limit("TSLA", Side::SELL, OrderType::STOP_LIMIT,
                     180.00, 179.50, 300, TimeInForce::DAY);
    stop_limit.print();

    // Benchmark : creation d'ordres via differents constructeurs
    std::cout << "\n=== Benchmark : Creation d'ordres ===" << std::endl;
    constexpr int N = 500'000;
    std::vector<Order> orders;
    orders.reserve(N);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        switch (i % 4) {
            case 0: orders.push_back(Order("AAPL", Side::BUY, 100)); break;
            case 1: orders.push_back(Order("MSFT", Side::SELL, 285.0, 200)); break;
            case 2: orders.push_back(Order("GOOGL", Side::BUY, 140.0, 50, TimeInForce::FOK)); break;
            case 3: orders.push_back(Order("TSLA", Side::SELL, OrderType::STOP_LIMIT,
                                           180.0, 179.0, 100, TimeInForce::DAY)); break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << N << " ordres crees en " << us << " us" << std::endl;
    std::cout << "Debit: " << (N * 1'000'000LL / us) << " ordres/sec" << std::endl;
    std::cout << "Latence: " << (us * 1000.0 / N) << " ns/ordre" << std::endl;
    std::cout << "Dernier ID: " << orders.back().get_id() << std::endl;

    return 0;
}
