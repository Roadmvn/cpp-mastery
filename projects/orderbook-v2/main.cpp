#include "order_book.h"

#include <map>
#include <deque>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdint>
#include <random>

using Clock = std::chrono::steady_clock;
using Ns    = std::chrono::nanoseconds;

static inline int64_t now_ns() {
    return std::chrono::duration_cast<Ns>(Clock::now().time_since_epoch()).count();
}

static int64_t percentile(std::vector<int64_t> v, double p) {
    if (v.empty()) return 0;
    std::sort(v.begin(), v.end());
    return v[static_cast<std::size_t>(p / 100.0 * (v.size() - 1))];
}

// ============================================================
// Order Book v1 : reference avec std::map
// ============================================================
struct OrderV1 {
    uint64_t order_id;
    int32_t  qty;
};

class OrderBookV1 {
public:
    void add_bid(uint64_t id, int32_t price, int32_t qty) {
        bids_[price].push_back({id, qty});
    }
    void add_ask(uint64_t id, int32_t price, int32_t qty) {
        asks_[price].push_back({id, qty});
    }
    bool has_bid() const { return !bids_.empty(); }
    bool has_ask() const { return !asks_.empty(); }
    int32_t best_bid() const { return bids_.rbegin()->first; }
    int32_t best_ask() const { return asks_.begin()->first; }

    int64_t trades{0};
    int64_t qty_traded{0};

private:
    std::map<int32_t, std::deque<OrderV1>> bids_;
    std::map<int32_t, std::deque<OrderV1>> asks_;
};

// ============================================================
// Generateur d'ordres aleatoires
// ============================================================
struct SimOrder {
    bool     is_bid;
    int32_t  price;
    int32_t  qty;
};

static std::vector<SimOrder> generate_orders(int n, int32_t mid_price, int32_t spread_half) {
    std::mt19937 rng(42);
    std::uniform_int_distribution<int32_t> price_dist(-spread_half, spread_half);
    std::uniform_int_distribution<int32_t> qty_dist(1, 100);
    std::bernoulli_distribution            side_dist(0.5);

    std::vector<SimOrder> orders;
    orders.reserve(n);
    for (int i = 0; i < n; ++i) {
        const bool is_bid = side_dist(rng);
        // Bids autour de mid - 1, asks autour de mid + 1
        const int32_t offset = price_dist(rng);
        const int32_t price  = is_bid ? mid_price - 1 + offset : mid_price + 1 + offset;
        orders.push_back({is_bid, price, qty_dist(rng)});
    }
    return orders;
}

// ============================================================
// Benchmark Order Book v2 (Price Ladder)
// ============================================================
static void bench_v2(const std::vector<SimOrder>& orders, int32_t base_price) {
    constexpr std::size_t DEPTH = 2000;
    OrderBookV2<DEPTH> book(base_price);

    std::vector<int64_t> latencies;
    latencies.reserve(orders.size());

    uint64_t next_id = 1;
    for (const auto& o : orders) {
        const int64_t t0 = now_ns();
        if (o.is_bid) {
            book.add_bid(next_id++, o.price, o.qty);
        } else {
            book.add_ask(next_id++, o.price, o.qty);
        }
        latencies.push_back(now_ns() - t0);
    }

    const auto& s = book.stats();
    std::printf("--- Order Book v2 (Price Ladder, depth=%zu) ---\n", DEPTH);
    std::printf("  ordres traites  : %zu\n", orders.size());
    std::printf("  trades executes : %llu\n", s.trades_executed);
    std::printf("  qty echangee    : %lld\n", s.qty_traded);
    std::printf("  latence p50     : %6lld ns\n", percentile(latencies, 50.0));
    std::printf("  latence p99     : %6lld ns\n", percentile(latencies, 99.0));
    std::printf("  latence p99.9   : %6lld ns\n", percentile(latencies, 99.9));
    if (book.best_bid() && book.best_ask()) {
        std::printf("  spread final    : %d ticks\n", *book.spread());
    }
    std::printf("\n");
}

// ============================================================
// Benchmark Order Book v1 (std::map)
// ============================================================
static void bench_v1(const std::vector<SimOrder>& orders) {
    OrderBookV1 book;

    std::vector<int64_t> latencies;
    latencies.reserve(orders.size());

    uint64_t next_id = 1;
    for (const auto& o : orders) {
        const int64_t t0 = now_ns();
        if (o.is_bid) {
            book.add_bid(next_id++, o.price, o.qty);
            if (book.has_ask() && book.best_bid() >= book.best_ask()) {
                book.trades++;
            }
        } else {
            book.add_ask(next_id++, o.price, o.qty);
            if (book.has_bid() && book.best_ask() <= book.best_bid()) {
                book.trades++;
            }
        }
        latencies.push_back(now_ns() - t0);
    }

    std::printf("--- Order Book v1 (std::map) ---\n");
    std::printf("  ordres traites  : %zu\n", orders.size());
    std::printf("  croisements     : %lld\n", book.trades);
    std::printf("  latence p50     : %6lld ns\n", percentile(latencies, 50.0));
    std::printf("  latence p99     : %6lld ns\n", percentile(latencies, 99.0));
    std::printf("  latence p99.9   : %6lld ns\n", percentile(latencies, 99.9));
    std::printf("\n");
}

int main() {
    constexpr int     NUM_ORDERS  = 100'000;
    constexpr int32_t MID_PRICE   = 10000;
    constexpr int32_t SPREAD_HALF = 50;
    constexpr int32_t BASE_PRICE  = MID_PRICE - 1000; // fenetre de 2000 ticks

    std::printf("=== Order Book Benchmark : v1 (std::map) vs v2 (Price Ladder) ===\n");
    std::printf("Ordres : %d | mid : %d | fenetre bid/ask : +/- %d ticks\n\n",
                NUM_ORDERS, MID_PRICE, SPREAD_HALF);

    const auto orders = generate_orders(NUM_ORDERS, MID_PRICE, SPREAD_HALF);

    bench_v1(orders);
    bench_v2(orders, BASE_PRICE);

    std::printf("Interpretation :\n");
    std::printf("  La Price Ladder elimine les allocations dynamiques et les\n");
    std::printf("  sauts de pointeurs de l'arbre rouge-noir. Le gain en latence\n");
    std::printf("  est particulierement visible sur le p99 et p99.9.\n");

    return 0;
}
