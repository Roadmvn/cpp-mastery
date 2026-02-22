// ============================================================
// Chapitre 09 - Challenge HFT : Interface IOrderValidator
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
// ============================================================
// Contexte : Avant d'envoyer un ordre au marche, il passe par
// une chaine de validateurs. Chaque validateur verifie un aspect
// different (prix, quantite, risque, limites). L'interface
// IOrderValidator permet d'ajouter/retirer des validateurs
// sans modifier le code existant.
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

enum class Side : uint8_t { BUY, SELL };

struct Order {
    std::string symbol;
    Side side;
    double price;
    uint32_t quantity;
    double notional() const { return price * quantity; }
};

struct ValidationResult {
    bool valid;
    std::string validator_name;
    std::string message;
};

// Interface : contrat pour tous les validateurs
class IOrderValidator {
public:
    virtual ~IOrderValidator() = default;
    virtual ValidationResult validate(const Order& order) const = 0;
    virtual std::string name() const = 0;
};

// Validateur : prix dans les limites
class PriceValidator : public IOrderValidator {
    double min_price;
    double max_price;
public:
    PriceValidator(double min_px, double max_px)
        : min_price(min_px), max_price(max_px) {}

    ValidationResult validate(const Order& order) const override {
        if (order.price <= 0) {
            return {false, name(), "Prix negatif ou nul"};
        }
        if (order.price < min_price) {
            return {false, name(), "Prix sous le minimum ($" +
                    std::to_string(min_price) + ")"};
        }
        if (order.price > max_price) {
            return {false, name(), "Prix au dessus du maximum ($" +
                    std::to_string(max_price) + ")"};
        }
        return {true, name(), "OK"};
    }

    std::string name() const override { return "PriceValidator"; }
};

// Validateur : quantite dans les limites
class QuantityValidator : public IOrderValidator {
    uint32_t min_qty;
    uint32_t max_qty;
public:
    QuantityValidator(uint32_t min_q, uint32_t max_q)
        : min_qty(min_q), max_qty(max_q) {}

    ValidationResult validate(const Order& order) const override {
        if (order.quantity < min_qty) {
            return {false, name(), "Quantite sous le minimum (" +
                    std::to_string(min_qty) + ")"};
        }
        if (order.quantity > max_qty) {
            return {false, name(), "Quantite au dessus du maximum (" +
                    std::to_string(max_qty) + ")"};
        }
        return {true, name(), "OK"};
    }

    std::string name() const override { return "QuantityValidator"; }
};

// Validateur : notionnel (prix * qty) ne depasse pas la limite
class NotionalValidator : public IOrderValidator {
    double max_notional;
public:
    explicit NotionalValidator(double max_n) : max_notional(max_n) {}

    ValidationResult validate(const Order& order) const override {
        double notional = order.notional();
        if (notional > max_notional) {
            return {false, name(), "Notionnel $" + std::to_string(notional) +
                    " depasse la limite $" + std::to_string(max_notional)};
        }
        return {true, name(), "OK"};
    }

    std::string name() const override { return "NotionalValidator"; }
};

// Validateur : symbole autorise
class SymbolValidator : public IOrderValidator {
    std::vector<std::string> allowed_symbols;
public:
    explicit SymbolValidator(std::vector<std::string> symbols)
        : allowed_symbols(std::move(symbols)) {}

    ValidationResult validate(const Order& order) const override {
        for (const auto& s : allowed_symbols) {
            if (s == order.symbol) return {true, name(), "OK"};
        }
        return {false, name(), "Symbole '" + order.symbol + "' non autorise"};
    }

    std::string name() const override { return "SymbolValidator"; }
};

// Chaine de validation : utilise le polymorphisme
class ValidationChain {
    std::vector<std::unique_ptr<IOrderValidator>> validators;

public:
    void add_validator(std::unique_ptr<IOrderValidator> v) {
        validators.push_back(std::move(v));
    }

    bool validate(const Order& order) const {
        std::cout << "  Validation de " << (order.side == Side::BUY ? "BUY" : "SELL")
                  << " " << order.quantity << " " << order.symbol
                  << " @ $" << std::fixed << std::setprecision(2) << order.price
                  << " (notionnel: $" << order.notional() << ")" << std::endl;

        bool all_valid = true;
        for (const auto& v : validators) {
            auto result = v->validate(order);
            std::cout << "    [" << result.validator_name << "] "
                      << (result.valid ? "PASS" : "FAIL")
                      << " - " << result.message << std::endl;
            if (!result.valid) all_valid = false;
        }

        std::cout << "  Resultat: " << (all_valid ? "ACCEPTE" : "REJETE") << std::endl;
        return all_valid;
    }
};

int main() {
    std::cout << "=== Challenge HFT : Order Validation Chain ===" << std::endl;

    // Configuration de la chaine de validation
    ValidationChain chain;
    chain.add_validator(std::make_unique<SymbolValidator>(
        std::vector<std::string>{"AAPL", "MSFT", "GOOGL", "TSLA", "AMZN"}));
    chain.add_validator(std::make_unique<PriceValidator>(0.01, 10000.0));
    chain.add_validator(std::make_unique<QuantityValidator>(1, 10000));
    chain.add_validator(std::make_unique<NotionalValidator>(1'000'000.0));

    // Ordres a valider
    std::vector<Order> orders = {
        {"AAPL",  Side::BUY,  185.50,  100},     // Valide
        {"MSFT",  Side::SELL, 380.00,  500},      // Valide
        {"HACK",  Side::BUY,  50.00,   200},      // Symbole interdit
        {"GOOGL", Side::BUY,  140.00,  50000},    // Quantite trop grande
        {"TSLA",  Side::SELL, 250.00,  5000},     // Notionnel trop eleve
        {"AMZN",  Side::BUY,  -10.00,  100},      // Prix negatif
    };

    int accepted = 0;
    int rejected = 0;

    for (const auto& order : orders) {
        std::cout << std::endl;
        if (chain.validate(order)) {
            accepted++;
        } else {
            rejected++;
        }
    }

    std::cout << "\n=== Bilan ===" << std::endl;
    std::cout << "Acceptes: " << accepted << "/" << orders.size() << std::endl;
    std::cout << "Rejetes:  " << rejected << "/" << orders.size() << std::endl;

    return 0;
}
