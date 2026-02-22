// ============================================================
// Chapitre 01 - Solution : Les Structures (struct)
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
#include <vector>

// ============================================================
// PARTIE 1 : Struct Etudiant
// ============================================================

struct Etudiant {
    std::string nom;
    int age;
    double moyenne;
};

void afficher_etudiant(const Etudiant& e) {
    std::cout << "Nom: " << e.nom
              << " | Age: " << e.age
              << " | Moyenne: " << e.moyenne << std::endl;
}

// ============================================================
// PARTIE 2 : Struct Cercle avec methodes
// ============================================================

struct Cercle {
    double rayon;

    double aire() const {
        return 3.14159265 * rayon * rayon;
    }

    double perimetre() const {
        return 2 * 3.14159265 * rayon;
    }
};

// ============================================================
// PARTIE 3 : Structs imbriquees + vector
// ============================================================

struct Coordonnee {
    double lat;
    double lon;
};

struct Ville {
    std::string nom;
    int population;
    Coordonnee pos;
};

const Ville& ville_plus_peuplee(const std::vector<Ville>& villes) {
    const Ville* max = &villes[0];
    for (const auto& v : villes) {
        if (v.population > max->population) {
            max = &v;
        }
    }
    return *max;
}

int main() {
    std::cout << "=== PARTIE 1 : Struct Etudiant ===" << std::endl;
    Etudiant alice{"Alice", 21, 15.7};
    afficher_etudiant(alice);

    Etudiant bob{"Bob", 23, 12.3};
    afficher_etudiant(bob);

    std::cout << "\n=== PARTIE 2 : Struct Cercle ===" << std::endl;
    Cercle c{5.0};
    std::cout << "Rayon: " << c.rayon << std::endl;
    std::cout << "Aire: " << c.aire() << std::endl;
    std::cout << "Perimetre: " << c.perimetre() << std::endl;

    std::cout << "\n=== PARTIE 3 : Villes ===" << std::endl;
    std::vector<Ville> villes = {
        {"Paris",     2161000, {48.8566, 2.3522}},
        {"Lyon",      516092,  {45.7640, 4.8357}},
        {"Marseille", 870731,  {43.2965, 5.3698}}
    };

    for (const auto& v : villes) {
        std::cout << v.nom << " - Pop: " << v.population
                  << " - Pos: (" << v.pos.lat << ", " << v.pos.lon << ")"
                  << std::endl;
    }

    const Ville& top = ville_plus_peuplee(villes);
    std::cout << "Ville la plus peuplee: " << top.nom
              << " (" << top.population << " hab.)" << std::endl;

    return 0;
}
