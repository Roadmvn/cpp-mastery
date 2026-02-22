// ============================================================
// Chapitre 08 - Solution : Polymorphisme et virtual
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

// ============================================================
// PARTIE 1 & 2 : Formes polymorphes
// ============================================================

class Forme {
public:
    virtual ~Forme() = default;
    virtual double aire() const { return 0.0; }
    virtual std::string type() const { return "Forme"; }
    virtual void afficher() const {
        std::cout << type() << " | Aire: " << aire() << std::endl;
    }
};

class Carre : public Forme {
private:
    double cote;
public:
    explicit Carre(double c) : cote(c) {}
    double aire() const override { return cote * cote; }
    std::string type() const override { return "Carre"; }
};

class Cercle : public Forme {
private:
    double rayon;
public:
    explicit Cercle(double r) : rayon(r) {}
    double aire() const override { return 3.14159265 * rayon * rayon; }
    std::string type() const override { return "Cercle"; }
};

class Triangle : public Forme {
private:
    double base;
    double hauteur;
public:
    Triangle(double b, double h) : base(b), hauteur(h) {}
    double aire() const override { return base * hauteur / 2.0; }
    std::string type() const override { return "Triangle"; }
};

// ============================================================
// PARTIE 3 : Override et final
// ============================================================

class Vehicule {
public:
    virtual ~Vehicule() = default;

    virtual void demarrer() {
        std::cout << "  Vehicule: vroom vroom (moteur thermique)" << std::endl;
    }

    virtual void arreter() {
        std::cout << "  Vehicule: moteur coupe" << std::endl;
    }
};

class VoitureElectrique : public Vehicule {
public:
    void demarrer() override {
        std::cout << "  VoitureElectrique: ... (demarrage silencieux)" << std::endl;
    }
};

class Tesla final : public VoitureElectrique {
public:
    void arreter() override {
        std::cout << "  Tesla: mode sentinelle active, veille" << std::endl;
    }
};

int main() {
    std::cout << "=== PARTIE 1 : Formes ===" << std::endl;
    Carre carre(5.0);
    Cercle cercle(3.0);
    Triangle triangle(6.0, 4.0);

    carre.afficher();
    cercle.afficher();
    triangle.afficher();

    std::cout << "\n=== PARTIE 2 : Vector polymorphe ===" << std::endl;
    std::vector<std::unique_ptr<Forme>> formes;
    formes.push_back(std::make_unique<Carre>(10.0));
    formes.push_back(std::make_unique<Cercle>(7.0));
    formes.push_back(std::make_unique<Triangle>(8.0, 3.0));
    formes.push_back(std::make_unique<Carre>(2.5));

    double total = 0.0;
    for (const auto& f : formes) {
        f->afficher();
        total += f->aire();
    }
    std::cout << "Aire totale: " << total << std::endl;

    std::cout << "\n=== PARTIE 3 : Override et final ===" << std::endl;
    std::vector<std::unique_ptr<Vehicule>> vehicules;
    vehicules.push_back(std::make_unique<Vehicule>());
    vehicules.push_back(std::make_unique<VoitureElectrique>());
    vehicules.push_back(std::make_unique<Tesla>());

    for (const auto& v : vehicules) {
        v->demarrer();
        v->arreter();
        std::cout << std::endl;
    }

    return 0;
}
