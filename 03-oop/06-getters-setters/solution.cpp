// ============================================================
// Chapitre 06 - Solution : Getters, Setters et Encapsulation
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>

// ============================================================
// PARTIE 1 : Temperature
// ============================================================

class Temperature {
private:
    double celsius = 0.0;

public:
    Temperature() = default;
    explicit Temperature(double c) { set_celsius(c); }

    double get_celsius() const { return celsius; }
    double get_fahrenheit() const { return celsius * 9.0 / 5.0 + 32.0; }
    double get_kelvin() const { return celsius + 273.15; }

    bool set_celsius(double c) {
        if (c < -273.15) {
            std::cerr << "Erreur: " << c << " C est sous le zero absolu" << std::endl;
            return false;
        }
        celsius = c;
        return true;
    }

    bool set_fahrenheit(double f) {
        return set_celsius((f - 32.0) * 5.0 / 9.0);
    }
};

// ============================================================
// PARTIE 2 : CompteBancaire
// ============================================================

class CompteBancaire {
private:
    std::string titulaire;
    double solde = 0.0;

public:
    explicit CompteBancaire(std::string nom) : titulaire(std::move(nom)) {}

    const std::string& get_titulaire() const { return titulaire; }
    double get_solde() const { return solde; }

    bool deposer(double montant) {
        if (montant <= 0) {
            std::cerr << "Depot refuse: montant invalide (" << montant << ")" << std::endl;
            return false;
        }
        solde += montant;
        return true;
    }

    bool retirer(double montant) {
        if (montant <= 0) {
            std::cerr << "Retrait refuse: montant invalide (" << montant << ")" << std::endl;
            return false;
        }
        if (montant > solde) {
            std::cerr << "Retrait refuse: solde insuffisant ("
                      << solde << " < " << montant << ")" << std::endl;
            return false;
        }
        solde -= montant;
        return true;
    }

    void afficher() const {
        std::cout << "Compte de " << titulaire
                  << " | Solde: " << solde << " EUR" << std::endl;
    }
};

// ============================================================
// PARTIE 3 : Requete (fluent interface)
// ============================================================

class Requete {
private:
    std::string url = "";
    std::string methode = "GET";
    int timeout = 30;
    bool ssl = false;

public:
    Requete& set_url(std::string u)      { url = std::move(u); return *this; }
    Requete& set_methode(std::string m)  { methode = std::move(m); return *this; }
    Requete& set_timeout(int t)          { timeout = t; return *this; }
    Requete& set_ssl(bool s)             { ssl = s; return *this; }

    void afficher() const {
        std::cout << methode << " " << (ssl ? "https" : "http")
                  << "://" << url
                  << " | Timeout: " << timeout << "s" << std::endl;
    }
};

int main() {
    std::cout << "=== PARTIE 1 : Temperature ===" << std::endl;
    Temperature t(100.0);
    std::cout << t.get_celsius() << " C = "
              << t.get_fahrenheit() << " F = "
              << t.get_kelvin() << " K" << std::endl;

    t.set_fahrenheit(32.0);
    std::cout << t.get_celsius() << " C = "
              << t.get_fahrenheit() << " F" << std::endl;

    t.set_celsius(-300.0);  // Erreur attendue

    std::cout << "\n=== PARTIE 2 : Compte Bancaire ===" << std::endl;
    CompteBancaire compte("Alice");
    compte.afficher();

    compte.deposer(1000.0);
    compte.afficher();

    compte.retirer(300.0);
    compte.afficher();

    compte.retirer(9999.0);   // Refuse : solde insuffisant
    compte.deposer(-50.0);    // Refuse : montant invalide

    std::cout << "\n=== PARTIE 3 : Requete (fluent) ===" << std::endl;
    Requete req;
    req.set_url("api.example.com/data")
       .set_methode("POST")
       .set_ssl(true)
       .set_timeout(60)
       .afficher();

    Requete req2;
    req2.set_url("localhost:8080/health").afficher();

    return 0;
}
