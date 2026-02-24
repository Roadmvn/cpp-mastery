#pragma once

#include "price_ladder.h"

#include <chrono>
#include <cstdint>
#include <optional>

// Statistiques de matching collectees par l'order book
struct MatchStats {
    uint64_t trades_executed{0};
    int64_t  qty_traded{0};
    int64_t  total_match_ns{0};  // somme des latences de matching

    double avg_match_ns() const {
        if (trades_executed == 0) return 0.0;
        return static_cast<double>(total_match_ns) / trades_executed;
    }
};

// Trade genere lors du matching
struct Trade {
    uint64_t aggressor_id;  // ordre entrant
    uint64_t passive_id;    // ordre au repos dans le book (order_id du premier ordre du niveau)
    int32_t  price;
    int32_t  qty;
};

// OrderBook v2 : bids + asks via PriceLadder, FIFO par niveau
//
// Depth = fenetre de prix en ticks (ex: 4000 => +/- 2000 ticks autour du base)
// Le base_price du bid side == base_price du ask side dans cette implementation.
template<std::size_t Depth = 4000>
class OrderBookV2 {
public:
    explicit OrderBookV2(int32_t base_price)
        : bids_(base_price), asks_(base_price)
    {}

    // Ajoute un ordre BID (achat). Tente le matching immediatement.
    // Retourne le Trade si execution partielle ou totale.
    std::optional<Trade> add_bid(uint64_t order_id, int32_t price, int32_t qty) {
        const int64_t t0 = now_ns();

        // Matching contre les asks au meme prix ou inferieur
        std::optional<Trade> trade = match_against_asks(order_id, price, qty, t0);

        // Si restant non execute, inserer dans le bid book
        if (qty > 0) {
            bids_.add_order({order_id, price, qty});
            update_best_bid(price);
        }

        return trade;
    }

    // Ajoute un ordre ASK (vente). Tente le matching immediatement.
    std::optional<Trade> add_ask(uint64_t order_id, int32_t price, int32_t qty) {
        const int64_t t0 = now_ns();

        // Matching contre les bids au meme prix ou superieur
        std::optional<Trade> trade = match_against_bids(order_id, price, qty, t0);

        if (qty > 0) {
            asks_.add_order({order_id, price, qty});
            update_best_ask(price);
        }

        return trade;
    }

    std::optional<int32_t> best_bid() const { return best_bid_; }
    std::optional<int32_t> best_ask() const { return best_ask_; }

    int32_t bid_qty_at(int32_t price) const { return bids_.qty_at(price); }
    int32_t ask_qty_at(int32_t price) const { return asks_.qty_at(price); }

    const MatchStats& stats() const { return stats_; }

    // Spread en ticks (nullopt si book incomplet)
    std::optional<int32_t> spread() const {
        if (!best_bid_ || !best_ask_) return std::nullopt;
        return *best_ask_ - *best_bid_;
    }

private:
    static int64_t now_ns() {
        using namespace std::chrono;
        return duration_cast<nanoseconds>(
            steady_clock::now().time_since_epoch()
        ).count();
    }

    std::optional<Trade> match_against_asks(uint64_t bid_id, int32_t price,
                                             int32_t& qty, int64_t t0) {
        if (!best_ask_ || price < *best_ask_) return std::nullopt;

        // Prendre le meilleur ask tant que le prix bid >= ask
        PriceLevel& level = asks_.level_at(*best_ask_);
        if (level.empty()) return std::nullopt;

        const int32_t match_price = *best_ask_;
        const uint64_t passive_id = level.orders.front().order_id;
        const int32_t consumed    = level.consume(qty);
        qty -= consumed;

        if (level.empty()) {
            recalc_best_ask();
        }

        stats_.trades_executed++;
        stats_.qty_traded    += consumed;
        stats_.total_match_ns += now_ns() - t0;

        return Trade{bid_id, passive_id, match_price, consumed};
    }

    std::optional<Trade> match_against_bids(uint64_t ask_id, int32_t price,
                                             int32_t& qty, int64_t t0) {
        if (!best_bid_ || price > *best_bid_) return std::nullopt;

        PriceLevel& level = bids_.level_at(*best_bid_);
        if (level.empty()) return std::nullopt;

        const int32_t match_price = *best_bid_;
        const uint64_t passive_id = level.orders.front().order_id;
        const int32_t consumed    = level.consume(qty);
        qty -= consumed;

        if (level.empty()) {
            recalc_best_bid();
        }

        stats_.trades_executed++;
        stats_.qty_traded    += consumed;
        stats_.total_match_ns += now_ns() - t0;

        return Trade{ask_id, passive_id, match_price, consumed};
    }

    void update_best_bid(int32_t price) {
        if (!best_bid_ || price > *best_bid_) best_bid_ = price;
    }

    void update_best_ask(int32_t price) {
        if (!best_ask_ || price < *best_ask_) best_ask_ = price;
    }

    void recalc_best_bid() {
        if (!best_bid_) return;
        // Parcourir vers le bas pour trouver le prochain niveau non vide
        for (int32_t p = *best_bid_; p >= bids_.base_price(); --p) {
            if (!bids_.level_at(p).empty()) {
                best_bid_ = p;
                return;
            }
        }
        best_bid_ = std::nullopt;
    }

    void recalc_best_ask() {
        if (!best_ask_) return;
        const int32_t max_price = asks_.base_price() + static_cast<int32_t>(Depth) - 1;
        for (int32_t p = *best_ask_; p <= max_price; ++p) {
            if (!asks_.level_at(p).empty()) {
                best_ask_ = p;
                return;
            }
        }
        best_ask_ = std::nullopt;
    }

    PriceLadder<Depth>    bids_;
    PriceLadder<Depth>    asks_;
    std::optional<int32_t> best_bid_;
    std::optional<int32_t> best_ask_;
    MatchStats             stats_;
};
