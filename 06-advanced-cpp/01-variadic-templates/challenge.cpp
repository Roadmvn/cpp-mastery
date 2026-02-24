// Chapitre 01 — Challenge HFT : Logger variadique formaté
// Compilation : g++ -std=c++17 -Wall -Wextra -O2 -o challenge challenge.cpp
//
// Contexte : En trading haute fréquence, les logs doivent être :
//   - Sans allocation dynamique dans le chemin critique
//   - Capables de formatter n'importe quel type
//   - Estampillés avec un timestamp nanoseconde
//   - Thread-safe (basique ici)
//
// On implémente un logger variadique qui :
//   1. Accepte un niveau (INFO/WARN/ERROR) et N arguments de types quelconques
//   2. Formate le tout en une string sans overhead d'allocation multiple
//   3. Affiche [LEVEL][timestamp_ns] message

#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <chrono>
#include <cstdint>

// ============================================================
// Utilitaire : timestamp en nanosecondes depuis epoch
// ============================================================

inline std::int64_t now_ns() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(
        steady_clock::now().time_since_epoch()
    ).count();
}

// ============================================================
// Niveau de log
// ============================================================

enum class Level { INFO, WARN, ERROR };

constexpr std::string_view level_str(Level l) {
    switch (l) {
        case Level::INFO:  return "INFO ";
        case Level::WARN:  return "WARN ";
        case Level::ERROR: return "ERROR";
    }
    return "?????";
}

// ============================================================
// format_to : écrit tous les args dans un ostringstream
// Utilise un fold expression pour éviter la récursion
// ============================================================

template<typename... Args>
std::string format_args(Args&&... args) {
    std::ostringstream oss;
    (oss << ... << std::forward<Args>(args));
    return oss.str();
}

// ============================================================
// Logger principal
// ============================================================

template<typename... Args>
void log(Level level, Args&&... args) {
    // On construit le message en une seule passe
    std::string msg = format_args(std::forward<Args>(args)...);

    // Timestamp *après* le formatage pour ne mesurer que l'I/O
    std::int64_t ts = now_ns();

    std::cout << "[" << level_str(level) << "]["
              << ts << "] "
              << msg << "\n";
}

// Wrappers pratiques
template<typename... Args>
void log_info(Args&&... args) {
    log(Level::INFO, std::forward<Args>(args)...);
}

template<typename... Args>
void log_warn(Args&&... args) {
    log(Level::WARN, std::forward<Args>(args)...);
}

template<typename... Args>
void log_error(Args&&... args) {
    log(Level::ERROR, std::forward<Args>(args)...);
}

// ============================================================
// Logger conditionnel : n'affiche que si le niveau est >= seuil
// Démontre l'utilisation de sizeof... pour la validation statique
// ============================================================

template<typename... Args>
void log_if(bool condition, Level level, Args&&... args) {
    static_assert(sizeof...(Args) > 0, "log_if() requires at least one message argument");
    if (condition) {
        log(level, std::forward<Args>(args)...);
    }
}

// ============================================================
// Simulation HFT : traitement d'ordres
// ============================================================

struct Order {
    int id;
    double price;
    int quantity;
    std::string symbol;
};

void process_order(const Order& o) {
    log_info("Received order id=", o.id,
             " symbol=", o.symbol,
             " price=", o.price,
             " qty=", o.quantity);

    bool price_valid = (o.price > 0.0 && o.price < 1e6);
    log_if(!price_valid, Level::ERROR,
           "Invalid price for order id=", o.id, " price=", o.price);

    bool qty_large = (o.quantity > 10000);
    log_if(qty_large, Level::WARN,
           "Large order detected: id=", o.id, " qty=", o.quantity);

    log_info("Order id=", o.id, " processed successfully");
}

// ============================================================
// main
// ============================================================

int main() {
    log_info("HFT Logger starting up");

    Order o1{1001, 142.50, 500, "AAPL"};
    Order o2{1002, -5.0, 200, "TSLA"};   // prix invalide
    Order o3{1003, 88.30, 15000, "NVDA"}; // grosse quantite

    process_order(o1);
    process_order(o2);
    process_order(o3);

    // Démonstration : types variés dans un seul log
    log_info("Stats: orders=", 3,
             " valid=", 2,
             " ratio=", 2.0/3.0);

    log_warn("End of session");

    return 0;
}
