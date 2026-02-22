#pragma once
// order_book.h - Order Book avec price-time priority
// Compilation: g++ -std=c++17 -O2 -o matching_engine main.cpp && ./matching_engine

#include <map>
#include <deque>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cassert>

// ─────────────────────────────────────────────
// Types fondamentaux
// ─────────────────────────────────────────────

enum class Side { BID, ASK };

inline std::string side_str(Side s) { return s == Side::BID ? "BID" : "ASK"; }

struct Order {
    uint64_t    id;
    Side        side;
    double      price;
    int         quantity;     // quantité restante
    int         orig_qty;     // quantité originale (pour affichage)
};

struct Trade {
    uint64_t trade_id;
    uint64_t buy_order_id;
    uint64_t sell_order_id;
    double   price;
    int      quantity;
};

// ─────────────────────────────────────────────
// PriceLevel - un niveau de prix
// ─────────────────────────────────────────────
//
//  Maintient une file FIFO d'ordres au même prix.
//  L'ordre d'arrivée détermine la priorité d'exécution.
//
//  ┌───────────────────────────────────────────────┐
//  │  PriceLevel @ 100.30                          │
//  │  total_volume = 8000                          │
//  │  orders: [O1 qty=3000][O2 qty=2000][O3 qty=3000] │
//  │           ↑ PREMIER EXÉCUTÉ (FIFO)            │
//  └───────────────────────────────────────────────┘

struct PriceLevel {
    double            price        = 0.0;
    int               total_volume = 0;
    std::deque<Order> orders;

    void add_order(const Order& o) {
        assert(o.price == price || price == 0.0);
        price         = o.price;
        total_volume += o.quantity;
        orders.push_back(o);
    }

    // Retirer un ordre par id. Retourne true si trouvé.
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

    // Consommer qty depuis le front (FIFO).
    // Génère des trades contre l'ordre incoming.
    // Modifie remaining_qty en place.
    std::vector<Trade> consume(int& remaining_qty,
                               uint64_t incoming_id,
                               Side incoming_side,
                               uint64_t& next_trade_id) {
        std::vector<Trade> trades;

        while (remaining_qty > 0 && !orders.empty()) {
            Order& front = orders.front();
            int fill     = std::min(remaining_qty, front.quantity);

            Trade t;
            t.trade_id      = next_trade_id++;
            t.buy_order_id  = (incoming_side == Side::BID) ? incoming_id : front.id;
            t.sell_order_id = (incoming_side == Side::ASK) ? incoming_id : front.id;
            t.price         = front.price;
            t.quantity      = fill;
            trades.push_back(t);

            front.quantity -= fill;
            total_volume   -= fill;
            remaining_qty  -= fill;

            if (front.quantity == 0)
                orders.pop_front();
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
    // bids: prix décroissant (best bid = begin())
    std::map<double, PriceLevel, std::greater<double>> bids;
    // asks: prix croissant (best ask = begin())
    std::map<double, PriceLevel>                       asks;

    struct OrderRef { Side side; double price; };
    std::unordered_map<uint64_t, OrderRef> order_index;

    // Statistiques
    long   total_orders  = 0;
    long   total_cancels = 0;

    void add_order(const Order& o) {
        if (o.side == Side::BID) {
            bids[o.price].add_order(o);
        } else {
            asks[o.price].add_order(o);
        }
        order_index[o.id] = {o.side, o.price};
        ++total_orders;
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
        ++total_cancels;
        return true;
    }

    double get_best_bid() const {
        return bids.empty() ? -1.0 : bids.begin()->first;
    }

    double get_best_ask() const {
        return asks.empty() ? -1.0 : asks.begin()->first;
    }

    double get_spread() const {
        double bb = get_best_bid(), ba = get_best_ask();
        return (bb > 0 && ba > 0) ? ba - bb : -1.0;
    }

    int bid_volume_at(double price) const {
        auto it = bids.find(price);
        return (it != bids.end()) ? it->second.total_volume : 0;
    }

    int ask_volume_at(double price) const {
        auto it = asks.find(price);
        return (it != asks.end()) ? it->second.total_volume : 0;
    }

    void print(const std::string& symbol = "BOOK", int depth = 5) const {
        const int W = 50;
        auto hr = [&]() { std::cout << "  +" << std::string(W, '-') << "+\n"; };

        std::cout << "\n  ORDER BOOK - " << symbol << "\n";
        hr();
        std::cout << "  | " << std::left << std::setw(W - 1) << "  Prix        Vol      Ordres (FIFO)" << "|\n";
        hr();

        // Asks: du plus haut au plus bas pour l'affichage
        std::vector<std::pair<double, const PriceLevel*>> ask_levels;
        int cnt = 0;
        for (auto it = asks.begin(); it != asks.end() && cnt < depth; ++it, ++cnt)
            ask_levels.push_back({it->first, &it->second});
        std::reverse(ask_levels.begin(), ask_levels.end());

        for (auto& [price, lvl] : ask_levels) {
            std::ostringstream oss;
            oss << "  ASK  " << std::fixed << std::setprecision(2) << price
                << "  " << std::setw(7) << lvl->total_volume << "  ";
            for (auto& o : lvl->orders)
                oss << "[" << o.quantity << "]";
            bool best = (price == get_best_ask());
            std::string line = oss.str();
            std::cout << "  | " << std::left << std::setw(W - 1) << line
                      << "|" << (best ? " ← best ask" : "") << "\n";
        }

        // Spread
        double spread = get_spread();
        if (spread >= 0) {
            std::ostringstream ss;
            ss << "  ── SPREAD " << std::fixed << std::setprecision(2) << spread << " ──";
            std::cout << "  | " << std::left << std::setw(W - 1) << ss.str() << "|\n";
        } else {
            std::cout << "  | " << std::left << std::setw(W - 1) << "  ── (book vide d'un côté) ──" << "|\n";
        }

        // Bids
        cnt = 0;
        for (auto it = bids.begin(); it != bids.end() && cnt < depth; ++it, ++cnt) {
            double price      = it->first;
            const auto& lvl   = it->second;
            std::ostringstream oss;
            oss << "  BID  " << std::fixed << std::setprecision(2) << price
                << "  " << std::setw(7) << lvl.total_volume << "  ";
            for (auto& o : lvl.orders)
                oss << "[" << o.quantity << "]";
            bool best = (price == get_best_bid());
            std::string line = oss.str();
            std::cout << "  | " << std::left << std::setw(W - 1) << line
                      << "|" << (best ? " ← best bid" : "") << "\n";
        }

        hr();
        std::cout << "  Niveaux bids=" << bids.size()
                  << "  asks=" << asks.size()
                  << "  ordres actifs=" << order_index.size() << "\n";
    }
};
