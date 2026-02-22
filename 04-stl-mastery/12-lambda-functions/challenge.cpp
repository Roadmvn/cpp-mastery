// ============================================================
// Lambdas — Challenge LeetCode
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// ============================================================
//
// Challenge : Comparateurs custom pour trier des structures complexes.
// Cas reel : un carnet d'ordres de marche (price + timestamp).
//
// Regles de tri :
// 1. Par prix decroissant (ordres au meilleur prix en premier)
// 2. A prix egal, par timestamp croissant (premier arrive, premier servi)
// 3. A prix et timestamp egaux, par volume decroissant
//
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cassert>
using namespace std;

// ============================================================
// Structure Order : ordre de marche
// ============================================================

struct Order {
    int id;
    double price;
    long long timestamp;  // en millisecondes depuis epoch
    int volume;
    string side;          // "BUY" ou "SELL"

    void print() const {
        cout << "  Order{id=" << id
             << ", price=" << price
             << ", ts=" << timestamp
             << ", vol=" << volume
             << ", side=" << side << "}" << endl;
    }
};

// ============================================================
// DEFI 1 : Tri du carnet d'ordres
// ============================================================
//
// Trier les ordres BUY : prix decroissant, puis timestamp croissant,
// puis volume decroissant (priorite au plus gros volume a egalite totale)

vector<Order> sortBuyOrders(vector<Order> orders) {
    sort(orders.begin(), orders.end(),
        [](const Order& a, const Order& b) {
            if (a.price != b.price)        return a.price > b.price;       // 1. prix desc
            if (a.timestamp != b.timestamp) return a.timestamp < b.timestamp; // 2. ts asc
            return a.volume > b.volume;                                    // 3. volume desc
        }
    );
    return orders;
}

// ============================================================
// DEFI 2 : Filtrer et regrouper par tranche de prix
// ============================================================
//
// Retourner le volume total des ordres dans une tranche de prix [low, high]

long long totalVolumeInRange(const vector<Order>& orders, double low, double high) {
    // Filtrer et accumuler en une expression
    return accumulate(orders.begin(), orders.end(), 0LL,
        [low, high](long long acc, const Order& o) {
            return (o.price >= low && o.price <= high) ? acc + o.volume : acc;
        }
    );
}

// ============================================================
// DEFI 3 : Top-K ordres par volume
// ============================================================
//
// Retourner les K ordres avec le plus grand volume
// sans trier tout le tableau (nth_element)

vector<Order> topKByVolume(vector<Order> orders, int k) {
    if (k >= (int)orders.size()) return orders;

    // nth_element pour partitionner les k plus gros volumes en O(n)
    nth_element(orders.begin(), orders.begin() + k, orders.end(),
        [](const Order& a, const Order& b) {
            return a.volume > b.volume;  // ordre decroissant de volume
        }
    );

    // Trier seulement les k premiers pour un affichage ordonne
    sort(orders.begin(), orders.begin() + k,
        [](const Order& a, const Order& b) {
            return a.volume > b.volume;
        }
    );

    return vector<Order>(orders.begin(), orders.begin() + k);
}

// ============================================================
// DEFI 4 : Priority Queue avec comparateur lambda custom
// ============================================================
//
// Implementer une file de priorite pour executer les ordres
// par prix decroissant avec priority_queue et lambda

#include <queue>

class OrderBook {
public:
    // Comparateur : on veut un max-heap sur le prix
    // priority_queue par defaut est un max-heap, mais avec struct on doit
    // definir l'ordre
    using Cmp = function<bool(const Order&, const Order&)>;

    OrderBook() : pq([](const Order& a, const Order& b) {
        if (a.price != b.price) return a.price < b.price;  // max-heap sur price
        return a.timestamp > b.timestamp;                   // min-heap sur ts (FIFO)
    }) {}

    void addOrder(const Order& o) {
        pq.push(o);
    }

    Order popBest() {
        Order best = pq.top();
        pq.pop();
        return best;
    }

    bool empty() const { return pq.empty(); }
    int size() const { return (int)pq.size(); }

private:
    priority_queue<Order, vector<Order>, Cmp> pq;
};

// ============================================================
// DEFI 5 : Analyse avec lambdas chaines
// ============================================================
//
// Statistiques sur un carnet d'ordres : prix moyen, volume total,
// meilleur et pire ordre

struct Stats {
    double avgPrice;
    long long totalVolume;
    double bestPrice;
    double worstPrice;
    int orderCount;
};

Stats analyzeOrders(const vector<Order>& orders) {
    if (orders.empty()) return {0, 0, 0, 0, 0};

    Stats s;
    s.orderCount = (int)orders.size();

    // Volume total
    s.totalVolume = accumulate(orders.begin(), orders.end(), 0LL,
        [](long long acc, const Order& o) { return acc + o.volume; });

    // Prix moyen pondere par volume
    double weightedSum = accumulate(orders.begin(), orders.end(), 0.0,
        [](double acc, const Order& o) { return acc + o.price * o.volume; });
    s.avgPrice = weightedSum / s.totalVolume;

    // Meilleur et pire prix
    auto [minIt, maxIt] = minmax_element(orders.begin(), orders.end(),
        [](const Order& a, const Order& b) { return a.price < b.price; });
    s.bestPrice = maxIt->price;
    s.worstPrice = minIt->price;

    return s;
}

// ============================================================
// Tests
// ============================================================

vector<Order> makeTestOrders() {
    return {
        {1,  100.5, 1000, 50,  "BUY"},
        {2,  100.5, 1500, 30,  "BUY"},
        {3,   99.0,  800, 100, "BUY"},
        {4,  101.0, 1200, 25,  "BUY"},
        {5,  100.5,  900, 80,  "BUY"},
        {6,   98.5,  500, 200, "BUY"},
        {7,  101.0, 1100, 40,  "BUY"},
        {8,   99.0, 1000, 60,  "BUY"},
    };
}

void testSortBuyOrders() {
    cout << "=== Test sortBuyOrders ===" << endl;

    auto orders = makeTestOrders();
    auto sorted = sortBuyOrders(orders);

    cout << "Ordres tries (prix desc, ts asc, vol desc) :" << endl;
    for (auto& o : sorted) o.print();

    // Verifications
    assert(sorted[0].id == 7 || sorted[0].id == 4);  // prix 101.0, ts le plus petit
    assert(sorted[0].price == 101.0);
    // A prix egal 101.0 : id=7 (ts=1100) avant id=4 (ts=1200)
    assert(sorted[0].id == 7);
    assert(sorted[1].id == 4);
    cout << "PASS" << endl;

    cout << endl;
}

void testTotalVolumeInRange() {
    cout << "=== Test totalVolumeInRange ===" << endl;

    auto orders = makeTestOrders();

    long long vol1 = totalVolumeInRange(orders, 100.0, 101.0);
    cout << "Volume dans [100.0, 101.0] : " << vol1 << endl;
    // Orders : id1(50), id2(30), id5(80), id4(25), id7(40) = 225
    assert(vol1 == 225);
    cout << "PASS" << endl;

    long long vol2 = totalVolumeInRange(orders, 99.0, 99.0);
    cout << "Volume dans [99.0, 99.0] : " << vol2 << endl;
    // Orders : id3(100), id8(60) = 160
    assert(vol2 == 160);
    cout << "PASS" << endl;

    cout << endl;
}

void testTopKByVolume() {
    cout << "=== Test topKByVolume ===" << endl;

    auto orders = makeTestOrders();
    auto top3 = topKByVolume(orders, 3);

    cout << "Top 3 par volume :" << endl;
    for (auto& o : top3) o.print();

    assert(top3[0].id == 6);  // volume 200
    assert(top3[1].id == 3);  // volume 100
    assert(top3[2].id == 5);  // volume 80
    cout << "PASS" << endl;

    cout << endl;
}

void testOrderBook() {
    cout << "=== Test OrderBook (priority queue) ===" << endl;

    OrderBook book;
    auto orders = makeTestOrders();
    for (auto& o : orders) book.addOrder(o);

    cout << "Execution dans l'ordre de priorite :" << endl;
    int prev_executed = 0;
    (void)prev_executed;
    double lastPrice = 1e9;

    while (!book.empty()) {
        Order best = book.popBest();
        cout << "  Execute : id=" << best.id
             << " price=" << best.price
             << " ts=" << best.timestamp << endl;
        assert(best.price <= lastPrice + 1e-9);
        lastPrice = best.price;
    }
    cout << "PASS (ordre decroissant de prix respecte)" << endl;

    cout << endl;
}

void testAnalyzeOrders() {
    cout << "=== Test analyzeOrders ===" << endl;

    auto orders = makeTestOrders();
    auto stats = analyzeOrders(orders);

    cout << "Nombre d'ordres : " << stats.orderCount << endl;
    cout << "Volume total : " << stats.totalVolume << endl;
    cout << "Prix moyen pondere : " << stats.avgPrice << endl;
    cout << "Meilleur prix : " << stats.bestPrice << endl;
    cout << "Pire prix : " << stats.worstPrice << endl;

    assert(stats.orderCount == 8);
    assert(stats.totalVolume == 585);
    assert(stats.bestPrice == 101.0);
    assert(stats.worstPrice == 98.5);
    cout << "PASS" << endl;

    cout << endl;
}

int main() {
    testSortBuyOrders();
    testTotalVolumeInRange();
    testTopKByVolume();
    testOrderBook();
    testAnalyzeOrders();

    cout << "Patterns utilises :" << endl;
    cout << "- Comparateur multi-criteres avec lambda et if-chain" << endl;
    cout << "- accumulate avec lambda pour volume range et prix pondere" << endl;
    cout << "- nth_element + lambda pour top-K sans tri complet" << endl;
    cout << "- priority_queue<T, vector<T>, function<bool(T,T)>> avec lambda" << endl;
    cout << "- minmax_element avec comparateur custom" << endl;

    return 0;
}
