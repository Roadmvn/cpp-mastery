// Chapitre 07 - Order Book Engine - EXERCICE
// Compilation: g++ -std=c++17 -O2 -o exercise exercise.cpp && ./exercise
//
// OBJECTIF: comprendre la structure d'un order book et ses opérations de base.
//
// EXERCICE 1: implémenter un PriceLevel (volume total + file d'ordres FIFO)
// EXERCICE 2: implémenter add_order dans le book (bids/asks)
// EXERCICE 3: implémenter get_best_bid / get_best_ask
// EXERCICE 4: afficher le book de façon lisible

#include <iostream>
#include <map>
#include <deque>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip>
#include <stdexcept>
#include <cassert>

// ─────────────────────────────────────────────
// Types de base
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
// EXERCICE 1 : PriceLevel - un niveau de prix
// ─────────────────────────────────────────────
//
// Représente tous les ordres au même prix.
// FIFO: les ordres sont exécutés dans l'ordre d'arrivée.
//
// Structure:
//   total_volume = somme des quantités de tous les ordres
//   orders       = file d'ordres dans l'ordre d'arrivée
//
// TODO: implémenter add_order, remove_order, is_empty

struct PriceLevel {
    int               total_volume = 0;
    std::deque<Order> orders;       // FIFO

    // TODO: ajouter un ordre dans la file
    void add_order(const Order& o) {
        // TODO: push_back + mettre à jour total_volume
    }

    // TODO: retirer un ordre par son id
    // Retourne true si trouvé et supprimé
    bool remove_order(uint64_t order_id) {
        // TODO: chercher dans orders, retirer, mettre à jour total_volume
        return false;
    }

    bool is_empty() const { return orders.empty(); }
};

// ─────────────────────────────────────────────
// EXERCICE 2 : SimpleOrderBook
// ─────────────────────────────────────────────
//
// Deux maps:
//   bids: std::map<double, PriceLevel, std::greater<double>>
//          le best bid est le premier élément (prix max)
//
//   asks: std::map<double, PriceLevel, std::less<double>>
//          le best ask est le premier élément (prix min)
//
// Un index id(side, price) pour les annulations rapides.

class SimpleOrderBook {
public:
    // Bids: prix décroissant (best bid = begin())
    std::map<double, PriceLevel, std::greater<double>> bids;
    // Asks: prix croissant (best ask = begin())
    std::map<double, PriceLevel, std::less<double>>    asks;

    // Index: order_id  (side, price) pour cancel en O(log N)
    struct OrderRef { Side side; double price; };
    std::unordered_map<uint64_t, OrderRef> order_index;

    // TODO: ajouter un ordre dans le book
    // - créer l'entrée dans bids ou asks si le prix n'existe pas encore
    // - appeler level.add_order()
    // - mettre à jour order_index
    void add_order(const Order& o) {
        // TODO
    }

    // TODO: annuler un ordre par son id
    // - chercher dans order_index
    // - appeler level.remove_order()
    // - si level est vide, supprimer l'entrée de la map
    // - supprimer de order_index
    // Retourne true si trouvé
    bool cancel_order(uint64_t order_id) {
        // TODO
        return false;
    }

    // EXERCICE 3 : accesseurs best bid/ask

    // TODO: retourner le meilleur prix d'achat (bid) ou -1 si vide
    double get_best_bid() const {
        // TODO: bids.begin()->first si !bids.empty()
        return -1.0;
    }

    // TODO: retourner le meilleur prix de vente (ask) ou -1 si vide
    double get_best_ask() const {
        // TODO: asks.begin()->first si !asks.empty()
        return -1.0;
    }

    // TODO: spread = best_ask - best_bid, ou -1 si l'un des deux est vide
    double get_spread() const {
        // TODO
        return -1.0;
    }

    // EXERCICE 4 : affichage du book
    //
    // Format attendu:
    //
    //   ┌──────────────────────────────────────────┐
    //   │           ORDER BOOK - AAPL              │
    //   ├──────────────┬──────────────┬────────────┤
    //   │   Prix        │    Volume    │   Côté     │
    //   ├──────────────┼──────────────┼────────────┤
    //   │   100.50      │    3000      │   ASK      │
    //   │   100.30      │    5000      │   ASK     │   best ask
    //   │── SPREAD 0.10 ─────────────────────────  │
    //   │   100.20      │    4000      │   BID     │   best bid
    //   │   100.10      │    1500      │   BID      │
    //   └──────────────┴──────────────┴────────────┘

    void print(const std::string& symbol = "BOOK", int depth = 5) const {
        // TODO: afficher les N meilleurs niveaux de chaque côté
        std::cout << "=== " << symbol << " ===\n";
        std::cout << "[TODO: implémenter l'affichage]\n";
    }
};

// ─────────────────────────────────────────────
// Main - tests
// ─────────────────────────────────────────────

int main() {
    std::cout << "=== Chapitre 07: Order Book Engine ===\n\n";

    SimpleOrderBook book;

    // Ajouter des ordres bids
    uint64_t id = 1;
    book.add_order({id++, Side::BID, 100.20, 4000});
    book.add_order({id++, Side::BID, 100.10,  500});
    book.add_order({id++, Side::BID, 100.10, 1000});   // même niveau que le précédent
    book.add_order({id++, Side::BID, 100.00, 3000});

    // Ajouter des ordres asks
    book.add_order({id++, Side::ASK, 100.30, 2000});
    book.add_order({id++, Side::ASK, 100.30, 3000});   // même niveau
    book.add_order({id++, Side::ASK, 100.40, 2000});
    book.add_order({id++, Side::ASK, 100.50, 1000});

    std::cout << "--- Book initial ---\n";
    book.print("AAPL");

    std::cout << "\nBest bid : " << std::fixed << std::setprecision(2) << book.get_best_bid() << "\n";
    std::cout << "Best ask : " << book.get_best_ask() << "\n";
    std::cout << "Spread   : " << book.get_spread() << "\n";

    // Annuler un ordre
    std::cout << "\n--- Annulation de l'ordre #2 (bid 100.10, qty=500) ---\n";
    bool ok = book.cancel_order(2);
    std::cout << "Cancel: " << (ok ? "OK" : "FAIL") << "\n";
    book.print("AAPL");

    // Ajouter un gros ordre ask
    std::cout << "\n--- Ajout d'un ask agressif à 100.20 (dans le spread) ---\n";
    book.add_order({id++, Side::ASK, 100.20, 5000});
    book.print("AAPL");

    std::cout << "\n[Implémente les TODO pour voir le book s'afficher correctement]\n";
    return 0;
}
