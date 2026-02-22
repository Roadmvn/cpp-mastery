// ============================================================
// Chapitre 02 - Solution : Les Enumerations (enum)
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
#include <vector>

// ============================================================
// PARTIE 1 : Enum class basique
// ============================================================

enum class Saison { PRINTEMPS, ETE, AUTOMNE, HIVER };

std::string to_string(Saison s) {
    switch (s) {
        case Saison::PRINTEMPS: return "Printemps";
        case Saison::ETE:       return "Ete";
        case Saison::AUTOMNE:   return "Automne";
        case Saison::HIVER:     return "Hiver";
    }
    return "Inconnu";
}

int temperature_moyenne(Saison s) {
    switch (s) {
        case Saison::PRINTEMPS: return 15;
        case Saison::ETE:       return 28;
        case Saison::AUTOMNE:   return 12;
        case Saison::HIVER:     return 3;
    }
    return 0;
}

// ============================================================
// PARTIE 2 : Enum class avec underlying type
// ============================================================

enum class Priorite : uint8_t {
    BASSE    = 1,
    NORMALE  = 5,
    HAUTE    = 8,
    CRITIQUE = 10
};

std::string to_string(Priorite p) {
    switch (p) {
        case Priorite::BASSE:    return "Basse";
        case Priorite::NORMALE:  return "Normale";
        case Priorite::HAUTE:    return "Haute";
        case Priorite::CRITIQUE: return "Critique";
    }
    return "Inconnu";
}

void comparer(Priorite a, Priorite b) {
    auto va = static_cast<uint8_t>(a);
    auto vb = static_cast<uint8_t>(b);

    std::cout << to_string(a) << " (" << static_cast<int>(va) << ") vs "
              << to_string(b) << " (" << static_cast<int>(vb) << ") -> ";

    if (va > vb)      std::cout << to_string(a) << " est plus haute" << std::endl;
    else if (vb > va) std::cout << to_string(b) << " est plus haute" << std::endl;
    else               std::cout << "Meme priorite" << std::endl;
}

// ============================================================
// PARTIE 3 : Enum dans une struct
// ============================================================

enum class Statut { EN_ATTENTE, EN_COURS, TERMINE, ECHEC };

std::string to_string(Statut s) {
    switch (s) {
        case Statut::EN_ATTENTE: return "En attente";
        case Statut::EN_COURS:   return "En cours";
        case Statut::TERMINE:    return "Termine";
        case Statut::ECHEC:      return "Echec";
    }
    return "Inconnu";
}

struct Tache {
    std::string nom;
    Statut statut;
    int progression;  // 0-100
};

void afficher_tache(const Tache& t) {
    std::cout << "[" << to_string(t.statut) << "] "
              << t.nom << " - " << t.progression << "%" << std::endl;
}

int main() {
    std::cout << "=== PARTIE 1 : Saisons ===" << std::endl;
    Saison saisons[] = {Saison::PRINTEMPS, Saison::ETE, Saison::AUTOMNE, Saison::HIVER};
    for (auto s : saisons) {
        std::cout << to_string(s) << " : ~" << temperature_moyenne(s) << " C" << std::endl;
    }

    std::cout << "\n=== PARTIE 2 : Priorites ===" << std::endl;
    std::cout << "sizeof(Priorite) = " << sizeof(Priorite) << " byte(s)" << std::endl;
    comparer(Priorite::BASSE, Priorite::CRITIQUE);
    comparer(Priorite::HAUTE, Priorite::NORMALE);
    comparer(Priorite::HAUTE, Priorite::HAUTE);

    std::cout << "\n=== PARTIE 3 : Taches ===" << std::endl;
    std::vector<Tache> taches = {
        {"Compiler le projet",   Statut::TERMINE,    100},
        {"Ecrire les tests",     Statut::EN_COURS,   45},
        {"Deployer en prod",     Statut::EN_ATTENTE, 0}
    };
    for (const auto& t : taches) {
        afficher_tache(t);
    }

    return 0;
}
