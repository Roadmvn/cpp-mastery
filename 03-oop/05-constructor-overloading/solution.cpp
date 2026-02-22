// ============================================================
// Chapitre 05 - Solution : Surcharge de Constructeurs
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>

// ============================================================
// PARTIE 1 : Date avec multiples constructeurs
// ============================================================

class Date {
private:
    int jour;
    int mois;
    int annee;

public:
    Date() : jour(1), mois(1), annee(2026) {}

    Date(int a) : jour(1), mois(1), annee(a) {}

    Date(int j, int m, int a) : jour(j), mois(m), annee(a) {}

    void afficher() const {
        std::cout << (jour < 10 ? "0" : "") << jour << "/"
                  << (mois < 10 ? "0" : "") << mois << "/"
                  << annee << std::endl;
    }
};

// ============================================================
// PARTIE 2 : Email avec delegation
// ============================================================

class Email {
private:
    std::string destinataire;
    std::string sujet;
    std::string corps;
    int priorite;

public:
    // Constructeur principal
    Email(std::string dest, std::string suj, std::string body, int prio)
        : destinataire(std::move(dest)), sujet(std::move(suj)),
          corps(std::move(body)), priorite(prio) {}

    // Delegation : sans priorite
    Email(std::string dest, std::string suj, std::string body)
        : Email(std::move(dest), std::move(suj), std::move(body), 0) {}

    // Delegation : juste destinataire et sujet
    Email(std::string dest, std::string suj)
        : Email(std::move(dest), std::move(suj), "", 0) {}

    void afficher() const {
        std::cout << "A: " << destinataire
                  << " | Sujet: " << sujet
                  << " | Priorite: " << priorite
                  << " | Corps: " << (corps.empty() ? "(vide)" : corps)
                  << std::endl;
    }
};

// ============================================================
// PARTIE 3 : Identifiant avec explicit et = delete
// ============================================================

class Identifiant {
private:
    int id;
    std::string label;

public:
    explicit Identifiant(int i, std::string l)
        : id(i), label(std::move(l)) {}

    explicit Identifiant(int i)
        : Identifiant(i, "sans-nom") {}

    // Copie interdite
    Identifiant(const Identifiant&) = delete;
    Identifiant& operator=(const Identifiant&) = delete;

    void afficher() const {
        std::cout << "ID: " << id << " | Label: " << label << std::endl;
    }
};

int main() {
    std::cout << "=== PARTIE 1 : Date ===" << std::endl;
    Date d1;
    std::cout << "Defaut: ";
    d1.afficher();

    Date d2(2030);
    std::cout << "Annee seule: ";
    d2.afficher();

    Date d3(15, 6, 2025);
    std::cout << "Complete: ";
    d3.afficher();

    std::cout << "\n=== PARTIE 2 : Email ===" << std::endl;
    Email e1("alice@corp.com", "Reunion", "Demain a 10h", 2);
    e1.afficher();

    Email e2("bob@corp.com", "Info", "RAS");
    e2.afficher();

    Email e3("admin@corp.com", "Alerte");
    e3.afficher();

    std::cout << "\n=== PARTIE 3 : Identifiant ===" << std::endl;
    Identifiant id1(42, "admin");
    id1.afficher();

    Identifiant id2(99);
    id2.afficher();

    // Identifiant id3 = id1;  // ERREUR : copie interdite
    // Identifiant id4(id1);   // ERREUR : copie interdite
    std::cout << "(copie interdite par = delete)" << std::endl;

    return 0;
}
