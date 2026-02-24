#pragma once

#include <array>
#include <deque>
#include <cstdint>
#include <cstddef>
#include <cassert>
#include <optional>
#include <algorithm>

// Represente un ordre individuel dans le book
struct Order {
    uint64_t order_id;
    int32_t  price;   // en ticks
    int32_t  qty;     // quantite restante
};

// Niveau de prix dans la price ladder : file FIFO d'ordres + quantite totale
struct PriceLevel {
    std::deque<Order> orders;
    int32_t           total_qty{0};

    bool empty() const { return orders.empty(); }

    void add_order(const Order& o) {
        orders.push_back(o);
        total_qty += o.qty;
    }

    // Retire 'qty' en FIFO. Retourne la quantite effectivement consommee.
    int32_t consume(int32_t qty) {
        int32_t consumed = 0;
        while (qty > 0 && !orders.empty()) {
            Order& front = orders.front();
            const int32_t take = std::min(qty, front.qty);
            front.qty  -= take;
            qty        -= take;
            consumed   += take;
            total_qty  -= take;
            if (front.qty == 0) {
                orders.pop_front();
            }
        }
        return consumed;
    }

    // Annule un ordre par id. Retourne true si trouve.
    bool cancel(uint64_t order_id) {
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if (it->order_id == order_id) {
                total_qty -= it->qty;
                orders.erase(it);
                return true;
            }
        }
        return false;
    }
};

// Price Ladder : tableau contigue indexe par prix (en ticks).
//
//   Depth       : taille de la fenetre de prix (nombre de ticks)
//   base_price  : prix minimum de la fenetre
//
// index = price - base_price
// Acces O(1) garanti. Pas d'allocation dynamique dans le tableau lui-meme.
template<std::size_t Depth>
class PriceLadder {
    static_assert(Depth >= 2, "Depth must be at least 2");

public:
    explicit PriceLadder(int32_t base_price) : base_price_(base_price) {}

    // Ajoute un ordre au niveau de prix correspondant.
    void add_order(const Order& order) {
        levels_[to_index(order.price)].add_order(order);
    }

    // Annule un ordre identifie par son prix et son id.
    bool cancel_order(int32_t price, uint64_t order_id) {
        return levels_[to_index(price)].cancel(order_id);
    }

    int32_t qty_at(int32_t price) const {
        return levels_[to_index(price)].total_qty;
    }

    PriceLevel& level_at(int32_t price) {
        return levels_[to_index(price)];
    }

    const PriceLevel& level_at(int32_t price) const {
        return levels_[to_index(price)];
    }

    int32_t base_price() const { return base_price_; }
    int32_t max_price()  const { return base_price_ + static_cast<int32_t>(Depth) - 1; }

    static constexpr std::size_t depth() { return Depth; }

private:
    std::size_t to_index(int32_t price) const {
        assert(price >= base_price_);
        assert(price < base_price_ + static_cast<int32_t>(Depth));
        return static_cast<std::size_t>(price - base_price_);
    }

    std::array<PriceLevel, Depth> levels_;
    int32_t                       base_price_;
};
