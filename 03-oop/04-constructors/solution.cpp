// ============================================================
// Chapitre 04 - Solution : Constructeurs et Destructeurs
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>

// ============================================================
// PARTIE 1 : Rectangle
// ============================================================

class Rectangle {
private:
    double largeur;
    double hauteur;

public:
    Rectangle() : largeur(1.0), hauteur(1.0) {}

    Rectangle(double l, double h) : largeur(l), hauteur(h) {}

    double aire() const { return largeur * hauteur; }
    double perimetre() const { return 2 * (largeur + hauteur); }

    void afficher() const {
        std::cout << "Rectangle " << largeur << "x" << hauteur
                  << " | Aire: " << aire()
                  << " | Perimetre: " << perimetre() << std::endl;
    }
};

// ============================================================
// PARTIE 2 : Trace (destructeur)
// ============================================================

class Trace {
private:
    std::string nom;

public:
    Trace(std::string n) : nom(std::move(n)) {
        std::cout << "  Trace [" << nom << "] : cree" << std::endl;
    }

    ~Trace() {
        std::cout << "  Trace [" << nom << "] : detruit" << std::endl;
    }
};

// ============================================================
// PARTIE 3 : Etudiant (membre const)
// ============================================================

class Etudiant {
private:
    const int matricule;
    std::string nom;
    double moyenne;

public:
    Etudiant(int mat, std::string n, double moy = 0.0)
        : matricule(mat), nom(std::move(n)), moyenne(moy) {}

    void modifier_note(double note) {
        moyenne = note;
    }

    void afficher() const {
        std::cout << "Matricule: " << matricule
                  << " | Nom: " << nom
                  << " | Moyenne: " << moyenne << std::endl;
    }
};

int main() {
    std::cout << "=== PARTIE 1 : Rectangle ===" << std::endl;
    Rectangle r1;
    r1.afficher();

    Rectangle r2(5.0, 3.0);
    r2.afficher();

    Rectangle r3{10.0, 7.5};
    r3.afficher();

    std::cout << "\n=== PARTIE 2 : Destructeur ===" << std::endl;
    Trace a("A - main");
    {
        std::cout << "-- Entree dans le bloc --" << std::endl;
        Trace b("B - bloc");
        Trace c("C - bloc");
        std::cout << "-- Sortie du bloc --" << std::endl;
    }
    std::cout << "-- Retour dans main --" << std::endl;

    std::cout << "\n=== PARTIE 3 : Etudiant ===" << std::endl;
    Etudiant e1(10001, "Alice", 16.5);
    e1.afficher();

    Etudiant e2(10002, "Bob");
    e2.afficher();
    e2.modifier_note(14.0);
    e2.afficher();

    std::cout << "\n-- Fin de main, destruction dans l'ordre inverse --" << std::endl;
    return 0;
}
