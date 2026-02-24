// Chapitre 04 — Challenge HFT : Base class avec compteur de performance
// Compilation : g++ -std=c++20 -Wall -Wextra -O2 -o challenge challenge.cpp
//
// Contexte : En HFT, on veut mesurer le coût de chaque opération (ordre, trade,
// calcul de position) sans overhead en production. Le pattern CRTP permet d'injecter
// une infrastructure de mesure qui peut être activée/désactivée à la compilation.
//
// On implémente :
//   1. PerformanceBase<Derived, Enabled> : mixin avec timing intégré
//   2. Polymorphisme statique sur process() sans vtable
//   3. Rapport de performance agrégé

#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <iomanip>

// ============================================================
// Utilitaire timing
// ============================================================

using ns_t = std::int64_t;

inline ns_t now_ns() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(
        steady_clock::now().time_since_epoch()
    ).count();
}

// ============================================================
// PerformanceBase<Derived, Enabled>
//
// Quand Enabled = true  : mesure le temps de chaque appel à execute()
// Quand Enabled = false : exécution directe, zéro overhead
// ============================================================

template<typename Derived, bool Enabled = true>
class PerformanceBase {
    static inline std::vector<ns_t> timings_;
    static inline std::size_t call_count_ = 0;

public:
    // Point d'entrée mesuré
    void execute() {
        if constexpr (Enabled) {
            ns_t start = now_ns();
            static_cast<Derived*>(this)->process();
            ns_t elapsed = now_ns() - start;
            timings_.push_back(elapsed);
            ++call_count_;
        } else {
            static_cast<Derived*>(this)->process();
        }
    }

    static void print_stats(const std::string& name) {
        if constexpr (!Enabled) {
            std::cout << "[" << name << "] Performance tracking disabled.\n";
            return;
        }
        if (timings_.empty()) {
            std::cout << "[" << name << "] No calls recorded.\n";
            return;
        }

        auto sorted = timings_;
        std::sort(sorted.begin(), sorted.end());

        double avg = static_cast<double>(
            std::accumulate(timings_.begin(), timings_.end(), ns_t{0})
        ) / static_cast<double>(timings_.size());

        std::cout << std::fixed << std::setprecision(1);
        std::cout << "[" << name << "] calls=" << call_count_
                  << " avg=" << avg << "ns"
                  << " min=" << sorted.front() << "ns"
                  << " p50=" << sorted[sorted.size() / 2] << "ns"
                  << " p95=" << sorted[sorted.size() * 95 / 100] << "ns"
                  << " max=" << sorted.back() << "ns\n";
    }

    static void reset_stats() {
        timings_.clear();
        call_count_ = 0;
    }
};

// ============================================================
// Moteur de matching d'ordres (simplifié)
// Hérite de PerformanceBase avec profiling activé
// ============================================================

struct MarketOrder {
    int id;
    double price;
    int quantity;
    bool is_buy;
};

class MatchingEngine : public PerformanceBase<MatchingEngine, true> {
    std::vector<MarketOrder> pending_buy_;
    std::vector<MarketOrder> pending_sell_;
    int next_id_ = 0;

public:
    void add_order(double price, int qty, bool is_buy) {
        if (is_buy)  pending_buy_.push_back({++next_id_, price, qty, true});
        else         pending_sell_.push_back({++next_id_, price, qty, false});
    }

    // process() est appelé via execute() (mesuré)
    void process() {
        // Tri + tentative de matching
        std::sort(pending_buy_.begin(), pending_buy_.end(),
                  [](auto& a, auto& b){ return a.price > b.price; }); // desc
        std::sort(pending_sell_.begin(), pending_sell_.end(),
                  [](auto& a, auto& b){ return a.price < b.price; }); // asc

        while (!pending_buy_.empty() && !pending_sell_.empty()) {
            auto& best_buy  = pending_buy_.front();
            auto& best_sell = pending_sell_.front();
            if (best_buy.price < best_sell.price) break;

            int matched_qty = std::min(best_buy.quantity, best_sell.quantity);
            // En vrai : enregistrer le trade
            best_buy.quantity  -= matched_qty;
            best_sell.quantity -= matched_qty;

            if (best_buy.quantity  == 0) pending_buy_.erase(pending_buy_.begin());
            if (best_sell.quantity == 0) pending_sell_.erase(pending_sell_.begin());
        }
    }

    std::size_t pending_buy_count()  const { return pending_buy_.size(); }
    std::size_t pending_sell_count() const { return pending_sell_.size(); }
};

// ============================================================
// Risk checker (plus simple, profiling activé)
// ============================================================

class RiskChecker : public PerformanceBase<RiskChecker, true> {
    double max_exposure_ = 1e6;
    double current_exposure_ = 0.0;
    int rejected_ = 0;

public:
    void add_exposure(double amount) {
        current_exposure_ += amount;
    }

    // process() vérifie les limites
    void process() {
        if (current_exposure_ > max_exposure_) {
            ++rejected_;
            current_exposure_ = max_exposure_;
        }
    }

    int rejected_count() const { return rejected_; }
    double exposure() const { return current_exposure_; }
};

// ============================================================
// DataFeed sans profiling (production path, zéro overhead)
// ============================================================

class DataFeed : public PerformanceBase<DataFeed, false> {
    double last_price_ = 0.0;
    int tick_count_ = 0;

public:
    void set_price(double p) { last_price_ = p; }

    void process() {
        ++tick_count_;
        // Traitement minimal du tick
        last_price_ *= 1.0;  // noop symbolique
    }

    int tick_count() const { return tick_count_; }
};

// ============================================================
// main
// ============================================================

int main() {
    // MatchingEngine : on simule un burst d'ordres
    MatchingEngine engine;
    for (int i = 0; i < 100; ++i) {
        engine.add_order(100.0 + (i % 5), 10 + (i % 20), (i % 2 == 0));
        engine.execute();
    }
    MatchingEngine::print_stats("MatchingEngine");

    // RiskChecker
    RiskChecker risk;
    for (int i = 0; i < 50; ++i) {
        risk.add_exposure(25000.0);
        risk.execute();
    }
    RiskChecker::print_stats("RiskChecker");
    std::cout << "  rejected: " << risk.rejected_count() << "\n";

    // DataFeed : profiling désactivé
    DataFeed feed;
    feed.set_price(142.50);
    for (int i = 0; i < 10000; ++i) {
        feed.execute();  // appel direct sans mesure
    }
    DataFeed::print_stats("DataFeed");  // affiche "disabled"
    std::cout << "  ticks processed: " << feed.tick_count() << "\n";

    return 0;
}
