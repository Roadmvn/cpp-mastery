#pragma once
// matching_engine.h - Moteur de matching prix-temps
// Compilation: g++ -std=c++17 -O2 -o matching_engine main.cpp && ./matching_engine

#include "order_book.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>

// ─────────────────────────────────────────────
// MatchingEngine
// ─────────────────────────────────────────────
//
// Flux de matching pour un ordre BID entrant:
//
//  ┌──────────────────────────────────────────────────────────────┐
//  │  submit_order(BUY, price_limit, qty)                        │
//  │                                                              │
//  │  while remaining > 0 AND best_ask <= price_limit:           │
//  │      level = asks.begin()                                   │
//  │      trades += level.consume(remaining, ...)                │
//  │      if level.is_empty() → asks.erase(begin)               │
//  │                                                              │
//  │  if remaining > 0:                                          │
//  │      add_order(resting BID @ price_limit, qty=remaining)   │
//  └──────────────────────────────────────────────────────────────┘

class MatchingEngine {
public:
    OrderBook              book;
    std::vector<Trade>     trade_log;
    uint64_t               next_order_id = 1;
    uint64_t               next_trade_id = 1;

    // Stats globales
    long   total_trades  = 0;
    long   total_volume  = 0;
    double total_turnover = 0.0;

    struct SubmitResult {
        uint64_t          order_id;
        std::vector<Trade> trades;
        int               resting_qty;   // quantité qui est restée dans le book
    };

    // Soumettre un ordre. Retourne les trades générés.
    SubmitResult submit_order(Side side, double price, int qty,
                              bool verbose = true) {
        uint64_t oid = next_order_id++;
        Order incoming{oid, side, price, qty, qty};

        std::vector<Trade> all_trades;
        int remaining = qty;

        if (side == Side::BID) {
            // Matcher contre les asks: asks dont le prix ≤ price_limit
            while (remaining > 0 && !book.asks.empty()) {
                auto& [best_ask_price, level] = *book.asks.begin();
                if (best_ask_price > price) break;   // plus rien à matcher

                auto trades = level.consume(remaining, oid, Side::BID, next_trade_id);
                for (auto& t : trades) {
                    all_trades.push_back(t);
                    trade_log.push_back(t);
                    if (verbose) print_trade(t);
                }

                if (level.is_empty())
                    book.asks.erase(book.asks.begin());
                // Mettre à jour l'index: retirer les ordres exécutés complètement
                // (simplifié: on ne gère pas le partial fill dans l'index ici)
            }
        } else {
            // Matcher contre les bids: bids dont le prix ≥ price_limit
            while (remaining > 0 && !book.bids.empty()) {
                auto& [best_bid_price, level] = *book.bids.begin();
                if (best_bid_price < price) break;

                auto trades = level.consume(remaining, oid, Side::ASK, next_trade_id);
                for (auto& t : trades) {
                    all_trades.push_back(t);
                    trade_log.push_back(t);
                    if (verbose) print_trade(t);
                }

                if (level.is_empty())
                    book.bids.erase(book.bids.begin());
            }
        }

        // Ordre restant: resting dans le book
        int resting_qty = remaining;
        if (remaining > 0) {
            Order resting{oid, side, price, remaining, qty};
            book.add_order(resting);
        }

        // Mettre à jour stats
        for (auto& t : all_trades) {
            total_trades++;
            total_volume  += t.quantity;
            total_turnover += t.price * t.quantity;
        }

        return {oid, all_trades, resting_qty};
    }

    bool cancel_order(uint64_t id) {
        return book.cancel_order(id);
    }

    double vwap() const {
        return (total_volume > 0) ? total_turnover / total_volume : 0.0;
    }

    void print_book(const std::string& symbol = "ME", int depth = 5) const {
        book.print(symbol, depth);
    }

    void print_stats() const {
        std::cout << "\n=== Stats Matching Engine ===\n";
        std::cout << "  Ordres soumis  : " << book.total_orders << "\n";
        std::cout << "  Annulations    : " << book.total_cancels << "\n";
        std::cout << "  Trades exécutés: " << total_trades << "\n";
        std::cout << "  Volume total   : " << total_volume << "\n";
        if (total_volume > 0)
            std::cout << "  VWAP           : " << std::fixed << std::setprecision(4)
                      << vwap() << "\n";
        std::cout << "  Spread actuel  : ";
        double spread = book.get_spread();
        if (spread >= 0)
            std::cout << std::setprecision(2) << spread << "\n";
        else
            std::cout << "N/A\n";

        std::cout << "\n  Derniers trades:\n";
        int show = std::min(10, (int)trade_log.size());
        int start = std::max(0, (int)trade_log.size() - show);
        for (int i = start; i < (int)trade_log.size(); i++) {
            const auto& t = trade_log[i];
            std::cout << "    #" << t.trade_id
                      << "  " << std::fixed << std::setprecision(2) << t.price
                      << "  qty=" << t.quantity
                      << "  buy=" << t.buy_order_id
                      << "  sell=" << t.sell_order_id << "\n";
        }
    }

private:
    void print_trade(const Trade& t) const {
        std::cout << "  TRADE #" << t.trade_id
                  << "  " << std::fixed << std::setprecision(2) << t.price
                  << "  qty=" << std::setw(6) << t.quantity
                  << "  buy=#" << t.buy_order_id
                  << "  sell=#" << t.sell_order_id << "\n";
    }
};
