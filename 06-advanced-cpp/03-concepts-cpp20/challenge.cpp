// Chapitre 03 — Challenge : Concepts Numeric et Container en contexte HFT
// Compilation : g++ -std=c++20 -Wall -Wextra -O2 -o challenge challenge.cpp
//
// Contexte : On construit un mini-framework de calcul statistique pour
// l'analyse de book d'ordres. On veut :
//   1. Un concept NumericPrice pour les prix (floating point seulement)
//   2. Un concept PriceContainer pour les séquences de prix
//   3. Des fonctions statistiques contraintes (mean, variance, vwap)
//   4. Un concept OrderBook pour valider une structure complète

#include <iostream>
#include <concepts>
#include <vector>
#include <deque>
#include <numeric>
#include <cmath>
#include <string>
#include <cstddef>

// ============================================================
// Concept NumericPrice : flottants uniquement (pas d'entiers)
// Les prix en finance sont des réels, pas des entiers.
// ============================================================

template<typename T>
concept NumericPrice = std::floating_point<T>;

// ============================================================
// Concept PriceContainer : séquence itérable de NumericPrice
// ============================================================

template<typename C>
concept PriceContainer = requires(C c) {
    typename C::value_type;
    requires NumericPrice<typename C::value_type>;
    { c.begin() } -> std::input_or_output_iterator;
    { c.end() }   -> std::input_or_output_iterator;
    { c.size() }  -> std::convertible_to<std::size_t>;
};

// ============================================================
// Fonctions statistiques contraintes
// ============================================================

template<PriceContainer C>
auto mean(const C& prices) -> typename C::value_type {
    if (prices.empty()) return typename C::value_type{0};
    typename C::value_type sum = 0;
    for (auto p : prices) sum += p;
    return sum / static_cast<typename C::value_type>(prices.size());
}

template<PriceContainer C>
auto variance(const C& prices) -> typename C::value_type {
    if (prices.size() < 2) return typename C::value_type{0};
    auto m = mean(prices);
    typename C::value_type sq_sum = 0;
    for (auto p : prices) {
        auto diff = p - m;
        sq_sum += diff * diff;
    }
    return sq_sum / static_cast<typename C::value_type>(prices.size() - 1);
}

template<PriceContainer C>
auto stddev(const C& prices) -> typename C::value_type {
    return std::sqrt(variance(prices));
}

// ============================================================
// VWAP : Volume Weighted Average Price
// Requiert deux conteneurs de même taille (prices + volumes)
// ============================================================

template<PriceContainer Prices, PriceContainer Volumes>
    requires std::same_as<typename Prices::value_type, typename Volumes::value_type>
auto vwap(const Prices& prices, const Volumes& volumes)
    -> typename Prices::value_type {
    using T = typename Prices::value_type;
    T total_pv = 0;
    T total_v = 0;
    auto pit = prices.begin();
    auto vit = volumes.begin();
    while (pit != prices.end() && vit != volumes.end()) {
        total_pv += (*pit) * (*vit);
        total_v  += (*vit);
        ++pit; ++vit;
    }
    return (total_v > 0) ? total_pv / total_v : T{0};
}

// ============================================================
// Concept OrderBook
// Une structure doit avoir bid_prices(), ask_prices(), et spread()
// ============================================================

// Helper : retire const/volatile/reference pour tester le concept sur le type nu
template<typename T>
concept OrderBook = requires(T book) {
    // bid_prices() et ask_prices() doivent retourner quelque chose
    // dont le type nu (sans ref/cv) satisfait PriceContainer
    requires PriceContainer<std::remove_cvref_t<decltype(book.bid_prices())>>;
    requires PriceContainer<std::remove_cvref_t<decltype(book.ask_prices())>>;
    { book.spread() } -> std::floating_point;
    requires std::same_as<
        typename std::remove_cvref_t<decltype(book.bid_prices())>::value_type,
        typename std::remove_cvref_t<decltype(book.ask_prices())>::value_type
    >;
};

// ============================================================
// Implémentation concrète d'un OrderBook simple
// ============================================================

struct SimpleOrderBook {
    std::vector<double> bids;
    std::vector<double> asks;

    const std::vector<double>& bid_prices() const { return bids; }
    const std::vector<double>& ask_prices() const { return asks; }

    double spread() const {
        if (asks.empty() || bids.empty()) return 0.0;
        return asks.front() - bids.front();
    }
};

static_assert(OrderBook<SimpleOrderBook>,
    "SimpleOrderBook must satisfy the OrderBook concept");

// ============================================================
// Fonction de synthèse : analyser un OrderBook
// ============================================================

template<OrderBook B>
void analyze(const B& book, const std::string& name) {
    std::cout << "=== " << name << " ===\n";

    auto bid_mean = mean(book.bid_prices());
    auto ask_mean = mean(book.ask_prices());
    auto bid_vol  = variance(book.bid_prices());
    auto ask_vol  = variance(book.ask_prices());

    std::cout << "Bid mean   : " << bid_mean << "\n";
    std::cout << "Ask mean   : " << ask_mean << "\n";
    std::cout << "Bid stddev : " << stddev(book.bid_prices()) << "\n";
    std::cout << "Ask stddev : " << stddev(book.ask_prices()) << "\n";
    std::cout << "Spread     : " << book.spread() << "\n";
    std::cout << "Bid variance: " << bid_vol << "  Ask variance: " << ask_vol << "\n";
}

// ============================================================
// main
// ============================================================

int main() {
    // Test statistiques de base
    std::vector<double> prices = {100.0, 101.5, 99.0, 102.0, 100.5};
    std::cout << "mean    = " << mean(prices) << "\n";
    std::cout << "stddev  = " << stddev(prices) << "\n";

    // VWAP
    std::vector<double> volumes = {1000.0, 500.0, 2000.0, 750.0, 1250.0};
    std::cout << "vwap    = " << vwap(prices, volumes) << "\n";

    // Deque fonctionne aussi (satisfait PriceContainer)
    std::deque<double> dq_prices(prices.begin(), prices.end());
    std::cout << "mean (deque) = " << mean(dq_prices) << "\n";

    // OrderBook complet
    SimpleOrderBook book{
        {100.0, 99.5, 99.0, 98.5, 98.0},   // bids (meilleur en premier)
        {100.5, 101.0, 101.5, 102.0, 102.5} // asks
    };
    analyze(book, "AAPL");

    // Test avec float aussi (PriceContainer<vector<float>> doit marcher)
    std::vector<float> fp_prices = {50.0f, 51.0f, 49.5f, 50.5f};
    std::cout << "\nfloat mean = " << mean(fp_prices) << "\n";

    // Décommenter pour vérifier l'erreur de compilation :
    // std::vector<int> int_prices = {100, 101, 99};
    // mean(int_prices);  // erreur : int ne satisfait pas NumericPrice

    return 0;
}
