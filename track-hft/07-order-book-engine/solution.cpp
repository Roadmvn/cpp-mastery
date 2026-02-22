// Chapitre 07 - Order Book Engine - SOLUTION
// Compilation: g++ -std=c++17 -O2 -o solution solution.cpp && ./solution

#include <iostream>
#include <map>
#include <deque>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip>
#include <cassert>
#include <algorithm>
#include <sstream>

// ─────────────────────────────────────────────
// Types
// ─────────────────────────────────────────────

enum class Side { BID, ASK };

struct Order {
    uint64_t    id;
    Side        side;
    double      price;
    int         quantity;

    std::string side_str() const { return side == Side::BID ? "BID" : "ASK"; }
};

// ─────────────────────────────────────────────
// PriceLevel
// ─────────────────────────────────────────────

struct PriceLevel {
    int               total_volume = 0;
    std::deque<Order> orders;

    void add_order(const Order& o) {
        total_volume += o.quantity;
        orders.push_back(o);
    }

    bool remove_order(uint64_t order_id) {
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if (it->id == order_id) {
                total_volume -= it->quantity;
                orders.erase(it);
                return true;
            }
        }
        return false;
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
        if (o.side == Side::BID) {
            bids[o.price].add_order(o);
        } else {
            asks[o.price].add_order(o);
        }
        order_index[o.id] = {o.side, o.price};
    }

    bool cancel_order(uint64_t order_id) {
        auto it = order_index.find(order_id);
        if (it == order_index.end()) return false;

        auto [side, price] = it->second;

        if (side == Side::BID) {
            auto bit = bids.find(price);
            if (bit != bids.end()) {
                bit->second.remove_order(order_id);
                if (bit->second.is_empty()) bids.erase(bit);
            }
        } else {
            auto ait = asks.find(price);
            if (ait != asks.end()) {
                ait->second.remove_order(order_id);
                if (ait->second.is_empty()) asks.erase(ait);
            }
        }

        order_index.erase(it);
        return true;
    }

    double get_best_bid() const {
        return bids.empty() ? -1.0 : bids.begin()->first;
    }

    double get_best_ask() const {
        return asks.empty() ? -1.0 : asks.begin()->first;
    }

    double get_spread() const {
        double bb = get_best_bid();
        double ba = get_best_ask();
        if (bb < 0 || ba < 0) return -1.0;
        return ba - bb;
    }

    void print(const std::string& symbol = "BOOK", int depth = 5) const {
        const int W_PRICE = 10, W_VOL = 8, W_ORDERS = 30;

        auto sep = [&]() {
            std::cout << "  +" << std::string(W_PRICE + 2, '-')
                      << "+" << std::string(W_VOL + 2, '-')
                      << "+" << std::string(W_ORDERS + 2, '-') << "+\n";
        };

        std::cout << "\n  ORDER BOOK - " << symbol << "\n";
        sep();
        std::cout << "  | " << std::left << std::setw(W_PRICE) << "Prix"
                  << " | " << std::setw(W_VOL) << "Volume"
                  << " | " << std::setw(W_ORDERS) << "Ordres (FIFO)"
                  << " |\n";
        sep();

        // Asks (inversées pour afficher du plus haut au plus bas)
        std::vector<std::pair<double, const PriceLevel*>> ask_levels;
        int cnt = 0;
        for (auto it = asks.begin(); it != asks.end() && cnt < depth; ++it, ++cnt)
            ask_levels.push_back({it->first, &it->second});
        std::reverse(ask_levels.begin(), ask_levels.end());

        for (auto& [price, level] : ask_levels) {
            std::ostringstream orders_ss;
            for (auto& o : level->orders)
                orders_ss << "[" << o.quantity << "]";
            bool is_best = (price == get_best_ask());
            std::cout << "  | " << std::right << std::fixed << std::setprecision(2)
                      << std::setw(W_PRICE) << price
                      << " | " << std::setw(W_VOL) << level->total_volume
                      << " | " << std::left << std::setw(W_ORDERS) << orders_ss.str()
                      << " |" << (is_best ? " ← best ask" : "") << "\n";
        }

        // Spread
        double spread = get_spread();
        if (spread >= 0) {
            std::ostringstream ss;
            ss << "── SPREAD " << std::fixed << std::setprecision(2) << spread << " ──";
            std::cout << "  | " << std::left << std::setw(W_PRICE + W_VOL + W_ORDERS + 5)
                      << ss.str() << " |\n";
        }

        // Bids
        cnt = 0;
        for (auto it = bids.begin(); it != bids.end() && cnt < depth; ++it, ++cnt) {
            double price     = it->first;
            const auto& level = it->second;
            std::ostringstream orders_ss;
            for (auto& o : level.orders)
                orders_ss << "[" << o.quantity << "]";
            bool is_best = (price == get_best_bid());
            std::cout << "  | " << std::right << std::fixed << std::setprecision(2)
                      << std::setw(W_PRICE) << price
                      << " | " << std::setw(W_VOL) << level.total_volume
                      << " | " << std::left << std::setw(W_ORDERS) << orders_ss.str()
                      << " |" << (is_best ? " ← best bid" : "") << "\n";
        }

        sep();
        std::cout << "  Niveaux bids=" << bids.size() << "  asks=" << asks.size()
                  << "  ordres=" << order_index.size() << "\n\n";
    }
};

// ─────────────────────────────────────────────
// Main
// ─────────────────────────────────────────────

int main() {
    std::cout << "=== Solution 07: Order Book Engine ===\n";

    OrderBook book;
    uint64_t id = 1;

    // Bids
    book.add_order({id++, Side::BID, 100.20, 4000});
    book.add_order({id++, Side::BID, 100.10,  500});
    book.add_order({id++, Side::BID, 100.10, 1000});
    book.add_order({id++, Side::BID, 100.00, 3000});

    // Asks
    book.add_order({id++, Side::ASK, 100.30, 2000});
    book.add_order({id++, Side::ASK, 100.30, 3000});
    book.add_order({id++, Side::ASK, 100.40, 2000});
    book.add_order({id++, Side::ASK, 100.50, 1000});

    std::cout << "\n--- Book initial ---";
    book.print("AAPL");

    std::cout << "Best bid : " << std::fixed << std::setprecision(2) << book.get_best_bid() << "\n";
    std::cout << "Best ask : " << book.get_best_ask() << "\n";
    std::cout << "Spread   : " << book.get_spread() << "\n";

    // Annuler l'ordre #2 (bid 100.10, qty=500)
    std::cout << "\n--- Cancel ordre #2 (bid 100.10 qty=500) ---";
    assert(book.cancel_order(2));
    book.print("AAPL");

    // Ajouter un ask agressif dans le spread
    std::cout << "--- Ajout ask 100.20 qty=5000 (dans le spread) ---";
    book.add_order({id++, Side::ASK, 100.20, 5000});
    book.print("AAPL");

    // Tests assert
    assert(book.get_best_bid() == 100.20);
    assert(book.get_best_ask() == 100.20);
    assert(book.get_spread() == 0.0);

    std::cout << "Tous les asserts passent - SOLUTION CORRECTE\n";
    return 0;
}
