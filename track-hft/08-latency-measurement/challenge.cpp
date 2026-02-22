// Challenge 08 - Benchmark: vector vs map vs unordered_map pour lookup de prix
// Compilation: g++ -std=c++17 -O2 -o challenge challenge.cpp && ./challenge
//
// OBJECTIF: benchmark complet de 5 structures de données pour un use-case HFT réel:
// retrouver un PriceLevel dans un order book en fonction du prix.
//
// STRUCTURES À BENCHMARKER:
//
//   1. vector<pair<double,int>> non trié (O(N) scan)
//   2. vector<pair<double,int>> trié + binary_search (O(log N), cache-friendly)
//   3. std::map<double,int> (O(log N), arbre rouge-noir, cache-unfriendly)
//   4. std::unordered_map<double,int> (O(1) amortie, hash)
//   5. Tableau fixe avec hash manuel simple (O(1), cache-friendly)
//
// MÉTRIQUES:
//   - Temps médian par lookup (ns)
//   - p99 (ns)
//   - Throughput (M lookups/sec)
//
// SCHÉMA - Comparaison des structures:
//
//  Cache locality:
//
//  vector (trié):  [99.10][99.20][99.30][100.00][100.10][100.20] ...
//                   continu en mémoire  excellent cache L1
//                   binary_search: log2(N) comparaisons
//
//  std::map:       noeud1 ───────────── noeud2 ── noeud3 ...
//                  chaque noeud = malloc séparé  cache L1 MISS fréquents
//
//  unordered_map:  bucket[0] bucket[1] ... bucket[K]
//                  hash(price)  bucket  linked list si collision
//                  O(1) mais hash + potential collision overhead
//
//  array fixe:     [slot 0][slot 1][slot 2]...[slot MAX]
//                  index = (price - min_price) / tick_size
//                  O(1) lookup + accès mémoire contigu  IDEAL en HFT
//
// PARTIE 1: implémenter les 5 structures (wrapper simple)
// PARTIE 2: implémenter bench_structure() générique
// PARTIE 3: calculer les percentiles sur 100K samples
// PARTIE 4: afficher le tableau comparatif et tirer des conclusions

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>
#include <cassert>
#include <iomanip>
#include <cmath>
#include <string>
#include <array>
#include <functional>
#include <mutex>

using Clock     = std::chrono::high_resolution_clock;
using Nanos     = std::chrono::nanoseconds;
using TimePoint = Clock::time_point;

int64_t ns_between(TimePoint a, TimePoint b) {
    return std::chrono::duration_cast<Nanos>(b - a).count();
}

// ─────────────────────────────────────────────
// Calcul de percentiles
// ─────────────────────────────────────────────

struct Percentiles {
    double mean;
    double median;   // p50
    double p90;
    double p99;
    double p999;
    double min_val;
    double max_val;
    double throughput_mops;  // M ops/seconde
};

// TODO: implémenter compute_percentiles
// Trier les samples, calculer chaque percentile par index.
// throughput = 1e9 / median (si median > 0)

Percentiles compute_percentiles(std::vector<int64_t>& samples) {
    Percentiles p{};
    if (samples.empty()) return p;

    // TODO: trier
    // TODO: calculer chaque champ de p

    return p;
}

// ─────────────────────────────────────────────
// PARTIE 1 : Wrappers de structures
// ─────────────────────────────────────────────

// Le "PriceLevel" qu'on veut retrouver (simplifié)
struct PriceLevel {
    double price;
    int    volume;
    int    order_count;
};

// ─────────────────────
// Structure 1: vector non trié
// ─────────────────────
class VectorUnsorted {
    std::vector<std::pair<double, PriceLevel>> data;
public:
    void insert(double price, PriceLevel lv) {
        data.push_back({price, lv});
    }

    // TODO: lookup par scan linéaire
    const PriceLevel* find(double price) const {
        // TODO: parcourir data, retourner &lv si price trouvé, sinon nullptr
        return nullptr;
    }
};

// ─────────────────────
// Structure 2: vector trié + binary_search
// ─────────────────────
class VectorSorted {
    std::vector<std::pair<double, PriceLevel>> data;
    bool sorted = false;
public:
    void insert(double price, PriceLevel lv) {
        data.push_back({price, lv});
        sorted = false;
    }

    void build() {
        std::sort(data.begin(), data.end(),
                  [](const auto& a, const auto& b) { return a.first < b.first; });
        sorted = true;
    }

    // TODO: lookup avec std::lower_bound (binary search)
    const PriceLevel* find(double price) const {
        // TODO: lower_bound sur data, comparer price, retourner ptr ou nullptr
        return nullptr;
    }
};

// ─────────────────────
// Structure 3: std::map
// ─────────────────────
class MapStructure {
    std::map<double, PriceLevel> data;
public:
    void insert(double price, PriceLevel lv) { data[price] = lv; }

    // TODO: lookup avec data.find(price)
    const PriceLevel* find(double price) const {
        // TODO
        return nullptr;
    }
};

// ─────────────────────
// Structure 4: std::unordered_map
// ─────────────────────
class HashMapStructure {
    std::unordered_map<double, PriceLevel> data;
public:
    explicit HashMapStructure(int capacity) { data.reserve(capacity * 2); }

    void insert(double price, PriceLevel lv) { data[price] = lv; }

    // TODO: lookup avec data.find(price)
    const PriceLevel* find(double price) const {
        // TODO
        return nullptr;
    }
};

// ─────────────────────
// Structure 5: Price Ladder (array fixe)
// ─────────────────────
//
// Idée: si les prix sont sur une grille régulière (tick_size = 0.01),
// on peut indexer directement dans un tableau.
// index = round((price - min_price) / tick_size)
//
// Avantages: O(1) exact, accès mémoire contigu, pas de hash, pas d'arbre.
// Limite: prix doivent être dans [min_price, max_price], tick_size fixe.

class PriceLadder {
    static constexpr int SLOTS = 2000;    // 0.01 * 2000 = [99.00, 119.00]
    static constexpr double MIN_PRICE  = 99.00;
    static constexpr double TICK       = 0.01;

    struct Slot {
        bool       occupied = false;
        PriceLevel level;
    };

    std::array<Slot, SLOTS> ladder;

    int price_to_idx(double price) const {
        return static_cast<int>(std::round((price - MIN_PRICE) / TICK));
    }

public:
    void insert(double price, PriceLevel lv) {
        int idx = price_to_idx(price);
        if (idx >= 0 && idx < SLOTS) {
            ladder[idx].occupied = true;
            ladder[idx].level    = lv;
        }
    }

    // TODO: lookup par calcul d'index direct (O(1))
    const PriceLevel* find(double price) const {
        // TODO: calculer idx, vérifier bounds et occupied, retourner ptr
        return nullptr;
    }
};

// ─────────────────────────────────────────────
// PARTIE 2 : bench_structure générique
// ─────────────────────────────────────────────
//
// Prend une fonction de lookup et la mesure sur REPS itérations.
// Retourne un vecteur de samples (ns par lookup).

template<typename LookupFn>
Percentiles bench_structure(const char* name,
                            LookupFn lookup_fn,
                            const std::vector<double>& prices_to_lookup,
                            int reps) {
    int N = static_cast<int>(prices_to_lookup.size());
    std::vector<int64_t> samples;
    samples.reserve(reps);

    // TODO: warm-up (100 lookups)
    // TODO: boucle reps fois:
    //   - choisir un prix de prices_to_lookup (index r % N)
    //   - mesurer Clock::now() avant et après lookup_fn(price)
    //   - stocker ns dans samples

    auto p = compute_percentiles(samples);

    std::cout << "  " << std::left << std::setw(22) << name
              << " | p50=" << std::setw(6) << std::fixed << std::setprecision(1) << p.median
              << " | p99=" << std::setw(6) << p.p99
              << " | p99.9=" << std::setw(7) << p.p999
              << " | " << std::setprecision(0) << p.throughput_mops << " Mops/s\n";
    return p;
}

// ─────────────────────────────────────────────
// Main
// ─────────────────────────────────────────────

int main() {
    std::cout << "=== Challenge 08: Benchmark Structures de Données pour Lookup ===\n\n";

    std::cout << "Schéma:\n";
    std::cout << "  vector (non trié):   [p1][p2][p3]...  scan O(N)\n";
    std::cout << "  vector (trié+bsrch): [p1][p2][p3]...  O(log N) cache-friendly\n";
    std::cout << "  std::map:            arbre RB          O(log N) cache-unfriendly\n";
    std::cout << "  unordered_map:       hash table        O(1) amortie\n";
    std::cout << "  price ladder:        array[idx]        O(1) exact, cache-optimal\n\n";

    constexpr int N_LEVELS = 200;   // niveaux de prix dans le book
    constexpr int REPS     = 100'000;

    // Générer N_LEVELS prix sur une grille de 0.01
    std::vector<double> all_prices;
    for (int i = 0; i < N_LEVELS; i++)
        all_prices.push_back(99.00 + i * 0.01);

    // Shuffler pour insertion aléatoire (sauf price ladder)
    std::vector<double> shuffled_prices = all_prices;
    std::mt19937 rng(42);
    std::shuffle(shuffled_prices.begin(), shuffled_prices.end(), rng);

    // Construire chaque structure
    VectorUnsorted  vec_unsorted;
    VectorSorted    vec_sorted;
    MapStructure    map_struct;
    HashMapStructure hash_struct(N_LEVELS);
    PriceLadder     price_ladder;

    for (double p : shuffled_prices) {
        PriceLevel lv{p, 1000 + (int)(p * 10) % 9000, 3};
        vec_unsorted.insert(p, lv);
        vec_sorted.insert(p, lv);
        map_struct.insert(p, lv);
        hash_struct.insert(p, lv);
        price_ladder.insert(p, lv);
    }
    vec_sorted.build();   // trier après toutes les insertions

    // Prix à chercher (lookup)
    std::vector<double> lookup_targets = {
        99.50, 100.00, 100.50, 101.00, 101.23,
        99.00, 100.99, 99.99, 100.01, 101.50
    };

    std::cout << "N_LEVELS=" << N_LEVELS << "  REPS=" << REPS << "\n\n";
    std::cout << "  " << std::left << std::setw(22) << "Structure"
              << " | " << std::setw(9) << "p50 (ns)"
              << " | " << std::setw(9) << "p99 (ns)"
              << " | " << std::setw(10) << "p99.9 (ns)"
              << " | " << "Throughput\n";
    std::cout << "  " << std::string(75, '-') << "\n";

    bench_structure("1-vector-unsorted",
        [&](double p) { return vec_unsorted.find(p); },
        lookup_targets, REPS);

    bench_structure("2-vector-sorted",
        [&](double p) { return vec_sorted.find(p); },
        lookup_targets, REPS);

    bench_structure("3-std::map",
        [&](double p) { return map_struct.find(p); },
        lookup_targets, REPS);

    bench_structure("4-unordered_map",
        [&](double p) { return hash_struct.find(p); },
        lookup_targets, REPS);

    bench_structure("5-price-ladder",
        [&](double p) { return price_ladder.find(p); },
        lookup_targets, REPS);

    std::cout << "\n[Implémente les TODO pour voir les vrais résultats]\n";
    std::cout << "Attendu: price-ladder ≈ 5-10x plus rapide que std::map\n";

    return 0;
}
