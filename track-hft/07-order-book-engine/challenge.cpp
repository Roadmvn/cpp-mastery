// Challenge 07 - Order Book Engine complet
// Compilation: g++ -std=c++17 -O2 -o challenge challenge.cpp && ./challenge
//
// OBJECTIF: implémenter un order book avec:
//   - add_order    : ajouter un ordre (BID ou ASK)
//   - cancel_order : annuler un ordre par son ID
//   - get_best_bid : meilleur prix d'achat
//   - get_best_ask : meilleur prix de vente
//   - match_order  : matcher un ordre entrant contre le book (price-time priority)
//
// SCHÉMA MATCHING:
//
//   Nouvel ordre BUY 100.30 qty=3000
//
//   ASKS:          [100.20 vol=5000][100.30 vol=5000][100.40 vol=2000]
//                       ↑ best ask (100.20 ≤ 100.30) → MATCH!
//
//   Round 1: ask 100.20, FIFO order[0] qty=2000 → trade 2000@100.20 (reste buy=1000)
//   Round 2: ask 100.20, FIFO order[1] qty=3000 → trade 1000@100.20 (buy fully filled)
//            order[1] reste avec qty=2000
//
//   TRADES GÉNÉRÉS:
//     Trade { buy_id, sell_id, price=100.20, qty=2000 }
//     Trade { buy_id, sell_id, price=100.20, qty=1000 }
//
// PARTIE 1 : implémenter PriceLevel (add, remove, FIFO consume)
// PARTIE 2 : implémenter OrderBook (add_order, cancel_order, best bid/ask)
// PARTIE 3 : implémenter match_order qui génère une liste de trades
// PARTIE 4 : afficher le book après chaque opération (print_book)
// BONUS    : calculer VWAP des trades et spread moyen

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
#include <cmath>

// ─────────────────────────────────────────────
// Types
// ─────────────────────────────────────────────

enum class Side { BID, ASK };

struct Order {
    uint64_t    id;
    Side        side;
    double      price;
    int         quantity;       // quantité restante

    std::string side_str() const { return side == Side::BID ? "BID" : "ASK"; }
};

struct Trade {
    uint64_t buy_id;
    uint64_t sell_id;
    double   price;
    int      quantity;
};

// ─────────────────────────────────────────────
// PARTIE 1 : PriceLevel
// ─────────────────────────────────────────────

struct PriceLevel {
    int               total_volume = 0;
    std::deque<Order> orders;       // FIFO

    // TODO: ajouter un ordre
    void add_order(const Order& o) {
        // TODO
    }

    // TODO: supprimer un ordre par id
    bool remove_order(uint64_t id) {
        // TODO
        return false;
    }

    // TODO: consommer qty units depuis le front de la file (FIFO matching)
    // Retourne la liste des trades partiels générés (peut affecter plusieurs ordres)
    // incoming_id = id de l'ordre entrant, incoming_side = son côté
    std::vector<Trade> consume(int& remaining_qty,
                               uint64_t incoming_id,
                               Side incoming_side) {
        std::vector<Trade> trades;

        while (remaining_qty > 0 && !orders.empty()) {
            Order& front = orders.front();
            int fill = std::min(remaining_qty, front.quantity);

            // TODO: créer un Trade
            uint64_t buy_id  = (incoming_side == Side::BID) ? incoming_id : front.id;
            uint64_t sell_id = (incoming_side == Side::ASK) ? incoming_id : front.id;

            // TODO: ajouter le trade à la liste

            // TODO: mettre à jour front.quantity et total_volume
            // TODO: si front.quantity == 0, pop_front
            // TODO: décrémenter remaining_qty

            (void)buy_id; (void)sell_id; (void)fill;
            break; // TODO: supprimer ce break
        }

        return trades;
    }

    bool is_empty() const { return orders.empty(); }
};

// ─────────────────────────────────────────────
// PARTIE 2 : OrderBook
// ─────────────────────────────────────────────

class OrderBook {
public:
    // bids: prix décroissant
    std::map<double, PriceLevel, std::greater<double>> bids;
    // asks: prix croissant
    std::map<double, PriceLevel>                       asks;

    struct OrderRef { Side side; double price; };
    std::unordered_map<uint64_t, OrderRef> order_index;

    // Stats globales
    long   total_trades  = 0;
    long   total_volume  = 0;
    double total_turnover = 0.0;  // pour VWAP

    // TODO: ajouter un ordre dans le book sans matching
    void add_order(const Order& o) {
        // TODO
    }

    // TODO: annuler un ordre par id
    bool cancel_order(uint64_t id) {
        // TODO
        return false;
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

    // PARTIE 3 : match_order
    //
    // Un ordre entrant (BID ou ASK) est matché contre le côté opposé.
    //
    // ALGO:
    //   Si BID entrant:
    //     while remaining > 0 AND best_ask <= order.price:
    //       trades += asks.begin().consume(remaining, ...)
    //       si niveau vide → supprimer du map asks
    //   Idem pour ASK entrant (contre bids, bid >= order.price)
    //
    //   Si remaining > 0 après matching → resting order (add_order)
    //   Mettre à jour les stats (total_trades, total_volume, total_turnover)
    //
    // Retourne la liste de tous les trades générés.

    std::vector<Trade> match_order(Order o) {
        std::vector<Trade> all_trades;

        // TODO: matching loop BID contre asks
        // TODO: matching loop ASK contre bids
        // TODO: si reste → add_order(o avec quantity=remaining)
        // TODO: mettre à jour total_trades, total_volume, total_turnover

        return all_trades;
    }

    // PARTIE 4 : affichage
    void print(const std::string& symbol = "BOOK", int depth = 5) const {
        // TODO: afficher les N meilleurs niveaux de chaque côté
        // Format:
        //   ASK  100.50  1000  [1000]
        //   ASK  100.40  2000  [2000]  ← best ask
        //   ── SPREAD 0.10 ──
        //   BID  100.30  4000  [4000]  ← best bid
        //   BID  100.20  1500  [500][1000]
        std::cout << "=== " << symbol << " ===\n";
        std::cout << "[TODO: implémenter print]\n";
    }
};

// ─────────────────────────────────────────────
// Scénario de test complet
// ─────────────────────────────────────────────

int main() {
    std::cout << "=== Challenge 07: Order Book Engine avec Matching ===\n\n";

    OrderBook book;
    uint64_t next_id = 1;
    std::vector<Trade> all_trades;

    auto submit = [&](Side side, double price, int qty) -> std::vector<Trade> {
        Order o{next_id++, side, price, qty};
        std::cout << ">>> " << o.side_str() << " " << qty << "@" << std::fixed
                  << std::setprecision(2) << price << " (id=" << o.id << ")\n";
        auto trades = book.match_order(o);
        for (auto& t : trades) {
            std::cout << "    TRADE: " << t.quantity << "@" << t.price
                      << " (buy#" << t.buy_id << " vs sell#" << t.sell_id << ")\n";
            all_trades.push_back(t);
        }
        book.print("AAPL");
        return trades;
    };

    // --- Construction du book initial ---
    std::cout << "=== Construction du book initial ===\n";
    // Resting orders (pas de matching car book vide)
    submit(Side::BID, 100.20, 4000);
    submit(Side::BID, 100.10,  500);
    submit(Side::BID, 100.10, 1000);
    submit(Side::BID, 100.00, 3000);
    submit(Side::ASK, 100.50, 2000);
    submit(Side::ASK, 100.40, 3000);
    submit(Side::ASK, 100.30, 5000);

    std::cout << "\n=== Ordre agressif BID 100.30 qty=7000 (matching partiel) ===\n";
    submit(Side::BID, 100.30, 7000);
    // Attendu: 5000 matché sur asks 100.30, 2000 reste en bid resting

    std::cout << "\n=== Annulation d'un ordre ===\n";
    std::cout << "Cancel id=2 (bid 100.10 qty=500): ";
    std::cout << (book.cancel_order(2) ? "OK" : "FAIL") << "\n";
    book.print("AAPL");

    // --- Stats finales ---
    std::cout << "\n=== Stats finales ===\n";
    std::cout << "Total trades  : " << book.total_trades << "\n";
    std::cout << "Total volume  : " << book.total_volume << "\n";
    if (book.total_volume > 0)
        std::cout << "VWAP trades   : " << std::fixed << std::setprecision(4)
                  << book.total_turnover / book.total_volume << "\n";
    std::cout << "Spread actuel : ";
    double spread = book.get_spread();
    if (spread >= 0) std::cout << std::setprecision(2) << spread << "\n";
    else std::cout << "N/A\n";

    std::cout << "\n[Implémente les TODO pour voir le matching fonctionner]\n";
    return 0;
}
