// ============================================================
// Chapitre 03 - Challenge HFT : Classe Ticker
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
// ============================================================
// Contexte : Un Ticker represente les donnees de marche en temps
// reel pour un instrument financier. Il agregue les prix, calcule
// des statistiques, et maintient un historique des derniers ticks.
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <iomanip>

class Ticker {
private:
    std::string symbol;
    double bid = 0.0;              // Meilleur prix d'achat
    double ask = 0.0;              // Meilleur prix de vente
    double last_price = 0.0;       // Dernier prix echange
    uint64_t volume = 0;           // Volume total
    int64_t last_update_ns = 0;    // Timestamp du dernier update

    std::vector<double> price_history;
    static constexpr size_t MAX_HISTORY = 1000;

    static int64_t now_ns() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
        ).count();
    }

public:
    void init(const std::string& sym, double initial_bid, double initial_ask) {
        symbol = sym;
        bid = initial_bid;
        ask = initial_ask;
        last_price = (bid + ask) / 2.0;
        last_update_ns = now_ns();
    }

    void update_quote(double new_bid, double new_ask, uint32_t qty) {
        bid = new_bid;
        ask = new_ask;
        last_price = (new_bid + new_ask) / 2.0;
        volume += qty;
        last_update_ns = now_ns();

        price_history.push_back(last_price);
        if (price_history.size() > MAX_HISTORY) {
            price_history.erase(price_history.begin());
        }
    }

    double spread() const { return ask - bid; }
    double spread_bps() const { return (spread() / mid_price()) * 10000.0; }
    double mid_price() const { return (bid + ask) / 2.0; }
    const std::string& get_symbol() const { return symbol; }
    uint64_t get_volume() const { return volume; }

    double vwap() const {
        if (price_history.empty()) return 0.0;
        double sum = std::accumulate(price_history.begin(), price_history.end(), 0.0);
        return sum / static_cast<double>(price_history.size());
    }

    double volatility() const {
        if (price_history.size() < 2) return 0.0;
        double mean = vwap();
        double sq_sum = 0.0;
        for (double p : price_history) {
            double diff = p - mean;
            sq_sum += diff * diff;
        }
        return std::sqrt(sq_sum / static_cast<double>(price_history.size() - 1));
    }

    double high() const {
        if (price_history.empty()) return 0.0;
        return *std::max_element(price_history.begin(), price_history.end());
    }

    double low() const {
        if (price_history.empty()) return 0.0;
        return *std::min_element(price_history.begin(), price_history.end());
    }

    void print() const {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "=== " << symbol << " ===" << std::endl;
        std::cout << "  Bid:        $" << bid << std::endl;
        std::cout << "  Ask:        $" << ask << std::endl;
        std::cout << "  Spread:     $" << spread()
                  << " (" << std::setprecision(1) << spread_bps() << " bps)" << std::endl;
        std::cout << std::setprecision(2);
        std::cout << "  Mid:        $" << mid_price() << std::endl;
        std::cout << "  Last:       $" << last_price << std::endl;
        std::cout << "  Volume:     " << volume << std::endl;
        std::cout << "  High:       $" << high() << std::endl;
        std::cout << "  Low:        $" << low() << std::endl;
        std::cout << "  VWAP:       $" << vwap() << std::endl;
        std::cout << "  Volatility: $" << volatility() << std::endl;
        std::cout << "  Ticks:      " << price_history.size() << std::endl;
    }
};

int main() {
    std::cout << "=== Challenge HFT : Market Data Ticker ===" << std::endl;

    Ticker aapl;
    aapl.init("AAPL", 185.40, 185.45);

    // Simuler 500 ticks de marche
    double base_bid = 185.40;
    for (int i = 0; i < 500; ++i) {
        double noise = ((i * 7 + 13) % 100 - 50) * 0.001;  // Deterministe
        double new_bid = base_bid + noise;
        double new_ask = new_bid + 0.05 + ((i % 10) * 0.001);
        uint32_t qty = 100 + (i * 31) % 900;
        aapl.update_quote(new_bid, new_ask, qty);
        base_bid += noise * 0.1;  // Drift leger
    }

    aapl.print();

    // Benchmark : combien de ticks on peut traiter par seconde
    std::cout << "\n=== Benchmark : Throughput des ticks ===" << std::endl;
    Ticker bench;
    bench.init("BENCH", 100.0, 100.05);

    constexpr int N = 1'000'000;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        double b = 100.0 + (i % 100) * 0.01;
        bench.update_quote(b, b + 0.05, 100);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << N << " ticks traites en " << us << " us" << std::endl;
    std::cout << "Debit: " << (N * 1'000'000LL / us) << " ticks/sec" << std::endl;
    std::cout << "Latence: " << (us * 1000.0 / N) << " ns/tick" << std::endl;

    return 0;
}
