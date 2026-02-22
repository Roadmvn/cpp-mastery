// ============================================================
// Chapitre 07 - Solution : Heritage (Inheritance)
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>

// ============================================================
// PARTIE 1 : Vehicules
// ============================================================

class Vehicule {
protected:
    std::string marque;
    int vitesse_max;

public:
    Vehicule(std::string m, int v) : marque(std::move(m)), vitesse_max(v) {}

    void afficher() const {
        std::cout << "Vehicule: " << marque << " | Vmax: " << vitesse_max << " km/h";
    }
};

class Voiture : public Vehicule {
private:
    int nb_portes;

public:
    Voiture(std::string m, int v, int portes)
        : Vehicule(std::move(m), v), nb_portes(portes) {}

    void afficher() const {
        Vehicule::afficher();
        std::cout << " | Portes: " << nb_portes << std::endl;
    }
};

class Moto : public Vehicule {
private:
    int cylindree;

public:
    Moto(std::string m, int v, int cc)
        : Vehicule(std::move(m), v), cylindree(cc) {}

    void afficher() const {
        Vehicule::afficher();
        std::cout << " | Cylindree: " << cylindree << " cc" << std::endl;
    }
};

// ============================================================
// PARTIE 2 : Formes
// ============================================================

class Forme {
protected:
    std::string nom;

public:
    Forme(std::string n) : nom(std::move(n)) {}

    void afficher() const {
        std::cout << "Forme: " << nom;
    }
};

class Rectangle : public Forme {
private:
    double largeur;
    double hauteur;

public:
    Rectangle(double l, double h) : Forme("Rectangle"), largeur(l), hauteur(h) {}

    double aire() const { return largeur * hauteur; }
    double perimetre() const { return 2 * (largeur + hauteur); }

    void afficher() const {
        Forme::afficher();
        std::cout << " " << largeur << "x" << hauteur
                  << " | Aire: " << aire()
                  << " | Perimetre: " << perimetre() << std::endl;
    }
};

class Cercle : public Forme {
private:
    double rayon;
    static constexpr double PI = 3.14159265;

public:
    Cercle(double r) : Forme("Cercle"), rayon(r) {}

    double aire() const { return PI * rayon * rayon; }
    double perimetre() const { return 2 * PI * rayon; }

    void afficher() const {
        Forme::afficher();
        std::cout << " R=" << rayon
                  << " | Aire: " << aire()
                  << " | Perimetre: " << perimetre() << std::endl;
    }
};

// ============================================================
// PARTIE 3 : Employes (chaine d'heritage)
// ============================================================

class Employe {
protected:
    std::string nom;
    double salaire;

public:
    Employe(std::string n, double s) : nom(std::move(n)), salaire(s) {}

    void afficher() const {
        std::cout << "Employe: " << nom << " | Salaire: " << salaire << " EUR";
    }
};

class Manager : public Employe {
protected:
    int equipe_size;

public:
    Manager(std::string n, double s, int eq)
        : Employe(std::move(n), s), equipe_size(eq) {}

    void afficher() const {
        Employe::afficher();
        std::cout << " | Equipe: " << equipe_size << " pers.";
    }
};

class Directeur : public Manager {
private:
    double budget;

public:
    Directeur(std::string n, double s, int eq, double b)
        : Manager(std::move(n), s, eq), budget(b) {}

    void afficher() const {
        Manager::afficher();
        std::cout << " | Budget: " << budget << " EUR" << std::endl;
    }
};

int main() {
    std::cout << "=== PARTIE 1 : Vehicules ===" << std::endl;
    Voiture v("Toyota", 180, 5);
    v.afficher();

    Moto m("Yamaha", 220, 600);
    m.afficher();

    std::cout << "\n=== PARTIE 2 : Formes ===" << std::endl;
    Rectangle r(10.0, 5.0);
    r.afficher();

    Cercle c(7.0);
    c.afficher();

    std::cout << "\n=== PARTIE 3 : Employes ===" << std::endl;
    Employe e("Alice", 35000);
    e.afficher();
    std::cout << std::endl;

    Manager mg("Bob", 55000, 8);
    mg.afficher();
    std::cout << std::endl;

    Directeur d("Charlie", 90000, 25, 2000000);
    d.afficher();

    return 0;
}
