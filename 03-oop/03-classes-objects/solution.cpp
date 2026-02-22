// ============================================================
// Chapitre 03 - Solution : Classes et Objets
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

// ============================================================
// PARTIE 1 : Classe Compteur
// ============================================================

class Compteur {
private:
    int valeur = 0;

public:
    void incrementer() { valeur++; }
    void decrementer() { valeur--; }
    void reset() { valeur = 0; }
    int get_valeur() const { return valeur; }
};

// ============================================================
// PARTIE 2 : Classe Vecteur2D
// ============================================================

class Vecteur2D {
private:
    double x = 0.0;
    double y = 0.0;

public:
    double norme() const {
        return std::sqrt(x * x + y * y);
    }

    void afficher() const {
        std::cout << "(" << x << ", " << y << ") norme=" << norme() << std::endl;
    }

    Vecteur2D& ajouter(double dx, double dy) {
        x += dx;
        y += dy;
        return *this;
    }
};

// ============================================================
// PARTIE 3 : Classe ListeNoms
// ============================================================

class ListeNoms {
private:
    std::vector<std::string> noms;

public:
    void ajouter(const std::string& nom) {
        noms.push_back(nom);
    }

    void supprimer(const std::string& nom) {
        auto it = std::find(noms.begin(), noms.end(), nom);
        if (it != noms.end()) {
            noms.erase(it);
        }
    }

    bool contient(const std::string& nom) const {
        return std::find(noms.begin(), noms.end(), nom) != noms.end();
    }

    size_t taille() const {
        return noms.size();
    }

    void afficher() const {
        std::cout << "Liste (" << noms.size() << " elements):" << std::endl;
        for (const auto& n : noms) {
            std::cout << "  - " << n << std::endl;
        }
    }
};

int main() {
    std::cout << "=== PARTIE 1 : Compteur ===" << std::endl;
    Compteur c;
    for (int i = 0; i < 5; ++i) c.incrementer();
    c.decrementer();
    c.decrementer();
    std::cout << "Valeur apres +5 -2 : " << c.get_valeur() << std::endl;
    c.reset();
    std::cout << "Apres reset : " << c.get_valeur() << std::endl;

    std::cout << "\n=== PARTIE 2 : Vecteur2D ===" << std::endl;
    Vecteur2D v;
    v.afficher();
    v.ajouter(3.0, 4.0).ajouter(1.0, -1.0);  // Chainage
    v.afficher();

    std::cout << "\n=== PARTIE 3 : ListeNoms ===" << std::endl;
    ListeNoms liste;
    liste.ajouter("Alice");
    liste.ajouter("Bob");
    liste.ajouter("Charlie");
    liste.ajouter("Diana");
    liste.afficher();

    std::cout << "Contient Bob? " << (liste.contient("Bob") ? "Oui" : "Non") << std::endl;
    liste.supprimer("Bob");
    std::cout << "Apres suppression de Bob:" << std::endl;
    liste.afficher();
    std::cout << "Contient Bob? " << (liste.contient("Bob") ? "Oui" : "Non") << std::endl;

    return 0;
}
