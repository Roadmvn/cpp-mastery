// ============================================================
// Chapitre 07 - Challenge HFT : Instrument -> Stock, Bond, Future
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
// ============================================================
// Contexte : En trading, tous les produits financiers sont des
// "instruments". Mais chaque type a ses proprietes specifiques.
// L'heritage modelise parfaitement cette hierarchie.
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Instrument {
protected:
    std::string symbol;
    std::string exchange;
    double price = 0.0;
    double tick_size;       // Variation minimale de prix
    int lot_size;           // Taille minimale d'un lot

public:
    Instrument(std::string sym, std::string exch, double tick, int lot)
        : symbol(std::move(sym)), exchange(std::move(exch)),
          tick_size(tick), lot_size(lot) {}

    void update_price(double new_price) { price = new_price; }

    const std::string& get_symbol() const { return symbol; }
    double get_price() const { return price; }

    double notional_value(int qty) const {
        return price * qty * lot_size;
    }

    void afficher() const {
        std::cout << std::fixed << std::setprecision(2)
                  << symbol << " @ " << exchange
                  << " | Price: $" << price
                  << " | Tick: " << tick_size
                  << " | Lot: " << lot_size;
    }
};

class Stock : public Instrument {
private:
    double dividend_yield;       // Rendement du dividende (%)
    uint64_t shares_outstanding; // Nombre d'actions en circulation
    std::string sector;

public:
    Stock(std::string sym, std::string exch, double div_yield,
          uint64_t shares, std::string sect)
        : Instrument(std::move(sym), std::move(exch), 0.01, 1),
          dividend_yield(div_yield), shares_outstanding(shares),
          sector(std::move(sect)) {}

    double market_cap() const {
        return price * static_cast<double>(shares_outstanding);
    }

    double annual_dividend_per_share() const {
        return price * dividend_yield / 100.0;
    }

    void afficher() const {
        std::cout << "[STOCK] ";
        Instrument::afficher();
        std::cout << " | Sector: " << sector
                  << " | Div: " << dividend_yield << "%"
                  << " | MCap: $" << std::setprecision(0) << market_cap()
                  << std::setprecision(2) << std::endl;
    }
};

class Bond : public Instrument {
private:
    double coupon_rate;     // Taux du coupon (%)
    double face_value;      // Valeur nominale
    double yield_to_maturity;
    int maturity_years;

public:
    Bond(std::string sym, std::string exch, double coupon,
         double face, double ytm, int maturity)
        : Instrument(std::move(sym), std::move(exch), 0.001, 1),
          coupon_rate(coupon), face_value(face),
          yield_to_maturity(ytm), maturity_years(maturity) {}

    double annual_coupon() const {
        return face_value * coupon_rate / 100.0;
    }

    double current_yield() const {
        if (price == 0) return 0;
        return (annual_coupon() / price) * 100.0;
    }

    bool is_premium() const { return price > face_value; }
    bool is_discount() const { return price < face_value; }

    void afficher() const {
        std::cout << "[BOND]  ";
        Instrument::afficher();
        std::cout << " | Coupon: " << coupon_rate << "%"
                  << " | Face: $" << face_value
                  << " | YTM: " << yield_to_maturity << "%"
                  << " | Mat: " << maturity_years << "y"
                  << " | " << (is_premium() ? "PREMIUM" : (is_discount() ? "DISCOUNT" : "PAR"))
                  << std::endl;
    }
};

class Future : public Instrument {
private:
    std::string underlying;     // Sous-jacent
    double margin_requirement;  // Marge requise (%)
    int contract_size;          // Multiplicateur
    std::string expiry_date;

public:
    Future(std::string sym, std::string exch, std::string under,
           double margin, int contract_sz, std::string expiry)
        : Instrument(std::move(sym), std::move(exch), 0.25, 1),
          underlying(std::move(under)), margin_requirement(margin),
          contract_size(contract_sz), expiry_date(std::move(expiry)) {}

    double contract_value() const {
        return price * contract_size;
    }

    double margin_per_contract() const {
        return contract_value() * margin_requirement / 100.0;
    }

    double leverage() const {
        if (margin_requirement == 0) return 0;
        return 100.0 / margin_requirement;
    }

    void afficher() const {
        std::cout << "[FUT]   ";
        Instrument::afficher();
        std::cout << " | Under: " << underlying
                  << " | Size: " << contract_size
                  << " | Margin: " << margin_requirement << "%"
                  << " | Leverage: " << std::setprecision(0) << leverage() << "x"
                  << std::setprecision(2)
                  << " | Exp: " << expiry_date
                  << std::endl;
    }
};

int main() {
    std::cout << "=== Challenge HFT : Instrument Hierarchy ===" << std::endl;

    // Stocks
    Stock aapl("AAPL", "NASDAQ", 0.55, 15'500'000'000ULL, "Technology");
    aapl.update_price(185.50);

    Stock jpm("JPM", "NYSE", 2.4, 2'900'000'000ULL, "Finance");
    jpm.update_price(195.30);

    // Bonds
    Bond ust10("UST-10Y", "CME", 4.25, 1000.0, 4.30, 10);
    ust10.update_price(985.50);

    Bond corp("CORP-AA", "NYSE", 5.5, 1000.0, 5.8, 5);
    corp.update_price(1020.00);

    // Futures
    Future es("ES-MAR26", "CME", "S&P 500", 5.0, 50, "2026-03-21");
    es.update_price(5150.25);

    Future cl("CL-APR26", "NYMEX", "Crude Oil", 8.0, 1000, "2026-04-20");
    cl.update_price(78.50);

    std::cout << "\n--- Stocks ---" << std::endl;
    aapl.afficher();
    jpm.afficher();

    std::cout << "\n--- Bonds ---" << std::endl;
    ust10.afficher();
    corp.afficher();

    std::cout << "\n--- Futures ---" << std::endl;
    es.afficher();
    cl.afficher();

    // Analyses
    std::cout << "\n--- Analyses ---" << std::endl;
    std::cout << "AAPL Market Cap: $" << std::setprecision(0) << std::fixed
              << aapl.market_cap() << std::endl;
    std::cout << "AAPL Div/share: $" << std::setprecision(2) << aapl.annual_dividend_per_share()
              << std::endl;
    std::cout << "UST-10Y Current Yield: " << ust10.current_yield() << "%" << std::endl;
    std::cout << "ES Contract Value: $" << es.contract_value() << std::endl;
    std::cout << "ES Margin/contract: $" << es.margin_per_contract() << std::endl;
    std::cout << "CL Leverage: " << std::setprecision(0) << cl.leverage() << "x" << std::endl;

    return 0;
}
