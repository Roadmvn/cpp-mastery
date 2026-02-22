// Challenge 05 - Producer-Consumer avec Market Data Feed
// Compilation: g++ -std=c++17 -O2 -pthread -o challenge challenge.cpp && ./challenge
//
// OBJECTIF: implémenter un vrai pipeline producer-consumer avec mutex + condition_variable.
// Un thread génère des prix (market data feed), l'autre les consomme et calcule des stats.
//
// PIPELINE :
//
//   ┌─────────────────┐     Queue (ring buffer)     ┌──────────────────┐
//   │  MarketFeed      │                             │  TickProcessor    │
//   │  Thread (prod)   │ ──────── MarketTick ──────► │  Thread (cons)   │
//   │                  │   mutex + condition_var      │                  │
//   │  - génère prix   │                             │  - compte ticks  │
//   │  - simule spread │                             │  - calcule VWAP  │
//   │  - 50000 ticks   │                             │  - détecte spike │
//   └─────────────────┘                             └──────────────────┘
//
// PARTIE 1 : implémenter MarketQueue (push / pop thread-safe)
// PARTIE 2 : implémenter le producer (génère des ticks réalistes)
// PARTIE 3 : implémenter le consumer (calcule VWAP + détecte price spike >0.5%)
// PARTIE 4 : afficher les stats finales

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>
#include <cassert>
#include <atomic>
#include <iomanip>

// ─────────────────────────────────────────────
// Types
// ─────────────────────────────────────────────

struct MarketTick {
    double  bid;        // meilleur bid
    double  ask;        // meilleur ask
    int     volume;     // volume de la transaction
    long    seq;        // sequence number
};

// ─────────────────────────────────────────────
// PARTIE 1 : MarketQueue thread-safe
// ─────────────────────────────────────────────
//
// SCHEMA:
//
//   Producer                 MarketQueue                Consumer
//       │                  ┌───────────────┐                │
//       │  push(tick) ────►│ [t1][t2][t3]  │──► pop(tick)  │
//       │                  │               │                │
//       │                  │  mutex: accès │                │
//       │                  │  cv_not_empty │                │
//       │                  │  cv_not_full  │                │
//       │                  └───────────────┘                │
//
//   MAX_SIZE = 1024 (bornée pour éviter OOM)

struct MarketQueue {
    static constexpr size_t MAX_SIZE = 1024;

    std::queue<MarketTick>  q;
    std::mutex              mtx;
    std::condition_variable cv_not_empty;
    std::condition_variable cv_not_full;

    // TODO: implémenter push()
    // - lock le mutex
    // - attendre que la queue ne soit pas pleine (cv_not_full)
    // - push le tick
    // - notifier cv_not_empty
    void push(const MarketTick& tick) {
        // TODO
    }

    // TODO: implémenter pop()
    // - lock le mutex
    // - attendre qu'il y ait des données (cv_not_empty) OU que done soit true
    // - si queue vide et done → retourner false
    // - sinon pop et retourner true
    bool pop(MarketTick& out, const std::atomic<bool>& done) {
        // TODO
        return false;
    }
};

// ─────────────────────────────────────────────
// PARTIE 2 : Producer - génère des ticks
// ─────────────────────────────────────────────
//
// Modèle de prix: marche aléatoire + spread fixe
//
//   price[t+1] = price[t] + N(0, σ)
//   bid = mid - spread/2
//   ask = mid + spread/2
//   volume = uniforme [100, 5000]
//
// Générer N_TICKS ticks puis signaler la fin.

void producer(MarketQueue& queue, std::atomic<bool>& done) {
    constexpr int    N_TICKS   = 50000;
    constexpr double INIT_PRICE = 100.0;
    constexpr double SPREAD    = 0.02;   // 2 cents
    constexpr double SIGMA     = 0.05;   // volatilité par tick

    // TODO: initialiser le générateur aléatoire (std::mt19937)
    // TODO: boucle sur N_TICKS, générer et pousser chaque tick
    // TODO: à la fin, mettre done=true et notifier la queue

    std::cout << "[Producer] done - pushed " << N_TICKS << " ticks\n";
}

// ─────────────────────────────────────────────
// PARTIE 3 : Consumer - calcule les stats
// ─────────────────────────────────────────────
//
// Stats à calculer :
//   - total_ticks        : nombre de ticks reçus
//   - total_volume       : volume cumulé
//   - VWAP               : (sum price*volume) / sum volume
//   - price_spikes       : ticks où |mid - prev_mid| / prev_mid > 0.5%
//   - spread_sum         : pour calculer spread moyen

struct ConsumerStats {
    long   total_ticks   = 0;
    long   total_volume  = 0;
    double vwap_num      = 0.0;   // numérateur VWAP
    double vwap_den      = 0.0;   // dénominateur VWAP
    int    price_spikes  = 0;
    double spread_sum    = 0.0;
    double prev_mid      = 0.0;
};

void consumer(MarketQueue& queue, std::atomic<bool>& done, ConsumerStats& stats) {
    // TODO: loop: pop() → si false, break
    // TODO: calculer mid = (bid+ask)/2
    // TODO: vwap_num += mid * volume, vwap_den += volume
    // TODO: détecter spike si prev_mid > 0 et variation > 0.5%
    // TODO: accumuler spread = ask - bid
}

// ─────────────────────────────────────────────
// PARTIE 4 : main + affichage stats
// ─────────────────────────────────────────────

int main() {
    std::cout << "=== Challenge 05: Market Data Feed Producer-Consumer ===\n\n";

    // Schéma du pipeline
    std::cout << "Pipeline:\n";
    std::cout << "  [MarketFeed] ──(mutex+cv)──► [Queue 1024] ──► [TickProcessor]\n\n";

    MarketQueue       queue;
    std::atomic<bool> done{false};
    ConsumerStats     stats;

    auto t_start = std::chrono::high_resolution_clock::now();

    // TODO: lancer producer et consumer dans des threads séparés
    // TODO: join les deux threads

    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

    // TODO: afficher les stats
    // Format attendu:
    //   Ticks reçus   : 50000
    //   Volume total  : XXXXXXX
    //   VWAP          : 100.XXXX
    //   Spread moyen  : 0.0200
    //   Price spikes  : XX (|Δprix| > 0.5%)
    //   Throughput    : XXXXX ticks/sec
    //   Durée totale  : XX.X ms

    std::cout << "\n[Challenge complet - implémente les TODO pour voir les stats]\n";
    return 0;
}
