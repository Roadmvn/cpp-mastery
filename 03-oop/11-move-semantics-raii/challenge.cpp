// ============================================================
// Challenge HFT : OrderBook avec Move Semantics
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp && ./challenge
// ============================================================
// Contexte : En HFT (High-Frequency Trading), un OrderBook recoit
// des milliers d'ordres par seconde. Chaque allocation/copie inutile
// coute des microsecondes. On utilise le move semantics pour
// transferer les ordres sans copie, et RAII pour garantir la
// proprete des ressources (locks, buffers, connexions).
//
// Architecture :
//   Order        : donnee d'un ordre, movable
//   OrderBuffer  : buffer d'ordres avec move semantics (comme std::vector)
//   OrderBook    : livre d'ordres avec RAII (acquire/release du matching engine)
//   MarketFeed   : generateur d'ordres qui retourne des OrderBuffer par move
// ============================================================

#include <iostream>
#include <string>
#include <utility>
#include <cstring>
#include <iomanip>
#include <stdexcept>
using namespace std;

// ============================================================
// 1. Order : donnee minimale, movable
// ============================================================

enum class Side : uint8_t { BUY, SELL };

struct Order {
    uint64_t   id;
    char       symbol[8];
    Side       side;
    double     price;
    uint32_t   quantity;

    Order() : id(0), side(Side::BUY), price(0.0), quantity(0) {
        symbol[0] = '\0';
    }

    Order(uint64_t id_, const char* sym, Side s, double px, uint32_t qty)
        : id(id_), side(s), price(px), quantity(qty)
    {
        strncpy(symbol, sym, 7);
        symbol[7] = '\0';
    }

    double notional() const { return price * quantity; }

    void print() const {
        cout << "  Order #" << setw(4) << id
             << " | " << setw(6) << symbol
             << " | " << (side == Side::BUY ? "BUY " : "SELL")
             << " | qty=" << setw(5) << quantity
             << " @ $" << fixed << setprecision(2) << price
             << " | notional=$" << notional() << endl;
    }
};

// ============================================================
// 2. OrderBuffer : buffer dynamique d'ordres avec move semantics
//    (version simplifiee d'un vecteur pour illustrer le move)
// ============================================================

class OrderBuffer {
    Order* data;
    int    count;
    int    capacity;

    void grow() {
        int new_cap = capacity == 0 ? 8 : capacity * 2;
        Order* new_data = new Order[new_cap];
        for (int i = 0; i < count; i++) {
            new_data[i] = std::move(data[i]); // Move chaque order
        }
        delete[] data;
        data     = new_data;
        capacity = new_cap;
    }

public:
    OrderBuffer() : data(nullptr), count(0), capacity(0) {
        cout << "  [OrderBuffer CONSTRUCT]" << endl;
    }

    ~OrderBuffer() {
        delete[] data;
        cout << "  [OrderBuffer DESTRUCT] count=" << count << endl;
    }

    // Copy : alloue et copie chaque element
    OrderBuffer(const OrderBuffer& other)
        : data(other.count > 0 ? new Order[other.capacity] : nullptr),
          count(other.count),
          capacity(other.capacity)
    {
        for (int i = 0; i < count; i++) data[i] = other.data[i];
        cout << "  [OrderBuffer COPY]    count=" << count << endl;
    }

    // Move : vol des pointeurs, O(1)
    OrderBuffer(OrderBuffer&& other) noexcept
        : data(other.data), count(other.count), capacity(other.capacity)
    {
        other.data     = nullptr;
        other.count    = 0;
        other.capacity = 0;
        cout << "  [OrderBuffer MOVE]    count=" << count << endl;
    }

    // Move assignment
    OrderBuffer& operator=(OrderBuffer&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        data     = other.data;
        count    = other.count;
        capacity = other.capacity;
        other.data     = nullptr;
        other.count    = 0;
        other.capacity = 0;
        cout << "  [OrderBuffer MOVE=]   count=" << count << endl;
        return *this;
    }

    OrderBuffer& operator=(const OrderBuffer&) = delete;

    void push(Order&& o) {
        if (count == capacity) grow();
        data[count++] = std::move(o);
    }

    void push(const Order& o) {
        if (count == capacity) grow();
        data[count++] = o;
    }

    int  size()    const { return count;    }
    bool empty()   const { return count == 0; }
    bool valid()   const { return data != nullptr || count == 0; }

    const Order& operator[](int i) const { return data[i]; }

    void printAll(const string& label) const {
        cout << "  --- " << label << " (" << count << " orders) ---" << endl;
        for (int i = 0; i < count; i++) data[i].print();
    }
};

// ============================================================
// 3. RAII : MatchingEngineLock
//    Simule l'acquisition d'un lock sur le matching engine.
//    Garanti de se liberer meme en cas d'exception.
// ============================================================

class MatchingEngineLock {
    string engine_id;
    bool   locked;

public:
    explicit MatchingEngineLock(const string& id)
        : engine_id(id), locked(true) {
        cout << "  [LOCK]   MatchingEngine " << engine_id << " acquis" << endl;
    }

    ~MatchingEngineLock() {
        if (locked) {
            locked = false;
            cout << "  [UNLOCK] MatchingEngine " << engine_id << " libere (RAII)" << endl;
        }
    }

    // Pas de copie : un lock = un proprietaire
    MatchingEngineLock(const MatchingEngineLock&)            = delete;
    MatchingEngineLock& operator=(const MatchingEngineLock&) = delete;

    // Move autorise
    MatchingEngineLock(MatchingEngineLock&& other) noexcept
        : engine_id(std::move(other.engine_id)), locked(other.locked) {
        other.locked = false;
    }

    void unlock() {
        if (locked) {
            locked = false;
            cout << "  [UNLOCK] MatchingEngine " << engine_id << " libere (manuel)" << endl;
        }
    }

    bool isLocked() const { return locked; }
};

// ============================================================
// 4. OrderBook : livre d'ordres avec RAII + move semantics
// ============================================================

class OrderBook {
    string       symbol;
    OrderBuffer  bids;      // Ordres d'achat
    OrderBuffer  asks;      // Ordres de vente
    uint64_t     sequence;

public:
    explicit OrderBook(const string& sym)
        : symbol(sym), sequence(0) {
        cout << "  [OrderBook INIT] " << symbol << endl;
    }

    // Non-copiable
    OrderBook(const OrderBook&)            = delete;
    OrderBook& operator=(const OrderBook&) = delete;

    // Movable
    OrderBook(OrderBook&& other) noexcept
        : symbol(std::move(other.symbol)),
          bids(std::move(other.bids)),
          asks(std::move(other.asks)),
          sequence(other.sequence)
    {
        other.sequence = 0;
        cout << "  [OrderBook MOVE] vers nouveau owner" << endl;
    }

    ~OrderBook() {
        cout << "  [OrderBook DESTRUCT] " << symbol << endl;
    }

    // Ajoute un ordre : move semantics pour eviter la copie
    void addOrder(Order&& order) {
        order.id = ++sequence;
        if (order.side == Side::BUY)  bids.push(std::move(order));
        else                          asks.push(std::move(order));
    }

    // Matching simplifie : le meilleur bid >= meilleur ask -> trade
    void match() {
        cout << "\n  === Matching " << symbol << " ===" << endl;

        // Trouve le meilleur bid (max price) et meilleur ask (min price)
        int best_bid_idx = -1;
        int best_ask_idx = -1;
        double best_bid_price = -1.0;
        double best_ask_price = 1e18;

        for (int i = 0; i < bids.size(); i++) {
            if (bids[i].price > best_bid_price) {
                best_bid_price = bids[i].price;
                best_bid_idx   = i;
            }
        }
        for (int i = 0; i < asks.size(); i++) {
            if (asks[i].price < best_ask_price) {
                best_ask_price = asks[i].price;
                best_ask_idx   = i;
            }
        }

        if (best_bid_idx >= 0 && best_ask_idx >= 0 && best_bid_price >= best_ask_price) {
            cout << "  TRADE EXECUTE ! BID $" << best_bid_price
                 << " >= ASK $" << best_ask_price << endl;
            cout << "  Buyer  : Order #" << bids[best_bid_idx].id << endl;
            cout << "  Seller : Order #" << asks[best_ask_idx].id << endl;
        } else {
            cout << "  Pas de match. Spread : $"
                 << (best_ask_price < 1e17 ? best_ask_price - best_bid_price : 0.0) << endl;
        }
    }

    void print() const {
        cout << "\n  OrderBook : " << symbol << endl;
        bids.printAll("BIDS");
        asks.printAll("ASKS");
    }

    const string& getSymbol() const { return symbol; }
};

// ============================================================
// 5. MarketFeed : generateur d'ordres, retourne par move
// ============================================================

OrderBuffer generateOrders(const char* symbol, int count) {
    OrderBuffer buf;
    double prices[] = { 185.10, 185.15, 185.20, 185.05, 185.25 };
    int    qtys[]   = { 100, 200, 50, 300, 150 };

    for (int i = 0; i < count; i++) {
        Side side = (i % 2 == 0) ? Side::BUY : Side::SELL;
        double px = prices[i % 5] + (i * 0.01);
        uint32_t qty = static_cast<uint32_t>(qtys[i % 5]);
        buf.push(Order(0, symbol, side, px, qty));
    }

    // RVO / NRVO : le compilateur peut elider la copie/move
    // Sinon, move implicite sur le retour d'un local
    return buf;
}

// ============================================================
// MAIN
// ============================================================

int main() {
    cout << "=== Challenge HFT : OrderBook avec Move Semantics ===" << endl;

    // --- Demo 1 : OrderBuffer move vs copy ---
    cout << "\n--- Demo 1 : OrderBuffer - Move vs Copy ---" << endl;
    {
        OrderBuffer buf1;
        buf1.push(Order(0, "AAPL", Side::BUY,  185.50, 100));
        buf1.push(Order(0, "AAPL", Side::SELL, 185.55, 200));
        buf1.push(Order(0, "AAPL", Side::BUY,  185.45, 150));
        buf1.printAll("buf1 original");

        cout << "\n  Move de buf1 -> buf2 (O(1)) :" << endl;
        OrderBuffer buf2 = std::move(buf1);
        buf2.printAll("buf2 apres move");
        cout << "  buf1 valide apres move : " << (buf1.valid() ? "OUI" : "NON") << endl;
        cout << "  buf1 size apres move   : " << buf1.size() << endl;
    }

    // --- Demo 2 : RAII MatchingEngineLock ---
    cout << "\n--- Demo 2 : RAII MatchingEngineLock ---" << endl;
    {
        MatchingEngineLock lock("ME-AAPL");
        cout << "  Lock acquis, traitement des ordres..." << endl;
        cout << "  Lock est actif : " << (lock.isLocked() ? "OUI" : "NON") << endl;
        // Exception simulee : le lock est quand meme libere par RAII
        cout << "  [sortie de scope -> RAII libere le lock]" << endl;
    }

    // --- Demo 3 : OrderBook complet ---
    cout << "\n--- Demo 3 : OrderBook avec RAII + Move ---" << endl;
    {
        MatchingEngineLock lock("ME-MSFT");

        OrderBook book("MSFT");
        book.addOrder(Order(0, "MSFT", Side::BUY,  380.00, 500));
        book.addOrder(Order(0, "MSFT", Side::BUY,  379.95, 1000));
        book.addOrder(Order(0, "MSFT", Side::SELL, 380.05, 300));
        book.addOrder(Order(0, "MSFT", Side::SELL, 380.00, 200));
        book.addOrder(Order(0, "MSFT", Side::BUY,  380.10, 150));

        book.print();
        book.match();

        cout << "\n  Move du book vers un autre owner :" << endl;
        OrderBook book2 = std::move(book);
        book2.print();

        cout << "\n  [sortie de scope -> RAII libere le lock + destructeurs]" << endl;
    }

    // --- Demo 4 : MarketFeed avec retour par move ---
    cout << "\n--- Demo 4 : MarketFeed - retour OrderBuffer par move ---" << endl;
    {
        cout << "  Generation de 6 ordres GOOGL :" << endl;
        OrderBuffer feed = generateOrders("GOOGL", 6);
        feed.printAll("feed GOOGL");

        // Injecte dans un OrderBook
        OrderBook book("GOOGL");
        for (int i = 0; i < feed.size(); i++) {
            // Note: on copie ici car feed[i] retourne une ref const
            Order o = feed[i];
            book.addOrder(std::move(o));
        }
        book.print();
        book.match();
    }

    cout << "\n=== Fin du challenge ===" << endl;
    return 0;
}
