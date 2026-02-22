// Matching Engine - main.cpp
// Compilation: g++ -std=c++17 -O2 -o matching_engine main.cpp && ./matching_engine

#include "matching_engine.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>

// ─────────────────────────────────────────────
// Scénario 1 : construction du book initial
// ─────────────────────────────────────────────

void scenario_build_book(MatchingEngine& me) {
    std::cout << "\n========================================\n";
    std::cout << "SCENARIO 1 : Construction du book initial\n";
    std::cout << "========================================\n\n";

    // Resting bids (pas de matching: asks vide)
    me.submit_order(Side::BID, 100.00, 5000, false);
    me.submit_order(Side::BID, 100.00, 3000, false);
    me.submit_order(Side::BID,  99.90, 8000, false);
    me.submit_order(Side::BID,  99.80, 4000, false);
    me.submit_order(Side::BID,  99.70, 6000, false);

    // Resting asks (pas de matching: aucun bid >= ask)
    me.submit_order(Side::ASK, 100.10, 5000, false);
    me.submit_order(Side::ASK, 100.10, 2000, false);
    me.submit_order(Side::ASK, 100.20, 7000, false);
    me.submit_order(Side::ASK, 100.30, 4000, false);
    me.submit_order(Side::ASK, 100.40, 3000, false);

    me.print_book("AAPL", 5);
    std::cout << "  Best bid=" << std::fixed << std::setprecision(2)
              << me.book.get_best_bid()
              << "  Best ask=" << me.book.get_best_ask()
              << "  Spread=" << me.book.get_spread() << "\n";
}

// ─────────────────────────────────────────────
// Scénario 2 : ordre agressif partiel
// ─────────────────────────────────────────────

void scenario_aggressive_bid(MatchingEngine& me) {
    std::cout << "\n========================================\n";
    std::cout << "SCENARIO 2 : Ordre BUY agressif (price-time priority)\n";
    std::cout << "========================================\n\n";

    // BUY 100.15, qty=9000 → doit matcher contre asks à 100.10 (total 7000)
    // puis 2000 restants restent dans le book comme resting BID à 100.15
    std::cout << ">>> BUY LIMIT 100.15 qty=9000\n";
    auto result = me.submit_order(Side::BID, 100.15, 9000, true);

    std::cout << "\n  Résumé: order_id=#" << result.order_id
              << "  trades=" << result.trades.size()
              << "  resting_qty=" << result.resting_qty << "\n";

    me.print_book("AAPL", 5);
}

// ─────────────────────────────────────────────
// Scénario 3 : ordre qui croise complètement
// ─────────────────────────────────────────────

void scenario_full_fill(MatchingEngine& me) {
    std::cout << "\n========================================\n";
    std::cout << "SCENARIO 3 : Ordre ASK qui traverse le spread\n";
    std::cout << "========================================\n\n";

    // SELL 99.90, qty=3000 → doit matcher contre BIDs >= 99.90
    // Best bid est à 100.15 (resting du scénario 2), puis 99.90
    std::cout << ">>> SELL LIMIT 99.90 qty=3000\n";
    auto result = me.submit_order(Side::ASK, 99.90, 3000, true);

    std::cout << "\n  Résumé: order_id=#" << result.order_id
              << "  trades=" << result.trades.size()
              << "  resting_qty=" << result.resting_qty << "\n";

    me.print_book("AAPL", 5);
}

// ─────────────────────────────────────────────
// Scénario 4 : annulations
// ─────────────────────────────────────────────

void scenario_cancellations(MatchingEngine& me) {
    std::cout << "\n========================================\n";
    std::cout << "SCENARIO 4 : Annulations d'ordres\n";
    std::cout << "========================================\n\n";

    // Annuler quelques ordres existants
    for (uint64_t id : {3ULL, 5ULL, 8ULL}) {
        bool ok = me.cancel_order(id);
        std::cout << "  Cancel #" << id << " : " << (ok ? "OK" : "FAIL (non trouvé)") << "\n";
    }

    me.print_book("AAPL", 5);
}

// ─────────────────────────────────────────────
// Scénario 5 : simulation de flux de marché
// ─────────────────────────────────────────────

void scenario_market_simulation(MatchingEngine& me) {
    std::cout << "\n========================================\n";
    std::cout << "SCENARIO 5 : Simulation flux de marché (100 ordres)\n";
    std::cout << "========================================\n\n";

    std::mt19937 rng(42);
    std::normal_distribution<double>  price_dist(100.10, 0.05);
    std::uniform_int_distribution<int> qty_dist(100, 5000);
    std::uniform_int_distribution<int> side_dist(0, 1);

    using Clock = std::chrono::high_resolution_clock;
    auto t0 = Clock::now();

    int n_trades = 0;
    for (int i = 0; i < 100; i++) {
        Side   side  = (side_dist(rng) == 0) ? Side::BID : Side::ASK;
        double price = std::round(price_dist(rng) * 100.0) / 100.0;
        int    qty   = qty_dist(rng);

        auto res = me.submit_order(side, price, qty, false);
        n_trades += static_cast<int>(res.trades.size());
    }

    auto t1 = Clock::now();
    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

    std::cout << "  100 ordres traités en " << std::fixed << std::setprecision(2) << ms << " ms\n";
    std::cout << "  Trades générés: " << n_trades << "\n";
    me.print_book("AAPL", 5);
}

// ─────────────────────────────────────────────
// Main
// ─────────────────────────────────────────────

int main() {
    std::cout << "╔══════════════════════════════════════════╗\n";
    std::cout << "║       MATCHING ENGINE - Projet HFT       ║\n";
    std::cout << "║   Price-Time Priority   Limit Orders     ║\n";
    std::cout << "╚══════════════════════════════════════════╝\n";

    MatchingEngine me;

    scenario_build_book(me);
    scenario_aggressive_bid(me);
    scenario_full_fill(me);
    scenario_cancellations(me);
    scenario_market_simulation(me);

    me.print_stats();

    return 0;
}
