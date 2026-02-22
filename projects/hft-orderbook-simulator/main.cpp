// HFT Order Book Simulator
// Compilation: g++ -std=c++17 -O2 -o simulator main.cpp && ./simulator
//
// Simule un flux d'ordres aléatoires injectés dans un order book.
// Affiche les stats: trades, spread moyen, latence p50/p99, VWAP.

#include <iostream>
#include <map>
#include <deque>
#include <unordered_map>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <cassert>
#include <cmath>
#include <string>

// ─────────────────────────────────────────────
// Types
// ─────────────────────────────────────────────

enum class Side { BID, ASK };

struct Order {
    uint64_t id;
    Side     side;
    double   price;
    int      quantity;
    int      orig_qty;
};

struct Trade {
    uint64_t trade_id;
    uint64_t buy_id;
    uint64_t sell_id;
    double   price;
    int      quantity;
};

// ─────────────────────────────────────────────
// PriceLevel
// ─────────────────────────────────────────────

struct PriceLevel {
    double            price        = 0.0;
    int               total_volume = 0;
    std::deque<Order> orders;

    void add_order(const Order& o) {
        price         = o.price;
        total_volume += o.quantity;
        orders.push_back(o);
    }

    bool remove_order(uint64_t id) {
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if (it->id == id) {
                total_volume -= it->quantity;
                orders.erase(it);
                return true;
            }
        }
        return false;
    }

    std::vector<Trade> consume(int& remaining, uint64_t incoming_id,
                               Side incoming_side, uint64_t& next_trade_id) {
        std::vector<Trade> trades;
        while (remaining > 0 && !orders.empty()) {
            Order& front = orders.front();
            int fill = std::min(remaining, front.quantity);

            Trade t;
            t.trade_id = next_trade_id++;
            t.buy_id   = (incoming_side == Side::BID) ? incoming_id : front.id;
            t.sell_id  = (incoming_side == Side::ASK) ? incoming_id : front.id;
            t.price    = front.price;
            t.quantity = fill;
            trades.push_back(t);

            front.quantity -= fill;
            total_volume   -= fill;
            remaining      -= fill;

            if (front.quantity == 0) orders.pop_front();
        }
        return trades;
    }

    bool is_empty() const { return orders.empty(); }
};

// ─────────────────────────────────────────────
// OrderBook
// ─────────────────────────────────────────────

class OrderBook {
public:
    std::map<double, PriceLevel, std::greater<double>> bids;
    std::map<double, PriceLevel>                       asks;

    struct OrderRef { Side side; double price; };
    std::unordered_map<uint64_t, OrderRef> order_index;

    void add_order(const Order& o) {
        if (o.side == Side::BID) bids[o.price].add_order(o);
        else                     asks[o.price].add_order(o);
        order_index[o.id] = {o.side, o.price};
    }

    bool cancel_order(uint64_t id) {
        auto it = order_index.find(id);
        if (it == order_index.end()) return false;
        auto [side, price] = it->second;
        if (side == Side::BID) {
            auto bit = bids.find(price);
            if (bit != bids.end()) {
                bit->second.remove_order(id);
                if (bit->second.is_empty()) bids.erase(bit);
            }
        } else {
            auto ait = asks.find(price);
            if (ait != asks.end()) {
                ait->second.remove_order(id);
                if (ait->second.is_empty()) asks.erase(ait);
            }
        }
        order_index.erase(it);
        return true;
    }

    double get_best_bid() const { return bids.empty() ? -1.0 : bids.begin()->first; }
    double get_best_ask() const { return asks.empty() ? -1.0 : asks.begin()->first; }
    double get_spread() const {
        double bb = get_best_bid(), ba = get_best_ask();
        return (bb > 0 && ba > 0) ? ba - bb : -1.0;
    }

    void print_snapshot(int depth = 3) const {
        // Asks (du plus haut au plus bas)
        std::vector<std::pair<double, int>> ask_levels;
        int cnt = 0;
        for (auto it = asks.begin(); it != asks.end() && cnt < depth; ++it, ++cnt)
            ask_levels.push_back({it->first, it->second.total_volume});
        std::reverse(ask_levels.begin(), ask_levels.end());

        for (auto& [p, v] : ask_levels)
            std::cout << "  ASK  " << std::fixed << std::setprecision(2) << p
                      << "  vol=" << std::setw(7) << v << "\n";

        double spread = get_spread();
        if (spread >= 0)
            std::cout << "  ─── SPREAD " << std::setprecision(3) << spread << " ───\n";

        cnt = 0;
        for (auto it = bids.begin(); it != bids.end() && cnt < depth; ++it, ++cnt)
            std::cout << "  BID  " << std::fixed << std::setprecision(2) << it->first
                      << "  vol=" << std::setw(7) << it->second.total_volume << "\n";
    }
};

// ─────────────────────────────────────────────
// MatchingEngine inline (self-contained)
// ─────────────────────────────────────────────

class MatchingEngine {
public:
    OrderBook          book;
    std::vector<Trade> trade_log;
    uint64_t           next_order_id = 1;
    uint64_t           next_trade_id = 1;

    long   total_trades  = 0;
    long   total_volume  = 0;
    double total_turnover = 0.0;

    std::vector<Trade> submit_order(Side side, double price, int qty) {
        uint64_t oid = next_order_id++;
        int remaining = qty;
        std::vector<Trade> all_trades;

        if (side == Side::BID) {
            while (remaining > 0 && !book.asks.empty()) {
                auto& [ap, level] = *book.asks.begin();
                if (ap > price) break;
                auto trades = level.consume(remaining, oid, Side::BID, next_trade_id);
                for (auto& t : trades) { all_trades.push_back(t); trade_log.push_back(t); }
                if (level.is_empty()) book.asks.erase(book.asks.begin());
            }
        } else {
            while (remaining > 0 && !book.bids.empty()) {
                auto& [bp, level] = *book.bids.begin();
                if (bp < price) break;
                auto trades = level.consume(remaining, oid, Side::ASK, next_trade_id);
                for (auto& t : trades) { all_trades.push_back(t); trade_log.push_back(t); }
                if (level.is_empty()) book.bids.erase(book.bids.begin());
            }
        }

        if (remaining > 0) {
            Order resting{oid, side, price, remaining, qty};
            book.add_order(resting);
        }

        for (auto& t : all_trades) {
            total_trades++;
            total_volume  += t.quantity;
            total_turnover += t.price * t.quantity;
        }

        return all_trades;
    }

    double vwap() const {
        return (total_volume > 0) ? total_turnover / total_volume : 0.0;
    }
};

// ─────────────────────────────────────────────
// Générateur d'ordres
// ─────────────────────────────────────────────
//
// Modèle:
//   mid[t+1] = mid[t] + N(0, sigma)
//   bid_price = round_to_tick(mid - spread/2 + noise)
//   ask_price = round_to_tick(mid + spread/2 + noise)
//   volume = LogNormal(mu=6, sigma=1)  médiane ~403

struct GeneratedOrder {
    Side   side;
    double price;
    int    quantity;
};

class OrderGenerator {
    std::mt19937 rng;
    std::normal_distribution<double>  price_noise;
    std::lognormal_distribution<double> vol_dist;
    std::uniform_int_distribution<int>  side_dist{0, 1};
    std::uniform_real_distribution<double> aggr_dist{0.0, 1.0};

    double mid_price;
    double spread;
    double sigma;
    double tick;

    double round_to_tick(double price) const {
        return std::round(price / tick) * tick;
    }

public:
    OrderGenerator(double init_price, double spread, double sigma,
                   double tick_size, uint64_t seed = 42)
        : rng(seed)
        , price_noise(0.0, sigma)
        , vol_dist(6.0, 0.8)   // log-normal: E[V] ≈ 665, median ≈ 403
        , mid_price(init_price)
        , spread(spread)
        , sigma(sigma)
        , tick(tick_size) {}

    GeneratedOrder next() {
        // Faire évoluer le mid price
        mid_price += price_noise(rng);
        mid_price  = std::max(50.0, mid_price);   // plancher à 50

        // Choisir le côté
        bool is_bid = (side_dist(rng) == 0);

        // Agressivité: 30% chance que l'ordre soit agressif (traverse le spread)
        double aggressiveness = aggr_dist(rng);
        double base_price;
        if (is_bid) {
            base_price = mid_price - spread / 2.0;
            if (aggressiveness < 0.30)
                base_price = mid_price + spread / 2.0 + price_noise(rng) * 0.5;
        } else {
            base_price = mid_price + spread / 2.0;
            if (aggressiveness < 0.30)
                base_price = mid_price - spread / 2.0 - std::abs(price_noise(rng)) * 0.5;
        }

        double price = round_to_tick(base_price);
        price = std::max(50.0, price);

        int qty = std::max(100, std::min(50000, (int)vol_dist(rng)));

        return {is_bid ? Side::BID : Side::ASK, price, qty};
    }

    double current_mid() const { return mid_price; }
};

// ─────────────────────────────────────────────
// Calcul percentiles
// ─────────────────────────────────────────────

struct Percentiles {
    double mean, p50, p90, p99, p999;
};

Percentiles compute_percentiles(std::vector<int64_t>& v) {
    if (v.empty()) return {};
    std::sort(v.begin(), v.end());
    int N = (int)v.size();
    auto at = [&](double p) { return (double)v[std::min(N-1, (int)(p*N))]; };
    double mean = std::accumulate(v.begin(), v.end(), 0.0) / N;
    return {mean, at(0.50), at(0.90), at(0.99), at(0.999)};
}

// ─────────────────────────────────────────────
// Main
// ─────────────────────────────────────────────

int main() {
    std::cout << "╔══════════════════════════════════════════════╗\n";
    std::cout << "║       HFT Order Book Simulator               ║\n";
    std::cout << "║  Marche aléatoire + matching price-time      ║\n";
    std::cout << "╚══════════════════════════════════════════════╝\n\n";

    // Paramètres
    constexpr int    N_ORDERS   = 10000;
    constexpr double INIT_PRICE = 100.00;
    constexpr double SPREAD     = 0.10;
    constexpr double SIGMA      = 0.03;   // volatilité / tick
    constexpr double TICK       = 0.01;

    std::cout << "Paramètres:\n";
    std::cout << "  N_ORDERS   = " << N_ORDERS << "\n";
    std::cout << "  Prix init  = " << INIT_PRICE << "\n";
    std::cout << "  Spread     = " << SPREAD << "\n";
    std::cout << "  Sigma/tick = " << SIGMA << "\n";
    std::cout << "  Tick size  = " << TICK << "\n\n";

    MatchingEngine engine;
    OrderGenerator gen(INIT_PRICE, SPREAD, SIGMA, TICK, 42);

    // Mesures de latence par ordre
    std::vector<int64_t> latencies_ns;
    latencies_ns.reserve(N_ORDERS);

    // Stats de spread
    std::vector<double> spreads;
    spreads.reserve(N_ORDERS);

    // Snapshots périodiques
    std::vector<int> snapshot_points = {500, 1000, 2000, 5000, N_ORDERS};
    int snap_idx = 0;

    using Clock = std::chrono::high_resolution_clock;

    std::cout << "Simulation de " << N_ORDERS << " ordres...\n\n";

    for (int i = 0; i < N_ORDERS; i++) {
        auto order = gen.next();

        auto t0 = Clock::now();
        engine.submit_order(order.side, order.price, order.quantity);
        auto t1 = Clock::now();

        int64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
        latencies_ns.push_back(ns);

        double spread = engine.book.get_spread();
        if (spread > 0) spreads.push_back(spread);

        // Snapshot
        if (snap_idx < (int)snapshot_points.size() && i + 1 == snapshot_points[snap_idx]) {
            std::cout << "--- Snapshot après ordre #" << (i + 1) << " ---\n";
            std::cout << "  Mid=" << std::fixed << std::setprecision(2) << gen.current_mid()
                      << "  Trades=" << engine.total_trades
                      << "  Volume=" << engine.total_volume << "\n";
            engine.book.print_snapshot(3);
            std::cout << "\n";
            snap_idx++;
        }
    }

    // ─── Stats finales ───
    auto lat = compute_percentiles(latencies_ns);
    double mean_spread = spreads.empty() ? 0.0 :
        std::accumulate(spreads.begin(), spreads.end(), 0.0) / spreads.size();

    // Prix initial et final (via les trades)
    double price_initial = INIT_PRICE;
    double price_final   = engine.trade_log.empty()
        ? gen.current_mid()
        : engine.trade_log.back().price;

    double price_change = price_final - price_initial;
    double price_change_pct = price_change / price_initial * 100.0;

    std::cout << "╔══════════════════════════════════════════════╗\n";
    std::cout << "║              STATS FINALES                   ║\n";
    std::cout << "╚══════════════════════════════════════════════╝\n\n";

    std::cout << "  Ordres traités    : " << N_ORDERS << "\n";
    std::cout << "  Trades générés    : " << engine.total_trades << "\n";
    std::cout << "  Volume total      : " << engine.total_volume << "\n";
    std::cout << "  VWAP              : " << std::fixed << std::setprecision(4)
              << engine.vwap() << "\n";
    std::cout << "  Prix initial      : " << std::setprecision(2) << price_initial << "\n";
    std::cout << "  Prix final (VWAP) : " << std::setprecision(2) << price_final
              << "  (" << (price_change >= 0 ? "+" : "") << std::setprecision(2) << price_change_pct << "%)\n";
    std::cout << "  Spread moyen      : " << std::setprecision(4) << mean_spread << "\n";

    std::cout << "\n  Latence de matching:\n";
    std::cout << "    mean  = " << std::setprecision(1) << lat.mean  << " ns\n";
    std::cout << "    p50   = " << lat.p50   << " ns\n";
    std::cout << "    p90   = " << lat.p90   << " ns\n";
    std::cout << "    p99   = " << lat.p99   << " ns\n";
    std::cout << "    p99.9 = " << lat.p999  << " ns\n";

    // Throughput
    double total_time_ns = std::accumulate(latencies_ns.begin(), latencies_ns.end(), 0.0);
    double orders_per_sec = N_ORDERS / (total_time_ns * 1e-9);
    std::cout << "\n  Throughput        : " << std::setprecision(0) << orders_per_sec
              << " ordres/sec\n";

    // Book final
    std::cout << "\n  Book final (top 5):\n";
    engine.book.print_snapshot(5);

    // Distribution des trades par prix (top 10)
    if (!engine.trade_log.empty()) {
        std::map<double, long, std::greater<double>> price_vol;
        for (auto& t : engine.trade_log)
            price_vol[t.price] += t.quantity;

        std::cout << "\n  Top 5 prix par volume tradé:\n";
        int n = 0;
        for (auto& [p, v] : price_vol) {
            if (n++ >= 5) break;
            std::cout << "    " << std::fixed << std::setprecision(2) << p
                      << "  vol=" << v << "\n";
        }
    }

    return 0;
}
